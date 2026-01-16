// https://github.com/codeplea/genann
#include "genann.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef const char *cstring;

// def'd in only some C standards
#define min(x,y) (x < y ? x : y)
#define max(x,y) (x < y ? y : x)

static size_t
non_null(size_t lim, cstring args[]) {
    size_t i, n = min(max(1, lim), 10);
    for (i = 0; i < n; i += 1) {
        if (args[i] == 0) break;
    }
    return i;
}

static genann *
xor_train(size_t lim, cstring args[]) {
    int i, n = non_null(lim, args);
    for (i = 0; i < n; i += 1)
        (void) printf(" - %s\n", args[i]);
    genann *ann = genann_init(2, 1, 2, 1);
    // two inputs, one hidden layer, two neurons, one output
    const double input[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    const double output[4] = {0, 1, 1, 0};

    // Train on the four labeled data points many times.
    for (i = 0; i < 500; ++i) {
        genann_train(ann, input[0], output + 0, 3);
        genann_train(ann, input[1], output + 1, 3);
        genann_train(ann, input[2], output + 2, 3);
        genann_train(ann, input[3], output + 3, 3);
    }
    cstring msg = "for [%1.f, %1.f]: %1.f.\n";
    (void) printf(msg, input[0][0], input[0][1], *genann_run(ann, input[0]));
    (void) printf(msg, input[1][0], input[1][1], *genann_run(ann, input[1]));
    (void) printf(msg, input[2][0], input[2][1], *genann_run(ann, input[2]));
    (void) printf(msg, input[3][0], input[3][1], *genann_run(ann, input[3]));
    return ann;
}

int main(int argc, cstring *argv) {
    (void) srand(time(0));
    genann *ann = xor_train(argc, argv + 1);
    (void) genann_free(ann);
    return EXIT_SUCCESS;
}
