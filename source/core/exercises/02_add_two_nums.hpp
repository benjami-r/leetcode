// 02_add_two_nums.hpp
// https://leetcode.com/problems/add-two-numbers/description/

// Definition for singly-linked list.
// clang-format off
#define ECHO
#include "sys.hpp"

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//-----------------------------------------Для отладки:
void pl(ListNode *l){ //печатаем список
  if(l->next) pl(l->next);
  echo("Node *{}: val = {}, next node = *{}\n", (void *)l, l->val, (void *)l->next);
}
void pirec(ListNode *l){ //вспомогат. к pi
  if(l->next) pirec(l->next);
  echo("{}", l->val);
}
void pi(ListNode *l){ //печатаем число из списка
  echo("num = ");
  pirec(l);
  echo("\n");
}
ListNode *i2l(unsigned long long i) { //превращаем число в список
  if(i==0) return new ListNode();
  return new ListNode(i%10, (i/10 == 0)?nullptr:i2l(i/10));
}
//----------------------------------------- Варианты:


class Solution { // 4 GPT..... Отличный вариант. Итерация вместо рекурсии, и вообще - красава (просто как в столбик складывать!). Учись!
public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode dummy; // первый элемент остается незадействованым, удобен для универсальности в цикле - каждый новый цепляется в next (общепринято)
    ListNode *tail = &dummy;    // указатель на него, потом tail будет двигаться
    int carry = 0;
    while (l1 || l2 || carry) { // хоть одно есть?
      int sum = carry;          // учли перенос
      if (l1) {                 // первый пошел...
        sum += l1->val;
        l1 = l1->next;
      }
      if (l2) {                 // второй пошел...
        sum += l2->val;
        l2 = l2->next;
      }
      carry = sum / 10;
      tail->next = new ListNode(sum % 10);
      tail = tail->next;
    }
    return dummy.next;          // т.е. возвращаем второй (первый - пустышка, дань циклу. Или первый отдельно пришлось бы отработать.)
  }
};


/*
class Solution { //3 My (глупые игры с 2-ым вариантом - попытка уменьшить количество проверок. GPT сказал - фигня. Этим код особо не улучшишь, особенно с оптимизатором.) Отправил на ЛитКод - оказался лучим чем 1-2.
  int over = 0;
public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    if(l1) {
      if(l2) {
        int val = l1->val + l2->val + over;
        over = val / 10;
        return new ListNode(val%10, addTwoNumbers(l1->next, l2->next));
      } //else
      int val = l1->val + over;
      over = val / 10;
      return new ListNode(val%10, addTwoNumbers(l1->next, nullptr));
    } //else
    if(l2) {
      int val = l2->val + over;
      over = val / 10;
      return new ListNode(val%10, addTwoNumbers(nullptr, l2->next));
    } //else
    if(over) { over=0; return new ListNode(1,nullptr); }
    return nullptr;

//------------
    // if(!l1 && !l2 ) {
    //   if(over) return new ListNode(1,nullptr);
    //   return nullptr;
    // }
    // int val = (l1?l1->val:0) + (l2?l2->val:0) + over;
    // over = val / 10;
    // return new ListNode(val%10, addTwoNumbers(l1?l1->next:l1, l2?l2->next:l2));
  }
};
*/



/*
class Solution { //2 My (красота, но GPT наругал за рекурсию и неочевидность)
  int over = 0;
public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    if(!l1 && !l2 ) {
      if(over) return new ListNode(1,nullptr);
      return nullptr;
    }
    int val = (l1?l1->val:0) + (l2?l2->val:0) + over;
    over = val / 10;
    return new ListNode(val%10, addTwoNumbers(l1?l1->next:l1, l2?l2->next:l2));
  }
};
*/


/*
class Solution { //1 My (через преобразование списков в числа, а после сложения - обратно в список. Был наказан 100-разрядным числом.)
//public:
  // int l2i(ListNode *l) { //[7,0,8] = 807
  //   int i = 0, rank = 0;
  //   while (l != nullptr) {
  //     i += l->val * pow(10, rank++);
  //     l = l->next;
  //   }
  //   return i;
  // }
  unsigned pow(unsigned x, unsigned power) { // recurrence
    if (power == 0) return 1;
    return x * pow(x, power - 1);
  }
  unsigned l2i(ListNode *l, unsigned rank=0) { //[7,0,8] = 807, recurrence
    if (l == nullptr) return 0;
    return (l->val * pow(10, rank)) + l2i(l->next, rank + 1);
  }
  ListNode *i2l(unsigned i) {
    if(i==0) return new ListNode();
    return new ListNode(i%10, (i/10 == 0)?nullptr:i2l(i/10));
  }
public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) { 
    return i2l(l2i(l1)+l2i(l2)); 
  }
};
*/

// Получить гарантированно верные min/max-значения для платформы:
// #include <climits> //С-библиотека
// INT_MIN;
// INT_MAX;
// #include <limits> //С++-библиотека
// std::numeric_limits<int>::min();
// std::numeric_limits<int>::max();
