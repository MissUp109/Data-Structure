#include <vector>
#include <iostream>
#include <math.h>
#define DEFAULT_CAPACITY 20
#define MAX_DELTA 10000

template<class T>
class Heap{
public:
	Heap(int c_size = DEFAULT_CAPACITY);
	Heap(std::vector<T> elements);
	~Heap();
	bool IsEmpty();
	bool IsFull();
	void Clear();
	bool FindMin(T& out);
	void PercolateUp(int id);
	void PercolateDown(int id, bool DeleteMinMode);
	bool Insert(T element);
	void DeleteMin();
	void IncreaseKey(int id, T delta);
	void DecreaseKey(int id, T delta);
	void Delete(int id);
	void Print();
	int size;
private:
	T* arr;
	int capacity;
};

template<class T>
Heap<T>::Heap(int c_size){
	capacity = c_size > DEFAULT_CAPACITY ? c_size : DEFAULT_CAPACITY;
	arr = new T[capacity];
	size = 0;
}

template<class T>
Heap<T>::Heap(std::vector<T> elements){
	int ratio = elements.size() / DEFAULT_CAPACITY;
	capacity = ratio > 0.6 ? (1 + (int)std::ceil(ratio)) * DEFAULT_CAPACITY : DEFAULT_CAPACITY;
	
	arr = new T[capacity];
	size = 0;
	for(int i = 0; i < elements.size(); ++i){
		Insert(elements[i]);
	}
}

template<class  T>
Heap<T>::~Heap(){
	delete[] arr;
	arr = NULL;
	size = 0;
}

template<class T> 
bool Heap<T>::IsEmpty(){
	return size == 0;
}

template<class T> 
bool Heap<T>::IsFull(){
	return size == capacity;
}

template<class T> 
void Heap<T>::Clear(){
	size = 0;
}

template<class T> 
bool Heap<T>::FindMin(T& out){
	if(IsEmpty()){
		std::cout << "The Heap is empty..." << std::endl;
		return false;
	}
	out = arr[0];
	return true;
}

template<class T> 
void Heap<T>::PercolateUp(int id){//for insertion id = size - 1
	T temp = arr[id];
	int i = id;
	for(; i >= 0;) {
		int parent = (i - 1) / 2;
		if(i > 0 && arr[parent] > temp){//if the first condition is "parent >= 0", a circle will take place.
			arr[i] = arr[parent];
			i = parent;
		}
		else break;
	}
	arr[i] = temp;

}

//When DeleteMinMode = true, this function is used for
//DeleteMin(), then temp = arr[size - 1] while id = 0. 
//When DeleteMinMode = false, this function is used for
//building a standard heap, then temp = arr[id].
template<class T> 
void Heap<T>::PercolateDown(int id, bool DeleteMinMode){
	T temp;
	if(DeleteMinMode) temp = arr[size - 1];
	else temp = arr[id]; 

	int i = id;
	for(; i < size; ){
		int child = 2 * i + 1;
		if(child + 1 < size && arr[child] > arr[child + 1])
			++child;

		if(child < size && arr[child] < temp) {
			arr[i] = arr[child];	
			i = child;	
		}
		else break;	
	}
	arr[i] = temp;
}

template<class T> 
bool Heap<T>::Insert(T element){
	if(IsFull()){
		std::cout << "The Heap is full..." << std::endl;
		return false;
	}
	arr[size++] = element;
	PercolateUp(size - 1);
	return true;
}

template<class T> 
void Heap<T>::DeleteMin(){
	if(IsEmpty()) {
		std::cout << "The Heap is empty..." << std::endl;
		return;
	}
	PercolateDown(0, true);
	--size;
}

template<class T> 
void Heap<T>::Print(){
	int factor = 1;
	for(int i = 0; i < size; ++i){
		std::cout << arr[i] << " ";
		
		if(i == 2 * factor - 2){
			std::cout << std::endl;
			factor *= 2;
		}
		else if(i == size - 1){
			std::cout << std::endl;
		}
	}
}

template<class T>
void Heap<T>::IncreaseKey(int id, T delta){
	if(id >= size || id < 0 || delta <= T(0)) return;
	arr[id] += delta;//may exist overflow
	PercolateDown(id, false);
}

template<class T>
void Heap<T>::DecreaseKey(int id, T delta){
	if(id >= size || id < 0 || delta <= T(0)) return;
	arr[id] -= delta;//may exist overflow
	PercolateUp(id);
}

template<class T>
void Heap<T>::Delete(int id){
	DecreaseKey(id, MAX_DELTA);
	Print(); std::cout << std::endl;
	DeleteMin();
}

