/*
 * Experiment 1 : Student Performance Analysis System
 * Description  : Menu-driven program to add, display, search and
 *                analyze student academic records.
 */
#include <stdio.h>
#include <conio.h>
#include <string.h>     // (string support)

#define MAX_STUDENTS 50     // maximum number of students stored
#define SUBJECTS 3          // number of subjects per student
#define PASS_MARKS 35       // minimum marks needed in EACH subject
#define MIN_ATTENDANCE 75.0 // minimum attendance % required

// Subject names stored as an array of strings
const char *subjectNames[SUBJECTS] = {"PP1", "BWD", "AOC"};

// Structure that groups all data of one student
struct Student
{
    int roll;                // roll number
    char name[30];           // student name
    int marks[SUBJECTS];     // marks in each subject
    float attendance;        // attendance percentage
    int total;               // total marks
    float percentage;        // percentage
    char grade;              // grade: A, B, C or F
    int passed;              // 1 = pass, 0 = fail
};

struct Student students[MAX_STUDENTS];  // array of student records
int count = 0;                          // number of students added so far

// Decide grade from percentage; a failed student always gets 'F'
char calculateGrade(float percentage, int passed)
{
    if (!passed)
	return 'F';
    if (percentage >= 80)
	return 'A';
    if (percentage >= 60)
	return 'B';
    return 'C';
}

// Read one student's data, calculate results and store it
void addStudent(void)
{
    struct Student s;   // temporary record
    int i;

    if (count >= MAX_STUDENTS)
    {
	printf("Student list is full!\n");
	return;
    }

    printf("Enter roll number : ");
    scanf("%d", &s.roll);
    printf("Enter name        : ");
    scanf(" %[^\n]", s.name);   // reads a full line (spaces allowed)

    s.total = 0;
    s.passed = 1;               // assume pass until a subject fails
    for (i = 0; i < SUBJECTS; i++)
    {
	printf("Marks in %-13s (out of 100): ", subjectNames[i]);
	scanf("%d", &s.marks[i]);
	s.total += s.marks[i];              // add to total
	if (s.marks[i] < PASS_MARKS)
	    s.passed = 0;                   // failed in this subject
    }

    printf("Enter attendance %%: ");
    scanf("%f", &s.attendance);

    s.percentage = (float)s.total / (SUBJECTS * 100) * 100;
    s.grade = calculateGrade(s.percentage, s.passed);

    students[count] = s;        // copy record into the array
    count++;
    printf("Record added successfully!\n");
}

// Display all records in table form
void displayAll(void)
{
    int i;

    if (count == 0)
    {
	printf("No records available.\n");
	return;
    }
    printf("\n%-6s %-16s %6s %9s %6s %-7s %7s\n",
	   "Roll", "Name", "Total", "Percent", "Grade", "Result", "Attend");
    printf("------------------------------------------------------------------\n");
    for (i = 0; i < count; i++)
    {
	printf("%-6d %-16s %6d %8.2f%% %6c %-7s %6.1f%%\n",
	       students[i].roll, students[i].name, students[i].total,
	       students[i].percentage, students[i].grade,
	       students[i].passed ? "Pass" : "Fail", students[i].attendance);
    }
}

// Search a student by roll number (linear search)
void searchStudent(void)
{
    int roll, i, j, found = 0;

    printf("Enter roll number to search: ");
    scanf("%d", &roll);

    for (i = 0; i < count; i++)
    {
	if (students[i].roll == roll)
	{
	    found = 1;
	    printf("\nRoll       : %d\n", students[i].roll);
	    printf("Name       : %s\n", students[i].name);
	    for (j = 0; j < SUBJECTS; j++)
		printf("%-13s : %d\n", subjectNames[j], students[i].marks[j]);
	    printf("Total      : %d\n", students[i].total);
	    printf("Percentage : %.2f%%\n", students[i].percentage);
	    printf("Grade      : %c\n", students[i].grade);
	    printf("Result     : %s\n", students[i].passed ? "Pass" : "Fail");
	    printf("Attendance : %.1f%%\n", students[i].attendance);
	    break;              // stop after the record is found
	}
    }
    if (!found)
	printf("Student with roll number %d not found.\n", roll);
}

// Class-level analysis
void analyzePerformance(void)
{
    int i, j, highest = 0, lowest = 0;
    int passCount = 0, failCount = 0, lowAttendance = 0;
    float sumPercent = 0, subjectSum[SUBJECTS] = {0};

    if (count == 0)
    {
	printf("No records available.\n");
	return;
    }

    for (i = 0; i < count; i++)
    {
	sumPercent += students[i].percentage;
	if (students[i].passed) passCount++; else failCount++;
	if (students[i].attendance < MIN_ATTENDANCE) lowAttendance++;
	if (students[i].total > students[highest].total) highest = i;
	if (students[i].total < students[lowest].total)  lowest = i;
	for (j = 0; j < SUBJECTS; j++)
	    subjectSum[j] += students[i].marks[j];
    }

    printf("\n------- Class Analysis -------\n");
    printf("Total students      : %d\n", count);
    printf("Class average       : %.2f%%\n", sumPercent / count);
    printf("Passed / Failed     : %d / %d\n", passCount, failCount);
    printf("Pass percentage     : %.2f%%\n", (float)passCount / count * 100);
    printf("Highest performer   : %s (%d marks)\n",
	   students[highest].name, students[highest].total);
    printf("Lowest performer    : %s (%d marks)\n",
	   students[lowest].name, students[lowest].total);
    printf("Attendance < %.0f%%   : %d student(s)\n", MIN_ATTENDANCE, lowAttendance);
    for (j = 0; j < SUBJECTS; j++)
	printf("Average in %-13s: %.2f\n", subjectNames[j], subjectSum[j] / count);
}

void main()
{
    int choice;

    do
    {
	clrscr();
	printf("\n===== Student Performance Analysis =====\n");
	printf("1. Add Student\n2. Display All\n3. Search Student\n");
	printf("4. Analyze Performance\n5. Exit\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	switch (choice)
	{
	    case 1: addStudent();         break;
	    case 2: displayAll();         break;
	    case 3: searchStudent();      break;
	    case 4: analyzePerformance(); break;
	    case 5: printf("Thank you!\n"); break;
	    default: printf("Invalid choice! Try again.\n");
	}

	if (choice != 5)
	{
	    printf("\n\nPress any key to continue...");
	    getch();
	}
    } while (choice != 5);

    getch();
}