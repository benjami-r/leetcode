// clang-format off
// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wc99-extensions"
//- - - - - - - - - - - - proba
#define ECHO
#include "sys.hpp"
//=============================

#include <vector>
#include "04_medium_two_arrays.hpp"
#include <random>  //новый
#include <algorithm>

std::random_device rd;  // Источник энтропии
std::mt19937 gen(rd()); // Генератор "Вихрь Мерсенна"
std::uniform_int_distribution<int> distSize(       0,    1000); // Диапазон включительно
std::uniform_int_distribution<int> distItem(-1000000, 1000000); // Диапазон включительно

void proba() {
  echo("{}\n", "PROBA");

  Solution sol;
/*
  std::vector<int> nums01{2};
  std::vector<int> nums02{1,3,4};
  sol.findMedianSortedArrays(nums01, nums02);
*/

/*
  std::vector<int> nums1;
  std::vector<int> nums2;
  int size1=0, size2=0;
int i=1;
while(i--){
  do{
    size1=distSize(gen);
    size2=distSize(gen);
  }while(!size1 && !size2);
  echo("size1={}, size2={}\n",size1,size2);
  for(int i=0; i<size1; ++i){nums1.push_back(distItem(gen));}
  for(int i=0; i<size2; ++i){nums2.push_back(distItem(gen));}
  std::sort(nums1.begin(), nums1.end());
  std::sort(nums2.begin(), nums2.end());
  sol.findMedianSortedArrays(nums1, nums2);
}
*/

//----------------------------------------------------------

  {
    std::vector<int> nums1;
    std::vector<int> nums2;
    nums1.insert(nums1.end(),{1,3,60,70,80,90,100,101,102,103});
    nums2.insert(nums2.end(),{0,1,2,5,8,12,14,60,90,95,110,111});
    sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
    nums1.insert(nums1.end(),{1,3,60,70,80,90,100,101,102});
    nums2.insert(nums2.end(),{0,1,2,5,8,12,14,60,90,95,110,111});
    sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
    nums1.insert(nums1.end(),{1,3,60,70,80,90,100,101,102,103});
    nums2.insert(nums2.end(),{1,2,5,8,12,14,60,90,95,110,111});
    sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
    nums1.insert(nums1.end(),{1,3,60,70,80,90,100,101,102});
    nums2.insert(nums2.end(),{1,2,5,8,12,14,60,90,95,110,111});
    sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
    nums1.insert(nums1.end(),{2});
    nums2.insert(nums2.end(),{1,3,5});
    sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
    nums1.insert(nums1.end(),{4});
    nums2.insert(nums2.end(),{1,3,5});
    sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
    nums1.insert(nums1.end(),{});
    nums2.insert(nums2.end(),{1});
    sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
    nums1.insert(nums1.end(),{1,3});
    nums2.insert(nums2.end(),{2,4,5});
    sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
  }

/*  {//!!!
    nums1.insert(nums1.end(),{1,5,6,6});
    nums2.insert(nums2.end(),{3,7,8,9,9,12});
    sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();nums1.insert(nums1.end(),{1,5,7,13});
    nums2.insert(nums2.end(),{3,3,8,9,9,12});
    sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
    nums1.insert(nums1.end(),{1,9,10,11});
    nums2.insert(nums2.end(),{3,3,4,5,6,7});
    sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
  }*/

}

//- - - - - - - - - - - -
//= = = = = = = = = = = = = = =

//- - - - - - - - - - - -
// #pragma GCC diagnostic pop
