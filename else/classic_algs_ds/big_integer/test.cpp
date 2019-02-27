#include <iostream>
using namespace std;

const int MAXN = 1000;

typedef struct BigInteger_t {
    int digits;
    int bits[MAXN]; // small-endian

    BigInteger_t() {
        digits = 0;
        for (int i = 0; i < MAXN; ++i) 
            bits[i] = 0;
    }

    BigInteger_t(int n) {
        digits = 0;
        while (n) {
            bits[digits++] = n % 10;
            n /= 10;
        }
    }
} BigInteger;

void multiply(BigInteger *bia, BigInteger *bib) {   // bia as ans
    int temp[MAXN] = {0}, bial = bia->digits, bibl = bib->digits;
    for (int i = 0; i < bial; ++i) {
        for (int j = 0; j < bibl; ++j) {
            temp[i + j] += bia->bits[i] * bib->bits[j];
        }
    }
    bia->digits = 0;
    int i = 0;
    for (; i < bial + bibl - 1; ++i) {
        bia->bits[bia->digits++] = temp[i] % 10;
        temp[i + 1] += temp[i] / 10;
    }
    while (i + 1 < MAXN && temp[i]) {
        bia->bits[bia->digits++] = temp[i] % 10;
        temp[i + 1] += temp[i] / 10;
        i++;
    }
}

void show(BigInteger *bi) {
    for (int i = bi->digits - 1; i >= 0; --i) {
        cout << bi->bits[i];
    }
}

// Complete the extraLongFactorials function below.
void extraLongFactorials(int n) {
    BigInteger *ans = new BigInteger(1);
    for (int i = 2; i <= n; ++i) {
        BigInteger *bi = new BigInteger(i);
        multiply(ans, bi);
    }
    show(ans);
}

int main()
{
    int n;
    cin >> n;
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');

    extraLongFactorials(n);

    return 0;
}