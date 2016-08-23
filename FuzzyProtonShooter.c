// FUZZY PROTON SHOOTER demo v1
//------------------------------------------------
// Prasil Koirala <prasilkoirala@hotmail.com>
// Free License

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>


float dist;
int i,j;
// angle of rotation for the camera direction
float angle = 0.0f;
float jumpvar = 1.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=5.0,y=5.0,z=0.8;

// the key states. These variables will be zero
//when no key is being pressed
float ambient[]={1,1,1,1};
float light_pos[]={27,80,2,3};
float deltaAngle = 0.0f;
float deltaleft = 0.0f;
float deltaMove = 0;
float deltaright = 0.0f;
int xOrigin = -0.5;

char letterx = '+';

void changeSize(int w, int h) {

  // Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void drawtree() {

	glColor3f(0.188f, 0.143f, 0.143f);
	glTranslatef(0.0f ,3.0f, 0.0f);
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	glRotatef(90.0f,1.0f,0.0f,0.0f);
	
	gluCylinder(quadratic,0.2f,0.3f,5.5f,32,32);
	glColor3f(0.0f, 0.3f, 0.0f);
	glutSolidSphere(1.0,32,32);


}

void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void moveleft(float deltaleft) {
	deltaAngle -= deltaleft;
		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
}

void moveright(float deltaright) {
	deltaAngle += deltaright;
		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
}

float pos1=0, pos2=1, pos3=0;
int killed=0;
float br=1.0;
float bg=1.0;

int score=0;

void colorchange() {
	if ((dist<20) && (dist>10)) {
	br=1.0;
	bg=0.0;
	printf("You scored a point man!\n");
	printf("Total Score : %d \n\n",++score);
	}
}

void deadmessage() {
	printf("Too close to ball. Retreat! \n");
}

void checkclose() {
	if ((dist<=5)) {
		deadmessage();
	}
}

void colororiginal() {
	br=1.0;
	bg=1.0;
}

void enemy() {
	glPushMatrix();
	glTranslatef(pos1,pos2,pos3);
	glColor3f(br,bg,0.0);
	glutSolidSphere(0.5,50,32);
	glPopMatrix();
}
	float updateby;

void upenemy() {
	int random=rand()%4;
	int randomiser=rand()%5;

	if (randomiser==0) { updateby=0.01; };
	if (randomiser==1) { updateby=0.05; };
	if (randomiser==2) { updateby=0.10; };
	if (randomiser==3) { updateby=0.15; }
	if (randomiser==4) { updateby=0.8; }


	if (random==0) {
		pos3=pos3+updateby;
	}else if(random==1){
		pos1=pos1+updateby;
	}else if(random==2){
		pos3=pos3-updateby;
	}else {
		pos1=pos1-updateby;
}
	checkclose();
}

int xpos1,xpos2,xpos3;  //positions of the blobs
int ypos1,ypos2,ypos3;

void destroyline() {
	xpos1=0;
	xpos2=0;
	xpos3=0;
	ypos1=0;
	ypos2=0;
	ypos3=0;
}

void createline() {
	xpos1=pos1;
	xpos2=pos2;
	xpos3=pos3;
	ypos1=x+lx;
	ypos2=jumpvar-0.1;
	ypos3=z+lz;
}


void drawline() {

	dist = sqrt(((xpos1-(x+lx))*(xpos1-(x+lx)))+(xpos3-(z+lz))*(xpos3-(z+lz)));

}

void renderScene(void) {



	if (deltaMove)
		computePos(deltaMove);
	if(deltaleft)
	  moveleft(deltaleft);
	if(deltaright)
	  moveright(deltaright);
		
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	x, jumpvar, z, x+lx, jumpvar,  z+lz, 0.0f, 1.0f,  0.0f);
	glColor3f(1.0f,1.0f,0.0f);											//FASDFADSFJALSKDFJA LKSDFJASLKDF;J LK
	glRasterPos3f(x+lx,jumpvar,z+lz);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,letterx);	
	drawline();

	enemy();
	upenemy();

// Draw ground

	glColor3f(0.0f, 0.5f, 0.0f);
	glPushMatrix();
	glTranslated(0,0,0);
	glScaled(100, 1, 100);
	glutSolidCube(1.0);
	glPopMatrix();

// Draw trees
	for(i = -3; i < 5; i++)
		for(j=-3; j < 5; j++) 
	{
	
                     glPushMatrix();
                     glTranslatef(i*10.0,0,j * 5.0);
                     drawtree();
                     glPopMatrix();
               }
        glutSwapBuffers();
} 

int jumpdown () {
	float i;
	for (i=2.0;i>1.0;i=i-0.09) {
		jumpvar = i;
		renderScene();
	}
	return 0;
}

int jumpup () {
	float i;
	for (i=1.0;i<2.0;i=i+0.09) {
		jumpvar = i;
		renderScene();
	}
	jumpdown();
	return 0;
}



void pressKey(unsigned char key, int xx, int yy) {

       switch (key) {
             case 119 : deltaMove = 0.8f; break;
             case 115 : deltaMove = -0.5f; break;
			 case 97 : deltaleft=0.01f; break;
			 case 100 : deltaright=0.01f; break;
			 case 32 : jumpup(); break;
			 case 102 :colorchange(); break;
       }
} 


void releaseKey(unsigned char key, int x, int y) { 	

        switch (key) {
             case 119 : 
             case 115 : deltaMove = 0;break;
			 case 97 : deltaleft =0; break;
			 case 100 : deltaright=0;break;
			 case 102 : colororiginal();  break;
        }
} 

int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,640);
	glutCreateWindow("FPS Demo");

	glClearColor(0.0, 0.6,1.0, 0.0);
	glColor3f(1.0f, 0.0f, 1.0f);

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutIgnoreKeyRepeat(1);
	//glutKeyboardFunc(processNormalKeys);
	glutKeyboardFunc(pressKey);
	glutKeyboardUpFunc(releaseKey);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glMaterialfv(GL_FRONT,GL_AMBIENT, ambient);
	//glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0,GL_POSITION, light_pos);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
