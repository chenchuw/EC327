// Copyright 2020 Chuwei Chen chenchuw@bu.edu
// To-do list
// 1. get input between 2 and 2147483647.
// 2. use iteration to find all divisors
// 3. calculate the sum of the divisors
// 4. print out everything in order
// cout << "Welcome, this is the divisorsum calculator!\n";
// cout << "Please type in the number
// cout << that you need its divisors & the sum.\n";
// cout << "(between 2 and 2147483647)\n";
// cout << "Enter 0 if you want to exit.\n";
#include<cstdint>
#include<iostream>

using std::cout;

double i, a;
int64_t sum, n;

int main() {
  while (true) {
    std::cin >> n;

    if (2 <= n && n <= 2147483647) {
      cout << n << ": " << "1";
      for (i = 1; i < n; i++) {
        a = n / i;
        if (a == static_cast<int>(a)) {
          sum = i + sum;
          if (i != 1) {
            cout << "+" << static_cast<int>(i);
          }
        }
      }
      cout << " = " << sum << "\n";
      sum = 0;
    } else if (n == 0) {
      return 0;
    } else {
      cout << "Try again! Please pick between 2 and 2147483647.\n";
    }
  }
}
