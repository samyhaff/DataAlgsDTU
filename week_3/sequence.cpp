#include <bits/stdc++.h>

using namespace std;

#define PENALTY 1

int main() {
    string x, y;
    getline(cin, x);
    getline(cin, y);

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

    // for (int i = 0; i <= n; i++) {
    //     for (int j = 0; j <= m; j++) {
    //         cout << arr[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << arr[n][m] << endl;

    string x_sol, y_sol;
    int i = n, j = m;

    while (i > 0 || j > 0) {
        if (i == 0) {
            x_sol.push_back('-');
            y_sol.push_back(j > 0 ? y[j - 1] : '-');
            j--;
            continue;
        }
        else if (j == 0) {
            x_sol.push_back(i > 0 ? x[i - 1] : '-');
            y_sol.push_back('-');
            i--;
            continue;
        }
        int cost = min({arr[i - 1][j - 1], arr[i][j - 1], arr[i - 1][j]});
        if (arr[i - 1][j - 1] == cost) {
            x_sol.push_back(i > 0 ? x[i - 1] : '-');
            y_sol.push_back(j > 0 ? y[j - 1] : '-');
            i--; j--;
        }
        else if (arr[i][j - 1] == cost) {
            x_sol.push_back('-');
            y_sol.push_back(j > 0 ? y[j - 1] : '-');
            j--;
        }
        else if (arr[i - 1][j] == cost) {
            x_sol.push_back(i > 0 ? x[i - 1] : '-');
            y_sol.push_back('-');
            i--;
        }
    }

    reverse(x_sol.begin(), x_sol.end());
    reverse(y_sol.begin(), y_sol.end());

    cout << x_sol << '\n' << y_sol;

    return 0;
}
