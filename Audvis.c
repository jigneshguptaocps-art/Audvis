#include <stdio.h>

// custom function to check if a number is prime
int isPrime(int n) {
    if (n <= 1)
        return 0;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int main(void) {
    int n;
    int num;
    int sum = 0;
    int even = 0, odd = 0, prime = 0;

    // while loop for input validation
    while (1) {
        printf("How many numbers do you want to enter? ");
        scanf("%d", &n);

        if (n > 0)
            break;
        else
            printf("Please enter a positive number.\n");
    }

    // for loop to process numbers
    for (int i = 1; i <= n; i++) {
        printf("Enter number %d: ", i);
        scanf("%d", &num);

        sum += num;

        // if / else logic
        if (num % 2 == 0)
            even++;
        else
            odd++;

        if (isPrime(num))
            prime++;
    }

    printf("\n--- Results ---\n");
    printf("Sum: %d\n", sum);
    printf("Even numbers: %d\n", even);
    printf("Odd numbers: %d\n", odd);
    printf("Prime numbers: %d\n", prime);

    return 0;
}