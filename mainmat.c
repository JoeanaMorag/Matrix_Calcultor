/*===================================================================================================
this program contain the input and output functions of a matrix calcultor, which allow the user to intract with the calcultor.
the user may choose from a set of commands to write or read matrix, and to make mathemtical calculations on them.
===================================================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <regex.h>
#include "mymat.h"

typedef struct _mat_array
  {
    char* name;
    mat *matrix_ptr;
  }mat_array;

char* get_input(int* eof_reached_flag);

char* remove_whitespaces_from_start(char* command_str);

int is_a_number(char* argument, double* number);

int mat_name_to_index(char* mat_name);

char* remove_white_spaces(char *str);

void read_mat(char* command_str, mat_array* mats_x);

void print_mat(mat mat_x);

void handle_add_mat(char* command_str, mat_array* mats_x);

void handle_sub_mat(char* command_str, mat_array* mats_x);

void handle_mul_mat(char* command_str, mat_array* mats_x);

void handle_mul_scalar(char* command_str, mat_array* mats_x);

void handle_trans_mat(char* command_str, mat_array* mats_x);

int main()
{
  char* command_p;
  char* command;
  char* arguments;
  int i, mat_index;
  int eof_reached_flag = 0;
  
  mat MAT_A,MAT_B,MAT_C,MAT_D,MAT_E,MAT_F;
  
  mat_array mats[] = {
  	       {"MAT_A",&MAT_A},
  	       {"MAT_B",&MAT_B},
  	       {"MAT_C",&MAT_C},
  	       {"MAT_D",&MAT_D},
  	       {"MAT_E",&MAT_E},
  	       {"MAT_F",&MAT_F}
  	     };
  
  for(i=0; i < ARRAY_LENGTH(mats); i++)
  {
    memset(mats[i].matrix_ptr, 0, sizeof(mat));
  }

  /*infinity loop that gets the users commands. Ends only with the command "stop".*/
  for(;;)
  {
	  printf("please enter your command (type \"help\" for more info)\n");
	  printf("====================\n");
	  
	  command_p = get_input(&eof_reached_flag);
	  
	  printf("the command you enter is:\n%s\n", command_p);
	  
	  if(command_p[0] == ' ' || command_p[0] == '\t')
	  {
	    command_p = remove_whitespaces_from_start(command_p);
	  }
	  
	  if(command_p == NULL) /*check if the memory allocatin succeeded*/
	  	break; 
	  
	  if(eof_reached_flag == 1)
	  {
	    printf("program terminated ungracefully - required stop command\n");
	    break;
	  }
	  else
	  {
	    
	    if((strchr(command_p, ' ') != NULL) || (strchr(command_p, '\t') != NULL))
	    {
	      command = strtok(command_p, " \t");
	      arguments = remove_white_spaces(&command_p[strlen(command)+1]);
	      
	      for(i = 0; i < strlen(arguments) - 1; i++)
	      {
	        if(arguments[i] == ',' && arguments[i+1] == ',')
	        {
	          printf("Multiple consecutive commas\n");
	        }
	      }
	    }
	    else
	    {
	      command = strtok(command_p, " \t");
	      arguments = NULL;
	    }   
	    if(strcmp(command,"help") == 0)
	    {
	      printf("there are six matrixs in this calculator you can use, named:\n"
	      	     "MAT_A, MAT_B, MAT_C, MAT_D, MAT_E, MAT_F.\n"
	      	     "choose from these commands:\n"
	      	     "- read_mat MAT_X, number, number...\n"
	      	     "this command allow you to initilize a matrix with up to 16 real numbers.\n"
	      	     "given less then 16 numbers the empty places in your matrix will initlize to zero.\n"
	      	     "- print_mat MAT_X\n"
	      	     "this command will print on screen the matrix you chose.\n"
	      	     "- add_mat MAT_X,MAT_Y,MAT_Z\n"
	      	     "this command calculate the addition of the first two matrixs and puts the resulte "
	      	     "in the last matrix.\n"
	      	     "- sub_mat MAT_X,MAT_Y,MAT_Z\n"
	      	     "this command calculate the substitution of the first two matrixs and puts the resulte "
	      	     "in the last matrix.\n"
	      	     "- mul_mat MAT_X,MAT_Y,MAT_Z\n"
	      	     "this command calculate the multiplication of the first two matrixs and puts the resulte "
	      	     "in the last matrix.\n"
	      	     "- mul_scalar MAT_X,real number,MAT_Z\n"
	      	     "this command calculate the multiplication of the first matrix and the real number "
	      	     "and puts the resulte in the last matrix.\n"
	      	     "- trans_mat MAT_X,MAT_Y\n"
	      	     "this command transpose the first matrix and puts the resulte "
	      	     "in the last matrix.\n"
	      	     "- stop\n"
	      	     "use this command to exit the program.\n\n");
	    }
	    else if(arguments != NULL)	    
	    {
	      if(strcmp(command,"read_mat") == 0)
	      {
	        read_mat(arguments, mats);
	      }
	      else if(strcmp(command,"print_mat") == 0)
	      {
	        mat_index = mat_name_to_index(arguments);
	      
	        if (mat_index != INVALID_INDEX)
	        {
		  printf("%s:\n",mats[mat_index].name);
		  print_mat(*mats[mat_index].matrix_ptr);
	        }
	      }
	      else if(strcmp(command,"add_mat") == 0)
	      {	      
	        handle_add_mat(arguments, mats);
	      }
	      else if(strcmp(command,"sub_mat") == 0)
	      {
	        handle_sub_mat(arguments, mats);
	      }
	      else if(strcmp(command,"mul_mat") == 0)
	      {
	        handle_mul_mat(arguments, mats);
	      }
	      else if(strcmp(command,"mul_scalar") == 0)
	      {
	        handle_mul_scalar(arguments, mats);
	      }
	      else if(strcmp(command,"trans_mat") == 0)
	      {
	        handle_trans_mat(arguments, mats);
	      }
	    }
	    else if(strcmp(command,"stop") == 0)
	    {
	      free(command_p);
	      break;
	    }
	    else
	      printf("Undefined command name (%s)\n", command);
	    	
	    free(command_p);
	  } /*end of commands if conditions*/ 
  }/*end of infinity loop*/
	  
  return 0;
}

