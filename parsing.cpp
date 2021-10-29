#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

int main(){
	//char str[] = "v -1.000000 -1.000000 -1.000000";
	// The following lines are use for the to tokenize the file lines
	//const int size = sizeof str;
	int i = 0;
	// THis lines are for getting the each line of the ile
	FILE *file;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;

	char v[] = "v";
	char vn[] = "vn";
	char vt[] = "vt";
	// open the file
	file = fopen("Cube-1.obj", "r");
	// check if the file is open sucessfully
	if( file == NULL){
		exit(EXIT_FAILURE);
	}

	// read each line of the file
	while((read = getline(&line, &len, file)) != -1){
        		char* token = strtok(line, " ");
			printf("%s <-- token\n", token);
			if (strcmp(token,v) == 0){
				printf("vertices\n");
				// get vertices
				token = strtok(NULL, " ");
				while (token != NULL){
					printf("%s ", token);
					token = strtok(NULL, " ");
				}
			}
	}
	// close the file
	fclose(file);
	if (line){
		free(line);
	}
	exit(EXIT_SUCCESS);
/*
	printf("GET first token: %s\n",token);
	while (token != NULL){
		printf("%s\n float: ", token);
		vertices[i++]=atof(token);
		token = strtok(NULL, " ");
		//vetices[i++] = atof(token);
		}
	*/
	cout << "test";
	return 0;
}
