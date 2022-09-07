#include <algorithm>
#include <iostream>

using namespace std;

#define SIZE 100000
#define LOSS 100 // value decreases by 100$ per day

/* gets best day for buying between day left and day
right when selling after day right + 1 (included) */
int get_buy_day(int *s, int left, int right) {
    int i = right, price, best_price = s[right];

    for (int k = right - 1; k >= left; k--) {
        price = s[k] + (right - k) * LOSS;
        if (price < best_price) {
            best_price = price;
            i = k;
        }
    }

    return i;
}

/* gets best day for selling between day left and day
right when buying before day left - 1 (included) */
int get_sell_day(int *b, int left, int right) {
    int i = left, price, best_price = b[left];

    for (int k = left + 1; k <= right; k++) {
        price = b[k] + (k - left) * LOSS;
        if (price > best_price) {
            best_price = price;
            i = k;
        }
    }

    return i;
}

int solve(int *s, int *b, int low, int high) {
    // base cases
    if (high < low) return 0;
    if (high == low) return max(0, b[low] - s[low]);

    int x = (low + high) / 2;
    int i = get_buy_day(s, low, x);
    int j = get_sell_day(b, x + 1, high);
    int profit = b[j] - s[i] - (j - i) * LOSS; // profit when buying
    int profit_left = solve(s, b, low, x); // solve left subproblem
    int profit_right = solve(s, b, x + 1, high); // solve right subproblem
    int best_profit = max({0, profit_left, profit_right, profit}); // merge

    return best_profit;
}

int main() {
    int n, s[SIZE], b[SIZE];
    cin >> n;

    for (int i = 0; i < n; i++) cin >> s[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    int profit = solve(s, b, 0, n - 1);
    cout << profit << endl;

    return 0;
}
