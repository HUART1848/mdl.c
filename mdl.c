#include <stdio.h>

#define W 2000
#define H 2000
#define MAXITER 128

unsigned char img[W*H];

unsigned char mdlc(float x, float y) {
    float zr = 0.0;
    float zi = 0.0;

    float cr = x;
    float ci = y;

    for (int i = 0; i < MAXITER; ++i) {
        float nzr = zr * zr - zi * zi;
        float nzi = (2 * zr * zi);
        zr = nzr;
        zi = nzi;

        zr += cr;
        zi += ci;
        if (zr * zr + zi * zi > 4.0) {
            return (unsigned char) ((255.0 * i) / MAXITER);
        }
    }
    return 0;
}

void imgtoppm(char *filename, unsigned char *img, int w, int h) {
    FILE *f = fopen(filename, "w");
    fprintf(f, "P3\n");
    fprintf(f, "%d %d\n", w, h);
    fprintf(f, "255\n");

    for (int i = 0; i < w * h; ++i) {
        fprintf(f, "%d %d %d\n", img[i], img[i], img[i]);
    }

    fclose(f);
}

int main(void) {
    float x1 = -1.5, x2 = 1.5;
    float y1 = -1.5, y2 = 1.5;

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            float x = x1 + (x2 - x1) * ((float) j / W);
            float y = y1 + (y2 - y1) * ((float) i / H);

            img[j + i * W] = mdlc(x, y);
        }
    }

    imgtoppm("mdl.ppm", img, W, H);
    return 0;
}
