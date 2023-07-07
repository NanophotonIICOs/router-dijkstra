#include <stdio.h>
#include <stdlib.h>
#include "headers/libbmp.h"
#include "headers/libbmp.c"

// #define GRID_WIDTH 500
// #define GRID_HEIGHT 500
#define GRID_SIZE 5
#define CELL_SIZE 5
#define AVAILABLE_COLOR_R 255
#define AVAILABLE_COLOR_G 255
#define AVAILABLE_COLOR_B 255
#define UNAVAILABLE_COLOR_R 0
#define UNAVAILABLE_COLOR_G 0
#define UNAVAILABLE_COLOR_B 0
#define PATH_COLOR_R 255
#define PATH_COLOR_G 0
#define PATH_COLOR_B 0

void drawGrid(bmp_img *img, const char *gridFilename, int width, int height) {
    FILE *file = fopen(gridFilename, "r");
    if (file == NULL) {
        printf("no se pudo abrir el archivo cuadricula\n");
        return;
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
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

int main(int argc, char **argv) {

    printf("\nRouter-bmp initialized\n");

    if (argc != 3) {
        printf("Uso: ./grid_maker.exe <width> <length>\n");
        return 1;
    }

    int width;
    int height;

    sscanf(argv[1], "%d", &width);
    sscanf(argv[2], "%d", &height);

    printf("width: %d, height: %d\n", width, height);

    bmp_img img;
    bmp_img_init_df(&img, width * CELL_SIZE, height * CELL_SIZE);

    drawGrid(&img, "D:/Desktop/PAR_scripts/router-dijkstra/gridCell.txt", width, height);
    highlightPath(&img, "D:/Desktop/PAR_scripts/router-dijkstra/path.txt");

    bmp_img_write(&img, "D:/Desktop/PAR_scripts/router-dijkstra/cuadricula_final.bmp");
    bmp_img_free(&img);

    return 0;
}
