#include "Heap.h"
#include <iostream>

using namespace std;

// Constructor: Initializes the heap with zero items
Heap::Heap() : numItems(0) {}

// Swap helper: Swaps two pointers to PrintJob objects
void Heap::swap(PrintJob*& a, PrintJob*& b) {
    PrintJob* temp = a;
    a = b;
    b = temp;
}

// Percolate up helper: Moves a job up the heap until the heap property is restored
void Heap::percolateUp(int index) {
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        // If current job has higher priority than its parent, swap them
        if (heap[index]->getPriority() > heap[parentIndex]->getPriority()) {
            swap(heap[index], heap[parentIndex]);
            index = parentIndex; // Move up to parent
        } else {
            break; // Heap property satisfied
        }
    }
}

// Enqueue: Adds a new PrintJob to the heap while maintaining the max-heap property
void Heap::enqueue(PrintJob* job) {
    if (numItems >= MAX_HEAP_SIZE) {
        // Heap is full, do nothing
        return;
    }

    // Place new job at the end of the heap
    heap[numItems] = job;
    int index = numItems;
    numItems++;

    // Restore heap by percolating the new job up to its correct position
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index]->getPriority() > heap[parent]->getPriority()) {
            swap(heap[index], heap[parent]);
            index = parent;
        } else {
            break; // No more adjustments needed
        }
    }
}

// Dequeue: Removes the highest priority job from the heap
void Heap::dequeue() {
    if (numItems == 0) {
        // Heap is empty, nothing to remove
        return;
    }

    // Delete the root job (highest priority)
    delete heap[0];

    // Move the last job to the root and reduce heap size
    heap[0] = heap[numItems - 1];
    numItems--;

    // Restore heap by trickling down the new root to its correct position
    trickleDown(0);
}

// Trickle down helper: Moves a job down the heap to restore the max-heap property
void Heap::trickleDown(int index) {
    int largest = index;
    int left = 2 * index + 1;  // Left child index
    int right = 2 * index + 2; // Right child index

    // Compare left child
    if (left < numItems && heap[left]->getPriority() > heap[largest]->getPriority()) {
        largest = left;
    }

    // Compare right child
    if (right < numItems && heap[right]->getPriority() > heap[largest]->getPriority()) {
        largest = right;
    }

    // If either child has higher priority, swap and continue trickling down
    if (largest != index) {
        swap(heap[index], heap[largest]);
        trickleDown(largest);
    }
}

// Returns the highest priority job without removing it
PrintJob* Heap::highest() {
    if (numItems == 0) return nullptr;
    return heap[0];
}

// Prints the highest priority job in the specified format
void Heap::print() const {
    if (numItems == 0) return;
    cout << "Priority: " << heap[0]->getPriority()
         << ", Job Number: " << heap[0]->getJobNumber()
         << ", Number of Pages: " << heap[0]->getPages()
         << endl;
}
