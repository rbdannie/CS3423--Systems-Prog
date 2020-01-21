/* INClUDE FILES */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "assign7.h"

/***** files ****/
FILE *pCoursefile;
#define COURSE_FILE "courses.dat"

/********************************************
Purpose: Function FIXES probems with prompt
and while loop.
********************************************/
void menuPrompt(){
    //menu prompt for user
    printf("Enter one of the following actions or press CTRL-D to exit.\n");
    printf("C - create a new course record\n");
    printf("R - read an existing course record\n");
    printf("U - update an existing record\n");
    printf("D - delete an existing record\n");
}

int main() 
{
    char szInputBuffer[100];    //one text line of input
    char User;                  //one character choice from user
    
    menuPrompt();

   //while not working correctly -> puts newline before printing menu-> FIXED!!!
   while(fgets(szInputBuffer,100,stdin) != NULL)
    {
        //scans user input and stores in user variable
        sscanf(szInputBuffer,"%c",&User);
        //scanf("%c",&User);
        //invokes function according to user input
        switch(User)
        {
            case 'C':
            case 'c':
                printf("You have picked create\n");
                create();
                break;
            case 'R':
            case 'r':
                printf("You have picked read\n");
                read();
                break;
            case 'U':
            case 'u':
                printf("You have picked update\n");
                update();
                break;
            case 'D':
            case 'd':
                printf("You have picked delete\n");
                delete();
                break;
            default:
                printf("ERROR: invalid option\n");
                break;
        }//end of switch statment
        
        //asks for user input again
	menuPrompt();
    
    }//end of while loop
    return 0;
}//end of main

int checkForCourseNumber(int course_num)
{
    COURSE crs;         // access to course structure
    long rr;            // used for fread
    long RBA;           // relative byte address

    //open file
    pCoursefile = fopen(COURSE_FILE, "rb");
    RBA = course_num * sizeof(COURSE);
    //seek to desired record in file
    fseek(pCoursefile, RBA, SEEK_SET);
    //reads data at desired position
    rr = fread(&crs, sizeof(COURSE), 1L, pCoursefile);
    fclose(pCoursefile);
    /* if courseHours is 0 then course was deleted,
     * therefore meaning it no longer exists.
     */
    if(crs.courseHours == 0)
        rr = 0;
    return rr;
}//end of checkForCourseNumber function

void create()
{
    COURSE crs;                 //access to course struct
    int course_num;             //course number
    char szInputBuffer[100];    
    int iScanfCnt = 0;
    long lCBA;
    int iWriteNew;              // 1 - wrote 1 record
                                // 0 - error
    int crFseek;
    int checkResult;
    
    printf("Enter a course number: \n");
    fgets(szInputBuffer,100,stdin);
    sscanf(szInputBuffer, "%d", &course_num);
    //iScanfCnt += scanf("%d", &course_num);
    
    //If course exist prints error, and leave create and return to menu prompt
    checkResult = checkForCourseNumber(course_num);
    if(checkResult !=0){
        printf("ERROR: course already exists\n");
        return;
    }
    
    printf("Enter a course name: \n");
    fgets(szInputBuffer,100,stdin);
    sscanf(szInputBuffer, "%30[^\n]",crs.courseName);
    //iScanfCnt += scanf("%[^\n]",crs.courseName);
    
    printf("Enter a course schedule (MWF) or (TR): \n");
    fgets(szInputBuffer,100,stdin);
    sscanf(szInputBuffer,"%s",crs.courseSched);
    //iScanfCnt += scanf("%s",crs.courseSched);
    
    printf("Enter the credit hours for the course: \n");
    fgets(szInputBuffer,100,stdin);
    sscanf(szInputBuffer,"%d",&crs.courseHours);
    //iScanfCnt += scanf("%d",&crs.courseHours);

    printf("Enter the initial course enrollment: \n");
    fgets(szInputBuffer,100,stdin);
    sscanf(szInputBuffer,"%d",&crs.courseSize);
    //iScanfCnt += scanf("%d",&crs.courseSize);

    //if (iScanfCnt < 5)
    //    printf("Only recieved %d valid values. Found : %s\n"
    //        ,iScanfCnt, szInputBuffer);
    
    //testing prints -> DELETE WHEN COMPELTELY FINISHED -> UNEEDED
    printf("your class course number is %d\n", course_num);    
    printf("your course name is %s\n", crs.courseName);    
    printf("your class course schedule is %s\n", crs.courseSched);    
    printf("your course has %d credit hours\n", crs.courseHours);    
    printf("your class course size is %.0d\n", crs.courseSize);    
    
    //open file
    pCoursefile = fopen(COURSE_FILE, "rb+");
    lCBA = course_num * sizeof(COURSE);
    //sets current position based on relative byte offset 
    crFseek = fseek(pCoursefile, lCBA, SEEK_SET); 
    //write data to the course file based on byte offset
    iWriteNew = fwrite(&crs, sizeof(COURSE), 1L, pCoursefile);
    if (iWriteNew != 1)
        printf("Error: encounted error writing record %d to file\n", course_num);
    fclose(pCoursefile);
}//end of create function

