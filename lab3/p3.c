#include <stdio.h>
#include <stdlib.h>

typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;

struct Node{
	ElementType element;
	Position next;
};

List MakeEmptyList(){
	List l = (List)malloc(sizeof(struct Node));
	l -> element = -999;
	l ->next = NULL;
	return l;
}

int isLast(Position p, List l){
	Position current = l;
	while(current->next != NULL){
		current = current->next;
	}
	return p == current;
}

Position FindPrevious(ElementType x, List l){
	Position current = l;
	while(current -> next !=NULL && current -> next -> element != x){
		current = current->next;
	}
	return current;
}

Position Find(ElementType x, List l){
	Position current = l;
	while(x!= -1 && current->next!=NULL && current->element != x){
		current = current->next;
	}
	return current;
}

void Insert(ElementType key1, ElementType key2, Position p, List l){
	Position tmp;
	tmp = (Position)malloc(sizeof(struct Node));
	if(key2 != -1 && p->element != key2){
		printf("Insertion(%d) Failed: cannot find the location to be inserted.\n", key1);
		return;
	}
	tmp -> element = key1;
	tmp -> next = p-> next;
	p->next = tmp;

}

void Delete(ElementType x, List l){
	Position tmp = FindPrevious(x, l); // x's previous position is stored
	if(!isLast(tmp, l)){ // if x's previous position is last, this means that x doesn't exist
		Position toDelete = tmp->next;
		tmp -> next = toDelete -> next;
		free(toDelete);
		return;
	}
	printf("Deletion failed: element %d is not in the list.\n", x);
}

void PrintList(List l){
	PtrToNode tmp = NULL;
	tmp = l -> next;
	if(tmp ==NULL){
		printf("list is empty!\n");
		return;
	}
	while(tmp!= NULL){
		printf("key: %d\t", tmp->element);
		tmp = tmp->next;
	}
	printf("\n");
}

void DeleteList(List l){
	Position p = NULL, tmp = NULL;
	p = l->next;
	l->next = NULL;
	while(p!=NULL){
		tmp = p->next;
		free(p);
		p = tmp;
	}
}

int main(int argc, char* argv[]){
	char command;
	int key1, key2;
	FILE *input, *output;
	Position header = NULL, tmp = NULL;

	if(argc <= 1){
		printf("Please enter an input file.");
		return 0;
	}
	else{
		input = fopen(argv[1], "r");
	}

	header = MakeEmptyList();
	while(1){
		command = fgetc(input); //fgetc returns int, but if type is char, int automatically changed to char according to ascii code.
		if(feof(input)){ //feof() returns > 0 if input.txt ends
			break;
		}
		else if(command == '\n'){ // fgetc deals with \n as one character. 
			command = fgetc(input); 
		}
		switch(command){
			case 'i':
			   fscanf(input, "%d %d", &key1, &key2);
			   tmp = Find(key2, header);
			   Insert(key1, key2, tmp, header);
			   break;

			case 'd':
			   fscanf(input, "%d", &key1);
			   Delete(key1, header);
			   break;

			case 'f':
			   fscanf(input, "%d", &key1);
			   tmp = FindPrevious(key1, header);
			   if(isLast(tmp, header)){
			   	printf("Could not find %d in the list.\n", key1);
			   }
			   else if(tmp -> element > 0){
			   	printf("Key of the previous node of %d is %d.\n", key1, tmp->element);
			   }
			   else{
			   	printf("Key of the previoud node of %d is header.\n", key1);
			   }
			   break;

			case 'p':
			   PrintList(header);
			   break;

			default:
			   printf("Invalid command line");
		}
	}

	DeleteList(header);
	fclose(input);
}