#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student{
	char* name;
	int student_id;
	char* major;
}student;

int main(int argc, char** args){
	char *input_path, *output_path;
	FILE *fi, *fo;

	int num;

	student* students;

	input_path = args[1];
	output_path = args[2];

	fi = fopen(input_path, "r");
	fo = fopen(output_path, "w");

	fscanf(fi, "%d\n", &num);
	students = (student*)malloc(num*sizeof(student));
	for(int i = 0; i < num; i++){
		students[i].name = (char*)malloc(31*sizeof(char));
		students[i].major = (char*)malloc(31*sizeof(char));
		fscanf(fi, "%s %d %s\n", students[i].name, &students[i].student_id, students[i].major);
	}
	fclose(fi);

	for(int i = 0; i < num; i++){
		fprintf(fo, "%s %d %s\n", students[i].name, students[i].student_id, students[i].major);
	}
	fclose(fo);
}