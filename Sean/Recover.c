#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2) return 1;
    
    FILE *file = fopen(argv[1], "r");
    if (!file) return 1;
    
    FILE *img;
    BYTE buffer[512];
    int num = 0;
    //bool
    int jpg = 0;
    
    while(fread(buffer, sizeof(buffer), 1, file)){
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0){
            if (jpg) {
                fclose(img);
                jpg = 0;
            }
            char filename[8];
            sprintf(filename, "%03i.jpg", num);
            img = fopen(filename, "w");
            fwrite(buffer, sizeof(buffer), 1, img);
            jpg = 1;
            num++;
        }
        else{
            if (jpg){
                fwrite(buffer, sizeof(buffer), 1, img);
            }
        }
    }
    fclose(img);
    fclose(file);
}
