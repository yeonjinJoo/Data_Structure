#include <stdio.h>
#include <stdlib.h>

const int INF = (int)2e9;

typedef struct Node{
	int vertex;
	int dist;
	int prev;
}Node;

// Turn Node* to Node**

typedef struct Heap{
	int capacity;
	int size;
	Node** elements;
}Heap;

Heap* createMinHeap(int X){
	Heap* h = (Heap*)malloc(sizeof(Heap));
	h->capacity = X;
	h->size = 0;
	// start at index 1
	h->elements = (Node**)malloc((X+1) * sizeof(Node*));

	for(int i = 0; i <= X; i++){
		h->elements[i] = (Node*)malloc(sizeof(Node));
		h->elements[i]->vertex = 0;
		h->elements[i]->dist = INF;
		h->elements[i]->prev = 0;
	}
	return h;
}
void insert(Heap* H, Node* N){
	if(H->size != H -> capacity){
		int i = ++ H -> size;
        // Without i > 1, H -> elements[i/2] -> dist can cause nullPointException
        while(i > 1 && H -> elements[i/2]->dist > N->dist){
    	    H->elements[i] = H -> elements[i/2];
    	    i /= 2;
        }
	
	    H -> elements[i] = N;
	}

}

Node* deleteMin(Heap* H){
	int i, child;
	Node* minNode = H->elements[1];
	Node* lastNode = H->elements[H->size--];

	for(i = 1; i*2 <= H->size; i = child){
		child = i*2;
		if(child != H->size && H->elements[child+1]->dist < H ->elements[child]->dist){
            child++;
		}

		if(lastNode->dist > H->elements[child]->dist){
			H->elements[i] = H->elements[child];
		}
		else{
			break;
		}
	}
	H->elements[i] = lastNode;
	return minNode;
}

void decreaseKey(Heap* H, Node* N){
	int index = 0;
	for(int i = 1; i <= H->size; i++){
		if(H->elements[i]->vertex == N->vertex){
			index = i;
			break;
		}
	}

	while(index > 1 && H -> elements[index/2]->dist > N->dist){
    	H->elements[index] = H -> elements[index/2];
    	index /= 2;
    }
	
	H -> elements[index] = N;

}

typedef struct Graph{
	int size;
	Node** nodes;
	int** matrix;
}Graph;

Graph* createGraph(int X){
	Graph* g = (Graph*)malloc(sizeof(Graph));
	g-> size = X;
	g-> nodes = (Node**)malloc((X+1) * sizeof(Node*));

	// initialize index 0, but not use
	for(int i = 0; i <= X; i++){
		g->nodes[i] = (Node*)malloc(sizeof(Node));
		g->nodes[i]->vertex = i;
		g->nodes[i]->dist = INF;
		g->nodes[i]->prev = 0;
	}

	g->matrix = (int**)malloc((X + 1)* sizeof(int*));
	for(int i = 0; i <= X; i++){
		g->matrix[i] = (int*)malloc((X + 1) * sizeof(int));
	}

	return g;
}

Graph* findShortestPath(Graph* G, int s){
	// s = starting vertex
	G-> nodes[s]->dist = 0;
	G-> nodes[s]->prev = s;

	for(int i = 1; i <= G->size; i++){
		// if s -> i exist, weight exist ( > 0)
		if(G-> matrix[s][i]){
			G->nodes[i]->dist = G-> matrix[s][i];
			G->nodes[i]->prev = s;
		}
	}

	Heap* H = createMinHeap(G->size);

	for(int i = 1; i <= G-> size; i++){
		insert(H, G->nodes[i]);
	}

	while(H->size != 0){
		Node* perm = deleteMin(H);

		for(int i = 1; i <= G-> size; i++){
			if(G->matrix[perm->vertex][i]){ // is adjacent? 
				// through is shorter than direct s-> i ?
				if(G->nodes[perm->vertex]->dist + G->matrix[perm->vertex][i] < G->nodes[i]->dist){
					G->nodes[i]->dist = G->nodes[perm->vertex]->dist + G->matrix[perm->vertex][i];
					G->nodes[i]->prev = perm->vertex;
					decreaseKey(H, G->nodes[i]);
				}
			}
		}
	}
	// H -> elements[i] 's reference is equal to G-> nodes[i]

	// for(int i = 0; i <= G->size; i++){
	// 	free(H->elements[i]);
	// }
	// free(H->elements);
	// free(H);

	return G;
}
void printShortestPath(Graph* G){
	Node* start;
	// find start node
	for(int i = 1; i <= G->size; i++){
		if(G->nodes[i]->dist == 0){
			start = G->nodes[i];
			break;
		}
	}

	for(int i = 1; i <= G->size; i++){
		// this means that I'll not print starting node's path
		if(G->nodes[i]->dist != 0){
			printf("%d", G->nodes[i]->vertex);
			if(G->nodes[i]->dist == INF){
				printf(" cannot be reached.\n");
				continue;
			}

			// To print all previous nodes
			int preVertex = G->nodes[i]->prev;
			while(preVertex != start->vertex){
				printf("<-%d", preVertex);
				preVertex = G->nodes[preVertex]->prev;
			}
			printf("<-%d cost: %d\n", preVertex, G->nodes[i]->dist);
		}
	}
}



int main(int argc, char* argv[]){
	FILE* fi = fopen(argv[1], "r");
	int size;

	fscanf(fi, "%d", &size);

	Graph* G = createGraph(size);

	int node_s, node_d, weight;
	while(fscanf(fi, "%d %d %d", &node_s, &node_d, &weight) != EOF){
		G->matrix[node_s][node_d] = weight;
	}

	G = findShortestPath(G, 1);

	printShortestPath(G);

	for (int i = 0; i <= G->size; i++) {
        free(G->nodes[i]);
        free(G->matrix[i]);
    }
    free(G->nodes);
    free(G->matrix);
    free(G);

	return 0;
}