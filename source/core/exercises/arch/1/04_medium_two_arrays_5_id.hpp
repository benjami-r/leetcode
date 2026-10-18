// 04_medium_two_arrays.hpp
// 4. Median of Two Sorted Arrays
// https://leetcode.com/problems/median-of-two-sorted-arrays/description/
// clang-format off

#define ECHO
#include "sys.hpp"

#include <vector>

class Solution {
  using vcr = std::vector<int>;
  std::size_t getL(std::size_t size) { //[1] => 0;  [1,2] => 0;  [1,2,3] => 1;  [1,2,3,4] => 1;  [1,2,3,4,5] => 2;  [1,2,3,4,5,6] => 2;  [1,2,3,4,5,6,7] => 3;  [1,2,3,4,5,6,7,8] => 3; заодно показывает сколько элементов слева
    return size / 2 - (size%2 ? 0 : 1); //у четного вычитаем 1
  }
  std::size_t getR(std::size_t size) { //[1] => 0;  [1,2] => 1;  [1,2,3] => 1;  [1,2,3,4] => 2;  [1,2,3,4,5] => 2;  [1,2,3,4,5,6] => 3;  [1,2,3,4,5,6,7] => 3;  [1,2,3,4,5,6,7,8] => 4
    return size / 2;
  }
//------------------------------------

  double f0(vcr &n1, int s1, vcr &n2, int s2) { //big, small
    const int l = getL(s1+s2), r=getR(s1+s2);
    if(s2==0) return(n1[l] + n1[r]); //if n2 empty



    return 0.0;
  }
//++++++++++++++++++++++++++++++++++++ // [a,b,c,..d,e,..f,g,h]   [l,m,..r,s,t,..u,v]
public:
  double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    int s1=nums1.size(), s2=nums2.size();
    //return (s1>s2 ? f0(nums1,s1, nums2,s2) : f0(nums2,s2, nums1,s1)) / 2.0;
  
    echo("l1={}, l2={}, l={}, l1+l2={}\n", getL(s1), getL(s2), getL(s1+s2), getL(s1)+getL(s2));

    return 0.0;
  } 
};


// [a,b,c,..d,e,..f,g,h]   [l,m,..r,s,t,..u,v]


  // std::size_t get_l(std::size_t size) { //[1] => 0;  [1,2] => 0;  [1,2,3] => 1;  [1,2,3,4] => 1;  [1,2,3,4,5] => 2;  [1,2,3,4,5,6] => 2;  [1,2,3,4,5,6,7] => 3;  [1,2,3,4,5,6,7,8] => 3; заодно показывает сколько элементов слева
  //   return size / 2 - (size%2 ? 0 : 1); //у четного вычитаем 1
  // }
  // std::size_t get_r(std::size_t size) { //[1] => 0;  [1,2] => 1;  [1,2,3] => 1;  [1,2,3,4] => 2;  [1,2,3,4,5] => 2;  [1,2,3,4,5,6] => 3;  [1,2,3,4,5,6,7] => 3;  [1,2,3,4,5,6,7,8] => 4
  //   return size / 2;
  // }

  // int get_l(int size) { //[1] => 1;  [1,2] => 1;  [1,2,3] => 2;  [1,2,3,4] => 2;  [1,2,3,4,5] => 3;  [1,2,3,4,5,6] => 3;  [1,2,3,4,5,6,7] => 4;  [1,2,3,4,5,6,7,8] => 4;
  //   return size / 2 + (size%2 ? 1 : 0); //к нечетному добавляем 1
  // }
  // int get_r(int size) { //[1] => 1;  [1,2] => 2;  [1,2,3] => 2;  [1,2,3,4] => 3;  [1,2,3,4,5] => 3;  [1,2,3,4,5,6] => 4;  [1,2,3,4,5,6,7] => 4;  [1,2,3,4,5,6,7,8] => 5
  //   return size / 2 + 1;
  // }



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

//Идея: виртуальные индексы - от 1000 - n1, от 2000 - n2 (но она не универсальна).
//вертим: n1 - в котором ищем l, если он в n2 - вертим, передавая пересчитанные индексы
