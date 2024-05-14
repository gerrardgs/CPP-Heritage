#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <unordered_map>
#include <numeric>

using namespace std;

unordered_map<int, int> memo;

// Function declarations
int exchangeCoinsBruteForce(int target, vector<int> &coins);
int exchangeCoinsGreedy(int target, vector<int> &coins);
vector<pair<string, int>> jobScheduleBruteForce(vector<pair<string, int>> &tasks);
vector<pair<string, int>> jobScheduleGreedy(vector<pair<string, int>> &tasks);
int knapsackBruteForce(vector<int>& weights, vector<int>& profits, int n, int capacity);
// Implemented functions
int knapsackGreedyByProfit(vector<int>& weights, vector<int>& profits, int n, int capacity);
int knapsackGreedyByWeight(vector<int>& weights, vector<int>& profits, int n, int capacity);
int knapsackGreedyByDensity(vector<int>& weights, vector<int>& profits, int n, int capacity);


int main()
{
    while (true)
    {
        int choice;
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
        {
            int method_choice;
            cout << "\n---------------------\n";
            cout << "Choose method:\n";
            cout << "---------------------\n";
            cout << "1. Brute Force\n";
            cout << "2. Greedy\n";
            cout << "---------------------\n";
            cout << "Enter your choice: ";
            cin >> method_choice;

            int coinCount;
            cout << "\nEnter the number of coins: ";
            cin >> coinCount;

            cout << "Enter the values of coins: ";
            vector<int> coins(coinCount);
            for (int i = 0; i < coinCount; ++i)
            {
                cin >> coins[i];
            }

            int amount;
            cout << "Enter the amount of Exchange: ";
            cin >> amount;

            switch (method_choice)
            {
            case 1:
                cout << "\nBrute Force Solution: " << exchangeCoinsBruteForce(amount, coins) << endl;
                break;
            case 2:
                cout << "\nGreedy Solution: " << exchangeCoinsGreedy(amount, coins) << endl;
                break;
            default:
                cout << "Invalid method choice.\n";
            }
            break;
        }

        case 2:
        {
            int method_choice;
            cout << "\n---------------------\n";
            cout << "Choose method:\n";
            cout << "---------------------\n";
            cout << "1. Brute Force\n";
            cout << "2. Greedy\n";
            cout << "---------------------\n";
            cout << "Enter your choice: ";
            cin >> method_choice;

            int jobCount;
            cout << "\nEnter the number of tasks: ";
            cin >> jobCount;

            vector<pair<string, int>> tasks(jobCount);
            cout << "Enter task (format 'name_task duration' separated by space):\n";
            for (int i = 0; i < jobCount; ++i)
            {
                cin >> tasks[i].first >> tasks[i].second;
            }

            switch (method_choice)
            {
            case 1:
            {
                vector<pair<string, int>> minSchedule = jobScheduleBruteForce(tasks);

                cout << "\nBrute Force Solution:\n";
                for (const auto &task : minSchedule)
                {
                    cout << task.first << " ";
                }
                int minWaitTime = 0;
                for (int i = 0; i < minSchedule.size(); ++i)
                {
                    int currentTime = 0;
                    for (int j = 0; j <= i; ++j)
                    {
                        currentTime += minSchedule[j].second;
                    }
                    minWaitTime += max(0, currentTime - minSchedule[i].second) - 1;
                }
                cout << "\nTotal Wait Time: " << minWaitTime << " hours\n";
                break;
            }

            case 2:
            {
                vector<pair<string, int>> minSchedule = jobScheduleGreedy(tasks);

                cout << "\nGreedy Solution:\n";
                for (const auto &task : minSchedule)
                {
                    cout << task.first << " ";
                }
                int minWaitTime = 0;
                for (int i = 0; i < minSchedule.size(); ++i)
                {
                    int currentTime = 0;
                    for (int j = 0; j <= i; ++j)
                    {
                        currentTime += minSchedule[j].second;
                    }
                    minWaitTime += max(0, currentTime - minSchedule[i].second) - 1;
                }
                cout << "\nTotal Wait Time: " << minWaitTime << " hours\n";
                break;
            }

            default:
                cout << "Invalid method choice.\n";
            }
            break;
        }

        case 3:
        {
            int method_choice;
            cout << "\n---------------------\n";
            cout << "Choose method:\n";
            cout << "---------------------\n";
            cout << "1. Brute Force\n";
            cout << "2. Greedy by profit\n";
            cout << "3. Greedy by weight\n";
            cout << "4. Greedy by density\n";
            cout << "---------------------\n";
            cout << "Enter your choice: ";
            cin >> method_choice;

            vector<int> weights, profits;
            int n, capacity;

            switch (method_choice)
            {
            case 1: // Brute Force
            {
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

                // Brute Force Knapsack
                int maxProfitBF = knapsackBruteForce(weights, profits, n, capacity);
                cout << "Maximum profit using Brute Force: " << maxProfitBF << endl;

                break;
            }
            case 2: // Greedy by profit
            {
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

                // Greedy by Profit Knapsack
                int maxProfitGP = knapsackGreedyByProfit(weights, profits, n, capacity);
                cout << "Maximum profit using Greedy by Profit: " << maxProfitGP << endl;

                break;
            }
            case 3: // Greedy by weight
            {
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

                // Greedy by Weight Knapsack
                int maxProfitGW = knapsackGreedyByWeight(weights, profits, n, capacity);
                cout << "Maximum profit using Greedy by Weight: " << maxProfitGW << endl;

                break;
            }
            case 4: // Greedy by density
            {
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

                // Greedy by Density Knapsack
                int maxProfitGD = knapsackGreedyByDensity(weights, profits, n, capacity);
                cout << "Maximum profit using Greedy by Density: " << maxProfitGD << endl;

                break;
            }
            default:
                cout << "Invalid choice.\n";
            }
            break;
        }

        case 4:
            cout << "Exiting program...\n";
            return 0;
        default:
            cout << "Invalid choice.\n";
        }
    }

    return 0;
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

