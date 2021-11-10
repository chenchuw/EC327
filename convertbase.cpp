// Copyright 2020 Chuwei Chen chenchuw@bu.edu

#include<iostream>
#include<string>

using std::cin;
using std::cout;
using std::string;

string convertbase(const string& numstr, const int frombase, const int tobase) {
  int digit_base10 = 0, power = 1, i, loop, bit, rest;
  string newbasedigit;
  char c;
  // 1. convert string from whatever base to base 10
  for (i = numstr.size() - 1; i >= 0; i--) {
    digit_base10 += (numstr[i] - '0') * power;
    power = power * frombase;
  }

  // 2. convert digit_base10 to digit_newbase
  loop = digit_base10;
  cout << digit_base10 <<"\n";
  while (loop > 0) {
    bit = loop % tobase;
    rest = loop / tobase;
    loop = rest;
    c = bit + '0';
    cout << "c is "<< c << "\n";
    newbasedigit = c + newbasedigit;
  }
  return newbasedigit;
}


int main() {
  string n;
  n = convertbase("10110", 5, 12);
  cout << n << "\n";
}

