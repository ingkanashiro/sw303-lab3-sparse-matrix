#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int fill(char *path, int m, int n) {
    FILE *file;
    file = fopen(path, "w");

    if (file == NULL) {
        printf("error: couldn't generate matrix.\n");
        return 0;
    }

    fprintf(file, "%d %d\n", m, n);

    int len = (int)(0.05 * (m * n));
    for (int k = 0; k < len; k++) {
        int i, j, num, den;
        i = rand() % m;
        j = rand() % n;

        num = rand() % 256;
        den = (rand() % 255) + 1;

        double val = (float)num / den;

        fprintf(file, "%d %d %lf\n", i, j, val);
    }

    fclose(file);
    return 1;
}


int main() {
    srand(time(NULL));

    int m, n, p;
    scanf("%d %d %d", &m, &n, &p);

    if (m > 1000 || n > 1000 || p > 1000) {
        fprintf(stderr, "error: invalid data.\n");
        return 1;
    }

    // fill 5% of each matrix with random values
    fill("util/matrix_a.txt", m, n);
    fill("util/matrix_b.txt", n, p);

    return 0;
}