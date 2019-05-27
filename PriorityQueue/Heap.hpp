
#include <vector>
#define DEFAULT_CAPACITY 20

template<class T>
class Heap{
public:
	public Heap(int c_size);//buildHeap
	public Heap(std::vector<T> elements)
	public ~Heap();
	public bool IsEmpty();
	public bool IsFull();
	public void Clear();
	public T FindMin();
	public void PercolateUp();
	public void PercolateDown();
	public bool Insert(T element);
	public void DeleteMin();
	public void IncreaseKey(int id, T delta);
	public void DecreaseKey(int id, T delta);
	public void Delete(int id);
	int size;
private:
	T* arr;
	int capacity = DEFAULT_CAPACITY;
}