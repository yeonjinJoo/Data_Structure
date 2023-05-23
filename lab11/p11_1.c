#include <stdio.h>
#include <stdlib.h>

struct MergeSort{
	int capacity;
	int size;
	int *array;
	int *tmparray;
};

typedef struct MergeSort* MergeSort;

MergeSort make_list(int size){
	MergeSort m = (MergeSort)malloc(sizeof(struct MergeSort));

	m -> capacity = 0;
	m -> size = size;
	m -> array = (int*)malloc(size * sizeof(int));
	m -> tmparray = (int*)malloc(size * sizeof(int));

	return m;
}

int min(int x, int y){
	if( x < y){
		return x;
	}
	return y;
}

void insert(MergeSort m, int a){
	m -> array[m -> capacity++] = a;
}

void printArray(MergeSort m, int l, int r){
	for(int i = l; i <= r; i++){
		printf("%d ", m->array[i]);
	}
	printf("\n");
}

void merge(MergeSort m, int lPos, int leftEnd, int rightEnd){

	int rPos, numElements, tmpPos;
	rPos = leftEnd + 1;
	tmpPos = lPos;
	numElements = rightEnd - lPos + 1;

	while(lPos <= leftEnd && rPos <= rightEnd){
		if(m -> array[lPos] <=  m-> array[rPos]){
			m->tmparray[tmpPos++] = m->array[lPos++];
		}
		else{
			m->tmparray[tmpPos++] = m->array[rPos++];
		}
	}

	while(lPos <= leftEnd){
		m->tmparray[tmpPos++] = m->array[lPos++];
	}

	while(rPos <= rightEnd){
		m->tmparray[tmpPos++] = m->array[rPos++];
	}

	for(int i = 0; i < numElements; i++, rightEnd--){
		m->array[rightEnd] = m->tmparray[rightEnd];
	}
}

void RmergeSort(MergeSort m, int l, int r){

	int center;

	if(l < r){
		center = (l + r) / 2;
		RmergeSort(m, l, center);
		RmergeSort(m, center + 1, r);
		merge(m, l, center, r);
		printArray(m, l, r);
	}
}

void ImergeSort(MergeSort m, int n){

	for(int k = 1; k <= n; k *= 2){ // 1, 2, 4, 8... size k block
		for(int i = 0; i < n; i += 2*k){
			int lPos = i;
			int leftEnd = k + i - 1;
			int rightEnd = min(i + 2*k - 1, n); // because n might not be power of 2.

			merge(m, lPos, leftEnd, rightEnd);
			printArray(m, lPos, rightEnd);
		}
	}
}

void main(int argc, char* argv[]){
	int size, key;
	int *iter_tmp, *rec_tmp;
	FILE *fi = fopen(argv[1], "r");
	MergeSort iter_m, rec_m;

	fscanf(fi, "%d", &size);

	iter_m = make_list(size);
	rec_m = make_list(size);

	for(int i = 0; i < size; i++){
		fscanf(fi, "%d", &key);
		insert(iter_m, key);
		insert(rec_m, key);
	}

	printf("input : \n");
	printArray(iter_m, 0, iter_m->size - 1);
	printf("\n");

	printf("iterative : \n");
	ImergeSort(iter_m, iter_m->size - 1);
	printf("\n");

	printf("recursive : \n");
	RmergeSort(rec_m, 0, rec_m->size - 1);
	printf("\n");
}