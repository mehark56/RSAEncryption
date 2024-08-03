#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// Function to find gcd
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to generate a random prime number
int generate_prime() {
    int primes[] = {101, 103, 107, 109, 113, 127, 131, 137, 139, 149,
                    151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199};
    int size = sizeof(primes) / sizeof(primes[0]);
    int index = rand() % size;
    return primes[index];
}

// Function to calculate (base^exp) % mod
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Function to find modular inverse of a under modulo m using Extended Euclidean Algorithm
int mod_inverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    // Apply extended Euclidean Algorithm
    while (a > 1) {
        // q is quotient
        q = a / m;
        t = m;

        // m is remainder now, process same as Euclid's algo
        m = a % m, a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0)
        x1 += m0;

    return x1;
}

// Function to generate RSA keys
void generate_keys(int *n, int *e, int *d) {
    // Generate two distinct prime numbers p and q
    int p = generate_prime();
    int q = generate_prime();
    while (q == p) {
        q = generate_prime();
    }

    // Calculate n = p * q
    *n = p * q;

    // Calculate the totient function phi(n) = (p-1)*(q-1)
    int phi = (p - 1) * (q - 1);

    // Choose an integer e such that 1 < e < phi(n) and gcd(e, phi(n)) = 1
    *e = 2;
    while (gcd(*e, phi) != 1) {
        (*e)++;
    }

    // Calculate d to satisfy the congruence relation d*e ≡ 1 (mod phi)
    *d = mod_inverse(*e, phi);
}

// Function to encrypt a message using public key
long long encrypt(int msg, int e, int n) {
    return mod_exp(msg, e, n);
}

// Function to decrypt a message using private key
int decrypt(long long cipher, int d, int n) {
    return mod_exp(cipher, d, n);
}

int main() {
    srand(time(0));

    int n, e, d;

    // Generate RSA keys
    generate_keys(&n, &e, &d);

    printf("Public Key: (n = %d, e = %d)\n", n, e);
    printf("Private Key: (d = %d)\n", d);

    // Example message to encrypt
    int msg;
    printf("Enter a message to encrypt (as an integer): ");
    scanf("%d", &msg);

    // Encrypt the message
    long long encrypted_msg = encrypt(msg, e, n);
    printf("Encrypted Message: %lld\n", encrypted_msg);

    // Decrypt the message
    int decrypted_msg = decrypt(encrypted_msg, d, n);
    printf("Decrypted Message: %d\n", decrypted_msg);

    return 0;
}
