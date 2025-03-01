#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //stops code if the key is not 26 letters long
    if (argc == 2 && strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    //stops code if the number of terms entered is not 2
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }


    if (argc == 2 && strlen(argv[1]) == 26)
    {
        //checks for non-alpha
        for (int k = 0; k < 26; k++)
        {
            if (!isalpha(argv[1][k]))
            {
                return 1;
            }
        }
        //checks for duplicates
        for (int m = 0; m < 26; m++)
        {
            for (int n = m + 1; n < 26; n++)
            {
                if (argv[1][m] == argv[1][n])
                {
                    return 1;
                }
            }
        }
        //creates ciphered text
        string plain = get_string("plaintext:  ");
        char alphabet [26];
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            alphabet[i] = argv[1][i];
        }
        for (int j = 0; j < strlen(plain); j++)
        {
            //determines which position in the key to use based on the original text
            char check = plain [j];
            if (isalpha(check))
            {
                check = toupper(check);
            }
            check -= 65;
            //gets corresponding letter in the key (case sensitive)
            if (isupper(plain[j]))
            {
                plain[j] = toupper(alphabet [(int)check]);
            }
            else if (islower(plain[j]))
            {
                plain[j] = tolower(alphabet [(int)check]);
            }
        }
        //prints the ciphered text
        printf("ciphertext: %s\n", plain);
        return 0;
    }
}