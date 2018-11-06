/*----------------------------------------------------------------
|Alexis Gonzalez
|
----------------------------------------------------------------*/
#include "Date_check.h"
/*---------------------------------------------------------------
|Limit_validation does the following:
|This function takes in a string ( command line input) and checks
|if the input is an int with the following - 
|     while not at end of string-
|     check if the ascii value represents an int, if so store it, if not 
|     return falty.
|if all char's are int values, return resulting int
-----------------------------------------------------------------*/
int Limit_validation(char *limit)
{
   int limit_index = START_COUNT;
   char current_char = *limit;
   int total_value = EMPTY_VALUE;
   int char_value = current_char - ASCII_0;
   while(current_char != '\0')
   {
      if(char_value < LOWEST_DIGIT || char_value > HIGHEST_DIGIT)
      {
         return STRING_ERROR;
      }
      total_value = (total_value * LEFT_SHIFT) + char_value;
      limit_index++;
      current_char = *(limit + limit_index);
      char_value = current_char - ASCII_0;
   }
   return total_value;

}

/* ----------------------------------------------------------------
|Digit_validation does the following- 
|   checks if inputed char represents an int by subtracting ascii_0 
|   from it.
|    If the resulting value is not in range of an int, return false
|     else- return true
---------------------------------------------------------------------*/
int Digit_validation(char current_char)
{
   int current_char_val = EMPTY_VALUE;
   current_char_val = current_char - ASCII_0;
   if(current_char_val < LOWEST_DIGIT || 
      current_char_val > HIGHEST_DIGIT)
   {
      return FALSE;
   }
   return TRUE;
}
/*-------------------------------------------------------------------
|Add_digit does the following- 
|The function takes in an inital value, and the char whose value is
| to be added to the end. This function assumes the char is representing
| a single digit. 
| The char is subtracted by ascii_0 to obtain it's int value, and
| the inital value is left_shifed by 1 place ( multiplied by 10) and
| the char's int value is added on.
| returns altered value
-------------------------------------------------------------------*/
int Add_digit(char current_char, int value)
{
   int current_char_val = EMPTY_VALUE;
   current_char_val = current_char - ASCII_0;
   value = value * LEFT_SHIFT + current_char_val;
   return value;
}
/*--------------------------------------------------------------
| Is_negative does the following-
|  This function takes in a char. If the char is equal to '-'
|  return true. if not, return false.
---------------------------------------------------------------*/
int Is_negative(char current_char)
{
   if(current_char == '-')
   {
      return TRUE;
   }
   return FALSE;
}
/*-------------------------------------------------------------
|Add_negative does the following-
|This function takes in an int, and multiplies it by -1
|Returns the negative value.
-------------------------------------------------------------*/
int Add_negative(int value)
{
   value = value * MAKE_NEGATIVE;
   return value;
}
/*--------------------------------------------------------------
|Standard_char_validation does the following - 
|This function takes in a char (not '/','\n',or 'EOF')
|  and a Validation type pointer ( used to keep track if a line 
|  is valid)
|The function performs the following 2 test-
|    1) Negative test
|     The function checks if the char is negative ( using a function)
|     If yes, the function checks if the current value 
|     has already revieved a negative(--1234) or if the negative is at 
|     the middle of the value ( ex. 12-34). If any of these are true,
|     the line is marked as bad ( (*line).good_line=FALSE). If both
|     are false , the value is marked as negative ( (*line).negative
|     = TRUE)
|
|   2) Digit/Overflow test
|     If negative check fails, the function now test if the char is
|     a digit ( using a function). If it's not, the line is flaged
|     as bad ( ex. A -> (*line).good_line = FALSE) If the check 
|     succeds, a test variable is assigned the current value
|     of whatever part of the date is being tested, and adds the 
|     digit to the end of it ( using a function). If the test overflows
|     then the line is marked as bad. If there is no overflow, the 
|     current tested part of the date is assigned the test value
---------------------------------------------------------------*/
void Standard_char_validation( char current_char, Validation *line)
{
   int negative_test = EMPTY_VALUE;
   int digit_validation = EMPTY_VALUE;
   int overflow_test = EMPTY_VALUE;
   negative_test = Is_negative(current_char);
   if(negative_test == TRUE && (*line).negative == TRUE)
   {
      (*line).good_line = FALSE;
   }
   if(negative_test == TRUE && (*line).negative == FALSE)
   {
     
      (*line).negative = TRUE;
      if((*line).date[(*line).in_line_location] != EMPTY_VALUE)
      {
         (*line).good_line = FALSE;
      }
   }
   if(negative_test == FALSE)
   {
      digit_validation = Digit_validation(current_char);
      if(digit_validation == FALSE)
      {
         (*line).good_line = FALSE;
      }
      else
      {
         overflow_test = 
         Add_digit(current_char,(*line).date[(*line).in_line_location]);
         if(overflow_test < (*line).date[(*line).in_line_location])
         {
            (*line).good_line = FALSE;
         }
         else
         {
            (*line).date[(*line).in_line_location] = overflow_test;
         }
      }

   }
}

