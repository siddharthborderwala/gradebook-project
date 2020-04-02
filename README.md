# gradebook-project
A gradebook, implementation of Linked List data structure

# docs
* The following is how the data-structures are defined
```c
///marksheet is a struct which has marks for 5 subjects
typedef struct marksheet {
	float math;
	float english;
	float science;
	float social_science;
	float sec_lang;
} marksheet;

///record is a struct like a node in a linked list
///it has name, roll number, marks (marksheet) and pointer to next record
typedef struct record {
	char name[50];
	long long int rollNum;
	marksheet marks;
	struct record * next;
} record;

///gradebook is a wrapper struct for the head, i.e. pointer to a particular
///linked list/ gradebook
typedef struct gradebook {
	record * head;
} gradebook;
```

# features
  * Create Record
  * Delete Record
  * Update Record
  * Read Record
  * Delete GradeBook
  * Print GradeBook

# contributors
* <a href="https://github.com/siddharthborderwala">Siddharth Borderwala</a>
* <a href="https://github.com/nk447">Niramay Kachhadiya</a>
* <a href="https://github.com/sgupta2501">Samarth Gupta</a>
* <a href="https://github.com/Aarjav-D">Aarjav Desai</a>
* <a href="https://github.com/HelBlazer">Yash Varshney</a>
