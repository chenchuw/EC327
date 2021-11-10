// Copyright 2020 Chuwei Chen chenchuw@bu.edu

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "timer.h"

using std::cout;
using std::vector;
using std::make_pair;
using std::unordered_map;

int convert_square(int num, int base) {
  int digit, sum = 0;
  while (num > 0) {
    digit = num % base;
    num = num / base;
    sum += (digit * digit);
  }
  return sum;
}

struct dizzyGenerator {
  vector<vector<int>> dizzymap;
  vector<int> dizzy_in_base;
  dizzyGenerator() {
    int num = 10, base = 11;
    for (int i = 2; i <= base; i++) {
      for (int j = 1; j <= num; j++) {
        if (isdizzy(j, i))
          dizzy_in_base.push_back(j);
      }
      dizzymap.push_back(dizzy_in_base);
      dizzy_in_base.clear();
    }

    // for (auto e : dizzymap){
    //   for (auto v : e)
    //     cout << v << " ";
    //   cout << endl;
    // }
  }

  bool isdizzy(int number, int base = 10) {
    std::vector<int> cycle = dizziness_cycle(number, base);
    return (cycle.size() == 1 and cycle.at(0) == 1);
  }

  std::vector<int> dizziness_cycle(int number, int base = 10) {
    unordered_map<int, int> all_pair;
    std::vector<int> allcycle;
    int sum_num = number;
    while (all_pair.find(sum_num) == all_pair.end()) {
      all_pair.insert(std::make_pair(sum_num, 1));
      allcycle.push_back(sum_num);
      sum_num = convert_square(sum_num, base);
      if (sum_num == 1) return {1};
    }
    int start = 0;
    for (int i = 0; i < allcycle.size(); ++i) {
      if (allcycle.at(i) == convert_square(allcycle.back(), base)) start = i;
    }
    std::vector<int> cycle(allcycle.begin() + start, allcycle.end());
    return cycle;
  }


  std::vector<int> find_dizzy_up_to(int last, const int base = 10) {
    std::vector<int> dizzyvec;
    if (last <= 10 and base <= 11) {
      for (int i = 0; i < dizzymap.at(base - 2).size()
           and dizzymap.at(base - 2).at(i) <= last; i++)
        dizzyvec.push_back(dizzymap.at(base - 2).at(i));
      return dizzyvec;
    } else {
      for (int i = 1; i <= last; i++) {
        if (is_dizzy(i, base) == 1)
          dizzyvec.push_back(i);
      }
      return dizzyvec;
    }
  }


  bool is_dizzy(int number, int base = 10) {
    if (number <= 10 and base <= 11) {
      if (find(dizzymap.at(base - 2).begin(),
               dizzymap.at(base - 2).end(), number)
          != dizzymap.at(base - 2).end())
        return true;
      else
        return false;
    }
    std::vector<int> cycle = dizziness_cycle(number, base);
    return (cycle.size() == 1 and cycle.at(0) == 1);
  }
};


// MAIN   leave this line and all below as is
//        when submitting


const double TLIMIT = 0.5;

void standard_tests();
void interactive_main();

int main(int argc, const char **argv) {
  if (argc > 1)
    interactive_main();
  else
    standard_tests();
  return 0;
}