/*-------------------------------------------------------------------
|Slash_validation does the following - 
|The function is called apon when a / is reached in the function 
| Input_validation. Validation * input used to keep track of line details
| The function does 2 checks: 
|  1) Negative check on month and day values
|       If the month or day values are found with a negative flag
|       the line is flaged invalid
|  2) To many / check
|        If the line has already reached the last possible date value
|        (tracked by (*line).in_line_location) then the line is flaged
|        invalid
|        If check 2 passes, then in_line_location is incremented.
--------------------------------------------------------------------*/
void Slash_validation(Validation *line)
{
   if((*line).negative == TRUE && (*line).in_line_location < YEAR_INDEX)
   {
      (*line).good_line = FALSE;
      (*line).negative = FALSE;
   }
   if((*line).in_line_location > ARRAY_SIZE)
   {
      (*line).good_line = FALSE;
   }
   else
   {
      (*line).in_line_location++;
   }

}
/*------------------------------------------------------------
|New_line_validation does the following- 
|  Validation *line used to keep track of line details
|  The function first checks if the year value needs the negative applied
|          if so, the negative is applied ( using a function)
|  Next the function checks if the line is still valid. If so, the 
|  function does the following - Sends the date values to be checked,
|  if they are validated they are sent out to be printed. If it fails
|  the line is marked as invalid.
-----------------------------------------------------------------*/
void New_line_validation (Validation *line)
{
   int valid_date = EMPTY_VALUE;
   if((*line).negative == TRUE && (*line).in_line_location == YEAR_INDEX)
   {
      (*line).date[YEAR_INDEX] = Add_negative((*line).date[YEAR_INDEX]);
   }
   if((*line).good_line == TRUE)
   {
      valid_date = Date_values_check((*line).date);
      if(valid_date == TRUE)
      {
         Send_date((*line).date);
      }
      else 
      {
         (*line).good_line = FALSE;
      }
   }
}
/*-----------------------------------------------------------------
|Clean_validation does the following
|  This function is used to initalize or clean up the Validation type
|  For a new line (new lines are assumed to be good untill an issue
|  occurs)
------------------------------------------------------------------*/
void Clean_validation(Validation *line)
{
   (*line).negative = FALSE;
   (*line).good_line = TRUE;
   (*line).in_line_location = START_ARRAY;
   (*line).date[MONTH_INDEX] = EMPTY_VALUE;
   (*line).date[DAY_INDEX] = EMPTY_VALUE;
   (*line).date[YEAR_INDEX] = EMPTY_VALUE;
}
/*----------------------------------------------------------------
|Input Validation does the following- 
|This function controls the validation step for the input files.
|
|The function takes in a max_input and sets up and initalizes a Validation
|Structure to keep track of line validation details. 
| 
|   First the function checks if there is a limit to the validation.
|   If there is it's assigned to input left. If there is not (input = 0)
|   then the function is flaged to have no limit.
|  Next the getchar loop is executed - until EOF or until the input_left
|  drops to zero (only EOF if input is uncapped)
|  The loop checks if the following 3 conditions occur:
|  1) char != EOF,/,\n
|         char is passed to Standard_char_validation
|  2) char = /
|         Slash_input_validation is called
|  3) char = \n or EOF
|          New_line_validation is called
|          if the line is flagged as good line, and there is a input
|              cap, the input_left is decremented. 
|          Validation gets re-initalized
|   Once the loop finshes, the program prints "0/0/0";
------------------------------------------------------------------*/
void Input_validation(int max_input)
{ 
   Validation *line;
   Validation input;
   line = &input;
   Clean_validation(line);
   int full_input = FALSE;
   int input_left = max_input;
   char current_char = NULL;
   if ( max_input == NO_CAP)
   {
      full_input = TRUE;
   }
   while (current_char != EOF &&
         (full_input == TRUE || input_left > EMPTY_VALUE))
   {  

      current_char = getchar();
      if(current_char != EOF && current_char != '/' && current_char != '\n')
      {
         Standard_char_validation(current_char,line);
      }
      if(current_char == '/')
      {
         Slash_validation(line);
      }
      if(current_char == '\n' || current_char == EOF)
      {
         New_line_validation(line);
         if((*line).good_line == TRUE && full_input == FALSE)
         {
            input_left--;
         }
         Clean_validation(line);
      }
   }
 printf("%s","!");
}


