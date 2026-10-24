/*
 * Experiment 3 : Inventory Management and Billing System
 * Description  : Manage shop products, update stock, generate bills
 *                and detect low-stock products.
 */
#include <stdio.h>
#include <conio.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MIN_STOCK 5             // stock at or below this is "low"
#define DISCOUNT_LIMIT 1000.0   // bill amount that earns a discount
#define DISCOUNT_RATE 0.10      // 10% discount
#define GST_RATE 0.05           // 5% tax

struct Product
{
    int id;
    char name[30];
    char category[20];
    int quantity;
    float price;            // unit price
};

struct Product products[MAX_PRODUCTS];
int count = 0;
int billNumber = 1000;      // bill numbers start from 1001

int findById(int id)
{
    int i;
    for (i = 0; i < count; i++)
	if (products[i].id == id)
	    return i;
    return -1;
}

// Stock status text based on quantity
const char *stockStatus(int qty)
{
    if (qty == 0)
	return "Out of Stock";
    if (qty <= MIN_STOCK)
	return "LOW STOCK";
    return "In Stock";
}

void addProduct(void)
{
    struct Product p;

    if (count >= MAX_PRODUCTS)
    {
	printf("Inventory is full!\n");
	return;
    }
    printf("Enter product ID : ");
    scanf("%d", &p.id);
    if (findById(p.id) != -1)
    {
	printf("Product ID already exists!\n");
	return;
    }
    printf("Enter name       : ");
    scanf(" %[^\n]", p.name);
    printf("Enter category   : ");
    scanf(" %[^\n]", p.category);
    printf("Enter quantity   : ");
    scanf("%d", &p.quantity);
    printf("Enter unit price : ");
    scanf("%f", &p.price);
    products[count++] = p;
    printf("Product added successfully!\n");
}

void displayProducts(void)
{
    int i;
    if (count == 0)
    {
	printf("Inventory is empty.\n");
	return;
    }
    printf("\n%-5s %-16s %-12s %5s %9s  %-12s\n",
	   "ID", "Name", "Category", "Qty", "Price", "Status");
    printf("--------------------------------------------------------------\n");
    for (i = 0; i < count; i++)
	printf("%-5d %-16s %-12s %5d %9.2f  %-12s\n",
	       products[i].id, products[i].name, products[i].category,
	       products[i].quantity, products[i].price,
	       stockStatus(products[i].quantity));
}

void searchProduct(void)
{
    int id, i;
    printf("Enter product ID to search: ");
    scanf("%d", &id);
    i = findById(id);
    if (i == -1)
	printf("Product not found!\n");
    else
    {
	printf("ID: %d | Name: %s | Category: %s | Qty: %d | Price: %.2f | %s\n",
	       products[i].id, products[i].name, products[i].category,
	       products[i].quantity, products[i].price,
	       stockStatus(products[i].quantity));
    }
}

void updateStock(void)
{
    int id, i, option, qty;

    printf("Enter product ID: ");
    scanf("%d", &id);
    i = findById(id);
    if (i == -1)
    {
	printf("Product not found!\n");
	return;
    }
    printf("1. Add stock  2. Reduce stock : ");
    scanf("%d", &option);
    printf("Enter quantity: ");
    scanf("%d", &qty);

    if (option == 1)
	products[i].quantity += qty;
    else if (option == 2 && qty <= products[i].quantity)
	products[i].quantity -= qty;
    else
    {
	printf("Invalid option or not enough stock!\n");
	return;
    }
    printf("Stock updated. New quantity of %s = %d\n",
	   products[i].name, products[i].quantity);
}

// Create a bill for several products
void generateBill(void)
{
    int itemId[20], itemQty[20];    // shopping cart
    int n = 0, id, qty, i, idx;
    float subtotal = 0, discount = 0, tax, grandTotal, amount;

    printf("Enter product ID and quantity (ID 0 to finish)\n");
    while (n < 20)
    {
	printf("Product ID : ");
	scanf("%d", &id);
	if (id == 0)
	    break;                  // end of purchase
	idx = findById(id);
	if (idx == -1)
	{
	    printf("Product not found!\n");
	    continue;               // ask again
	}
	printf("Quantity   : ");
	scanf("%d", &qty);
	if (qty <= 0 || qty > products[idx].quantity)
	{
	    printf("Only %d unit(s) of %s in stock!\n",
		   products[idx].quantity, products[idx].name);
	    continue;
	}
	products[idx].quantity -= qty;      // reduce inventory
	itemId[n] = id;
	itemQty[n] = qty;
	n++;
    }

    if (n == 0)
    {
	printf("No items purchased.\n");
	return;
    }

    billNumber++;
    printf("\n=============== BILL No. %d ===============\n", billNumber);
    printf("%-16s %5s %9s %10s\n", "Item", "Qty", "Rate", "Amount");
    printf("--------------------------------------------\n");
    for (i = 0; i < n; i++)
    {
	idx = findById(itemId[i]);
	amount = itemQty[i] * products[idx].price;
	subtotal += amount;
	printf("%-16s %5d %9.2f %10.2f\n",
	       products[idx].name, itemQty[i], products[idx].price, amount);
    }
    if (subtotal >= DISCOUNT_LIMIT)
	discount = subtotal * DISCOUNT_RATE;
    tax = (subtotal - discount) * GST_RATE;
    grandTotal = subtotal - discount + tax;

    printf("--------------------------------------------\n");
    printf("%-33s %10.2f\n", "Sub Total", subtotal);
    printf("%-33s %10.2f\n", "Less: Discount (10% if >= 1000)", discount);
    printf("%-33s %10.2f\n", "GST (5%)", tax);
    printf("%-33s %10.2f\n", "GRAND TOTAL", grandTotal);
    printf("============================================\n");
}

void lowStockReport(void)
{
    int i, found = 0;
    printf("\nProducts with stock <= %d:\n", MIN_STOCK);
    for (i = 0; i < count; i++)
    {
	if (products[i].quantity <= MIN_STOCK)
	{
	    printf("ID %d - %s (Qty: %d)\n",
		   products[i].id, products[i].name, products[i].quantity);
	    found = 1;
	}
    }
    if (!found)
	printf("All products have sufficient stock.\n");
}

void main()
{
    int choice;

    do
    {
	clrscr();
	printf("\n===== Inventory & Billing System =====\n");
	printf("1. Add Product\n2. Display Products\n3. Search Product\n");
	printf("4. Update Stock\n5. Generate Bill\n6. Low Stock Report\n7. Exit\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	switch (choice)
	{
	    case 1: addProduct();      break;
	    case 2: displayProducts(); break;
	    case 3: searchProduct();   break;
	    case 4: updateStock();     break;
	    case 5: generateBill();    break;
	    case 6: lowStockReport();  break;
	    case 7: printf("Thank you!\n"); break;
	    default: printf("Invalid choice! Try again.\n");
	}

	if (choice != 7)
	{
	    printf("\n\nPress any key to continue...");
	    getch();
	}
    } while (choice != 7);

    getch();
}