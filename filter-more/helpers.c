#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over all x and y values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // d is equal to all rgb values summed and divided by three
            // Then sets all the values of the current pixel to d
            int d = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = d;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;

    // Iterate over all x and y values
    for (int i = 0; i < height; i++)
    {
        // Checks to see if width is divisble by two
        if (width % 2 == 0)
        {
            for (int j = 0; j < width / 2; j++)
            {
                // Mirrors the image
                tmp = image[i][j];
                image[i][j] = image[i][width - (j + 1)];
                image[i][width - (j + 1)] = tmp;
            }
        }
        else
        {
            for (int j = 0; j < (width - 1) / 2; j++)
            {
                // Mirrors the image
                tmp = image[i][j];
                image[i][j] = image[i][width - (j + 1)];
                image[i][width - (j + 1)] = tmp;
            }
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    // Iterate over all x and y values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float r = 0, g = 0, b = 0, a = 0;

            // 3x3 around selected pixel
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k < 0 || i + k > height - 1)
                    {
                        continue;
                    }

                    if (j + l < 0 || j + l > width - 1)
                    {
                        continue;
                    }

                    r += image[i + k][j + l].rgbtRed;
                    g += image[i + k][j + l].rgbtGreen;
                    b += image[i + k][j + l].rgbtBlue;
                    a++;
                }
            }

            temp[i][j].rgbtRed = round(r / a);
            temp[i][j].rgbtGreen = round(g / a);
            temp[i][j].rgbtBlue = round(b / a);
        }
    }

    // Make changes to the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Iterate over all x and y values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxr = 0, gyr = 0;
            int gxg = 0, gyg = 0;
            int gxb = 0, gyb = 0;

            // 3x3 around selected pixel
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k < 0 || i + k > height - 1)
                    {
                        continue;
                    }

                    if (j + l < 0 || j + l > width - 1)
                    {
                        continue;
                    }

                    gxr += image[i + k][j + l].rgbtRed * gx[k + 1][l + 1];
                    gyr += image[i + k][j + l].rgbtRed * gy[k + 1][l + 1];
                    gxg += image[i + k][j + l].rgbtGreen * gx[k + 1][l + 1];
                    gyg += image[i + k][j + l].rgbtGreen * gy[k + 1][l + 1];
                    gxb += image[i + k][j + l].rgbtBlue * gx[k + 1][l + 1];
                    gyb += image[i + k][j + l].rgbtBlue * gy[k + 1][l + 1];
                }
            }

            int r = round(sqrt(gxr * gxr + gyr * gyr));
            int g = round(sqrt(gxg * gxg + gyg * gyg));
            int b = round(sqrt(gxb * gxb + gyb * gyb));

            temp[i][j].rgbtRed = (r > 255) ? 255 : r;
            temp[i][j].rgbtGreen = (g > 255) ? 255 : g;
            temp[i][j].rgbtBlue = (b > 255) ? 255 : b;
        }
    }

    // Make changes to the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }

    return;
}
