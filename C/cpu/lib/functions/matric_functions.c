#include <stdio.h>
#include <stdlib.h>

/*Description:
 * free matrix takes in input a matrix and its number of rows and frees the heap from that
 * 
 * Input:
 * 		@double** m: matrix m
 * 		@int rows: number of rows of m
 * Output:
 * 		@int 0 if there wasn't any errors
 * */
int
free_matrix (double **m, int rows)
{
  int i;
  for (i = 0; i < rows; i++)
    {
      free (m[i]);
    }
  free (m);
  return 0;
}


/*Description:
 * transpose takes a matrix and computes its transpose
 * 
 * Input:
 * 		@double** m: input matrix
 * 		@int rows: rows of m
 * 		@int cols: columns of m
 * Output:
 * 		@double** transpose: the transpose matrix of m
 * */
double **
transpose (double **m, int rows, int cols)
{
  int i, j;
  double **transpose = (double **) malloc (sizeof (double *) * cols);
  for (i = 0; i < cols; i++)
    {
      transpose[i] = (double *) malloc (sizeof (double) * rows);
      for (j = 0; j < rows; j++)
	{
	  transpose[i][j] = m[j][i];
	}
    }

  return transpose;
}


/*Description:
 * transpose takes a matrix and turns it into a mono-dimensional vector
 * 
 * Input:
 * 		@double** m: input matrix
 * 		@int rows: rows of m
 * 		@int cols: columns of m
 * Output:
 * 		@double*  v: the mono-dimensional vector obtained from m
 * */
double *
from_matrix_to_vector (double **m, int rows, int cols)
{
  int i, j;
  double *v = (double *) malloc (sizeof (double) * rows * cols);
  for (i = 0; i < rows; i++)
    {
      for (j = 0; j < cols; j++)
	{
	  v[i * cols + j] = m[i][j];
	}
    }
  return v;
}

/*Description:
 * transpose takes a vector and turns it into a bi-dimensional matrix
 * 
 * Input:
 * 		@double* v: input vector
 * 		@int rows: number of rows we want that the output matrix has
 * 		@int cols: cnumber of columns we want that the output matrix has
 * Output:
 * 		@double**  m: the bi-dimensional matrix obtained from v
 * */
double **
from_vector_to_matrix (double *v, int rows, int cols)
{
  int i, j;
  double **m = (double **) malloc (sizeof (double *) * rows);
  for (i = 0; i < rows; i++)
    {
      m[i] = (double *) malloc (sizeof (double) * cols);
      for (j = 0; j < cols; j++)
	{
	  m[i][j] = v[i * cols + j];
	}
    }

  return m;
}


/*Description:
 * mul2D computes the matrix multiplication beetween 2 bi-dimensional matrices
 * 
 * Input:
 * 		@double** m1: matrix number 1
 * 		@double** m2: matrix number 2
 * 		@int rows1: number of rows of matrix number 1
 * 		@int cols1: number of columns of matrix number 1 and rows of matrix number 2
 * 		@int cols2: number of columns of matrix number 2
 * Output:
 * 		@double** dot: matrix multiplication of size rows1xcols2
 * */
double **
mul2D_caching_one (double **m1, double **m2, int rows1, int cols1, int cols2)
{
  int i, j, k;
  double sum;
  double **dot = (double **) malloc (sizeof (double *) * rows1);
  for (i = 0; i < rows1; i++)
    {
      dot[i] = (double *) malloc (sizeof (double) * cols2);
      for (j = 0; j < cols2; j++)
	{
	  sum = 0;
	  for (k = 0; k < cols1; k++)
	    {
	      sum += m1[i][k] * m2[k][j];
	    }
	  dot[i][j] = sum;
	}
    }


  return dot;

}




/*Description:
 * mul2D computes the matrix multiplication beetween 2 bi-dimensional matrices
 * 
 * Input:
 * 		@double** m1: matrix number 1
 * 		@double** m2: matrix number 2
 * 		@int rows1: number of rows of matrix number 1
 * 		@int cols1: number of columns of matrix number 1 and rows of matrix number 2
 * 		@int cols2: number of columns of matrix number 2
 * Output:
 * 		@double** dot: matrix multiplication of size rows1xcols2
 * */
