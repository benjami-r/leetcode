// clang-format off
// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wc99-extensions"
//- - - - - - - - - - - - proba
#define ECHO
#include "sys.hpp"
//=============================




#include "02_add_two_nums.hpp"

void proba() {
  echo("{}\n", "PROBA");

  // ListNode *l = new ListNode(2, new ListNode(4, new ListNode(3)));
  // pl(l);
  // pi(l);

  Solution sol;
  ListNode *l1 = i2l(999);
  ListNode *l2 = i2l(1);
  pl(l1);
  pi(l1);
  pl(l2);
  pi(l2);

  ListNode *l = sol.addTwoNumbers(l1, l2);
  pl(l);
  pi(l);

}

//- - - - - - - - - - - -
//= = = = = = = = = = = = = = =

//- - - - - - - - - - - -
// #pragma GCC diagnostic pop
