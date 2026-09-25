// #include "sys.hpp"
#pragma once
// clang-format off
// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wc99-extensions"

//- - - - - - - - - - - - common #include ...
#include <cassert> //assert(bool_expr [&& "msg"]);
#include <cstddef> //!!! size_t, NULL, offsetof, ptrdiff_t, nullptr_t, max_align_t, byte, to_integer
// #include <unistd.h>   //ssize_t
// #include <cstdint> //int8_t; int16_t;..int64_t; uint8_t;..uint64_t;
// #include <iostream>
// #include <random>

////- - - - - - - - - - - - echo 
////в .cpp актуализируем echo: #define ECHO

#ifdef ECHO //Этот вариант устаревший, но вродь наиэффективный, в т.ч. если ECHO не определен - цена действительно 0 (вызов вообще не рассматривается).
    #include <print>
    #define echo(...) std::print(__VA_ARGS__)
#else
    #define echo(...) ((void)0)
#endif
//Usage:
//    #define ECHO //перед #include "sys.hpp"
//    #include "sys.hpp"
//    ...
//    echo("{}\n","TEXT");
//// #define echo1(...) do { std::cout << "[echo] " << __FILE_NAME__ << ", " << __func__ << "(): " << __VA_ARGS__ << "\n"; } while(0)

// #ifdef ECHO //Этот вариант современнее, но возни у компилятора с ним больше: даже если ECHO не определен, компилятор разбирает типы и вызов аргументов, вычисляет их (причем если аргумент динамический - вызов функции, то она выполняется) просто тело самой функции пусто.
//   #include <print> //std::print()
//   template<typename... Args>
//   inline void echoNew(const char *fmt, Args... args) {
//       std::print(fmt, args...);
//   }
// #else
//   template<typename... Args>
//   inline void echoNew(const char*, Args...) noexcept {} //плохо - дает пустое тело фунции, но типы обрабатываются, в динамике аргументы вычисляются.
// #endif

//- - - - - - - - - - - - My helpful
template <typename T>
void swap(T &x, T &y) {
  T tmp(x);
  x = y;
  y = tmp;
}


template<typename T, int Capacity> //STM32-ориентировано. Для создания и менеджирования зараннее неизвестным кол-вом однотипных объектов вместо кучи предлагает С-масив, где размер и тип объектов задавается параметрами шаблона.
class Objs{
protected:
  alignas(T) unsigned char storage[Capacity][sizeof(T)]; //массив ячеек под объекты
  T *occupieds[Capacity]; //массив указателей на ячейки в storage для их менеджирования. Указатели на занятые ячейки всегда держим слева (от [0]).
  int occupied = 0;    //количество занятых ячеек
public:
  Objs(){
    for(int i=0; i<Capacity; ++i) { occupieds[i] = reinterpret_cast<T*>(&storage[i]); } //инициализируем указателями на пока пустые ячейки 
  }
  template<typename... Args> //создать объект по следующему указателю на свободную ячейку 
  T *addObj(Args... args){ //T *t = addObj<T>(1,'a');
    if(occupied==Capacity) return nullptr; //objs полон
    return new(occupieds[occupied++]) T(args...);
  }
  int delObj(T* obj){ //ret remainder of free storage
    for(int i=0; i<occupied; ++i) {
      if(occupieds[i]==obj){
        obj->~T(); //call dtor
        --occupied;
        swap<T>(occupieds[i], occupieds[occupied]);
        return Capacity-occupied; //Ok (obj deleted, return occupied >= 0)
      }
    }
    return -1; //error: obj с таким адресом не существует (или, возможно, уже был удален)
  }
  int getOccupied() const { return occupied; }
  int getFree()     const { return Capacity - occupied; }
};



