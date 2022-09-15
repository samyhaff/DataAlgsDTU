#include <bits/stdc++.h>

#define N_MAX 1000

using namespace std;

int main() {
    int n;

    cin >> n;
    int *R = new int[n * n];
    int *D = new int[n * n];
    int *W = new int[n * n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - 1; j++)
            cin >> R[n * i + j];
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n; j++)
            cin >> D[n * i + j];

    W[0] = 0;
    for (int i = 1; i < n; i++)
        W[i] = R[i - 1] + W[i - 1];
    for (int i = 1; i < n; i++)
        W[n * i] = D[n * (i - 1)] + W[n * (i - 1)];
    for (int i = 1; i < n; i++)
        for (int j = 1; j < n; j++)
            W[n * i + j] = max(W[n * (i - 1) + j] + D[n * (i - 1) + j],
                               W[n * i + j - 1] + R[n * i + j - 1]);

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++)
    //         cout << W[n * i + j] << " ";
    //     cout << endl;
    // }
    cout << W[n * (n - 1) + n - 1];

    return 0;
}
