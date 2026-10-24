/*
 * Experiment 5 : Employee Payroll Management System
 * Description  : Calculates gross salary, deductions and net salary of
 *                employees and prints salary slips and a summary.
 */
#include <stdio.h>
#include <conio.h>

#define MAX_EMP 50
#define HRA_RATE 0.20       // House Rent Allowance: 20% of basic
#define DA_RATE 0.10        // Dearness Allowance: 10% of basic
#define PF_RATE 0.12        // Provident Fund: 12% of basic

struct Employee
{
    int id;
    char name[30];
    char designation[20];
    float basic;
    float hra, da, otherAllowance;
    float gross;
    float pf, profTax, incomeTax, otherDeduction;
    float totalDeduction;
    float net;
};

struct Employee emp[MAX_EMP];
int count = 0;

// Calculate income tax using simple slabs on gross salary
float calcIncomeTax(float gross)
{
    if (gross > 50000)
	return gross * 0.10;    // 10% for gross above 50000
    else if (gross > 30000)
	return gross * 0.05;    // 5% for gross above 30000
    return 0;                   // no tax otherwise
}

void addEmployee(void)
{
    struct Employee e;

    if (count >= MAX_EMP)
    {
	printf("Employee list is full!\n");
	return;
    }
    printf("Enter employee ID     : ");
    scanf("%d", &e.id);
    printf("Enter name            : ");
    scanf(" %[^\n]", e.name);
    printf("Enter designation     : ");
    scanf(" %[^\n]", e.designation);
    printf("Enter basic salary    : ");
    scanf("%f", &e.basic);
    printf("Enter other allowances: ");
    scanf("%f", &e.otherAllowance);
    printf("Enter other deductions: ");
    scanf("%f", &e.otherDeduction);

    // Salary calculation
    e.hra = e.basic * HRA_RATE;
    e.da = e.basic * DA_RATE;
    e.gross = e.basic + e.hra + e.da + e.otherAllowance;

    e.pf = e.basic * PF_RATE;
    e.profTax = (e.gross >= 20000) ? 200 : 0;   // flat professional tax
    e.incomeTax = calcIncomeTax(e.gross);
    e.totalDeduction = e.pf + e.profTax + e.incomeTax + e.otherDeduction;
    e.net = e.gross - e.totalDeduction;

    emp[count++] = e;
    printf("Employee added successfully!\n");
}

void displayAll(void)
{
    int i;
    if (count == 0)
    {
	printf("No employee records.\n");
	return;
    }
    printf("\n%-5s %-14s %-12s %10s %10s %10s\n",
	   "ID", "Name", "Designation", "Gross", "Deduction", "Net");
    printf("------------------------------------------------------------------\n");
    for (i = 0; i < count; i++)
	printf("%-5d %-14s %-12s %10.2f %10.2f %10.2f\n",
	       emp[i].id, emp[i].name, emp[i].designation,
	       emp[i].gross, emp[i].totalDeduction, emp[i].net);
}

// Detailed salary slip of one employee
void salarySlip(void)
{
    int id, i, found = 0;

    printf("Enter employee ID: ");
    scanf("%d", &id);
    for (i = 0; i < count; i++)
    {
	if (emp[i].id == id)
	{
	    found = 1;
	    printf("\n========== SALARY SLIP ==========\n");
	    printf("ID          : %d\nName        : %s\nDesignation : %s\n",
		   emp[i].id, emp[i].name, emp[i].designation);
	    printf("--------- Earnings ---------\n");
	    printf("Basic Salary      : %10.2f\n", emp[i].basic);
	    printf("HRA (20%%)         : %10.2f\n", emp[i].hra);
	    printf("DA (10%%)          : %10.2f\n", emp[i].da);
	    printf("Other Allowances  : %10.2f\n", emp[i].otherAllowance);
	    printf("GROSS SALARY      : %10.2f\n", emp[i].gross);
	    printf("-------- Deductions --------\n");
	    printf("Provident Fund    : %10.2f\n", emp[i].pf);
	    printf("Professional Tax  : %10.2f\n", emp[i].profTax);
	    printf("Income Tax        : %10.2f\n", emp[i].incomeTax);
	    printf("Other Deductions  : %10.2f\n", emp[i].otherDeduction);
	    printf("TOTAL DEDUCTIONS  : %10.2f\n", emp[i].totalDeduction);
	    printf("----------------------------\n");
	    printf("NET SALARY        : %10.2f\n", emp[i].net);
	    printf("=================================\n");
	    break;
	}
    }
    if (!found)
	printf("Employee not found!\n");
}

// List employees whose net salary is above a given amount
void searchBySalary(void)
{
    float limit;
    int i, found = 0;

    printf("Show employees with net salary above: ");
    scanf("%f", &limit);
    for (i = 0; i < count; i++)
    {
	if (emp[i].net > limit)
	{
	    printf("%d - %s (%s) : Net = %.2f\n",
		   emp[i].id, emp[i].name, emp[i].designation, emp[i].net);
	    found = 1;
	}
    }
    if (!found)
	printf("No employee has net salary above %.2f\n", limit);
}

// Organisation-level totals
void organisationSummary(void)
{
    int i, hi = 0, lo = 0;
    float totalGross = 0, totalDed = 0, totalNet = 0;

    if (count == 0)
    {
	printf("No employee records.\n");
	return;
    }
    for (i = 0; i < count; i++)
    {
	totalGross += emp[i].gross;
	totalDed += emp[i].totalDeduction;
	totalNet += emp[i].net;
	if (emp[i].net > emp[hi].net) hi = i;
	if (emp[i].net < emp[lo].net) lo = i;
    }
    printf("\n------- Organisation Summary -------\n");
    printf("Total employees     : %d\n", count);
    printf("Total gross salary  : %.2f\n", totalGross);
    printf("Total deductions    : %.2f\n", totalDed);
    printf("Total net salary    : %.2f\n", totalNet);
    printf("Average net salary  : %.2f\n", totalNet / count);
    printf("Highest paid        : %s (%.2f)\n", emp[hi].name, emp[hi].net);
    printf("Lowest paid         : %s (%.2f)\n", emp[lo].name, emp[lo].net);
}

void main()
{
    int choice;

    do
    {
	clrscr();
	printf("\n===== Employee Payroll System =====\n");
	printf("1. Add Employee\n2. Display All Employees\n3. Salary Slip\n");
	printf("4. Search by Net Salary\n5. Organisation Summary\n6. Exit\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	switch (choice)
	{
	    case 1: addEmployee();         break;
	    case 2: displayAll();          break;
	    case 3: salarySlip();          break;
	    case 4: searchBySalary();      break;
	    case 5: organisationSummary(); break;
	    case 6: printf("Thank you!\n"); break;
	    default: printf("Invalid choice! Try again.\n");
	}

	if (choice != 6)
	{
	    printf("\n\nPress any key to continue...");
	    getch();
	}
    } while (choice != 6);

    getch();
}