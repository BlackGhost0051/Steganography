#include <stdio.h>
#include <stdlib.h>
#include <png.h>

void hideInPng(char* fileName, char *hideFileName) {
    int width, height;

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

    printf("Reading pixels:\n");
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            png_byte *ptr = &(row_pointers[y][x * 4]);
            printf("Pixel at (%d, %d): RGBA(%d, %d, %d, %d)\n", x, y, ptr[0], ptr[1], ptr[2], ptr[3]);
        }
    }

    for (int y = 0; y < height; y++) {
        free(row_pointers[y]);
    }
    free(row_pointers);

    return;
}

int main() {
    char inputFile[] = "test1.png";
    char hideFile[] = "test.txt";

    hideInPng(inputFile, hideFile);
    
    return 0;
}
