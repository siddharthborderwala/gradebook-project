#include "gradebook.h"

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
	printf("findRecordByName\n");
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
		printf("Searching\n");
		printf("Start Searching for %s\n", name);
		printf("curr record name =   %s\n", cur->name);
		printf("result of str cmp = %d\n", strcmp(cur->name, name));
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

	printf("Gradebook is sorted by name\n");
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

	printf("Gradebook is sorted by roll number\n");
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
			printf("\nFailed");
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
	// print the relative grades of each student in the gradereport
}
