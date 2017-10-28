//
// Created by belisariops on 10/25/17.
//

#include <cstdlib>

static int mod(int a, int b) {
    return a >= 0 ? a%b :  ( b - abs ( a%b ) ) % b;
}


