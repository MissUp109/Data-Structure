#include "Heap.hpp"
#include <iostream>
//#include <algorithm>
#include <math.h>

template<class T>
Heap<T>::Heap(int c_size){
	capacity = c_size > DEFAULT_CAPACITY ? c_size : DEFAULT_CAPACITY;
	arr = new T[capacity];
	size = 0;
}

template<class T>
Heap<T>::Heap(std::vector<T> elements){
	size = elements.size();
	int ratio = size / DEFAULT_CAPACITY;
	capacity = ratio > 0.6 ? (1 + (int)std::ceil(ratio)) * DEFAULT_CAPACITY : DEFAULT_CAPACITY;
	arr = new T[capacity];
	for(int i = 0; i < size; ++i){
		arr[i] = elements[i];
		PercolateUp();
	}
}

template<class  T>
Heap<T>::~Heap(){
	delete[] arr;
	arr = NULL;
	size = 0;
}

template<class T> bool IsEmpty(){
	return size == 0;
}

template<class T> bool IsFull(){
	return size == capacity;
}

template<class T> void Clear(){
	size = 0;
}

template<class T> void FindMin(T& out){
	if(!IsEmpty())
		out = arr[0];
	std::cout << "The Heap is empty..." << std::endl;
}

template<class T> void PercolateUp(){//for insertion
	for(int i = size - 1; i >= 1;) {
		int parent = (i - 1) / 2;
		if(arr[parent] > arr[size - 1]){
			arr[i] = arr[parent];
			i = parent;
		}
		else break;
	}
	arr[i] = arr[size - 1];

}

template<class T> void PercolateDown(){//for deletion
	for(int i = 0; i <= (size - 1) / 2; ){
		int child = 2 * i + 1;
		if(i + 1 < size && arr[i] > arr[i + 1])
			++child;

		if(arr[child] < arr[size - 1]) {
			arr[i] = arr[child];	
			i = child;	
		}
		else break;	
	}
	arr[i] = arr[size - 1];
}

template<class T> bool Insert(T element){
	if(IsFull()){
		std::cout << "The Heap is full..." << std::endl;
		return false;
	}
	arr[size++] = element;
	PercolateUp();
}

template<class T> void DeleteMin(){
	if(IsEmpty()) {
		std::cout << "The Heap is empty..." << std::endl;
		return;
	}
	PercolateDown();
	--size;
}

template<class T> void print(){
	int height = (int)std::log(size) + 1;
	for(int h = 0; h < height; ++h){
		for(int i = 0; i < std::pow(2, height) && i < size; ++i){
			std::cout << arr[i] << " ";
		}
		std::cout << std::endl;
	}
}



