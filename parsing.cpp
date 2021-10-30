#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
class Point{
	public:
	float x;
	float y;
	float z;	
void printPoint(){
	cout << x << " " << y << " " << z << "\n";
}
};
int main(){
	// The following lines are use for the to tokenize the file lines
	FILE *file;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;

	//declare a vector of points
	vector<Point> points;
	// The following are used to check if the line has information regarding
	// vertices, normals, textures, or faces
	char v[] = "v";
	char vn[] = "vn";
	char vt[] = "vt";
	char f[] = "f";
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
				Point point;
				// add the x cordinate
				token = strtok(NULL, " ");
				point.x = atof(token);
				// add the y cordinate
				token = strtok(NULL, " ");
				point.y = atof(token);
				// add the z cordinate
				token = strtok(NULL, " ");
				point.z = atof(token);
				// print the points
				cout << "Print the point:\n";
				point.printPoint();
				// push the point to the vector of points
				points.push_back(point);
				/*
				while (token != NULL){
					printf("%s ", token);
					token = strtok(NULL, " ");
				}
				*/
			}
	}
	//print to check if the vector of points has the information it hast to have
	cout << "Check vector of points:\n";
	for( int i = 0; i < points.size(); i++){
		points[i].printPoint();
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
