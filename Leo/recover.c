#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
   if(argc != 2)
    {
        printf("Usage:./recover image\n");
        return 1;
    }
    
    FILE *file_sdcard = fopen(argv[1], "r");
    FILE *img;
    
    unsigned char buffer[512];
    
    int num_jpg = 0;
    int in_jpg = 0;
    
    while(fread(buffer, 512, 1, file_sdcard))
    {
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if(in_jpg == 0)
            {
                char filename[8];
                sprintf(filename, "%03i.jpg", num_jpg);
                img = fopen(filename, "w");
                fwrite(buffer, 512, 1, img);
                num_jpg += 1;
                in_jpg = 1;
            }
            else if(in_jpg == 1)
            {
                fclose(img);
                in_jpg = 0;
                char filename[8];
                sprintf(filename, "%03i.jpg", num_jpg);
                img = fopen(filename, "w");
                fwrite(buffer, 512, 1, img);
                num_jpg += 1;
                in_jpg = 1;
            }
        }
        else
        {
            if(in_jpg == 1)
            {
                fwrite(buffer, 512, 1, img);
            }
        }
    }
    fclose(img);
    fclose(file_sdcard);
}