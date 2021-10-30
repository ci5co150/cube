#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
class Point{
	public:
	float x=0.0;
	float y=0.0;
	float z=0.0;	
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

	//declare a vector of points for the vertices
	vector<Point> vertices;
	Point point;
	// Becasue openGL starts at 1 set dummy data for index 0
	vertices.push_back(point);
	//declare a vector of points for the normals
	vector<Point> verticesNormals;
	// Becasue openGL starts at 1 set dummy data for index 0
	verticesNormals.push_back(point);
	//declare a vector of points for the normals
	vector<Point> verticesTex;
	// Becasue openGL starts at 1 set dummy data for index 0
	verticesTex.push_back(point);
	//declare a vector of vectors to hold the faces
	vector<vector<int>> faces;
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
			//printf("%s <-- token\n", token);
			if (strcmp(token,v) == 0){
			//	printf("vertices\n");
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
				//cout << "Print the point:\n";
				//point.printPoint();
				// push the point to the vector of points
				vertices.push_back(point);
			}
				/*
				while (token != NULL){
					printf("%s ", token);
					token = strtok(NULL, " ");
				}
				*/
			else if(strcmp(token,vn) == 0){
			//	printf("vertices noraml\n");
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
				//cout << "Print the point:\n";
				//point.printPoint();
				// push the point to the vector of the normals
				verticesNormals.push_back(point);
			}
			else if(strcmp(token,vt) == 0){
			//	printf("vertices Texture\n");
				Point point;
				// add the x cordinate
				token = strtok(NULL, ",");
				point.x = atof(token);
				// add the y cordinate
				token = strtok(NULL, ",");
				point.y = atof(token);
				//point.printPoint();
				// push the point to the vector of the normals
				verticesTex.push_back(point);
			}
	}
	//print to check if the vector of points has the information it hast to have
	cout << "Check vector of points:\n";
	for( int i = 0; i < vertices.size(); i++){
		vertices[i].printPoint();
	}
	cout << "Check vector of Normals:\n";
	for( int i = 0; i < verticesNormals.size(); i++){
		verticesNormals[i].printPoint();
	}
	cout << "Check vector of Texture:\n";
	for( int i = 0; i < verticesTex.size(); i++){
		verticesTex[i].printPoint();
	}
	// close the file
	fclose(file);
	if (line){
		free(line);
	}
	exit(EXIT_SUCCESS);
	return 0;
	//
}
