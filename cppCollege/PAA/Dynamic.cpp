#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int knapsack(const vector<int>& weights, const vector<int>& values, int W) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (weights[i-1] <= w) {
                dp[i][w] = max(dp[i-1][w], dp[i-1][w - weights[i-1]] + values[i-1]);
                } else {
                    dp[i][w] = dp[i-1][w];
                }
            }
        }
    return dp[n][W];
}

int main() {
    vector<int> weights = {2, 3, 4, 5, 6, 7, 8};
    vector<int> values = {90, 30, 60, 70, 20, 80, 50};
    int W = 15; 
    cout << "Nilai maksimum yang dapat diperoleh: " << knapsack(weights, values, W) << endl;
    return 0;
}