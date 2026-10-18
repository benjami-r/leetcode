// 04_medium_two_arrays.hpp
// 4. Median of Two Sorted Arrays
// https://leetcode.com/problems/median-of-two-sorted-arrays/description/
// clang-format off

#define ECHO
#include "sys.hpp"
#include <vector>


//[2,6,9] [3,7,11,22,30]

// v1=[1,3,5]    
// v2=[7,8]
// [a,b   ,c,d,e] 
class Solution {
  std::size_t get_l(std::size_t size) { //[1] => 0;  [1,2] => 0;  [1,2,3] => 1;  [1,2,3,4] => 1
    return size / 2 - (size%2 ? 0 : 1); //у четного вычитаем 1
  }
  std::size_t get_r(std::size_t size) { //[1] => 0;  [1,2] => 1;  [1,2,3] => 1;  [1,2,3,4] => 2
    return size / 2;
  }


  double one_empty(std::vector<int>& non_empty, std::size_t l, std::size_t r) {
    return (non_empty[l] + non_empty[r]);
  }

  double one_before_other(std::vector<int>& one, std::size_t one_size, std::vector<int>& other, std::size_t l, std::size_t r) {
    return l<one_size ? one[l] : other[l - one_size] +
           r<one_size ? one[r] : other[r - one_size];
  }

  // double mixed(
  //   std::vector<int>& nums1, std::vector<int>& nums2, 
  //   std::size_t size1, std::size_t size2,
  //   std::size_t size, std::size_t l, std::size_t r)
  // {
  //   std::size_t l1 = 

  //   return 0.0;
  // }


public:
  double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    std::size_t size1 = nums1.size();
    std::size_t size2 = nums2.size();
    std::size_t size  = size1 + size2;
    std::size_t l = get_l(size); ////size / 2 - (size%2 ? 0 : 1);
    std::size_t r = get_r(size); ////size / 2;
    double sum = 0;

    if(size1 == 0) sum = one_empty(nums2, l, r); else // nums1 is empty
    if(size2 == 0) sum = one_empty(nums1, l, r); else // nums2 is empty
    if(nums1[size1-1] <= nums2[0]) sum = one_before_other(nums1, size1, nums2, l, r); else //[nums1][nums2] one after another
    if(nums2[size1-1] <= nums1[0]) sum = one_before_other(nums2, size2, nums1, l, r); else //[nums2][nums1] one after another
    {                                                 //[nums1nums2] mixed



    }
    return sum / 2.0;
  } 
};


// [a,b,c,..,d,e]   [l,m,..,r,s,t]

  // double one_empty(std::vector<int>& non_empty) {
  //   std::size_t l = non_empty.size() / 2 - (non_empty.size()%2 ? 0 : 1);
  //   std::size_t r = non_empty.size() / 2;
  //   return (non_empty[l] + non_empty[r]) / 2.0;
  // }



