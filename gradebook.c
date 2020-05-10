#include "gradebook.h"

//code for center alignment of text for aesthetics and stuff
/*#ifdef _WIN32
#include <Windows.h>
int GetColumnWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    HANDLE out;

    if (!(out = GetStdHandle(STD_OUTPUT_HANDLE)) ||
        !GetConsoleScreenBufferInfo(out, &info))
        return 80;
    return info.dwSize.X;
}//GetColumnWidth
#else
int GetColumnWidth() {return 80;}
#endif
void centre_align(char *s)
{
    const int total_width = GetColumnWidth();
    const int s_width = strlen(s);
    const int field_width = (total_width - s_width) / 2 + s_width;

    printf("%*s:\n", field_width, s);
}
*/
size_t record_size = sizeof(Record);

// -> UTILITY FUNCTIONS

float avgMarks(Marksheet ms)
{
	float sum = ms.math + ms.english + ms.science + ms.social_science + ms.sec_lang;
	float avg = sum / 5.0;
	return avg;
}

void printMarksheet(Marksheet ms)
{
	printf("\n\tMath:              %5.2f", ms.math);
	printf("\n\tEnglish:           %5.2f", ms.english);
	printf("\n\tScience:           %5.2f", ms.science);
	printf("\n\tSocial Science:    %5.2f", ms.social_science);
	printf("\n\tSecond Language:   %5.2f", ms.sec_lang);
}

void printRecord(Record *rec)
{
	printf("\n\nName:          %s", rec->name);
	printf("\nRoll Number:  %lld", rec->roll_num);
	printf("\nMarksheet:");
	printMarksheet(rec->marks);
	printf("\nAverage:       %5.2f", avgMarks(rec->marks));
}

int isGradeBookEmpty(Gradebook *gb_ptr)
{
	if (gb_ptr->head == NULL && gb_ptr->tail == NULL)
		return 1;
	else
		return 0;
}

void addRecord(Gradebook *gb1)
{
	char name[50], ch;
	rollNum roll_num;
	Marksheet marks;
	Record rec;

	scanf("%c", &ch); // temp statement to clear buffer
	printf("\nEnter name: ");
	//	fgets(name, 50, stdin);  // read name string
	//	scanf("%c",&ch);
	scanf("%[^\n]", name);
	printf("\nEnter roll number:  ");
	scanf("%lld", &roll_num);
	printf("Enter marksheet details:\n");
	printf("\nEnter Maths marks: ");
	scanf("%f", &marks.math);
	printf("\nEnter English marks: ");
	scanf("%f", &marks.english);
	printf("\nEnter Science marks: ");
	scanf("%f", &marks.science);
	printf("\nEnter Social Science marks: ");
	scanf("%f", &marks.social_science);
	printf("\nEnter second language marks: ");
	scanf("%f", &marks.sec_lang);

	strcpy(rec.name, name);
	rec.roll_num = roll_num;
	rec.marks = marks;
	createNewRecord(gb1, rec);
}

// -> CORE FUNCTIONS
void defdata(Gradebook *gb1)
{
	//	Gradebook gb1 = createGradeBook();
	createNewRecord(gb1, (Record){
													 "Siddharth Borderwala",
													 1910110389,
													 (Marksheet){98.2, 97.5, 99.0, 97.2, 98.6}});
	createNewRecord(gb1, (Record){
													 "Niramay Kachhadiya",
													 1910110225,
													 (Marksheet){98.2, 97.5, 99.0, 97.2, 98.6}});
	createNewRecord(gb1, (Record){
													 "Yash Varshney",
													 1910110285,
													 (Marksheet){98.2, 97.5, 99.0, 97.2, 98.6}});
	createNewRecord(gb1, (Record){
													 "Samarth Gupta",
													 1910110300,
													 (Marksheet){98.2, 97.5, 99.0, 97.2, 98.6}});
	createNewRecord(gb1, (Record){
													 "Aarjav Desai",
													 1910110120,
													 (Marksheet){98.2, 97.5, 99.0, 97.2, 98.6}});
}

Gradebook createGradeBook()
{
	Record *head_record = (Record *)malloc(record_size);

	//if the malloc function fails
	if (head_record == NULL)
	{
		printf("\nCouldn't create a new grade book, not enough memory :(");
		exit(0);
	}

	head_record = NULL;
	Gradebook new_gb = {head_record};
	return new_gb;
}

