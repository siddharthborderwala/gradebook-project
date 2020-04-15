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

/*
Returns 1 if strings are equal
Takes in two strings to compare
Returns int
*/
int isStrEq(char[], char[]);

// -> core functions

/*
Initializes a new Gradebook Object
Takes in nothing
Returns Gradebook
*/
Gradebook createGradeBook();

/*
Creates a new record in an existing gradebook
Takes in a Pointer to Gradebook and a Record Object
Returns the newly created Record
*/
Record createNewRecord(Gradebook *, Record);

/*
Prints if the record is found, if yes then prints record
Takes in a Pointer to Gradebook and a Name
Returns void
*/
void findRecordByName(Gradebook *, char[]);

/*
Prints if the record is found, if yes then prints record
Takes in a Pointer to Gradebook and a Roll Number
Returns void
*/
void findRecordByRollNum(Gradebook *, rollNum);

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