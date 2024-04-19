//#include <SDL2/SDL.h>
#include <stdio.h>



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

    char fileName[] = "task.png";

    readFile(fileName);

    return 0;
}
