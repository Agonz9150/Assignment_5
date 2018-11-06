#include<stdio.h>

#define NO_ERROR 0
#define NUMBER_OF_ARGUMENTS 2
#define EMPTY_VALUE 0
#define LEFT_SHIFT 10
#define START_COUNT 0
#define ARRAY_SIZE 3
#define MONTH_INDEX 0
#define DAY_INDEX 1
#define YEAR_INDEX 2
#define LOWEST_DIGIT 0
#define HIGHEST_DIGIT 9
#define LEAP_RULE_1 4
#define LEAP_RULE_2 100
#define LEAP_RULE_3 400
#define DIVISIBLE 0
#define LEAP_DAY 1
#define NON_EXISTANT_YEAR 0
#define ASCII_0 48
#define LIMIT_INDEX 1
#define STRING_ERROR -1
#define START_ARRAY 0
#define NO_CAP 0
#define MAKE_NEGATIVE -1
#define FALSE_LINE -1
#define START_INDEX 0
#define BUFFER 256 // Ample space to append input to output

enum Month {JANUARY = 1, FEBRUARY = 2, MARCH = 3, APRIL = 4, MAY = 5, JUNE = 6,
           JULY = 7, AUGUST = 8, SEPTEMBER = 9, OCTOBER = 10, NOVEMBER = 11,
           DECEMBER = 12};

enum Boolean {FALSE = 0, TRUE = 1};
static const int MONTH_DAYS[] = {EMPTY_VALUE,31,28,31,30,31,30,
                                 31,31,30,31,30,31};

static const char *MONTH_NAMES[] = {NULL,"JAN","FEB","MAR",
                                         "APR","MAY","JUN",
                                         "JUL","AUG","SEP",
                                         "OCT","NOV","DEC"};

struct validation
{
   int negative;
   int in_line_location;
   int good_line;
   int date[ARRAY_SIZE];
};

typedef struct validation Validation;
void Char_array_cleanup(char[*],int);
void Input_validation(int);
int Digit_validation(char);
int Add_digit(char,int);
int Is_negative(char);
int Add_negative(int);
void Standard_char_validation(char,Validation *);
void Slash_validation(Validation *);
void New_line_validation(Validation *);
void Clean_validation(Validation *);
int Date_values_check(int[*]);
int Leap_year(int);
int Month_check(int);
int Day_check(int,int,int);
int Year_check(int);
void Send_date(int[*]);
int Limit_validation(char[*]);
void Convert_date();
void Output_date(int[*]);
void Append_file();