char* get_input(int* eof_reached_flag)
{
  char* ptr;
  int char_count = COMMAND_MEMORY_SIZE;
  int memory_count = 0;
  
  ptr = (char*)malloc(COMMAND_MEMORY_SIZE);
  if(!ptr)
  {
    printf("Memory allocation failed\n");
    return NULL;
  }
  
  do 
  {
    ptr[memory_count] = getchar();
    char_count --;
    memory_count ++;
    
    if(char_count == 0)
    {
      char* temp_ptr;
      
      temp_ptr = (char*) realloc(ptr, (memory_count + COMMAND_MEMORY_SIZE) * sizeof(char));
      if(!temp_ptr)
      {
        printf("memory allocation failed");
    	return ptr;
      }
      else
      {
        ptr = temp_ptr;
        char_count = COMMAND_MEMORY_SIZE;
      }
    }/*end of realloc allocation*/

  } while(ptr[memory_count - 1] != EOF && ptr[memory_count - 1] != '\n');/*end of do while loop*/

  if(ptr[memory_count - 1] == EOF)
  	*eof_reached_flag = 1;
  	
  if(ptr[0] == '\n')
  {
  	free(ptr);
  	return get_input(eof_reached_flag);
  }
  	
  ptr[memory_count-1] = '\0';
  
  return ptr;
}

/*===================================================================================================
gets a pionter to a string and remove any withspaces from its begining.
return the pointer to the string witout the whitspaces.
===================================================================================================*/
char* remove_whitespaces_from_start(char* command_str)
{
  int count = 0, j, k;
  
    while (command_str[count] == ' ' || command_str[count] == '\t')
        count++;

    for (j = count, k = 0;
         command_str[j] != '\0'; j++, k++) {
        command_str[k] = command_str[j];
    }
    command_str[k] = '\0';
  
    return command_str;
}


