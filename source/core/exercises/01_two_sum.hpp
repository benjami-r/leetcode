// 01_two_sum.hpp
// clang-format off 
//РЕШИЛ НЕПЛОХО. НИЖЕ ЕСТЬ 2 ЦЕННЫХ УЛУЧШЕНИЯ ОТ GEMINI: 1) СОРТИРОВКА ИНДЕКСОВ ВМЕСТО СОРТИРОВКИ ЭЛЕМЕНТОВ, И 2) ИДЕАЛЬНОЕ РЕШЕНИЕ ХЕШ-ТАБЛИЦЕЙ.

//1. Two Sum
//You are given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
//You may assume that each input would have exactly one solution, and you may not use the same element twice.
//You can return the answer in any order.
//Example 1:
//Input: nums = [2,7,11,15], target = 9
//Output: [0,1]
//Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
//Example 2:
//Input: nums = [3,2,4], target = 6
//Output: [1,2]
//Example 3:
//Input: nums = [3,3], target = 6
//Output: [0,1]
//Constraints:
//    2 <= nums.length <= 10^4
//    -10^9 <= nums[i] <= 10^9
//    -10^9 <= target <= 10^9
//    Only one valid answer exists.
//Follow-up: Can you come up with an algorithm that is less than O(n^2) time complexity?

#include <vector>
#include <algorithm>

class Solution { //Второе успешное решение, время Runtime 0ms Beats100.00%, Memory 14.80MB, Beats58.41%

public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
      std::vector<int> tmp = nums;
      std::ranges::sort(tmp);
      int i=0,j=nums.size()-1, s;
      while(true) { //i<j
        s = tmp[i]+tmp[j];
        if (s<target){
          ++i;
        } else if (s>target){
          --j;
        } else break;
      }
      int a=-1,b=-1;
      for(int k = 0; k<nums.size(); ++k){
        if(nums[k]==tmp[i]) {if(a<0){a=k; continue;}}
        if(nums[k]==tmp[j]) {b=k;}
        if(a>=0 && b>=0) break; //надо?
      }
      return {a,b};
    }
};

// class Solution { //Первое успешное решение, время Runtime 43ms Beats26.16%, 14.11MB Beats76.44%
// public:
//     std::vector<int> twoSum(std::vector<int>& nums, int target) {
//       for(int i = 0; i<nums.size()-1; ++i){
//         for(int j = i+1; j<nums.size(); ++j){
//           if(nums[i]+nums[j]==target) return {i,j};
//         }
//       }
//       return {-1,-1};
//     }
// };



//Предложенные Gemini два подхода (не делал):
// - 1й - улучшение моего через сортировку индексов элементов, а не самих элементов (универсален для любого типа элементов, даже громадных, и не требует второго цикла поиска индексов элементов в исходном векторе, а сама косвенная адресация довольно дешевая).
// - 2й - идеальный, на хэш-таблице.
//Цитирую:
//1й: 
// #include <vector>
// #include <numeric>   // для std::iota
// #include <algorithm> // для std::ranges::sort
// class Solution {
// public:
//     std::vector<int> twoSum(std::vector<int>& nums, int target) {
//         int n = nums.size();
//         // Создаем вектор индексов: [0, 1, 2, ..., n-1]
//         std::vector<int> indices(n);
//         std::iota(indices.begin(), indices.end(), 0);
//         // Сортируем индексы на основе значений в nums
//         std::ranges::sort(indices, [&](int a, int b) {
//             return nums[a] < nums[b];
//         });
//         int i = 0, j = n - 1;
//         while (i < j) {
//             int s = nums[indices[i]] + nums[indices[j]];
//             if (s < target) {
//                 ++i;
//             } else if (s > target) {
//                 --j;
//             } else {
//                 return {indices[i], indices[j]}; // Сразу возвращаем реальные индексы!
//             }
//         }
//         return {};
//     }
// };
//Нет двусмысленного поиска элементов по второму кругу, нет дублирования самого массива nums (сортируются только легкие индексы). Сложность по времени: O(nlogn), по памяти: O(n) на вектор индексов.

//2й: Идеальное решение за один проход — O(n) (Хэш-таблица)
//Профессиональный канонический способ решения классической Two Sum — использование std::unordered_map (хэш-таблицы). Мы идем по массиву один раз и для каждого элемента проверяем: «А не встречали ли мы уже число, дополняющее текущее до target?».
// #include <vector>
// #include <unordered_map>
// class Solution {
// public:
//     std::vector<int> twoSum(std::vector<int>& nums, int target) {
//         std::unordered_map<int, int> seen; // число -> его индекс
//         for (int i = 0; i < nums.size(); ++i) {
//             int complement = target - nums[i];    
//             // Если искомое число уже есть в мапе — мы нашли пару!
//             if (seen.find(complement) != seen.end()) {
//                 return {seen[complement], i};
//             }
//             // Запоминаем текущее число и его индекс
//             seen[nums[i]] = i;
//         }
//         return {};
//     }
// };
//Возможные коллизии <unordered_map> разрешает классическим методом цепочек (Separate Chaining).
// Почему это круче:
//   Время: O(n) вместо O(nlogn) из-за сортировки. Код отработает не просто за 0 мс, а принципиально быстрее на больших массивах.
//   Код короче: Всего один цикл и минимум логики.


/* //= = = = = = = = = = = = = = = run

//- - - - - - - - - - - - proba
#define ECHO
#include "sys.hpp"
//=============================

#include "01_two_sum.hpp"

void proba() {
  echo("{}\n", "PROBA");

  std::vector<int> numbers1 = {2,7,11,15};
  int target1 = 9;
  Solution sol1;
  std::vector<int> result1 = sol1.twoSum(numbers1, target1); //auto result
  echo("result = [{},{}]\n", result1[0], result1[1]);

  std::vector<int> numbers2 = {3,2,4};
  int target2 = 6;
  Solution sol2;
  std::vector<int> result2 = sol2.twoSum(numbers2, target2); //auto result
  echo("result = [{},{}]\n", result2[0], result2[1]);

  std::vector<int> numbers3 = {3,3};
  int target3 = 6;
  Solution sol3;
  std::vector<int> result3 = sol3.twoSum(numbers3, target3); //auto result
  echo("result = [{},{}]\n", result3[0], result3[1]);

  std::vector<int> numbers4 = {-1,-2,-3,-4,-5};
  int target4 = -8;
  Solution sol4;
  std::vector<int> result4 = sol4.twoSum(numbers4, target4); //auto result
  echo("result = [{},{}]\n", result4[0], result4[1]);
}

*/
