// Copyright 2020 Chuwei Chen chenchuw@bu.edu
// Working principle:
// After conducting the happy number calculation,
// happy number will result in 1
// unhappy number will result in 4

#include <iostream>
using std::cin;
using std::cout;

int happycalculator(int num) {
  int rem = 0, sum = 0;

  while (num > 0) {
    rem = num % 10;
    sum = sum + (rem * rem);
    num = num / 10;
  }
  return sum;
}

int main() {
  int num;
  while (true) {
    cin >> num;
    int result = num;

    if (num == 0) {
      return 0;
    } else if (num < 1 || num > 2147483647) {
      cout << "Try again, give a number between 1 and 2147483647";
    } else {
      
      while (result != 1 && result != 4) {
        result = happycalculator(result);
      }

      if (result == 1)
        cout << num << " is happy\n";
      else if (result == 4)
        cout << num << " is not happy\n";
    }
  }
}
