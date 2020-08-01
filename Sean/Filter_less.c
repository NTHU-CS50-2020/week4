#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            float tmp = 0;
            tmp += image[i][j].rgbtBlue;
            tmp += image[i][j].rgbtGreen;
            tmp += image[i][j].rgbtRed;
            tmp = round(tmp/3);
            image[i][j].rgbtBlue = tmp;
            image[i][j].rgbtGreen = tmp;
            image[i][j].rgbtRed = tmp;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            float r = image[i][j].rgbtRed;
            float g = image[i][j].rgbtGreen;
            float b = image[i][j].rgbtBlue;
            int sr = round(.393 * r + .769 * g + .189 * b);
            int sg = round(.349 * r + .686 * g + .168 * b);
            int sb = round(.272 * r + .534 * g + .131 * b);
            image[i][j].rgbtRed = sr >= 255 ? 255 : sr;
            image[i][j].rgbtGreen = sg >= 255 ? 255 : sg;
            image[i][j].rgbtBlue = sb >= 255 ? 255 : sb;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width/2; j++){
            int tmp_r = image[i][j].rgbtRed;
            int tmp_g = image[i][j].rgbtGreen;
            int tmp_b = image[i][j].rgbtBlue;
            int right = width - j - 1;
            image[i][j].rgbtRed = image[i][right].rgbtRed;
            image[i][j].rgbtGreen = image[i][right].rgbtGreen;
            image[i][j].rgbtBlue = image[i][right].rgbtBlue;
            image[i][right].rgbtRed = tmp_r;
            image[i][right].rgbtGreen = tmp_g;
            image[i][right].rgbtBlue = tmp_b;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            float tmp_r = 0, tmp_g = 0, tmp_b = 0;
            int count = 0;
            for (int z = i>0?(i - 1):i; z <= i+1 && z <= height-1; z++){
                for (int k = j>0?(j - 1):j; k <= j+1 && k <= width-1; k++){
                    tmp_r += image[z][k].rgbtRed;
                    tmp_g += image[z][k].rgbtGreen;
                    tmp_b += image[z][k].rgbtBlue;
                    count++;
                }
            }
            tmp_r = round(tmp_r/count);
            tmp_g = round(tmp_g/count);
            tmp_b = round(tmp_b/count);
            temp[i][j].rgbtRed = tmp_r;
            temp[i][j].rgbtGreen = tmp_g;
            temp[i][j].rgbtBlue = tmp_b;
        }
    }
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}
