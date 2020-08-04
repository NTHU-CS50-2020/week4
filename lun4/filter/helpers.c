#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{//the average of the red, green, and blue values to determine what shade of grey to make the new pixel.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double avg=round((image[i][j].rgbtRed+image[i][j].rgbtGreen+image[i][j].rgbtBlue)/3);
            image[i][j].rgbtRed=avg;
            image[i][j].rgbtGreen=avg;
            image[i][j].rgbtBlue=avg;
            
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
            float originalRed=image[i][j].rgbtRed;
            float originalGreen=image[i][j].rgbtGreen;
            float originalBlue=image[i][j].rgbtBlue;
            
            float sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            float sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            float sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;
            
            sepiaRed=(sepiaRed>=255)? 255:sepiaRed ;
            sepiaRed=(sepiaGreen>=255)? 255:sepiaGreen ;
            sepiaRed=(sepiaBlue>=255)? 255:sepiaBlue ;
            
            image[i][j].rgbtRed=sepiaRed;
            image[i][j].rgbtGreen=sepiaGreen;
            image[i][j].rgbtBlue=sepiaBlue;
            //image[i][j].rgbtRedimage[i][j].rgbtGreenimage[i][j].rgbtBliue
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int e=width/2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < e; j++)
        {
            float t=image[i][j].rgbtRed;
            image[i][j].rgbtRed=image[i][width-i].rgbtRed;
            image[i][width-i].rgbtRed=t;
            
            t=image[i][j].rgbtGreen;
            image[i][j].rgbtGreen=image[i][width-i].rgbtGreen;
            image[i][width-i].rgbtGreen=t;
            
            t=image[i][j].rgbtBlue;
            image[i][j].rgbtBlue=image[i][width-i].rgbtBlue;
            image[i][width-i].rgbtBlue=t;
        }
    }
            
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{// the average of the values of all of the pixels that are within 1 row and column of the original pixel (forming a 3x3 box)
    RGBTRIPLE blur_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float r = 0, g = 0, b = 0,e=0;

            for(int ii = -1; ii<=1; ii++)
            {
                for(int jj = -1; jj<=1; jj++)
                {
                    if(i+ii<height&&i+ii>0&&j+jj<width&&j+jj>0)
                    {
                        r += image[i+ii][j+jj].rgbtRed;
                        g += image[i+ii][j+jj].rgbtGreen;
                        b += image[i+ii][j+jj].rgbtBlue;
                        e++;
                        
                    }
                }
            }
        
            blur_image[i][j].rgbtRed = round(r/e);
            blur_image[i][j].rgbtGreen = round(g/e);
            blur_image[i][j].rgbtBlue = round(b/e);
            
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = blur_image[i][j].rgbtRed;
            image[i][j].rgbtGreen = blur_image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = blur_image[i][j].rgbtBlue;
        }
    }

    return;
}
