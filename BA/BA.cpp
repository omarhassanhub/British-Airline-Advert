 #include "stdafx.h"
#include <stdlib.h>
#include "glut.h"
#include <math.h>
#include <stdio.h>

int tx=0, ty=0;	
int sign=0;
int frame=0;
int cycle=0;
int no_points=15;
double SquareArray[4][2];
double spin = 0.0;
double time=0.0;
float sx=1.0, sy=1.0; 
float theta=90.0;
float fTranslate = 0.0; 	
float  fRotate    = 0.0;   	
float fScale     = 0.0; 	

const GLfloat colour[][3] = {
	{ 255.0/255.0,   0.0/255.0,   0.0/255.0},
	{ 128.0/255.0,   0.0/255.0,   0.0/255.0},
	{ 205.0/255.0,   0.0/255.0,   0.0/255.0},
	{   0.0/255.0, 255.0/255.0,   0.0/255.0},
	{   0.0/255.0, 128.0/255.0,   0.0/255.0},
	{   0.0/255.0, 205.0/255.0,   0.0/255.0},
	{   0.0/255.0,   0.0/255.0, 255.0/255.0},
	{   0.0/255.0,   0.0/255.0, 128.0/255.0},
	{   0.0/255.0,   0.0/255.0, 205.0/255.0},
	{ 255.0/255.0, 255.0/255.0,   0.0/255.0},
	{ 128.0/255.0, 128.0/255.0,   0.0/255.0},
	{ 205.0/255.0, 205.0/255.0,   0.0/255.0},
	{   0.0/255.0, 255.0/255.0, 255.0/255.0},
	{   0.0/255.0, 128.0/255.0, 128.0/255.0},
	{   0.0/255.0, 205.0/255.0, 205.0/255.0},
	{ 255.0/255.0,   0.0/255.0, 255.0/255.0},
	{ 128.0/255.0,   0.0/255.0, 128.0/255.0},
	{ 205.0/255.0,   0.0/255.0, 205.0/255.0},
};



void renderSpacedBitmapString(float x, float y, void *font, char *string) {
	char *c;
	int x1=x;
	for (c=string; *c != '\0'; c++) {
		glRasterPos2f(x1,y);
		glutBitmapCharacter(font, *c);
		x1 = x1 + glutBitmapWidth(font,*c);
	}

}

void circle( double radius, double xc, double yc)
{
	int i;
	double angle = 2*3.1415/50;	
	double x, y;

	glBegin(GL_POLYGON);
	for(i=0;i<50;i++)
	{
		x = radius * cos (i *angle) + xc;
		y = radius * sin (i * angle) + yc;
		glVertex2f(x,y);	
	}
	glEnd();
}

void circle2( double radius, double xc, double yc)
{
	int i;
	double angle = 2*3.1415/25;	
	double x, y;

	glBegin(GL_POLYGON);
	for(i=0;i<50;i++)
	{
		x = radius * cos (i *angle) + xc;
		y = radius * sin (i * angle) + yc;
		glVertex2f(x,y);	
	}
	glEnd();
}



class wcPt2D{
public:
	float p, l;
};

wcPt2D letter_p[15]=
{{185.22, 173.8},
{221.63, 173.85},
{246.87, 200},
{259.63, 200},
{237.1, 173.85},
{276.95, 173.85},
{305.07, 199.63},
{323.22, 199.26},
{276.95, 142.44},
{237.1, 142.37},
{259.63, 118.12},
{246.87, 118.12},
{221.63, 141.5},
{185.22, 141.12},
{160.59, 156.03}};

