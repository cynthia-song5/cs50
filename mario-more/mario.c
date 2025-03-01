#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //prompts user
     int height = get_int("Height: ");
    if (height < 0 || height > 8 ){
      height = get_int("Height: ");
    }

    //creates triangles

    for (int i = 1; i<=height; i++){
    for (int j = 0; j<= i; j++){
        int dif = height - i;
        if (dif > j){
          printf (" ");
        }
        else{
        printf ("#");
        }
        dif++;
    }
    printf ("\n");
    }
}