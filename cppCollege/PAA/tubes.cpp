#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

// Brute Force Recursive Solution
void coinChangeUtilBF(std::vector<int>& coins, int amount, int& minCoins, std::vector<int>& result, std::vector<int>& current, int index) {
    if (amount == 0) {
        // Base case: amount is 0, calculate the total number of coins used
        int totalCoins = 0;
        for (int coin : current) {
            totalCoins += coin;
        }
        if (totalCoins < minCoins) {
            minCoins = totalCoins;
            result = current;
        }
        return;
    }
    
    for (int i = index; i < coins.size(); ++i) {
        if (coins[i] <= amount) {
            current.push_back(coins[i]);
            coinChangeUtilBF(coins, amount - coins[i], minCoins, result, current, i); // Recursive call
            current.pop_back(); // Backtrack
        }
    }
}

std::vector<int> coinChangeBruteForce(std::vector<int>& coins, int amount) {
    std::vector<int> result;
    std::vector<int> current;
    int minCoins = INT_MAX;
    coinChangeUtilBF(coins, amount, minCoins, result, current, 0);
    
    if (minCoins == INT_MAX) {
        // If it's not possible to make the exact amount with given coins
        return std::vector<int>{-1};
    } else {
        return result;
    }
}

// Greedy Solution
std::vector<int> coinChangeGreedy(std::vector<int>& coins, int amount) {
    std::sort(coins.rbegin(), coins.rend()); // Sort coins in descending order

    std::vector<int> result;
    for (int coin : coins) {
        while (amount >= coin) {
            result.push_back(coin);
            amount -= coin;
        }
    }

    if (amount == 0) {
        return result;
    } else {
        // If it's not possible to make the exact amount with given coins
        return std::vector<int>{-1};
    }
}

int main() {
    std::vector<int> coins = {1, 5, 10, 25};
    int amount = 0;
    int choice = 0;

    while (true) {
        std::cout << "Enter the amount for which you want to make change (enter 0 to exit): ";
        std::cin >> amount;

        if (amount == 0) {
            std::cout << "Exiting the program..." << std::endl;
            break;
        }

        std::cout << "Choose algorithm for making change:" << std::endl;
        std::cout << "1. Brute Force" << std::endl;
        std::cout << "2. Greedy" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::vector<int> changeBF = coinChangeBruteForce(coins, amount);
                if (changeBF[0] == -1) {
                    std::cout << "It's not possible to make exact change for " << amount << " using given coins." << std::endl;
                } else {
                    std::cout << "Brute Force Solution:" << std::endl;
                    std::cout << "Minimum coins needed: " << changeBF.size() << std::endl;
                    std::cout << "Coins used: ";
                    for (int coin : changeBF) {
                        std::cout << coin << " ";
                    }
                    std::cout << std::endl;
                }
                break;
            }
            case 2: {
                std::vector<int> changeGreedy = coinChangeGreedy(coins, amount);
                if (changeGreedy[0] == -1) {
                    std::cout << "It's not possible to make exact change for " << amount << " using given coins." << std::endl;
                } else {
                    std::cout << "Greedy Solution:" << std::endl;
                    std::cout << "Minimum coins needed: " << changeGreedy.size() << std::endl;
                    std::cout << "Coins used: ";
                    for (int coin : changeGreedy) {
                        std::cout << coin << " ";
                    }
                    std::cout << std::endl;
                }
                break;
            }
            default:
                std::cout << "Invalid choice! Please enter 1 or 2." << std::endl;
        }
    }

    return 0;
}