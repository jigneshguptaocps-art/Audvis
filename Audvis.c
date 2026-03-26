#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int isPrime(int n) {
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

static void flush_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void) {
    int n;

    while (1) {
        printf("How many numbers do you want to enter? ");
        if (scanf("%d", &n) != 1) {
            printf("Invalid input. Please enter a positive integer.\n");
            flush_stdin();
            continue;
        }
        if (n > 0) break;
        printf("Please enter a positive number.\n");
    }

    int *nums = malloc((size_t)n * sizeof(int));
    if (!nums) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        return 1;
    }

    long long sum = 0;
    int even = 0, odd = 0, prime = 0;
    int min = INT_MAX, max = INT_MIN;

    for (int i = 0; i < n; i++) {
        printf("Enter number %d: ", i + 1);
        while (scanf("%d", &nums[i]) != 1) {
            printf("Invalid input. Enter an integer: ");
            flush_stdin();
        }

        sum += nums[i];
        if (nums[i] < min) min = nums[i];
        if (nums[i] > max) max = nums[i];
        if (nums[i] % 2 == 0) even++; else odd++;
        if (isPrime(nums[i])) prime++;
    }

    double avg = (double)sum / n;

    printf("\n========== Results ==========\n");
    printf("  Count   : %d\n", n);
    printf("  Sum     : %lld\n", sum);
    printf("  Average : %.2f\n", avg);
    printf("  Min     : %d\n", min);
    printf("  Max     : %d\n", max);
    printf("  Even    : %d\n", even);
    printf("  Odd     : %d\n", odd);
    printf("  Primes  : %d", prime);

    if (prime > 0) {
        printf("  {");
        int first = 1;
        for (int i = 0; i < n; i++) {
            if (isPrime(nums[i])) {
                if (!first) printf(", ");
                printf("%d", nums[i]);
                first = 0;
            }
        }
        printf("}");
    }

    printf("\n=============================\n");

    free(nums);
    return 0;
}
