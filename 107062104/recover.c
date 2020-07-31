#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (!file)
    {
        printf("?_?\n");
        return 1;
    }

    /*
    //count blocks
    fseek(file, 0, SEEK_END);
    long fileLen = ftell(file);
    rewind(file);
    printf("file length : %ld\n", fileLen/512);
    */

    unsigned char buffer[512];
    int JPEG_has_found = 0;
    int file_count = 0;
    FILE *out = NULL;

    while(fread(buffer, 512, 1, file))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
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
        }

        if(JPEG_has_found)
        {
            fwrite(buffer, 512, 1, out);
        }
    }

    fclose(file);
    fclose(out);

    return 0;
}
