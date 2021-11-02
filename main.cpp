//Francisco J. Gomez
//Fall 2021
//Csci_172
#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>

#include <math.h>

#include <stdio.h>
//use to get the soil library
#include <SOIL.h>
#include <vector>
using namespace std;

bool WireFrame = false;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

int theta=0;
int thetaX = 0;
float alpha = 1.0;
float rx = 0;
float ry = 0;
float rz = 0;

/* GLUT callback Handlers */
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
//declare a vector of points for the vertices
vector<Point> vertices;
//declare a vector of points for the normals
vector<Point> verticesNormals;
//declare a vector of points for the normals
vector<Point> verticesTex;
//declare a vector of vectors to hold the faces
vector<vector<int>> faces;
vector<vector<float>> m;
//declare a Gl integer
GLuint tex;

static void resize(int width, int height)
{
     double Ratio;

   if(width<=height)
            glViewport(0,(GLsizei) (height-width)/2,(GLsizei) width,(GLsizei) width);
    else
          glViewport((GLsizei) (width-height)/2 ,0 ,(GLsizei) height,(GLsizei) height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective (50.0f,1,0.1f, 100.0f);
 }
// This function is use to get the data from the object file
void getObject(){
	Point point;
	// Becasue openGL starts at 1 set dummy data for index 0
	vertices.push_back(point);
	// Becasue openGL starts at 1 set dummy data for index 0
	verticesNormals.push_back(point);
	// Becasue openGL starts at 1 set dummy data for index 0
	verticesTex.push_back(point);


// The following lines are use to tokenize the file lines
	FILE *file;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;

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
            //check if the line has information regarding vertices
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
			//check if the line has information regarding vertices normals
			else if(strcmp(token,vn) == 0){
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
			//check if the line has information regarding vertices texture
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
    // close the file
	fclose(file);
	if (line){
		free(line);
	}


}
// This function is used to load an image to use as texture
// it takes the string representing the path of the image.
 
 void imageLoad(char * fileName){
 glEnable(GL_TEXTURE_2D);
 glGenTextures(1, &tex);
 glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
 glBindTexture(GL_TEXTURE_2D, tex); // images are 2D arrays of pixels, bound to the GL_TEXTURE_2D target.
 int width, height; // width & height for the image reader
 unsigned char* image;
 image = SOIL_load_image(fileName, &width, &height, 0, SOIL_LOAD_RGB);
 glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
// binding image data
 SOIL_free_image_data(image);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

 }
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,5,10,0.0,0.0,0.0,0.0,1.0,0.0);

    if(WireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		//Draw Our Mesh In Wireframe Mesh
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		//Toggle WIRE FRAME

    // your code here
    // function to rotate the object
    //glRotatef(thetaX,1.0,0,0);
    glPushMatrix();
    glRotatef(theta,0,1,0);
    glRotatef(thetaX,1,0,0);

    // function to scale the object
    glScaled(alpha,alpha,alpha);

    //Loop for each face of the object
    for(int i = 0; i < faces.size(); i++){
        //Feed information to the triangles using the data extracted from .obj file
        //stored in the vectors.
        glBegin(GL_TRIANGLES);
        glTexCoord2f(verticesTex[faces[i][1]].x,verticesTex[faces[i][1]].y);
        glNormal3f(verticesNormals[faces[i][2]].x,verticesNormals[faces[i][2]].y, verticesNormals[faces[i][2]].z);
        glVertex3f(vertices[faces[i][0]].x,vertices[faces[i][0]].y, vertices[faces[i][0]].z);

        glTexCoord2f(verticesTex[faces[i][4]].x,verticesTex[faces[i][4]].y);
        glNormal3f(verticesNormals[faces[i][5]].x,verticesNormals[faces[i][5]].y, verticesNormals[faces[i][5]].z);
        glVertex3f(vertices[faces[i][3]].x,vertices[faces[i][3]].y, vertices[faces[i][3]].z);

        glTexCoord2f(verticesTex[faces[i][7]].x,verticesTex[faces[i][7]].y);
        glNormal3f(verticesNormals[faces[i][8]].x,verticesNormals[faces[i][8]].y, verticesNormals[faces[i][8]].z);
        glVertex3f(vertices[faces[i][6]].x,vertices[faces[i][6]].y, vertices[faces[i][6]].z);

        glEnd();
    }
    glPopMatrix();
    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'w':
            WireFrame = !WireFrame;
            break;
        case 'q':
            exit(0);
            break;
    }
}
// Used to rotate and scale the cube
void Specialkeys(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_LEFT:
            ry = 1;
            rx = 0;
            theta -=5 % 360;
            if(theta % 90 == 0){
                rx = 0;
                rz = 1;
            }
        break;
    case GLUT_KEY_RIGHT:
            theta +=5 % 360;
        break;
    case GLUT_KEY_UP:
             rx = 1;
             ry = 0;
            thetaX -=5 % 360;
        break;
    case GLUT_KEY_DOWN:
            thetaX +=5 % 360;
        break;
    case GLUT_KEY_END:
            alpha += 0.25;
    break;
        case GLUT_KEY_HOME:
            alpha -= 0.25;
    break;
   }
  glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

static void init(void)
{
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    // Calls the imageLoad with the path of the image
    // that is going to be use as texture.
    imageLoad("images/crate.jpg");
}


/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitWindowSize(800,600);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");
    init();
    glutReshapeFunc(resize);
    //get the information about the object
    getObject();
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(Specialkeys);

    glutIdleFunc(idle);
    glutMainLoop();

    return EXIT_SUCCESS;
}
