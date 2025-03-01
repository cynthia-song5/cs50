#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//prototypes
int count_words(string t);
int sentences(string t);
int letters(string t);

int main(void)
{
    string text = get_string("Text: ");
    int w = count_words(text);
    float s = (float)sentences(text);
    float l = (float)letters(text);
    float avgw = w / 100.0;

    //find average sentences and letters
    s /= avgw;
    l /= avgw;

    //determines grade level
    int index = round((0.0588 * l) - (0.296 * s) - 15.8);

    //prints grade level
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

//counts the total number of words
int count_words(string t)
{
    int spaces = 0;
    for (int i = 0; i < strlen(t); i++)
    {
        if (t[i] == ' ')
        {
            spaces++;
        }
    }
    return spaces + 1;
}
//counts the total number of letters
int letters(string t)
{
    int total = 0;
    for (int i = 0; i < strlen(t); i++)
    {
        if (isalpha(t[i]))
        {
            total++;
        }
    }
    return total;
}

//counts the total number of sentences
int sentences(string t)
{
    int total = 0;
    for (int i = 0; i < strlen(t); i++)
    {
        //checks for punctuation
        if (t[i] == '.' || t[i] == '!' || t[i] == '?')
        {
            total++;
        }
    }
    return total;
}