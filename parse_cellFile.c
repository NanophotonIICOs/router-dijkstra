#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Rectangle {
    float x1, y1, x2, y2;
    int direction;
};

struct Macro {
    char name[50];
    struct Rectangle* rectangles;
    int numRectangles;
    int maxRectangles;
};

void extractRectangles(char* line, struct Macro* macro) {
    float x1, y1, x2, y2;
    sscanf(line, "\t\t\t\tRECT %f %f %f %f", &x1, &y1, &x2, &y2);
    struct Rectangle rect = { x1, y1, x2, y2 };
    macro->rectangles[macro->numRectangles++] = rect;
}

int main() {
    FILE* file = fopen("./amis_cells/amis500cxascb.lef", "r"); // LEF FILE <--------------------
    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    const char* filename = "./amis_cells/cell_rects.txt"; // OUTFILE -------------------->
    FILE* file_cell = fopen(filename, "w");
    if (file_cell == NULL) {
        printf("Error: No se pudo abrir el archivo.\n");
        return 1;
    }

    struct Macro macro;
    int isMacroStarted = 0;
    int isLayerM1Started = 0;
    int isDirectionOutputStarted = 0;
    char name_end[50];

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "MACRO") != NULL) {
            sscanf(line, "MACRO %s", macro.name);
            sprintf(name_end, "END %s", macro.name);
            macro.numRectangles = 0;
            macro.maxRectangles = 10; // Tamaño inicial
            macro.rectangles = malloc(macro.maxRectangles * sizeof(struct Rectangle));
            isMacroStarted = 1;
        } else if (isMacroStarted && strstr(line, "DIRECTION OUTPUT") != NULL) {
            isDirectionOutputStarted = 1;
        } else if (strstr(line, "LAYER M1 ;") != NULL) {
            isLayerM1Started = 1;
        } else if (isMacroStarted && isLayerM1Started && strstr(line, "RECT") != NULL) {
            if (macro.numRectangles == macro.maxRectangles) {
                macro.maxRectangles *= 2; // Duplicar el tamaño actual
                macro.rectangles = realloc(macro.rectangles, macro.maxRectangles * sizeof(struct Rectangle));
            }
            extractRectangles(line, &macro);
            macro.rectangles[macro.numRectangles - 1].direction = isDirectionOutputStarted;
        } else if (isMacroStarted && isLayerM1Started && strstr(line, "END") != NULL) {
            isLayerM1Started = 0;
            isDirectionOutputStarted = 0;
        } else if (isMacroStarted && strstr(line, name_end) != NULL) {
            isMacroStarted = 0;

            printf("MACRO: %s\n", macro.name);
            fprintf(file_cell, "MACRO: %s\n", macro.name);
            for (int i = 0; i < macro.numRectangles; i++) {
                struct Rectangle rect = macro.rectangles[i];
                printf("RECT %d, %d: %.3f, %.3f - %.3f, %.3f\n", i + 1, macro.rectangles[i].direction, rect.x1, rect.y1, rect.x2, rect.y2);
                fprintf(file_cell, "RECT %d, %d: %.3f, %.3f - %.3f, %.3f\n", i + 1, macro.rectangles[i].direction, rect.x1, rect.y1, rect.x2, rect.y2);
            }
            fprintf(file_cell, "END\n");
            printf("\n");
        }
    }

    free(macro.rectangles);

    fclose(file);
    fclose(file_cell);
    return 0;
}
