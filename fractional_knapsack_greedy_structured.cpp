/**
 * @file fractional_knapsack_greedy_structured.cpp
 * @author Mohamad Syafiq Asyraf Bin Bharudin (https://github.com/binaryassasins)
 * @brief This program is an implementation of fractional knapsack using greedy algorithm
 * @version 0.1
 * @date 2023-05-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <cstdlib>

using namespace std;

int total_value = 0;

void verifyTotalWeight (double* bag, double* weight, int n) {
  double totWeight = 0.0;
  for (int i = 0; i < n; i++) {
    totWeight += (bag[i] * weight[n-i]);
  }
  cout << "Total Weight: " << totWeight << endl;
}

double bagValue(double capacity, double* weight, double* value, int n, double* bag) {
  // check if the first item weight is < capacity or not
  int i = 0;
  while (true) {
    // if there is remaining capacity that is currently free, then insert the next item which has the value per weight
    if (capacity < weight[(n-1)-i]) {
      // insert into bag
      bag[i] = capacity/weight[(n-1)-i];
      // calculate the total value
      ::total_value += (bag[i] * value[(n-1)-i]); 
      break;
    } else {
      // insert whole item
      bag[i] = 1.0;
      capacity -= weight[(n-1)-i];
      // calculate the total value
      ::total_value += (bag[i] * value[(n-1)-i]); 
      i++;
    }
  }
  cout << "ITEM\tINCLUDE" << endl;
  for (int i = 0; i < n; i++) {
    cout << i+1 << "\t" << bag[i] << endl;
  }
  cout << endl;
  verifyTotalWeight (bag, weight, n-1);
  return total_value;
}

void sort(double* val_per_weight, double* weight, double* value, int n) {
  int i, j, temp_val_per_weight = 0, temp_weight = 0, temp_value = 0;
  for (i = 0; i < n; i++) {
    for (j = i+1; j < n; j++) {
      if (val_per_weight[i] > val_per_weight[j]) {
        temp_val_per_weight = val_per_weight[i];
        temp_weight = weight[i];
        temp_value = value[i];
        
        val_per_weight[i] = val_per_weight[j];
        weight[i] = weight[j];
        value[i] = value[j];

        val_per_weight[j] = temp_val_per_weight;
        weight[j] = temp_weight;
        value[j] = temp_value;
      }
    }
  }
}

// calculate value per weight for each item using recursion
void calcValuePerWeight(double* val_per_weight, double* weight, double* value, int n) {
  if (n < 0) {
    return;
  }
  val_per_weight[n] = value[n] / weight[n];
  calcValuePerWeight(val_per_weight, weight, value, n-1);
}

int knapsack(double capacity, double* weight, double* value, int n) {
  // declare bag
  double bag[n] = {};
  // declare an array to store value per weight
  double val_per_weight[n] = {};
  calcValuePerWeight(val_per_weight, weight, value, n-1);

  cout << "Knapsack Capacity: " << capacity << "\n\nITEM\tWEIGHT\tVALUE\tVALUE_PER_WEIGHT" << endl;
  for (int i = 0; i < n; i++) {
    cout << i+1 << "\t" << weight[i] << "\t" << "$" << value[i] << "\t" << "$" << val_per_weight[i] << endl;
  }
  cout << endl;  

  sort(val_per_weight, weight, value, n);
  return bagValue(capacity, weight, value, n, bag);
}

int main() {
  double capacity = 16;
  double weight[] = {2, 5, 10, 5};
  double value[] = {20, 30, 50, 10};
  // calculate the size of array
  int n = sizeof(weight) / sizeof(weight[0]);
  int total_value = 0;
  total_value = knapsack(capacity, weight, value, n);  

  cout << "Total Value: " << total_value << endl;
  system("pause");
  return 0;
}