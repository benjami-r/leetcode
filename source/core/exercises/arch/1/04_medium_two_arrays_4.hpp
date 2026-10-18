// 04_medium_two_arrays.hpp
// 4. Median of Two Sorted Arrays
// https://leetcode.com/problems/median-of-two-sorted-arrays/description/
// clang-format off

#define ECHO
#include "sys.hpp"

#include <vector>

class Solution {
  std::size_t s1,s2,s,l,r;

  std::size_t get_l(std::size_t size) { //[1] => 1;  [1,2] => 1;  [1,2,3] => 2;  [1,2,3,4] => 2;  [1,2,3,4,5] => 3;  [1,2,3,4,5,6] => 3;  [1,2,3,4,5,6,7] => 4;  [1,2,3,4,5,6,7,8] => 4;
    return size / 2 + (size%2 ? 1 : 0); //к нечетному добавляем 1
  }
  std::size_t get_r(std::size_t size) { //[1] => 1;  [1,2] => 2;  [1,2,3] => 2;  [1,2,3,4] => 3;  [1,2,3,4,5] => 3;  [1,2,3,4,5,6] => 4;  [1,2,3,4,5,6,7] => 4;  [1,2,3,4,5,6,7,8] => 5
    return size / 2 + 1;
  }
  
  // std::vector<int> nums2{11,21,31, 41, 51,61,71};
  // std::vector<int> nums1{12,15, 65,75};

  double f2(std::vector<int>& n1, std::size_t b1, std::size_t e1, std::vector<int>& n2, std::size_t b2, std::size_t e2) {
    std::size_t l1 = get_l(e1-b1+1) + b1-1;
    std::size_t l2 = get_l(e2-b2+1) + b2-1;
    if(n1[l1] < n2[l2]) {

    }
  }

  double f1(std::vector<int>& n1, std::vector<int>& n2) {
    s  = s1 + s2;
    l  = get_l(s); //с 1
    r  = get_r(s); //с 1
    if(s2 == 0) return (n1[l-1] + n1[r-1]); //n2 is empty
    return f2(n1,1,s1,n2,1,s2);
  }

public:
  double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    double sum=0.0;
    if(nums1.size() >= nums2.size()) {
      s1 = nums1.size();
      s2 = nums2.size();
      sum=f1(nums1,nums2);
    } else {
      s1 = nums2.size();
      s2 = nums1.size();
      sum=f1(nums2,nums1);
    }



    
    // if(s1==0) return (nums2[l-1] + nums2[r-1]) / 2.0; //nums1 is empty
    // if(s2==0) return (nums1[l-1] + nums1[r-1]) / 2.0; //nums2 is empty
    // if(nums1[s1-1]<=nums2[0]) return ((l<=s1 ? nums1[l-1] : nums2[l-s1-1]) + (r<=s1 ? nums1[r-1] : nums2[r-s1-1])) / 2.0; //joining: [nums1nums2]
    // if(nums2[s2-1]<=nums1[0]) return ((l<=s2 ? nums2[l-1] : nums1[l-s2-1]) + (r<=s2 ? nums2[r-1] : nums1[r-s2-1])) / 2.0; //joining: [nums2nums1]

    return sum/2.0;
  } 
};


// [a,b,c,..,d,e]   [l,m,..,r,s,t]

  // double one_empty(std::vector<int>& non_empty) {
  //   std::size_t l = non_empty.size() / 2 - (non_empty.size()%2 ? 0 : 1);
  //   std::size_t r = non_empty.size() / 2;
  //   return (non_empty[l] + non_empty[r]) / 2.0;
  // }



  // std::size_t get_l(std::size_t size) { //[1] => 0;  [1,2] => 0;  [1,2,3] => 1;  [1,2,3,4] => 1;  [1,2,3,4,5] => 2;  [1,2,3,4,5,6] => 2;  [1,2,3,4,5,6,7] => 3;  [1,2,3,4,5,6,7,8] => 3; заодно показывает сколько элементов слева
  //   return size / 2 - (size%2 ? 0 : 1); //у четного вычитаем 1
  // }
  // std::size_t get_r(std::size_t size) { //[1] => 0;  [1,2] => 1;  [1,2,3] => 1;  [1,2,3,4] => 2;  [1,2,3,4,5] => 2;  [1,2,3,4,5,6] => 3;  [1,2,3,4,5,6,7] => 3;  [1,2,3,4,5,6,7,8] => 4
  //   return size / 2;
  // }




  // double one_empty(std::vector<int>& non_empty, std::size_t l, std::size_t r) {
  //   return (non_empty[l] + non_empty[r]);
  // }

  // double one_before_other(std::vector<int>& one, std::size_t one_size, std::vector<int>& other, std::size_t l, std::size_t r) {


// double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
//     std::size_t s1 = nums1.size();
//     std::size_t s2 = nums2.size();
//     std::size_t s  = s1 + s2;
//     std::size_t l  = get_l(s); //с 1
//     std::size_t r  = get_r(s); //с 1
//     if(s1==0) return (nums2[l-1] + nums2[r-1]) / 2.0; //nums1 is empty
//     if(s2==0) return (nums1[l-1] + nums1[r-1]) / 2.0; //nums2 is empty
//     if(nums1[s1-1]<=nums2[0]) return ((l<=s1 ? nums1[l-1] : nums2[l-s1-1]) + (r<=s1 ? nums1[r-1] : nums2[r-s1-1])) / 2.0; //joining: [nums1nums2]
//     if(nums2[s2-1]<=nums1[0]) return ((l<=s2 ? nums2[l-1] : nums1[l-s2-1]) + (r<=s2 ? nums2[r-1] : nums1[r-s2-1])) / 2.0; //joining: [nums2nums1]
//     //f(nums1,nums2,1,s1,1,s2);
//     return 0.0;
//   } 