/*-------------------------------------------------------------
| Date_values_check does the following -
|  This function takes in a date array organized as [month,day,year]
|
|  The function first checks if the year is valid ( using a function)
|  If valid year is true the following occurs:
|   The function checks if the year is a leap year( using a function)
|   the result gets sent to day check ( does both month and day check)
|   If the result is true, then True is returned.
| If either Year or Day check is false, False is returned.
|
-----------------------------------------------------------------------*/
int Date_values_check(int date[])
{
   int leap_year_check = FALSE;
   int valid_day = EMPTY_VALUE;
   int valid_year = EMPTY_VALUE;
   valid_year = Year_check(date[YEAR_INDEX]);
   if(valid_year == TRUE)
   {
      leap_year_check = Leap_year(date[YEAR_INDEX]);
      valid_day = 
        Day_check(date[MONTH_INDEX],date[DAY_INDEX],leap_year_check);
   }
   if(valid_year == TRUE && valid_day == TRUE)
   {
      return TRUE;
   }
   return FALSE;
}
/*--------------------------------------------------------------
| Leap_year does the following -
|  Checks if the inputed year is a leap year by the following rules
|   year % 4 = 0 -> Is a leap year, unless
|            year % 100 = 0 -> not a leap year, unless
|                year % 400 = 0 -> is a leap year
----------------------------------------------------------------*/
int Leap_year(int year)
{
   if((year % LEAP_RULE_1) == DIVISIBLE)
   {
      if((year % LEAP_RULE_2) == DIVISIBLE)
      {
         if((year % LEAP_RULE_3) == DIVISIBLE)
         {
            return TRUE;
         }
         else
         {
            return FALSE;
         }
      }
      else
      {
         return TRUE;
      }
    }
   return FALSE;
}
/*----------------------------------------------------------------
|Month_check does the following
|
|Checks if a month exist. If yes, returns true, if no, returns false
-----------------------------------------------------------------*/
int Month_check(int month)
{
   if(month <= DECEMBER && month >= JANUARY)
   {
      return TRUE;
   }
   else
   {
      return FALSE;
   }
}
/*----------------------------------------------------------------
|Day_check does the following
|
|  Function takes in a month and day value and a value representing 
|  the existance of a leap year.
|  First, the month is checked by a function. If it exist, the
|  function then checks if the month is feburary. If the month is 
|  If the month is feburary, the day check is performed as follows
|   If leap year - check if day <= MONTH_DAYS[FEBRUARY] + 1
|   If not leap year - check if day <= MONTH_DAYS[FEBRUARY]
|  If the month is not feburary, the following applies
|   check if day <= MONTH_DAYS[MONTH]
|  If the day check passes, true is return. If it fails, false is returned
--------------------------------------------------------------------*/
int Day_check(int month,int day,int leap_year)
{
   int valid_month = EMPTY_VALUE;
   valid_month = Month_check(month);
   if (valid_month == TRUE)
   {
      if (month == FEBRUARY)
      {
         if(leap_year == TRUE)
         {
            if(day <= (MONTH_DAYS[FEBRUARY] + LEAP_DAY))
            {
               return TRUE;
            }
            else
            {
               return FALSE;
            }
         }
      }
      if(day <= (MONTH_DAYS[month]))
      {
         return TRUE;
      }
   }
   return FALSE;
}
/*-------------------------------------------------------------
|Year_check does the following
|Checks if inputed year is not equal to zero. Returns true if
|Year != 0, False otherwise
---------------------------------------------------------------*/
int Year_check(int year)
{
   if(year == NON_EXISTANT_YEAR)
   {
      return FALSE;
   }
   return TRUE;
}
/*-----------------------------------------------------
|Send_date does the following
|  Takes in a validated date array and prints it in the 
|  following maner
|    month/day/year
--------------------------------------------------------*/
void Send_date(int date[])
{
   printf("%d/%d/%d\n",
   date[MONTH_INDEX],date[DAY_INDEX],date[YEAR_INDEX]);

}
/*--------------------------------------------------
|Convert_date does the following
|
| The function assumes all input is checked.
| The function grabs chars from the input stream in an attempt to
|   grab date values and send them to be printed.
|   The function works on 5 basic checks
|
|   Char = digit -> add digit to current in_line_location value
|   char = / -> increment location line
|  char = - ->  mark as negative year
|   char = \n -> send line, restart counters for new line
|   char = ! -> stop scaning
-----------------------------------------------------------*/

