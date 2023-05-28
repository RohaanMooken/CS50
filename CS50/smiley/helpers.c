#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing

    // Iterate over all pixels in the y axis/height
    for (int i = 0; i < height; i++)
    {
        // Iterate over all pixels in the x axis/width
        for (int j = 0; j < width; j++)
        {
            // Check if current pixel is black
            if (image[i][j].rgbtRed == 0 && image[i][j].rgbtGreen == 0 && image[i][j].rgbtBlue == 0)
            {
                // Change color of current pixel to red
                image[i][j].rgbtRed = 255;
                image[i][j].rgbtGreen = 0;
                image[i][j].rgbtBlue = 0;
            }
        }
    }
}
