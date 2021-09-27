# primegen

Prime number generator using the segmented sieve of Eratosthenes algorithm, implemented in C++11

# Building and Running
## Linux
Dependencies:
- GCC 4.8.1 or newer

Clone this repo:
```
git clone https://github.com/muazr/primegen.git
```

Change directory and compile the executable:
```
cd primegen
make
```

To generate prime numbers up to NUM:
```
prime-number-generator NUM
```

To test whether NUM is a prime number:
```
prime-number-generator -t NUM
```

To find the next prime number after NUM:
```
prime-number-generator -n NUM
```

To view help message:
```
prime-number-generator -h
```
