#include <stdio.h>
#include <string.h>

#define W 2000
#define H 2000
#define MAXITER 128

unsigned char imgdata[W*H*3];

unsigned char mdlc(float x, float y) {
    float zr = 0.0;
    float zi = 0.0;

    float cr = x;
    float ci = y;

    for (int i = 0; i < MAXITER; ++i) {
        float nzr = zr * zr - zi * zi + cr;
        float nzi = (2 * zr * zi) + ci;

        zr = nzr;
        zi = nzi;
        if (zr * zr + zi * zi > 4.0) {
            return (unsigned char) ((255.0 * i) / MAXITER);
        }
    }
    return 0;
}

void imgtoppm(char *filename, unsigned char *imgdata, int w, int h) {
    /* Write header */
    FILE *f = fopen(filename, "w");
    fprintf(f, "P6\n");
    fprintf(f, "%d %d\n", w, h);
    fprintf(f, "255\n");
    fclose(f);

    /* Write pixels */
    f = fopen(filename, "ab");
    fwrite(imgdata, 1, w * h * 3, f);
    fclose(f);
}

int main(void) {
    float x1 = -1.5, x2 = 1.5;
    float y1 = -1.5, y2 = 1.5;

    puts("Computing...");
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            float x = x1 + (x2 - x1) * ((float) j / W);
            float y = y1 + (y2 - y1) * ((float) i / H);

            unsigned char c = mdlc(x, y);
            int idx = (j + i * W) * 3;
            imgdata[idx] = c;
            imgdata[idx+1] = c;
            imgdata[idx+2] = c;
        }
    }

    puts("Writing to file...");
    imgtoppm("mdl.ppm", imgdata, W, H);

    return 0;
}
