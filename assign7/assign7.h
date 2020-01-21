/***********************************************************************
assign7.h by rui026
Purpose:
    Defines constants:
        max constants
        error constants
        boolean constants
    Defines typedef for
        Course  (courseName, courseSched, courseHours, courseSize)
    Prototypes
        Functions created and provided by rui026 (student)
        Utility functions provided by notes
Notes:
    n/a
************************************************************************/
/*** constants ******/
//Maximum constants
#define MAX_LINE_SIZE 100   //Maximum number of character per input line
#define MAX_TOKEN 50        //Maximum number of actual characters for a token


//Error constants (program return values)
#define ERR_COMMAND_LINE_SYNTAX     1   // invalid command line syntax
#define USAGE ONLY                  2   // show usage only
#define ERROR_PROCESSING            99  // error during processing

//Boolean constants
#define FALSE 0
#define TRUE 1

/**** typedef ***/

//Token typdef
typedef char Token[MAX_TOKEN + 1];

// Course typedef used for course values place in the file 
typedef struct
{
    char courseName[64];        // course name
    char courseSched[4];        // days of class {MWF or TR}
    unsigned int courseHours;   // credit hours for course
    unsigned int courseSize;    // Number of students in class
} COURSE;

/********************** prototypes ***********************/
//functions used in program to make it work correctly
void create();
void read();
void update();
void delete();
void menuPrompt();

//Utility routines
void errExit(char szFMT[], ...);
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo);


