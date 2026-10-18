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
  // std::vector<int> nums01{50};
  // std::vector<int> nums02{};
  // res = sol.findMedianSortedArrays(nums01, nums02);
  
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


  const int s1b=1, s1e=5;
  const int s2b=0, s2e=5;
  std::vector<int> nums1;
  std::vector<int> nums2;
  for(int i2=s2b; i2<=s2e; ++i2){
    for(int i1=s1b; i1<=s1e; ++i1){
      nums1.push_back()
    }
  }




  echo("res={}\n", res);
}

//- - - - - - - - - - - -
//= = = = = = = = = = = = = = =

//- - - - - - - - - - - -
// #pragma GCC diagnostic pop
