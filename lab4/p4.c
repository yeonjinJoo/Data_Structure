#include <stdio.h>
#include <stdlib.h>

typedef struct Stack{
	int* key;
	int top;
	int max_stack_size;
}Stack;

Stack* CreateStack(int max){
	Stack* s = (Stack*)malloc(sizeof(Stack));
	s -> max_stack_size = max;
	s -> key = (int*)malloc(sizeof(int)*max);
	s -> top = -1;
	return s;
}

int IsEmpty(Stack* s){
	if(s -> top == -1){
		return 1; // stack is empty
	}
	return 0;
}

int IsFull(Stack* s){
	if(s -> top == s->max_stack_size -1){
		return 1; // stack is full
	}
	return 0;
}

void ErrorMessage(const char* errorstr){
	printf("\n%s\n", errorstr);
}

int Push(Stack* s, int x){
	if(IsFull(s)){
		ErrorMessage("Your stack is full!!!");
		return 0; // means that Push isn't succeeded
	}
	s -> key[++s->top] = x;
	return 1; // success
}

int Pop(Stack* s){
	if(IsEmpty(s)){
		ErrorMessage("Your stack is empty!!!");
		return -9999; // means that Pop isn't succeeded
		// because s -> key[s -> top--] can be 0 (as a result of performing operation),
		// I used -9999 instead of 0. 
	}
	return s -> key[s -> top--];// success
}

int Top(Stack* s){
	return s->key[s->top];
}

void DeleteStack(Stack* s){
	free(s->key);
	free(s);
}

int Postfix(Stack* s, char input_str){
	if(!(input_str=='+'||input_str=='-'||input_str=='*'||input_str=='/'||input_str=='%')){
		if(!Push(s, input_str - '0')){
			return 0; // if stack is full, postfix is not succeeded
		}
	}
	else{
		int operands[2];
		for(int i = 0; i < 2; i++){
			operands[i] = Pop(s);
			if(operands[i]==-9999){
				return 0; // if stack is empty, postfix is not succeeded
			}
		}

		if(input_str == '+'){
			Push(s, operands[1] + operands[0]);
		}
		else if(input_str == '-'){
			Push(s, operands[1] - operands[0]);
		}
		else if(input_str == '*'){
			Push(s, operands[1] * operands[0]);
		}
		else if(input_str == '/'){
			Push(s, operands[1] / operands[0]);
		}
		else if(input_str == '%'){
			Push(s, operands[1] % operands[0]);
		}
	}
	return 1; // Postfix is succeeded
}

void main(int argc, char* argv[]){
	FILE* fi = fopen(argv[1], "r");

	Stack* stack = CreateStack(10);

	char c;
	printf("Top numbers: ");
	while(1){
		fscanf(fi, "%c", &c);
		if(c == '#'){
			break;
		}
		if(!Postfix(stack, c)){
			return;
		}
		printf("%d ", Top(stack));
	}
	printf("\n");
	printf("evaluation result: %d\n", Pop(stack));

	fclose(fi);
	DeleteStack(stack);
}