/*===================================================================================================
gets command_str which is the sub string of the arguments after the command in the command line,
and the mats[] array. 
a valide command_str will contain a valid matrix name in big letters (MAT_A) and at least one double number
seperated by comma.
example: MAT_A, 15, 222.11, 3
===================================================================================================*/
void read_mat(char* command_str, mat_array* mats_x)
{
  int i = 0, j = 0; 
  int index_mat;
  char* token;
  double new_num;
  
  /*chack if the command ends properly (if line doesn't ends with a comma)*/
  if(command_str[strlen(command_str)-1] == ',')
  {
    printf("Extraneous text after end of command\n");
    return;
  }
  
  remove_white_spaces(command_str);
  
  token = strtok(command_str, ",");
  
  index_mat = mat_name_to_index(token);
  
  /*checks the matrix name*/
  if(index_mat == INVALID_INDEX)
  	return;
  
  token = strtok(NULL, ",");	
  if(token == NULL)/*check if there are arguments in the commend*/
  {
    printf("Missing argument\n");
    return;
  }
  
  memset(mats_x[index_mat].matrix_ptr, 0, sizeof(mat));/*sets the matrix to zero*/
  	
  while(token != NULL)
  {
    if(is_a_number(token, &new_num) == SUCCESS)
    {
      (*mats_x[index_mat].matrix_ptr)[i][j] = new_num;
    }
    else
    	break;
    
    token = strtok(NULL, ",");
    
    j++;
    
    if(j == SIZE)/*move to the next row*/
    {
      j = 0;
      i++;
    }
    
    if(i == SIZE)
    	break;
  }/*end of while loop*/
  
  printf("Your command initilized %s to:\n", mats_x[index_mat].name);
  print_mat(*mats_x[index_mat].matrix_ptr);
  
}/*end of read_mat*/

/*===================================================================================================
chack if the string is a real number
gets char* argument, and a pointer to a double.
if the strind is a number, it is placed in the double number.
the function returns 0 for success or 1 for failure.
===================================================================================================*/
int is_a_number(char* argument, double* number)
{
  char* end;
  double temp_num;
  
  errno = 0;
  
  temp_num = strtod(argument, &end);
  
  if((temp_num != HUGE_VAL) && (errno == 0) && (end[0] == '\0'))
  {
    *number = temp_num;
    return SUCCESS;
  }
  else
  {
    printf("Argument is not a real number (%s)\n", argument);
    return FAILURE;
  }
}


/*===================================================================================================
chacks of the matrix name is valid.
gets a string containing the matrix number, if it is accurate return the index to that matrix in the matrixs array.
if the mane is wrong, prints a worning and returns invalid index (-1)
===================================================================================================*/
int mat_name_to_index(char* mat_name)
{
  if(mat_name == NULL)
  {
    printf("Missing argument\n");
  }
  
  if(strcmp(mat_name,"MAT_A") == 0)
  	return 0;
  else if(strcmp(mat_name,"MAT_B") == 0)
  	return 1;
  else if (strcmp(mat_name,"MAT_C") == 0)
  	return 2;
  else if (strcmp(mat_name,"MAT_D") == 0)
  	return 3;
  else if (strcmp(mat_name,"MAT_E") == 0)
  	return 4;
  else if (strcmp(mat_name,"MAT_F") == 0)
  	return 5;
  else
  {
  	printf("Undefined matrix name: (%s)\n", mat_name);
  	return -1;
  }
}

/*===================================================================================================
prints the matrix in a fine view.
gets an mat argument to the specific matrix it need to print
===================================================================================================*/
void print_mat(mat mat_x)
{
  int i,j;
  for(i=0; i < SIZE; i++)
  {
    for(j=0; j < SIZE; j++)
      printf("%7.2f", mat_x[i][j]);
    
    printf("\n");
  }
}