// Function implementations for Knapsack problem (replace existing placeholders)
int knapsackGreedyByProfit(vector<int>& weights, vector<int>& profits, int n, int capacity) {
  // Calculate total weight of all items
  int totalWeight = 0;
  for (int weight : weights) {
    totalWeight += weight;
  }

  // Sort profits in decreasing order (assuming profits vector)
  sort(profits.begin(), profits.end(), greater<int>());

  int totalProfit = 0;
  int remainingCapacity = capacity;

  for (int profit : profits) {
    int itemIndex = find(profits.begin(), profits.end(), profit) - profits.begin();
    if (weights[itemIndex] <= remainingCapacity) {
      totalProfit += profit;
      remainingCapacity -= weights[itemIndex];

      // Display individual profit contribution (x)
      cout << "Profit added: " << profit << endl;
    } else {
      // Skip to next iteration if exceeding capacity
      continue;
    }
  }
  return totalProfit;
}



int knapsackGreedyByWeight(vector<int>& weights, vector<int>& profits, int n, int capacity) {
    vector<pair<int, int>> weightProfit(n); // Use pair<int, int> for weight and profit
    for (int i = 0; i < n; ++i)
        weightProfit[i] = {weights[i], profits[i]};

    // Sort by weight in ascending order (smallest to largest)
    sort(weightProfit.begin(), weightProfit.end());

    int totalWeight = 0;
    int totalProfit = 0;
    for (int i = 0; i < n; ++i) {
        if (weightProfit[i].first <= capacity) {
            totalWeight += weightProfit[i].first;
            totalProfit += weightProfit[i].second;
            capacity -= weightProfit[i].first;
        } else {
            break;
        }
    }

    return totalProfit;
}

int knapsackGreedyByDensity(vector<int>& weights, vector<int>& profits, int n, int capacity) {
    vector<pair<double, int>> density;

    for (int i = 0; i < n; ++i)
        density.push_back(make_pair((double)profits[i] / weights[i], i));

    // Sort in decreasing order of density
    sort(density.begin(), density.end(), greater<pair<double, int>>());

    int totalWeight = 0;
    int totalProfit = 0;
    for (int i = 0; i < n; ++i) {
        int index = density[i].second;
        if (weights[index] <= capacity) {
            totalWeight += weights[index];
            totalProfit += profits[index];
            capacity -= weights[index];
        } else {
            break;
        }
    }

    return totalProfit;
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
