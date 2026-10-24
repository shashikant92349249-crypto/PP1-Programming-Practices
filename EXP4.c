/*
 * Experiment 4 : Student Attendance Management System
 * Description  : Stores day-wise attendance (P/A) of students, calculates
 *                percentages, checks eligibility and prints a summary.
 */
#include <stdio.h>
#include <conio.h>

#define MAX_STUDENTS 20
#define MAX_DAYS 31
#define THRESHOLD 75.0      // minimum attendance % for eligibility
#define BORDERLINE 80.0     // below this (but eligible) = warning

int roll[MAX_STUDENTS];
char names[MAX_STUDENTS][30];
char attendance[MAX_STUDENTS][MAX_DAYS];    // 'P' or 'A' for each day
float percent[MAX_STUDENTS];
int n, days;                                // students and working days

// Read attendance of all students
void inputAttendance(void)
{
    int i, d, present;

    for (i = 0; i < n; i++)
    {
	printf("\nStudent %d - Roll number : ", i + 1);
	scanf("%d", &roll[i]);
	printf("Student %d - Name        : ", i + 1);
	scanf(" %[^\n]", names[i]);
	printf("Enter attendance for %d days (P/A) : ", days);
	present = 0;
	for (d = 0; d < days; d++)
	{
	    scanf(" %c", &attendance[i][d]);    // space skips whitespace
	    if (attendance[i][d] == 'P' || attendance[i][d] == 'p')
		present++;
	}
	percent[i] = (float)present / days * 100;
    }
}

// Show the register with percentage and eligibility
void displayAttendance(void)
{
    int i, d;

    printf("\n%-6s %-14s %-*s %8s  %-10s\n", "Roll", "Name", days + 1,
	   "Days", "Percent", "Status");
    printf("--------------------------------------------------------------\n");
    for (i = 0; i < n; i++)
    {
	printf("%-6d %-14s ", roll[i], names[i]);
	for (d = 0; d < days; d++)
	    printf("%c", attendance[i][d]);
	printf(" %7.2f%%  %-12s\n", percent[i],
	       percent[i] >= THRESHOLD ? "Eligible" : "Not Eligible");
    }
}

// List the students below the required threshold
void showBelowThreshold(void)
{
    int i, found = 0;

    printf("\nStudents with attendance below %.0f%%:\n", THRESHOLD);
    for (i = 0; i < n; i++)
    {
	if (percent[i] < THRESHOLD)
	{
	    printf("Roll %d - %s : %.2f%%\n", roll[i], names[i], percent[i]);
	    found = 1;
	}
    }
    if (!found)
	printf("None. All students satisfy the criteria.\n");
}

// Class-level attendance summary
void showSummary(void)
{
    int i, maxIdx = 0, minIdx = 0, eligible = 0, any = 0;
    float sum = 0;

    for (i = 0; i < n; i++)
    {
	sum += percent[i];
	if (percent[i] > percent[maxIdx]) maxIdx = i;
	if (percent[i] < percent[minIdx]) minIdx = i;
	if (percent[i] >= THRESHOLD) eligible++;
    }

    printf("\n------ Attendance Summary ------\n");
    printf("Total students        : %d\n", n);
    printf("Working days          : %d\n", days);
    printf("Class attendance      : %.2f%%\n", sum / n);
    printf("Maximum attendance    : %s (%.2f%%)\n", names[maxIdx], percent[maxIdx]);
    printf("Minimum attendance    : %s (%.2f%%)\n", names[minIdx], percent[minIdx]);
    printf("Eligible / Not eligible: %d / %d\n", eligible, n - eligible);

    printf("Need improvement      : ");
    for (i = 0; i < n; i++)
    {
	if (percent[i] < BORDERLINE)       // includes the failing students
	{
	    printf("%s%s", any ? ", " : "", names[i]);
	    any = 1;
	}
    }
    printf("%s\n", any ? "" : "None");
}

void main()
{
    int choice;

    clrscr();
    printf("Enter number of students (max %d): ", MAX_STUDENTS);
    scanf("%d", &n);
    printf("Enter number of working days (max %d): ", MAX_DAYS);
    scanf("%d", &days);
    inputAttendance();

    do
    {
	clrscr();
	printf("\n===== Attendance Management =====\n");
	printf("1. Display Attendance\n2. Students Below Threshold\n");
	printf("3. Attendance Summary\n4. Exit\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	switch (choice)
	{
	    case 1: displayAttendance();  break;
	    case 2: showBelowThreshold(); break;
	    case 3: showSummary();        break;
	    case 4: printf("Thank you!\n"); break;
	    default: printf("Invalid choice! Try again.\n");
	}

	if (choice != 4)
	{
	    printf("\n\nPress any key to continue...");
	    getch();
	}
    } while (choice != 4);

    getch();
}