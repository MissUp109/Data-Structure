#include "Heap.hpp"
#include <iostream>

template<class T>
public Heap<T>::Heap(int c_size){
	capacity = c_size > DEFAULT_CAPACITY ? c_size : DEFAULT_CAPACITY;
	arr = new T[capacity];
}

template<class T>
public Heap<T>::Heap(std::vector<T> elements){
	int size = elements.size();
	capacity = size > DEFAULT_CAPACITY ? size : DEFAULT_CAPACITY;
	
}