#include <stdio.h>
// Greatest common divisor

int main() {
    unsigned long long int a, b, t;
    scanf_s("%llu %llu", &a, &b);

    if (a == 0 || b == 0) { // особый случай
        return 1;
    }

    while (b) {
        t = a % b;
        a = b;
        b = t;
    }

    printf("%llu", a);

    return 0;
}
