// Copyright 2020 Chuwei Chen chenchuw@bu.edu
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "timer.h"

using std::vector;
using std::string;
using std::cout;
using std::sort;

class Arrangements {
 private:
  // your private data
  int max_size;
  string names;
  vector<string> a, b, arrangements;

 public:
  // more stuff here. data and methods

  Arrangements() {
    names = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    max_size = names.size();
  }

  explicit Arrangements(string thenames) {
    max_size = thenames.size();
    names = thenames;
  }

  vector<string> panel_shuffles(int n) {
    // Error handling
    if (n > max_size) throw n;
    // names is the input string and n is input size
    // If n==0, n==1 or n==2, return the particular results.
    if (n == 0) return {""};

    if (n == 1) {
      string s = {names.at(0)};
      return vector<string>() = {s};
    }
    if (n == 2) {
      string s1, s2;
      s1 += names.at(0);
      s1 += names.at(1);
      s2 += names.at(1);
      s2 += names.at(0);
      return vector<string>() = {s1, s2};
    }

    vector<vector<string>> all;
    string s1, s2;

    s1 += names.at(0);
    arrangements = {s1};
    all.push_back(arrangements);

    s1 = "";
    s1 += names.at(0);
    s1 += names.at(1);
    s2 += names.at(1);
    s2 += names.at(0);
    arrangements = {s1, s2};
    all.push_back(arrangements);

    for (int i = 2; i < n; i++) {
      a = all.at(i - 2);
      b = all.at(i - 1);

      arrangements.clear();
      for (int j = 0; j < a.size(); j++) {
        string s = "";
        s += a.at(j);
        s += names.at(i);
        s += names.at(i - 1);
        arrangements.push_back(s);
      }

      for (int k = 0; k < b.size(); k++) {
        string s = "";
        s += b.at(k);
        s += names.at(i);
        arrangements.push_back(s);
      }
      all.push_back(arrangements);
    }
    // View the 2-D vector
    // for (int i = 0; i < all.size(); i++) {
    //     for (int j = 0; j < all.at(i).size(); j++)
    //         cout << all.at(i).at(j) << " ";
    //     cout << endl;
    // }

    return arrangements;
  }

  double panel_count(int n) {  // use fibonacchi appoach
    if (n > max_size) throw n;
    vector <double> v = {1, 1};

    if (n == 0) return 0;
    if (n == 1) return 1;

    for (double i = 2; i <= n; i++) {
      double newarrangements = v.at(i - 1) + v.at(i - 2);
      v.push_back(newarrangements);
    }

    return v.at(n);
  }

  vector<string> dinner_shuffles(int n) {
    // Error handling
    if (n > max_size) throw n;
    vector<string> dinner_arrangements;
    // names is the input string and n is input size
    // If n==0, n==1 or n==2, return the particular results.
    if (n == 0) return {""};
    if (n == 1) {
      string s = {names.at(0)};
      dinner_arrangements.push_back(s);
      return dinner_arrangements;
    }
    if (n == 2) {
      string s1, s2;
      s1 += names.at(0);
      s1 += names.at(1);
      s2 += names.at(1);
      s2 += names.at(0);
      dinner_arrangements = {s1, s2};
      return dinner_arrangements;
    }

    // dinner_arrangements contain 3 cases.
    // 1. COPY PANEL: panel_shuffles.at(n)  --  panel_count(n) arrangements
    // 2. Head tail swap: "names.at(i)+panel.at(n-2)+names.at(0)"
    //    --  panel_count(n-2) arrangements
    // 3: mv left and mv right  --  2 arrangements

    dinner_arrangements = panel_shuffles(n);  // case 1
    string dinner_move = names.substr(0, n);

    // case 3
    std::rotate(dinner_move.begin(),
                dinner_move.begin() + 1, dinner_move.end());
    dinner_arrangements.push_back(dinner_move);
    std::rotate(dinner_move.begin(),
                dinner_move.begin() + n - 2, dinner_move.end());
    dinner_arrangements.push_back(dinner_move);

    vector<string> case2_middle =  panel_shuffles(n - 2);  // case 2
    string new_char = {names.at(n - 1)};
    string first_char = {names.at(0)};
    int found;
    for (int i = 0; i < case2_middle.size(); i++) {
      string s = case2_middle.at(i);
      for (int j = 0; j < s.size(); j++) {
        found = names.find(s.at(j));
        string str = {names.at(found + 1)};
        case2_middle.at(i).replace(j, 1, str);
      }
      case2_middle.at(i).append(first_char);
      case2_middle.at(i).insert(0, new_char);
      dinner_arrangements.push_back(case2_middle.at(i));
    }

    return dinner_arrangements;
  }

