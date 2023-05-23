#include <stdio.h>
#include <time.h>

#include "la.h"

/* height(m), weight(lbs) */ /* male or female, 1 || 0 */

float cost(float w1, float w2, Matrix *matIn) {
    float result = 0.0f;
    for(size_t i = 0; i < matIn->rows; i++) {
        float x1 = matIn->data[i][0];
        float x2 = matIn->data[i][1];
        float y = w1*x1 + w2*x2;
        float d = y - matIn->data[i][2];
        result += d*d;
    }
    result /= matIn->rows;
    return result;
}

float randFloat() {
    return (float) rand()/ (float) RAND_MAX;
}

int main() {
    FILE *fp = fopen("input.txt", "r");
    Matrix *input = matInitFromFile(fp);

    srand(time(0));
    float w1 = randFloat() * 10;
    float w2 = randFloat() * 10;

    float rate = 1e-8;
    float h = 1e-5;

    for(int i = 0; i < 10000000; i++) {
        float c = cost(w1, w2, input);

        printf("w1 :%f, w2: %f, c: %f\n", w1, w2, c);

        float dw1 = (cost(w1 + h, w2, input) - c)/h;
        float dw2 = (cost(w1, w2 + h, input) - c)/h;

        w1 -= rate*dw1;
        w2 -= rate*dw2;
    }

    return 0;
}
