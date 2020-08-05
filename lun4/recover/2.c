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
    //有沒有在家
    if (!file) return 2;
    
    //📌digital cameras often initialize cards with a FAT file system whose “block size” is 512 bytes (B). 
    //each block is 512 bytes🧊🧊🧊🧊🧊
    unsigned char buffer[512];//unsigned char 0~255
   
    printf("%lu\n",sizeof(buffer));//512
    printf("%c\n",buffer[1]);//📌我想知道裡面是甚麼，然後為甚麼可以和== 0xd8比較

    int JPEG_has_found = 0;
    int file_count = 0;
    FILE *out = NULL;
    //fread, fwrite - binary stream input/output
    //size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
    //The function fread() reads nmemb items of data, each size bytes long, from the stream pointed to by stream, storing them at the location given by ptr.
    while(fread(buffer, sizeof(buffer), 1, file))
    {
        printf("*\n");
        //&位元(一個0b1110????一個0b11110000比較0b11100000)運算 
        if ((buffer[3] & 0xf0) == 0xe0&&buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff )
        {
            printf("**\n");//📌進不來
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
        // keep writing file and changing the current file name
        if(JPEG_has_found)
        {
            printf("**\n");
            fwrite(buffer, 512, 1, out);
        }
        
        printf("***\n");
        //Close any remaining file    
        fclose(file);
        fclose(out);
        return 0;
        
    }
}
