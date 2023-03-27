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

void ErrorMessage(const char* errorstr){
	printf("\nError: %s\n", errorstr);
}

void IsEmpty(Stack* s){
	if(s -> top == -1){
		ErrorMessage("Your stack is empty!!!");
		exit(0); // stack is empty
	}
}

void IsFull(Stack* s){
	if(s -> top == s->max_stack_size -1){
		ErrorMessage("Your stack is full!!!");
		exit(0); // stack is full
	}
}

void Push(Stack* s, int x){
	IsFull(s);
	s -> key[++s->top] = x;
}

int Pop(Stack* s){
	IsEmpty(s);
	return s -> key[s -> top--];// success
}

int Top(Stack* s){
	return s->key[s->top];
}

void DeleteStack(Stack* s){
	free(s->key);
	free(s);
}

void Postfix(Stack* s, char input_str){
	if(!(input_str=='+'||input_str=='-'||input_str=='*'||input_str=='/'||input_str=='%')){
		Push(s, input_str - '0');
	}
	else{
		int operands[2];
		for(int i = 0; i < 2; i++){
			operands[i] = Pop(s);
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
		else if(input_str == '/' || '%'){
			if(operands[0]==0){
				ErrorMessage("Divided by zero!!!");
				exit(0);
			}
			if(input_str == '/'){
				Push(s, operands[1] / operands[0]);
			}
			else{
				Push(s, operands[1] % operands[0]);
			}
		}
	} // Postfix is succeeded
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
		Postfix(stack, c);
		printf("%d ", Top(stack));
	}
	printf("\n");
	printf("evaluation result: %d\n", Pop(stack));

	fclose(fi);
	DeleteStack(stack);
}