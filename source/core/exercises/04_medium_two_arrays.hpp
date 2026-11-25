// 04_medium_two_arrays.hpp
// 4. Median of Two Sorted Arrays
// https://leetcode.com/problems/median-of-two-sorted-arrays/description/
// clang-format off

#include <cassert>
//#define ECHO
#undef ECHO

#include "sys.hpp"

#include <vector>

class Solution {

#define L1 n1[(l1)-1]
#define L2 n2[(l2)-1]
#define R1 n1[(r1)-1]
#define R2 n2[(r2)-1]

int idL(int size) {
  assert(size>=0);
  return (size / 2 + size%2); //add 1 to an odd
}
int idR(int size) {
  assert(size>=0);
  return size?(size / 2 + 1):0;
}

int sum(std::vector<int> &n1,std::vector<int> &n2,  int s1,int s2,  int b1=0,int e1=0,  int depth=1) {
  //b1,e1 - сколько отбросили в начале/конце n1 (соответственно, конце/начале n2)
  assert(s1>=0 && s2>=0 && b1>=0 && e1>=0);
  int w1=s1-b1-e1, w2=s2-b1-e1;
  assert(w1>=0 && w2>=0);
  int l1=idL(w1)+b1, r1=idR(w1)+b1, l2=idL(w2)+e1, r2=idR(w2)+e1;
  //pvs(n1,n2, s1,s2, b1,e1, w1,w2, l1,l2,r1,r2); echoln("depth={}",depth);
  if( w1 &&  w2){ //echoln("■: w1 &&  w2"); //■
    if(L1 > R2) {e1=s1-r1+1; return sum(n1,n2,s1,s2,b1,e1,depth+1);}
    if(L2 > R1) {b1=l1;      return sum(n1,n2,s1,s2,b1,e1,depth+1);}
    return (L1>L2?L1:L2) + (R1<R2?R1:R2);
  }else if(!w1 &&  w2){ //echo("▲: !w1 &&  w2"); //▲
    if(!b1 && !e1){ //echoln(", !b1 && !e1"); 
      return L2 + R2; 
    }
    if(b1 && e1){ //echo("b1 && e1"); 
      l1=b1; r1=b1+1; //echoln(", L1={},L2={},R1={},R2={}",L1,L2,R1,R2); 
      return (L1>L2?L1:L2) + (R1<R2?R1:R2);
    }
    else  if(b1){ //echo("b1");       
      l1=b1; //echoln(", L1={},L2={}, R2={}",L1,L2, R2); 
      return (L1>L2?L1:L2) + R2;
    }
    else        { //echo("e1");  
      r1=s1-e1+1; //echoln(", L2={}, R1={},R2={}",L2, R1,R2); 
      return L2 + (R1<R2?R1:R2);
    }
  }else if( w1 && !w2){ //echoln("▼:  w1 && !w2"); //▼
    assert(false); //return L1 + R1;
  }else{ //               echoln("|: !w1 && !w2");//|
    if(b1 && e1){ //echo("b1 && e1"); 
      l1=b1; r1=b1+1; l2=e1; r2=e1+1; 
    } else  if(b1){ //echo("b1");       
      l1=s1; r1=s1;   l2=1;  r2=1;
    } else { //echo("e1");       
      l1=1;  r1=1;    l2=s2; r2=s2;
    }
    //echoln(", L1={},L2={},R1={},R2={}",L1,L2,R1,R2);
    return (L1>L2?L1:L2) + (R1<R2?R1:R2);
  }

  return 0;
}

public:
  double findMedianSortedArrays(std::vector<int> &nums1, std::vector<int> &nums2) {
    int s1 = nums1.size(), s2 = nums2.size();
    double res;
    if(s1 < s2){
      res = sum(nums1,nums2, s1,s2); //sum(nums1,nums2, s1,s2, 0,0,0,0);
    }else{
      res = sum(nums2,nums1, s2,s1); //sum(nums2,nums1, s2,s1, 0,0,0,0);
    }
    res/=2.0;
    //echo("========================================================= res={}\n", res);
    return res;
  }

  private:
  void pv(std::vector<int> &n,  int s,  int b,int e,  int w,  int l,int r) {
    char delim[]{'\0','\0'};
    echo("s={:02},b={:02},e={:02},w={:02},l={:02},r={:02} : [",s,b,e,w,l,r);
    int i=1;
    for(; i<=b; ++i,delim[0]=',') echo("{}{}{}{}", delim, i==l||i==r?"<":"", n[i-1], i==l||i==r?">":"");
    echo("] [");delim[0]='\0';
    for(; i< e; ++i,delim[0]=',') echo("{}{}{}{}", delim, i==l||i==r?"<":"", n[i-1], i==l||i==r?">":"");
    echo("] [");delim[0]='\0';
    for(; i<=s; ++i,delim[0]=',') echo("{}{}{}{}", delim, i==l||i==r?"<":"", n[i-1], i==l||i==r?">":"");
    echo("]\n");
  }
  void pvs(std::vector<int> &n1,std::vector<int> &n2,  int s1,int s2,  int b1,int e1,  int w1,int w2,  int l1,int l2,int r1,int r2){
    pv(n1,s1, b1,s1-e1+1,w1,l1,r1);
    pv(n2,s2, e1,s2-b1+1,w2,l2,r2);
  }

};




//-------------------------------------------------------------------------

/* test proba()

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

  
  // {
  //   double d=0;
  //   std::vector<int> nums1;
  //   std::vector<int> nums2;
  //   nums1.insert(nums1.end(),{0,1,2,95});
  //   nums2.insert(nums2.end(),{1,3,60,70,80,90,100,101,102,103});
  //   d+=sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
  //   nums1.insert(nums1.end(),{0,1,3,60,70,80,90,100,101,102});
  //   nums2.insert(nums2.end(),{0,1,2,5,8,12,14,60,90,95});
  //   d+=sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
  //   nums1.insert(nums1.end(),{1,3,60,70,80,90,100,101,102,103});
  //   nums2.insert(nums2.end(),{0,1,2,5,8,12,14,60,90,95,110,111});
  //   d+=sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
  //   nums1.insert(nums1.end(),{1,3,60,70,80,90,100,101,102});
  //   nums2.insert(nums2.end(),{0,1,2,5,8,12,14,60,90,95,110,111});
  //   d+=sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
  //   nums1.insert(nums1.end(),{1,3,60,70,80,90,100,101,102,103});
  //   nums2.insert(nums2.end(),{1,2,5,8,12,14,60,90,95,110,111});
  //   d+=sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
  //   nums1.insert(nums1.end(),{1,3,60,70,80,90,100,101,102});
  //   nums2.insert(nums2.end(),{1,2,5,8,12,14,60,90,95,110,111});
  //   d+=sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
  //   nums1.insert(nums1.end(),{2});
  //   nums2.insert(nums2.end(),{1,3,5});
  //   d+=sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
  //   nums1.insert(nums1.end(),{4});
  //   nums2.insert(nums2.end(),{1,3,5});
  //   d+=sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
  //   nums1.insert(nums1.end(),{});
  //   nums2.insert(nums2.end(),{1});
  //   d+=sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();
  //   nums1.insert(nums1.end(),{1,3});
  //   nums2.insert(nums2.end(),{2,4,5});
  //   d+=sol.findMedianSortedArrays(nums1, nums2); nums1.clear(); nums2.clear();

  //   echo("d={}",d);//d=381.5
  // }
  
}

*/

//- - - - - - - - - - - -
//= = = = = = = = = = = = = = =
