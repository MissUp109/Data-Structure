
#include <vector>
#define DEFAULT_CAPACITY 20

template<class T>
class Heap{
public:
	Heap(int c_size = DEFAULT_CAPACITY);//buildHeap
	Heap(std::vector<T> elements);
	~Heap();
	bool IsEmpty();
	bool IsFull();
	void Clear();
	T FindMin();
	void PercolateUp();
	void PercolateDown();
	bool Insert(T element);
	void DeleteMin();
	void IncreaseKey(int id, T delta);
	void DecreaseKey(int id, T delta);
	void Delete(int id);
	int size;
private:
	T* arr;
	int capacity = DEFAULT_CAPACITY;
};