/*===================================================================================================
remove white spaces from a string.
gets a pointer to a string.
return the pointer to the string without white speces.
===================================================================================================*/
char* remove_white_spaces(char *str)
{
	int i = 0, j = 0;
	while (str[i])
	{
	  if ((str[i] != ' ') && (str[i] != '\t'))
	  {
            str[j] = str[i];
            j++;
	  }
	  i++;
	}
	str[j] = '\0';
	return str;
}

/*===================================================================================================
check the validation of the command line and its arguments befor calling the add_mat functon.
gets the command arguments and the mats array.
if the arguments are incorect or missing it will return without calling add_mat function.
===================================================================================================*/
void handle_add_mat(char* command_str, mat_array* mats_x)
{
  char mat_a[6];
  char mat_b[6];
  char mat_c[COMMAND_MEMORY_SIZE];
  int mat_index_a, mat_index_b, mat_index_c;
  
  if(sscanf(command_str, "%5[^,\n\t],%5[^,\n\t],%s", mat_a, mat_b, mat_c) != 3)
  {
    printf("%s, %s, %s", mat_a, mat_b, mat_c);
    printf("Missing or invalid argument (%s)\n", command_str);
    return;
  }
  
  mat_index_a = mat_name_to_index(mat_a);
  if(mat_index_a == -1)
  	return;
  mat_index_b = mat_name_to_index(mat_b);
  if(mat_index_b == -1)
  	return;
  mat_index_c = mat_name_to_index(mat_c);
  if(mat_index_c == -1)
  	return;
	      
  printf("Your command: %s + %s = %s:\n", mats_x[mat_index_a].name, mats_x[mat_index_b].name,
  					  mats_x[mat_index_c].name);	

  add_mat(*mats_x[mat_index_a].matrix_ptr, *mats_x[mat_index_b].matrix_ptr, *mats_x[mat_index_c].matrix_ptr);
  
  printf("%s is now:\n", mats_x[mat_index_c].name);
  print_mat(*mats_x[mat_index_c].matrix_ptr);
}

/*===================================================================================================
check the validation of the command line and its arguments befor calling the sub_mat functon.
gets the command arguments and the mats array.
if the arguments are incorect or missing it will return without calling sub_mat function.
===================================================================================================*/
void handle_sub_mat(char* command_str, mat_array* mats_x)
{
  char mat_a[6];
  char mat_b[6];
  char mat_c[COMMAND_MEMORY_SIZE];
  int mat_index_a, mat_index_b, mat_index_c;
  
  if(sscanf(command_str, "%5[^,\t\n],%5[^,\t\n],%s", mat_a, mat_b, mat_c) != 3)
  {
    printf("Missing or invalide argument (%s)\n", command_str);
    return;
  }
  
  mat_index_a = mat_name_to_index(mat_a);
  if(mat_index_a == -1)
  	return;
  mat_index_b = mat_name_to_index(mat_b);
  if(mat_index_b == -1)
  	return;
  mat_index_c = mat_name_to_index(mat_c);
  if(mat_index_c == -1)
  	return;
  
  printf("Your command: %s - %s = %s:\n", mats_x[mat_index_a].name, mats_x[mat_index_b].name,
  					  mats_x[mat_index_c].name);	

  sub_mat(*mats_x[mat_index_a].matrix_ptr, *mats_x[mat_index_b].matrix_ptr, *mats_x[mat_index_c].matrix_ptr);
  
  printf("%s is now:\n", mats_x[mat_index_c].name);
  print_mat(*mats_x[mat_index_c].matrix_ptr);
}

