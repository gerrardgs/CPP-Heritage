#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <unordered_map>
#include <numeric>

#define SIZE 100

using namespace std;

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

unordered_map<int, int> memo;

//--------------------------------------------
// EXCHANGE COIN
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

void generateCoinCombinations(int target, int *coins, int coinCount, int *combination, int index, int **combinations, int *minCount, CoinSelection *selections)
{
    if (target == 0)
    {
        int totalCount = 0;
        for (int i = 0; i < coinCount; ++i)
        {
            totalCount += combination[i];
        }
        if (totalCount < *minCount)
        {
            *minCount = totalCount;
            for (int i = 0; i < coinCount; ++i)
            {
                selections[i].count = combination[i];
            }
        }
        return;
    }
    if (index == coinCount)
    {
        return;
    }
    for (int i = 0; coins[index] * i <= target; ++i)
    {
        combination[index] = i;
        generateCoinCombinations(target - coins[index] * i, coins, coinCount, combination, index + 1, combinations, minCount, selections);
    }
}

CoinResult exchangeCoinsBruteForce(int target, int *coins, int coinCount)
{
    CoinSelection *selections = new CoinSelection[coinCount];
    for (int i = 0; i < coinCount; ++i)
    {
        selections[i].value = coins[i];
        selections[i].count = 0;
    }

    int minCount = INT_MAX;
    int *combination = new int[coinCount];
    generateCoinCombinations(target, coins, coinCount, combination, 0, nullptr, &minCount, selections);

    CoinResult result = {minCount, coinCount, selections};
    delete[] combination;
    return result;
}

CoinResult exchangeCoinsGreedy(int target, int *coins, int coinCount)
{
    sort(coins, coins + coinCount, greater<int>());
    int totalCount = 0;
    CoinSelection *selections = new CoinSelection[coinCount];
    for (int i = 0; i < coinCount; ++i)
    {
        selections[i].value = coins[i];
        selections[i].count = 0;
    }
    for (int i = 0; i < coinCount; ++i)
    {
        int coin = coins[i];
        while (target >= coin)
        {
            target -= coin;
            selections[i].count++;
            totalCount++;
        }
    }
    CoinResult result = {totalCount, coinCount, selections};
    return result;
}

int chooseMethod(int target, int *coins, int coinCount, int method_choice)
{
    switch (method_choice)
    {
    case 1:
    {
        CoinResult result = exchangeCoinsBruteForce(target, coins, coinCount);
        cout << "\nBrute Force Solution: ";
        printCoinSelection(result.selections, coinCount);
        delete[] result.selections;
        return result.totalCount;
    }
    case 2:
    {
        CoinResult result = exchangeCoinsGreedy(target, coins, coinCount);
        cout << "\nGreedy Solution: ";
        printCoinSelection(result.selections, coinCount);
        delete[] result.selections;
        return result.totalCount;
    }
    default:
        cout << "Invalid method choice.\n";
        return -1;
    }
}

void getUserInputCoin(int *coinCount, int coins[], int *amount, int *method_choice)
{
    cout << "\nEnter the number of coins: ";
    cin >> *coinCount;

    cout << "Enter the values of coins: ";
    for (int i = 0; i < *coinCount; ++i)
    {
        cin >> coins[i];
    }

    cout << "Enter the amount of Exchange: ";
    cin >> *amount;

    cout << "\n---------------------";
    cout << "\nChoose method:\n";
    cout << "---------------------\n";
    cout << "1. Brute Force\n";
    cout << "2. Greedy\n";
    cout << "---------------------\n";
    cout << "Enter your choice: ";
    cin >> *method_choice;
}

void displayExchange(int solution)
{
    cout << "Total Coin: " << solution << " coin\n";
}

//--------------------------------------------
// JOB SCHEDULE
//--------------------------------------------
void getUserInputCoinTasks(int *taskCount, Task *tasks, int *method_choice)
{
    cout << "\nEnter the number of tasks: ";
    cin >> *taskCount;
    cout << "Enter task (format 'name_task duration' separated by space):\n";
    for (int i = 0; i < *taskCount; ++i)
    {
        cin >> tasks[i].name >> tasks[i].duration;
    }

    cout << "\n---------------------\n";
    cout << "Choose method:\n";
    cout << "---------------------\n";
    cout << "1. Brute Force\n";
    cout << "2. Greedy\n";
    cout << "---------------------\n";
    cout << "Enter your choice: ";
    cin >> *method_choice;
}

