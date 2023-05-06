#include <stdio.h>
#include <stdlib.h>

typedef struct HeapStruct* Heap;
struct HeapStruct{
	int capacity;
	int size;
	int* elements;
};

Heap CreateHeap(int heapSize){
	Heap heap;
	heap = (Heap)malloc(sizeof(struct HeapStruct));
	heap -> capacity = heapSize;
	heap -> size = 0;
	heap -> elements = (int*)malloc(sizeof(int) * (heapSize + 1));
	return heap;
}
int Find(Heap heap, int value){
	if(heap->size == 0){ // empty
		return 0; 
	}
	
	for(int i = 1; i <= heap->size; i++){
		if(heap->elements[i] == value){
			return 1;
		}
	}
	return 0;

}
void Insert(Heap heap, int value){
	if(heap -> size == heap -> capacity){
		printf("Insertion Error: Max Heap is full.\n");
		return;
	}
	if(Find(heap, value)){
		printf("%d is already in the heap.\n", value);
		return;
	}

	printf("Insert %d\n", value);

	int i;
	for(i = ++heap->size; heap -> elements[i/2] < value; i /= 2){
		if(i == 1){
			break;
		}
		heap -> elements[i] = heap -> elements[i/2];
	}
	heap -> elements[i] = value;	
}

void DeleteMax(Heap heap){
	if(heap->size == 0){
		printf("Deletion Error: Max Heap is empty!\n");
		return;
	}

	printf("Max element(%d) deleted.\n", heap->elements[1]);

	int i, child, lastElement;

	lastElement = heap -> elements[heap->size--];
	for(i = 1; i*2 <= heap->size; i = child){
		child = i*2;
		if(child != heap->size && heap->elements[child+1] > heap->elements[child]){
			child++;
		}

		if(heap->elements[child] > lastElement){
			heap->elements[i] = heap -> elements[child];
		}
		else{
			break;
		}
	}
	heap -> elements[i] = lastElement;
}

void PrintHeap(Heap heap){
	if(heap -> size == 0){
		printf("Max Heap is empty!\n");
		return;
	}
	for(int i = 1; i <= heap->size; i++){
		printf("%d ", heap->elements[i]);
	}
	printf("\n");
}

void FreeHeap(Heap heap){
	free(heap->elements);
	free(heap);
}

void main(int argc, char* argv[]){
	FILE *fi = fopen(argv[1], "r");
	char cv;
	Heap maxHeap;
	int value, maxValue;

	while(EOF != fscanf(fi, "%c", &cv)){ // to avoid last line being printed twice
		// https://amornatura.tistory.com/126
		
		switch(cv){
			case 'n':
				fscanf(fi, "%d", &value);
				maxHeap = CreateHeap(value);
				break;

			case 'i':
				fscanf(fi, "%d", &value);
				Insert(maxHeap, value);
				break;

			case 'd':
				DeleteMax(maxHeap);
				break;

			case 'f':
				fscanf(fi, "%d", &value);
				if(Find(maxHeap, value)){
					printf("%d is in the heap.\n", value);
				}
				else{
					printf("%d is not in the heap.\n", value);
				}
				break;

			case 'p':
				PrintHeap(maxHeap);
				break;
		}
	}
	FreeHeap(maxHeap);
}