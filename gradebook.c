
#include "gradebook.h"

//code for center alignment of text for aesthetics and stuff
#ifdef _WIN32
#include <Windows.h>
int GetColumnWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	HANDLE out;

	if (!(out = GetStdHandle(STD_OUTPUT_HANDLE)) ||
		!GetConsoleScreenBufferInfo(out, &info))
		return 80;
	return info.dwSize.X;
}
#else
int GetColumnWidth() { return 80; }
#endif
void centre_align(char *s)
{
	const int total_width = GetColumnWidth();
	const int s_width = strlen(s);
	const int field_width = (total_width - s_width) / 2 + s_width;

	printf("%*s:\n", field_width, s);
}

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

	scanf("%c", &ch);
	printf("\nEnter name: ");
	scanf("%[^\n]", name);
	printf("\nEnter roll number:  ");
	scanf("%lld", &roll_num);
	printf("Enter marksheet details:\n");
	printf("\nEnter Maths marks: ");
	do{
	scanf("%f", &marks.math);
	if(marks.math<0 || marks.math>100)
    {
        printf("Please enter marks in valid range(0-100):");
    }
	}while(marks.math>100 || marks.math<0);
	printf("\nEnter English marks: ");
	do{
	scanf("%f", &marks.english);
	if(marks.english<0 || marks.english>100)
    {
        printf("Please enter marks in valid range(0-100):");
    }
	}while(marks.english>100 || marks.english<0);
	printf("\nEnter Science marks: ");
	do{
	scanf("%f", &marks.science);
	if(marks.science<0 || marks.science>100)
    {
        printf("Please enter marks in valid range(0-100):");
    }
	}while(marks.science>100 || marks.science<0);
	printf("\nEnter Social Science marks: ");
	do{
	scanf("%f", &marks.social_science);
	if(marks.social_science<0 || marks.social_science>100)
    {
        printf("Please enter marks in valid range(0-100):");
    }
	}while(marks.social_science>100 || marks.social_science<0);
	printf("\nEnter second language marks: ");
	do{
	scanf("%f", &marks.sec_lang);
	if(marks.sec_lang<0 || marks.sec_lang>100)
    {
        printf("Please enter marks in valid range(0-100):");
    }
	}while(marks.sec_lang>100 || marks.sec_lang<0);

	strcpy(rec.name, name);
	rec.roll_num = roll_num;
	if((chck_namedup(gb1,name)==1)&&(chck_rolldup(gb1,roll_num)==1))
    {printf("\nData for this student is already present. Data not added!\nPlease use options 9-11 for updation\n");
    return;
    }
	if((chck_namedup(gb1,name)==0)&&(chck_rolldup(gb1,roll_num)==1))
	{
	    printf("\nDifferent name for same roll number. KINDLY RECHECK!\n");
	    return;
	}
	rec.marks = marks;
	createNewRecord(gb1, rec);
}

