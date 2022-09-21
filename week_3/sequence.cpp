#include <bits/stdc++.h>

using namespace std;

#define PENALTY 1

int main() {
    string x, y;
    cin >> x >> y;

    int n = x.length();
    int m = y.length();

    int **arr = new int*[n + 1];
    for (int i = 0; i <= n; i++) arr[i] = new int[m + 1];

    for (int i = 0; i <= n; i++) arr[i][0] = i * PENALTY;
    for (int j = 0; j <= m; j++) arr[0][j] = j * PENALTY;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arr[i + 1][j + 1] = min({(x[i] != y[j]) * PENALTY + arr[i][j],
                                        PENALTY + arr[i + 1][j],
                                        PENALTY + arr[i][j + 1]});
        }
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    // cout << arr[n][m] << endl;

    return 0;
}
