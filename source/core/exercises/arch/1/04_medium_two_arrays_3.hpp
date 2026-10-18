// 04_medium_two_arrays.hpp
// 4. Median of Two Sorted Arrays
// https://leetcode.com/problems/median-of-two-sorted-arrays/description/
// clang-format off

#define ECHO
#include "sys.hpp"

#include <vector>


class Solution {
  std::size_t get_l(std::size_t size) { //[1] => 0;  [1,2] => 0;  [1,2,3] => 1;  [1,2,3,4] => 1;  [1,2,3,4,5] => 2;  [1,2,3,4,5,6] => 2;  [1,2,3,4,5,6,7] => 3;  [1,2,3,4,5,6,7,8] => 3; заодно показывает сколько элементов слева
    return size / 2 - (size%2 ? 0 : 1); //у четного вычитаем 1
  }
  std::size_t get_r(std::size_t size) { //[1] => 0;  [1,2] => 1;  [1,2,3] => 1;  [1,2,3,4] => 2;  [1,2,3,4,5] => 2;  [1,2,3,4,5,6] => 3;  [1,2,3,4,5,6,7] => 3;  [1,2,3,4,5,6,7,8] => 4
    return size / 2;
  }

  double f(std::vector<int>& n1, std::vector<int>& n2) {
    double sum = 0.0;
    std::size_t s1 = n1.size();
    std::size_t s2 = n2.size();
    assert(s1 >= s2);
    std::size_t s = s1 + s2;
    std::size_t l = get_l(s);
    std::size_t r = get_r(s);

    //echo:
    char delimiter[]{'\0','\0'};
    echo("n1 = [");
    for(std::size_t i=0; i<s1; ++i) {echo("{}{}",delimiter,n1[i]); delimiter[0]=',';}
    echo("]\n");
    delimiter[0]='\0';
    echo("n2 = [");
    for(std::size_t i=0; i<s2; ++i) {echo("{}{}",delimiter,n2[i]); delimiter[0]=',';}
    echo("]\n");
    echo("s1={}, s2={}, s={}, l={}, r={}\n", s1,s2,s,l,r);

    if(s2 == 0) { sum = n1[l] + n1[r]; } else 
    {
      echo("\n=== n1 and n2 not empty ===\n");

      std::size_t l1 = get_l(s1);
      std::size_t l2 = get_l(s2);

      echo("Test for:\n"
            "\tl1={}, leftRoll1={}\n" 
            "\tl2={}, leftRoll2={}\n"
            "\t      leftRoll ={}\n" 
            , l1,l1
            , l2,l2
            , l1+l2
          );

      if(n1[l1]>=n2[l2]) {
        std::size_t s2_2 = s2-(l2+1);
        echo("s2_2={}\n",s2_2);
        //if()
      }

    }


    return sum;
  }

public:
  double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    double sum;
    if(nums1.size() >= nums2.size()) {
      sum = f(nums1, nums2);
    } else {
      sum = f(nums2, nums1);
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



  // std::size_t get_l(std::size_t size) { //[1] => 0;  [1,2] => 0;  [1,2,3] => 1;  [1,2,3,4] => 1
  //   return size / 2 - (size%2 ? 0 : 1); //у четного вычитаем 1
  // }
  // std::size_t get_r(std::size_t size) { //[1] => 0;  [1,2] => 1;  [1,2,3] => 1;  [1,2,3,4] => 2
  //   return size / 2;
  // }

  // double one_empty(std::vector<int>& non_empty, std::size_t l, std::size_t r) {
  //   return (non_empty[l] + non_empty[r]);
  // }

  // double one_before_other(std::vector<int>& one, std::size_t one_size, std::vector<int>& other, std::size_t l, std::size_t r) {
