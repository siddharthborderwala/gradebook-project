#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

// -> -> STRUCTURE DEFINITIONS

/*
rollNum data type
*/
typedef long long int rollNum;

/*
marksheet is a struct which has marks for 5 subjects
*/
typedef struct marksheet
{
	float math;
	float english;
	float science;
	float social_science;
	float sec_lang;
} Marksheet;

/*
record is a struct like a node in a linked list
it has name, roll number, marks (marksheet) and pointer to next record
*/
typedef struct record
{
	char name[50];
	rollNum roll_num;
	Marksheet marks;
	struct record *next;
} Record;
/*
gradebook is a wrapper struct for the head, i.e. pointer to a particular
linked list/gradebook
*/
typedef struct Gradebook
{
	Record *head;
	Record *tail;
} Gradebook;

// -> -> FUNCTION DEFINITIONS

// -> utility functions

/*
Returns the average marks of the 5 subjects
Takes in a Marksheet
Returns a float value
*/
float avgMarks(Marksheet);

/*
Prints the marksheet
Takes in a Marksheet
Returns nothing aka void
*/
void printMarksheet(Marksheet);

/*
Prints the Record
Takes in a Pointer to Record
Returns void
*/
void printRecord(Record *);

/*
Returns 1 if gradebook is empty
Takes in a Pointer to Gradebook
Returns int
*/
int isGradeBookEmpty(Gradebook *);


// -> core functions

/*
Creates a new record in an existing gradebook
Takes the input from the user for record data,
that is, name, roll number, marksheet
Creates the gradebook, if not alreday created.
*/

void addRecord(Gradebook *);

/*
Initializes a new Gradebook Object
Takes in nothing
*/
void defdata(Gradebook *);

/*
Creates a new empty Gradebook Object
Takes in nothing
Returns Gradebook
*/

Gradebook createGradeBook();

/*
Creates a new record in an existing gradebook
Takes in a Pointer to Gradebook and a Record Object
Returns the newly created Record
*/
void createNewRecord(Gradebook *, Record);

/*
Finds the record by a search name if found returns and prints it if third argument is true
Takes in a Pointer to Gradebook and a Name
*/
Record findRecordByName(Gradebook *, char[], bool);

/*
Finds the record by a search roll number if found returns and prints it if third argument is true
Takes in a Pointer to Gradebook and a Roll Number
Returns the record if found
*/
Record findRecordByRollNum(Gradebook *, rollNum, bool);

/*
Updates the name in a record
Takes in a Pointer to Gradebook, a new Name and a search Roll Number
Returns the updated Record/if record not found function terminates
*/
Record updateNameInRecord(char[], rollNum, Gradebook *);

/*
Updates the roll number in a record
Takes in a Pointer to Gradebook, a search Name and a new Roll Number
Returns the updated Record/if record not found function terminates
*/
Record updateRollNumInRecord(char[], rollNum, Gradebook *);

/*
Updates the marksheet in a record
Takes in a Pointer to Gradebook, either a search Name or a search Roll Number and The new Marksheet
Returns the updated Record/if record not found function terminates
*/
Record updateMarksheetInRecord(char[], rollNum, Marksheet, Gradebook *);

/*
Deletes a record in a gradebook
Takes in either a search name or a search roll number and a pointer to gradebook
Returns void
*/
void deleteRecord(char [], rollNum , Gradebook *);

/*
Deletes the record at the head of the gradebook
Takes in a pointer to gradebook
Returns void
*/
void deleteRecordHead(Gradebook *gb_ptr);

/*
Deletes a gradebook
Takes in a pointer to gradebook
Returns void
*/
void deleteGradebook(Gradebook *);

/*
Prints a gradebook
Takes in a Pointer to Gradebook
Returns void
*/
void printGradebook(Gradebook *);
/*
sorts the records in gradebook in ascending or descending order of name
*/
void sortGradebookName(Gradebook *, bool);
/*
sorts the records in gradebook in ascending or descending order of roll num
*/
void sortGradebookRollNum(Gradebook *, bool);
/*
Find the student with max total marks
print this record
*/
void findTopper(Gradebook *);
/*
find the records of students who fail in 1 or more subjects
print these records
*/
void findFailingStudents(Gradebook *);
/*
count the number of records in the gradebook
return the number
*/
int countGradebookRecords(Gradebook *);
/*
print the grades and marksheet of each student in the gradereport 
*/
/*
print the absolute grades of each student in the gradereport
*/

void printAbsGrade(Gradebook *);

/*
print the relative grades of each student in the gradereport
*/
void printRelativeGrading(Gradebook *);
