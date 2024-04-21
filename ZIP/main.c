#include <stdio.h>

int hide_zip_in_png(char *imageName, char *zipName, char *outputName){
    FILE *imageFile, *zipFile, *outputFile;
    char buffer[1024];
    size_t bytesRead;

    imageFile = fopen(imageName,"rb");
    zipFile = fopen(zipName,"rb");

    if(imageFile == NULL || zipFile == NULL){
        printf("Error open file");
        return 1;
    }
    
    outputFile = fopen(outputName,"wb");
    if(outputFile == NULL){
        printf("Output File Error");
        return 1;
    }



    while((bytesRead = fread(buffer, 1, sizeof(buffer), imageFile)) > 0){
        fwrite(buffer, 1, bytesRead, outputFile);
    }
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), zipFile)) > 0) {
        fwrite(buffer, 1, bytesRead, outputFile);
    }



    fclose(outputFile);
    fclose(imageFile);
    fclose(zipFile);

    return 0;
}


int main(){
    char imageName[] = "image.png";
    char zipName[] = "folder.zip";
    char outputName[] = "output.png";

    hide_zip_in_png(imageName, zipName, outputName);
    
    return 0;
}
