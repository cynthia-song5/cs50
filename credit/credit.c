#include <cs50.h>
#include <stdio.h>
#include <math.h>


void check(long cc)
{
//determines the length of the string
    int length = 0;
    long copy = cc;
    do
    {
        //remove the last digit
        copy /= 10;
        //count
        length++;
    }
    while (copy != 0);

    //get total
    int sum1 = 0;
    int sum2 = 0;
    long x = cc;
    int total = 0;
    int mod1;
    int mod2;
    do
    {
        //sum of every other starting from end
        mod1 = x % 10;
        x /= 10;
        sum1 += mod1;
        //sum of every other starting from begining
        mod2 = x % 10;
        x /= 10;
        //multiply each term by 2 & add the first and last terms
        mod2 *= 2;
        sum2 = sum2 + (mod2 % 10) + (mod2 / 10);
    }
    while (x > 0);
    total = sum1 + sum2;

    //determines if the total ends in 0
    long end = total %= 10;
    if (end != 0)
    {
        printf("INVALID\n");
    }

    //determines the type
    else if (length != 15 && length != 13 && length != 16)
    {
        printf("INVALID\n");
    }
    else
    {
        //visa
        if (length == 16 && (long)(cc / pow(10, 15)) == 4)
        {
            printf("VISA\n");
        }
        else if (length == 13 && (long)(cc / pow(10, 12)) == 4)
        {
            printf("VISA\n");
        }
        //amex
        else if (length == 15 && ((long)(cc / pow(10, 13)) == 34 || ((long)(cc / pow(10, 13)) == 37)))
        {
            printf("AMEX\n");
        }
        //mastercard
        else if (length == 16 && (long)(cc / pow(10, 14) >= 51 && (long)(cc / pow(10, 14)) <= 55))
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}

int main(void)
{
    long card = get_long("Number: ");
    check(card);
}
