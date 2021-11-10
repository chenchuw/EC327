// Copyright 2020 Hanming Wang hita@bu.edu
// Copyright 2020 Chuwei Chen chenchuw@bu.edu

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "movedef.h"

char tttresult(std::string board) {
  int a = 0, b = 0;
  if (board.size() != 9) return 'e';
  for (int i = 0; i < board.size(); ++i) {
    if (board[i] != 'x' and board[i] != '#' and board[i] != 'o') return 'e';
    if (board[i] == 'x') a++;
    if (board[i] == 'o') b++;
  }
  if (a - b > 1 or b > a) return 'i';
  std::map<char, int> m = {{'x', 0}, {'o', 0}};
  for (int j = 0; j <= 6; j = j + 3)
    if (board[j] == board[j + 1] and board[j] == board[j + 2]) m[board[j]] += 1;
  for (int k = 0; k < 3; k++)
    if (board[k] == board[k + 3] and board[k] == board[k + 6]) m[board[k]] += 1;
  if (board[0] == board[4] and board[4] == board[8]) m[board[0]] += 1;
  if (board[2] == board[4] and board[4] == board[6]) m[board[2]] += 1;
  if ((m['x'] == 1 and a == b) or (m['o'] == 1 and a != b)) return 'i';
  if (m['x'] >= 1) return 'x';
  if (m['o'] >= 1) return 'o';
  if (a + b == 9) return 't';
  return 'c';
}

char tttresult(std::vector<Move> board) {
  std::string s = "#########";
  for (int i = 0; i < board.size(); i++) {
    int d = board[i].r * 3 + board[i].c;
    if (s[d] != '#' or board[i].player != 'x' and board[i].player != 'o')
      return 'e';
    s[d] = board[i].player;
  }
  return tttresult(s);
}

std::string dec2ter(int base_ten) {
  std::string result = "";
  while (base_ten > 0) {
    result = static_cast<char>(('0' + base_ten % 3)) + result;
    base_ten /= 3;
  }
  int remain = 9 - result.size();
  for (int i = 0; i < remain; i++)
    result = '0' + result;
  return result;
}

std::vector<std::string> get_all_boards() {
  std::vector<std::string> v;
  for (int i = 0; i < 19683; i++) {
    std::string s = "";
    for (int j = 0; j < 9; j++) {
      if (dec2ter(i)[j] == '0') s += 'x';
      if (dec2ter(i)[j] == '1') s += 'o';
      if (dec2ter(i)[j] == '2') s += '#';
    }
    v.push_back(s);
  }
  return v;
}

// MAIN
int main() {
  std::vector<std::string> v = get_all_boards();
  std::map<char, int> m;
  for (int i = 0; i < v.size(); i++)
    m[tttresult(v[i])] += 1;
  std::cout << "x " << m['x'] << "\n" << "o " << m['o'] << "\n" << "t "
            << m['t'] << "\n" << "i " << m['i'] << "\n" << "c "
            << m['c'] << "\n";
  return 0;
}
