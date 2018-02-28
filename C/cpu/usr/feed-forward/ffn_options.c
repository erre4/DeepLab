#include <stdio.h>
#include <stdlib.h>
#include "../ann.h"



/*Description:
 * write a feed-forward-network on a file, if that file doesn't exist creates it otherwise overwrite it
 * 
 * Input:
 * 		@char* file: file_path.bin
 * 		@AnnElem* a: pointer to a network structure
 * 		@FFNetwork* ffn: a pointer to feed forward network structure
 * Output:
 * 		@int 0: error doesn't occur
 * 		@int 1: error occurs
 * */
int
save_FFN (char *file, AnnElem * a, FFNetwork * ffn)
{

  int i, j, k, ok;
  FILE *f = fopen (file, "w+");


  if (!fwrite (a, sizeof (struct AnnElem), 1, f))
    return 1;

  if (!fwrite (ffn->neurons, sizeof (int) * (a->hidden_layers + 2), 1, f))
    return 1;

  if (!fwrite (ffn->activations, sizeof (int) * (a->hidden_layers + 1), 1, f))
    return 1;

  if (!fwrite
      (ffn->reg_len_per_layer, sizeof (int) * (a->hidden_layers + 1), 1, f))
    return 1;

  for (i = 0; i < a->hidden_layers + 1; i++)
    {
      if (!fwrite
	  (ffn->regularization[i], sizeof (int) * (ffn->reg_len_per_layer[i]),
	   1, f))
	return 1;
    }



  for (i = 1; i < a->hidden_layers + 2; i++)
    {
      if (!fwrite (ffn->b[i - 1], ffn->neurons[i] * sizeof (double), 1, f))
	return 1;
    }

  for (i = 1; i < a->hidden_layers + 2; i++)
    {
      if (!fwrite
	  (ffn->w[i - 1],
	   ffn->neurons[i] * ffn->neurons[i - 1] * sizeof (double), 1, f))
	return 1;
    }


  ok = fclose (f);
  if (ok)
    return 1;
  return 0;

}


/*Description:
 * load a feed-forward-network from a file.bin
 * Input:
 * 		@char* file: file_path.bin
 * 		@AnnElem* a: pointer to a network structure
 * 		@FFNetwork* ffn: a pointer to feed forward network structure
 * Output:
 * 		@int 0: error doesn't occur
 * 		@int 1: error occurs
 * */
int
load_FFN (char *file, AnnElem * a, FFNetwork * ffn)
{
  int i, j, k, ok;
  FILE *f = fopen (file, "rb");

  ffn = (struct FFNetwork *) malloc (sizeof (struct FFNetwork));

  a = (struct AnnElem *) malloc (sizeof (struct AnnElem));


  if (f == NULL)
    return 1;

  if (!fread (a, sizeof (struct AnnElem), 1, f))
    return 1;

  ffn->neurons = (int *) malloc (sizeof (int) * (a->hidden_layers + 2));

  if (!fread (ffn->neurons, sizeof (int) * (a->hidden_layers + 2), 1, f))
    return 1;

  ffn->activations = sizeof (int) * (a->hidden_layers + 1);

  if (!fread (ffn->activations, sizeof (int) * (a->hidden_layers + 1), 1, f))
    return 1;

  ffn->reg_len_per_layer =
    (int *) malloc (sizeof (int) * (a->hidden_layers + 1));

  if (!fread
      (ffn->reg_len_per_layer, sizeof (int) * (a->hidden_layers + 1), 1, f))
    return 1;

  ffn->regularization =
    (int **) malloc (sizeof (int *) * (a->hidden_layers + 1));

  for (i = 0; i < a->hidden_layers + 1; i++)
    {
      ffn->regularization[i] =
	(int *) malloc (sizeof (int) * ffn->reg_len_per_layer[i]));
      if (!fread
	  (ffn->regularization[i], sizeof (int) * (ffn->reg_len_per_layer[i]),
	   1, f))
	return 1;
    }

  ffn->b = (double **) malloc (sizeof (double *) * (a->hidden_layers + 1));

  ffn->w = (double ***) malloc (sizeof (double **) * (a->hidden_layers + 1));

  for (i = 1; i < a->hidden_layers + 2; i++)
    {
      ffn->b[i - 1] = (double *) malloc (sizeof (double) * ffn->neurons[i]);
      ffn->w[i - 1] =
	(double **) malloc (sizeof (double *) * ffn->neurons[i]);
      for (j = 0; j < neurons[i]; j++)
	{
	  ffn->w[i - 1][j] =
	    (double *) malloc (sizeof (double) * ffn->neurons[i - 1]);
	}
    }

  for (i = 1; i < a->hidden_layers + 2; i++)
    {
      if (!fread (ffn->b[i - 1], ffn->neurons[i] * sizeof (double), 1, f))
	return 1;
    }

  for (i = 1; i < a->hidden_layers + 2; i++)
    {
      if (!fread
	  (ffn->w[i - 1],
	   ffn->neurons[i] * ffn->neurons[i - 1] * sizeof (double), 1, f))
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
