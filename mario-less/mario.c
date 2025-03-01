#include <cs50.h >
#include <stdio.h>

int main(void)
{
    //prompts user
    int height = get_int("Height: ");
    if (height <= 0 || height > 8)
    {
        height = get_int("Height: ");
    }

    //creates pyramid
    for (int i = 1; i <= height; i++)
    {
        //spaces
        for (int j = 0; j <  height - i; j++)
        {
            printf(" ");
        }
        //hashes
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}

