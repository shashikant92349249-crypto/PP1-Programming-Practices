/*
 * Experiment 2 : Library Management System
 * Description  : Add, display, search, issue and return books.
 */
#include <stdio.h>
#include <conio.h>
#include <string.h>     // strcmp, strstr

#define MAX_BOOKS 100

// Structure for one book
struct Book
{
    int id;
    char title[40];
    char author[30];
    char category[20];
    float price;
    int available;      // 1 = available in library, 0 = issued
};

struct Book books[MAX_BOOKS];
int count = 0;

// Print the table heading
void printHeader(void)
{
    printf("\n%-5s %-26s %-18s %-10s %8s %-10s\n",
	   "ID", "Title", "Author", "Category", "Price", "Status");
    printf("-----------------------------------------------------------------------------\n");
}

// Print one book row (i = index in the array)
void printBook(int i)
{
    printf("%-5d %-26s %-18s %-10s %8.2f %-10s\n",
	   books[i].id, books[i].title, books[i].author, books[i].category,
	   books[i].price, books[i].available ? "Available" : "Issued");
}

// Return array index of book with given ID, or -1 if not found
int findById(int id)
{
    int i;
    for (i = 0; i < count; i++)
	if (books[i].id == id)
	    return i;
    return -1;
}

void addBook(void)
{
    struct Book b;

    if (count >= MAX_BOOKS)
    {
	printf("Library is full!\n");
	return;
    }
    printf("Enter book ID   : ");
    scanf("%d", &b.id);
    if (findById(b.id) != -1)          // reject duplicate IDs
    {
	printf("A book with this ID already exists!\n");
	return;
    }
    printf("Enter title     : ");
    scanf(" %[^\n]", b.title);
    printf("Enter author    : ");
    scanf(" %[^\n]", b.author);
    printf("Enter category  : ");
    scanf(" %[^\n]", b.category);
    printf("Enter price     : ");
    scanf("%f", &b.price);
    b.available = 1;                    // new book is available
    books[count++] = b;
    printf("Book added successfully!\n");
}

void displayBooks(void)
{
    int i;
    if (count == 0)
    {
	printf("No books in the library.\n");
	return;
    }
    printHeader();
    for (i = 0; i < count; i++)
	printBook(i);
}

// Search by ID, title or author
void searchBook(void)
{
    int option, id, i, found = 0;
    char text[40];

    printf("Search by: 1.ID  2.Title  3.Author : ");
    scanf("%d", &option);

    if (option == 1)
    {
	printf("Enter book ID: ");
	scanf("%d", &id);
	i = findById(id);
	if (i != -1)
	{
	    printHeader();
	    printBook(i);
	    found = 1;
	}
    }
    else if (option == 2 || option == 3)
    {
	printf("Enter %s (full or partial): ", option == 2 ? "title" : "author");
	scanf(" %[^\n]", text);
	for (i = 0; i < count; i++)
	{
	    // strstr returns non-NULL if 'text' occurs inside the string
	    char *place = (option == 2) ? strstr(books[i].title, text)
					: strstr(books[i].author, text);
	    if (place != NULL)
	    {
		if (!found)
		    printHeader();
		printBook(i);
		found = 1;
	    }
	}
    }
    else
    {
	printf("Invalid search option!\n");
	return;
    }
    if (!found)
	printf("No matching book found.\n");
}

void issueBook(void)
{
    int id, i;
    printf("Enter book ID to issue: ");
    scanf("%d", &id);
    i = findById(id);
    if (i == -1)
	printf("Book not found!\n");
    else if (!books[i].available)
	printf("Sorry, '%s' is already issued.\n", books[i].title);
    else
    {
	books[i].available = 0;
	printf("Book '%s' issued successfully.\n", books[i].title);
    }
}

void returnBook(void)
{
    int id, i;
    printf("Enter book ID to return: ");
    scanf("%d", &id);
    i = findById(id);
    if (i == -1)
	printf("Book not found!\n");
    else if (books[i].available)
	printf("This book was not issued.\n");
    else
    {
	books[i].available = 1;
	printf("Book '%s' returned successfully.\n", books[i].title);
    }
}

// status = 1 shows available books, status = 0 shows issued books
void displayByStatus(int status)
{
    int i, found = 0;
    for (i = 0; i < count; i++)
    {
	if (books[i].available == status)
	{
	    if (!found)
		printHeader();
	    printBook(i);
	    found = 1;
	}
    }
    if (!found)
	printf("No %s books.\n", status ? "available" : "issued");
}

void main()
{
    int choice;

    do
    {
	clrscr();
	printf("\n===== Library Management System =====\n");
	printf("1. Add Book\n2. Display All Books\n3. Search Book\n");
	printf("4. Issue Book\n5. Return Book\n6. Display Available Books\n");
	printf("7. Display Issued Books\n8. Exit\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	switch (choice)
	{
	    case 1: addBook();            break;
	    case 2: displayBooks();       break;
	    case 3: searchBook();         break;
	    case 4: issueBook();          break;
	    case 5: returnBook();         break;
	    case 6: displayByStatus(1);   break;
	    case 7: displayByStatus(0);   break;
	    case 8: printf("Thank you!\n"); break;
	    default: printf("Invalid choice! Try again.\n");
	}

	if (choice != 8)
	{
	    printf("\n\nPress any key to continue...");
	    getch();
	}
    } while (choice != 8);

    getch();
}