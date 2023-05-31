#include <stdio.h>
#include <stdlib.h>

typedef struct _Queue{
	int size;
	int *key;
	int front;
	int rear;
} Queue;

Queue* CreateQueue(int x){
	Queue* q = (Queue*)malloc(sizeof(Queue));

	q-> size = x;
	q->key = (int*)malloc(sizeof(int) * x);
	q->front = 0;
	q->rear = 0;
	return q;
}

void Enqueue(Queue *Q, int item){
	Q->key[Q->rear++] = item;
}

int Dequeue(Queue *Q){
	return Q->key[Q->front++];
}

typedef struct _Graph{
	int size;
	int *vertex;
	int **edge;
} Graph;

Graph *CreateGraph(int x){
	Graph* g = (Graph*)malloc(sizeof(Graph));
	g->size = x;
	g->vertex = (int*)malloc(sizeof(int) * x);
	g->edge = (int**)malloc(sizeof(int*) * x);

	for(int i = 0; i < x; i++){
		g->edge[i] = (int*)malloc(sizeof(int) * x);
	}
	return g;
}

void InsertEdge(Graph *G, int u, int v){
	// find index and insert
	for(int i = 0; i < G->size; i++){
		if(G->vertex[i] == u){
			for(int j = 0; j < G->size; j++){
				if(G->vertex[j] == v){
					G->edge[i][j] = 1;
					return;
				}
			}
		}
	}
}

void Topsort(Graph *G){
	// make indegree index
	int sum, vIndex;
	Queue* q;
	int *indegree = (int*)malloc(sizeof(int) * G->size);

	for(int j = 0; j < G->size; j++){
		sum = 0;
		for(int i = 0; i < G->size; i++){
			sum += G->edge[i][j];
		}
		indegree[j] = sum;
	}

	// make queue
	q = CreateQueue(G->size);
	for(int i = 0; i < q->size; i++){
		if(indegree[i] == 0){
			// save index, not real number
			Enqueue(q, i);
			// notice that indegree[i] is inserted to queue
			indegree[i] = -1;
		}
	}


	while(q->front != q -> rear){
		vIndex = Dequeue(q);
		printf("%d ", G->vertex[vIndex]);

		for(int i = 0; i < G->size; i++){
			if(G->edge[vIndex][i] == 1 && --indegree[i] == 0){
				Enqueue(q, i);
				indegree[i] = -1;
			}
		}
	}
	printf("\n");
}

int main(int argc, char *argv[]){
	FILE *fi = fopen(argv[1], "r");
	int X, u, v;

	fscanf(fi, "%d", &X);

	Graph *G = CreateGraph(X);

	for(int i = 0; i < X; i++){
		fscanf(fi, "%d", &G->vertex[i]);
	}

	while(fscanf(fi, "%d %d", &u, &v) != EOF){
		InsertEdge(G, u, v);
	}

	Topsort(G);

	return 0;
}