void standard_tests() {
  double speed = computer_speed();
  std::cerr << "Your computers speed relative to server: " << speed << "\n";

  Timer tall, t0("setup"), t1("all100");
  Timer t3("lots_of_base_10"), t4("lots_of_bases");


  std::vector<std::pair<int, int>> res;

  t0.start();
  dizzyGenerator h;
  t0.stop();

  // Test case definitions.
  std::vector<int> dizzy_tests_one{1, 4, 7, 145, 91, 31435135};
  std::vector<std::vector<int>> dizzy_tests_two{{14500, 10}, {2, 3},
    {255, 2}, {255, 4}, {998, 998}, {4, 10}, {7, 3},
    {41, 100}, {234, 100}, {124, 100}, {22357, 1000}, {1049, 1000}};
  std::vector<std::vector<int>> find_upto_tests_two{{100, 3},
    {1000, 11}, {20, 2}};
  std::vector<int> find_upto_tests_one{10, 100};

  std::cout << "Testing is_dizzy (two parameters)\n";
  for (auto e : dizzy_tests_two) {
    std::cout << "is_dizzy(" << e.at(0) << "," << e.at(1) << ") = ";
    std::cout << h.is_dizzy(e.at(0), e.at(1)) << "\n";
  }

  std::cout << "Testing is_dizzy (one parameter)\n";
  for (auto e : dizzy_tests_one) {
    std::cout << "is_dizzy(" << e << ") = ";
    std::cout << h.is_dizzy(e) << "\n";
  }

  std::cout << "Testing dizziness_cycle (two parameters)\n";
  for (auto e : dizzy_tests_two) {
    std::cout << "dizziness_cycle(" << e.at(0) << "," << e.at(1) << ") = ";
    for (auto cyc_val : h.dizziness_cycle(e.at(0), e.at(1)))
      std::cout << cyc_val << " ";
    std::cout << "\n";
  }

  std::cout << "Testing dizziness_cycle (one parameter)\n";
  for (auto e : dizzy_tests_one) {
    std::cout << "dizziness_cycle(" << e << ") = ";
    for (auto cyc_val : h.dizziness_cycle(e))
      std::cout << cyc_val << " ";
    std::cout << "\n";
  }

  std::cout << "Testing find_dizzy_up_to (two parameters)\n";
  for (auto e : find_upto_tests_two) {
    std::cout << "find_dizzy_up_to(" << e.at(0) << "," << e.at(1) << ") = ";
    for (auto dizzyval : h.find_dizzy_up_to(e.at(0), e.at(1)))
      std::cout << dizzyval << " ";
    std::cout << "\n";
  }


  std::cout << "Testing find_dizzy_up_to (one parameter)\n";
  for (auto e : find_upto_tests_one) {
    std::cout << "find_dizzy_up_to(" << e << ") = ";
    for (auto dizzynum : h.find_dizzy_up_to(e))
      std::cout << dizzynum << " ";
    std::cout << "\n";
  }


  std::cout << "Finding the dizziest bases\n";

  t1.start();
  for (int i = 2; i < 100; i++) {
    auto v = h.find_dizzy_up_to(100, i);
    res.push_back(std::make_pair(v.size(), i));
  }
  t1.stop();

  std::sort(res.begin(), res.end());

  std::cout << "The ten dizziest bases (for 1 to 100) are \n";
  for (auto it = res.rbegin(); it != res.rbegin() + 10 ; it++)
    std::cout << "base "  << it -> second << " has "
              << it -> first << " dizzy\n";



  std::cout << "\nHow many dizzy can you find in 0.5 seconds, base 10?\n";
  int start_size = 100;
  while (t3.time() < TLIMIT) {
    t3.start();
    std::vector<int> res =  h.find_dizzy_up_to(start_size);
    t3.stop();
    std::vector<uint64_t> locs{0, res.size() / 3,
                               2 * res.size() / 3, res.size() - 1};
    for (auto i : locs) {
      std::cout << "ss:" << start_size << " i: " << i
                << " v: " << res.at(i) << "\n";
    }
    start_size *= 2;
  }



  std::cout << "\nHow many dizzy can you find in 0.5 seconds, all bases?\n";
  int base = 2;
  while (t4.time() < TLIMIT) {
    t4.start();
    std::vector<int> res =  h.find_dizzy_up_to(20000, base);
    t4.stop();
    std::vector<uint64_t> locs{0, res.size() / 3,
                               2 * res.size() / 3, res.size() - 1};
    for (auto i : locs) {
      std::cout << "base:" << base
                << " i: " << i << " v: " << res.at(i) << "\n";
    }
    base *= 2;
  }
}


void interactive_main() {
  std::string asktype;
  int number, parameters, base;
  dizzyGenerator h;

  while (true) {
    std::cin >> asktype;
    if (asktype == "quit") break;
    std::cin >> parameters >> number;
    if (parameters > 1) std::cin >> base;
    if (asktype == "i" and parameters == 2) {
      std::cout << "is_dizzy(" << number << "," << base << ") = ";
      std::cout << h.is_dizzy(number, base) << "\n";
    } else if (asktype == "i" and parameters == 1) {
      std::cout << "is_dizzy(" << number << ") = ";
      std::cout << h.is_dizzy(number) << "\n";
    } else if (asktype == "c" and parameters == 2) {
      std::cout << "dizziness_cycle(" << number << "," << base << ") = ";
      for (auto cyc_val : h.dizziness_cycle(number, base) )
        std::cout << cyc_val << " ";
      std::cout << "\n";
    } else if (asktype == "c" and parameters == 1) {
      std::cout << "dizziness_cycle(" << number << ") = ";
      for (auto cyc_val : h.dizziness_cycle(number))
        std::cout << cyc_val << " ";
      std::cout << "\n";
    } else if (asktype == "f" and parameters == 2) {
      std::cout << "find_dizzy_up_to(" << number << "," << base << ") = ";
      for (auto dizzyval : h.find_dizzy_up_to(number, base))
        std::cout << dizzyval << " ";
      std::cout << "\n";
    } else if (asktype == "f" and parameters == 1) {
      std::cout << "find_dizzy_up_to(" << number << ") = ";
      for (auto dizzynum : h.find_dizzy_up_to(number))
        std::cout << dizzynum << " ";
      std::cout << "\n";
    }
  }
}