void createNewRecord(Gradebook *gb, Record new_record)
{
	Record *new_rec_ptr = (Record *)malloc(record_size);

	//if the malloc function fails
	if (new_rec_ptr == NULL)
	{
		printf("\nCouldn't create a new record, not enough memory :(");
		exit(0);
	}

	strcpy(new_rec_ptr->name, new_record.name);
	new_rec_ptr->marks = new_record.marks;
	new_rec_ptr->roll_num = new_record.roll_num;
	new_rec_ptr->next = NULL;

	// if the gradebook is empty
	if (isGradeBookEmpty(gb))
	{
		gb->head = new_rec_ptr;
		gb->tail = new_rec_ptr;
	}
	else
	{
		gb->tail->next = new_rec_ptr;
		gb->tail = new_rec_ptr;
	}
}

Record findRecordByName(Gradebook *gb_ptr, char name[], bool should_print)
{
	printf("Finding the record . . . .\n");
	// if gradebook is empty
	if (isGradeBookEmpty(gb_ptr))
	{
		printf("\nGradebook is empty :(");
		return;
	}

	// if length of the search name is greater than 50 characters, it will be truncated
	if (strlen(name) > 50)
	{
		printf("\nLength of the name cannot be greater than 50 characters, it will be truncated for the search");
		name[50] = '\0';
	}

	Record *cur = gb_ptr->head;

	while (cur != NULL && strcmp(cur->name, name) != 0) //isStrEq(cur->name, name)
	{
       cur->name;
    strcmp(cur->name, name);
		//		printRecord(cur);
		cur = cur->next;
	}
	if (cur == NULL)
	{
		printf("\nFinding record by name %s - Record not found\n", name);
		return;
	}

	if (should_print)
	{
		printf("\n\nRecord found:");
		printRecord(cur);
	}
	return (*cur);
}

Record findRecordByRollNum(Gradebook *gb_ptr, rollNum roll_num, bool should_print)
{
	// if gradebook is empty
	if (isGradeBookEmpty(gb_ptr))
	{
		printf("\nGradebook is empty :(");
		return;
	}

	Record *cur = gb_ptr->head;

	while (cur != NULL && cur->roll_num != roll_num)
		cur = cur->next;

	if (cur == NULL)
	{
		printf("\nFinding record by Roll Number %lld - Record not found\n", roll_num);
		return;
	}

	if (should_print)
	{
		printf("\n\nRecord found:");
		printRecord(cur);
	}
	return (*cur);
}

Record updateNameInRecord(char new_name[], rollNum roll_num, Gradebook *gb_ptr)
{
	// if gradebook is empty
	if (isGradeBookEmpty(gb_ptr))
	{
		printf("\nGradebook is empty :(");
		return;
	}

	// if length of new name is greater than 50 characters, it will be truncated
	if (strlen(new_name) > 50)
	{
		printf("\nLength of the name cannot be greater than 50 characters, it will be truncated");
		new_name[50] = '\0';
	}

	Record *cur = gb_ptr->head;

	while (cur != NULL && cur->roll_num != roll_num)
		cur = cur->next;

	if (cur == NULL)
	{
		printf("\nUpdating %lld - Record not found\n", roll_num);
		return;
	}

	strcpy(cur->name, new_name);
	return (*cur);
}

Record updateRollNumInRecord(char name[], rollNum new_roll_num, Gradebook *gb_ptr)
{
	// if gradebook is empty
	if (isGradeBookEmpty(gb_ptr))
	{
		printf("\nGradebook is empty :(");
		return;
	}
	// if length of the search name is greater than 50 characters, it will be truncated
	if (strlen(name) > 50)
	{
		printf("\nLength of the name cannot be greater than 50 characters, it will be truncated for the search");
		name[50] = '\0';
	}

	Record *cur = gb_ptr->head;

	while (cur != NULL && (strcmp(cur->name, name) != 0))
		cur = cur->next;

	if (cur == NULL)
	{
		printf("\nUpdating Roll Number of %s - Record not found\n", name);
		return;
	}

	cur->roll_num = new_roll_num;
	printf("\nThe updated record is:\n");
	return (*cur);
}

