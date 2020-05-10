#include "gradebook.h"

void main()
{
	int menu;
	char name[50];
	rollNum roll_num;
	Marksheet marks;
	Gradebook gb1 = createGradeBook();
	char ch;
	int cnt;
	Record rec1;

	while (1)
	{
		printf("\n0.Exit\n");
		printf("1.Use default gradebook\n");
		printf("2.Insert a record in gradebook\n");
		printf("3.Delete the first record\n");
		printf("4.Delete a record by name\n");
		printf("5.Delete a record by roll number\n");
		printf("6.Delete all records\n");
		printf("7.Find a record by name\n");
		printf("8.Find a record by roll number\n");
		printf("9.Update name in record\n");
		printf("10.Update roll number in a record\n");
		printf("11.Update marksheet by name in a record\n");
		printf("12.Update marksheet by roll number in a record\n");
		printf("13.Sort the gradebook in ascending order by name \n");
		printf("14.Sort the gradebook in descending order by name \n");
		printf("15.Sort the gradebook in ascending order by roll number\n");
		printf("16.Sort the gradebook in descending order by roll number\n");
		printf("17.Find the topper of the class \n");
		printf("18.Find the students who have failed in one or more subjects \n");
		printf("19.Print gradebook\n");
		printf("20.Count and Print number of students in gradebook\n");
		printf("21.Print relative grading for all the students \n");
		printf("22.Print absolute grading for all the students \n");
		printf("23.Clear screen\n");
		printf("\nEnter a menu choice: ");
		scanf("%d", &menu);
		switch (menu)
		{
		case 0:
			exit(0);
			break;
		case 1:
			printf("\nDefault data is being used . . . .\n");
			defdata(&gb1);
			break;
		case 2:
			addRecord(&gb1);
			break;
		case 3:
			if (!isGradeBookEmpty(&gb1))
			printf("\nDeleting the first record . . .DELETED!\n");
			deleteRecordHead(&gb1);
			break;
		case 4:
			scanf("%c", &ch);
			printf("\nEnter name: ");
			scanf("%[^\n]", name);
			if(chck_namedup(&gb1,name)==1)
			{
            printf("\nThere are more than 1 students with same name!\n Please enter the roll number of student record to be deleted\n");
			scanf("%c", &ch);
			printf("\nEnter roll number:  ");
			scanf("%lld", &roll_num);
			strcpy(name, "");
			if (!isGradeBookEmpty(&gb1))
			printf("\nDeleting record . . .DELETED!\n");
			deleteRecord(name, roll_num, &gb1);
			}
			roll_num = 0;
			if (!isGradeBookEmpty(&gb1))
			printf("\nDeleting record . . .DELETED!\n");
			deleteRecord(name, roll_num, &gb1);
			break;
		case 5:
			scanf("%c", &ch);
			printf("\nEnter roll number:  ");
			scanf("%lld", &roll_num);
			strcpy(name, "");
			if (!isGradeBookEmpty(&gb1))
			printf("\nDeleting record . . .DELETED!\n");
			deleteRecord(name, roll_num, &gb1);
			break;
		case 6:
			if (!isGradeBookEmpty(&gb1))
			printf("\nAll records have been deleted! As good as new!\n");
			deleteGradebook(&gb1);
			break;
		case 7:
			scanf("%c", &ch);
			printf("\nEnter name: ");
			scanf("%[^\n]", name);
			cnt = strcmpi(name, "Samarth Gupta");

			scanf("%c", &ch);
			findRecordByName(&gb1, name, true);
			break;
		case 8:
			scanf("%c", &ch);
			printf("\nEnter roll number:  ");
			scanf("%lld", &roll_num);
			findRecordByRollNum(&gb1, roll_num, true);
			break;
		case 9:
			printf("\nEnter roll number:  ");
			scanf("%lld", &roll_num);
			scanf("%c", &ch);
			printf("\nEnter name: ");
			scanf("%[^\n]", name);
			rec1 = updateNameInRecord(name, roll_num, &gb1);
			printRecord(&rec1);
			break;
		case 10:
			scanf("%c", &ch);
			printf("\nEnter name: ");
			scanf("%[^\n]", name);
			printf("\nEnter roll number:  ");
			scanf("%lld", &roll_num);
			rec1 = updateRollNumInRecord(name, roll_num, &gb1);
			printRecord(&rec1);
			break;
		case 11:
			scanf("%c", &ch);
			printf("\nEnter name: ");
			scanf("%[^\n]", name);
			rec1 = updateNameInRecord(name, roll_num, &gb1);
			roll_num = 0;
			printf("\nEnter new marksheet details:\n");
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
			rec1 = updateMarksheetInRecord(name, roll_num, marks, &gb1);
			printf("\nThe updated record is:\n");
			printRecord(&rec1);
			break;
		case 12:
			scanf("%c", &ch);
			printf("\nEnter roll number:  ");
			scanf("%lld", &roll_num);
			strcpy(name, "");
			printf("\nEnter new marksheet details:\n");
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
			rec1 = updateMarksheetInRecord(name, roll_num, marks, &gb1);
			printf("\nThe updated record is:\n");
			printRecord(&rec1);
			break;
		case 13: //sort ascending
			sortGradebookName(&gb1, true);
			printf("The sorted gradebook is:\n");
			printGradebook(&gb1);
			break;
		case 14: //sort descending
			sortGradebookName(&gb1, false);
			printf("The sorted gradebook is:\n");
			printGradebook(&gb1);
			break;
		case 15: //sort ascending
			sortGradebookRollNum(&gb1, true);
			printf("The sorted gradebook is:\n");
			printGradebook(&gb1);
			break;
		case 16: //sort descending
			sortGradebookRollNum(&gb1, false);
			printf("The sorted gradebook is:\n");
			printGradebook(&gb1);
			break;
		case 17:
			printf("The record details of the topper are:");
			findTopper(&gb1);
			break;
		case 18:
			findFailingStudents(&gb1);
			break;
		case 19:
			printGradebook(&gb1);
			break;
		case 20:
			cnt = countGradebookRecords(&gb1);
			printf("\nNumber of records in the gradebook = %d", cnt);
			break;
		case 21:
			printRelativeGrading(&gb1);
			break;
		case 22: printAbsGrade(&gb1);
			break;
		case 23:
			system("cls");
			//system("clear");
			break;
		default:
			printf("\nEnter valid option\n");
			break;
		}
	}
}
