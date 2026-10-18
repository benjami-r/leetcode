// 04_medium_two_arrays.hpp
// 4. Median of Two Sorted Arrays
// https://leetcode.com/problems/median-of-two-sorted-arrays/description/
// clang-format off

#define ECHO
#include "sys.hpp"

#include <vector>

class Solution {
  using vcr = std::vector<int>;

  int getL(int size) { //[1] => 1;  [1,2] => 1;  [1,2,3] => 2;  [1,2,3,4] => 2;  [1,2,3,4,5] => 3;  [1,2,3,4,5,6] => 3;  [1,2,3,4,5,6,7] => 4;  [1,2,3,4,5,6,7,8] => 4;
    return size / 2 + (size%2 ? 1 : 0); //к нечетному добавляем 1
  }
  int getR(int size) { //[1] => 1;  [1,2] => 2;  [1,2,3] => 2;  [1,2,3,4] => 3;  [1,2,3,4,5] => 3;  [1,2,3,4,5,6] => 4;  [1,2,3,4,5,6,7] => 4;  [1,2,3,4,5,6,7,8] => 5
    return size / 2 + 1;
  }
  
//------------------------------------//pvs(n1,s1,b1,e1,s1-b1-e1,0, n2,s2,b2,e2,s2-b2-e2,0, s,l,r);
  double f0(vcr n1,int s1,int b1,int e1,  vcr n2,int s2,int b2,int e2,  int s,int l,int r, int i=0){
    int w1=s1-b1-e1, w2=s2-b2-e2; //b,e - сколько отброшено
    int l1=getL(w1), l2=getL(w2)-(w1%2 && w2%2), r1=0, r2=0;
    double res=0.0;
    pvs(n1,s1,b1,e1,w1,l1, n2,s2,b2,e2,w2,l2, s,l,r);

    if(w2==0){
      //res=n1[l1-1]+n1[r1-1];
    }else{
      l2=getL(s2)-(s1%2 && s2%2);
      if(n1[l1-1]>n2[l2-1]){
        //проверка на найденность
        //if()

      }
    }

    return res;
    return 0.0;
  }

//++++++++++++++++++++++++++++++++++++ // [a,b,c,..d,e,..f,g,h]   [l,m,..r,s,t,..u,v]
public:
  double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    int s1=nums1.size();
    int s2=nums2.size();
    int s=s1+s2, l=getL(s), r=getR(s);
    return (s1>s2 ? f0(nums1,s1,0,0, nums2,s2,0,0, s,l,r) : f0(nums2,s2,0,0, nums1,s1,0,0, s,l,r)) / 2.0;
  }

//pppppppppppppppppppppppppppppppppppp
private:
  void pv(int id, vcr &n,int s,int b,int e,int w,int l){ //b,e - начало и конец рабочего куска
    char delim[]{'\0','\0'};
    echo("n{0}={1}: s{0}={2:02}, b{0}={3:02}, e{0}={4:02}, (w{0}={5:02}), l{0}={6:02} : \n[", id,(void*)&n,s,b,e,w,l);
    for(int i=1; i<=s; ++i){
      echo("{}{}{}{}", delim, i==l?"<":"", n[i-1], i==l?">":""); delim[0]=',';  
    }
    echo("]\n");
  }
  void pvs(vcr n1,int s1,int b1,int e1,int w1,int l1,  vcr n2,int s2,int b2,int e2,int w2,int l2,  int s,int l,int r){
    pv(1, n1,s1,b1,e1,w1,l1);
    pv(2, n2,s2,b2,e2,w2,l2);
    echo("___s={},___l={},___r={}___\n", s,l,r);
  }

};

