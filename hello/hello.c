#include <cs50.h>
#include <stdio.h>

int main(void)
{
      //asks user for name
    string name = get_string("What's your name? ");
    //prints 'hello,' followed by the user's name
    printf("hello, %s\n", name);

//printf("hello, %s\n", get_string("What's your name?")); --> worse design bc unable to use answer later
}
