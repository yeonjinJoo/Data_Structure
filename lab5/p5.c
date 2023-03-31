#include <stdio.h>
#include <stdlib.h>

struct CircularQueueStruct{
	int *key;
	int first;
	int rear;
	int qsize;
	int max_queue_size;
};
typedef struct CircularQueueStruct* CircularQueue;

CircularQueue MakeEmpty(int max){
	CircularQueue Q = (CircularQueue)malloc(sizeof(struct CircularQueueStruct));
	Q -> key = (int*)malloc(sizeof(int)*max);
	Q -> first = 0;
	Q -> rear = max - 1;
	Q -> qsize = 0; // the number of elements in queue
	Q -> max_queue_size = max;
	return Q;
}
int IsEmpty(CircularQueue Q){
	if(Q -> qsize == 0){
		return 1;
	}
	return 0;
}

int IsFull(CircularQueue Q){
	if(Q -> qsize == Q -> max_queue_size){
		return 1;
	}
	return 0;
}

void Dequeue(CircularQueue Q){
	if(IsEmpty(Q)){
		printf("Dequeue failed : Queue is Empty!\n");
		return;
	}
	printf("Dequeue %d\n", Q->key[Q->first]);
	Q -> qsize--;
	Q -> first = (Q -> first + 1) % Q->max_queue_size;
}

void Enqueue(CircularQueue Q, int X){
	if(IsFull(Q)){
		printf("Enqueue failed : Queue is Full!\n");
		return;
	}
	Q -> qsize++;
	Q -> rear = (Q->rear + 1) % Q->max_queue_size;
	Q -> key[Q->rear] = X;
	printf("Enqueue %d\n", X);
}
void PrintFirst(CircularQueue Q){
	if(IsEmpty(Q)){
		printf("Queue is Empty!\n");
		return;
	}
	printf("First : %d\n", Q->key[Q->first]);
}
void PrintRear(CircularQueue Q){
	if(IsEmpty(Q)){
		printf("Queue is Empty!\n");
		return;
	}
	printf("Rear : %d\n", Q->key[Q->rear]);
}
void DeleteQueue(CircularQueue Q){
	free(Q->key);
	free(Q);
}

int main(int argc, char* argv[]){
	char command;
	FILE *input;
	CircularQueue queue;
	int queueSize;
	int tmpNum;

	input = fopen(argv[1], "r");

	while(1){
		command = fgetc(input);
		if(feof(input)){
			break;
		}
		else if(command == '\n'){ // fgetc deals with \n as one character. 
			command = fgetc(input); 
		}
		switch(command){
			case 'n':
				fscanf(input, "%d", &queueSize);
				queue = MakeEmpty(queueSize);
				break;

			case 'e':
				fscanf(input, "%d", &tmpNum);
				Enqueue(queue, tmpNum);
				break;

			case 'd':
				Dequeue(queue);
				break;

			case 'f':
				PrintFirst(queue);
				break;

			case 'r':
				PrintRear(queue);
				break;

			default:
				break;
		}
	}
	DeleteQueue(queue);
}