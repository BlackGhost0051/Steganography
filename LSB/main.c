#include <stdio.h>



void readFile(char* fileName){

    FILE* file = fopen(fileName, "rb");

    if(file == NULL){
        printf("Error open %s!\n", fileName);
        return;
    }

    int byte;
    while((byte = fgetc(file)) != EOF){
        
        printf("%02x\n", byte);
        /*
        for (int i = 7; i >= 0; i--) {
            printf("%d", (byte >> i) & 1);
        }
        printf("\n");
        */
    }

    fclose(file);

    return;
}



int main(){

    char fileName[] = "image.bmp";

    readFile(fileName);

    return 0;
}
