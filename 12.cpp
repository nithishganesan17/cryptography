#include <stdio.h>
#include <math.h>

int main() {
   
    double factorial = 1;
    for (int i = 2; i <= 24; ++i) {
        factorial *= i;
    }

    double unique_keys = factorial / 2;

    double log_base_2 = log2(unique_keys);

    printf("Approximate number of effectively unique keys: %.0lf (approximately 2^%.0lf)\n", unique_keys, log_base_2);

    return 0;
}

