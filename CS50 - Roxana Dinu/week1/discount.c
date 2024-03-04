#include <cs50.h>
#include <stdio.h>

float discount(float price, int percentage);
int main(void)
{
    float regular = get_float("Regular price: ");
    int percentage= get_int("Discount percentage: ");
    float sale = discount(regular, percentage);
     printf("Sale price is %.2f \n", sale);
}

float discount(float price, int percentage)
{
    float sale = price*((float)(100-percentage)/100.0);
    return sale;
}