// -> CORE FUNCTIONS
void defdata(Gradebook *gb1)
{
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

	while (cur != NULL && strcmp(cur->name, name) != 0)
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
	{
		while (i != gb_ptr->tail)
		{
			j = i->next;
			while (j != NULL)
			{
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
			}
			i = i->next;
		}
	}
	else
	{
		//sort the records in gradebook in descending order of roll num
		while (i != gb_ptr->tail)
		{
			j = i->next;
			while (j != NULL)
			{
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
	{
		while (i != gb_ptr->tail)
		{
			j = i->next;
			while (j != NULL)
			{
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
			}
			i = i->next;
		}
	}
	else
	{
		//sort the records in gradebook in descending order of roll num
		while (i != gb_ptr->tail)
		{
			j = i->next;
			while (j != NULL)
			{
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
			}
			i = i->next;
		}
	}

	printf("\n\nGRADEBOOK IS SORTED BY ROLL NUMBER\n\n");
}

void findTopper(Gradebook *gb_ptr)
{
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
	Record *cur = gb_ptr->head;

	printf("\nThe records of the students currently failing in 1 or more subjects is:\n");
	while (cur != NULL)
	{
		Marksheet marks = cur->marks;
		if (!(marks.english >= 33 && marks.math >= 33 && marks.science >= 33 && marks.sec_lang >= 33 && marks.social_science >= 33))
		{
			printRecord(cur);
		}
		cur = cur->next;
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

char *generateRelativeGrade(double subj_marks, double mean_marks, double std_marks)
{
	char *grade;
	if (subj_marks > (mean_marks + (1.5 * std_marks)))
		grade = "A+";
	else if (((std_marks) + (mean_marks)) < subj_marks && ((1.5 * std_marks) + (mean_marks)) >= subj_marks)
		grade = "A";
	else if (((mean_marks + (0.5 * std_marks)) <= subj_marks && (std_marks) + (mean_marks)) >= subj_marks)
		grade = "B+";
	else if (((mean_marks)) < subj_marks && ((0.5 * std_marks) + (mean_marks)) >= subj_marks)
		grade = "B";
	else if (((mean_marks) - (0.5 * std_marks)) <= subj_marks && (((mean_marks)) >= subj_marks))
		grade = "C";
	else if (((mean_marks) - (std_marks)) <= subj_marks && ((mean_marks) - (0.5 * std_marks)) >= subj_marks)
		grade = "D";
	else
		grade = "F";

	return grade;
}

void printAbsGrade(Gradebook *gb_ptr)
{
	Record *temp = gb_ptr->head;
	char *grade_english;
	char *grade_sec_lang;
	char *grade_math;
	char *grade_science;
	char *grade_social_science;
	Marksheet marks_individual;

	temp = gb_ptr->head;
	while (temp != NULL)
	{
		printf("Abs grading roll no = %lld\n",temp->roll_num);
		marks_individual = temp->marks;
		if (marks_individual.math>90) grade_math = "A+";
		else if (marks_individual.math>80) grade_math = "A";
		else if (marks_individual.math>70) grade_math = "B+";
		else if (marks_individual.math>60) grade_math = "B";
		else if (marks_individual.math>50) grade_math = "C";
		else if (marks_individual.math>40) grade_math = "D";
		else grade_math = "F";

		if (marks_individual.english>90) grade_english = "A+";
		else if (marks_individual.english>80) grade_english = "A";
		else if (marks_individual.english>70) grade_english = "B+";
		else if (marks_individual.english>60) grade_english = "B";
		else if (marks_individual.english>50) grade_english = "C";
		else if (marks_individual.english>40) grade_english = "D";
		else grade_english = "F";

		if (marks_individual.science>90) grade_science = "A+";
		else if (marks_individual.science>80) grade_science = "A";
		else if (marks_individual.science>70) grade_science = "B+";
		else if (marks_individual.science>60) grade_science = "B";
		else if (marks_individual.science>50) grade_science = "C";
		else if (marks_individual.science>40) grade_science = "D";
		else grade_science = "F";

		if (marks_individual.social_science>90) grade_social_science = "A+";
		else if (marks_individual.social_science>80) grade_social_science = "A";
		else if (marks_individual.social_science>70) grade_social_science = "B+";
		else if (marks_individual.social_science>60) grade_social_science = "B";
		else if (marks_individual.social_science>50) grade_social_science = "C";
		else if (marks_individual.social_science>40) grade_social_science = "D";
		else grade_social_science = "F";

		if (marks_individual.sec_lang>90) grade_sec_lang = "A+";
		else if (marks_individual.sec_lang>80) grade_sec_lang = "A";
		else if (marks_individual.sec_lang>70) grade_sec_lang = "B+";
		else if (marks_individual.sec_lang>60) grade_sec_lang = "B";
		else if (marks_individual.sec_lang>50) grade_sec_lang = "C";
		else if (marks_individual.sec_lang>40) grade_sec_lang = "D";
		else grade_sec_lang = "F";

		printf("\nAbsolute Grades for %s - %lld are\n", temp->name, temp->roll_num);
		printf("\n\tMaths:              %s", grade_english);
		printf("\n\tEnglish:           %s", grade_math);
		printf("\n\tScience:           %s", grade_science);
		printf("\n\tSocial Science:    %s", grade_social_science);
		printf("\n\tSecond Language:   %s", grade_sec_lang);
		printf("\n");

		temp = temp->next;
	}
}
void printRelativeGrading(Gradebook *gb_ptr)
{
	char *grade_english;
	char *grade_sec_lang;
	char *grade_math;
	char *grade_science;
	char *grade_social_science;

	Record *temp = gb_ptr->head;
	double mean_marks[5] = {0};
	int j = 0;
	Marksheet marks = temp->marks;
	while (temp != NULL)
	{
		j++;
		mean_marks[0] += marks.english;
		mean_marks[1] += marks.math;
		mean_marks[2] += marks.science;
		mean_marks[3] += marks.social_science;
		mean_marks[4] += marks.sec_lang;
		temp = temp->next;
	}
	if(j<=30)
	{
		printf("Relative grading is possible for class size greater than 30\n");
		printf("Current class size =%d. Printing absolute grading\n",j);
		printAbsGrade(gb_ptr	);
		return;
	}
	for (int its = 0; its < 5; its++)
	{
		mean_marks[its] /= j;
	}
	temp = gb_ptr->head;
	Marksheet marks1 = temp->marks;
	double std_marks[5] = {0};
	while (temp != NULL)
	{
		std_marks[0] += pow((marks1.english - mean_marks[0]), 2);
		std_marks[1] += pow((marks1.math - mean_marks[1]), 2);
		std_marks[2] += pow((marks1.science - mean_marks[2]), 2);
		std_marks[3] += pow((marks1.social_science - mean_marks[3]), 2);
		std_marks[4] += pow((marks1.sec_lang - mean_marks[4]), 2);
		temp = temp->next;
	}
	for (int her = 0; her < 5; her++)
	{
		std_marks[her] = sqrt(std_marks[her] / j);
	}
	temp = gb_ptr->head;
	Marksheet marks_individual;
	while (temp != NULL)
	{
		marks_individual = temp->marks;
		grade_english = generateRelativeGrade(marks_individual.english, mean_marks[0], std_marks[0]);
		grade_math = generateRelativeGrade(marks_individual.math, mean_marks[1], std_marks[1]);
		grade_science = generateRelativeGrade(marks_individual.science, mean_marks[2], std_marks[2]);
		grade_social_science = generateRelativeGrade(marks_individual.social_science, mean_marks[3], std_marks[3]);
		grade_sec_lang = generateRelativeGrade(marks_individual.sec_lang, mean_marks[4], std_marks[4]);

		printf("\nRelative Grades for %s - %lld are\n", temp->name, temp->roll_num);
		printf("\n\tMaths:              %s", grade_english);
		printf("\n\tEnglish:           %s", grade_math);
		printf("\n\tScience:           %s", grade_science);
		printf("\n\tSocial Science:    %s", grade_social_science);
		printf("\n\tSecond Language:   %s", grade_sec_lang);
		printf("\n");

		temp = temp->next;
	}
}

int chck_rolldup(Gradebook * gb_ptr, rollNum roll_num) {
  if (isGradeBookEmpty(gb_ptr))
    return 0;
  Record * cur = gb_ptr -> head;
  while (cur != NULL && cur -> roll_num != roll_num)
    cur = cur -> next;
  if (cur == NULL)
    return 0;
  else
    return 1;
}

int chck_namedup(Gradebook * gb_ptr, char name[]) {
  if (isGradeBookEmpty(gb_ptr))
    return 0;
  if (strlen(name) > 50)
    name[50] = '\0';
  Record * cur = gb_ptr -> head;
  while (cur != NULL && strcmpi(cur -> name, name) != 0) {
    cur -> name;
    strcmpi(cur -> name, name);
    cur = cur -> next;
  }
  if (cur == NULL)
    return 0;
  else

    return 1;
}