Record updateMarksheetInRecord(char name[], rollNum roll_num, Marksheet new_ms, Gradebook *gb_ptr)
{
	// if gradebook is empty
	if (isGradeBookEmpty(gb_ptr))
	{
		printf("\nGradebook is empty :(");
		return;
	}

	Record *cur = gb_ptr->head;

	if (roll_num != 0) // update using the name
	{
		while (cur != NULL && cur->roll_num != roll_num)
			cur = cur->next;
	}
	else if (strcmp(name, "") != 0) // update using the roll number isStrEq(name, "")
	{
		// if length of the search name is greater than 50 characters, it will be truncated
		if (strlen(name) > 50)
		{
			printf("\nLength of the search name cannot be greater than 50 characters, it will be truncated for the search");
			name[50] = '\0';
		}

		while (cur != NULL && strcmp(cur->name, name) != 0) //isStrEq
			cur = cur->next;
	}
	else
	{
		printf("\nEnter valid information");
		return;
	}
	/*
	if (strcmp(name, "")) // update using the roll number isStrEq(name, "")
	{
		while (cur != NULL && cur->roll_num != roll_num)
			cur = cur->next;
	}
	else if (roll_num == 0) // update using the name
	{
		// if length of the search name is greater than 50 characters, it will be truncated
		if (strlen(name) > 50)
		{
			printf("\nLength of the search name cannot be greater than 50 characters, it will be truncated for the search");
			name[50] = '\0';
		}
		while (cur != NULL && !strcmp(cur->name, name))//isStrEq
			cur = cur->next;
	}
	else
	{
		printf("\nEnter valid information");
		return;
	}
*/

	if (cur == NULL)
	{
		printf("\nUpdating Marksheet of %s, %lld - Record not found\n", name, roll_num);
		return;
	}

	cur->marks = new_ms;

	return (*cur);
}

void deleteRecord(char name[], rollNum roll_num, Gradebook *gb_ptr)
{
	// if gradebook is empty
	if (isGradeBookEmpty(gb_ptr))
	{
		printf("\nGradebook is empty");
		return;
	}

	Record *cur = gb_ptr->head;
	Record *prev = gb_ptr->head;
	if (roll_num != 0)
	{
		while (cur != NULL && cur->roll_num != roll_num)
		{
			prev = cur;
			cur = cur->next;
		}
	}
	else if (strcmp(name, "") != 0)
	{
		while (cur != NULL && strcmp(cur->name, name) != 0)
		{
			prev = cur;
			cur = cur->next;
		}
	}
	else
	{
		printf("\nEnter valid information to find the record to be deleted");
		return;
	}

	/*	if (strcmp(name, ""))//isStrEq
	{
		while (cur != NULL && cur->roll_num != roll_num)
		{
			prev = cur;
			cur = cur->next;
		}
	}
	else if (roll_num == 0)
	{
		// if length of the search name is greater than 50 characters, it will be truncated
		if (strlen(name) > 50)
		{
			printf("\nLength of the search name cannot be greater than 50 characters, it will be truncated for the search");
			name[50] = '\0';
		}
		while (cur != NULL && strcmp(cur->name, name)!=0)//isStrEq
		{
			prev = cur;
			cur = cur->next;
		}
	}
	else if (strcmp(name, "") && roll_num == 0)//isStrEq
	{
		printf("\nEnter valid information to find the record to be deleted");
		return;
	}*/

	if (cur == NULL)
	{
		printf("\nWhile deleting given data name = %s, roll no = %lld  - Record not found\n", name, roll_num);
		return;
	}

	if (cur->next == NULL)
	{
		//if the record to be deleted is the last one
		gb_ptr->tail = prev;
		prev->next = NULL;
	}
	else if (cur == gb_ptr->head)
	{
		// if the record to be deleted is the first one
		gb_ptr->head = cur->next;
	}
	else
		prev->next = cur->next;

	free(cur);
}

void printGradebook(Gradebook *gb_ptr)
{
	// if the gradebook is empty
	if (isGradeBookEmpty(gb_ptr))
	{
		printf("\nGradebook is empty :(\n");
		return;
	}

	Record *cur = gb_ptr->head;

	printf("\n------Gradebook------");

	while (cur != NULL)
	{
		printRecord(cur);
		cur = cur->next;
	}

	printf("\n\n------Task Over------\n");
}

