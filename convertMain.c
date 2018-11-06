#include "Date_check.h"
/*----------------------------------------------------------
| The main does the following 3 process
|
|   Runs Convert_date to handle the input stream
|   Prints 2 blamk lines to the input_stream
|   Runs Append_fime to append orignal File (needs dates.dat)
|
|
-------------------------------------------------------------*/
int main()
{
   Convert_date();
   printf("\n\n");
   Append_file();
   return NO_ERROR;
}
