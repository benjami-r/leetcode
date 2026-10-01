// q01_concat_array.hpp
// Q1. Concatenation of Array
//  Given an integer array nums of length n, you want to create an array ans of
//  length 2n where ans[i] == nums[i] and ans[i + n] == nums[i] for 0 <= i < n
//  (0-indexed). Specifically, ans is the concatenation of two nums arrays.
//  Return the array ans.
//  Example 1:
//  Input: nums = [1,2,1]
//  Output: [1,2,1,1,2,1]
//  Explanation: The array ans is formed as follows:
//  - ans = [nums[0],nums[1],nums[2],nums[0],nums[1],nums[2]]
//  - ans = [1,2,1,1,2,1]
//  Example 2:
//  Input: nums = [1,3,2,1]
//  Output: [1,3,2,1,1,3,2,1]
//  Explanation: The array ans is formed as follows:
//  - ans = [nums[0],nums[1],nums[2],nums[3],nums[0],nums[1],nums[2],nums[3]]
//  - ans = [1,3,2,1,1,3,2,1]
//  Constraints:
//      n == nums.length
//      1 <= n <= 1000
//      1 <= nums[i] <= 1000

#include <vector>
class Solution {
public:
  std::vector<int> getConcatenation(std::vector<int> &nums) {
    std::vector<int> ans;
    ans.reserve(2 * nums.size());
    ans = nums;
    ans.insert(ans.end(), nums.begin(), nums.end());
    return ans;
  }
};

/*//============================= run

//- - - - - - - - - - - - proba
#define ECHO
#include "sys.hpp"


#include "q01_concat_array.hpp"

void proba() {
  echo("{}\n", "PROBA");

  std::vector<int> numbers1 = {1,2,3,4};
  std::vector<int> numbers2 = {5,6,7};
  Solution sol1;
  std::vector<int> dbl = sol1.getConcatenation(numbers1);
  echo("size = {}, capacity = {}:\n", dbl.size(), dbl.capacity());
  for(auto n : dbl) {
    echo("- [{}]\n", n);
  }
}

*/