wcPt2D letter_l[15]={
	{209.07, 155.87},
	{274.55, 155.87},
	{270.34, 145.45},
	{267.18, 145.46},
	{270.45, 153.6},
	{270.45, 153.6},
	{270.45, 153.6},
	{270.45, 153.6},
	{270.45, 153.6},
	{270.45, 153.6},
	{270.45, 153.6},
	{270.45, 153.6},
	{270.45, 153.6},
	{270.45, 153.6},
	{209.07, 153.59}};

	wcPt2D dis[15];
	wcPt2D tweenPoly[15];
	float proportion =0.0;

	int mode;

	void tween(wcPt2D source[15], wcPt2D destination[15], int numPoints, double proportion, wcPt2D tweenPoly[15])
	{

		for( int i = 0; i < numPoints; i++)
		{

			double sourceX = source[i].p;
			double sourceY = source[i].l;


			double destinationX = destination[i].p;
			double destinationY = destination[i].l;


			double differenceX = (destinationX - sourceX);
			double differenceY = (destinationY - sourceY);


			double tweenX = sourceX + ( differenceX * proportion );
			double tweenY = sourceY + ( differenceY * proportion );


			tweenPoly[i].p = tweenX;
			tweenPoly[i].l = tweenY;
		}


	}



	void morphplane2()
	{
		int i;
		glColor3f(1.0,0.0,0.0);
		tween(letter_p,letter_l,no_points,proportion,tweenPoly);

		glBegin(GL_LINE_LOOP);
		for(i=0;i<no_points;i++)
		{
			glVertex2i (tweenPoly[i].p,tweenPoly[i].l);
		} 
		glEnd();
	}


	void background9(){

		glBegin(GL_POLYGON);
		glColor3f(0.0,0.0,0.0);
		glVertex2i  (0, 0);
		glVertex2i (500, 0);
		glVertex2i (500, 500);
		glVertex2i (0, 500);
		glEnd();

		//line
		glBegin(GL_POLYGON);
		glColor3f(1.0,0.0,0.0);
		glVertex2i(0,400);
		glVertex2i(500,400);
		glVertex2i(500,395);
		glVertex2i(0,395);

		glEnd();

	}

	void text8()
	{
		int red = rand()%255;
		int green = rand()%255;
		int blue = rand()%255;
		glColor3f (0.0, 0, 1.0); 


		renderSpacedBitmapString(10,10,GLUT_BITMAP_HELVETICA_18,"BRITISH AIRWAYS");

	}

	void text7()
	{
		int red = rand()%255;
		int green = rand()%255;
		int blue = rand()%255;
		glColor3f (1.0, 0, 0.0);


		renderSpacedBitmapString(10,10,GLUT_BITMAP_TIMES_ROMAN_24,"THE");
		renderSpacedBitmapString(10,3,GLUT_BITMAP_TIMES_ROMAN_24,"WORLD");
		renderSpacedBitmapString(10,-5,GLUT_BITMAP_TIMES_ROMAN_24,"IS ON");
		renderSpacedBitmapString(10,-12,GLUT_BITMAP_TIMES_ROMAN_24,"SALE");
		renderSpacedBitmapString(10,-19,GLUT_BITMAP_TIMES_ROMAN_10,"Hundreds of");
		renderSpacedBitmapString(10,-26,GLUT_BITMAP_TIMES_ROMAN_10,"flights on offer");
		renderSpacedBitmapString(10,-33,GLUT_BITMAP_TIMES_ROMAN_10,"Hurry, only");
		renderSpacedBitmapString(10,-40,GLUT_BITMAP_TIMES_ROMAN_10,"available until");
		renderSpacedBitmapString(10,-47,GLUT_BITMAP_TIMES_ROMAN_10,"midnight Tuesday");
		renderSpacedBitmapString(10,-54,GLUT_BITMAP_TIMES_ROMAN_10,"at ba.com");
		renderSpacedBitmapString(10,-61,GLUT_BITMAP_HELVETICA_18,"To Fly. To Serve");


	}

	void morphplane1(){
		glBegin(GL_LINE_LOOP);
		glColor3f(1,0,0);

		glVertex2i (185.22, 173.8);
		glVertex2i (221.63, 173.85);
		glVertex2i (246.87, 200);
		glVertex2i (259.63, 200);
		glVertex2i (237.1, 173.85);
		glVertex2i (276.95, 173.85);
		glVertex2i (305.07, 199.63);
		glVertex2i (323.22, 199.26);
		glVertex2i(276.95, 142.44);
		glVertex2i (237.1, 142.37);
		glVertex2i (259.63, 118.12);
		glVertex2i (246.87, 118.12);
		glVertex2i (221.63, 141.5);
		glVertex2i (185.22, 141.12);
		glVertex2i (160.59, 156.03);
		glEnd();
	}


	void background10(){

		glBegin(GL_POLYGON);
		glColor3f(0.0,0.0,0.0);
		glVertex2i (0,0);
		glVertex2i (500,0);
		glVertex2i (500,500);
		glVertex2i (0,500);
		glEnd();


	}


	void text9()
	{
		int red = rand()%255;
		int green = rand()%255;
		int blue = rand()%255;
		glColor3f (1,1,1); 


		renderSpacedBitmapString(0,0,GLUT_BITMAP_HELVETICA_18,"THE END");

	}

	void background8(){

		glBegin(GL_POLYGON);
		glColor3f(0.658824,0.658824,0.658824);
		glVertex2i  (0, 0);
		glVertex2i (500, 0);
		glVertex2i (500, 500);
		glVertex2i (0, 500);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0,0,0);
		glVertex2i (198.36, 381.03);
		glVertex2i (198.31, 413.76);
		glVertex2i (200.08, 413.86);
		glVertex2i (200.11, 381.03);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(1,1,1);
		circle(3,199,380);
		glEnd();


		//front wall
		glBegin(GL_POLYGON);
		glColor3f(1,1,1);
		glVertex2i (100, 350);
		glVertex2i (100, 150);
		glVertex2i (350, 150);
		glVertex2i (350, 350);
		glEnd();
		//side wall
		glBegin(GL_POLYGON);
		glColor3f(1,1,1);
		glVertex2i (0, 450.6);
		glVertex2i (100, 350);
		glVertex2i (100, 150);
		glVertex2i (0, 50);
		glEnd();
		//floor
		glBegin(GL_POLYGON);
		glColor3f(0.623529,0.623529,0.372549);
		glVertex2i(100, 150);
		glVertex2i (-20, 30);
		glVertex2i(520, 30);
		glVertex2i (350, 150);

		glEnd();

		//table 1
		glBegin(GL_POLYGON);
		glColor3f(0.329412,0.329412,0.329412);
		glVertex2i (100, 229.06);
		glVertex2i (110.02, 241.91);
		glVertex2i (196.28, 241.91);
		glVertex2i (196.70, 229.15);
		glEnd();

		//table 2
		glBegin(GL_POLYGON);
		glColor3f(0.658824,0.658824,0.658824);
		glVertex2i(100, 229.06);
		glVertex2i (100, 219.02);
		glVertex2i (195.25, 219.12);
		glVertex2i (195.58, 229.15);

		glEnd();

		//leg 1
		glBegin(GL_POLYGON);
		glColor3f(0.658824,0.658824,0.658824);

		glVertex2i (104.8, 219.03);
		glVertex2i (104.72, 140.72);
		glVertex2i (111.72, 140.72);
		glVertex2i (111.77, 219.04);
		glEnd();

		//leg 2
		glBegin(GL_POLYGON);
		glColor3f(0.358824,0.358824,0.358824);

		glVertex2i (111.77, 219.04);
		glVertex2i (111.72, 145.08);
		glVertex2i (115.07, 145.08);
		glVertex2i (115.04, 219.04);
		glEnd();

		//leg 3
		glBegin(GL_POLYGON);
		glColor3f(0.658824,0.658824,0.658824);

		glVertex2i (190.5, 219.11);
		glVertex2i(182.94, 219.11);
		glVertex2i (182.65, 140.76);
		glVertex2i (190.5, 140.76);
		glEnd();


		//leg table small side
		glBegin(GL_POLYGON);
		glColor3f(0.658824,0.658824,0.658824);


		glVertex2i (196.28, 246.91);
		glVertex2i (195.58, 229.15);
		glVertex2i (195.25, 219.12);
		glVertex2i (196.20, 228.15);
		glEnd();

		//computer screen
		glBegin(GL_POLYGON);
		glColor3f(1.329412,0.329412,0.329412);
		glVertex2i (138, 239);
		glVertex2i (138, 270);
		glVertex2i (173, 270);
		glVertex2i (173, 239);
		glEnd();


		//computer under
		glBegin(GL_POLYGON);
		glColor3f(1.329412,0.329412,0.329412);
		glVertex2i (136.45, 234.36);
		glVertex2i (176.75, 234.36);
		glVertex2i (173, 239);
		glVertex2i (138, 239);
		glEnd();

		//computer keyboard
		glBegin(GL_POLYGON);
		glColor3f(1.229412,0.229412,0.229412);
		glVertex2i (139.1, 239);
		glVertex2i (138.1, 235.2);
		glVertex2i (174.22, 235.26);
		glVertex2i (172.25, 239);

		glEnd();
		//mouse pad
		glBegin(GL_POLYGON);
		glColor3f(1.429412,0.429412,0.429412);
		glVertex2i (152.88, 236.22);
		glVertex2i (152.88, 234.36);
		glVertex2i (159.34, 234.36);
		glVertex2i (159.34, 236.22);
		glEnd();

		//stickman head
		glBegin(GL_POLYGON);
		glColor3f(0,0,0);
		circle(7,121,245);
		glEnd();

		//stickman neck
		glBegin(GL_POLYGON);
		glColor3f(0,0,0);
		glVertex2i (121.28, 233.31);
		glVertex2i (121.29, 243.2);
		glVertex2i (122.92, 243.2);
		glVertex2i (122.92, 233.31);
		glEnd();

		//stickman leg 2 down
		glBegin(GL_POLYGON);
		glColor3f(0,0,0);
		glVertex2i (145.54, 197.27);
		glVertex2i (143.46, 197.41);
		glVertex2i (143.09, 165.25);
		glVertex2i (145.64, 165.25);
		glEnd();

		//stickman leg 3 down
		glBegin(GL_POLYGON);
		glColor3f(0,0,0);
		glVertex2i (138.54, 197.27);
		glVertex2i (136.46, 197.41);
		glVertex2i (136.09, 165.25);
		glVertex2i (138.64, 165.25);
		glEnd();
		//chair sit on
		glBegin(GL_POLYGON);
		glColor3f(0.439216,0.858824,0.858824);
		glVertex2i (134.38, 183.43);
		glVertex2i (134.38, 197.9);
		glVertex2i (153.36, 197.6);

		glEnd();

		//stickman leg 1 sit
		glBegin(GL_POLYGON);
		glColor3f(0,0,0);
		glVertex2i (134.38, 186.98);
		glVertex2i (134.38, 185.17);
		glVertex2i (145.54, 197.27);
		glVertex2i (143.46, 197.41);
		glEnd();

		//stickman leg 2 sit
		glBegin(GL_POLYGON);
		glColor3f(0,0,0);
		glVertex2i (128.38, 186.98);
		glVertex2i (128.38, 185.17);
		glVertex2i (139.54, 197.27);
		glVertex2i (137.46, 197.41);
		glEnd();




		//chair back
		glBegin(GL_POLYGON);
		glColor3f(0.339216,0.758824,0.758824);
		glVertex2i (112.57, 238.02);
		glVertex2i (112.47, 187.93);
		glVertex2i (134.38, 183.43);
		glVertex2i (134.38, 233.21);

		glEnd();

		//chair leg 1
		glBegin(GL_POLYGON);
		glColor3f(0.439216,0.858824,0.858824);
		glVertex2i (117.52, 186.9);
		glVertex2i (112.47, 187.93);
		glVertex2i (112.2, 140.51);
		glVertex2i (117.49, 140.51);
		glEnd();

		//chair leg 2
		glBegin(GL_POLYGON);
		glColor3f(0.439216,0.858824,0.858824);
		glVertex2i (128.77, 184.58);
		glVertex2i (128.8, 140.65);
		glVertex2i (134.28, 140.65);
		glVertex2i (134.38, 183.43);
		glEnd();

		//chair leg 3
		glBegin(GL_POLYGON);
		glColor3f(0.439216,0.858824,0.858824);
		glVertex2i (153.32, 145.55);
		glVertex2i (149.5, 145.55);
		glVertex2i (149.61, 194.59);
		glVertex2i (153.36, 197.6);
		glEnd();
	}

	void sc2(){
		//computer screen 2
		glBegin(GL_POLYGON);
		glColor3f(0,0,0);
		glVertex2i (140.55, 268.45);
		glVertex2i (171.03, 268.45);
		glVertex2i (171.01, 240.35);
		glVertex2i (140.56, 240.36);
		glEnd();


	}

	void sc3(){

		//computer screen 3
		glBegin(GL_POLYGON);
		glColor3f(1,1,1);
		glVertex2i (154.85, 257.95);
		glVertex2i (155.85, 257.95);
		glVertex2i (155.85, 253.02);
		glVertex2i (154.85, 253.02);
		glEnd();


		//computer screen 4
		glBegin(GL_POLYGON);
		glColor3f(1,1,1);
		glVertex2i(156.15, 257.95);
		glVertex2i (157.15, 257.95);
		glVertex2i (157.15, 253.02);
		glVertex2i(156.15, 253.02);
		glEnd();
	}

	void hand(){
		//stickman hand
		glBegin(GL_POLYGON);
		glColor3f(0,0,0);
		glVertex2i (134.38, 211.44);
		glVertex2i (154.21, 237.6);
		glVertex2i (155.84, 236.92);
		glVertex2i (134.38, 210);
		glEnd();

	}


	void background7(){

		glBegin(GL_POLYGON);
		glColor3f(1.0, 0.5, 0.0);
		glVertex2i (0,177);
		glVertex2i (600,177);glColor3f(1.0, 1.0, 0.0);
		glVertex2i (600,500);glColor3f(1.0, 1.0, 0.0);

		glVertex2i (0,500);
		glEnd();


		//sea
		glBegin(GL_POLYGON);
		glColor3f(0.0,0.0,1.0);
		glVertex2i (0, 0);
		glVertex2i (0, 190);
		glVertex2i (600, 190);
		glVertex2i (600, 0);
		glEnd();

		//circle top
		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0, 0.0);
		circle(55,50,270);	
		glEnd();

		//circle middle
		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0, 0.0);
		circle(70,50,170);	
		glEnd();


		//overlap sea middle
		glBegin(GL_POLYGON);
		glColor3f(0.0,0.0,1.0);
		glVertex2i (0, 150);
		glVertex2i (0, 50);
		glVertex2i (268.13, 50.65);
		glVertex2i (268.13, 150);
		glEnd();

		//circle bottom
		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0, 0.0);
		circle(35,110,130);	
		glEnd();

		//overlap sea bottom
		glBegin(GL_POLYGON);
		glColor3f(0.0,0.0,1.0);
		glVertex2i (0, 37.29);
		glVertex2i (268.13, 35.72);
		glVertex2i(268.13, 123.71);
		glVertex2i(0, 123.71);
		glEnd();

		//pole
		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0,1.0);
		glVertex2i (54.93, 193.71);
		glVertex2i (62.47, 193.63);
		glVertex2i (62.47, 293.83);
		glVertex2i (54.93, 293.83);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0,1.0);
		glVertex2i (58.76, 293.83);
		glVertex2i (26.93, 293.98);
		glVertex2i (26.93, 312.92);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0,1.0);
		glVertex2i (58.76, 293.83);
		glVertex2i (90.7, 293.98);
		glVertex2i (90.7, 313.69);
		glEnd();


	}
	void boat(){
		//boat
		glBegin(GL_POLYGON);
		glColor3f(1.0,0.0,0.0);
		glVertex2i (381.45, 190);
		glVertex2i (440.02, 190);
		glVertex2i(448.43, 205.42);
		glVertex2i (373.24, 205.42);
		glEnd();

		//boat 2
		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0,1.0);
		glVertex2i (419.3, 266.35);
		glVertex2i(419.51, 205.42);
		glVertex2i (438.1, 205.42);
		glEnd();
	}
	void text6()
	{
		int red = rand()%255;
		int green = rand()%255;
		int blue = rand()%255;
		glColor3f (float(green)/255.0, 0, 0.0); 


		renderSpacedBitmapString(0,0,GLUT_BITMAP_HELVETICA_18,"and idyllics....");


	}


	void background6(){
		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2i (0,120);
		glColor3f(0.8, 0.6, 0.6);
		glVertex2i (600,120);
		glColor3f(0.0, 0.0, 1.0);
		glVertex2i (600,500);
		glVertex2i (0,500);
		glEnd();

		//transparent window mountain
		glBegin(GL_POLYGON);
		glColor3f(0.1, 0.1, 0.1);
		glVertex2i (0,0);glColor3f(1.0, 1.0, 1.0);
		glVertex2i (0,100);glColor3f(1.0, 1.0, 1.0);
		glVertex2i (600,100);glColor3f(1.0, 1.0, 1.0);
		glVertex2i (600,0);glColor3f(1.0, 1.0, 1.0);

		glEnd();


		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0,1.0);
		glVertex2i (0, 0);
		glVertex2i (0, 150);
		glVertex2i (78.05, 296.46);
		glVertex2i (171.31, 152.68);
		glVertex2i (247.63, 204.68);
		glVertex2i (263.85, 338.51);
		glVertex2i (344.24, 158.51);
		glVertex2i (583.23, 311.14);
		glVertex2i (597.43, 0);
		glVertex2i(365.24, 144.86);
		glVertex2i (313.54, 359.81);
		glVertex2i (456.5, 147.9);
		glEnd();


	}
	void snowing()
	{
		glColor3f(0.8, 0.8,0.8);

		glPointSize(7);
		glBegin(GL_POINTS);
		glVertex2i(rand()%1000-200, rand()%1000-200);
		glVertex2i(rand()%1000-200, rand()%1000-200);
		glVertex2i(rand()%1000-200, rand()%1000-200);
		glVertex2i(rand()%1000-200, rand()%1000-200);
		glEnd();
		glPointSize(5);
		glBegin(GL_POINTS);
		glVertex2i(rand()%1000-200, rand()%1000-200);
		glVertex2i(rand()%1000-200, rand()%1000-200);
		glVertex2i(rand()%1000-200, rand()%1000-200);
		glVertex2i(rand()%1000-200, rand()%1000-200);
		glVertex2i(rand()%1000-200, rand()%1000-200);
		glVertex2i(rand()%1000-200, rand()%1000-200);
		glEnd();

		glPointSize(3);
		glBegin(GL_POINTS);
		glVertex2i(rand()%1000-200, rand()%1000-200);
		glVertex2i(rand()%1000-200, rand()%1000-200);
		glVertex2i(rand()%1000-200, rand()%1000-200);
		glVertex2i(rand()%1000-200, rand()%1000-200);
		glEnd();

	}

	void text5()
	{
		int red = rand()%255;
		int green = rand()%255;
		int blue = rand()%255;
		glColor3f (float(green)/255.0, 0, 0.0); 


		renderSpacedBitmapString(0,0,GLUT_BITMAP_HELVETICA_18,"Mountaintop....");

	}


	void background5(){

		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2i (0,120);
		glColor3f(0.8, 0.6, 0.6);
		glVertex2i (600,120);
		glColor3f(0.0, 0.0, 1.0);
		glVertex2i (600,500);
		glVertex2i (0,500);
		glEnd();


		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0, 0.0);
		circle(35,330,400);	
		glEnd();

		glBegin(GL_POLYGON);
		//Hoolywood
		glBegin(GL_POLYGON);
		glColor3f(0.0,1.0,0.0);
		glVertex2i (0, 0);
		glVertex2i (0, 196.55);
		glVertex2i(72.74, 242.98);
		glVertex2i (167.11, 242.98);
		glVertex2i (396.12, 359.21);
		glVertex2i (599.8, 315.48);
		glVertex2i (600, 0);
		glEnd();
		glEnd();


	}


	void text4()
	{
		int red = rand()%255;
		int green = rand()%255;
		int blue = rand()%255;
		glColor3f (float(green)/255.0, 0, 0.0); 


		renderSpacedBitmapString(0,0,GLUT_BITMAP_HELVETICA_18,"Popular regions....");

	}

	void hollywood_text()
	{

		glColor3f (1.0,1.0, 1.0);


		renderSpacedBitmapString(10,550,GLUT_BITMAP_HELVETICA_18,"HOLLYWOOD");
	}



	void background4(){

		glBegin(GL_POLYGON);
		glColor3f(0.8, 0.8, 0.0);
		glVertex2i (0,120);
		glColor3f(0.8, 0.6, 0.6);
		glVertex2i (600,120);
		glColor3f(0.0, 0.0, 1.0);
		glVertex2i (600,500);
		glVertex2i (0,500);
		glEnd();


		//mid backgroud
		glColor3f(0.658824, 0.658824, 0.658824);
		glBegin(GL_POLYGON);
		glVertex2i (0,120);
		glVertex2i (600,120);
		glVertex2i (600,0);
		glVertex2i (0,0);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0, 0.0);
		circle(40,440,300);	
		glEnd();

		glBegin(GL_POLYGON);

		glColor3f(0.91 , 0.76 , 0.65);
		glVertex2i (0, 0);
		glVertex2i (50.85, 0);
		glVertex2i (50.85, 200.55);
		glVertex2i(0, 200);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.91 , 0.76 , 0.65);

		glVertex2i (50.85, 0);
		glVertex2i (71.21, 0);
		glVertex2i (71.21, 41.83);
		glVertex2i (50.85, 41.83);

		glEnd();


		glBegin(GL_POLYGON);
		glColor3f(0.91 , 0.76 , 0.65);
		glVertex2i (70.83, 0);
		glVertex2i (89.19, 0);
		glVertex2i (89.56, 136.86);
		glVertex2i(70.83, 136.86);
		glEnd();


		glBegin(GL_POLYGON);
		glColor3f(0.91 , 0.76 , 0.65);
		glVertex2i (109.47, 0);
		glVertex2i (174.07, 0);
		glVertex2i (174.07, 281.72);
		glVertex2i(109.47, 281.72);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.91 , 0.76 , 0.65);


		glVertex2i (119, 281.7);
		glVertex2i (119, 328.7);
		glVertex2i (125, 328.7);//problem
		glVertex2i (125, 343.7);
		glVertex2i (134.91, 343.7);
		glVertex2i (140.98, 379.22);
		glVertex2i (148, 343.7);
		glVertex2i (157, 343.7);
		glVertex2i (157, 328.7);
		glVertex2i (163, 328.7);
		glVertex2i (163, 281.7);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.91 , 0.76 , 0.65);
		glVertex2i (193.68, 0);
		glVertex2i (242.57, 0.1);
		glVertex2i (242.56, 137.33);
		glVertex2i (193.87, 137.26);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.91 , 0.76 , 0.65);
		glVertex2i (262.84, 0);
		glVertex2i(325.34, 0);
		glVertex2i (325.33, 200.04);
		glVertex2i (262.61, 200.04);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.91 , 0.76 , 0.65);
		glVertex2i (365.33, 0);
		glVertex2i (419.2, 0);
		glVertex2i (419.74, 290);
		glVertex2i (365.97, 290);
		glEnd();


		glBegin(GL_POLYGON);
		glColor3f(0.91 , 0.76 , 0.65);
		glVertex2i(464.78, 0);
		glVertex2i (464.78, 188.97);
		glVertex2i(549.64, 189.43);
		glVertex2i (550, 0);
		glEnd();


	}


	void background2(){

		//background colour
		glBegin(GL_POLYGON);
		glColor3f(0.196078, 0.8, 1.0);
		glVertex2i (0,177);
		glVertex2i (600,177);
		glVertex2i (600,500);
		glColor3f(1.0, 1.0, 0.0);
		glVertex2i (0,500);
		glEnd();

		//background sun
		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0, 0.0);
		circle(40,5,500);	
		glEnd();


		//green background
		glPushMatrix();
		glColor3f(0.0, 0.5, 0.0);
		glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(600, 0);
		glVertex2f(600, 177);
		glVertex2f(0,177);
		glEnd();
		glPopMatrix();

		//Black background 1 (beneth)
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex2f(0, 45);
		glVertex2f(600, 45);
		glVertex2f(600, 105);
		glVertex2f(0,105);
		glEnd();
		glPopMatrix();


		//Black background 1 (above)
		glPushMatrix();
		glColor3f(0.3, 0.3, 0.3);
		glBegin(GL_POLYGON);
		glVertex2f(0, 50);
		glVertex2f(600, 50);
		glVertex2f(600, 100);
		glVertex2f(0,100);
		glEnd();
		glPopMatrix();

		//White strips
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);


		glBegin(GL_POLYGON);
		glVertex2f(20, 70);
		glVertex2f(30, 70);
		glVertex2f(32, 73);
		glVertex2f(22, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(40, 70);
		glVertex2f(50, 70);
		glVertex2f(52, 73);
		glVertex2f(42, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(60, 70);
		glVertex2f(70, 70);
		glVertex2f(72, 73);
		glVertex2f(62, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(80, 70);
		glVertex2f(90, 70);
		glVertex2f(92, 73);
		glVertex2f(82, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(100, 70);
		glVertex2f(110, 70);
		glVertex2f(112, 73);
		glVertex2f(102, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(120, 70);
		glVertex2f(130, 70);
		glVertex2f(132, 73);
		glVertex2f(122, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(140, 70);
		glVertex2f(150, 70);
		glVertex2f(152, 73);
		glVertex2f(142, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(160, 70);
		glVertex2f(170, 70);
		glVertex2f(172, 73);
		glVertex2f(162, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(180, 70);
		glVertex2f(190, 70);
		glVertex2f(192, 73);
		glVertex2f(182, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(180, 70);
		glVertex2f(190, 70);
		glVertex2f(192, 73);
		glVertex2f(182, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(200, 70);
		glVertex2f(210, 70);
		glVertex2f(212, 73);
		glVertex2f(202, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(220, 70);
		glVertex2f(230, 70);
		glVertex2f(232, 73);
		glVertex2f(222, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(240, 70);
		glVertex2f(250, 70);
		glVertex2f(252, 73);
		glVertex2f(242, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(260, 70);
		glVertex2f(270, 70);
		glVertex2f(272, 73);
		glVertex2f(262, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(280, 70);
		glVertex2f(290, 70);
		glVertex2f(292, 73);
		glVertex2f(282, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(300, 70);
		glVertex2f(310, 70);
		glVertex2f(312, 73);
		glVertex2f(302, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(320, 70);
		glVertex2f(330, 70);
		glVertex2f(332, 73);
		glVertex2f(322, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(340, 70);
		glVertex2f(350, 70);
		glVertex2f(352, 73);
		glVertex2f(342, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(360, 70);
		glVertex2f(370, 70);
		glVertex2f(372, 73);
		glVertex2f(362, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(380, 70);
		glVertex2f(390, 70);
		glVertex2f(392, 73);
		glVertex2f(382, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(400, 70);
		glVertex2f(410, 70);
		glVertex2f(412, 73);
		glVertex2f(402, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(420, 70);
		glVertex2f(430, 70);
		glVertex2f(432, 73);
		glVertex2f(422, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(440, 70);
		glVertex2f(450, 70);
		glVertex2f(452, 73);
		glVertex2f(442, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(460, 70);
		glVertex2f(470, 70);
		glVertex2f(472, 73);
		glVertex2f(462, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(480, 70);
		glVertex2f(490, 70);
		glVertex2f(492, 73);
		glVertex2f(482, 73);
		glEnd();


		glPopMatrix();
	}

	void airplane1(){

		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0, 1.0);

		glVertex2i (350, 510);
		glVertex2i (1400, 510);
		glVertex2i (1400, 250);
		glVertex2i (708.87, 253.3);
		glVertex2i (614.17, 275.61);
		glVertex2i (568.99, 293.03);
		glVertex2i (525.3, 311.56);
		glVertex2i (479.06, 335.38);
		glVertex2i (438.43, 362);
		glVertex2i (400, 400);
		glVertex2i (375.37, 432.06);
		glVertex2i (358.56, 461.48);
		glVertex2i (351.28, 487.88);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.258824,0.258824, 0.258824);
		glVertex2i (855, 252);
		glVertex2i (881, 252);
		glVertex2i (881, 154);
		glVertex2i (855, 154);
		glEnd();


	}


	void text1()
	{
		int red = rand()%255;
		int green = rand()%255;
		int blue = rand()%255;
		glColor3f (float(red)/255.0, 0, 0.0); 


		renderSpacedBitmapString(0,0,GLUT_BITMAP_HELVETICA_18,"Our Aeroplanes...");


	}
	void tyre1(){


		glColor3f(0.1,0.1, 0.1);
		circle2(60,0,0);
		glColor3f(0.658824,0.658824, 0.658824);
		circle2(50,0,0);
		glColor3f(0.258824,0.258824, 0.258824);
		circle2(3,0,0);

	}

	void background1(){
		//background red
		glColor3f(3.1,0.0,0.0);
		glBegin(GL_POLYGON);
		glVertex2i (0, 0);
		glVertex2i (500, 0);
		glVertex2i (500, 500);
		glVertex2i (0, 500);
		glEnd();

		//white square
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_POLYGON);
		glVertex2i (211.23, 228.83);
		glVertex2i (256.66, 228.83);
		glVertex2i (256.66, 293.24);
		glVertex2i (211.23, 293.24);
		glEnd();
	}

	void playbutton(){

		//back triangle
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_POLYGON);
		glVertex2i (225.41, 270.36);
		glVertex2i (225.41, 252.8);
		glVertex2i(244.69, 260.71);
		glEnd();

		//front triangle
		glColor3f(6.0,0.0,0.0);
		glBegin(GL_POLYGON);
		glVertex2i (225.41, 252.8);
		glVertex2i (242.14, 259.67);
		glVertex2i (225.41, 270.36);


		glEnd();

		//mouse button triangle
		glColor3f(0.658824,0.658824,0.658824);
		glBegin(GL_POLYGON);
		glVertex2i (232.73, 249.61);
		glVertex2i(231.86, 259.24);
		glVertex2i (241.28, 255.6);
		glVertex2i (235.75, 255.69);
		glVertex2i (234.28, 254.8);

		glEnd();

		//mouse tale
		glColor3f(0.658824,0.658824,0.658824);
		glBegin(GL_POLYGON);
		glVertex2i(235.75, 255.69);
		glVertex2i (234.28, 254.8);
		glVertex2i(240, 248);
		glVertex2i (241.52, 249.12);
		glEnd();

	}

	void airplane2(){

		//wing under 2
		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0,1.0);


		glVertex2i (457.81, 193.48);glColor3f(0.329412,0.329412,0.329412);
		glVertex2i(462.53, 191.72);
		glVertex2i (442.39, 175.24);
		glVertex2i (426.55, 175.24);

		glEnd();


		//body bottom
		glBegin(GL_POLYGON);
		glColor3f(0.658824,0.658824,0.658824);
		glVertex2i (339.45, 156.36);
		glVertex2i(339.45, 156.36);
		glVertex2i (394, 156.36);
		glVertex2i(396.18, 156.45);
		glVertex2i (398.35, 156.55);
		glVertex2i (400.52, 156.75);
		glVertex2i (402.88, 156.85);
		glColor3f(0.329412,0.329412,0.329412);
		glVertex2i (405.94, 157.05);
		glVertex2i (409.3, 157.34);
		glVertex2i (414.82, 157.93);
		glVertex2i(423.01, 159.61);
		glVertex2i (445.88, 163.08);
		glColor3f(0.329412,0.329412,0.329412);
		glVertex2i (454.33331, 165.82829);
		glVertex2i (339.44995, 165.72797);

		glEnd();


		//body top
		glBegin(GL_POLYGON);


		glVertex2i (339.45, 165.73);
		glVertex2i (339.39, 189.86);
		glColor3f(1.0,1.0,1.0);
		glVertex2i (405.56, 189.81);
		glVertex2i (410.26, 189.57);
		glVertex2i (416.83, 188.99);
		glVertex2i (421.76, 188.16);
		glVertex2i (426.22, 187.22);
		glVertex2i (430.45, 186.29);
		glVertex2i (434.44, 185.35);
		glVertex2i (438.55, 184.17);
		glVertex2i (442.19, 183.12);
		glVertex2i (454.30846, 178.84374);glColor3f(0.329412,0.329412,0.329412);
		glVertex2i (454.33331, 165.82829);
		glEnd();

		//on top of top body shadow
		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0,1.0);
		glVertex2i  (454.28, 178.57);
		glVertex2i (442.19, 183.12);
		glVertex2i (405.56, 189.81);
		glVertex2i (339.39, 189.86);
		glColor3f(0.329412,0.329412,0.329412);
		glVertex2i (339.43, 168.57);


		glEnd();


		//head
		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0,1.0);
		glVertex2i (339.39, 189.86);glColor3f(0.329412,0.329412,0.329412);
		glVertex2i (336.97, 190.71);
		glVertex2i (334.62, 190.66);
		glVertex2i (331.65, 190.18);
		glVertex2i (329.06, 189.51);
		glVertex2i (326.33, 188.45);
		glVertex2i (323.7, 187.16);
		glVertex2i (322.07, 186.36);
		glVertex2i (318.8, 184.72);
		glVertex2i (315.49, 182.96);
		glVertex2i (313.61, 181.78);
		glVertex2i (311.84, 180.77);
		glVertex2i (310.4, 179.96);
		glVertex2i (308.34, 178.9);
		glVertex2i (306.12, 177.66);
		glVertex2i (304.12, 175.64);
		glVertex2i (302.04, 171.61);
		glVertex2i (301.78, 169.13);
		glVertex2i (302.21, 166.68);
		glVertex2i (303.59, 165.27);
		glVertex2i (305.98, 164.01);
		glVertex2i (308.42, 162.45);
		glVertex2i (311.15, 161.04);
		glVertex2i (313.38, 160.3);
		glVertex2i (317.05, 159.29);
		glVertex2i (321.33, 158.26);
		glVertex2i (326.03, 157.11);
		glVertex2i (330.66, 156.27);
		glVertex2i (335.43, 156.2);
		glVertex2i (339.45, 156.36);

		glEnd();
		//middle line
		glBegin(GL_POLYGON);
		glColor3f(0.0,0.5,0.5);
		glVertex2i(339.45, 166.45);glColor3f(0.329412,0.329412,0.329412);
		glVertex2i (454.26, 166.45);
		glVertex2i(454.38, 165.81);
		glVertex2i(339.45, 165.72);
		glEnd();
		//between head and body line
		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0,1.0);	
		glVertex2i (339.39, 189.86);glColor3f(0.329412,0.329412,0.329412);
		glVertex2i (338.36, 189.87);
		glVertex2i (338.38, 156.38);
		glVertex2i (339.45, 156.36);
		glEnd();


		//head window
		glBegin(GL_POLYGON);
		glColor3f(0.0,0.0,0.0);
		glVertex2i (305.12, 176.66);
		glVertex2i (316.18, 176.66);
		glVertex2i (315.7, 179.95);
		glVertex2i(310.4, 179.96);

		glEnd();

		//window inside line
		glBegin(GL_LINES);
		glColor3f(0.329412,0.329412,0.329412);

		glVertex2i (313.11, 179.96);
		glVertex2i (313.63, 176);

		glVertex2i (310.11, 179.96);
		glVertex2i (310.63, 176);

		glEnd();

		//door
		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0,1.0);
		glVertex2i (341.38, 176.29);glColor3f(0.329412,0.329412,0.329412);
		glVertex2i (343.25, 176.29);
		glVertex2i (343.75, 168.05);
		glVertex2i (341.38, 168.05);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.429412,0.429412,0.429412);

		circle(0.3,342,172);

		glEnd();


		//tale body
		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0,1.0);
		glVertex2i (405.56, 189.81);
		glVertex2i (425, 190);glColor3f(0.329412,0.329412,0.329412);
		glVertex2i (432.91, 190.71);
		glVertex2i (436.68, 197.87);
		glVertex2i (444.95, 216.46);
		glVertex2i (452.96, 216.46);
		glVertex2i (442.19, 183.12);
		glEnd();

		//line inside tale
		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0,1.0);
		glVertex2i (449.7, 216.46);glColor3f(0.329412,0.329412,0.329412);
		glVertex2i (436.3, 184.8);
		glVertex2i(436.44, 185.35);glColor3f(0.329412,0.329412,0.329412);
		glVertex2i(448.21, 216.46);glEnd();


		//wing front
		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0,1.0);
		glVertex2i (358.52, 165.72);glColor3f(0.329412,0.329412,0.329412);
		glVertex2i (394.97574, 143.05895);
		glVertex2i (407, 146.05);
		glVertex2i (394.58, 165.7);
		glEnd();

		//top of wing
		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0,1.0);
		glVertex2i (394.98, 143.06);glColor3f(0.329412,0.329412,0.329412);
		glVertex2i (407, 146.05);
		glVertex2i (406.32, 153.47);
		glVertex2i (398.97, 153.47);

		glEnd();


		//back exhaust
		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0,1.0);
		glVertex2i (454.09, 178.67);glColor3f(0.329412,0.329412,0.329412);
		glVertex2i (454.06, 165.71);
		glVertex2i (455, 165.62);
		glVertex2i (455.04, 178.45);
		glEnd();


		//wing under 1
		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0,1.0);
		glVertex2i(426.55, 175.24);glColor3f(0.329412,0.329412,0.329412);
		glVertex2i (457.11, 162.44);
		glVertex2i (463.35, 164.04);
		glVertex2i (442.39, 175.24);
		glEnd();



		//window


		glBegin(GL_POLYGON);
		glColor3f(0.658824,0.658824,0.658824);
		circle(0.8,345,173);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.658824,0.658824,0.658824);
		circle(0.8,350,173);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.658824,0.658824,0.658824);
		circle(0.8,355,173);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.658824,0.658824,0.658824);
		circle(0.8,360,173);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.658824,0.658824,0.658824);
		circle(0.8,365,173);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.658824,0.658824,0.658824);
		circle(0.8,370,173);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.658824,0.658824,0.658824);
		circle(0.8,375,173);
		glEnd();


		glBegin(GL_POLYGON);
		glColor3f(0.658824,0.658824,0.658824);
		circle(0.8,380,173);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.658824,0.658824,0.658824);
		circle(0.8,385,173);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.658824,0.658824,0.658824);
		circle(0.8,390,173);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.658824,0.658824,0.658824);
		circle(0.8,395,173);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.658824,0.658824,0.658824);
		circle(0.8,400,173);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.658824,0.658824,0.658824);
		circle(0.8,405,173);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.658824,0.658824,0.658824);
		circle(0.8,410,173);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.658824,0.658824,0.658824);
		circle(0.8,415,173);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.658824,0.658824,0.658824);
		circle(0.8,420,173);
		glEnd();


		//logo1
		glBegin(GL_POLYGON);

		glColor3f(1.0,0.0,0.0);
		glVertex2i (351.93, 183.49);
		glVertex2i(329.41, 183.49);
		glVertex2i(326.49, 181.75);
		glVertex2i (324.16, 179.61);
		glVertex2i(330, 180);
		glVertex2i (346.69, 180.19);
		glVertex2i (349.27, 181.3);
		glEnd();

		//logo 2
		glBegin(GL_POLYGON);

		glColor3f(0.117255,0.117255,0.516863);

		glVertex2i(324.16, 179.61);
		glVertex2i (323.67, 177.82);
		glVertex2i (324.17, 175.38);
		glVertex2i (326.54, 174.09);
		glVertex2i (328.83, 173.16);
		glVertex2i (332.64, 176.39);
		glVertex2i (328.29, 177.5);
		glVertex2i (326.76, 178.43);
		glVertex2i (326.08, 179.74);
		glEnd();

	}


	void background3(){

		glBegin(GL_POLYGON);
		glColor3f(0.196078, 0.8, 1.0);
		glVertex2i (0,177);
		glVertex2i (600,177);
		glVertex2i (600,500);
		glColor3f(1.0, 1.0, 0.0);
		glVertex2i (0,500);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0, 0.0);
		circle(40,5,500);	
		glEnd();


		glBegin(GL_POLYGON);
		glColor3f(0.85,0.85, 0.85);
		glVertex2i (220,177);
		glVertex2i (250,177);
		glVertex2i (250,300);
		glVertex2i (220,300);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.85,0.85, 0.85);
		glVertex2i (203, 337);
		glVertex2i(268, 337);
		glVertex2i(268, 300);
		glVertex2i(203, 300);
		glEnd();
		//asd
		glBegin(GL_POLYGON);
		glColor3f(0.85,0.85, 0.85);
		glVertex2i (232.2, 337.65);
		glVertex2i(238.51, 337.65);
		glVertex2i (238.55, 380);
		glVertex2i (232.2, 380);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.85,0.85, 0.85);
		glVertex2i (260, 177);
		glVertex2i (600, 177);
		glVertex2i (600, 250);
		glVertex2i (260, 250);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.0,0.0, 1.0);
		glVertex2i (269.93, 207.53);
		glVertex2i(586.77, 207.53);
		glVertex2i (586.77, 235.12);
		glVertex2i (269.93, 235.12);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.0,0.0, 1.0);
		glVertex2i (203.11, 333.14);
		glVertex2i(268.56, 333.14);
		glVertex2i (268.56, 318.44);
		glVertex2i (203.11, 318.44);
		glEnd();


		//green background
		glPushMatrix();
		glColor3f(0.0, 0.5, 0.0);
		glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(600, 0);
		glVertex2f(600, 177);
		glVertex2f(0,177);
		glEnd();
		glPopMatrix();

		//Black background 1 (beneth)
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex2f(2, 45);
		glVertex2f(600, 45);
		glVertex2f(600, 105);
		glVertex2f(18,105);
		glEnd();
		glPopMatrix();


		//Black background 1 (above)
		glPushMatrix();
		glColor3f(0.3, 0.3, 0.3);
		glBegin(GL_POLYGON);
		glVertex2f(5, 50);
		glVertex2f(600, 50);
		glVertex2f(600, 100);
		glVertex2f(20,100);
		glEnd();
		glPopMatrix();


		//Black background 2 (beneth)
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex2f(20, 115);
		glVertex2f(600, 115);
		glVertex2f(600, 175);
		glVertex2f(38,175);
		glEnd();
		glPopMatrix();

		//Black background 2 (above)
		glPushMatrix();
		glColor3f(0.3, 0.3, 0.3);
		glBegin(GL_POLYGON);
		glVertex2f(25, 120);
		glVertex2f(600, 120);
		glVertex2f(600, 170);
		glVertex2f(40,170);
		glEnd();
		glPopMatrix();



		//White strips
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);


		glBegin(GL_POLYGON);
		glVertex2f(20, 70);
		glVertex2f(30, 70);
		glVertex2f(32, 73);
		glVertex2f(22, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(40, 70);
		glVertex2f(50, 70);
		glVertex2f(52, 73);
		glVertex2f(42, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(60, 70);
		glVertex2f(70, 70);
		glVertex2f(72, 73);
		glVertex2f(62, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(80, 70);
		glVertex2f(90, 70);
		glVertex2f(92, 73);
		glVertex2f(82, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(100, 70);
		glVertex2f(110, 70);
		glVertex2f(112, 73);
		glVertex2f(102, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(120, 70);
		glVertex2f(130, 70);
		glVertex2f(132, 73);
		glVertex2f(122, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(140, 70);
		glVertex2f(150, 70);
		glVertex2f(152, 73);
		glVertex2f(142, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(160, 70);
		glVertex2f(170, 70);
		glVertex2f(172, 73);
		glVertex2f(162, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(180, 70);
		glVertex2f(190, 70);
		glVertex2f(192, 73);
		glVertex2f(182, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(180, 70);
		glVertex2f(190, 70);
		glVertex2f(192, 73);
		glVertex2f(182, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(200, 70);
		glVertex2f(210, 70);
		glVertex2f(212, 73);
		glVertex2f(202, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(220, 70);
		glVertex2f(230, 70);
		glVertex2f(232, 73);
		glVertex2f(222, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(240, 70);
		glVertex2f(250, 70);
		glVertex2f(252, 73);
		glVertex2f(242, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(260, 70);
		glVertex2f(270, 70);
		glVertex2f(272, 73);
		glVertex2f(262, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(280, 70);
		glVertex2f(290, 70);
		glVertex2f(292, 73);
		glVertex2f(282, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(300, 70);
		glVertex2f(310, 70);
		glVertex2f(312, 73);
		glVertex2f(302, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(320, 70);
		glVertex2f(330, 70);
		glVertex2f(332, 73);
		glVertex2f(322, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(340, 70);
		glVertex2f(350, 70);
		glVertex2f(352, 73);
		glVertex2f(342, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(360, 70);
		glVertex2f(370, 70);
		glVertex2f(372, 73);
		glVertex2f(362, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(380, 70);
		glVertex2f(390, 70);
		glVertex2f(392, 73);
		glVertex2f(382, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(400, 70);
		glVertex2f(410, 70);
		glVertex2f(412, 73);
		glVertex2f(402, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(420, 70);
		glVertex2f(430, 70);
		glVertex2f(432, 73);
		glVertex2f(422, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(440, 70);
		glVertex2f(450, 70);
		glVertex2f(452, 73);
		glVertex2f(442, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(460, 70);
		glVertex2f(470, 70);
		glVertex2f(472, 73);
		glVertex2f(462, 73);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(480, 70);
		glVertex2f(490, 70);
		glVertex2f(492, 73);
		glVertex2f(482, 73);
		glEnd();
		//2nd street
		glBegin(GL_POLYGON);
		glVertex2f(40, 140);
		glVertex2f(50, 140);
		glVertex2f(52, 143);
		glVertex2f(42, 143);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(60, 140);
		glVertex2f(70, 140);
		glVertex2f(72, 143);
		glVertex2f(62, 143);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(80, 140);
		glVertex2f(90, 140);
		glVertex2f(92, 143);
		glVertex2f(82, 143);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(100, 140);
		glVertex2f(110, 140);
		glVertex2f(112, 143);
		glVertex2f(102, 143);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(120, 140);
		glVertex2f(130, 140);
		glVertex2f(132, 143);
		glVertex2f(122, 143);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(140, 140);
		glVertex2f(150, 140);
		glVertex2f(152, 143);
		glVertex2f(142, 143);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(160, 140);
		glVertex2f(170, 140);
		glVertex2f(172, 143);
		glVertex2f(162, 143);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(180, 140);
		glVertex2f(190, 140);
		glVertex2f(192, 143);
		glVertex2f(182, 143);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(200, 140);
		glVertex2f(210, 140);
		glVertex2f(212, 143);
		glVertex2f(202, 143);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(220, 140);
		glVertex2f(230, 140);
		glVertex2f(232, 143);
		glVertex2f(222, 143);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(240, 140);
		glVertex2f(250, 140);
		glVertex2f(252, 143);
		glVertex2f(242, 143);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(260, 140);
		glVertex2f(270, 140);
		glVertex2f(272, 143);
		glVertex2f(262, 143);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(280, 140);
		glVertex2f(290, 140);
		glVertex2f(292, 143);
		glVertex2f(282, 143);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(300, 140);
		glVertex2f(310, 140);
		glVertex2f(312, 143);
		glVertex2f(302, 143);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(320, 140);
		glVertex2f(330, 140);
		glVertex2f(332, 143);
		glVertex2f(322, 143);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(340, 140);
		glVertex2f(350, 140);
		glVertex2f(352, 143);
		glVertex2f(342, 143);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(360, 140);
		glVertex2f(370, 140);
		glVertex2f(372, 143);
		glVertex2f(362, 143);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(380, 140);
		glVertex2f(390, 140);
		glVertex2f(392, 143);
		glVertex2f(382, 143);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(400, 140);
		glVertex2f(410, 140);
		glVertex2f(412, 143);
		glVertex2f(402, 143);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(420, 140);
		glVertex2f(430, 140);
		glVertex2f(432, 143);
		glVertex2f(422, 143);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(440, 140);
		glVertex2f(450, 140);
		glVertex2f(452, 143);
		glVertex2f(442, 143);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(460, 140);
		glVertex2f(470, 140);
		glVertex2f(472, 143);
		glVertex2f(462, 143);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(480, 140);
		glVertex2f(490, 140);
		glVertex2f(492, 143);
		glVertex2f(482, 143);
		glEnd();

		glPopMatrix();
	}

	void flag()
	{

		glColor3f (0.658824, 0.658824,0.658824);
		//pole
		glBegin(GL_LINES);				
		glVertex2i (100, 10);
		glVertex2i (100, 200);
		glEnd();

		glColor3f (0.137255, 0.137255, 0.556863);
		//flag
		glBegin(GL_POLYGON);				

		glVertex2i (100, 150);
		glVertex2i (100, 200);
		glVertex2i (150+rand()%20,200+rand()%20);
		glVertex2i (150+rand()%20,150+rand()%20);
		glEnd();


	}

	void lineA(){
		//tyre line 1
		glLineWidth(2);
		glBegin(GL_POLYGON);

		glColor3f(1.0,1.0,1.0);

		glVertex2i (338.3, 155.99);glColor3f(0.329412,0.329412,0.329412);
		glVertex2i (341.3, 155.99);
		glVertex2i (341.3, 150.99);
		glVertex2i (339.3, 150.99);

		glEnd();
	}
	void tyreA(){

		// tyre 1

		glBegin(GL_POLYGON);
		glColor3f(0.0,0.0,0.0);
		circle(4,340,145);

		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.452941,0.452941,0.452941);

		circle(3,340,145);

		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.0,0.0,0.0);

		circle(2.7,340,145);

		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(1.0,1.0,1.0);

		circle(0.2,340,145);

		glEnd();
	}
	void tyreB(){
		//second tyre
		glBegin(GL_POLYGON);
		glColor3f(0.0,0.0,0.0);
		circle(4,392,145);

		glEnd();
		//SECOND TYRE inside
		glBegin(GL_POLYGON);
		glColor3f(0.452941,0.452941,0.452941);

		circle(3,392,145);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.0,0.0,0.0);

		circle(2.7,392,145);

		glEnd();

	}
	void text2()
	{
		int red = rand()%255;
		int green = rand()%255;
		int blue = rand()%255;
		glColor3f (float(green)/255.0, 0, 0.0);


		renderSpacedBitmapString(0,0,GLUT_BITMAP_HELVETICA_18,"Navigate to....");


	}
	void text3()
	{
		int red = rand()%255;
		int green = rand()%255;
		int blue = rand()%255;
		glColor3f (float(green)/255.0, 0, 0.0); 


		renderSpacedBitmapString(0,0,GLUT_BITMAP_HELVETICA_18,"Vibrant cities ....");


	}

	void light(){

		glBegin(GL_POLYGON);

		glVertex2i (111.47, 0);
		glVertex2i (115.07, 0);
		glVertex2i (115.07, 281.72);
		glVertex2i(111.47, 281.72);
		glEnd();

		glBegin(GL_POLYGON);

		glVertex2i (168.47, 0);
		glVertex2i (172.07, 0);
		glVertex2i (172.07, 281.72);
		glVertex2i(168.47, 281.72);
		glEnd();


	}


	GLuint texture[1];

	typedef struct Texture_Image
	{
		int width;
		int height;
		int format;
		unsigned char *data;
	} 

	TEXTURE_IMAGE;

	typedef TEXTURE_IMAGE *P_TEXTURE_IMAGE;

	P_TEXTURE_IMAGE t1;


	P_TEXTURE_IMAGE AllocateTextureBuffer(GLint w, GLint h, GLint f)
	{
		P_TEXTURE_IMAGE ti=NULL;
		unsigned char *c=NULL;

		ti = (P_TEXTURE_IMAGE)malloc(sizeof(TEXTURE_IMAGE));

		if (ti != NULL) {
			ti->width = w;
			ti->height = h;
			ti->format = f;

			c = (unsigned char *)malloc(w * h * f);

			if (c != NULL) {
				ti->data = c;
			}else {
				printf("File Error");
				return NULL;
			}
		}else
		{
			printf("File Error");
			return NULL;
		}
		return ti;
	}

	void DeallocateTexture(P_TEXTURE_IMAGE t)
	{
		if(t)
		{
			if(t->data)
			{
				free(t->data);
			}
			free(t);
		}
	}


	int ReadTextureData (char *filename, P_TEXTURE_IMAGE buffer)
	{
		FILE *f;
		int i, j, k, done = 0;
		int stride = buffer->width * buffer->format;
		unsigned char *p = NULL;

		f = fopen(filename, "rb");
		if (f !=NULL)
		{
			for (i = buffer->height-1; i>=0; i--)
			{
				p = buffer->data + (i * stride);
				for (j = 0; j < buffer->width; j++)
				{
					for (k = 0; k < buffer->format-1; k++, p++, done++)
					{
						*p = fgetc(f);
					}
					*p = 255; p++;
				}
			}
			fclose(f);
		}else
		{
			printf("File Name Error\n");
		}
		return done;
	}


	void BuildTexture (P_TEXTURE_IMAGE tex)
	{
		glGenTextures(1, &texture[0]);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->width, tex->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->data);
	}

	void PictureQuad(){

		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glBegin(GL_QUADS);
		glColor3f(1.85,0.85,0.10);
		glTexCoord2f(1.0, 0.0);glVertex3f( 112, 112, 0.0);
		glTexCoord2f(1.0, 1.0);glVertex3f( 112, -112, 0.0);
		glTexCoord2f(0.0, 1.0);glVertex3f( -112, -112, 0.0);
		glTexCoord2f(0.0, 0.0);glVertex3f( -112, 112, 0.0);
		glEnd();
	}


	void display(void)
	{

		glClear(GL_COLOR_BUFFER_BIT);

		frame++;
		fprintf(stdout,"Frame = %i\n", frame);


		if((frame>0) && (frame<=50))	
		{

			glPushMatrix();
			background1();
			playbutton();
			glPopMatrix();


		}
		else if((frame>50) && (frame<=480))	
		{
			background2();

			glPushMatrix();
			glTranslatef(10,10,0);
			glScalef(0.5,2.0,0);
			text1();
			glPopMatrix();

			glPushMatrix();		
			fTranslate += 2.0f;
			glTranslatef(-fTranslate, 0 , 0);
			airplane1();

			glTranslatef(866, 140 , 0);


			fRotate    += 2.0f;
			glRotatef(-theta, 0, 0, 1);
			tyre1();
			glPopMatrix();

		}
		else if((frame>480) && (frame<=750)){
			background3();
			glPushMatrix();
			glTranslatef(10,10,0);
			glScalef(0.5,2.0,0);
			text2();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-60, 166 , 0);
			flag();
			glPopMatrix();



			if((frame > 480) && (frame<=700)){


				glPushMatrix();
				fTranslate += 2.0f;
				glTranslatef(1100, 0 , 0);
				glTranslatef(-fTranslate,0,0);
				tyreB();
				airplane2();
				lineA();
				tyreA();
				glPopMatrix();

			}

			if((frame>700) && (frame<=750)){
				glPushMatrix();
				fTranslate += 1.8;
				glTranslatef(1050,250,0);
				glTranslatef(-fTranslate,0,0);
				airplane2();
				glPopMatrix();
			}

		}
		else if((frame>750) && (frame<=1000)){


			background4();

			glPushMatrix();
			glTranslatef(10,10,0);
			glScalef(0.5,2.0,0);
			text3();
			glPopMatrix();

			glPushMatrix();
			fTranslate += 1.8;
			glTranslatef(1500,250,0);
			glTranslatef(-fTranslate,0,0);
			airplane2();
			glPopMatrix();

			glColor3f(colour[cycle][0],colour[cycle][1],colour[cycle][2]);


			glPushMatrix();
			cycle++;
			light();
			glPopMatrix();


		}

		else if((frame>1000) && (frame<=1250)){

			background5();

			glPushMatrix();
			glTranslatef(10,10,0);
			glScalef(0.5,2.0,0);
			text4();
			glPopMatrix();

			fTranslate += 1.8;
			glPushMatrix();

			glTranslatef(1950,250,0);
			glTranslatef(-fTranslate,0,0);
			airplane2();
			glPopMatrix();

			glPushMatrix();


			glTranslatef(180,-900,0);	
			glScalef(1.9,2,0);
			hollywood_text();
			glPopMatrix();


		}
		else if((frame>1250) && (frame<=1530)){	

			background6();
			snowing();
			glPushMatrix();
			glTranslatef(10,10,0);
			glScalef(0.5,2.0,0);
			text5();
			glPopMatrix();


			fTranslate += 1.8;

			glPushMatrix();
			glTranslatef(2450,250,0);
			glTranslatef(-fTranslate,0,0);
			airplane2();
			glPopMatrix();

		}
		else if((frame>1530) && (frame<=1770)){	

			background7();

			glPushMatrix();
			glTranslatef(10,10,0);
			glScalef(0.5,2.0,0);
			text6();
			glPopMatrix();

			fTranslate += 1.8;
			glPushMatrix();
			glTranslatef(2950,250,0);
			glTranslatef(-fTranslate,0,0);
			airplane2();
			glPopMatrix();

			glPushMatrix();
			fTranslate += 0.3;

			boat();
			glPopMatrix();
		}

		else if((frame>1770) && (frame<=1980)){	

			glPushMatrix();
			glViewport(0, 0, 375, 840);
			background4();
			glPopMatrix();

			if((frame>1820) && (frame<=1870)){

				glPushMatrix();
				glViewport(375, 0, 375, 840);
				background5();
				glPopMatrix();

			}else if((frame>1870) && (frame<=1920)){	

				glPushMatrix();
				glViewport(375, 0, 375, 840);
				background5();
				glPopMatrix();

				glPushMatrix();
				glViewport(750, 0, 375, 840);
				background6();
				glPopMatrix();

			}else if((frame>1920) && (frame<=1980)){	
				glPushMatrix();
				glViewport(375, 0, 375, 840);
				background5();
				glPopMatrix();

				glPushMatrix();
				glViewport(750, 0, 375, 840);
				background6();
				glPopMatrix();

				glPushMatrix();
				glViewport(1125, 0, 375, 840);
				background7();
				glPopMatrix();
			}


		}
		else if((frame>0) && (frame<=2100)){	

			background9();
			glPushMatrix();
			glTranslatef(222,112,0);
			glEnable(GL_TEXTURE_2D);
			PictureQuad();
			glDisable(GL_TEXTURE_2D);
			glPopMatrix();

			glViewport(0,0,1450,840);


			glPushMatrix();
			glTranslatef(204,140,0);
			glScalef(0.4,2.0,0);
			text8();

			glPopMatrix();

			glPushMatrix();
			glTranslatef(20,350,0);
			glScalef(0.5,2.0,0);
			text7();

			glPopMatrix();

			if((frame>1980) && (frame<1990))
			{

				morphplane1();
			}


			else if((frame>1989) && (frame<2100))
			{

				morphplane2();
				proportion +=0.03;

				if(proportion >1.0) proportion =1.0;
			}


		}
		else if((frame>2100) && (frame<=2230)){	

			background8();

			glPushMatrix();
			glTranslatef(300,300,0);
			glRotatef(spin, 0.0, 0.0, 1.0);
			glColor3f(0.658824,  0.658824 , 0.658824);
			glRectf(-25.0, -25.0, 25.0, 25.0);
			glColor3f(0.329412,  0.329412 , 0.329412);
			glRectf(-20.0, -20.0, 20.0, 20.0);
			glColor3f(0.80,  0.80 , 0.80);
			glRectf(-15.0, -15.0, 15.0, 15.0);
			glPopMatrix();


			if((frame >2100) && (frame < 2130)){

				sc2();

			}
			else if((frame >2130) && (frame < 2230)){
				hand();
				sc3();

			}


		}
		else if((frame>2230) && (frame<=2530)){

			background10();

			glPushMatrix();
			glTranslatef(232,250,0);	
			glScalef(0.1,2.0,0);
			glScalef(fScale,0,0);
			text9();


			glPopMatrix();

			fScale +=0.05;

			if(fScale >5.0) fScale =5.0;

		}

		if(spin>=360.0) sign =1;	
		if (sign ==0) spin=spin+2.0;
		if (sign ==1) spin=spin-2.0;

		if(theta>=90.0) sign =1;	
		if (sign ==0) theta=theta+2.0;
		if (sign ==1) theta=theta-2.0;

		fScale     -= 0.010f;
		//if(fTranslate > 5530.0f) fTranslate = 0.0f;  
		//if(frame>2530)frame=0;
		if(frame>2500)exit(0);
		if(fScale < 0.5f)     fScale     = 1.0f;



		glutSwapBuffers();
		glFlush ();
	}

	void Timer( int value )
	{
		if( value ) glutPostRedisplay();
		glutTimerFunc(40,Timer,value);
	}
	void spinDisplay()
	{
		spin = spin + 2.0;
		if(spin > 360.0)
			spin = spin - 360.0;
		glutPostRedisplay();
	}

	int init(GLvoid)
	{

		glClearColor (0.196078, 0.6,0.8, 1.0);

		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();
		gluOrtho2D(0,500,0,500);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		t1 = AllocateTextureBuffer(256, 256, 4);
		if (ReadTextureData("globe.bmp", t1) == 0)
		{
			printf("File Error\n");
			return false;
		}

		BuildTexture (t1);

		DeallocateTexture (t1);



		return true;
	}

	void Visibility (int state) 
	{ 

		switch (state) { 
		case GLUT_VISIBLE: 
			Timer(1); 
			break; 
		case GLUT_NOT_VISIBLE: 
			Timer(0); 
			break; 
		default: break; } 
	} 


	int main(int argc, char** argv)
	{

		glutInit(&argc,argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
		glutInitWindowSize(1440,720);
		glutInitWindowPosition(90,160);
		glutCreateWindow("British Airways");
		glutDisplayFunc(display);
		init();
		glutVisibilityFunc(Visibility);

		glutMainLoop();
		return 0;

	}