void Convert_date()
{
   char current_char = NULL;
   int date[] = {EMPTY_VALUE,EMPTY_VALUE,EMPTY_VALUE};
   int in_line_location = START_INDEX;
   int negative = EMPTY_VALUE;
   while(current_char != '!')
   {
      current_char = getchar();
      if(current_char != '/' && current_char !='\n' && current_char != '!'
         && current_char != '-')
      {
         date[in_line_location] = 
         Add_digit(current_char, date[in_line_location]);
      }
      if(current_char == '/')
      {
         in_line_location++;
      }
      if(current_char == '-')
      {
         negative = TRUE;
      }
      if(current_char == '\n')
      {
         if(negative == TRUE)
         {
            date[YEAR_INDEX] = Add_negative(date[YEAR_INDEX]);
            negative = FALSE;
         }
         Output_date(date);
         date[MONTH_INDEX] = EMPTY_VALUE;
         date[DAY_INDEX] = EMPTY_VALUE;
         date[YEAR_INDEX] = EMPTY_VALUE;
         in_line_location = START_INDEX;
      }
   }
}
/*-------------------------------------------------------
|Output_date does the following: 
|   prints the date in the following format : 
|                  day  First_3_leters_of_month Year
----------------------------------------------------------*/
void Output_date(int date[])
{
   printf("%.2d  ",date[DAY_INDEX]);
   printf("%s  ",MONTH_NAMES[date[MONTH_INDEX]]);
   printf("%-d \n",date[YEAR_INDEX]);

}
/*----------------------------------------------------------------
|  Append_file does the following
|     Opens the orignal input file (as read) and scans every line
|     prints each line to the output stream
|     closes open file
--------------------------------------------------------------*/
void Append_file()
{
   FILE *orignal;
   char buffer[BUFFER];
   orignal = fopen("dates.dat","r");

   while(fgets(buffer, sizeof(buffer),orignal))
   {
      printf("%s", buffer);
   }
   fclose(orignal);
   
}
   
