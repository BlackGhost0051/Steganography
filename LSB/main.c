#include <stdio.h>
#include <stdlib.h>
#include <png.h>

void hideInPng(char* fileName, char *hideFileName){
    int byte, i;
    unsigned char IDATStructure[] = {0x49, 0x44, 0x41, 0x54}; // IDAT 49 44 41 54
    unsigned char IHDRStructure[] = {0x49, 0x48, 0x44, 0x52}; // IHDR 49 48 44 52
    int j = 0, k = 0;
    int idatIndex =  -1;
    int ihdrIndex = -1;

    FILE* file = fopen(fileName,"rb");
    if(file == NULL){
        return;
    }
    

    while((byte = fgetc(file)) != EOF){
        if(idatIndex == -1){
            if((unsigned char)byte == IDATStructure[j]){
                j++;
                if(j == sizeof(IDATStructure)){
                    idatIndex = ftell(file);            // IDAT -> T byte
                    printf("\nIDAT = %d\n", idatIndex);
                }
            } else {
                j = 0;
            }
        }


        if(ihdrIndex == -1){
            if((unsigned char)byte == IHDRStructure[k]){
                k++;
                if(k == sizeof(IHDRStructure)){
                    ihdrIndex = ftell(file);            // IHDR -> R byte
                    printf("\nIHDR = %d\n", ihdrIndex);
                    for(i = 0; i < 8; i++){
                        int nextByte = fgetc(file);
                        printf("%d ", nextByte);
                    }
                }
            } else {
                k = 0;
            }
        }
    }





    fclose(file);
    return;
}

void checkStructure(char* fileName, char *hideFileName){
    int byte, i;
    unsigned char fileStructure[8];
    unsigned char pngStructure[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    unsigned char gifStructure[] = {0x47, 0x49, 0x46, 0x38, 0x39, 0x61};
    unsigned char bmpStructure[] = {0x42, 0x4D};

    FILE* file = fopen(fileName, "rb");
    if(file == NULL){
        printf("Error: File not found");
        return;
    }


    for (i = 0; i < 8; i++) {
        byte = fgetc(file);
        if (byte == EOF) {
            printf("Error: File End\n");
            fclose(file);
            return;
        }
        fileStructure[i] = (unsigned char)byte;
    }


    fclose(file);

    // Check PNG structure
    int isPNG = 1;
    for (i = 0; i < 8; i++) {
        if (fileStructure[i] != pngStructure[i]) {
            isPNG = 0;
            break;
        }
    }

    // Check GIF structure
    int isGIF = 1;
    for (i = 0; i < 6; i++) {
        if (fileStructure[i] != gifStructure[i]) {
            isGIF = 0;
            break;
        }
    }

    // Check BMP structure
    int isBMP = 1;
    for (i = 0; i < 2; i++) {
        if (fileStructure[i] != bmpStructure[i]) {
            isBMP = 0;
            break;
        }
    }


    if(isPNG){
        printf("%s = PNG\n", fileName);
        hideInPng(fileName, hideFileName);
    } else if (isGIF) {
        printf("%s = GIF\n", fileName);
    } else if (isBMP) {
        printf("%s = BMP\n", fileName);
    } else {
        printf("%s Structure not found\n", fileName);
    }

    return;
}

void readFile(char* fileName){

    FILE* file = fopen(fileName, "rb");

    if(file == NULL){
        printf("Error open %s!\n", fileName);
        return;
    }

    int byte;
    int i = 0;
    while((byte = fgetc(file)) != EOF){

//        printf("%02x\t", byte);

        for (int i = 7; i >= 0; i--) {
            printf("%d", (byte >> i) & 1);
        }
        printf("\t");

        if(i %  12 == 0){
            printf("\n");
        }
        
        i++;
   
        
    }

    fclose(file);

    return;
}



int main(){

    char filePng[] = "test1.png";

    char hideFile[] = "test.txt";

    checkStructure(filePng, hideFile);
    return 0;
}
