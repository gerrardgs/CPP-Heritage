#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <unordered_map>
#include <numeric>

#define SIZE 100

using namespace std;

//--------------------------------------------
// Structs
//--------------------------------------------

struct CoinSelection
{
    int value;
    int count;
};

struct CoinResult
{
    int totalCount;
    int selectedCount;
    CoinSelection *selections;
};

struct Task
{
    int duration;
    char name[50];
};

//--------------------------------------------
// Global Variables
//--------------------------------------------

unordered_map<int, int> memo;

//--------------------------------------------
// Helper Functions
//--------------------------------------------

int compare(const void *a, const void *b)
{
    return (*(int *)b - *(int *)a);
}

void printCoinSelection(CoinSelection *selections, int coinCount)
{
    for (int i = 0; i < coinCount; ++i)
    {
        if (selections[i].count > 0)
        {
            cout << "\nCoin " << selections[i].value << " = " << selections[i].count << " ";
        }
    }
    cout << "\n";
}

//--------------------------------------------
// Exchange Coin Functions
//--------------------------------------------

CoinResult exchangeCoinsBruteForce(int target, vector<int> &coins)
{
    if (target == 0)
        return {0, 0, nullptr};
    if (memo.find(target) != memo.end())
        return {memo[target], 0, nullptr};

    CoinSelection *selections = new CoinSelection[coins.size()];
    int result = INT_MAX;
    for (int coin : coins)
    {
        if (target - coin >= 0)
        {
            CoinResult subResult = exchangeCoinsBruteForce(target - coin, coins);
            if (subResult.totalCount != INT_MAX)
            {
                result = min(result, subResult.totalCount + 1);
                for (int i = 0; i < coins.size(); ++i)
                {
                    selections[i].value = coins[i];
                    selections[i].count = subResult.selections[i].count;
                }
                selections[coin].count++; // Fixing the error here
            }
        }
    }
    memo[target] = (result == INT_MAX) ? INT_MAX : result;
    CoinResult finalResult = {memo[target], static_cast<int>(coins.size()), selections};
    delete[] selections; // Freeing memory
    return finalResult;
}

CoinResult exchangeCoinsGreedy(int target, vector<int> &coins)
{
    sort(coins.begin(), coins.end(), greater<int>());
    CoinSelection *selections = new CoinSelection[coins.size()];
    int totalCount = 0;
    for (int i = 0; i < coins.size(); ++i)
    {
        selections[i].value = coins[i];
        selections[i].count = 0;
    }
    for (int i = 0; i < coins.size(); ++i)
    {
        int coin = coins[i];
        while (target >= coin)
        {
            target -= coin;
            selections[i].count++;
            totalCount++;
        }
    }
    CoinResult finalResult = {totalCount, static_cast<int>(coins.size()), selections};
    delete[] selections; // Freeing memory
    return finalResult;
}

//--------------------------------------------
// Job Schedule Functions
//--------------------------------------------

