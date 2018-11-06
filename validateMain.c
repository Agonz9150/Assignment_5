#include "Date_check.h"
/*-------------------------------------------------------------------
|Main does the following
|  1)checks if command_line_input is correct(first num of inputs
|                                             then input type)
|      if incorrect, error is printed to screen and kill kode is sent to
|       second program
|   2) goes to Input_validation with the command line inputed
|          validation limit
|
----------------------------------------------------------------------*/
int main(int argc, char *argv[])

{
   if(argc != NUMBER_OF_ARGUMENTS)
   {
      fprintf(stderr,"%s","Incorrect input \n");
      printf("%s","!");
      return NO_ERROR;
   }
   int validation_limit = Limit_validation(argv[LIMIT_INDEX]);
   if(validation_limit == STRING_ERROR)
   {
      fprintf(stderr,"%s"," Command line input is invalid \n");
      printf("%s","!");
      return NO_ERROR;
   }
   Input_validation(validation_limit);
   return NO_ERROR;
}
