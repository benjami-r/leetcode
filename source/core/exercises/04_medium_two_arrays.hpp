// 04_medium_two_arrays.hpp
// 4. Median of Two Sorted Arrays
// https://leetcode.com/problems/median-of-two-sorted-arrays/description/
// clang-format off

#define ECHO
#include "sys.hpp"

#include <vector>

using vcr = std::vector<int>;
#define L1 n1[l1-1]
#define L2 n2[l2-1]
#define R1 n1[r1-1]
#define R2 n2[r2-1]

class Solution {
  int getL(int size) { //[]=>0; [1]=>1; [1,2]=>1; [1,2,3]=>2; [1,2,3,4]=>2; [1,2,3,4,5]=>3; [1,2,3,4,5,6]=>3; [1,2,3,4,5,6,7]=>4; [1,2,3,4,5,6,7,8]=>4;
    return size / 2 + size%2; //add 1 to an odd
  }
  int getR(int size) { //[]=>1; [1]=>1; [1,2]=>2; [1,2,3]=>2; [1,2,3,4]=>3; [1,2,3,4,5]=>3; [1,2,3,4,5,6]=>4; [1,2,3,4,5,6,7]=>4; [1,2,3,4,5,6,7,8]=>5;
    return size / 2 + 1;
  }
  int getSum(vcr &n1,vcr &n2,  int l1, int l2, int r1, int r2){
    return (L1>L2?L1:L2) + (R1<R2?R1:R2);
  }

  int f0(vcr &n1,vcr &n2, int s1,int s2,  int b1,int b2,int e1,int e2,  int depth=1){
    int w1=e1-b1-1, w2=e2-b2-1;
    int l1=getL(w1)+b1, l2=getL(w2)+b2, r1=getR(w1)+b1, r2=getR(w2)+b2;

    pvs(n1,n2, s1,s2, b1,b2,e1,e2, w1,w2, l1,l2,r1,r2);
    //if(depth==4){echo("Depth={}, stop.\n", depth); return 20000000;}

    if(w1 && w2){
      if(L1>R2){
        e1=l1;
        b2=s1-e1+1;
        return f0(n1,n2, s1,s2, b1,b2,e1,e2, depth+1);
      }
      if(L2>R1){
        b1=r1;
        e2=s2-b1+1;
        return f0(n1,n2, s1,s2, b1,b2,e1,e2, depth+1);
      }
      return (L1>L2?L1:L2) + (R1<R2?R1:R2);
    }else if(!w1 && !w2){
        if(b1 && b2) return getSum(n1,n2, b1,b2,e1,e2);
        if(b1)       return n1[s1-1] + n2[0];
        if(b2)       return n2[s2-1] + n1[0];
        return  20000000;
    }else{ // if(w1==0)
        if(b1 && b2) return getSum(n1,n2, b1,l2,e1,r2);
        echo("b1={}, n1[b1-1]={}, L2={}, R2={}", b1, n1[b1-1], L2, R2);
        //Проблема: если s нечет, нужно дважды брать элемент из b1, а не n1[b1-1] + R2
        if(b1)       return (n1[b1-1]>L2?n1[b1-1]:L2) + R2;
        if(b2)       return L2 + (n1[e1-1]<R2?n1[e1-1]:R2);
        return L2 + R2;
    }
    //return  20000000;
  }
public:
  double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    int s1 = nums1.size(), s2 = nums2.size();
    double res;
    if(s1 < s2){
      res = f0(nums1,nums2, s1,s2, 0,0,s1+1,s2+1);
    }else{
      res = f0(nums2,nums1, s2,s1, 0,0,s2+1,s1+1);
    }
    res/=2.0;
    echo("========================================================= res={}\n", res);
    return res;
  }

  private:
  void pv(vcr &n,int s,int b,int e,  int w,int l,int r){
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
  void pvs(vcr n1,vcr n2,  int s1,int s2,  int b1,int b2,int e1,int e2,  int w1,int w2,  int l1,int l2,int r1,int r2){
    pv(n1,s1, b1,e1,w1,l1,r1);
    pv(n2,s2, b2,e2,w2,l2,r2);
  }

};
