#include <bits/stdc++.h>

using namespace std;

int max_score(int c[], int *opt[], int i, int j) {
    int left_score, right_score;
    if (opt[i][j] >= 0) return opt[i][j];
    if (i == j) {
        opt[i][j] = c[i];
        return c[i];
    }
    if (i > j) {
        opt[i][j] = 0;
        return 0;
    }
    if (c[i + 1] > c[j]) left_score = c[i] + max_score(c, opt, i+2, j);
    else left_score = c[i] + max_score(c, opt, i+1, j-1);
    if (c[j - 1] > c[i]) right_score = c[j] + max_score(c, opt, i, j-2);
    else right_score = c[j] + max_score(c, opt, i+1, j-1);
    opt[i][j] = max(left_score, right_score);
    return opt[i][j];
}

int main() {
    int n;

    cin >> n;
    int *c = new int[n];
    for (int i = 0; i < n; i++) cin >> c[i];

    int **opt = new int*[n];
    for (int i = 0; i < n; i++) opt[i] = new int[n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            opt[i][j] = -1;

    cout << max_score(c, opt, 0, n - 1) << endl;

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++)
    //         cout << opt[i][j] << " ";
    //     cout << endl;
    // }

    return 0;
}
