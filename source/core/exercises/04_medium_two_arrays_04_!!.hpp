// 04_medium_two_arrays.hpp
// 4. Median of Two Sorted Arrays
// https://leetcode.com/problems/median-of-two-sorted-arrays/description/
// clang-format off

#define ECHO
#include "sys.hpp"

#include <vector>

class Solution {
  using vcr = std::vector<int>;

//------------------------------------//pvs(n1,s1,b1,e1,l1, n2,s2,b2,e2,l2, s,l,r);

  double f0(vcr n1,int s1,int b1,int e1, vcr n2,int s2,int b2,int e2, int s,int l,int r, int depth=1){
    int w1=s1-b1-e1; //if(w1==0) 
    int l1=w1/2+1;
    int w2=s2-b2-e2; //if(w2==0)
    int l2=l-l1+1;
    /*DBG*/pvs(n1,s1,b1,e1,w1,l1, n2,s2,b2,e2,w2,l2, s,l,r);
    /*DBG*/int CTRLDEPTH=3; if(depth==CTRLDEPTH) {echo("Stop depth={}\n",CTRLDEPTH); return -CTRLDEPTH;}
    if(n1[l1-1] <= n2[l2-1]){ //может быть результирующим если слева от n2[l2-1] нет элемента меньше него
      if(l2==b2+1 || n1[l1-1]>=n2[l2-2]) return n1[l1-1] + n1[l1-1];//tmp
      b1=l1;
      e2=l2;
      return f0(n1,s1,b1,e1,  n2,s2,b2,e2,  s,l,r,   depth+1);
    }else{ //n1[l1-1] > n2[l2-1]
      return f0(n2,s2,b2,e2,  n1,s1,b1,e1,  s,l,r,   depth+1);
    }

    
    return 0.0;
  }

//++++++++++++++++++++++++++++++++++++ // [a,b,c,..d,e,..f,g,h]   [l,m,..r,s,t,..u,v]
public:
  double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    int s1=nums1.size(), s2=nums2.size(), s=s1+s2, l=s/2+s%2, r=s/2+1;
    double res;
    if(s1>=s2) {
      if(s2==0) res=nums1[l-1]+nums1[s/2]; else res=f0(nums1,s1,0,0, nums2,s2,0,0, s,l,r);
    } else {
      if(s1==0) res=nums2[l-1]+nums2[s/2]; else res=f0(nums2,s2,0,0, nums1,s1,0,0, s,l,r);
    }
    // res=f0(nums1,s1,0,0, nums2,s2,0,0, s,l,r);
    echo("res={}\n",res/2.0);
    echo("=============================================================\n");
    return res/2.0;
  }

//pppppppppppppppppppppppppppppppppppp
private:
  void pv(vcr &n,int s,int b,int e,int w,int l){
    char delim[]{'\0','\0'};
    echo("s={:02},b={:02},e={:02},w={:02},l={:02} : [",s,b,e,w,l);
    // for(int i=1; i<=s; ++i){
    //   if(i==b+1) {echo("] [");delim[0]='\0';}
    //   echo("{}{}{}{}", delim, i==l?"<":"", n[i-1], i==l?">":""); delim[0]=',';
    //   if(i==s-e) {echo("] [");delim[0]='\0';}
    // }
    int i=1;
    for(; i<=  b; ++i,delim[0]=',') echo("{}{}{}{}", delim, i==l?"<":"", n[i-1], i==l?">":"");
    echo("] [");delim[0]='\0';
    for(; i<=s-e; ++i,delim[0]=',') echo("{}{}{}{}", delim, i==l?"<":"", n[i-1], i==l?">":"");
    echo("] [");delim[0]='\0';
    for(; i<=  s; ++i,delim[0]=',') echo("{}{}{}{}", delim, i==l?"<":"", n[i-1], i==l?">":"");
    echo("]\n");
  }
  void pvs(vcr n1,int s1,int b1,int e1,int w1,int l1,  vcr n2,int s2,int b2,int e2,int w2,int l2,  int s,int l,int r){
    pv(n1,s1,b1,e1,w1,l1);
    pv(n2,s2,b2,e2,w2,l2);
    //echo("__________________________________________________s={},l={},r={}\n", s,l,r);
    echo("s={},l={},r={}\n", s,l,r);
  }

};




  // int getL(int size) { //[1] => 1;  [1,2] => 1;  [1,2,3] => 2;  [1,2,3,4] => 2;  [1,2,3,4,5] => 3;  [1,2,3,4,5,6] => 3;  [1,2,3,4,5,6,7] => 4;  [1,2,3,4,5,6,7,8] => 4;
  //   return size / 2 + (size%2 ? 1 : 0); //к нечетному добавляем 1
  // }
  // int getR(int size) { //[1] => 1;  [1,2] => 2;  [1,2,3] => 2;  [1,2,3,4] => 3;  [1,2,3,4,5] => 3;  [1,2,3,4,5,6] => 4;  [1,2,3,4,5,6,7] => 4;  [1,2,3,4,5,6,7,8] => 5
  //   return size / 2 + 1;
  // }



  // void pv(int id, vcr &n,int s,int b,int e,int w,int l){ //b,e - начало и конец рабочего куска
  //   char delim[]{'\0','\0'};
  //   echo("n{0}={1}: s{0}={2:02}, b{0}={3:02}, e{0}={4:02}, (w{0}={5:02}), l{0}={6:02} : \n[", id,(void*)&n,s,b,e,w,l);
  //   for(int i=1; i<=s; ++i){
  //     echo("{}{}{}{}", delim, i==l?"<":"", n[i-1], i==l?">":""); delim[0]=',';  
  //   }
  //   echo("]\n");
  // }
  // void pvs(vcr n1,int s1,int b1,int e1,int w1,int l1,  vcr n2,int s2,int b2,int e2,int w2,int l2,  int s,int l,int r){
  //   pv(1, n1,s1,b1,e1,w1,l1);
  //   pv(2, n2,s2,b2,e2,w2,l2);
  //   echo("___s={},___l={},___r={}___\n", s,l,r);
  // }




//------------v
   // assert(s2>0);
    // double res=0.0;
    // int w2=s2-b2-e2;
    // int l2=w2/2+w2%2 + b2;
    // assert(l2>b2 && l2<=s2-e2);
    // int l1=l-l2;
    // echo("To assert: l1={},b1={},s1={},e1={}\n",l1,b1,s1,e1);
    // assert(l1>b1 && l1<=s1-e1);

    // pvs(n1,s1,l1,b1,e1, n2,s2,l2,b2,e2, s,l);
    // if(depth==6) {echo("DEPTH.\n");return 2.0;} else {echo("NEXT\n");}

    // if(n1[l1-1] >= n2[l2-1]){ 
    //   {//проверка на окончание поиска
    //     if(l2==s2-e2 || n1[l1-1]<=n2[l2]){//l2 - смотрим справа от сверяемого в n2
    //       return n1[l1-1] * 2;
    //     }
    //   }
    //   e1=s1-l1+1;
    //   b2=l2;
    //   res=f0(n1,s1,b1,e1, n2,s2,b2,e2, s,l, depth+1);
    // }else{
    //   res=f0(n2,s2,b2,e2, n1,s1,b1,e1, s,l, depth+1);
    // }
    // return res;
//------------^
