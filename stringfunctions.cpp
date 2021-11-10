// Copyright 2020 Chuwei Chen chenchuw@bu.edu
// Copyright 2020 Hanming Wang hita@bu.edu

// stringfunctions_original.cpp is a template
//
// make a copy of this file to stringfunctions.cpp to submit.
//
// error  output  is coded as follows:

// w - is_word
// p - is_palindrome
// a - add
// c - convertbase
// m - multibase

#include <iostream>
#include <string>
using std::string;
using std::cerr;
using std::cout;
using std::cin;


bool is_word(string s) {
  int size = s.size();
  if (size <= 0) return false;
  char first = s.at(0);
  if (!isalpha(first)) return false;
  if (size == 1) return true;
  char second = s.at(1);
  if (islower(first)) {
    // lower case
    for (int i = 1; i < size; ++i) {
      if (!islower(s.at(i))) return false;
    }
    return true;
  } else if (isupper(second)) {
    // upper case
    for (int i = 1; i < size; ++i) {
      if (!isupper(s.at(i))) return false;
    }
    return true;
  } else if (islower(second)) {
    // capitalized
    for (int i = 2; i < size; ++i) {
      if (!islower(s.at(i))) return false;
    }
    return true;
  } else {
    return false;
  }
}



bool is_palindrome(string num, bool * error) {
  int size = num.size();
  if (size <= 0) {
    *error = true;
    return false;
  }
  if (size == 1) {
    if (!isdigit(num.at(0))) {
      *error = true;
      return false;
    } else {
      *error = false;
      return true;
    }
  }
  if (!isdigit(num.at(0)) or num.at(0) == '0') {
    *error = true;
    return false;
  }
  for (int i = 0; i < size; ++i) {
    if (!isdigit(num.at(i))) {
      *error = true;
      return false;
    }
  }
  int sum = size - 1;
  for (int i = 0; i < size / 2; ++i) {
    if (num.at(i) != num.at(sum - i)) {
      *error = false;
      return false;
    }
  }
  *error = false;
  return true;
}


string add(const string& num1, const string& num2) {
  string out = "";
  int x, y, sum = 0, carry = 0;
  string a = num1, b = num2;
  while (a.length() != 0 or b.length() != 0) {
    (a.length() > 0) ? x = (a.back() - '0') : x = 0;
    (b.length() > 0) ? y = (b.back() - '0') : y = 0;
    sum = x + y + carry;
    if (sum >= 10) {
      sum = sum - 10;
      carry = 1;
    } else {
      carry = 0;
    }
    string temp = std::to_string(sum);
    out = temp + out;
    if (a.length() > 0) a.pop_back();
    if (b.length() > 0) b.pop_back();
  }
  if (carry == 1) out = "1" + out;
  return out;
}


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
  while (loop > 0) {
    bit = loop % tobase;
    rest = loop / tobase;
    loop = rest;
    c = bit + '0';
    newbasedigit = c + newbasedigit;
  }
  return newbasedigit;
}

string multibase(int x) {
  int loop, bit, rest;
  string newbasedigit, multibase;
  char c;
  for (int i = 2; i <= x - 1; i++) {
    // convert digit_base10 to digit_newbase
    loop = x;
    while (loop > 0) {
      bit = loop % i;
      rest = loop / i;
      loop = rest;
      c = bit + '0';
      newbasedigit = c + newbasedigit;
    }

    if (newbasedigit == string(newbasedigit.rbegin(), newbasedigit.rend())) {
      multibase = multibase + std::to_string(i) + " ";
    }

    newbasedigit = "";
  }
  multibase.pop_back();
  return multibase;
}

