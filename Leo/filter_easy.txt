#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int average = 0, red_value = 0, green_value = 0, blue_value = 0;
            red_value += image[i][j].rgbtRed;
            green_value += image[i][j].rgbtGreen;
            blue_value += image[i][j].rgbtBlue;
            average = (red_value + green_value + blue_value)/3;
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
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
           int sepia_red = 0, sepia_green = 0, sepia_blue = 0; 
           sepia_red = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
           if(sepia_red > 255)
           sepia_red = 255;
           sepia_green = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
           if(sepia_green > 255)
           sepia_green = 255;
           sepia_blue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
           if(sepia_blue > 255)
           sepia_blue = 255;
           image[i][j].rgbtRed = sepia_red;
           image[i][j].rgbtGreen = sepia_green;
           image[i][j].rgbtBlue = sepia_blue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        if(width % 2 == 0)
        {
            for(int j = 0; j < width/2; j++)
            {
               int intial_red = 0, intial_green = 0, intial_blue = 0;
               intial_red = image[i][j].rgbtRed;
               intial_green = image[i][j].rgbtGreen;
               intial_blue = image[i][j].rgbtBlue;
               image[i][j].rgbtRed = image[i][width- 1 - j].rgbtRed;
               image[i][j].rgbtGreen = image[i][width- 1 - j].rgbtGreen;
               image[i][j].rgbtBlue = image[i][width- 1 - j].rgbtBlue;
               image[i][width- 1 - j].rgbtRed = intial_red;
               image[i][width- 1 - j].rgbtGreen = intial_green;
               image[i][width- 1 - j].rgbtBlue = intial_blue;
            }
        }
        else
        {
            for(int j = 0; j < (width - 1)/2; j++)
            {
               int intial_red = 0, intial_green = 0, intial_blue = 0;
               intial_red = image[i][j].rgbtRed;
               intial_green = image[i][j].rgbtGreen;
               intial_blue = image[i][j].rgbtBlue;
               image[i][j].rgbtRed = image[i][width- 1 - j].rgbtRed;
               image[i][j].rgbtGreen = image[i][width- 1 - j].rgbtGreen;
               image[i][j].rgbtBlue = image[i][width- 1 - j].rgbtBlue;
               image[i][width- 1 - j].rgbtRed = intial_red;
               image[i][width- 1 - j].rgbtGreen = intial_green;
               image[i][width- 1 - j].rgbtBlue = intial_blue;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blur_image[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int num = 0;
            float blur_red = 0, blur_green = 0, blur_blue = 0;
            for(int k = i - 1; k <= i + 1; k++)
            {
                    for(int p = j - 1; p <= j + 1; p++)
                    {
                        if(0 <= p && p < width && 0 <= k && k < height)
                        {
                            blur_red += image[k][p].rgbtRed;
                            blur_green += image[k][p].rgbtGreen;
                            blur_blue += image[k][p].rgbtBlue;
                            num = num + 1;
                        }
                   
                    }
            }
            blur_red = round(blur_red/num);
            blur_green = round(blur_green/num);
            blur_blue = round(blur_blue/num);
            blur_image[i][j].rgbtRed = blur_red;
            blur_image[i][j].rgbtGreen = blur_green;
            blur_image[i][j].rgbtBlue = blur_blue;
        }
    }
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = blur_image[i][j].rgbtRed;
            image[i][j].rgbtGreen = blur_image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = blur_image[i][j].rgbtBlue;
        }
    }
    return;
}
