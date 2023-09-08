#define SIZE 4
#define COMMAND_MEMORY_SIZE 100
#define MAT_SIZE 16
#define ARRAY_LENGTH(x) (sizeof(x) / sizeof((x)[0]))
#define TRUE 1
#define FALSE 0
#define FAILURE 1
#define SUCCESS 0
#define INVALID_INDEX -1

typedef double mat[SIZE][SIZE];


/*===================================================================================================
this function add one matrix with another
it gets three matrix of the type mat, add the first two and store the result in the theird.
returns a pointer to the theird matrix.
===================================================================================================*/
mat* add_mat(mat mat_x, mat mat_y, mat mat_z);

/*===================================================================================================
this function substruct one matrix from another
it gets three matrix of the type mat, substruct the first two and store the result in the theird.
returns a pointer to the theird matrix.
===================================================================================================*/
mat* sub_mat(mat mat_x, mat mat_y, mat mat_z);

/*===================================================================================================
this function multiply one matrix with another
it gets three matrix of the type mat, multiply the first two and store the result in the theird.
returns a pointer to the theird matrix.
===================================================================================================*/
mat* mul_mat(mat mat_x, mat mat_y, mat mat_z);

/*===================================================================================================
this function multiply one matrix with a real number (scalar)
it gets two matrix of the type mat and a real number, multiply the first matrix with the scalar and store the result in the second matrix.
returns a pointer to the second matrix.
===================================================================================================*/
mat* mul_scalar(mat mat_x, double scalar, mat mat_y);

/*===================================================================================================
this function transpose a matrix
it gets two matrix of the type mat, transpose the first matrix and store the result in the second matrix.
returns a pointer to the second matrix.
===================================================================================================*/
mat* trans_mat(mat mat_x, mat mat_y);

