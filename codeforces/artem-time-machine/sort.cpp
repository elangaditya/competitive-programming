#include <algorithm>
#include <iostream>
#include <vector>

// Define the struct (same as before)
struct MyStruct {
  int a;
  int b;
};

// Custom comparison function for ascending order of 'a'
bool customCompareAscending(const MyStruct &x, const MyStruct &y) {
  // If either b is 0, we should not swap them based on 'a'.
  if (x.b == 0 || y.b == 0) {
    return false; // Don't swap
  }

  // Otherwise, sort by 'a' in ascending order
  return x.a < y.a; // Changed from '>' to '<'
}

int main() {
  std::vector<MyStruct> data = {
      {10, 5}, {20, 0}, // b is 0
      {5, 10}, {15, 0}, // b is 0
      {25, 2}, {8, 0}   // b is 0
  };

  std::cout << "Before sorting:" << std::endl;
  for (const auto &elem : data) {
    std::cout << "{a: " << elem.a << ", b: " << elem.b << "} ";
  }
  std::cout << std::endl;

  // Sort the vector using the custom comparison function for ascending order
  std::sort(data.begin(), data.end(), customCompareAscending);

  std::cout << "After sorting (ascending 'a', b=0 in place):" << std::endl;
  for (const auto &elem : data) {
    std::cout << "{a: " << elem.a << ", b: " << elem.b << "} ";
  }
  std::cout << std::endl;

  return 0;
}
