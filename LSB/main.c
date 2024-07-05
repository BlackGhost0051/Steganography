#include <stdio.h>
#include <stdlib.h>
#include <png.h>

#define OUTPUT_FILE_NAME_HIDE_IN_PNG "output.png"


#define INPUT_FILE_NAME "output.png"
#define OUTPUT_FILE_NAME "hidden_data.txt"


void hideInPng(char* fileName, char *hideFileName) {
    int width, height;
    int data_size = 0;
    unsigned char *data_buffer = NULL;
    int data_index = 0;

    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        printf("Failed to open the file %s.\n", fileName);
        return;
    }

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png == NULL) {
        fclose(file);
        printf("png_create_read_struct failed\n");
        return;
    }

    png_infop info = png_create_info_struct(png);
    if (info == NULL) {
        png_destroy_read_struct(&png, NULL, NULL);
        fclose(file);
        printf("png_create_info_struct failed\n");
        return;
    }

    if (setjmp(png_jmpbuf(png))) {
        png_destroy_read_struct(&png, &info, NULL);
        fclose(file);
        printf("Error during init_io\n");
        return;
    }

    png_init_io(png, file);
    png_read_info(png, info);

    width = png_get_image_width(png, info);
    height = png_get_image_height(png, info);

    printf("Width: %d, Height: %d\n", width, height);

    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth = png_get_bit_depth(png, info);

    if (bit_depth == 16) {
        png_set_strip_16(png);
    }
    if (color_type == PNG_COLOR_TYPE_PALETTE) {
        png_set_palette_to_rgb(png);
    }
    if (png_get_valid(png, info, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(png);
    }

    png_read_update_info(png, info);

    png_bytep *row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png, info));
    }

    png_read_image(png, row_pointers);

    fclose(file);
    png_destroy_read_struct(&png, &info, NULL);

    FILE *hideFile = fopen(hideFileName, "rb");
    if (hideFile == NULL) {
        printf("Failed to open the hide file %s.\n", hideFileName);
        for (int y = 0; y < height; y++) {
            free(row_pointers[y]);
        }
        free(row_pointers);
        return;
    }

    fseek(hideFile, 0, SEEK_END);
    data_size = ftell(hideFile);
    rewind(hideFile);

    data_buffer = (unsigned char *) malloc(data_size);
    if (data_buffer == NULL) {
        printf("Memory allocation error\n");
        fclose(hideFile);
        for (int y = 0; y < height; y++) {
            free(row_pointers[y]);
        }
        free(row_pointers);
        return;
    }

    fread(data_buffer, 1, data_size, hideFile);
    fclose(hideFile);

    for (int y = 0; y < height; y++) {
        png_bytep row = row_pointers[y];
        for (int x = 0; x < width; x++) {
            png_byte *ptr = &(row[x * 4]);
            if (data_index < data_size * 8) { 
                for (int i = 0; i < 3; i++) {
                    if (data_index < data_size * 8) {
                        ptr[i] &= 0xFE;
                        ptr[i] |= (data_buffer[data_index / 8] >> (7 - (data_index % 8))) & 1;
                        data_index++;
                    }
                }
            }
        }
    }

    FILE *outputFile = fopen(OUTPUT_FILE_NAME_HIDE_IN_PNG, "wb");
    if (outputFile == NULL) {
        printf("Failed to open output file %s\n", OUTPUT_FILE_NAME_HIDE_IN_PNG);
        for (int y = 0; y < height; y++) {
            free(row_pointers[y]);
        }
        free(row_pointers);
        free(data_buffer);
        return;
    }

    png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        fclose(outputFile);
        printf("png_create_write_struct failed\n");
        for (int y = 0; y < height; y++) {
            free(row_pointers[y]);
        }
        free(row_pointers);
        free(data_buffer);
        return;
    }

    info = png_create_info_struct(png);
    if (!info) {
        png_destroy_write_struct(&png, NULL);
        fclose(outputFile);
        printf("png_create_info_struct failed\n");
        for (int y = 0; y < height; y++) {
            free(row_pointers[y]);
        }
        free(row_pointers);
        free(data_buffer);
        return;
    }

    if (setjmp(png_jmpbuf(png))) {
        png_destroy_write_struct(&png, &info);
        fclose(outputFile);
        printf("Error during init_io\n");
        for (int y = 0; y < height; y++) {
            free(row_pointers[y]);
        }
        free(row_pointers);
        free(data_buffer);
        return;
    }

    png_init_io(png, outputFile);
    png_set_IHDR(png, info, width, height, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);

    png_write_image(png, row_pointers);
    png_write_end(png, NULL);

    fclose(outputFile);
    png_destroy_write_struct(&png, &info);

    for (int y = 0; y < height; y++) {
        free(row_pointers[y]);
    }
    free(row_pointers);
    free(data_buffer);

    printf("Data successfully hidden in %s\n", OUTPUT_FILE_NAME_HIDE_IN_PNG);

    return;
}


