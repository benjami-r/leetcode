// clang-format off
// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wc99-extensions"
//- - - - - - - - - - - - proba
#define ECHO
#include "sys.hpp"
//=============================

#include <vector>
#include "04_medium_two_arrays.hpp"

void proba() {
  echo("{}\n", "PROBA");

  double res;

  Solution sol;

  std::vector<int> nums01{   20,22,32,34,36,38,65,100,101,102   }; //7
  std::vector<int> nums02{10,20,30,40,50,60,70,80,90,95}; //9
  res = sol.findMedianSortedArrays(nums01, nums02);
  
  // std::vector<int> nums03{50};
  // std::vector<int> nums04{50};
  // res = sol.findMedianSortedArrays(nums03, nums04);
 
  // std::vector<int> nums05{50,60};
  // std::vector<int> nums06{};
  // res = sol.findMedianSortedArrays(nums05, nums06);
 
  // std::vector<int> nums07{50,60};
  // std::vector<int> nums08{50};
  // res = sol.findMedianSortedArrays(nums07, nums08);
  
  // std::vector<int> nums09{50,60};
  // std::vector<int> nums10{50,60};
  // res = sol.findMedianSortedArrays(nums09, nums10);

  //1234 1234  1234 1234 1234
  //     1     12   123  1234          
  //12345 12345  12345 12345 12345 12345
  //      1      12    123   1234  12345
  // std::vector<int> nums1, nums2;
  // for(int i=4; i<=5; ++i){
  //   for(int j=1;j<=i;++j){
  //     nums1.push_back(j);
  //   }
  //   for(int j=0; j<=i; ++j){
  //     for(int k=1; k<=j; ++k){
  //       nums2.push_back(k);
  //     }
  //     res = sol.findMedianSortedArrays(nums1, nums2);
  //     echo("-----res={}\n", res);
  //     nums2.clear();
  //   }
  //   nums1.clear();
  // }

  echo("res={}\n", res);
}

//- - - - - - - - - - - -
//= = = = = = = = = = = = = = =

//- - - - - - - - - - - -
// #pragma GCC diagnostic pop
