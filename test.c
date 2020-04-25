#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gradebook.h"

void main()
{
	Gradebook gb1 = createGradeBook();
	createNewRecord(&gb1, (Record) {
		"Siddharth Borderwala",
		1910110389,
		(Marksheet) {98.2,97.5,99.0,97.2,98.6}
	});
	createNewRecord(&gb1, (Record) {
		"Niramay Kachhadiya",
		1910110225,
		(Marksheet) {98.2,97.5,99.0,97.2,98.6}
	});
	createNewRecord(&gb1, (Record) {
		"Yash Varshney",
		1910110285,
		(Marksheet) {98.2,97.5,99.0,97.2,98.6}
	});
	createNewRecord(&gb1, (Record) {
		"Samarth Gupta",
		1910110300,
		(Marksheet) {98.2,97.5,99.0,97.2,98.6}
	});
	createNewRecord(&gb1, (Record) {
		"Aarjav Desai",
		1910110120,
		(Marksheet) {98.2,97.5,99.0,97.2,98.6}
	});

	printGradebook(&gb1);	//done

	findRecordByName(&gb1, "Siddharth Borderwala", true);	//done
	deleteRecord("Siddharth Borderwala", 0, &gb1);	//done
	
	updateNameInRecord("Dev Patel", 1910110120, &gb1);	//done
	updateRollNumInRecord("Samarth Gupta", 1910110215, &gb1);	//done
	updateMarksheetInRecord("", (rollNum) 1910110285, (Marksheet) {
		98.2,97.5,99.0,97.2,98.6
	}, &gb1);	//done

	findRecordByRollNum(&gb1, (rollNum) 1910110285, true);	//done
	findRecordByName(&gb1, "Dev Patel", true);	//done

	printGradebook(&gb1);	//done
	deleteGradebook(&gb1);
	printGradebook(&gb1);
}