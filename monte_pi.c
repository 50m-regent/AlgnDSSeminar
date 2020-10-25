#include <stdio.h>
#include <math.h>

long x=1;

short int rnd() {
  x=x*1103515245+12345;
  return (short int)(x>>16)&32767;
}

void seed(unsigned short s) {
  x=s;
}

double estimate_pi(int n) {
    int i, inside_cnt = 0;
    double x, y;

    for (i = 0; i < n; i++) {
        x = rnd() / 32767.0;
        y = rnd() / 32767.0;

        if (y * y <= 1 - x * x) {
            inside_cnt++;
        }
    }

    return 4.0 * (double)inside_cnt / (double)n;
}

int main() {
    seed(123);

    int n;
    double pi;
    
    puts("----------------");
    for (n = 10; n < 1e9; n *= 10) {
        printf("Number of Points: %d\n", n);

        pi = estimate_pi(n);
        printf("Estimated PI: %f\n", pi);

        if (pi > M_PI) {
            printf("Error: %f%%\n", (pi - M_PI) / M_PI * 100.0);
        } else {
            printf("Error: %f%%\n", (M_PI - pi) / M_PI * 100.0);
        }
        
        puts("----------------");
    }
}