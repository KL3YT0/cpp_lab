#include <iostream>
#include <iomanip>

#include "BinaryHeap.h"
#include "../IsPowerOfTwo/IsPowerOfTwo.h"

using namespace std;

BinaryHeap::BinaryHeap(int maxSize) {
    this->hArr = new int[maxSize];
    this->maxSize = maxSize;
    this->currSize = 0;
}

BinaryHeap::~BinaryHeap() {
    //delete[] this->hArr;
}

void BinaryHeap::push(int value) {
    hArr[this->currSize] = value;
    this->currSize++;

    this->up();
}

int BinaryHeap::pop() {
    int head = hArr[0];       
    hArr[0] = hArr[this->currSize - 1];
    this->currSize--;

    this->heapify(0);

    return head;
}

void BinaryHeap::show() {
    int counter = 0;
    int width = 30;
    int lastPowered = -1;

    for (int i = 0; i < this->currSize; i++) {
        cout << std::setw(width) << "" << this->hArr[i] << std::setw(width) << "";

        if (isPowerOfTwo(counter) && counter > lastPowered) {
            lastPowered = counter + 1;
            counter = 1;
            cout << endl << endl << endl;
            width /= 2;
        } else {
            counter++;
        }
    } 

    cout << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << endl;
}

void BinaryHeap::up() {
    int currIdx = this->currSize - 1;
    int parentIdx = this->parentIdx(currIdx);
    //int temp = 0;

    while (currIdx > 0 && (hArr[currIdx] > hArr[parentIdx])) {
        swap(currIdx, parentIdx);
        currIdx = parentIdx;
        parentIdx = this->parentIdx(currIdx);
    }
}

void BinaryHeap::heapify(int i) {
    int maxIdx = i;
    int leftIdx = this->leftIdx(i);
    int rightIdx = this->rightIdx(i);

    if (leftIdx < this->currSize - 1) {
        if (this->hArr[maxIdx] < this->hArr[leftIdx]) {
            maxIdx = leftIdx;
        }
    }

    if (rightIdx < this->currSize - 1) {
        if (this->hArr[maxIdx] < this->hArr[rightIdx]) {
            maxIdx = rightIdx;
        }
    }

    if (maxIdx == i) {
        return;
    }

    swap(i, maxIdx);

    heapify(maxIdx);
}

void BinaryHeap::swap(int aIdx, int bIdx) {
    int temp = hArr[aIdx];
    hArr[aIdx] = hArr[bIdx];
    hArr[bIdx] = temp;
}

int BinaryHeap::parentIdx(int i) {
    return i / 2;
}

int BinaryHeap::leftIdx(int i) {
    return 2 * i + 1;
}

int BinaryHeap::rightIdx(int i) {
    return 2 * i + 2;
}