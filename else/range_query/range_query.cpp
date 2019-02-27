#include <cstdio>
#include <cstdlib>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int SZ = 1 << 20;  //improve IO buff 
struct fastio{
    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin, inbuf, _IOFBF, SZ);
        setvbuf(stdout, outbuf, _IOFBF, SZ);
    }
}io;

const int MAXN = 10000001;
int number[MAXN] = {0};

int main(int argc, char const *argv[])
{
    int n, m, p, l, r, max_val = 0;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &p);
        number[p] = 1;
        max_val = max(max_val, p);
    }
    for (int i = 1; i <= max_val; ++i) {
        number[i] += number[i - 1];
    }
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &l, &r);
        r = min(r, max_val);
        if (l == 0)
            printf("%d\n", number[r]);
            // cout << number[r] << endl;
        else if (l > max_val)
            printf("0\n");
            // cout << 0 << endl;
        else
            printf("%d\n", number[r] - number[l - 1]);
            // cout << number[r] - number[l - 1] << endl;
    }
    return 0;
}