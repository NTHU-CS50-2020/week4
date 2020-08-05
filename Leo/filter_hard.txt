#include "helpers.h"
#include <math.h>
#include <stdlib.h>


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


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
     RGBTRIPLE edge_image[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int Gx_red = 0, Gx_green = 0, Gx_blue = 0, Gy_red = 0, Gy_green = 0, Gy_blue = 0, edge_red = 0, edge_green = 0, edge_blue = 0;

            if(i - 1 < 0)
            {
               if(j - 1 < 0)
               {
                    Gx_red = image[i][j+1].rgbtRed*(2)+image[i+1][j+1].rgbtRed*(1);
                    Gy_red = image[i+1][j].rgbtRed*(2)+image[i+1][j+1].rgbtRed*(1);
                    edge_red = Gx_red*Gx_red + Gy_red*Gy_red;

                    Gx_green = image[i][j+1].rgbtGreen*(2)+image[i+1][j+1].rgbtGreen*(1);
                    Gy_green = image[i+1][j].rgbtGreen*(2)+image[i+1][j+1].rgbtGreen*(1);
                    edge_green = Gx_green*Gx_green + Gy_green*Gy_green;

                    Gx_blue = image[i][j+1].rgbtBlue*(2)+image[i+1][j+1].rgbtBlue*(1);
                    Gy_blue = image[i+1][j].rgbtBlue*(2)+image[i+1][j+1].rgbtBlue*(1);
                    edge_blue = Gx_red*Gx_blue + Gy_red*Gy_blue;
               }
               else if(j + 1 >= width)
               {
                    Gx_red = image[i][j-1].rgbtRed*(-2)+image[i+1][j-1].rgbtRed*(-1);
                    Gy_red = image[i+1][j-1].rgbtRed*(1)+image[i+1][j].rgbtRed*(2);
                    edge_red = Gx_red*Gx_red + Gy_red*Gy_red;

                    Gx_green = image[i][j-1].rgbtGreen*(-2)+image[i+1][j-1].rgbtGreen*(-1);
                    Gy_green = image[i+1][j-1].rgbtGreen*(1)+image[i+1][j].rgbtGreen*(2);
                    edge_green = Gx_green*Gx_green + Gy_green*Gy_green;

                    Gx_blue = image[i][j-1].rgbtBlue*(-2)+image[i+1][j-1].rgbtBlue*(-1);
                    Gy_blue = image[i+1][j-1].rgbtBlue*(1)+image[i+1][j].rgbtBlue*(2);
                    edge_blue = Gx_red*Gx_blue + Gy_red*Gy_blue;
               }
               else
               {
                    Gx_red = image[i][j-1].rgbtRed*(-2)+image[i+1][j-1].rgbtRed*(-1)+image[i][j+1].rgbtRed*(2)+image[i+1][j+1].rgbtRed*(1);
                    Gy_red = image[i+1][j-1].rgbtRed*(1)+image[i+1][j].rgbtRed*(2)+image[i+1][j+1].rgbtRed*(1);
                    edge_red = Gx_red*Gx_red + Gy_red*Gy_red;

                    Gx_green = image[i][j-1].rgbtGreen*(-2)+image[i+1][j-1].rgbtGreen*(-1)+image[i][j+1].rgbtGreen*(2)+image[i+1][j+1].rgbtGreen*(1);
                    Gy_green = image[i+1][j-1].rgbtGreen*(1)+image[i+1][j].rgbtGreen*(2)+image[i+1][j+1].rgbtGreen*(1);
                    edge_green = Gx_green*Gx_green + Gy_green*Gy_green;

                    Gx_blue = image[i][j-1].rgbtBlue*(-2)+image[i+1][j-1].rgbtBlue*(-1)+image[i][j+1].rgbtBlue*(2)+image[i+1][j+1].rgbtBlue*(1);
                    Gy_blue = image[i+1][j-1].rgbtBlue*(1)+image[i+1][j].rgbtBlue*(2)+image[i+1][j+1].rgbtBlue*(1);
                    edge_blue = Gx_red*Gx_blue + Gy_red*Gy_blue;
               }
            }
            else if(i + 1 >= height)
            {
               if(j - 1 < 0)
               {
                    Gx_red = image[i-1][j+1].rgbtRed*(1)+image[i][j+1].rgbtRed*(2);
                    Gy_red = image[i-1][j].rgbtRed*(-2)+image[i-1][j+1].rgbtRed*(-1);
                    edge_red = Gx_red*Gx_red + Gy_red*Gy_red;

                    Gx_green = image[i-1][j+1].rgbtGreen*(1)+image[i][j+1].rgbtGreen*(2);
                    Gy_green = image[i-1][j].rgbtGreen*(-2)+image[i-1][j+1].rgbtGreen*(-1);
                    edge_green = Gx_green*Gx_green + Gy_green*Gy_green;

                    Gx_blue = image[i-1][j+1].rgbtBlue*(1)+image[i][j+1].rgbtBlue*(2);
                    Gy_blue = image[i-1][j].rgbtBlue*(-2)+image[i-1][j+1].rgbtBlue*(-1);
                    edge_blue = Gx_red*Gx_blue + Gy_red*Gy_blue;
               }
               else if(j + 1 >= width)
               {
                    Gx_red = image[i-1][j-1].rgbtRed*(-1)+image[i][j-1].rgbtRed*(-2);
                    Gy_red = image[i-1][j-1].rgbtRed*(-1)+image[i-1][j].rgbtRed*(-2);
                    edge_red = Gx_red*Gx_red + Gy_red*Gy_red;

                    Gx_green = image[i-1][j-1].rgbtGreen*(-1)+image[i][j-1].rgbtGreen*(-2);
                    Gy_green = image[i-1][j-1].rgbtGreen*(-1)+image[i-1][j].rgbtGreen*(-2);
                    edge_green = Gx_green*Gx_green + Gy_green*Gy_green;

                    Gx_blue = image[i-1][j-1].rgbtBlue*(-1)+image[i][j-1].rgbtBlue*(-2);
                    Gy_blue = image[i-1][j-1].rgbtBlue*(-1)+image[i-1][j].rgbtBlue*(-2);
                    edge_blue = Gx_red*Gx_blue + Gy_red*Gy_blue;
               }
               else
               {
                    Gx_red = image[i-1][j-1].rgbtRed*(-1)+image[i][j-1].rgbtRed*(-2)+image[i-1][j+1].rgbtRed*(1)+image[i][j+1].rgbtRed*(2);
                    Gy_red = image[i-1][j-1].rgbtRed*(-1)+image[i-1][j].rgbtRed*(-2)+image[i-1][j+1].rgbtRed*(-1);
                    edge_red = Gx_red*Gx_red + Gy_red*Gy_red;

                    Gx_green = image[i-1][j-1].rgbtGreen*(-1)+image[i][j-1].rgbtGreen*(-2)+image[i-1][j+1].rgbtGreen*(1)+image[i][j+1].rgbtGreen*(2);
                    Gy_green = image[i-1][j-1].rgbtGreen*(-1)+image[i-1][j].rgbtGreen*(-2)+image[i-1][j+1].rgbtGreen*(-1);
                    edge_green = Gx_green*Gx_green + Gy_green*Gy_green;

                    Gx_blue = image[i-1][j-1].rgbtBlue*(-1)+image[i][j-1].rgbtBlue*(-2)+image[i-1][j+1].rgbtBlue*(1)+image[i][j+1].rgbtBlue*(2);
                    Gy_blue = image[i-1][j-1].rgbtBlue*(-1)+image[i-1][j].rgbtBlue*(-2)+image[i-1][j+1].rgbtBlue*(-1);
                    edge_blue = Gx_red*Gx_blue + Gy_red*Gy_blue;
               }
            }
            else if(j - 1 < 0)
            {
                    Gx_red = image[i-1][j+1].rgbtRed*(1)+image[i][j+1].rgbtRed*(2)+image[i+1][j+1].rgbtRed*(1);
                    Gy_red = image[i-1][j].rgbtRed*(-2)+image[i-1][j+1].rgbtRed*(-1)+image[i+1][j].rgbtRed*(2)+image[i+1][j+1].rgbtRed*(1);
                    edge_red = Gx_red*Gx_red + Gy_red*Gy_red;

                    Gx_green = image[i-1][j+1].rgbtGreen*(1)+image[i][j+1].rgbtGreen*(2)+image[i+1][j+1].rgbtGreen*(1);
                    Gy_green = image[i-1][j].rgbtGreen*(-2)+image[i-1][j+1].rgbtGreen*(-1)+image[i+1][j].rgbtGreen*(2)+image[i+1][j+1].rgbtGreen*(1);
                    edge_green = Gx_green*Gx_green + Gy_green*Gy_green;

                    Gx_blue = image[i-1][j+1].rgbtBlue*(1)+image[i][j+1].rgbtBlue*(2)+image[i+1][j+1].rgbtBlue*(1);
                    Gy_blue = image[i-1][j].rgbtBlue*(-2)+image[i-1][j+1].rgbtBlue*(-1)+image[i+1][j].rgbtBlue*(2)+image[i+1][j+1].rgbtBlue*(1);
                    edge_blue = Gx_red*Gx_blue + Gy_red*Gy_blue;
            }
            else if(j + 1 >= width)
            {
                    Gx_red = image[i-1][j-1].rgbtRed*(-1)+image[i][j-1].rgbtRed*(-2)+image[i+1][j-1].rgbtRed*(-1);
                    Gy_red = image[i-1][j-1].rgbtRed*(-1)+image[i-1][j].rgbtRed*(-2)+image[i+1][j-1].rgbtRed*(1)+image[i+1][j].rgbtRed*(2);
                    edge_red = Gx_red*Gx_red + Gy_red*Gy_red;

                    Gx_green = image[i-1][j-1].rgbtGreen*(-1)+image[i][j-1].rgbtGreen*(-2)+image[i+1][j-1].rgbtGreen*(-1);
                    Gy_green = image[i-1][j-1].rgbtGreen*(-1)+image[i-1][j].rgbtGreen*(-2)+image[i+1][j-1].rgbtGreen*(1)+image[i+1][j].rgbtGreen*(2);
                    edge_green = Gx_green*Gx_green + Gy_green*Gy_green;

                    Gx_blue = image[i-1][j-1].rgbtBlue*(-1)+image[i][j-1].rgbtBlue*(-2)+image[i+1][j-1].rgbtBlue*(-1);
                    Gy_blue = image[i-1][j-1].rgbtBlue*(-1)+image[i-1][j].rgbtBlue*(-2)+image[i+1][j-1].rgbtBlue*(1)+image[i+1][j].rgbtBlue*(2);
                    edge_blue = Gx_red*Gx_blue + Gy_red*Gy_blue;
            }
            else
            {
                Gx_red = image[i-1][j-1].rgbtRed*(-1)+image[i][j-1].rgbtRed*(-2)+image[i+1][j-1].rgbtRed*(-1)+image[i-1][j+1].rgbtRed*(1)+image[i][j+1].rgbtRed*(2)+image[i+1][j+1].rgbtRed*(1);
                Gy_red = image[i-1][j-1].rgbtRed*(-1)+image[i-1][j].rgbtRed*(-2)+image[i-1][j+1].rgbtRed*(-1)+image[i+1][j-1].rgbtRed*(1)+image[i+1][j].rgbtRed*(2)+image[i+1][j+1].rgbtRed*(1);
                edge_red = Gx_red*Gx_red + Gy_red*Gy_red;

                Gx_green = image[i-1][j-1].rgbtGreen*(-1)+image[i][j-1].rgbtGreen*(-2)+image[i+1][j-1].rgbtGreen*(-1)+image[i-1][j+1].rgbtGreen*(1)+image[i][j+1].rgbtGreen*(2)+image[i+1][j+1].rgbtGreen*(1);
                Gy_green = image[i-1][j-1].rgbtGreen*(-1)+image[i-1][j].rgbtGreen*(-2)+image[i-1][j+1].rgbtGreen*(-1)+image[i+1][j-1].rgbtGreen*(1)+image[i+1][j].rgbtGreen*(2)+image[i+1][j+1].rgbtGreen*(1);
                edge_green = Gx_green*Gx_green + Gy_green*Gy_green;

                Gx_blue = image[i-1][j-1].rgbtBlue*(-1)+image[i][j-1].rgbtBlue*(-2)+image[i+1][j-1].rgbtBlue*(-1)+image[i-1][j+1].rgbtBlue*(1)+image[i][j+1].rgbtBlue*(2)+image[i+1][j+1].rgbtBlue*(1);
                Gy_blue = image[i-1][j-1].rgbtBlue*(-1)+image[i-1][j].rgbtBlue*(-2)+image[i-1][j+1].rgbtBlue*(-1)+image[i+1][j-1].rgbtBlue*(1)+image[i+1][j].rgbtBlue*(2)+image[i+1][j+1].rgbtBlue*(1);
                edge_blue = Gx_red*Gx_blue + Gy_red*Gy_blue;
            }

            edge_red = round(sqrt(abs(edge_red)));
            edge_green = round(sqrt(abs(edge_green)));
            edge_blue = round(sqrt(abs(edge_blue)));

            if(edge_red > 255)
            edge_red = 255;
            if(edge_green > 255)
            edge_green = 255;
            if(edge_blue > 255)
            edge_blue = 255;

            edge_image[i][j].rgbtRed = edge_red;
            edge_image[i][j].rgbtGreen = edge_green;
            edge_image[i][j].rgbtBlue = edge_blue;
        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = edge_image[i][j].rgbtRed;
            image[i][j].rgbtGreen = edge_image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = edge_image[i][j].rgbtBlue;
        }
    }
    return;
}
