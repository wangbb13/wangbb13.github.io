// ref: https://github.com/xtaci/algorithms/blob/master/include/shuffle.h

#ifndef ALGO_SHUFFLE_H__
#define ALGO_SHUFFLE_H__

#include <cstdio>
#include <cstdlib>
#include <ctime>

namespace alg {
    template<typename T>
    static void shuffle(T *list, int len) {
        srand(time(NULL));
        int i = len, j;
        T temp;

        if (i == 0)
            return;
        while (--i) {
            j = rand() % (i + 1);
            temp = list[i];
            list[i] = list[j];
            list[j] = temp;
        }
    }
}

#endif