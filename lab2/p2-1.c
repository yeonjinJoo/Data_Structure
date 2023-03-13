#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int n = atoi(argv[1]);
	printf("enter %d names:\n", n);

	char** names = (char**)malloc(n*sizeof(char*));
	for(int i = 0; i < n; i++){
		names[i] = (char*)malloc(31*sizeof(char));
		scanf("%s", names[i]);
	}

	printf("the names you entered:\n");
	for(int i = 0; i < n; i++){
		printf("%s\n", names[i]);
		free(names[i]);
	}

	free(names);
	return 0;
}