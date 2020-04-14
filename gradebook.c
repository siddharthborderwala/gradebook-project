#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

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
	printf("\nName:          %s", rec->name);
	printf("\nRoll Nummber:  %lld", rec->roll_num);
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

int isStrEq(char a[], char b[])
{
	size_t len_a = strlen(a);
	size_t len_b = strlen(b);
	if (len_a != len_b)
		return 0;
	for (size_t i = 0; i <= len_a; i++)
		if (a[i] != b[i])
			return 0;
	return 1;
}

// -> CORE FUNCTIONS

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

Record createNewRecord(Gradebook *gb, Record new_record)
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

	return *new_rec_ptr;
}

void findRecordByName(Gradebook *gb_ptr, char name[])
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

	while (cur != NULL && !isStrEq(cur->name, name))
		cur = cur->next;

	if (cur == NULL)
	{
		printf("\nSorry record not found :(");
		return;
	}

	printf("\nRecord found:");
	printRecord(cur);
}

void findRecordByRollNum(Gradebook *gb_ptr, rollNum roll_num)
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
		printf("\nSorry record not found :(");
		return;
	}

	printf("\nRecord found:");
	printRecord(cur);
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
		printf("\nRecord not found :(");
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

	while (cur != NULL && !isStrEq(cur->name, name))
		cur = cur->next;

	if (cur == NULL)
	{
		printf("\nRecord not found :(");
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

	if (isStrEq(name, "")) // update using the roll number
	{
		while (cur != NULL && cur->roll_num != roll_num)
			cur = cur->next;
	}
	else if (roll_num = 0) // update using the name
	{
		// if length of the search name is greater than 50 characters, it will be truncated
		if (strlen(name) > 50)
		{
			printf("\nLength of the search name cannot be greater than 50 characters, it will be truncated for the search");
			name[50] = '\0';
		}

		while (cur != NULL && !isStrEq(cur->name, name))
			cur = cur->next;
	}
	else
	{
		printf("Enter valid information");
		return;
	}

	if (cur == NULL)
	{
		printf("\nRecord not found :(");
		return;
	}

	cur->marks = new_ms;

	return (*cur);
}

// just for testing puroses during development
void main()
{
	;
}