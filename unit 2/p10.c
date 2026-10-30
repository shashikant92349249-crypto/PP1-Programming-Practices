#include <stdio.h>
int main()
{
    float quantity, price, discount;
    float total, discountAmount, finalAmount;
    printf("Enter quantity: ");
    scanf("%f", &quantity);
   printf("Enter price per item: ");
    scanf("%f", &price);
   printf("Enter discount percentage: ");
   scanf("%f", &discount);
   total = quantity * price;
   discountAmount = (total * discount) / 100;
    finalAmount = total - discountAmount;
    printf("Total Amount = %.2f\n", total);
    printf("Discount Amount = %.2f\n", discountAmount);
    printf("Final Amount = %.2f", finalAmount);
    return 0;
}
