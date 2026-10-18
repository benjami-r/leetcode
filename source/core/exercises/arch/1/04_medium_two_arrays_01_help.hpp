// 04_medium_two_arrays.hpp
// 4. Median of Two Sorted Arrays
// https://leetcode.com/problems/median-of-two-sorted-arrays/description/
// clang-format off

#include <cstddef>
#define ECHO
#include "sys.hpp"

#include <vector>
//#include <span>

class Solution {
  using vcr = std::vector<int>;
  using spn = std::span<int>;
  //using szt = int;

  
  int getL(int size) { //[1] => 1;  [1,2] => 1;  [1,2,3] => 2;  [1,2,3,4] => 2;  [1,2,3,4,5] => 3;  [1,2,3,4,5,6] => 3;  [1,2,3,4,5,6,7] => 4;  [1,2,3,4,5,6,7,8] => 4;
    return size / 2 + (size%2 ? 1 : 0); //к нечетному добавляем 1
  }
  int getR(int size) { //[1] => 1;  [1,2] => 2;  [1,2,3] => 2;  [1,2,3,4] => 3;  [1,2,3,4,5] => 3;  [1,2,3,4,5,6] => 4;  [1,2,3,4,5,6,7] => 4;  [1,2,3,4,5,6,7,8] => 5
    return size / 2 + 1;
  }
//------------------------------------
  double f1(vcr &n1,int s1,int b1,int e1, vcr &n2,int s2,int b2,int e2, int l, int r, int i=0){
    pvs(n1,b1,e1, n2,b2,e2, l,r);
    if(i==1) return 1;
    double res=0;
    int l1=b1+getL(s1-b1-e1), l2=l-l1; //l2 -сколько элементов из n2 должно стать слева, чтобы l1 стал l. А значит n1[l1-1] сравнмваем с элементами [l2-1] и [l2] в n2, и если n1[l1-1] больше-равен n2[l2-1] и меньше-равен n2[l2], то l1=l, первый элемеет найден.
    if(n1[l1-1]>=n2[l2-1] && n1[l1]<=n2[l2]) //то l1 найдено
//Можно сразу так: допустим в n1 10 элементов, а в n2 - 3. Тогда l=7. Стало быть, если n1[4-1]>n2[3-1], то весь n2 стал слева от n1[4-1], и l найден (l=3+3+1), т.е. седьмой слева. Смотрим справа: если n1[7-1]<n2[1-1], то весь n2 стал справа от n1[7-1], и l найден (l=13-3-3, т.е. седьмой справа).


    return res;
  }

  double f0(vcr &n1,int s1, vcr &n2,int s2){
    double res=0;
    //int l=; //так или иначе, нужно найти именно этот по порядку элемент в условно слитом массиве
    res = f1(n1,s1,0,0, n2,s2,0,0, getL(s1+s2),getR(s1+s2));
    return res;
  }
//int* last = nums.data() + nums.size() - 1;
//int* last = nums.empty() ? nullptr : &nums.back();

// сравнивать сразу l1,l2 - в начале это середины, а потом - насколько улетают

//++++++++++++++++++++++++++++++++++++ // [a,b,c,..d,e,..f,g,h]   [l,m,..r,s,t,..u,v]
public:
  double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    int s1=nums1.size(), s2=nums2.size();
    return ( s1>=s2 ? f0(nums1,s1, nums2,s2) : f0(nums2,s2, nums1,s1) ) / 2.0;
  }
private:
  void pv(vcr &n,int b,int e){ //b,e - начало и конец рабочего куска
    assert(b>=0 && e>=0 && b+e<=(int)n.size());

    int l=b+getL((int)n.size()-b-e);
    char delim[]{'\0','\0'};
    int i=1;
    echo("n: {{[");
    for(;i<=b;++i)                               {echo("{}{}{}{}", delim,i==l?"<":"",n[i-1],i==l?">":""); delim[0]=',';} 
    echo("] ["); delim[0]='\0';
    for(;i>b&&i<=(int)n.size()-e;++i)            {echo("{}{}{}{}", delim,i==l?"<":"",n[i-1],i==l?">":""); delim[0]=',';} 
    echo("] ["); delim[0]='\0';
    for(;i>(int)n.size()-e&&i<=(int)n.size();++i){echo("{}{}{}{}", delim,i==l?"<":"",n[i-1],i==l?">":""); delim[0]=',';}
    echo("]}}\n");
  }
  void pvs(vcr &n1,int b1,int e1,  vcr &n2,int b2,int e2, int l, int r){
    pv(n1,b1,e1);
    pv(n2,b2,e2);
    echo("l={}, r={}\n", l,r);
  }

};


// [a,b,c,..d,e,..f,g,h]   [l,m,..r,s,t,..u,v]


  // int getL(int size) { //[1] => 0;  [1,2] => 0;  [1,2,3] => 1;  [1,2,3,4] => 1;  [1,2,3,4,5] => 2;  [1,2,3,4,5,6] => 2;  [1,2,3,4,5,6,7] => 3;  [1,2,3,4,5,6,7,8] => 3; заодно показывает сколько элементов слева
  //   return size / 2 - (size%2 ? 0 : 1); //у четного вычитаем 1
  // }
  // int getR(int size) { //[1] => 0;  [1,2] => 1;  [1,2,3] => 1;  [1,2,3,4] => 2;  [1,2,3,4,5] => 2;  [1,2,3,4,5,6] => 3;  [1,2,3,4,5,6,7] => 3;  [1,2,3,4,5,6,7,8] => 4
  //   return size / 2;
  // }

  // int get_l(int size) { //[1] => 1;  [1,2] => 1;  [1,2,3] => 2;  [1,2,3,4] => 2;  [1,2,3,4,5] => 3;  [1,2,3,4,5,6] => 3;  [1,2,3,4,5,6,7] => 4;  [1,2,3,4,5,6,7,8] => 4;
  //   return size / 2 + (size%2 ? 1 : 0); //к нечетному добавляем 1
  // }
  // int get_r(int size) { //[1] => 1;  [1,2] => 2;  [1,2,3] => 2;  [1,2,3,4] => 3;  [1,2,3,4,5] => 3;  [1,2,3,4,5,6] => 4;  [1,2,3,4,5,6,7] => 4;  [1,2,3,4,5,6,7,8] => 5
  //   return size / 2 + 1;
  // }



// double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
//     int s1 = nums1.size();
//     int s2 = nums2.size();
//     int s  = s1 + s2;
//     int l  = get_l(s); //с 1
//     int r  = get_r(s); //с 1
//     if(s1==0) return (nums2[l-1] + nums2[r-1]) / 2.0; //nums1 is empty
//     if(s2==0) return (nums1[l-1] + nums1[r-1]) / 2.0; //nums2 is empty
//     if(nums1[s1-1]<=nums2[0]) return ((l<=s1 ? nums1[l-1] : nums2[l-s1-1]) + (r<=s1 ? nums1[r-1] : nums2[r-s1-1])) / 2.0; //joining: [nums1nums2]
//     if(nums2[s2-1]<=nums1[0]) return ((l<=s2 ? nums2[l-1] : nums1[l-s2-1]) + (r<=s2 ? nums2[r-1] : nums1[r-s2-1])) / 2.0; //joining: [nums2nums1]
//     //f(nums1,nums2,1,s1,1,s2);
//     return 0.0;
//   } 

//Идея: виртуальные индексы - от 1000 - n1, от 2000 - n2 (но она не универсальна).
//вертим: n1 - в котором ищем l, если он в n2 - вертим, передавая пересчитанные индексы

