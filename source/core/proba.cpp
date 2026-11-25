// clang-format off
// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wc99-extensions"
//- - - - - - - - - - - - proba
#define ECHO
#include "sys.hpp"
//============================= //Приоритеты и правила группировки операторов - Дейтел:164

#include <vector>
#include "04_medium_two_arrays.hpp"
#include <random>  //новый
#include <algorithm>

std::random_device rd;  // Источник энтропии
std::mt19937 gen(rd()); // Генератор "Вихрь Мерсенна"
std::uniform_int_distribution<int> distSize(       0,    1000); // Диапазон включительно
std::uniform_int_distribution<int> distItem(-1000000, 1000000); // Диапазон включительно

void proba() {
  echoln("PROBA");

  Solution sol;

  {
    int TESTS = 1000000;
    std::vector<int> nums1;
    std::vector<int> nums2;
    std::vector<int> nums;
    int size1=0, size2=0;

    int test=0, ok=0, bad=0;
    while(TESTS--){
      ++test;
      do{
        size1=distSize(gen);
        size2=distSize(gen);
      }while(!size1 && !size2);
      for(int i=0; i<size1; ++i){nums1.push_back(distItem(gen));}
      for(int i=0; i<size2; ++i){nums2.push_back(distItem(gen));}
      std::sort(nums1.begin(), nums1.end());
      std::sort(nums2.begin(), nums2.end());
      double res = sol.findMedianSortedArrays(nums1, nums2);

      //check:
      nums.reserve(size1 + size2);
      nums.insert(nums.end(), nums1.begin(), nums1.end());
      nums.insert(nums.end(), nums2.begin(), nums2.end());
      std::sort(nums.begin(), nums.end());
      int size = nums.size();
      assert(size == size1+size2);
      int left = size/2 + size%2;
      int right = size/2 + 1;
      double d = (nums[left-1] + nums[right-1]) / 2.0;
      echoln("############################## test #{:6}: size1={:4}, size2={:4} ... {}",test, size1,size2, res==d?(ok++,"Ok"):(bad++,"BAD"));
      
      nums1.clear(); nums2.clear(); nums.clear();
    }
    echoln("############################## tests={}, {} Ok, {} Bad", test,ok,bad);
}

//----------------------------------------------------------

  /*
  {
    double d=0;
    std::vector<int> nums1;
    std::vector<int> nums2;
    nums1.insert(nums1.end(),{0,1,2,95});
    nums2.insert(nums2.end(),{1,3,60,70,80,90,100,101,102,103});
    d+=sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
    nums1.insert(nums1.end(),{0,1,3,60,70,80,90,100,101,102});
    nums2.insert(nums2.end(),{0,1,2,5,8,12,14,60,90,95});
    d+=sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
    nums1.insert(nums1.end(),{1,3,60,70,80,90,100,101,102,103});
    nums2.insert(nums2.end(),{0,1,2,5,8,12,14,60,90,95,110,111});
    d+=sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
    nums1.insert(nums1.end(),{1,3,60,70,80,90,100,101,102});
    nums2.insert(nums2.end(),{0,1,2,5,8,12,14,60,90,95,110,111});
    d+=sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
    nums1.insert(nums1.end(),{1,3,60,70,80,90,100,101,102,103});
    nums2.insert(nums2.end(),{1,2,5,8,12,14,60,90,95,110,111});
    d+=sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
    nums1.insert(nums1.end(),{1,3,60,70,80,90,100,101,102});
    nums2.insert(nums2.end(),{1,2,5,8,12,14,60,90,95,110,111});
    d+=sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
    nums1.insert(nums1.end(),{2});
    nums2.insert(nums2.end(),{1,3,5});
    d+=sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
    nums1.insert(nums1.end(),{4});
    nums2.insert(nums2.end(),{1,3,5});
    d+=sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
    nums1.insert(nums1.end(),{});
    nums2.insert(nums2.end(),{1});
    d+=sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
    nums1.insert(nums1.end(),{1,3});
    nums2.insert(nums2.end(),{2,4,5});
    d+=sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();

    echo("d={}",d);//d=381.5
  }
  */
}

//- - - - - - - - - - - -
//= = = = = = = = = = = = = = =

//- - - - - - - - - - - -
// #pragma GCC diagnostic pop
