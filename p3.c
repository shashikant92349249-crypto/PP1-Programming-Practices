#include <stdio.h>
int main()
{
    float p, r, t, si;
  printf("Enter Principal Amount: ");
   scanf("%f", &p);
 printf("Enter Rate of Interest: ");
  scanf("%f", &r);
   printf("Enter Number of Years: ");
   scanf("%f", &t);
   si = (p * r * t) / 100;
   printf("Simple Interest = %.2f", si);

    return 0;
}
