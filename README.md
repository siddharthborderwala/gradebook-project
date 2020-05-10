# Gradebook-project
A gradebook, implementation of Linked List data structure.  
This project can be used as a library.  

# Features
  * Create Record
  * Delete Record
  * Update Record
  * Read Record
  * Create Gradebook
  * Print GradeBook
  * Delete GradeBook
  * Search record in Gradebook by Roll number or name
  * Update the various details of any record in the gradebook
  * Sort the records in gradebook by roll number or name
  * Find the topper among the students whose records are entered
  * Count the number of records entered in the gradebook
  * Find out the absolute grades of each student in various subjects
  * Find out the relative grades of each student in various subjects

# To look at the Demo
```sh
#first make sure you're in the correct directory

#if your OS supports make command
make

#else use gcc
gcc test.c gradebook.c --no-warnings

#run the executable
#for unix
./a.out
#for windows
a.exe
```


# Documentation
### The following is a reference for the defined data-structures  
```c
/*
rollNum data type
*/
typedef long long int rollNum;

/*
marksheet is a struct which has marks for 5 subjects
*/
typedef struct marksheet {
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
typedef struct record {
	char name[50];
	rollNum roll_num;
	Marksheet marks;
	struct record * next;
} Record;

/*
gradebook is a wrapper struct for the head, i.e. pointer to a particular
linked list/gradebook
*/
typedef struct Gradebook {
	Record * head;
	Record * tail;
} Gradebook;
```  

### The following is a reference for functions of the api  
```c
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
void deleteRecord(char[], rollNum, Gradebook *);

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
print the absolute grades of each student in the gradereport
*/
void printAbsGrade(Gradebook *);
/*
finds the relative grades by taking three inputs
marks of the individual in the subject, mean_marks and std_marks of the class
returns a string (grade)
*/
char *generateRelativeGrade(double, double, double);

/*
print the relative grades of each student in the gradereport when class size is greater than 30
*/
void printRelativeGrading(Gradebook *);

/*
checks for roll number duplication
return bool true if duplicate is found
*/
bool chck_rolldup(Gradebook *, rollNum);

/*
checks for name duplication
return bool true if duplicate is found
*/
bool chck_namedup(Gradebook *, char[]);
```

# Areas of improvements

### Suggestions
* Every name input should have the first letter capitalized to avoid any discrepencies.  
* Gradebook wouldn't be saved once the user has exited the program, concept of filing might be applied to increase the usefulness of the program manyfolds.  
* It also takes in identical records, so a function to stop duplication should be introduced.  

### Additional things that can be done 
* Finding lowest aggregate marks out of all the records in the gradebook  
* Finding highest/lowest marks in a particular subject  
<em>also refer to suggestions</em>

### Additional integrity checks that can be performed
* Check that marks entered should not be less than zero or greater than 100.
* String matching should be made case insensitive (strcmpi instead of strcmp)
