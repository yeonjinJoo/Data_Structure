#include <stdio.h>
#include <stdlib.h>

struct TreeStruct{
	int size;
	int numOfNode;
	int* element;
};

typedef struct TreeStruct* Tree;

Tree CreateTree(int size){
	Tree t = (Tree)malloc(sizeof(struct TreeStruct));
	t -> size = size;
	t -> numOfNode = 0;
	t -> element = (int*)malloc(sizeof(int)* (size+1));
	t -> element[0] = 0;
	return t;
}
void Insert(Tree tree, int value){
	if(tree-> size == tree-> numOfNode){
		printf("Error! Tree is full.\n");
		return;
	}
	tree->element[tree->numOfNode+1] = value;
	tree->numOfNode++;
}

int get_left_child(Tree tree, int index){
	if((2*index)<= tree->numOfNode){
		return 2*index;
	}
	return -1;
}

int get_right_child(Tree tree, int index){
	if((2*index+1)<= tree->numOfNode){
		return 2*index + 1;
	}
	return -1;
}

void PrintPreorder(Tree tree, int index){
	if(index > 0){
		printf("%d ", tree->element[index]);
		PrintPreorder(tree, get_left_child(tree, index));
		PrintPreorder(tree, get_right_child(tree, index));
	}
}
void PrintInorder(Tree tree, int index){
	if(index > 0){
		PrintInorder(tree, get_left_child(tree, index));
		printf("%d ", tree->element[index]);
		PrintInorder(tree, get_right_child(tree, index));
	}
}
void PrintPostorder(Tree tree, int index){
	if(index > 0){
		PrintPostorder(tree, get_left_child(tree, index));
		PrintPostorder(tree, get_right_child(tree, index));
		printf("%d ", tree->element[index]);
	}
}
void DeleteTree(Tree tree){
	free(tree->element);
	free(tree);
}

void PrintTree(Tree tree){
	printf("Preorder: ");
	PrintPreorder(tree, 1);
	printf("\n");

	printf("Inorder: ");
	PrintInorder(tree, 1);
	printf("\n");
	
	printf("Postorder: ");
	PrintPostorder(tree, 1);
	printf("\n");
}

void main(int argc, char* argv[]){
	FILE* fi;
	Tree tree;
	int treeSize;
	int tmpNum;

	fi = fopen(argv[1], "r");
	fscanf(fi, "%d", &treeSize);
	tree = CreateTree(treeSize);

	while(fscanf(fi, "%d", &tmpNum)==1){
		Insert(tree, tmpNum);
	}
	PrintTree(tree); //PRINT recursive use
	DeleteTree(tree);
}