void read()
{
    COURSE crs;                 //access to course struct
    int course_num;             //course number
    char szInputBuffer[101];
    int iScanfCnt;
    int checkResult;
    int crFseek;
    long lCBA;
    int rr;
    
    //prompts user for course number and checks if it exists
    printf("Enter a CS course number: \n");
    fgets(szInputBuffer,100,stdin);
    //scanf("%d",&course_num);
    sscanf(szInputBuffer, "%d", &course_num);
    //TESTING PRINT -> DELETE WHEN COMPELTED -> NOT NEEDED
    printf("the course you are looking for is %d\n", course_num);

    //checks if course exists
    checkResult = checkForCourseNumber(course_num);
    if(checkResult == 0){
        printf("ERROR: course not found\n");
        return;
    }

    //open file and read data
    pCoursefile = fopen(COURSE_FILE, "rb+");
    lCBA = course_num * sizeof(COURSE);
    //sets current position based on relative byte offset 
    crFseek = fseek(pCoursefile, lCBA, SEEK_SET); 
    rr = fread(&crs, sizeof(COURSE), 1L, pCoursefile);
    if(rr != 1)
        printf("ERROR: encourted error reading record %d\n", course_num);
    else{ 
        //print read result
        printf("Course number: %d\n", course_num);
        printf("Course name: %s\n", crs.courseName);
        printf("Scheduled days: %s\n",crs.courseSched);
        printf("Credit hours: %d\n", crs.courseHours);
        printf("Enrolled students: %d\n", crs.courseSize);
    }
    fclose(pCoursefile);
}//end of read function