double **
mul2D_caching_two (double **m1, double **m2, int rows1, int cols1, int cols2)
{
  int i, j, k;
  double sum;
  double **m = transpose (m2, cols1, cols2);
  double **dot = (double **) malloc (sizeof (double *) * rows1);
  for (i = 0; i < rows1; i++)
    {
      dot[i] = (double *) malloc (sizeof (double) * cols2);
      for (j = 0; j < cols2; j++)
	{
	  sum = 0;
	  for (k = 0; k < cols1; k++)
	    {
	      sum += m1[i][k] * m[j][k];
	    }
	  dot[i][j] = sum;
	}
    }
  free_matrix (m, cols2);
  return dot;


}



/*Description:
 * mul2D computes the matrix multiplication beetween 1 bi-dimensional matricex and 1 mono-dimensional vector
 * 
 * Input:
 * 		@double** m1: matrix
 * 		@double* v: vector
 * 		@int rows: number of rows of matrix
 * 		@int cols: number of columns of matrix and length of vector
 * Output:
 * 		@double* vector: vector multiplication of size rowsx1
 * */
double *
mul1D (double **w, double *v, int rows, int cols)
{
  int i, j;
  double *vector = (double *) calloc (rows, sizeof (double));
  for (i = 0; i < rows; i++)
    {
      for (j = 0; j < cols; j++)
	{
	  vector[i] += w[i][j] * v[j];
	}
    }
  return vector;
}


/*Description:
 * vector_sum computes the sum of 2 vectors
 * 
 * Input:
 * 		@double* v1: vector 1
 * 		@double* v2: vector 2
 * 		@int len: length of vector 1 and 2
 * Output:
 * 		@double* v: vector of size lenx1
 * */
double *
vector_sum (double *v1, double *v2, int len)
{
  int i;
  double *v = (double *) malloc (sizeof (double) * len);
  for (i = 0; i < len; i++)
    {
      v[i] = v1[i] + v2[i];
    }

  return v;
}




/*Description:
 * dot computes the dot_product between 2 vectors
 * 
 * Input:
 * 		@double* v1: vector 1
 * 		@double* v2: vector 2
 * 		@int len: length of vector 1 and 2
 * Output:
 * 		@double* v: vector of size lenx1
 * */
double *
dot (double *v1, double *v2, int len)
{
  int i;
  double *v = (double *) malloc (sizeof (double) * len);
  for (i = 0; i < len; i++)
    {
      v[i] = v1[i] * v2[i];
    }

  return v;
}

/*Description:
 * mul computes the matrix multiplication between 2 vectors
 * 
 * Input:
 * 		@double* v1: vector 1
 * 		@double* v2: vector 2
 * 		@int len: length of vector 1 and 2
 * Output:
 * 		@double sum
 * */
double
mul (double *v1, double *v2, int len)
{
  int i;
  double sum = 0;
  for (i = 0; i < len; i++)
    {
      sum += v1[i] * v2[i];
    }

  return sum;
}




/*Description:
 * dot2D computes the dot_product between 2 matrices
 * 
 * Input:
 * 		@double** v1: matrix 1
 * 		@double** v2: matrix 2
 * 		@int rows: rows of matrices 1 and 2
 * 		@int cols: columns of matrices 1 and 2
 * Output:
 * 		@double** v: matrix of size rowsxcols
 * */
double *
dot2D (double **v1, double **v2, int rows, int cols)
{
  int i, j;
  double **v = (double **) malloc (sizeof (double *) * rows);
  for (i = 0; i < rows; i++)
    {
      v[i] = (double *) malloc (sizeof (double) * cols);
      for (j = 0; j < cols; j++)
	{
	  v[i][j] = v1[i][j] * v2[i][j];
	}

    }

  return v;
}


/*Description:
 * matrix_sum computes the sum of the components of the matrix
 * 
 * Input:
 * 		@double** v1: matrix
 * 		@int rows: rows
 * 		@int cols: columns
 * Output:
 * 		@double sum: sum of the components of the matrix
 * */
double
matrix_sum (double **v1, int rows, int cols)
{
  double sum = 0;
  int i, j;
  for (i = 0; i < rows; i < cols; i++)
    {
      for (j = 0; j < cols; j++)
	{
	  sum += v1[i][j];
	}
    }

  return sum;
}