void deleteRecordHead(Gradebook *gb_ptr)
{
	// if the gradebook is empty
	if (isGradeBookEmpty(gb_ptr))
	{
		printf("\nGradebook is empty :(");
		return;
	}

	if (gb_ptr->head == gb_ptr->tail)
	{
		free(gb_ptr->head);
		gb_ptr->head = NULL;
		gb_ptr->tail = NULL;
	}
	else
	{
		Record *cur = gb_ptr->head;
		gb_ptr->head = cur->next;
		free(cur);
	}
}

void deleteGradebook(Gradebook *gb_ptr)
{
	// if the gradebook is empty
	if (isGradeBookEmpty(gb_ptr))
	{
		printf("\nGradebook is empty :(");
		return;
	}

	while (!isGradeBookEmpty(gb_ptr))
		deleteRecordHead(gb_ptr);
}

void sortGradebookName(Gradebook *gb_ptr, bool asc)
{
	Record *i, *j, k;

	i = gb_ptr->head;

	if (asc == true)
	{ //	printf("Inside function\n");
		while (i != gb_ptr->tail)
		{
			//	printf("Inside i while roll num=%lld\n",i->roll_num);
			j = i->next;
			while (j != NULL)
			{
				//	printf("Inside j while roll number=%lld\n",j->roll_num);

				if (strcmp(i->name, j->name) > 0)
				{
					k.roll_num = i->roll_num;
					i->roll_num = j->roll_num;
					j->roll_num = k.roll_num;
					k.marks = i->marks;
					i->marks = j->marks;
					j->marks = k.marks;
					strcpy(k.name, i->name);
					strcpy(i->name, j->name);
					strcpy(j->name, k.name);
				}
				j = j->next;
				//	printf("Inside j while roll number=%lld\n",j->roll_num);
			}
			i = i->next;
		}
	}
	else
	{
		//sort the records in gradebook in descending order of roll num
		while (i != gb_ptr->tail)
		{
			//	printf("Inside i while roll num=%lld\n",i->roll_num);
			j = i->next;
			while (j != NULL)
			{
				//	printf("Inside j while roll number=%lld\n",j->roll_num);

				if (strcmp(i->name, j->name) < 0)
				{
					k.roll_num = i->roll_num;
					i->roll_num = j->roll_num;
					j->roll_num = k.roll_num;
					k.marks = i->marks;
					i->marks = j->marks;
					j->marks = k.marks;
					strcpy(k.name, i->name);
					strcpy(i->name, j->name);
					strcpy(j->name, k.name);
				}
				j = j->next;
				//	printf("Inside j while roll number=%lld\n",j->roll_num);
			}
			i = i->next;
		}
	}

	printf("\n\nGRADEBOOK IS SORTED BY NAME\n\n");
}

void sortGradebookRollNum(Gradebook *gb_ptr, bool asc)
{
	Record *i, *j, k;

	i = gb_ptr->head;

	if (asc == true)
	{ //	printf("Inside function\n");
		while (i != gb_ptr->tail)
		{
			//	printf("Inside i while roll num=%lld\n",i->roll_num);
			j = i->next;
			while (j != NULL)
			{
				//	printf("Inside j while roll number=%lld\n",j->roll_num);

				if (i->roll_num > j->roll_num)
				{
					k.roll_num = i->roll_num;
					i->roll_num = j->roll_num;
					j->roll_num = k.roll_num;
					k.marks = i->marks;
					i->marks = j->marks;
					j->marks = k.marks;
					strcpy(k.name, i->name);
					strcpy(i->name, j->name);
					strcpy(j->name, k.name);
				}
				j = j->next;
				//	printf("Inside j while roll number=%lld\n",j->roll_num);
			}
			i = i->next;
		}
	}
	else
	{
		//sort the records in gradebook in descending order of roll num
		while (i != gb_ptr->tail)
		{
			//	printf("Inside i while roll num=%lld\n",i->roll_num);
			j = i->next;
			while (j != NULL)
			{
				//	printf("Inside j while roll number=%lld\n",j->roll_num);

				if (i->roll_num < j->roll_num)
				{
					k.roll_num = i->roll_num;
					i->roll_num = j->roll_num;
					j->roll_num = k.roll_num;
					k.marks = i->marks;
					i->marks = j->marks;
					j->marks = k.marks;
					strcpy(k.name, i->name);
					strcpy(i->name, j->name);
					strcpy(j->name, k.name);
				}
				j = j->next;
				//	printf("Inside j while roll number=%lld\n",j->roll_num);
			}
			i = i->next;
		}
	}

	printf("\n\nGRADEBOOK IS SORTED BY ROLL NUMBER\n\n");
}

