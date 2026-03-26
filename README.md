# Audvis

A command-line number analysis tool written in C. Enter a batch of integers and get a full statistical breakdown instantly.

## Features

- Sum, average, min, and max
- Even / odd counts
- Prime number detection with a list of which numbers were prime
- Input validation — rejects non-integers and zero/negative counts
- Overflow-safe sum using `long long`

## Build

```bash
make
```

## Usage

```
$ ./Audvis
How many numbers do you want to enter? 5
Enter number 1: 3
Enter number 2: 7
Enter number 3: 8
Enter number 4: 12
Enter number 5: 13

========== Results ==========
  Count   : 5
  Sum     : 43
  Average : 8.60
  Min     : 3
  Max     : 13
  Even    : 2
  Odd     : 3
  Primes  : 3  {3, 7, 13}
=============================
```

## Clean

```bash
make clean
```
