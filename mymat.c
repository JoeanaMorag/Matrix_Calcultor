/*===================================================================================================
this program include all the matemtical functions for the matrix type.
===================================================================================================*/
#include "mymat.h"

/*===================================================================================================
this function copy one matrix data into another
it gets two matrix of the type mat, and copy the first matrix data into the other.
===================================================================================================*/
void mat_copy(mat mat_x, mat mat_y)
{
  int i,j;
  
  for(i = 0; i < SIZE; i++)
  {
    for(j = 0; j < SIZE; j++)
    {
      mat_y[i][j] = mat_x[i][j];
    }
  }
}

/*===================================================================================================
this function add one matrix with another
it gets three matrix of the type mat, add the first two and store the result in the theird.
returns a pointer to the theird matrix.
===================================================================================================*/
mat* add_mat(mat mat_x, mat mat_y, mat mat_z)
{
  mat mat_temp = {0};
  int i, j;
  
  for(i = 0; i < SIZE; i++)
  {
    for(j = 0; j < SIZE; j++)
    {
      mat_temp[i][j] = mat_x[i][j] + mat_y[i][j];
    }
  }
  
  mat_copy(mat_temp, mat_z);  
  return (mat*)mat_z;
}

mat* sub_mat(mat mat_x, mat mat_y, mat mat_z)
{
  mat mat_temp = {0};
  int i, j;
  
  for(i = 0; i < SIZE; i++)
  {
    for(j = 0; j < SIZE; j++)
    {
      mat_temp[i][j] = mat_x[i][j] - mat_y[i][j];
    }
  }
  
  mat_copy(mat_temp, mat_z);
  return (mat*)mat_z;
}

mat* mul_mat(mat mat_x, mat mat_y, mat mat_z)
{
  mat mat_temp = {0};
  int i, j, k;
  
  for(i = 0; i < SIZE; i++)
  {
    for(j = 0; j < SIZE; j++)
    {
      for(k = 0; k < SIZE; k++)
      {
        mat_temp[i][j] += mat_x[i][k] * mat_y[k][j];
      }
    }
  }
  
  mat_copy(mat_temp, mat_z);
  return (mat*)mat_z;
}

mat* mul_scalar(mat mat_x, double scalar, mat mat_y)
{
  mat mat_temp = {0};
  int i, j;
  
  for(i = 0; i < SIZE; i++)
  {
    for(j = 0; j < SIZE; j++)
    {
      mat_temp[i][j] = mat_x[i][j] * scalar;
    }
  }
  
  mat_copy(mat_temp, mat_y);
  return (mat*)mat_y;
}

mat* trans_mat(mat mat_x, mat mat_y)
{
  mat mat_temp = {0};
  int i, j;
  
  for(i = 0; i < SIZE; i++)
  {
    for(j = 0; j < SIZE; j++)
    {
      mat_temp[i][j] = mat_x[j][i];
    }
  }
  
  mat_copy(mat_temp, mat_y);
  return (mat*)mat_y;
}

