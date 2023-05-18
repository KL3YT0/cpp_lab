#include <iostream>
#include <iomanip>

using namespace std;

class BinaryHeap {
    public: 
    int *hArr;
    int maxSize;
    int currSize;

    BinaryHeap(int maxSize);

    ~BinaryHeap();

    void push(int value);

    int pop();

    void show();

    private:
    void up();

    void heapify(int i);

    void swap(int aIdx, int bIdx);

    static int parentIdx(int i);

    static int leftIdx(int i);

    static int rightIdx(int i);
};