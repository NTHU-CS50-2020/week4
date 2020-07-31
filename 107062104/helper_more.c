#include "helpers.h"
#include "math.h"
#include "stdlib.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i<height; i++)
    {
        for(int j = 0; j<width; j++)
        {
            float total = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            int avg = round(total/3);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int halfWidth = width/2;
    RGBTRIPLE tmp[halfWidth];
    //printf("%d %d\n", width, halfWidth);
    for(int i = 0; i<height; i++)
    {
        for(int j = 0; j<halfWidth; j++)
        {
            tmp[j].rgbtRed = image[i][j].rgbtRed;
            tmp[j].rgbtGreen = image[i][j].rgbtGreen;
            tmp[j].rgbtBlue = image[i][j].rgbtBlue;
        }
        if(width%2 == 1)
        {
            for(int j = halfWidth + 1; j<width; j++)
            {
                image[i][2*halfWidth - j].rgbtRed = image[i][j].rgbtRed;
                image[i][2*halfWidth - j].rgbtGreen = image[i][j].rgbtGreen;
                image[i][2*halfWidth - j].rgbtBlue = image[i][j].rgbtBlue;
                image[i][j].rgbtRed = tmp[2*halfWidth - j].rgbtRed;
                image[i][j].rgbtGreen = tmp[2*halfWidth - j].rgbtGreen;
                image[i][j].rgbtBlue = tmp[2*halfWidth - j].rgbtBlue;
            }
        }
        else
        {
            for(int j = halfWidth; j<width; j++)
            {
                image[i][2*halfWidth - j - 1].rgbtRed = image[i][j].rgbtRed;
                image[i][2*halfWidth - j - 1].rgbtGreen = image[i][j].rgbtGreen;
                image[i][2*halfWidth - j - 1].rgbtBlue = image[i][j].rgbtBlue;
                image[i][j].rgbtRed = tmp[2*halfWidth - j - 1].rgbtRed;
                image[i][j].rgbtGreen = tmp[2*halfWidth - j - 1].rgbtGreen;
                image[i][j].rgbtBlue = tmp[2*halfWidth - j - 1].rgbtBlue;
            }

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blur[height][width];
    for(int i = 0; i<height; i++)
    {
        for(int j = 0; j<width; j++)
        {
            int count = 0;
            float tmpRed = 0;
            float tmpGreen = 0;
            float tmpBlue = 0;
            for(int k = -1; k<2; k++)
            {
                for(int l = -1; l<2; l++)
                {
                    if(i+k>=0 && i+k<height && j+l>=0 && j+l<width)
                    {
                        count++;
                        tmpRed += image[i+k][j+l].rgbtRed;
                        tmpGreen += image[i+k][j+l].rgbtGreen;
                        tmpBlue += image[i+k][j+l].rgbtBlue;
                    }
                }
            }
            blur[i][j].rgbtRed = round(tmpRed/count);
            blur[i][j].rgbtGreen =  round(tmpGreen/count);
            blur[i][j].rgbtBlue =  round(tmpBlue/count);
        }
    }
    for(int i = 0; i<height; i++)
    {
        for(int j = 0; j<width; j++)
        {
            image[i][j] = blur[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE g[height][width];
    for(int i = 0; i<height; i++)
    {
        for(int j = 0; j<width; j++)
        {
            float gxRed = 0;
            float gxGreen = 0;
            float gxBlue = 0;
            float gyRed = 0;
            float gyGreen = 0;
            float gyBlue = 0;
            for(int k = -1; k<2; k++)
            {
                for(int l = -1; l<2; l++)
                {
                    if(i+k>=0 && i+k<height && j+l>=0 && j+l<width)
                    {
                        gxRed += image[i+k][j+l].rgbtRed * (l * (2 - (abs(k))));
                        gxGreen += image[i+k][j+l].rgbtGreen * (l * (2 - (abs(k))));
                        gxBlue += image[i+k][j+l].rgbtBlue * (l * (2 - (abs(k))));
                        gyRed += image[i+k][j+l].rgbtRed * (k * (2 - (abs(l))));
                        gyGreen += image[i+k][j+l].rgbtGreen * (k * (2 - (abs(l))));
                        gyBlue += image[i+k][j+l].rgbtBlue * (k * (2 - (abs(l))));
                        //printf("[%d][%d] =\ngxRed : %f\ngxGreen : %f\ngxBlue : %f\ngyRed : %f\ngyGreen : %f\ngyBlue : %f\n", i+k, j+l, gxRed, gxGreen, gxBlue, gyRed, gyGreen, gyBlue);
                    }
                }
            }
            g[i][j].rgbtRed = (round(sqrt(gxRed*gxRed + gyRed*gyRed)) >= 255 ) ? 255 : round(sqrt(gxRed*gxRed + gyRed*gyRed));
            g[i][j].rgbtGreen =  (round(sqrt(gxGreen*gxGreen + gyGreen*gyGreen)) >= 255 ) ? 255 : round(sqrt(gxGreen*gxGreen + gyGreen*gyGreen));
            g[i][j].rgbtBlue =  (round(sqrt(gxBlue*gxBlue + gyBlue*gyBlue)) >= 255 ) ? 255 : round(sqrt(gxBlue*gxBlue + gyBlue*gyBlue));
        }
    }
    for(int i = 0; i<height; i++)
    {
        for(int j = 0; j<width; j++)
        {
            image[i][j] = g[i][j];
        }
    }
    return;
}
