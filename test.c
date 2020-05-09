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
	
	while(1)
	{
		printf("0.Exit\n");
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
		printf("21.Print gradereport (over all grade and marksheet) for all the students \n");		
		printf("22.Print relative grading for all the students \n");					
		printf("23.Clear screen\n");
		printf("\nEnter a menu choice: ");
		scanf("%d", &menu);
		switch(menu)
		{
			case 0: exit(0);
				break;
			case 1: defdata(&gb1);
				break;
			case 2: addRecord (&gb1);
				break;
			case 3:deleteRecordHead(&gb1);
				break;
			case 4: scanf("%c",&ch); // temp statement to clear buffer
			printf("\nEnter name: ");
//			fgets(name, 50, stdin);  // read name string
			scanf("%[^\n]",name);
			roll_num=0;
			deleteRecord(name, roll_num, &gb1);
				break;
			case 5: scanf("%c",&ch);
			printf("\nEnter roll number:  ");
			scanf("%lld",&roll_num);
//			printf("roll no is %lld\n", roll_num);
			strcpy(name,"");
			deleteRecord(name, roll_num, &gb1);
				break;
			case 6: deleteGradebook(&gb1);
				break;
			case 7: //printf("I m here\n"); 
			scanf("%c",&ch); // temp statement to clear buffer
			printf("\nEnter name: ");
//			scanf("%c",&ch); // temp statement to clear buffer
			//fgets(name, 50, stdin);  // read name string
			scanf("%[^\n]",name);
			cnt=strcmp(name,"Samarth Gupta");
			printf("enetreed strng %s is same as Samarth Gupta %d \n",name,cnt);
			scanf("%c",&ch);
			findRecordByName(&gb1, name, true); //true for printing the found record
				break;
			case 8: scanf("%c",&ch); // temp statement to clear buffer
			printf("\nEnter roll number:  ");
			scanf("%lld", &roll_num);
			findRecordByRollNum(&gb1, roll_num, true); //true for printing the found record
				break;
			case 9: printf("\nEnter roll number:  ");
			scanf("%lld", &roll_num);
			scanf("%c",&ch); // temp statement to clear buffer
			printf("\nEnter name: ");
//			fgets(name, 50, stdin);  // read name string
			scanf("%[^\n]",name);
			rec1=updateNameInRecord(name, roll_num, &gb1);
			printRecord(&rec1);
				break;
			case 10: scanf("%c",&ch); // temp statement to clear buffer
			printf("\nEnter name: ");
//			fgets(name, 50, stdin);  // read name string
//			scanf("%c",&ch); // temp statement to clear buffer
			scanf("%[^\n]",name);
			printf("\nEnter roll number:  ");
			scanf("%lld", &roll_num);
			rec1=updateRollNumInRecord(name, roll_num, &gb1);
			printRecord(&rec1);
				break;
			case 11: scanf("%c",&ch); // temp statement to clear buffer
			printf("\nEnter name: ");
//			fgets(name, 50, stdin);  // read name string
			scanf("%[^\n]",name);
			rec1=updateNameInRecord(name, roll_num, &gb1);
			roll_num=0;
			printf("\nEnter new marksheet details:\n");
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
			rec1=updateMarksheetInRecord(name, roll_num, marks, &gb1);
			printRecord(&rec1);
				break;
			case 12: scanf("%c",&ch); // temp statement to clear bufferprintf("\nEnter roll number:  "); 
			printf("\nEnter roll number:  ");
			scanf("%lld", &roll_num);
			strcpy(name,"");
			printf("\nEnter new marksheet details:\n");
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
			rec1=updateMarksheetInRecord(name, roll_num, marks, &gb1);
			printRecord(&rec1);
				break;
			case 13: //sort ascending
			sortGradebookName(&gb1,true);
				break;
			case 14: //sort descending
			sortGradebookName(&gb1,false);
				break;
			case 15: //sort ascending
			sortGradebookRollNum(&gb1,true);
				break;
			case 16: //sort descending
			sortGradebookRollNum(&gb1,false);
				break;
			case 17: 
			//findTopper(&gb1);
				break;
			case 18: 
			//findFailingStudents(&gb1);
				break;
			case 19: printGradebook(&gb1);
				break;
			case 20: cnt=countGradebookRecords(&gb1);
				printf("\nNumber of records in the gradebook = %d",cnt);
				break;			
			case 21: printGrades(&gb1);
				break;			
			case 22: printRelativeGrading(&gb1);
				break;			
			case 23: 		system("clear");
				break;						
			default: printf("\nEnter valid option\n");
				break;
		}	
	}
	//printGradebook(&gb1);	//done 

//	findRecordByName(&gb1, "Siddharth Borderwala", true);	//done  
	
	//printGradebook(&gb1);//added
	
//	deleteRecord("Siddharth Borderwala",0, &gb1);	//done 
	
//	updateNameInRecord("Dev Patel", 1910110120, &gb1);	//done

//	updateRollNumInRecord("Samarth Gupta", 1910110338, &gb1);	//done


//	updateMarksheetInRecord("", 0, (Marksheet) {
//		0,97.5,99.0,97.2,98.6
//	}, &gb1);	//done
//	printGradebook(&gb1);

//	findRecordByRollNum(&gb1, (rollNum) 1910110285, true);	//done
//	findRecordByName(&gb1, "Dev Patel", true);	//done

//	printGradebook(&gb1);	//done

//	deleteRecordHead(&gb1);	
//	deleteGradebook(&gb1);
//	printGradebook(&gb1);
}
