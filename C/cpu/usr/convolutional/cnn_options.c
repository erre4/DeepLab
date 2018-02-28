#include <stdio.h>
#include <stdlib.h>
#include "../ann.h"

/*Description:
 * write a convolutional neural network on a file, if that file doesn't exist creates it otherwise overwrite it
 * 
 * Input:
 * 		@char* file: file_path.bin
 * 		@AnnElem* a: pointer to a network structure
 * 		@CNNetwork* cnn: a pointer to convolutional neural network structure
 * Output:
 * 		@int 0: error doesn't occur
 * 		@int 1: error occurs
 * */
int
save_CNN (char *file, AnnElem * a, CNNetwork * cnn)
{
  int i, j, k, ok;
  FILE *f = fopen (file, "w+");
  if (f == NULL)
    return 1;

  if (!fwrite (a, sizeof (struct AnnElem), 1, f))
    return 1;

  if (!fwrite (cnn->neurons, sizeof (int) * (a->hidden_layers + 2), 1, f))
    return 1;

  if (!fwrite (cnn->activations, sizeof (int) * (a->hidden_layers + 1), 1, f))
    return 1;

  if (!fwrite
      (cnn->reg_len_per_layer, sizeof (int) * (a->hidden_layers + 1), 1, f))
    return 1;

  for (i = 0; i < a->hidden_layers + 1; i++)
    {
      if (!fwrite
	  (cnn->regularization[i], sizeof (int) * (cnn->reg_len_per_layer[i]),
	   1, f))
	return 1;
    }

  if (!fwrite (cnn->pooling, sizeof (int) * (a->hidden_layers + 1), 1, f))
    return 1;

  if (!fwrite (cnn->padding, sizeof (int) * (a->hidden_layers + 1), 1, f))
    return 1;

  if (!fwrite (cnn->stride, sizeof (int) * (a->hidden_layers + 1), 1, f))
    return 1;

  if (!fwrite
      (cnn->kernel_size, sizeof (int) * (a->hidden_layers + 1) * 2, 1, f))
    return 1;


  for (i = 1; i < a->hidden_layers + 2; i++)
    {
      if (!fwrite
	  (cnn->b[i - 1], cnn->feature_maps[i] * sizeof (double), 1, f))
	return 1;
    }

  for (i = 1; i < a->hidden_layers + 2; i++)
    {
      if (!fwrite
	  (cnn->w[i - 1],
	   cnn->kernel_size[i - 1][0] * cnn->kernel_size[i -
							 1][0] *
	   sizeof (double), 1, f))
	return 1;
    }

  ok = fclose (f);
  if (ok)
    return 1;
  return 0;

}




/*Description:
 * load a convolutional neural network on a file, if that file doesn't exist creates it otherwise overwrite it
 * 
 * Input:
 * 		@char* file: file_path.bin
 * 		@AnnElem* a: pointer to a network structure
 * 		@CNNetwork* cnn: a pointer to convolutional neural network structure
 * Output:
 * 		@int 0: error doesn't occur
 * 		@int 1: error occurs
 * */
int
load_CNN (char *file, AnnElem * a, CNNetwork * cnn)
{
  int i, j, k, ok;
  FILE *f = fopen (file, "rb");

  cnn = (struct CNNetwork *) malloc (sizeof (struct CNNetwork));

  a = (struct AnnElem *) malloc (sizeof (struct AnnElem));


  if (f == NULL)
    return 1;

  if (!fread (a, sizeof (struct AnnElem), 1, f))
    return 1;

  cnn->neurons = (int *) malloc (sizeof (int) * (a->hidden_layers + 2));

  if (!fread (cnn->neurons, sizeof (int) * (a->hidden_layers + 2), 1, f))
    return 1;

  cnn->activations = sizeof (int) * (a->hidden_layers + 1);

  if (!fread (cnn->activations, sizeof (int) * (a->hidden_layers + 1), 1, f))
    return 1;

  cnn->reg_len_per_layer =
    (int *) malloc (sizeof (int) * (a->hidden_layers + 1));

  if (!fread
      (cnn->reg_len_per_layer, sizeof (int) * (a->hidden_layers + 1), 1, f))
    return 1;

  cnn->regularization =
    (int **) malloc (sizeof (int *) * (a->hidden_layers + 1));

  for (i = 0; i < a->hidden_layers + 1; i++)
    {
      cnn->regularization[i] =
	(int *) malloc (sizeof (int) * cnn->reg_len_per_layer[i]));
      if (!fread
	  (cnn->regularization[i], sizeof (int) * (cnn->reg_len_per_layer[i]),
	   1, f))
	return 1;
    }

  cnn->pooling = (int *) malloc (sizeof (int) * (a->hidden_layers + 1));

  if (!fread (cnn->pooling, sizeof (int) * (a->hidden_layers + 1), 1, f))
    return 1;

  cnn->padding = (int *) malloc (sizeof (int) * (a->hidden_layers + 1));

  if (!fread (cnn->padding, sizeof (int) * (a->hidden_layers + 1), 1, f))
    return 1;

  cnn->stride = (int *) malloc (sizeof (int) * (a->hidden_layers + 1));

  if (!fread (cnn->stride, sizeof (int) * (a->hidden_layers + 1), 1, f))
    return 1;

  cnn->kernel_size =
    (int **) malloc (sizeof (int *) * (a->hidden_layers + 1));

  for (i = 0; i < (a->hidden_layers + 1); i++)
    {
      cnn->kernel_size[i] = (int *) malloc (sizeof (int) * 2);
    }

  if (!fwrite
      (cnn->kernel_size, sizeof (int) * (a->hidden_layers + 1) * 2, 1, f))
    return 1;


  cnn->b = (double **) malloc (sizeof (double *) * (a->hidden_layers + 1));

  cnn->w = (double ***) malloc (sizeof (double **) * (a->hidden_layers + 1));

  for (i = 1; i < a->hidden_layers + 2; i++)
    {
      cnn->b[i - 1] =
	(double *) malloc (sizeof (double) * cnn->feature_maps[i]);
      cnn->w[i - 1] =
	(double **) malloc (sizeof (double *) * cnn->kernel_size[i - 1][0]);
      for (j = 0; j < kernel_size[i][0]; j++)
	{
	  cnn->w[i - 1][j] =
	    (double *) malloc (sizeof (double) * cnn->kernel_size[i - 1][1]);
	}
    }

  for (i = 1; i < a->hidden_layers + 2; i++)
    {
      if (!fread
	  (cnn->b[i - 1], cnn->feature_maps[i] * sizeof (double), 1, f))
	return 1;
    }

  for (i = 1; i < a->hidden_layers + 2; i++)
    {
      if (!fread
	  (cnn->w[i - 1],
	   cnn->kernel_size[i - 1][0] * cnn->kernel_size[i -
							 1][1] *
	   sizeof (double), 1, f))
	return 1;
    }


  if (feof (f))
    {
      ok = fclose (f);
      if (ok)
	return 1;
      return 0;
    }
  fclose (f);
  return 1;
}
