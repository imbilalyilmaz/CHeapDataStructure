#include <stdio.h>
#include <malloc.h>
#include <time.h>

struct Node {
    int key;
    //other informations
};

struct Heap {
    struct Node *array;
    int size;
    int capacity;
};

struct Heap* createHeap(int capacity) {
    struct Heap* heap = (struct Heap*)malloc(sizeof(struct Heap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->array = (struct Node*)malloc(capacity*sizeof(struct Node));
    return heap;
}

void printHeap(struct Heap* heap) {
    for (int i = 0; i < heap->size; ++i) {
            printf("%d ", heap->array[i].key);
    }
}

void bubleDown(struct Heap* heap, int index) {
    int largest = index;
    int leftChild = 2*index+1;
    int rightChild = 2*index+2;

    while(leftChild < heap->size) {
        if(leftChild < heap->size && heap->array[leftChild].key > heap->array[largest].key) {
            largest = leftChild;
        }
        if(rightChild < heap->size && heap->array[rightChild].key > heap->array[largest].key) {
            largest = rightChild;
        }
        if(largest != index) {
            struct Node temp = heap->array[index];
            heap->array[index] = heap->array[largest];
            heap->array[largest] = temp;
            index = largest;
        }else {
            break;
        }
        leftChild = 2 * index + 1;
        rightChild = 2 * index + 2;
    }

}

void heapify(struct Heap* heap) {
    for (int i = heap->size/2-1; i >= 0; i--) {
        bubleDown(heap,i);
    }
}

void fillWithRandom(struct Heap* heap, int size, int limit) {
    int db,newKey;
    srand(time(NULL));
    heap->array[0].key =rand()%limit + 1;
    for (int i = 1; i <size ; ++i) {
        while(1) {
            db = 1;
            newKey = rand()%limit + 1;
            for (int j = 0; j < i; ++j) {
                if(newKey == heap->array[j].key) {
                    db = 0;
                    break;
                }
            }
            if(db == 0) continue;
            heap->array[i].key = newKey;
            break;
        }
    }
    heap->size = size;
}

void bubleUp(struct Heap* heap, int index) {
    int temp = index;
    int parent = (index-1)/2;
    while(heap->array[parent].key < heap->array[temp].key && parent >= 0) {
        struct Node tempNode = heap->array[temp];
        heap->array[temp] = heap->array[parent];
        heap->array[parent] = tempNode;
        temp = parent;
        parent = (temp-1)/2;
    }
}

int heapSearch(struct Heap* heap, int data) {
    for (int i = 0; i < heap->size; ++i) {
        if(heap->array[i].key == data) {
            return 1;
        }
    }
    return 0;
}

void insert(struct Heap* heap, int key) {
    if(heapSearch(heap,key) == 1) return;
    if(heap->size < heap->capacity) {
        heap->size++;
        heap->array[heap->size-1].key = key;
        bubleUp(heap,heap->size-1);
    }
}

void deleteMax(struct Heap* heap) {
    struct Node temp;
    if(heap->size>1) {
        temp = heap->array[0];
        heap->array[0] = heap->array[heap->size-1];
        heap->array[heap->size-1] = temp;
        heap->size--;
        bubleDown(heap,0);
    }
}

void heapSort(struct Heap* heap) {
    int temp = heap->size;

    for (int i = 0; i <temp ; ++i) {
        deleteMax(heap);
    }
    heap->size = temp;
}

int main() {
    struct Heap* heap = createHeap(100);
    fillWithRandom(heap,25,25);
    /*insert(heap,15);
    insert(heap,56);
    insert(heap,75);
    insert(heap,98);
    insert(heap,92);
    insert(heap,48);*/
    printHeap(heap);
    printf("\n");

    heapify(heap);
    printHeap(heap);
    printf("\n");

    heapSort(heap);
    printHeap(heap);
    printf("\n");

    return 0;
}