  double dinner_count(int n) {
    if (n > max_size) throw n;
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;
    return (panel_count(n) + panel_count(n - 2) + 2);
  }

  // more methods if you want
};

// Methods and constructors defined here:

// TESTING: leave this line and below as is.

void show_result(vector<string> v) {
  sort(v.begin(), v.end());
  for (auto c : v)
    cout << c << "\n";
  cout << "\n";
}

void show_partial_result(string testname, vector<string> res, int n) {
  if (res.empty()) return;

  sort(res.begin(), res.end());

  std::vector<uint64_t> locs{0, res.size() / 3,
                             2 * res.size() / 3, res.size() - 1};
  std::cout << "\n" << testname << " " << n << "\n";
  for (auto i : locs) {
    std::cout << " res.at(" << i
              << ") = " << res.at(i) << "\n";
  }
}


const int COUNTLIM = 100;
const int COUNTLIM_SMALL = 30;

void standard_tests();
void alternate_tests();
void interactive_main();

int main(int argc, char const ** argv) {
  if (argc > 1 and string(*(argv + 1)) == "alt")
    alternate_tests();
  else if (argc > 1 and (string(*(argv + 1)) == string("int")))
    interactive_main();
  else
    standard_tests();
}

// tests to be run for full credit, including performance.
void standard_tests() {
  int n;

  cout.precision(15);

  // Basic test
  Arrangements standard;

  cout << "\nPanel Shuffles for 4 panelists.\n";
  show_result(standard.panel_shuffles(4));

  cout << "\nDinner Shuffles for 4 guests.\n";
  show_result(standard.dinner_shuffles(4));

  // Test other names
  Arrangements numbers("123456789");
  Arrangements symbols("!@#$%^&*()_+");

  std::array<Arrangements*, 3> v{&standard, &numbers, &symbols};

  cout << "\nPanel Shuffles for 6 panelists, 3 sets of names.\n";
  for (auto arr : v)
    show_result(arr->panel_shuffles(6));

  cout << "\nDinner Shuffles for 6 guests, 3 sets of names.\n";
  for (auto arr : v)
    show_result(arr->dinner_shuffles(6));

  // Count tests
  Arrangements large(string(COUNTLIM, 'a'));

  Timer t_pc("panel count", true);
  n = 1;
  cout << "\nPanel Shuffle Count Table (0.1 seconds)\n";
  cout << "     N  panel(N)\n";

  while (n < COUNTLIM and t_pc.time() < 0.1) {
    t_pc.start();
    double pc = large.panel_count(n);
    t_pc.stop();
    cout << std::setw(6) << n << " "
         << std::setw(6) << pc << "\n";
    n++;
  }


  Timer t_dc("dinner count", true);
  n = 1;
  cout << "\nDinner Shuffle Count Table (0.1 seconds)\n";
  cout << "     N  dinner(N)\n";

  while (n < COUNTLIM and t_dc.time() < 0.1) {
    t_dc.start();
    double dc = large.dinner_count(n);
    t_dc.stop();
    cout << std::setw(6) << n << " "
         << std::setw(6) << dc << "\n";
    n++;
  }

  Timer t_panel("panel", true);
  n = 4;
  cout << "\nHow many panel shuffles can be created in 0.5 seconds?\n";

  while (t_panel.time() < 0.5)  {
    double last = t_panel.time();
    t_panel.start();
    vector<string> res = standard.panel_shuffles(n);
    t_panel.stop();
    show_partial_result("panel", res, n);
    cout << "time " << t_panel.time() - last << "\n";
    n++;
  }

  int largest_panel = n - 1;

  Timer t_dinner("dinner timing", true);
  n = 4;
  cout << "\nHow many dinner shuffles can be created in 0.5 seconds?\n";

  while (t_dinner.time() < 0.5)  {
    double last = t_dinner.time();
    t_dinner.start();
    vector<string> res = standard.dinner_shuffles(n);
    t_dinner.stop();
    show_partial_result("dinner", res, n);
    cout << "time " << t_dinner.time() - last << "\n";
    n++;
  }
  cout << "\nLargest panel shuffles performed: "
       << largest_panel << "\n";
  cout << "\nLargest dinner shuffles performed: " << n - 1 << "\n";

  // Error checking
  Arrangements small("abcd");
  cout << "\nError Handling Tests\n";

  try {
    small.panel_count(5);
  } catch (int n) {
    cout << n;
  }
  try {
    small.panel_shuffles(6);
  } catch (int n) {
    cout << n;
  }
  try {
    small.dinner_count(7);
  } catch (int n) {
    cout << n;
  }
  try {
    small.dinner_shuffles(89);
  } catch (int n) {
    cout << n;
  }
  try {
    large.dinner_shuffles(122);
  } catch (int n) {
    cout << n;
  }
  try {
    numbers.dinner_shuffles(9);
  } catch (int n) {
    cout << n;
  }
  try {
    numbers.dinner_shuffles(10);
  } catch (int n) {
    cout << n;
  }
  cout << "\n";
}

