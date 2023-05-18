#include <iostream>
#include <iomanip>
#include <locale>
#include <math.h>

#include "./BinaryHeap/BinaryHeap.h"

using namespace std;

int main(int argc, char **argv)
{

    BinaryHeap binary_heap(15);

    binary_heap.push(100);

    binary_heap.push(80);

    binary_heap.push(90);

    binary_heap.push(300);

    binary_heap.push(10);

    binary_heap.push(150);

    binary_heap.push(150);

    binary_heap.push(350);

    binary_heap.push(20);

    binary_heap.push(700);

    binary_heap.push(70);

    binary_heap.push(81);

    binary_heap.show();

    binary_heap.pop();

    binary_heap.show();

    binary_heap.pop();

    binary_heap.show();

    binary_heap.pop();

    binary_heap.show();

    binary_heap.pop();

    binary_heap.show();

    binary_heap.pop();

    binary_heap.show();

    return 0;    
}