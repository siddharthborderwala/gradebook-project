# gradebook-project
A gradebook, implementation of Linked List data structure

# features
  * Create Record
  * Delete Record
  * Update Record
  * Read Record
  * Create Gradebook
  * Print GradeBook
  * Delete GradeBook

# docs
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
Finds the record by a search name if found returns and prints it
Takes in a Pointer to Gradebook and a Name
Returns the record if found
*/
Record findRecordByName(Gradebook *, char[]);

/*
Finds the record by a search roll number if found returns and prints it
Takes in a Pointer to Gradebook and a Roll Number
Returns the record if found
*/
Record findRecordByRollNum(Gradebook *, rollNum);

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
```


# contributors
[Siddharth Borderwala](https://github.com/siddharthborderwala)  
[Niramay Kachhadiya](https://github.com/niramay447)  
[Aarjav Desai](https://github.com/Aarjav-D)  
[Samarth Gupta](https://github.com/sgupta2501)  
[Yash Varshney](https://github.com/HelBlazer)  