template<int Capacity>
class Permutation {
protected:
  int pos_to_ind[Capacity]; //Кто в 5й поз.? Объект 10. Кто в 7й поз.? Объект 20.
  int ind_to_pos[Capacity]; //Где объект 10? В 5й поз. Где объект 20? В 7й поз.
public:
  Permutation() {
    for(int i=0; i<Capacity; ++i) pos_to_ind[i] = ind_to_pos[i] = i;
  }
  void swap(size_t pos_x, size_t pos_y) {
    assert(pos_x<Capacity && pos_y<Capacity && "Out of range.");
    ::swap(pos_to_ind[pos_x], pos_to_ind[pos_y]);
    ind_to_pos[pos_to_ind[pos_x]] = pos_x;
    ind_to_pos[pos_to_ind[pos_y]] = pos_y;
  }
  size_t getWhoInPos(size_t pos) const {
    assert(pos<Capacity && "Out of range.");
    return pos_to_ind[pos];
  }
    size_t getPosOfIt(size_t ind) const {
    assert(ind<Capacity && "Out of range.");
    return ind_to_pos[ind];
  }
  void dbg_print(){
    for(int i=0; i<Capacity; ++i) {
      echo("В яч. {} объект {:02}.  Объект {:02} в яч. {}.\n",i, getWhoInPos(i),i, getPosOfIt(i));
    }
  }
};

template<typename T>
struct Obj{
  T *obj;
  size_t ind;
};

template<typename T, int Capacity> //STM32-ориентировано. Для создания и менеджирования зараннее неизвестным кол-вом однотипных объектов вместо кучи предлагает С-масив, где размер и тип объектов задавается параметрами шаблона.
class Objs1{
protected:
  alignas(T) unsigned char storage[Capacity][sizeof(T)]; //массив ячеек под объекты
  size_t occupied = 0;    //количество занятых ячеек
  Permutation<Capacity> pm;
public:
  template<typename... Args>
  Obj<T> add(Args... args) { //создать объект в своб. ячейке, вернуть Obj{указ.на.объект, индекс.объекта(0..Capacity-1) (nullptr, Capacity - если все ячейки заняты) 
    if(occupied == Capacity-1) return Obj<T>{nullptr, Capacity};
    size_t ind = pm.getWhoInPos(occupied++);
    return Obj<T>{new(&storage[ind]) T(args...), ind};
  }

  void del(Obj<T> &obj) {
    size_t pos = pm.getPosOfIt(obj.ind);
    if(pos < occupied) {
      //reinterpret_cast<T*>(&storage[index])->~T();
      &storage[obj.ind]->~T();
      pm.swap(pos, --occupied);
    }
  }

};




template<typename T, int Capacity> //STM32-ориентировано. Для создания и менеджирования зараннее неизвестным кол-вом однотипных объектов вместо кучи предлагает С-масив, где размер и тип объектов задавается параметрами шаблона.
class Os{
protected:
  alignas(T) unsigned char storage[Capacity][sizeof(T)]; //массив ячеек под объекты
  size_t occupied = 0;    //количество занятых ячеек
  Permutation<Capacity> pm;
public:
  template<typename... Args> //создать объект по следующему указателю на свободную ячейку 
  size_t add(Args... args) {
    size_t index;
    if(occupied==Capacity) { 
      index = Capacity; //objs полон
    } else {
      index = pm.getIndexByOrder(occupied++);
      new(&storage[index]) T(args...);
    }
    return index;
  }
  T *ptr(size_t index) {
    T *obj;
    if(pm.getOrderByIndex(index) < occupied) {
      obj = reinterpret_cast<T*>(&storage[index]);
    } else {
      obj = nullptr;
    }
    return obj;
  }
  void del(size_t index) {
    if(pm.getOrderByIndex(index) < occupied) {
      reinterpret_cast<T*>(&storage[index])->~T();
      pm.swap(index, --occupied);
    }
  }

};

//- - - - - - - - - - - -
// #pragma GCC diagnostic pop
// clang-format on
//- - - - - - - - - - - -
//= = = = = = = = = = = = = = =
