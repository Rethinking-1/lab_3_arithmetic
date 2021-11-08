#pragma once
#include<iostream>
static int MaxSize = 25;
template<class T>
class TStack
{
  int MemSize;
  int DataCount;
  T Top;
  T* pMem;
public:
  TStack(int size = MaxSize);
  ~TStack();
  bool isEmpty();
  bool isFull();
  int size();
  void push(T obj);
  void pop();
  const T top();
};

template<class T>
inline TStack<T>::TStack(int size) : MemSize(size)
{
  if (MemSize < 0)
    throw std::exception();
  pMem = new T[MemSize];
  DataCount = 0;
}

template<class T>
inline TStack<T>::~TStack()
{
  if (pMem != nullptr)
    pMem = nullptr;
}

template<class T>
inline bool TStack<T>::isEmpty()
{
  return !DataCount;
}

template<class T>
inline bool TStack<T>::isFull()
{
  return DataCount == MemSize;
}

template<class T>
inline int TStack<T>::size()
{
  return DataCount;
}

template<class T>
inline void TStack<T>::push(const T obj)
{
  if (isFull())
    throw std::exception();
  pMem[DataCount++] = obj;
  Top = obj;
}

template<class T>
inline void TStack<T>::pop()
{
  if (isEmpty())
    throw std::exception();
  --DataCount;
  if (DataCount)
    Top = pMem[DataCount - 1];
}

template<class T>
inline const T TStack<T>::top()
{
  if (isEmpty())
    throw std::exception();
  return Top;
}