void printSchedule(Task *tasks, int taskCount)
{
    for (int i = 0; i < taskCount; ++i)
    {
        cout << tasks[i].name << " ";
    }
    cout << "\n";
}

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

void displaySchedule(Task *tasks, int taskCount, string method)
{
    cout << "\n"
         << method << " Solution:\n";
    printSchedule(tasks, taskCount);

    int waitingTime = 0;
    for (int i = 1; i < taskCount; ++i)
    {
        waitingTime += tasks[i - 1].duration;
    }
    cout << "Total Wait Time: " << waitingTime << " hours\n";
}

// Function for Brute Force Knapsack
int knapsackBruteForce(vector<int>& weights, vector<int>& profits, int n, int capacity) {
    // Base case
    if (n == 0 || capacity == 0)
        return 0;

    // If weight of the nth item is more than Knapsack capacity, then this item cannot be included in the optimal solution
    if (weights[n - 1] > capacity)
        return knapsackBruteForce(weights, profits, n - 1, capacity);

    // Return the maximum of two cases:
    // (1) nth item included
    // (2) not included
    else
        return max(profits[n - 1] + knapsackBruteForce(weights, profits, n - 1, capacity - weights[n - 1]), knapsackBruteForce(weights, profits, n - 1, capacity));
}

// Function for Greedy by Profit Knapsack
int knapsackGreedyByProfit(vector<int>& weights, vector<int>& profits, int n, int capacity) {
    // Array to store the profit per unit weight
    vector<pair<double, int>> pPerW;

    for (int i = 0; i < n; ++i)
        pPerW.push_back(make_pair((double)profits[i] / weights[i], i));

    // Sort in decreasing order of profit per unit weight
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

// Function for Greedy by Weight Knapsack
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

// Function for Greedy by Density Knapsack
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

// Function to calculate exchange coins using brute force algorithm
int exchangeCoinsBruteForce(int target, vector<int> &coins)
{
    if (target == 0)
        return 0;
    if (memo.find(target) != memo.end())
        return memo[target];
    int result = INT_MAX;
    for (int coin : coins)
    {
        if (target - coin >= 0)
        {
            int subResult = exchangeCoinsBruteForce(target - coin, coins);
            if (subResult != INT_MAX)
            {
                result = min(result, subResult + 1);
            }
        }
    }
    memo[target] = (result == INT_MAX) ? INT_MAX : result;
    return memo[target];
}

// Function to calculate exchange coins using greedy algorithm
int exchangeCoinsGreedy(int target, vector<int> &coins)
{
    sort(coins.begin(), coins.end(), greater<int>());
    int count = 0;
    for (int coin : coins)
    {
        while (target >= coin)
        {
            target -= coin;
            count++;
        }
    }
    return count;
}

// Function to calculate job schedule using brute force algorithm
vector<pair<string, int>> jobScheduleBruteForce(vector<pair<string, int>> &tasks)
{
    vector<pair<string, int>> minSchedule;
    int minWaitTime = INT_MAX;

    vector<int> perm(tasks.size());
    iota(perm.begin(), perm.end(), 0);

    do
    {
        int waitTime = 0;
        for (int i = 0; i < tasks.size(); ++i)
        {
            int currentTime = 0;
            for (int j = 0; j <= i; ++j)
            {
                currentTime += tasks[perm[j]].second;
            }
            waitTime += max(0, currentTime - tasks[perm[i]].second);
        }
        if (waitTime < minWaitTime)
        {
            minWaitTime = waitTime;
            minSchedule.clear();
            for (int i = 0; i < tasks.size(); ++i)
            {
                minSchedule.push_back(tasks[perm[i]]);
            }
        }
    } while (next_permutation(perm.begin(), perm.end()));

    return minSchedule;
}

// Function to calculate job schedule using greedy algorithm
vector<pair<string, int>> jobScheduleGreedy(vector<pair<string, int>> &tasks)
{
    sort(tasks.begin(), tasks.end(), [](const pair<string, int> &a, const pair<string, int> &b)
         { return a.second < b.second; });

    return tasks;
}