void findTopper(Gradebook *gb_ptr)
{
	//find the record with maximum total marks
	//print this record
	Record *cur = gb_ptr->head;
	Record max = *cur;

	while (cur != NULL)
	{
		if (avgMarks(cur->marks) > avgMarks(max.marks))
			max = *cur;
		cur = cur->next;
	}

	printRecord(&max);
}

void findFailingStudents(Gradebook *gb_ptr)
{
	//find the records of students who fail in 1 or more subjects
	//print these records
	Record *cur = gb_ptr->head;

	while (cur != NULL)
	{
		Marksheet marks = cur->marks;
		if (!(marks.english >= 33 && marks.math >= 33 && marks.science >= 33 && marks.sec_lang >= 33 && marks.social_science >= 33))
		{
			printf("\nThe records of the students currently failing in 1 or more subjects is:\n");
			printRecord(cur);
		}
	}
}

int countGradebookRecords(Gradebook *gb_ptr)
{
	int count = 0;
	Record *cur = gb_ptr->head;

	while (cur != NULL)
	{
		cur = cur->next;
		count++;
	}

	return count;
}

void printRelativeGrading(Gradebook *gb_ptr)
{
    char grade_english;
    char grade_sec_lang;
    char grade_math;
    char grade_science;
    char grade_social_science;
    // print the relative grades of each student in the gradereport
    Record *temp = gb_ptr->head;
    double mean_marks[5] = {0};
    int j = 0;
    Marksheet marks = temp->marks;
    while(temp!=NULL) {
        j++;
        mean_marks[0] += marks.english;
        mean_marks[1] += marks.math;
        mean_marks[2] += marks.science;
        mean_marks[3] += marks.social_science;
        mean_marks[4] += marks.sec_lang;
        temp = temp->next;
    }
    for(int its=0;its<5;its++) {
        mean_marks[its]/=j;
    }
    temp = gb_ptr->head;
    Marksheet marks1 = temp->marks;
    double std_marks[5] = {0};
    while(temp!=NULL) {
        std_marks[0] += pow((marks1.english - mean_marks[0]),2);
        std_marks[1] += pow((marks1.math - mean_marks[1]),2);
        std_marks[2] += pow((marks1.science - mean_marks[2]),2);
        std_marks[3] += pow((marks1.social_science - mean_marks[3]),2);
        std_marks[4] += pow((marks1.sec_lang - mean_marks[4]),2);
        temp = temp->next;
    }
    for(int her=0;her<5;her++) {
        std_marks[her]= sqrt(std_marks[her]/j);
    }
    temp = gb_ptr->head;
    Marksheet marks2 = temp->marks;
    while(temp!=NULL) {
        if (marks2.english>(mean_marks[0]+(1.5*std_marks[0])))
        grade_english='A+';
        else if (((std_marks[0])+(mean_marks[0]))<marks2.english && ((1.5*std_marks[0])+(mean_marks[0]))>=marks2.english)
        grade_english='A';
        else if (((mean_marks[0]+(0.5*std_marks[0]))<=marks2.english && (std_marks[0])+(mean_marks[0]))>=marks2.english)
        grade_english='B+';
        else if (((mean_marks[0]))<marks2.english && ((0.5*std_marks[0])+(mean_marks[0]))>=marks2.english)
        grade_english='B';
        else if (((mean_marks[0])-(0.5*std_marks[0]))<=marks2.english && (((mean_marks[0]))>=marks2.english))
        grade_english='C';
        else if (((mean_marks[0])-(std_marks[0]))<=marks2.english && ((mean_marks[0])-(0.5*std_marks[0]))>=marks2.english)
        grade_english='D';
        else
        grade_english='F';

        if (marks2.math>(mean_marks[1]+(1.5*std_marks[1])))
        grade_math='A+';
        else if (((std_marks[1])+(mean_marks[1]))<marks2.math && ((1.5*std_marks[1])+(mean_marks[1]))>=marks2.math)
        grade_math='A';
        else if (((mean_marks[1]+(0.5*std_marks[1]))<=marks2.math && (std_marks[1])+(mean_marks[1]))>=marks2.math)
        grade_math='B+';
        else if (((mean_marks[1]))<marks2.math && ((0.5*std_marks[1])+(mean_marks[1]))>=marks2.math)
        grade_math='B';
        else if (((mean_marks[1])-(0.5*std_marks[1]))<=marks2.math && (((mean_marks[1]))>=marks2.math))
        grade_math='C';
        else if (((mean_marks[1])-(std_marks[1]))<=marks2.math && ((mean_marks[1])-(0.5*std_marks[1]))>=marks2.math)
        grade_math='D';
        else
        grade_math='F';

        if (marks2.science>(mean_marks[2]+(1.5*std_marks[2])))
        grade_science='A+';
        else if (((std_marks[2])+(mean_marks[2]))<marks2.science && ((1.5*std_marks[2])+(mean_marks[2]))>=marks2.science)
        grade_science='A';
        else if (((mean_marks[2]+(0.5*std_marks[2]))<=marks2.science && (std_marks[2])+(mean_marks[2]))>=marks2.science)
        grade_science='B+';
        else if (((mean_marks[2]))<marks2.science && ((0.5*std_marks[2])+(mean_marks[2]))>=marks2.science)
        grade_science='B';
        else if (((mean_marks[2])-(0.5*std_marks[2]))<=marks2.science && (((mean_marks[2]))>=marks2.science))
        grade_science='C';
        else if (((mean_marks[2])-(std_marks[2]))<=marks2.science && ((mean_marks[2])-(0.5*std_marks[2]))>=marks2.science)
        grade_science='D';
        else
        grade_science='F';

        if (marks2.social_science>(mean_marks[3]+(1.5*std_marks[3])))
        grade_social_science='A+';
        else if (((std_marks[3])+(mean_marks[3]))<marks2.social_science && ((1.5*std_marks[3])+(mean_marks[3]))>=marks2.social_science)
        grade_social_science='A';
        else if (((mean_marks[3]+(0.5*std_marks[3]))<=marks2.social_science && (std_marks[3])+(mean_marks[3]))>=marks2.social_science)
        grade_social_science='B+';
        else if (((mean_marks[3]))<marks2.social_science && ((0.5*std_marks[3])+(mean_marks[3]))>=marks2.social_science)
        grade_social_science='B';
        else if (((mean_marks[3])-(0.5*std_marks[3]))<=marks2.social_science && (((mean_marks[3]))>=marks2.social_science))
        grade_social_science='C';
        else if (((mean_marks[3])-(std_marks[3]))<=marks2.social_science && ((mean_marks[3])-(0.5*std_marks[3]))>=marks2.social_science)
        grade_social_science='D';
        else
        grade_social_science='F';

        if (marks2.sec_lang>(mean_marks[4]+(1.5*std_marks[4])))
        grade_sec_lang='A+';
        else if (((std_marks[4])+(mean_marks[4]))<marks2.sec_lang && ((1.5*std_marks[4])+(mean_marks[4]))>=marks2.sec_lang)
        grade_sec_lang='A';
        else if (((mean_marks[4]+(0.5*std_marks[4]))<=marks2.sec_lang && (std_marks[4])+(mean_marks[4]))>=marks2.sec_lang)
        grade_sec_lang='B+';
        else if (((mean_marks[4]))<marks2.sec_lang && ((0.5*std_marks[4])+(mean_marks[4]))>=marks2.sec_lang)
        grade_sec_lang='B';
        else if (((mean_marks[4])-(0.5*std_marks[4]))<=marks2.sec_lang && (((mean_marks[4]))>=marks2.sec_lang))
        grade_sec_lang='C';
        else if (((mean_marks[4])-(std_marks[4]))<=marks2.sec_lang && ((mean_marks[4])-(0.5*std_marks[4]))>=marks2.sec_lang)
        grade_sec_lang='D';
        else
        grade_sec_lang='F';

        return;




}

	// print the relative grades of each student in the gradereport
}