void alternate_tests() {
  cout.precision(15);
  // Basic test
  Arrangements standard;

  cout << "\nPanel Shuffles for 4 panelists.\n";
  show_result(standard.panel_shuffles(4));

  cout << "\nPanel Shuffles for 10 panelists.\n";
  show_result(standard.panel_shuffles(10));

  int n = 1;

  // Count tests
  Timer t_pc("panel count", true);
  cout << "\nPanel Shuffle Count Table (0.1 seconds)\n";
  cout << "     N  panel(N)\n";
  while (n < 52 and t_pc.time() < 0.1) {
    t_pc.start();
    double pc = standard.panel_count(n);
    t_pc.stop();
    cout << std::setw(6) << n << " "
         << std::setw(6) << pc << "\n";
    n++;
  }

  cout << "\nHow many panel shuffles can be created in 0.5 seconds?\n";
  n = 4;

  Timer t_panel("panel", true);

  while (t_panel.time() < 0.5)  {
    t_panel.start();
    vector<string> res = standard.panel_shuffles(n);
    t_panel.stop();
    show_partial_result("panel", res, n);
    n++;
  }
  cout << "\nLargest panel shuffles performed: "
       << n - 1 << "\n";
}


void interactive_main() {
  std::string asktype, symbols;
  int number;
  cout << "Type quit to exit.\n";
  cout << "Commands:\npc names n\nps names n\ndc names n\nds names n\n";
  cout.precision(15);

  while (true) {
    std::cin >> asktype;
    if (asktype == "quit") break;
    std::cin >> symbols;
    Arrangements h(symbols);
    std::cin >> number;
    if (asktype == "pc") {
      std::cout << "panel_count(" << number <<  ") = ";
      std::cout << h.panel_count(number) << "\n";
    } else if (asktype == "ps") {
      std::cout << "panel_shuffles(" << number <<  ") = ";
      for (auto e : h.panel_shuffles(number) )
        std::cout << e << " ";
      std::cout << "\n";
    } else if (asktype == "dc") {
      std::cout << "dinner_count(" << number << ") = ";
      std::cout << h.dinner_count(number) << "\n";
    } else if (asktype == "ds") {
      std::cout << "dinner_shuffles(" << number <<  ") = ";
      for (auto e : h.dinner_shuffles(number))
        std::cout << e << " ";
      std::cout << "\n";
    }
  }
}