void bruteForceSchedule(Task *tasks, int taskCount)
{
    for (int i = 0; i < taskCount - 1; ++i)
    {
        for (int j = 0; j < taskCount - i - 1; ++j)
        {
            if (tasks[j].duration > tasks[j + 1].duration)
            {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
}

void greedySchedule(Task *tasks, int taskCount)
{
    for (int i = 0; i < taskCount - 1; ++i)
    {
        int minIndex = i;
        for (int j = i + 1; j < taskCount; ++j)
        {
            if (tasks[j].duration < tasks[minIndex].duration)
            {
                minIndex = j;
            }
        }
        Task temp = tasks[i];
        tasks[i] = tasks[minIndex];
        tasks[minIndex] = temp;
    }
}

//--------------------------------------------
// Knapsack Problem Functions
//--------------------------------------------

int knapsackBruteForce(vector<int>& weights, vector<int>& profits, int n, int capacity) {
    if (n == 0 || capacity == 0)
        return 0;
    if (weights[n - 1] > capacity)
        return knapsackBruteForce(weights, profits, n - 1, capacity);
    else
        return max(profits[n - 1] + knapsackBruteForce(weights, profits, n - 1, capacity - weights[n - 1]), knapsackBruteForce(weights, profits, n - 1, capacity));
}

int knapsackGreedyByProfit(vector<int>& weights, vector<int>& profits, int n, int capacity) {
    vector<pair<double, int>> pPerW;
    for (int i = 0; i < n; ++i)
        pPerW.push_back(make_pair((double)profits[i] / weights[i], i));
    sort(pPerW.begin(), pPerW.end(), greater<pair<double, int>>());

    int maxProfit = 0;
    for (int i = 0; i < n; ++i) {
        int index = pPerW[i].second;
        if (weights[index] <= capacity) {
            maxProfit += profits[index];
            capacity -= weights[index];
        } else {
            maxProfit += (profits[index] * ((double)capacity / weights[index]));
            break;
        }
    }
    return maxProfit;
}

int knapsackGreedyByWeight(vector<int>& weights, vector<int>& profits, int n, int capacity) {
    vector<pair<double, int>> wPerP;
    for (int i = 0; i < n; ++i)
        wPerP.push_back(make_pair((double)weights[i] / profits[i], i));
    sort(wPerP.begin(), wPerP.end());

    int maxProfit = 0;
    for (int i = 0; i < n; ++i) {
        int index = wPerP[i].second;
        if (weights[index] <= capacity) {
            maxProfit += profits[index];
            capacity -= weights[index];
        } else {
            maxProfit += (profits[index] * ((double)capacity / weights[index]));
            break;
        }
    }
    return maxProfit;
}

int knapsackGreedyByDensity(vector<int>& weights, vector<int>& profits, int n, int capacity) {
    vector<pair<double, int>> density;
    for (int i = 0; i < n; ++i)
        density.push_back(make_pair((double)profits[i] / weights[i], i));
    sort(density.begin(), density.end(), greater<pair<double, int>>());

    int maxProfit = 0;
    for (int i = 0; i < n; ++i) {
        int index = density[i].second;
        if (weights[index] <= capacity) {
            maxProfit += profits[index];
            capacity -= weights[index];
        } else {
            maxProfit += (profits[index] * ((double)capacity / weights[index]));
            break;
        }
    }
    return maxProfit;
}

//--------------------------------------------
// Main Function
//--------------------------------------------

int main()
{
    int choice, coinCount, amount, method_choice, taskCount, knapsack_choice;
    Task tasks[SIZE];
    int coins[SIZE], solution;
    vector<int> coinValues; // Move declaration outside switch

    int waitingTime = 0; // Move declaration outside the switch statement
    int waitTime = 0;    // Move declaration outside the switch statement

    vector<int> weights, profits; // Move declaration outside the switch statement

    while (true)
    {
        cout << "\n---------------------\n";
        cout << "Menu:\n";
        cout << "---------------------\n";
        cout << "1. Exchange Coins\n";
        cout << "2. Job Schedule\n";
        cout << "3. Knapsack Problem\n";
        cout << "4. Exit\n";
        cout << "---------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\n---------------------\n";
            cout << "Choose method:\n";
            cout << "---------------------\n";
            cout << "1. Brute Force\n";
            cout << "2. Greedy\n";
            cout << "---------------------\n";
            cout << "Enter your choice: ";
            cin >> method_choice;

            cout << "\nEnter the number of coins: ";
            cin >> coinCount;

            cout << "Enter the values of coins: ";
            coinValues.clear(); // Clear before reusing
            coinValues.resize(coinCount); // Resize to fit the number of coins
            for (int i = 0; i < coinCount; ++i)
            {
                cin >> coinValues[i];
            }

            cout << "Enter the amount of Exchange: ";
            cin >> amount;

            switch (method_choice)
            {
            case 1:
                solution = exchangeCoinsBruteForce(amount, coinValues).totalCount;
                cout << "\nBrute Force Solution: " << solution << endl;
                break;
            case 2:
                solution = exchangeCoinsGreedy(amount, coinValues).totalCount;
                cout << "\nGreedy Solution: " << solution << endl;
                break;
            default:
                cout << "Invalid method choice.\n";
            }
            break;

        case 2:
            cout << "\n---------------------\n";
            cout << "Choose method:\n";
            cout << "---------------------\n";
            cout << "1. Brute Force\n";
            cout << "2. Greedy\n";
            cout << "---------------------\n";
            cout << "Enter your choice: ";
            cin >> method_choice;

            cout << "\nEnter the number of tasks: ";
            cin >> taskCount;

            cout << "Enter task (format 'name_task duration' separated by space):\n";
            for (int i = 0; i < taskCount; ++i)
            {
                cin >> tasks[i].name >> tasks[i].duration;
            }

            switch (method_choice)
            {
            case 1:
                bruteForceSchedule(tasks, taskCount);
                cout << "\nBrute Force Solution:\n";
                for (int i = 0; i < taskCount; ++i)
                {
                    cout << tasks[i].name << " ";
                }
                waitingTime = 0; // Reset waitingTime
                for (int i = 1; i < taskCount; ++i)
                {
                    waitingTime += tasks[i - 1].duration;
                }
                cout << "\nTotal Wait Time: " << waitingTime << " hours\n";
                break;
            case 2:
                greedySchedule(tasks, taskCount);
                cout << "\nGreedy Solution:\n";
                for (int i = 0; i < taskCount; ++i)
                {
                    cout << tasks[i].name << " ";
                }
                waitTime = 0; // Reset waitTime
                for (int i = 0; i < taskCount; ++i)
                {
                    int currentTime = 0;
                    for (int j = 0; j <= i; ++j)
                    {
                        currentTime += tasks[j].duration;
                    }
                    waitTime += max(0, currentTime - tasks[i].duration) - 1;
                }
                cout << "\nTotal Wait Time: " << waitTime << " hours\n";
                break;
            default:
                cout << "Invalid method choice.\n";
            }
            break;

        case 3:
            cout << "\n---------------------\n";
            cout << "Choose method:\n";
            cout << "---------------------\n";
            cout << "1. Brute Force\n";
            cout << "2. Greedy by profit\n";
            cout << "3. Greedy by weight\n";
            cout << "4. Greedy by density\n";
            cout << "---------------------\n";
            cout << "Enter your choice: ";
            cin >> knapsack_choice;

            weights.clear(); // Clear weights vector
            profits.clear(); // Clear profits vector

            int n, capacity;

            cout << "Enter the number of items: ";
            cin >> n;
            cout << "Enter the weights of items: ";
            for (int i = 0; i < n; ++i)
            {
                int w;
                cin >> w;
                weights.push_back(w);
            }
            cout << "Enter the profits of items: ";
            for (int i = 0; i < n; ++i)
            {
                int p;
                cin >> p;
                profits.push_back(p);
            }

            cout << "Enter the capacity of knapsack: ";
            cin >> capacity;

            switch (knapsack_choice)
            {
            case 1: // Brute Force
            {
                int maxProfitBF = knapsackBruteForce(weights, profits, n, capacity);
                cout << "Maximum profit using Brute Force: " << maxProfitBF << endl;
                break;
            }
            case 2: // Greedy by profit
            {
                int maxProfitGP = knapsackGreedyByProfit(weights, profits, n, capacity);
                cout << "Maximum profit using Greedy by Profit: " << maxProfitGP << endl;
                break;
            }
            case 3: // Greedy by weight
            {
                int maxProfitGW = knapsackGreedyByWeight(weights, profits, n, capacity);
                cout << "Maximum profit using Greedy by Weight: " << maxProfitGW << endl;
                break;
            }
            case 4: // Greedy by density
            {
                int maxProfitGD = knapsackGreedyByDensity(weights, profits, n, capacity);
                cout << "Maximum profit using Greedy by Density: " << maxProfitGD << endl;
                break;
            }
            default:
                cout << "Invalid choice.\n";
            }
            break;

        case 4:
            cout << "Exiting program...\n";
            return 0;

        default:
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}
