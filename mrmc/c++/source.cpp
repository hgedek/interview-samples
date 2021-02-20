#include "header.hpp"
#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <algorithm>

/*
 * Looping from outer side to inner side and each loop will move one step into inner.
 * It will take O(mn) time but not O(n^2) 
 */
void StringifyMatrix(int* matrix, int rows, int columns, char* outBuffer) {
  int m = rows;
  int n = columns;

  int i, k = 0, l = 0;
  int count = 0;
  int total = m * n;

  int data;
  std::string buffer;

  auto append = [&] {
    buffer += std::to_string(data) + ",";
  };


  // loop counters 
  // each time we will take inner rectangle
  while (k < m && l < n) {

     if (count == total)
        break;

     for (i = k; i < m; ++i){
        data = *(matrix + (i*columns + l));
        append();
        count++;
     }

     l++;

     if (count == total)
        break;

     for (i = l; i < n; ++i){
        data = *(matrix + ((rows - l) * columns + i));
        append();
        count++;
     }

     m--;

     if (count == total)
        break;

     if (k < m){
        for (i = m; i > k; --i){
          data = *(matrix + (i * columns - l ));
          append();
          count++;
        }
        n--;
     }

    if (count == total)
        break;

     if (l < n){

        k++;

        for (i = l; i < n; ++i){
          data = *(matrix +( columns * k - i - 1));
          append();
          count++;
        }
     }
  }

  // remove last , 
  buffer.pop_back();
  strcpy(outBuffer, buffer.c_str());
}

void PrintRndByEleven(int n /* numbers to generate */) {

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib(1, 1000);

  std::vector<int> numbers;

  for (auto i = 0; i < n; ++i)
    numbers.emplace_back(distrib(gen));

  std::cout << "Original: ";
  std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));

  std::sort(numbers.begin(), numbers.end(), [](int left, int right){
      auto left_div = left / 11;
      auto right_div = right / 11;
      return left_div > right_div;
  });
  
  std::cout << "\nSorted: ";
  std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
}
