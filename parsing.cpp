#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
// create a point class for the vertices
class Point{
	// keep them public for eazy access
	public:
	float x=0.0;
	float y=0.0;
	float z=0.0;	
void printPoint(){ // print the points
	cout << x << " " << y << " " << z << "\n";
}
 
void printTex(){ // used to print the texture 
	cout << x << " " << y << "\n";
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
			if (strcmp(token,v) == 0){
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
				// push the point to the vector of points
				vertices.push_back(point);
			}
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
				// push the point to the vector of the normals
				verticesNormals.push_back(point);
			}
			else if(strcmp(token,vt) == 0){
				Point point;
				// add the x cordinate
				token = strtok(NULL, ",");
				point.x = atof(token);
				// add the y cordinate
				token = strtok(NULL, ",");
				point.y = atof(token);
				// push the point to the vector of the normals
				verticesTex.push_back(point);
			}
			// populate the vector of faces vector
			else if(strcmp(token,f) == 0){
				vector<int> facesPrime;
				// populate the faces vector
				for(int i = 0; i < 3; i++){
					token = strtok(NULL, "/");
					facesPrime.push_back(atoi(token));
					token = strtok(NULL, "/");
					facesPrime.push_back(atoi(token));
					token = strtok(NULL, " ");
					facesPrime.push_back(atoi(token));
				}
				faces.push_back(facesPrime);
			}
	}
	//print to check if the vectors have the information they have to have
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
		verticesTex[i].printTex();
	}
	cout << "Check vector of Faces:\n";
	for( int i = 0; i < faces.size(); i++){
		for(int j = 0; j <faces[i].size(); j++){
			cout << faces[i][j] << " ";
		}
		cout << endl;
	}

	// close the file
	fclose(file);
	if (line){
		free(line);
	}
	exit(EXIT_SUCCESS);
	return 0;
}