void update()
{
    COURSE newcrs;              //access to new course struct
    COURSE oldcourse;           //access to old course struct
    int course_num;             //course number
    char szInputBuffer[100];
    int iScanfCnt = 0;
    long lCBA;
    long iWriteNew;             // 1 - wrote 1 record
                                // 0 - error
    int crFseek;
    int checkResult;
    int rr;

    //prompts user for course number and checks if it exists
    printf("Enter a course number: \n");
    fgets(szInputBuffer,100,stdin);
    sscanf(szInputBuffer,"%d",&course_num);
    //scanf("%d",&course_num);
    checkResult = checkForCourseNumber(course_num);
    if(checkResult == 0){
        printf("ERROR: course not found\n");
        return;
    }
    printf("Enter a course name: \n");
    fgets(szInputBuffer,100,stdin);
    //scanf("%[^\n]",newcrs.courseName);
    //if new info is not entered then copy null byte to course variable
    if(szInputBuffer[0] == '\n')
        strcpy(newcrs.courseName, "\0");
    //if new info is updated then scan into course variable
    else
        sscanf(szInputBuffer, "%30[^\n]",newcrs.courseName);
    
    printf("Enter a course schedule (MWF) or (TR): \n");
    fgets(szInputBuffer,100,stdin);
    if(szInputBuffer[0] == '\n')
        strcpy(newcrs.courseSched, "\0");
    else
        sscanf(szInputBuffer,"%s",newcrs.courseSched);
    
    printf("Enter the credit hours for the course: \n");
    fgets(szInputBuffer,100,stdin);
    if(szInputBuffer[0] == '\n')
        newcrs.courseHours = 0;
    else
        sscanf(szInputBuffer,"%d",&newcrs.courseHours);

    printf("Enter the initial course enrollment: \n");
    fgets(szInputBuffer,100,stdin);
    if(szInputBuffer[0] == '\n')
        newcrs.courseSize = 0;
    else
        sscanf(szInputBuffer, "%d",&newcrs.courseSize);
    
    //open file and read data
    pCoursefile = fopen(COURSE_FILE, "rb+");
    lCBA = course_num * sizeof(COURSE);
    //sets current position based on relative byte offset 
    fseek(pCoursefile, lCBA, SEEK_SET); 
    rr = fread(&oldcourse, sizeof(COURSE), 1L, pCoursefile);
    if(rr != 1)
        printf("ERROR: encourted error reading record %d\n", course_num);
    
    //Update struct
    if(newcrs.courseName[0] == '\0')
        strcpy(newcrs.courseName, oldcourse.courseName);
    if(newcrs.courseSched[0] == '\0')
        strcpy(newcrs.courseSched, oldcourse.courseSched);
    if(newcrs.courseHours == 0)
        newcrs.courseHours = oldcourse.courseHours;
    if(newcrs.courseSize == 0)
        newcrs.courseSize = oldcourse.courseSize;

    //write updated course info to file
    fseek(pCoursefile, lCBA, SEEK_SET); 
    iWriteNew = fwrite(&newcrs, sizeof(COURSE), 1L, pCoursefile);
    if(rr != 1)
        printf("ERROR: encourted error reading record %d\n", course_num);
    else{
        //TESTING PRINTS -> NOT NEEDED -> DELETE LATER
        printf("Course number: %d\n", course_num);
        printf("Course name: %s\n", newcrs.courseName);
        printf("Scheduled days: %s\n",newcrs.courseSched);
        printf("Credit hours: %d\n", newcrs.courseHours);
        printf("Enrolled students: %d\n",newcrs.courseSize);
    }
    fclose(pCoursefile);
    
}//end of update function

void delete()
{
    COURSE crs;                 //access to course struct
    int course_num;              //course number
    char szInputBuffer[100];
    long lCBA;
    int rr;
    int checkResult;

    //prompts user for course number and checks if it exists
    printf("Enter a course number: \n");
    fgets(szInputBuffer,100,stdin);
    sscanf(szInputBuffer,"%d",&course_num);
    checkResult = checkForCourseNumber(course_num);
    if(checkResult == 0){
        printf("ERROR: course not found\n");
        return;
    }
    //open file and read data
    pCoursefile = fopen(COURSE_FILE, "rb+");
    lCBA = course_num * sizeof(COURSE);
    //sets current position based on relative byte offset 
    fseek(pCoursefile, lCBA, SEEK_SET); 
    rr = fread(&crs, sizeof(COURSE), 1L, pCoursefile);
    if(rr != 1)
        printf("ERROR: encourted error reading record %d\n", course_num);
    
    //change credit hours to 0 so course is no longer valid    
    crs.courseHours = 0;
    
    //write updated course info to file
    fseek(pCoursefile, lCBA, SEEK_SET); 
    fwrite(&crs, sizeof(COURSE), 1L, pCoursefile);
    if(crs.courseHours == 0)
        printf("%d was successfully deleted\n", course_num);
    fclose(pCoursefile);
}//end of delete function



