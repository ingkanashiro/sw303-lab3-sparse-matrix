#include <stdio.h>

typedef struct {
    int row;
    int col;
    double value;
} element;

int convert(char *path, char *dest) {
    FILE *origin, *output;
    origin = fopen(path, "r");
    output = fopen(dest, "wb");

    if (origin == NULL || output == NULL) {
        fprintf(stderr, "error: couldn't open files.\n");
        return 0;
    }

    int rows, cols;
    fscanf(origin, "%d %d", &rows, &cols);

    fwrite(&rows, sizeof(int), 1, output);
    fwrite(&cols, sizeof(int), 1, output);

    int i, j; double val;
    while (fscanf(origin, "%d %d %lf", &i, &j, &val) != EOF) {

        element e;
        e.row = i;
        e.col = j;
        e.value = val;

        fwrite(&e, sizeof(e), 1, output);
    }

    return 1;
}

int main() {

    convert("util/matrix_a.txt", "util/matrix_a.dat");
    convert("util/matrix_b.txt", "util/matrix_b.dat");

    return 0;
}