/*===================================================================================================
check the validation of the command line and its arguments befor calling the mul_mat functon.
gets the command arguments and the mats array.
if the arguments are incorect or missing it will return without calling mul_mat function.
===================================================================================================*/
void handle_mul_mat(char* command_str, mat_array* mats_x)
{
  char mat_a[6];
  char mat_b[6];
  char mat_c[COMMAND_MEMORY_SIZE];
  int mat_index_a, mat_index_b, mat_index_c;
  
  if(sscanf(command_str, "%5[^,\t\n],%5[^,\t\n],%s", mat_a, mat_b, mat_c) != 3)
  {
    printf("Missing or invalide argument (%s)\n", command_str);
    return;
  }
  
  mat_index_a = mat_name_to_index(mat_a);
  if(mat_index_a == -1)
  	return;
  mat_index_b = mat_name_to_index(mat_b);
  if(mat_index_b == -1)
  	return;
  mat_index_c = mat_name_to_index(mat_c);
  if(mat_index_c == -1)
  	return;
	      
  printf("Your command: %s * %s = %s\n", mats_x[mat_index_a].name, mats_x[mat_index_b].name,
  					 mats_x[mat_index_c].name);	
  					  
  mul_mat(*mats_x[mat_index_a].matrix_ptr, *mats_x[mat_index_b].matrix_ptr, *mats_x[mat_index_c].matrix_ptr);
  
  printf("%s is now:\n", mats_x[mat_index_c].name);
  print_mat(*mats_x[mat_index_c].matrix_ptr);
}

/*===================================================================================================
check the validation of the command line and its arguments befor calling the mul_scalar functon.
gets the command arguments and the mats array.
if the arguments are incorect or missing it will return without calling mul_scalar function.
===================================================================================================*/
void handle_mul_scalar(char* command_str, mat_array* mats_x)
{
  char mat_a[6];
  char mat_b[COMMAND_MEMORY_SIZE];
  double scalar;
  int i, mat_index_a, mat_index_b;

  i = sscanf(command_str, "%5[^,\t\n],%lf,%s", mat_a, &scalar, mat_b);
  
  if(i != 3)
  {
    if(i == 1)
    {
      printf("Second argument is not a scalar\n");
      return;
    }
    printf("Missing or invalide argument (%s)\n", command_str);
    return;
  }
  

  mat_index_a = mat_name_to_index(mat_a);
  if(mat_index_a == -1)
  	return;
  mat_index_b = mat_name_to_index(mat_b);
  if(mat_index_b == -1)
  	return;
	      
  printf("Your command: %s * %7.2lf = %s\n", mats_x[mat_index_a].name, scalar, mats_x[mat_index_b].name);	
  					  
  mul_scalar(*mats_x[mat_index_a].matrix_ptr, scalar, *mats_x[mat_index_b].matrix_ptr);
  
  printf("%s is now:\n", mats_x[mat_index_b].name);
  print_mat(*mats_x[mat_index_b].matrix_ptr);
}

/*===================================================================================================
check the validation of the command line and its arguments befor calling the trans_mat functon.
gets the command arguments and the mats array.
if the arguments are incorect or missing it will return without calling trans_mat function.
===================================================================================================*/
void handle_trans_mat(char* command_str, mat_array* mats_x)
{
  char mat_a[6];
  char mat_b[COMMAND_MEMORY_SIZE];
  int mat_index_a, mat_index_b;
  
  if(sscanf(command_str, "%5[^,\t\n],%s", mat_a, mat_b) != 2)
  {
    printf("Missing or invalide argument (%s)\n", command_str);
    return;
  }
  

  mat_index_a = mat_name_to_index(mat_a);
  if(mat_index_a == -1)
  	return;
  mat_index_b = mat_name_to_index(mat_b);
  if(mat_index_b == -1)
  	return;
	      
  printf("Your command: transpose %s = %s\n", mats_x[mat_index_a].name, mats_x[mat_index_b].name);	
  					  
  trans_mat(*mats_x[mat_index_a].matrix_ptr, *mats_x[mat_index_b].matrix_ptr);
  
  printf("%s is now:\n", mats_x[mat_index_b].name);
  print_mat(*mats_x[mat_index_b].matrix_ptr);
}
