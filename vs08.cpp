#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm> // for std::find_if and std::any_of

using namespace std;

void f() {
  vector<string> names{"Tom", "Tim", "Bart", "Harry"};
  auto end = names.end();
  auto i = find_if(names.begin(), end,
                   [](const string& name) { return name.size() > 3; });
  if (i == end)
    cout << "Only short names.\n";
  else
    cout << "First long name: " << *i << ".\n";
}

void g() {
  vector<string> names{"Tom", "Tim", "Bart", "Harry"};
  set<string> blacklist{"Bart"};
  if (any_of(names.begin(), names.end(),
             [&](const string& name) {
               return blacklist.count(name) > 0;
             }))
    cout << "Blacklisted name found!\n";
  else
    cout << "All names are good to go!\n";
}

int main(int, char**) {
  f();
  g();
}
