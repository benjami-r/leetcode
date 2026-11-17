// 04_medium_two_arrays.hpp
// 4. Median of Two Sorted Arrays
// https://leetcode.com/problems/median-of-two-sorted-arrays/description/
// clang-format off

#define ECHO
#include "sys.hpp"
#include <vector>
using vcr = std::vector<int>;


class Solution {
  static constexpr int L1_MORE_THAN_R2{1100000}, L2_MORE_THAN_R1{-1100000};
  int getL(int size) { //[1] => 1;  [1,2] => 1;  [1,2,3] => 2;  [1,2,3,4] => 2;  [1,2,3,4,5] => 3;  [1,2,3,4,5,6] => 3;  [1,2,3,4,5,6,7] => 4;  [1,2,3,4,5,6,7,8] => 4;
    return size / 2 + size%2; //add 1 to an odd
  }
  int getR(int size) { //[1] => 1;  [1,2] => 2;  [1,2,3] => 2;  [1,2,3,4] => 3;  [1,2,3,4,5] => 3;  [1,2,3,4,5,6] => 4;  [1,2,3,4,5,6,7] => 4;  [1,2,3,4,5,6,7,8] => 5
    return size / 2 + 1;
  }
  double min(int a, int b){return a<b?a:b;}
  double max(int a, int b){return a<b?b:a;}

  double cross_comparison(int l1, int r1, int l2, int r2){
    if(l1>r2) return L1_MORE_THAN_R2;
    if(l2>r1) return L2_MORE_THAN_R1;
    return (max(l1,l2)+min(r1,r2)) / 2.0;
  }



  double f0(vcr n1,int s1,  vcr n2,int s2,  int s,int l,int r,  int depth=1,  int b1=0,int b2=0,int e1=0,int e2=0){
    double res=0.0;
    int w1=s1-b1-e1, w2=s2-b2-e2;
    int l1=getL(w1)+b1, l2=getL(w2)+b2, r1=getR(w1)+b1, r2=getR(w2)+b2;
    pvs(n1,s1,  n2,s2,  s,l,r,  depth, b1,b2,e1,e2,w1,w2,  l1,l2,r1,r2);
    if(depth==1){echo("Stop at depth={}\n",depth); return 0.0;}
    if( !(w1%2) && !(w2%2) ){//even,even
      echo("even,even\n");
      // if(!w1){
      //   if(!w2){
      //     if(b1 && e2)
      //   }
      // }
      if( n1[l1-1] <= n2[r2-1] ){//across ('''\...)
        echo("across\\=Yes ({}\\{})\n",n1[l1-1],n2[r2-1]);
        if( n2[l2-1] <= n1[r1-1]){//across (.../''')
          echo("across/=Yes ({}/{})\n",n2[l2-1],n1[r1-1]);
          return (n1[l1-1]>n2[l2-1]?n1[l1-1]:n2[l2-1]) + (n1[r1-1]<n2[r2-1]?n1[r1-1]:n2[r2-1]); //большее из левых + меньшее из правых
        }else{
          echo("across/=No ({}/{})\n",n2[l2-1],n1[r1-1]);
          b1=l1;
          e2=b1;
          res=f0(n1,s1,  n2,s2,  s,l,r,  depth+1,  b1,b2, e1,e2);
        }
      }else{
        echo("across\\=No ({}\\{})\n",n1[l1-1],n2[r2-1]);
        e1=s1-r1+1;
        b2=e1;
        res=f0(n1,s1,  n2,s2,  s,l,r,  depth+1,  b1,b2, e1,e2);
      }
    }else if( (w1%2) && !(w2%2) ){ // ab< 2 >de  ОДИНАКОВО (но можно упростить)
      echo("odd,even\n");          //qwr<4 5>lkj
      if( n1[l1-1] <= n2[r2-1] ){//across ('''\...)
        echo("across\\=Yes ({}\\{})\n",n1[l1-1],n2[r2-1]);
        if( n2[l2-1] <= n1[r1-1]){//across (.../''')
          echo("across/=Yes ({}/{})\n",n2[l2-1],n1[r1-1]);
          return (n1[l1-1]>n2[l2-1]?n1[l1-1]:n2[l2-1]) + (n1[r1-1]<n2[r2-1]?n1[r1-1]:n2[r2-1]); //большее из левых + меньшее из правых
        }else{
          echo("across/=No ({}/{})\n",n2[l2-1],n1[r1-1]);
          b1=l1;
          e2=b1;
          res=f0(n1,s1,  n2,s2,  s,l,r,  depth+1,  b1,b2, e1,e2);
        }
      }else{
        echo("across\\=No ({}\\{})\n",n1[l1-1],n2[r2-1]);
        e1=s1-r1+1;
        b2=e1;
        res=f0(n1,s1,  n2,s2,  s,l,r,  depth+1,  b1,b2, e1,e2);
      }


    }else if( !(w1%2) && (w2%2) ){ // ab<4 5>de  ОДИНАКОВО (но можно упростить)
      echo("even,odd\n");          //qwr< с >lkj
      if( n1[l1-1] <= n2[r2-1] ){//across ('''\...)
        echo("across\\=Yes ({}\\{})\n",n1[l1-1],n2[r2-1]);
        if( n2[l2-1] <= n1[r1-1]){//across (.../''')
          echo("across/=Yes ({}/{})\n",n2[l2-1],n1[r1-1]);
          return (n1[l1-1]>n2[l2-1]?n1[l1-1]:n2[l2-1]) + (n1[r1-1]<n2[r2-1]?n1[r1-1]:n2[r2-1]); //большее из левых + меньшее из правых
        }else{
          echo("across/=No ({}/{})\n",n2[l2-1],n1[r1-1]);
          b1=l1;
          e2=b1;
          res=f0(n1,s1,  n2,s2,  s,l,r,  depth+1,  b1,b2, e1,e2);
        }
      }else{
        echo("across\\=No ({}\\{})\n",n1[l1-1],n2[r2-1]);
        e1=s1-r1+1;
        b2=e1;
        res=f0(n1,s1,  n2,s2,  s,l,r,  depth+1,  b1,b2, e1,e2);
      }


    }else{
      echo("odd,odd\n");
      if(w1==1 || w2==1) return n1[l1-1] + n2[r2-1];
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
