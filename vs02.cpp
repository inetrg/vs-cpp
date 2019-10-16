#include <iostream>
#include <vector>

int main(int, char**) {
  std::vector<int> xs{10, 20, 30};
  xs.emplace_back(40);
  for (int x : xs)
    std::cout << x << ' ';
  std::cout << '\n';
}
