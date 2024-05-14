#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>

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

struct Item
{
  int value;
  int weight;
  double density;
};

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

//--------------------------------------------
// KNAPSACK PROBLEM
//--------------------------------------------
void generateCombinations(int index, int itemCount, vector<int> &currentCombination, vector<vector<int>> &combinations)
{
  if (index == itemCount)
  {
    combinations.push_back(currentCombination);
    return;
  }

  currentCombination[index] = 1;
  generateCombinations(index + 1, itemCount, currentCombination, combinations);

  currentCombination[index] = 0;
  generateCombinations(index + 1, itemCount, currentCombination, combinations);
}

int knapsackBruteForce(int capacity, Item items[], int itemCount, vector<Item> &selectedItems)
{
  vector<vector<int>> combinations;
  vector<int> currentCombination(itemCount, 0);
  generateCombinations(0, itemCount, currentCombination, combinations);

  int maxValue = 0;
  vector<Item> tempSelectedItems;

  for (const auto &combination : combinations)
  {
    int totalWeight = 0;
    int totalValue = 0;
    tempSelectedItems.clear();

    for (int i = 0; i < itemCount; ++i)
    {
      if (combination[i])
      {
        totalWeight += items[i].weight;
        totalValue += items[i].value;
        tempSelectedItems.push_back(items[i]);
      }
    }

    if (totalWeight <= capacity && totalValue > maxValue)
    {
      maxValue = totalValue;
      selectedItems = tempSelectedItems;
    }
  }

  return maxValue;
}

int knapsackGreedyByProfit(int capacity, Item items[], int itemCount, vector<Item> &selectedItems)
{
  sort(items, items + itemCount, [](const Item &a, const Item &b)
       { return a.value > b.value; });

  int totalValue = 0;
  int totalWeight = 0;

  for (int i = 0; i < itemCount; ++i)
  {
    if (totalWeight + items[i].weight <= capacity)
    {
      totalValue += items[i].value;
      totalWeight += items[i].weight;
      selectedItems.push_back(items[i]);
    }
  }
  return totalValue;
}

int knapsackGreedyByWeight(int capacity, Item items[], int itemCount, vector<Item> &selectedItems)
{
  sort(items, items + itemCount, [](const Item &a, const Item &b)
       { return a.weight < b.weight; });

  int totalValue = 0;
  int totalWeight = 0;

  for (int i = 0; i < itemCount; ++i)
  {
    if (totalWeight + items[i].weight <= capacity)
    {
      totalValue += items[i].value;
      totalWeight += items[i].weight;
      selectedItems.push_back(items[i]);
    }
    else
    {
      break;
    }
  }

  // Sort selectedItems based on item value
  sort(selectedItems.begin(), selectedItems.end(), [](const Item &a, const Item &b){ 
    return a.value < b.value; 
    });

  return totalValue;
}


int knapsackGreedyByDensity(int capacity, Item items[], int itemCount, vector<Item> &selectedItems)
{
  for (int i = 0; i < itemCount; ++i)
  {
    items[i].density = (double)items[i].value / items[i].weight;
  }

  sort(items, items + itemCount, [](const Item &a, const Item &b)
       {
        if (a.density != b.density) {
            return a.density > b.density;
        }
        else {
            return a.value > b.value;
        } });

  int totalValue = 0;
  int totalWeight = 0;

  for (int i = 0; i < itemCount; ++i)
  {
    if (totalWeight + items[i].weight <= capacity)
    {
      totalValue += items[i].value;
      totalWeight += items[i].weight;
      selectedItems.push_back(items[i]);
    }
  }
  return totalValue;
}

void getInputForKnapsackProblem(int &capacity, int &itemCount, Item items[], int &method_choice)
{
  cout << "\nEnter the capacity of the knapsack: ";
  cin >> capacity;

  cout << "Enter the number of items: ";
  cin >> itemCount;

  cout << "Enter the value and weight of each item:\n";
  for (int i = 0; i < itemCount; ++i)
  {
    cout << "Item " << i + 1 << " value: ";
    cin >> items[i].value;
    cout << "Item " << i + 1 << " weight: ";
    cin >> items[i].weight;
  }

  cout << "\n---------------------\n";
  cout << "Choose method:\n";
  cout << "---------------------\n";
  cout << "1. Brute Force\n";
  cout << "2. Greedy by Profit\n";
  cout << "3. Greedy by Weight\n";
  cout << "4. Greedy by Density\n";
  cout << "---------------------\n";
  cout << "Enter your choice: ";
  cin >> method_choice;
}

//--------------------------------------------
// MAIN PROGRAM
//--------------------------------------------
int main()
{
  int choice;
  int coinCount, amount, method_choice;
  int taskCount;
  int capacity, itemCount;
  int coins[SIZE];
  Task tasks[SIZE];
  Item items[SIZE];
  int solution;
  int maxValue;
  vector<Item> selectedItems;

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
      getUserInputCoin(&coinCount, coins, &amount, &method_choice);
      solution = chooseMethod(amount, coins, coinCount, method_choice);
      if (solution != -1)
      {
        displayExchange(solution);
      }
      break;
    case 2:
      getUserInputCoinTasks(&taskCount, tasks, &method_choice);
      switch (method_choice)
      {
      case 1:
        bruteForceSchedule(tasks, taskCount);
        displaySchedule(tasks, taskCount, "Brute Force");
        break;
      case 2:
        greedySchedule(tasks, taskCount);
        displaySchedule(tasks, taskCount, "Greedy");
        break;
      default:
        cout << "Invalid method choice.\n";
      }
      break;
    case 3:
      // Reset selectedItems
      selectedItems.clear();
      // Reset maxValue
      maxValue = 0;
      getInputForKnapsackProblem(capacity, itemCount, items, method_choice);
      switch (method_choice)
      {
      case 1:
        maxValue = knapsackBruteForce(capacity, items, itemCount, selectedItems);
        break;
      case 2:
        maxValue = knapsackGreedyByProfit(capacity, items, itemCount, selectedItems);
        break;
      case 3:
        maxValue = knapsackGreedyByWeight(capacity, items, itemCount, selectedItems);
        break;
      case 4:
        maxValue = knapsackGreedyByDensity(capacity, items, itemCount, selectedItems);
        break;
      default:
        cout << "Invalid choice.\n";
        return 1;
      }
      cout << "\nTotal Value: " << maxValue << endl;
      cout << "Selected Items: ";
      for (int i = 0; i < selectedItems.size(); ++i)
      {
        cout << "Item " << i + 1 << " (" << selectedItems[i].value << ") ";
        if (i != selectedItems.size() - 1)
          cout << ", ";
      }
      cout << "\n";
      break;
    case 4:
      cout << "Exiting program... Thank You...\n";
      return 0;
    default:
      cout << "Invalid menu. Please enter a valid menu.\n";
    }
  }

  return 0;
}
