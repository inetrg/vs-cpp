#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

void f() {
  std::vector<std::string> names{"Tom", "Tim", "Bart", "Harry"};
  auto end = names.end();
  auto i = find_if(names.begin(), end,
                   [](const auto& name) { return name.size() > 3; });
  if (i == end)
    std::cout << "Only short names.\n";
  else
    std::cout << "First long name: " << *i << ".\n";
}

void g() {
  std::vector<std::string> names{"Tom", "Tim", "Bart", "Harry"};
  std::set<std::string> blacklist{"Bart"};
  if (any_of(names.begin(), names.end(),
             [&](const auto& name) { return blacklist.count(name) > 0; }))
    std::cout << "Blacklisted name found!\n";
  else
    std::cout << "All names are good to go!\n";
}

int main(int, char**) {
  f();
  g();
}
