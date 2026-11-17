// 04_medium_two_arrays.hpp
// 4. Median of Two Sorted Arrays
// https://leetcode.com/problems/median-of-two-sorted-arrays/description/
// clang-format off

#define ECHO
#include "sys.hpp"

#include <vector>

class Solution {
using vcr = std::vector<int>;
#define L1 n1[l1-1]
#define R1 n1[r1-1]
#define L2 n2[l2-1]
#define R2 n2[r2-1]

  int getL(int size) { //[1] => 1;  [1,2] => 1;  [1,2,3] => 2;  [1,2,3,4] => 2;  [1,2,3,4,5] => 3;  [1,2,3,4,5,6] => 3;  [1,2,3,4,5,6,7] => 4;  [1,2,3,4,5,6,7,8] => 4;
    return size / 2 + size%2; //add 1 to an odd
  }
  int getR(int size) { //[1] => 1;  [1,2] => 2;  [1,2,3] => 2;  [1,2,3,4] => 3;  [1,2,3,4,5] => 3;  [1,2,3,4,5,6] => 4;  [1,2,3,4,5,6,7] => 4;  [1,2,3,4,5,6,7,8] => 5
    return size / 2 + 1;
  }
  int sumLLRR(vcr n1,vcr n2,  int l1,int l2,int r1,int r2){
    return (L1>L2?L1:L2) + (R1<R2?R1:R2); //большее из левых + меньшее из правых
  }

  int f0(vcr n1,int s1,  vcr n2,int s2,  int s,int l,int r,  int depth=1,  int b1=0,int b2=0,int e1=0,int e2=0){
    int w1=s1-b1-e1, w2=s2-b2-e2;
    int l1=getL(w1)+b1, l2=getL(w2)+b2, r1=getR(w1)+b1, r2=getR(w2)+b2;
    int res=0;
    if(w1==0) {
      if(w2==0) {               //:::::  w1==0 && w2==0
        if(b1 && e2){
          if(b2 && e1) {        // (b1 && e2) && (b2 && e1)
            res = sumLLRR(n1,n2, b1,b2, s1-e1+1,s2-e2+1);
          }else{                // (b1 && e2)
            res = sumLLRR(n1,n2, b1,b1, s2-e2+1,s2-e2+1);
          }
        }else if(b2 && e1){     // (b2 && e1)
          res = sumLLRR(n1,n2, b2,b2, s1-e1+1,s1-e1+1);
        }
      }else{                    //:::::  w1==0
        res = L2+R2; 
      }
    }else{
      if(L1 > R2){
        e1 = s1-r1+1;
        b2 = e1;
        res = f0(n1,s1,  n2,s2,  s,l,r,  depth+1,  b1,b2, e1,e2);
      }else if(L2 > R1){
        b1 = l1;
        e2 = b1;
        res = f0(n1,s1,  n2,s2,  s,l,r,  depth+1,  b1,b2, e1,e2);
      }else{
        res = sumLLRR(n1,n2, l1,l2,r1,r2);
      }
    }
    return res;
  }

public:
  double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    int s1=nums1.size(), s2=nums2.size(), s=s1+s2, l=getL(s), r=getR(s);
    double res;
    if(s1<s2){//first smaller
      res = f0(nums1,s1,  nums2,s2,  s,l,r);
    }else{
      res = f0(nums2,s2,  nums1,s1,  s,l,r);
    }
    echo("res = {}\n", res);
    res/=2.0;
    echo("========================================================= res={}\n", res);
    return res;
  }

  private:
  void pv(vcr &n,int s,int b,int e,  int w,int l,int r){
    char delim[]{'\0','\0'};
    echo("s={:02},b={:02},e={:02},w={:02},l={:02},r={:02} : [",s,b,e,w,l,r);
    int i=1;
    for(; i<=  b; ++i,delim[0]=',') echo("{}{}{}{}", delim, i==l||i==r?"<":"", n[i-1], i==l||i==r?">":"");
    echo("] [");delim[0]='\0';
    for(; i<=s-e; ++i,delim[0]=',') echo("{}{}{}{}", delim, i==l||i==r?"<":"", n[i-1], i==l||i==r?">":"");
    echo("] [");delim[0]='\0';
    for(; i<=  s; ++i,delim[0]=',') echo("{}{}{}{}", delim, i==l||i==r?"<":"", n[i-1], i==l||i==r?">":"");
    echo("]\n");
  }
  void pvs(vcr n1,int s1,  vcr n2,int s2,  int s,int l,int r,  int depth,  int b1=0,int b2=0,int e1=0,int e2=0,int w1=0,int w2=0,  int l1=0,int l2=0,int r1=0,int r2=0){
    pv(n1,s1, b1,e1,w1,l1,r1);
    pv(n2,s2, b2,e2,w2,l2,r2);
    echo("s={},l={},r={},depth={}\n", s,l,r, depth);
  }


};
