#include <stdio.h>

typedef struct {
    int row;
    int col;
    double value;
} element;

int main() {

    FILE *matrix_a, *matrix_b, *accumulated;
    matrix_a = fopen("util/matrix_a.dat", "rb");
    matrix_b = fopen("util/matrix_b.dat", "rb");

    accumulated = fopen("util/accumulated.dat", "wb");

    if (matrix_a == NULL || matrix_b == NULL || accumulated == NULL) {
        fprintf(stderr, "error: couldn't open files.\n");
        return 1;
    }

    int ai, aj, bi, bj;
    fread(&ai, sizeof(int), 1, matrix_a);
    fread(&aj, sizeof(int), 1, matrix_a);
    fread(&bi, sizeof(int), 1, matrix_b);
    fread(&bj, sizeof(int), 1, matrix_b);

    fseek(matrix_a, 8, SEEK_SET);

    element a, b;
    while (fread(&a, sizeof(element), 1, matrix_a) == 1) {
        fseek(matrix_b, 8, SEEK_SET);
        
        while (fread(&b, sizeof(element), 1, matrix_b) == 1) {

            if (b.row == a.col) {
                element res;
                res.row = a.row;
                res.col = b.col;
                res.value = a.value * b.value;

                fwrite(&res, sizeof(element), 1, accumulated);
            }   
        }
    }

    fclose(matrix_a);
    fclose(matrix_b);
    fclose(accumulated);

    return 0;
}