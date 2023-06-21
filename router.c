#include <stdio.h>
#include <stdlib.h>
#include "headers/libbmp.h"
#include "headers/libbmp.c"

#define GRID_WIDTH 500
#define GRID_HEIGHT 300
#define GRID_SIZE 20
#define CELL_SIZE 20
#define AVAILABLE_COLOR_R 255
#define AVAILABLE_COLOR_G 255
#define AVAILABLE_COLOR_B 255
#define UNAVAILABLE_COLOR_R 0
#define UNAVAILABLE_COLOR_G 0
#define UNAVAILABLE_COLOR_B 0
#define PATH_COLOR_R 255
#define PATH_COLOR_G 0
#define PATH_COLOR_B 0

void drawGrid(bmp_img *img, const char *gridFilename) {
    FILE *file = fopen(gridFilename, "r");
    if (file == NULL) {
        printf("no se pudo abrir el archivo cuadricula\n");
        return;
    }

    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            int cellStatus;
            fscanf(file, "%d", &cellStatus);

            int startX = j * CELL_SIZE;
            int startY = i * CELL_SIZE;
            int endX = startX + CELL_SIZE;
            int endY = startY + CELL_SIZE;

            for (int x = startX; x < endX; x++) {
                for (int y = startY; y < endY; y++) {
                    if (cellStatus == 1) {
                        bmp_pixel_init(&img->img_pixels[y][x], AVAILABLE_COLOR_R, AVAILABLE_COLOR_G, AVAILABLE_COLOR_B);
                    } else {
                        bmp_pixel_init(&img->img_pixels[y][x], UNAVAILABLE_COLOR_R, UNAVAILABLE_COLOR_G, UNAVAILABLE_COLOR_B);
                    }
                    if (x == startX || x == endX - 1 || y == startY || y == endY - 1) {
                        bmp_pixel_init(&img->img_pixels[y][x], UNAVAILABLE_COLOR_R, UNAVAILABLE_COLOR_G, UNAVAILABLE_COLOR_B);  // Lineas negras entre celdas
                    }
                }
            }
        }
    }

    fclose(file);
}

void saveImage(const char *filename, bmp_img *img) {
    bmp_img_write(img, filename);
    // printf("Imagen guardada: %s\n", filename); //DEBUG
}

void highlightPath(bmp_img *img, const char *pathFilename) {
    FILE *file = fopen(pathFilename, "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    int row, col;
    int imageCount = 1;
    char filename[50];

    while (fscanf(file, "%d, %d", &row, &col) != EOF) {
        int startX = col * CELL_SIZE;
        int startY = row * CELL_SIZE;
        int endX = startX + CELL_SIZE;
        int endY = startY + CELL_SIZE;

        for (int x = startX; x < endX; x++) {
            for (int y = startY; y < endY; y++) {
                bmp_pixel_init(&img->img_pixels[y][x], PATH_COLOR_R, PATH_COLOR_G, PATH_COLOR_B);
            }
        }

        // Guardar imagenes intermedias de path
        // sprintf(filename, "./imagenes/path_%03d.bmp", imageCount++);
        // saveImage(filename, img);
    }

    fclose(file);
}

int main() {
    bmp_img img;
    bmp_img_init_df(&img, GRID_WIDTH * CELL_SIZE, GRID_HEIGHT * CELL_SIZE);

    drawGrid(&img, "./gridCells.txt");
    highlightPath(&img, "./path.txt");

    bmp_img_write(&img, "./cuadricula_final.bmp");
    bmp_img_free(&img);

    return 0;
}
