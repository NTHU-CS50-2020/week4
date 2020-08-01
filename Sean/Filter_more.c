#include "helpers.h"
#include <math.h>

// Convert image to grayscale
// same as less
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

// Reflect image horizontally
// same as less
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
// same as less
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            float tmp_r = 0, tmp_g = 0, tmp_b = 0;
            int count = 0;
            for (int z = i>0 ? (i - 1) : i; z <= i+1 && z <= height-1; z++){
                for (int k = j>0 ? (j - 1) : j; k <= j+1 && k <= width-1; k++){
                    tmp_r += image[z][k].rgbtRed;
                    tmp_g += image[z][k].rgbtGreen;
                    tmp_b += image[z][k].rgbtBlue;
                    count++;
                }
            }
            tmp_r = round(tmp_r/count);
            tmp_g = round(tmp_g/count);
            tmp_b = round(tmp_b/count);
            tmp[i][j].rgbtRed = tmp_r;
            tmp[i][j].rgbtGreen = tmp_g;
            tmp[i][j].rgbtBlue = tmp_b;
        }
    }
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
        }
    }
    return;
}

int sobel (int gx, int gy)
{
    float edge = pow(gx, 2) + pow(gy, 2);
    edge = round(sqrt(edge));
    return edge>=255 ? 255 : edge;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            int gxr = 0, gxg = 0, gxb =0;
            int gyr = 0, gyg = 0, gyb = 0;

            if (i > 0){
                if (j > 0) {
                    gxr += -1*image[i-1][j-1].rgbtRed;
                    gxg += -1*image[i-1][j-1].rgbtGreen;
                    gxb += -1*image[i-1][j-1].rgbtBlue;

                    gyr += -1*image[i-1][j-1].rgbtRed;
                    gyg += -1*image[i-1][j-1].rgbtGreen;
                    gyb += -1*image[i-1][j-1].rgbtBlue;
                }
                
                gyr += -2*image[i-1][j].rgbtRed;
                gyg += -2*image[i-1][j].rgbtGreen;
                gyb += -2*image[i-1][j].rgbtBlue;
                
                if (j+1 < width) {
                    gxr += 1*image[i-1][j+1].rgbtRed;
                    gxg += 1*image[i-1][j+1].rgbtGreen;
                    gxb += 1*image[i-1][j+1].rgbtBlue;

                    gyr += -1*image[i-1][j+1].rgbtRed;
                    gyg += -1*image[i-1][j+1].rgbtGreen;
                    gyb += -1*image[i-1][j+1].rgbtBlue;
                }
            }

            if (j > 0) {
                gxr += -2*image[i][j-1].rgbtRed;
                gxg += -2*image[i][j-1].rgbtGreen;
                gxb += -2*image[i][j-1].rgbtBlue;
            }
            if (j+1 < width) {
                gxr += 2*image[i][j+1].rgbtRed;
                gxg += 2*image[i][j+1].rgbtGreen;
                gxb += 2*image[i][j+1].rgbtBlue;
            }

            if (i+1 < height){
                if (j > 0) {
                    gxr += -1*image[i+1][j-1].rgbtRed;
                    gxg += -1*image[i+1][j-1].rgbtGreen;
                    gxb += -1*image[i+1][j-1].rgbtBlue;
                    
                    gyr += 1*image[i+1][j-1].rgbtRed;
                    gyg += 1*image[i+1][j-1].rgbtGreen;
                    gyb += 1*image[i+1][j-1].rgbtBlue;
                }
                
                gyr += 2*image[i+1][j].rgbtRed;
                gyg += 2*image[i+1][j].rgbtGreen;
                gyb += 2*image[i+1][j].rgbtBlue;
                
                if (j+1 < width) {
                    gxr += 1*image[i+1][j+1].rgbtRed;
                    gxg += 1*image[i+1][j+1].rgbtGreen;
                    gxb += 1*image[i+1][j+1].rgbtBlue;
                    
                    gyr += 1*image[i+1][j+1].rgbtRed;
                    gyg += 1*image[i+1][j+1].rgbtGreen;
                    gyb += 1*image[i+1][j+1].rgbtBlue;
                }
            }

            tmp[i][j].rgbtRed = sobel(gxr, gyr);
            tmp[i][j].rgbtGreen = sobel(gxg, gyg);
            tmp[i][j].rgbtBlue = sobel(gxb, gyb);
        }
    }
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
        }
    }

    return;
}
