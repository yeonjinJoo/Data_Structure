#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _DisjointSet{
	int size;
	int *ptr_arr; // parent
}DisjointSets;

typedef struct _PrintDisjointSet{
	int size;
	int *ptr_arr; // wall
}PrintDisjointSets;

void init(DisjointSets *sets, PrintDisjointSets *maze, int n){
	sets -> size = n * n + 1;
	// element start from index 1. index 0 is for root with rank 0.
	sets -> ptr_arr = (int*)malloc((sets->size)*sizeof(int));
	for(int i = 0; i < sets->size; i++){
		sets->ptr_arr[i] = 0;
	}

	maze -> size = 2 * n * (n + 1);
	// wall number starts from index 0.
	maze -> ptr_arr = (int*)malloc((maze->size) * sizeof(int));
	for(int i = 0; i < maze->size; i++){
		maze->ptr_arr[i] = 1;
	}
	// start and end is 0.
	maze->ptr_arr[n] = 0;
	maze->ptr_arr[(2*n-1)*(n+1)] = 0;
}

int find(DisjointSets *sets, int x){
	while(sets -> ptr_arr[x] > 0){
		x = sets -> ptr_arr[x];
	}
	return x;
}
void union_(DisjointSets *sets, int i, int j){
	// theses are root index
	int i_root = find(sets, i);
	int j_root = find(sets, j);

	int i_root_rank = sets->ptr_arr[i_root];
	int j_root_rank = sets->ptr_arr[j_root];

    // rank is negative value. 
	if(i_root_rank < j_root_rank){
		sets->ptr_arr[j_root] = i_root;
	}
	else{
		if(i_root_rank == j_root_rank){
			sets->ptr_arr[j_root]--;
		}
		sets->ptr_arr[i_root] = j_root;
	}
}
void createMaze(DisjointSets *sets, PrintDisjointSets *maze, int n){
	srand(time(NULL));
	// if first and end are in the same set, while ends.
	while(find(sets, 1) != find(sets, n*n)){
		int wallNum = rand() % maze->size;
		if(maze->ptr_arr[wallNum] && !(wallNum < n || (wallNum >= (maze->size - n))
			|| wallNum % (2*n + 1) == n || wallNum % (2*n + 1) == 2*n))
		{
			int e1, e2;

			// up, down comparison
			if(((wallNum - 1) % (2*n + 1)) < n){
				e1 = (wallNum / (2*n + 1) - 1) * n + wallNum % (2*n + 1) + 1;
				e2 = e1 + n;
			}
			// left, right comparison
			else{
				e1 = wallNum / (2*n + 1) * n + wallNum % (2*n + 1) - n;
				e2 = e1 + 1;
			}

			if(!(find(sets, e1) == find(sets, e2))){
				union_(sets, e1, e2);
				maze->ptr_arr[wallNum] = 0;
			}
		}
	}
}
void printMaze(PrintDisjointSets *maze, int n){
	for(int i = 0; i < maze->size; i++){
		if(maze->ptr_arr[i]){
			if(i % (2*n + 1) < n){
				printf(" -");
			}
			else{
				printf("| ");
			}
		}
		else{
			printf("  ");
		}

		if(i % (2*n + 1) == n-1 || i % (2*n + 1) == 2*n){
			printf("\n");
		}
	}
}

void freeMaze(DisjointSets *sets, PrintDisjointSets *maze){
	free(sets->ptr_arr);
	free(sets);

	free(maze->ptr_arr);
	free(maze);
}

int main(int argc, char* argv[]){
	int num;
	FILE *fi = fopen(argv[1], "r");
	fscanf(fi, "%d", &num);
	fclose(fi);

	DisjointSets *sets;
	PrintDisjointSets *maze;

	sets = (DisjointSets*)malloc(sizeof(DisjointSets));
	maze = (PrintDisjointSets*)malloc(sizeof(PrintDisjointSets));

	init(sets, maze, num);

	createMaze(sets, maze, num);

	printMaze(maze, num);

	freeMaze(sets, maze);

	return 0;
}