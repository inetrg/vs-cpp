#include <vector>
#include <iostream>

int main(int, char**) {
  std::vector<int> xs{10, 20, 30};
  xs.emplace_back(40);
  for (auto x : xs)
    std::cout << x << ' ';
  std::cout << std::endl;
}
