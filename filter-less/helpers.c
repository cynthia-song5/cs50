#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //determine average and apply average for all values
            float avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.00;
            avg = round(avg);
            image[i][j].rgbtBlue = (int)avg;
            image[i][j].rgbtGreen = (int)avg;
            image[i][j].rgbtRed = (int)avg;

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //calculate sepia values
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            //exceptions if the sepia value exceeds the maximum
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            //apply filter
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
//swap oppositie things
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //use an array bc it is better design since there are 3 v similar variables of the same data type!
    int temp [3];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp [0] = image[i][j].rgbtRed;
            temp [1] = image[i][j].rgbtGreen;
            temp [2] = image[i][j].rgbtBlue;
            //swap pt 1
            image[i][j].rgbtRed = image[i][width - (j + 1)].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - (j + 1)].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - (j + 1)].rgbtBlue;
            //swap pt 2
            image[i][width - (j + 1)].rgbtRed = temp [0];
            image[i][width - (j + 1)].rgbtGreen = temp [1];
            image[i][width - (j + 1)].rgbtBlue = temp [2];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //make a copy of the ORIGINAL image!
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            float avgRed = 0.0;
            float avgGreen = 0.0;
            float avgBlue = 0.0;
            int squares = 1;
            //actual pixel

            avgRed += temp[i][j].rgbtRed;
            avgGreen += temp[i][j].rgbtGreen;
            avgBlue += temp[i][j].rgbtBlue;
            //every possile scenario thyme!

            //edges
            if (j < width - 1)
            {
                squares++;
                avgRed += temp[i][j + 1].rgbtRed;
                avgGreen += temp[i][j + 1].rgbtGreen;
                avgBlue += temp[i][j + 1].rgbtBlue;
            }
            if (j > 0)
            {
                squares++;
                avgRed += temp[i][j - 1].rgbtRed;
                avgGreen += temp[i][j - 1].rgbtGreen;
                avgBlue += temp[i][j - 1].rgbtBlue;
            }
            if (i < height - 1)
            {
                squares++;
                avgRed += temp[i + 1][j].rgbtRed;
                avgGreen += temp[i + 1][j].rgbtGreen;
                avgBlue += temp[i + 1][j].rgbtBlue;
            }

            if (i > 0)
            {
                squares++;
                avgRed += temp[i - 1][j].rgbtRed;
                avgGreen += temp[i - 1][j].rgbtGreen;
                avgBlue += temp[i - 1][j].rgbtBlue;
            }

            //corners
            if (i > 0 && j > 0)
            {
                squares++;
                avgRed += temp[i - 1][j - 1].rgbtRed;
                avgGreen += temp[i - 1][j - 1].rgbtGreen;
                avgBlue += temp[i - 1][j - 1].rgbtBlue;
            }
            if (i < height - 1 && j < width - 1)
            {
                squares++;
                avgRed += temp[i + 1][j + 1].rgbtRed;
                avgGreen += temp[i + 1][j + 1].rgbtGreen;
                avgBlue += temp[i + 1][j + 1].rgbtBlue;
            }
            if (i > 0 && j < width - 1)
            {
                squares++;
                avgRed += temp[i - 1][j + 1].rgbtRed;
                avgGreen += temp[i - 1][j + 1].rgbtGreen;
                avgBlue += temp[i - 1][j + 1].rgbtBlue;
            }
            if (i < height - 1 && j > 0)
            {
                squares++;
                avgRed += temp[i + 1][j - 1].rgbtRed;
                avgGreen += temp[i + 1][j - 1].rgbtGreen;
                avgBlue += temp[i + 1][j - 1].rgbtBlue;
            }
            //modify the actual image!
            image[i][j].rgbtRed = round(avgRed / (float)squares);
            image[i][j].rgbtGreen = round(avgGreen / (float)squares);
            image[i][j].rgbtBlue = round(avgBlue / (float)squares);
        }
    }
    return;
}
