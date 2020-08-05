#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
   
    FILE *file = fopen(argv[1], "r");
    if (!file) return 2;
    
    unsigned char buffer[512];//unsigned char 0~255

    int JPEG_has_found = 0;
    int file_count = 0;
    FILE *out = NULL;
    while(fread(buffer, sizeof(buffer), 1, file))
    {
        if ((buffer[3] & 0xf0) == 0xe0&&buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff )
        {
            if(JPEG_has_found)
            {
                fclose(out);
            }
            else
            {
                JPEG_has_found = 1;
            }

            char filename[10];
            sprintf(filename, "%03d.jpg", file_count++);
            out = fopen(filename, "a+");
        }//If already found JPEG 
        if(JPEG_has_found)
        {
            fwrite(buffer, 512, 1, out);
        }
        
        fclose(file);
        fclose(out);
        return 0;
        
    }
}
