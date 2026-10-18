// 03_longest_substring.hpp
// clang-format off
// https://leetcode.com/problems/longest-substring-without-repeating-characters/description/
// #define ECHO
// #include "sys.hpp"

#include <string>
// #include <unordered_map>

class Solution {
public:
  int lengthOfLongestSubstring(std::string s) {
    constexpr std::size_t FREE = 100001, SIZE = 128;
    std::size_t arr[SIZE];
    for (std::size_t j = 0; j < SIZE; ++j) arr[j] = FREE;
    int max = 0, cur = 0, start = 0;
    for (std::size_t i = 0; s[i]!='\0'; ++i) {
      std::size_t id = s[i];
      if (arr[id] == FREE) {
        arr[id] = i;
        ++cur;
      } else {
        if (max < cur) max = cur;
        for(std::size_t j = start; j<arr[id]; ++j) arr[s[j]]=FREE;
        cur = cur - (arr[id] - start);
        start = arr[id] + 1;
        arr[id] = i;
      }
    }
    if (max < cur) max = cur;
    return max;
  }
};



//- - - - - - - - - - - - proba
#define ECHO
#include "sys.hpp"
//=============================


/*-------------------PROBA
#include <string>
#include "03_longest_substring.hpp"

void proba() {
  echo("{}\n", "PROBA");

  Solution sol;
  std::string s = "bbaaabbbbbaaaabbbbbabaaaaaababaaabbbbbabbbababaaaabbbbbabbbaaaababababbaabaaabbaabbaabaaabaaababbababbaaabababaabbbbababababaaaaababbabbaaabbabbaaaaabbbbbbbaaaaaaabbaaaaabbaaababaaaaaabbbabbaababaababbbaaaabbbaaabbaaaababaaababbaaaabababbbbababbabbaabababbaababbaaababbaaabbbbabbbbbbababbbababaaaaaaaabaaabbbbababaaaaaababbababbabaabbabbbaababbbaabbbbbbbbababbabaaabaabbaabbbbabbbbbabbbbaababababaabbaaabbbbbbabbabaaabbbbabbbbaaaabaaaa";
  //std::string s = "aBcdeBghB";
  echo("RES: max={}", sol.lengthOfLongestSubstring(s));
}
*/