void extractFromPng(char* fileName) {
    int width, height;
    int data_index = 0;
    int data_size = 0;
    unsigned char *data_buffer = NULL;

    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        printf("Failed to open the file %s.\n", fileName);
        return;
    }

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png == NULL) {
        fclose(file);
        printf("png_create_read_struct failed\n");
        return;
    }

    png_infop info = png_create_info_struct(png);
    if (info == NULL) {
        png_destroy_read_struct(&png, NULL, NULL);
        fclose(file);
        printf("png_create_info_struct failed\n");
        return;
    }

    if (setjmp(png_jmpbuf(png))) {
        png_destroy_read_struct(&png, &info, NULL);
        fclose(file);
        printf("Error during init_io\n");
        return;
    }

    png_init_io(png, file);
    png_read_info(png, info);

    width = png_get_image_width(png, info);
    height = png_get_image_height(png, info);

    printf("Width: %d, Height: %d\n", width, height);

    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth = png_get_bit_depth(png, info);

    if (bit_depth == 16) {
        png_set_strip_16(png);
    }
    if (color_type == PNG_COLOR_TYPE_PALETTE) {
        png_set_palette_to_rgb(png);
    }
    if (png_get_valid(png, info, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(png);
    }

    png_read_update_info(png, info);

    png_bytep *row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png, info));
    }

    png_read_image(png, row_pointers);

    fclose(file);
    png_destroy_read_struct(&png, &info, NULL);

    data_buffer = (unsigned char *) malloc(width * height * 3 / 8);

    for (int y = 0; y < height; y++) {
        png_bytep row = row_pointers[y];
        for (int x = 0; x < width; x++) {
            png_byte *ptr = &(row[x * 4]);
            for (int i = 0; i < 3; i++) {
                if (data_index < width * height * 3 / 8) {
                    data_buffer[data_index / 8] |= (ptr[i] & 1) << (7 - (data_index % 8));
                    data_index++;
                }
            }
        }
    }

    data_size = data_index / 8;

    FILE *outputFile = fopen(OUTPUT_FILE_NAME, "wb");
    if (outputFile == NULL) {
        printf("Failed to open output file %s\n", OUTPUT_FILE_NAME);
        for (int y = 0; y < height; y++) {
            free(row_pointers[y]);
        }
        free(row_pointers);
        free(data_buffer);
        return;
    }

    fwrite(data_buffer, 1, data_size, outputFile);

    fclose(outputFile);
    for (int y = 0; y < height; y++) {
        free(row_pointers[y]);
    }
    free(row_pointers);
    free(data_buffer);

    printf("Data successfully extracted and saved to %s\n", OUTPUT_FILE_NAME);

    return;
}


int main() {
    char inputFile[] = "test1.png";
    char hideFile[] = "test.txt";



    //hideInPng(inputFile, hideFile);
    //extractFromPng(INPUT_FILE_NAME);

    return 0;
}
