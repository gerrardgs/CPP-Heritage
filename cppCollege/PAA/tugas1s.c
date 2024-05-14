#include <stdio.h>

int sum_of_divisors(int n) {
    if (n <= 1) {
        return 0;
    }

    int divisors_sum = 1;
    int i = 2;
    while (i * i <= n) {
        if (n % i == 0) {
            divisors_sum += i;
            if (i * i != n) {
                divisors_sum += n / i;
            }
        }
        i++;
    }
    return divisors_sum;
}

int main() {
    int num_test_cases;
    scanf("%d", &num_test_cases);
    if (num_test_cases <= 0) {
        return 1;
    }
    int test_cases[num_test_cases];
    for (int i = 0; i < num_test_cases; i++) {
        scanf("%d", &test_cases[i]);
    }
    for (int i = 0; i < num_test_cases; i++) {
        printf("%d\n", sum_of_divisors(test_cases[i]));
    }
    return 0;
}
