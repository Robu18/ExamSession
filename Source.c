#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>


int cmp(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

int promote(int v[], int n) {
	for (int i = 1; i <= n; i++)
		if (v[i] < 5) return 0;
	return 1;
}

typedef struct {
	char firstname[25], lastname[25];
	int age, grades[10];
}stud;

void statistic(stud e[], int nrex, int nrstd) {
	system("cls");
	printf("\nThe statistic is based on the average grade of every student.\n\n");
	printf("Interpretation of statistical indicators:\n");
	printf("The MEAN is the sum of the value of each observation in a dataset divided by the number of observations.\n");
	printf("The MEDIAN is the middle value in distribution when the values are arranged in ascending or descending order.\n");
	printf("  The median divides the distribution in half(there are 50 %% of observations on either side of the median value).\n");
	printf("The MODE is the most commonly occurring value in a distribution.\n");
	printf("The RANGE is the difference between the largest and smallest values in a set of values.\n");
	printf("The VARIANCE is the average squared deviation from the mean.\n");
	printf("The STANDARD DEVIATION is the square root of the variance.\n");
	printf("The AVERAGE DEVIATION of a data set is an average of all deviations from a set central point.\n");
	printf("The COEFFICENT OF VARIATION shows the extent of variability in relation to the mean of the population.\n");
	float* avg = malloc(nrstd * sizeof(float));
	for (int i = 1; i <= nrstd; i++) avg[i] = 0;
	for (int i = 1; i <= nrstd; i++) {
		for (int j = 1; j <= nrex; j++)
			avg[i] += e[i].grades[j];
		avg[i] /= nrex;
	}
	printf("\nFirst Name | Last Name | Average\n");
	printf("---------------------------------\n");
	for (int i = 1; i <= nrstd; i++) {
		printf("%s | %s | %.2f\n", e[i].firstname, e[i].lastname, avg[i]);
		printf("---------------------------------\n");
	}
	qsort(avg, nrstd + 1, sizeof(float), cmp);
	//Central Tendency Indicators
	printf("\nCentral Tendency Indicators:\n");
	float mean = 0, median = avg[(nrstd + 1) / 2], mode = 0;
	int okmax = 0, oki = 0;
	for (int i = 1; i <= nrstd; i++) {
		mean += avg[i];
		int okk = 0;
		for (int j = 1; j <= nrstd; j++)
			if (avg[i] == avg[j]) okk++;
		if (okk >= okmax) okmax = okk, oki = i;
	}
	mean /= nrstd;
	if (okmax != 1 && okmax != 0) {
		mode = avg[oki];
		printf("MEAN: %.2f\nMEDIAN: %.2f\nMODE: %.2f\n\n", mean, median, mode);
	}
	else
		printf("MEAN: %.2f\nMEDIAN: %.2f\nMODE: N/A\n\n", mean, median);
	//Variation Measures
	printf("Variation Measures:\n");
	float abl = 0, avgmin = 11, avgmax = 0, dis = 0;
	for (int i = 1; i <= nrstd; i++) {
		abl += abs(avg[i] - mean);
		dis += pow(avg[i] - mean, 2);
		if (avg[i] > avgmax) avgmax = avg[i];
		if (avg[i] < avgmin) avgmin = avg[i];
	}
	abl /= nrstd; dis /= nrstd;
	float sd = sqrt(dis), cv = sd / mean * 100, r = avgmax - avgmin;
	printf("RANGE: %.2f \nVARIANCE: %.2f \nAVERAGE DEVIATION: %.2F \nSTANDARD DEVIATION: %.2f \nCOEFFICIENT OF VARIATION: %.2f%%\n\n", r, dis, abl, sd, cv);
	//Other
	printf("Other:\n");
	float prm = 0;
	for (int i = 1; i <= nrstd; i++)
		if (promote(e[i].grades, nrex)) prm++;
	printf("The number of students who promote all the exams: %.2f (%.2f%%)\n", prm, prm / nrstd * 100);
	printf("The number of students who did not promote all the exams: %.2f (%.2f%%)", nrstd - prm, (nrstd - prm) / nrstd * 100);
	printf("\n\nPress any key to go back to the menu...");
}

void eachexam(stud e[], int nrex, int nrstd) {
	system("cls");
	printf("Information for each exam.\n\n");
	for (int i = 1; i <= nrex; i++) {
		float prom = 0, av = 0, gmx = 0, gmn = 11;
		int gmxi = 0, gmni = 0;
		printf("For exam no.%d: \n", i);
		for (int j = 1; j <= nrstd; j++) {
			if (e[j].grades[i] >= 5) prom++;
			if (e[j].grades[i] > gmx) gmx = e[j].grades[i], gmxi = j;
			if (e[j].grades[i] < gmn) gmn = e[j].grades[i], gmni = j;
			av += e[j].grades[i];
		}
		av /= nrstd;
		printf("\tThe number of students who promote the exam: %.2f\n", prom);
		printf("\tThe rate of promovability: %.2f%%\n", prom / nrstd * 100);
		printf("\tThe average grade: %.2f\n", av);
		printf("\tBest student: %s %s (%.2f)\n", e[gmxi].firstname, e[gmxi].lastname, gmx);
		printf("\tWorst student: %s %s (%.2f)\n", e[gmni].firstname, e[gmni].lastname, gmn);
	}
	printf("\n--------------------------------\n");
	printf("Graph representing the promotion rate for each exam:\n");
	printf("--------------------------------\n\n");
	for (int i = 1; i <= nrex; i++) {
		printf("Exam no.%d: ", i);
		float pr = 0;
		for (int j = 1; j <= nrstd; j++)
			if (e[j].grades[i] >= 5) pr++, printf(">>>");
		printf("\t(%.2f%%)\n", pr / nrstd * 100);
	}
	printf("--------------------------------\n");
	printf("\n\nPress any key to go back to the menu...");
}

void beststud(stud e[], int nrex, int nrstd) {
	system("cls");
	float* avg = malloc(nrstd * sizeof(float));
	for (int i = 1; i <= nrstd; i++) avg[i] = 0;
	for (int i = 1; i <= nrstd; i++) {
		for (int j = 1; j <= nrex; j++)
			avg[i] += e[i].grades[j];
		avg[i] /= nrex;
	}
	float max = 0, g = 0; int maxi;
	for (int i = 1; i <= nrstd; i++)
		if (max < avg[i]) max = avg[i], maxi = i;
	printf("The best student is:\n\t%s %s \n\tAge: %d \n\tAverage Grade: %.2f.\n", e[maxi].firstname, e[maxi].lastname, e[maxi].age, max);
	printf("--------------------------------------------\n");
	printf("All grades: \n");
	for (int i = 1; i <= nrex; i++)
		printf("\t->Exam no.%d: %d;\n", i, e[maxi].grades[i]);
	printf("--------------------------------------------\n");
	for (int i = 1; i <= nrex; i++)
		if (e[maxi].grades[i] >= 5) g++;
	printf("Promotion rate: %.2f%%\n\n", g / nrex * 100);
	printf("Press any key to go back to the menu...");
}

void menu(stud e[], int nrex, int nrstd) {
	_getch();
	system("cls");
	int c;
	printf("\n--------------------------------------------------------------\n");
	printf("For statistical analysis (by averages) enter the number 1.\n");
	printf("--------------------------------------------------------------\n");
	printf("For the situation of each exam enter the number 2.\n");
	printf("--------------------------------------------------------------\n");
	printf("For the best student enter the number 3.\n");
	printf("--------------------------------------------------------------\n");
	printf("For exit enter the number 4.\n");
	printf("--------------------------------------------------------------\n");
	printf("\n\n\t\tEnter your choice: "); scanf("%d", &c);
	switch (c) {
	case 1:
		statistic(e, nrex, nrstd);
		menu(e, nrex, nrstd);
		break;
	case 2:
		eachexam(e, nrex, nrstd);
		menu(e, nrex, nrstd);
		break;
	case 3:
		beststud(e, nrex, nrstd);
		menu(e, nrex, nrstd);
		break;
	case 4:
		exit(1);
	default:
		system("cls");
		printf("Wrong key :( Try again!");
		menu(e, nrex, nrstd);
	}
}


void main() {
	int nrex, nrstd;
	printf("Enter the number of students: "); scanf("%d", &nrstd);
	printf("Enter the number of exams: "); scanf("%d", &nrex);
	printf("--------------------------------------\n");
	stud e[10];
	for (int i = 1; i <= nrstd; i++) {
		printf("First Name of student no.%d: ", i); scanf("%s", &e[i].firstname);
		printf("Last Name of student no.%d: ", i); scanf("%s", &e[i].lastname);
		printf("Age of student no.%d: ", i); scanf("%d", &e[i].age);
		for (int j = 1; j <= nrex; j++) {
			printf("Grade of student no.%d for the no.%d exam: ", i, j);
			scanf("%d", &e[i].grades[j]);
		}
		printf("--------------------------------------\n");
	}
	printf("\nPress any key to see the menu.");
	menu(e, nrex, nrstd);
}