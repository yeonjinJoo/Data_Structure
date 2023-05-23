#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct QuickSort{
	int capacity;
	int size;
	int *array;
};

typedef struct QuickSort* QuickSort;

QuickSort make_list(int size){
	QuickSort q = (QuickSort)malloc(sizeof(struct QuickSort));
	q -> capacity = 0;
	q -> size = size;
	q -> array = (int*)malloc(size * sizeof(int));

	return q;
}

void insert(QuickSort q, int a){
	q->array[q->capacity++] = a;
}
void printArray(QuickSort q){
	printf("result : ");
	for(int i = 0; i < q->size; i++){
		printf("%d ", q->array[i]);
	}
	printf("\n");
}

void swap(int *a, int *b){
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int middle_partition(QuickSort q, int left, int right){
	int pivot = q->array[(left + right) / 2];
	printf("pivot value : %d\n", pivot);
	int i = left; int j = right;
	while(i <= j){
		while(q->array[i] < pivot){
			i++;
		}

		while(q->array[j] > pivot){
			j--;
		}

		if(i < j){
			// 5 0 7 6 9 1 3 8 6 case, double 6 exist.
			if(q->array[i] == q->array[j]){
				j--;
				continue;
			}
			swap(&q->array[i], &q->array[j]);
		}
		else{
			return i;
		}
	}

}
int leftmost_partition(QuickSort q, int left, int right){
	int pivot = q->array[left];
	printf("pivot value : %d\n", pivot);
	int i = left; int j = right + 1;
	while(i <= j){
		while(q->array[++i] < pivot);
		while(q->array[--j] > pivot);

		if(i < j){
			swap(&q->array[i], &q->array[j]);
		}
		else{
			swap(&q->array[j], &q->array[left]);
			return j;
		}
	}

}
int rightmost_partition(QuickSort q, int left, int right){
	int pivot = q->array[right];
	printf("pivot value : %d\n", pivot);
	int i = left - 1; int j = right;

	while(i <= j){
		while(q->array[++i] < pivot);
		while(q->array[--j] > pivot);
		
		if(i < j){
			swap(&q->array[i], &q->array[j]);
		}
		else{
			swap(&q->array[i], &q->array[right]);
			return i;
		}
	}
}
void quicksort(QuickSort q, int left, int right, int type){
	int p;
	if(left >= right){
		return;
	}

	if(type == 0){
		p = leftmost_partition(q, left, right);
		printArray(q);
		quicksort(q, left, p - 1, 0);
		quicksort(q, p + 1, right, 0);
	}
	else if(type == 1){
		p = rightmost_partition(q, left, right);
		printArray(q);
		quicksort(q, left, p - 1, 1);
		quicksort(q, p + 1, right, 1);
	}
	else if(type == 2){
		p = middle_partition(q, left, right);
		printArray(q);
		quicksort(q, left, p - 1, 2);
		quicksort(q, p + 1, right, 2);
	}
}

void main(int argc, char* argv[]){
	char type_s[10];
	int list_size, key, type_i;
	QuickSort q;
	FILE *fi = fopen(argv[1], "r");

	fscanf(fi, "%s", type_s);
	if(!(strcmp(type_s, "leftmost"))){
		type_i = 0;
	}
	else if(!(strcmp(type_s, "rightmost"))){
		type_i = 1;
	}
	else if(!(strcmp(type_s, "middle"))){
		type_i = 2;
	}

	fscanf(fi, "%d", &list_size);
	q = make_list(list_size);
	for(int i = 0; i < list_size; i++){
		fscanf(fi, "%d", &key);
		insert(q, key);
	}

	quicksort(q, 0, list_size - 1, type_i);

	free(q->array);
	free(q);
}