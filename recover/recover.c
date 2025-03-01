#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //open file
    //  r stands for read mode
    // FILE *f = fopen(filename, "r");
    if (argc != 2)
    {
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        return 1;
    }

    //initialize variables
    BYTE bytes[512];

    int i = 0;
    // 8 beacuse
    char filename[8];
    // a pointer to the file that will be written to
    FILE *img_pointer = NULL;
    // loop until the end of the file
    while (fread(&bytes, 512, 1, file) != 0)
    {
        //check first 3 bytes
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && ((bytes[3] & 0xf0) == 0xe0))
        {
            //  buffer aritmatic! 0xe...
            // close prev JPEG if not the first
            if (i != 0)
            {
                fclose(img_pointer);
            }

            //  make new JPEG
            // doesnt print to terminal, but rather to a string
            // first paramenter --> name of string you want to write t
            // second parameter --> format string (i = integer)
            // third paramenter --> number you want to substitute
            sprintf(filename, "%03i.jpg", i);
            // writing
            img_pointer = fopen(filename, "w");
            i++;
            // fread returns the number of items of size (2nd parameter) that were read
        }

        // if JPEG found, write
        if (i != 0)
        {
            fwrite(&bytes, 512, 1, img_pointer);
        }
    }
    //  close files
    fclose(file);
    fclose(img_pointer);
    return 0;
}