#include "helpers.h"
#include "math.h"

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    /*
    sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
    sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
    sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
    */
    for(int i = 0; i<height; i++)
    {
        for(int j = 0; j<width; j++)
        {
            float originalRed = image[i][j].rgbtRed;
            float originalGreen = image[i][j].rgbtGreen;
            float originalBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue) >= 255 ? 255 : round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            image[i][j].rgbtGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue) >= 255 ? 255 : round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            image[i][j].rgbtBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue) >= 255 ? 255 :round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);
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
