#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // take the average of all the colors and set it to a specific one

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE p = image[i][j];
            int average = round((float)(p.rgbtRed + p.rgbtGreen + p.rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;


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
            int sepiaR = round((float)(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue));
            if (sepiaR > 255)
            {
                sepiaR = 255;
            }
            if (sepiaR < 0)
            {
                sepiaR = 0;
            }
            int sepiaG = round((float)(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue));
            if (sepiaG > 255)
            {
                sepiaG = 255;
            }
            if (sepiaG < 0)
            {
                sepiaG = 0;
            }
            int sepiaB = round((float)(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue));
            if (sepiaB > 255)
            {
                sepiaB = 255;
            }
            if (sepiaB < 0)
            {
                sepiaB = 0;
            }
            image[i][j].rgbtRed = sepiaR;
            image[i][j].rgbtGreen = sepiaG;
            image[i][j].rgbtBlue = sepiaB;
        }
    }


//   sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
//   sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
//   sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tempPixel = image[i][j]; // store temp
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tempPixel;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary array to store the blurred values
    RGBTRIPLE temp[height][width];

    // Loop over each pixel in the image
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // Initialize the sum and count variables
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            int count = 0;

            // Loop over the 3x3 grid around the pixel
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    // Check if the neighbor pixel is within the image bounds
                    if (row + i >= 0 && row + i < height && col + j >= 0 && col + j < width)
                    {
                        // Add the neighbor pixel's RGB values to the sum
                        sumRed += image[row + i][col + j].rgbtRed;
                        sumGreen += image[row + i][col + j].rgbtGreen;
                        sumBlue += image[row + i][col + j].rgbtBlue;

                        // Count valid pixels proivded a three e by three
                        count++;
                    }
                }
            }

            // Calculate avg
            int avgR = round((float)sumRed / count);
            int avgG = round((float)sumGreen / count);
            int avgB = round((float)sumBlue / count);

            // Assign the average values to the temporary array
            temp[row][col].rgbtRed = avgR;
            temp[row][col].rgbtGreen = avgG;
            temp[row][col].rgbtBlue = avgB;
        }
    }

    // Copy the temporary array to the original image array
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image[row][col] = temp[row][col];
        }
    }

    return;
}
