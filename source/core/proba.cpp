// clang-format off
// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wc99-extensions"
//- - - - - - - - - - - - proba
#define ECHO
#include "sys.hpp"
//=============================




#include "01_two_sum.hpp"

void proba() {
  echo("{}\n", "PROBA");

  std::vector<int> numbers1 = {2,7,11,15};
  int target1 = 9;
  Solution sol1;
  std::vector<int> result1 = sol1.twoSum(numbers1, target1); //auto result
  echo("result = [{},{}]\n", result1[0], result1[1]);

  std::vector<int> numbers2 = {3,2,4};
  int target2 = 6;
  Solution sol2;
  std::vector<int> result2 = sol2.twoSum(numbers2, target2); //auto result
  echo("result = [{},{}]\n", result2[0], result2[1]);

  std::vector<int> numbers3 = {3,3};
  int target3 = 6;
  Solution sol3;
  std::vector<int> result3 = sol3.twoSum(numbers3, target3); //auto result
  echo("result = [{},{}]\n", result3[0], result3[1]);

  std::vector<int> numbers4 = {-1,-2,-3,-4,-5};
  int target4 = -8;
  Solution sol4;
  std::vector<int> result4 = sol4.twoSum(numbers4, target4); //auto result
  echo("result = [{},{}]\n", result4[0], result4[1]);
}

//- - - - - - - - - - - -
//= = = = = = = = = = = = = = =

//- - - - - - - - - - - -
// #pragma GCC diagnostic pop