// leave this line and everything below as is
int main() {
  bool error;

  cerr << std::boolalpha;
  cout << std::boolalpha;

  // is_word basic tests
  if (not is_word("test")) cerr << "we1\n";
  if (not is_word("Test")) cerr << "we2\n";
  if (not is_word("TEST")) cerr << "we3\n";
  if (not is_word("thisisaword")) cerr << "we4\n";

  if (is_word("123")) cerr << "we5\n";
  if (is_word("")) cerr << "we6\n";
  if (is_word("abc123abc")) cerr << "we7\n";
  if (is_word("tEst")) cerr << "we8\n";
  if (is_word("tEst")) cerr << "we9\n";
  if (is_word("TESTer")) cerr << "we10\n";


  // is_palindrome basic tests
  if (not is_palindrome("12321", &error) or error) cerr << "pe1\n";
  if (not is_palindrome("9009", &error) or error) cerr  << "pe2\n";
  if (not is_palindrome("9", &error) or error)  cerr << "pe3\n";
  if (not is_palindrome("123456777654321", &error) or error) cerr << "pe4\n";

  if (is_palindrome("abcba", &error) or not error) cerr << "pe5\n";
  if (is_palindrome("12321 a", &error) or not error) cerr << "pe6\n";
  if (is_palindrome("0012100", &error) or not error) cerr << "pe7\n";

  if (is_palindrome("123", &error) or error) cerr << "pe8\n";
  if (is_palindrome("123211", &error) or error) cerr << "pe9\n";
  if (not is_palindrome("0", &error) or error)  cerr << "pe10\n";

  // add basic tests
  if (add("123", "456") != "579") cerr << "ae1\n";
  if (add("123", "4") != "127") cerr << "ae2\n";
  if (add("1234", "9") != "1243") cerr << "ae3\n";
  if (add("88", "12") != "100") cerr << "ae4\n";
  if (add("1234567890123456789", "10000000000000999")
      != "1244567890123457788") cerr << "ae5\n";

  string longone(120, '2');
  longone[0] = '3';
  string longother(123, '1');
  longother[0] = '4';
  longother[3] = '2';
  string longresult(123, '3');
  longresult[0] = '4';
  longresult[1] = '1';
  longresult[2] = '1';
  longresult[3] = '5';

  if (add(longone, longother) != longresult ) cerr << "ae6\n";

  // convertbase tests

  if (convertbase("1111", 2, 10) != "15" ) cerr << "ce1\n";
  if (convertbase("255", 10, 16) != "??")  cerr << "ce2\n";
  if (convertbase("755", 8, 2) != "111101101") cerr << "ce3\n";

  if (convertbase("987123", 30, 30) != "987123" ) cerr << "ce4\n";
  if (convertbase("azbc", 100, 10) != "49745051") cerr << "ce5\n";

  if (convertbase("azbc", 100, 2) != "10111101110000110010011011")
    cerr << "ce6\n";

  // multibase tests

  if (multibase(121) != "3 7 8 10 120") cerr << "me1\n";
  if (multibase(45) != "2 8 14 44") cerr << "me2\n";
  if (multibase(63) != "2 4 8 20 62") cerr << "me3\n";
  if (multibase(10) != "3 4 9") cerr << "me4\n";


  // ad-hoc tests from cin

  string asktype;
  bool res;
  string userinput, num1, num2;
  int mbase, frombase, tobase;



  while (cin >> asktype) {
    if (asktype == "w") {  // is_word
      std::cin >> userinput;
      cout << is_word(userinput) << "\n";
    } else if (asktype == "p") {  // p - is_palindrome
      std::cin >> userinput;
      res = is_palindrome(userinput, &error);
      cout << res << " " << error << "\n";
    } else if (asktype == "a") {  // a - add
      std::cin >> num1 >> num2;
      cout << add(num1, num2) << "\n";
    } else if (asktype == "c") {  // c - convertbase
      std::cin >> userinput >> frombase >> tobase;
      cout << convertbase(userinput, frombase, tobase) << "\n";
    } else if (asktype == "m") {  // m - multibase
      std::cin >> mbase;
      cout << multibase(mbase) << "\n";
    } else {
      return 0;
    }
  }
  return 0;
}
