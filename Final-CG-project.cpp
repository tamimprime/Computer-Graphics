#include <iostream>
#include <stdlib.h>
#include<GL/gl.h>
#include <GL/glut.h>
#include<math.h>
#include<cmath>
#include<cstring>
#define playerSizeY .2
#define playerSizeX .1
#define maxAxisX 2
#define maxAxisY 2
#include<time.h>
#include<windows.h>
#include <sstream>
#include<fstream>
# define PI 3.14
using namespace std;
void player();
void enemy1();
void enemy2();
void ally1();
void updateWheel(int value);
void playerWheelMoving();
void display1();
float playerPositionx=0,playerPositiony=0,enemy1Positionx=-0.3,enemy1Positiony=1.8,enemy2Positionx=-0.8,ally1Positionx=-0.6,ally1Positiony=1.6,scoreUpPositionx=0.3,scoreUpPositiony=1.6;
int timer=500;
float _angleWheel = 0;
float speedWheel = 1.0f;
char gameOverText[] = "GAME OVER. ";
bool gameOver=false;
short life=3;
int sky1=38, sky2= 154, sky3=  214;
int sun1= 252, sun2=211, sun3= 3;
int daynightcounter=2;
bool scenestatus=true;
float bigshipposition=0.0;
float smallshipposition=0.0;
float positionCloud1=0.0f;
float speedCloud1=0.003f;
float positionCloud2=0.0f;
float speedCloud2=0.005f;
float positionRain= 0.0f;
float speedRain=- 0.01f;
bool rainStatus=false;

void display()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    display1();
    player();
    enemy1();
    enemy2();
    ally1();
    glFlush();
}

void player()

{
    glPushMatrix();
    glColor3ub(139,0,0);
    glTranslatef(playerPositionx, playerPositiony, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0,-0.95);
    glVertex2f(0.1,-0.95);
    glVertex2f(0.05,-0.85);
    glEnd();

    glColor3ub(0,0,139);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.05,-1.0);
    glVertex2f(0.1,-0.9);
    glVertex2f(0.0,-0.9);
    glEnd();
    glPopMatrix();

    ///WHEEL
    ///FIRST BLADE
    glPushMatrix();
    glTranslatef(playerPositionx, playerPositiony, 0.0);
    glTranslatef(0.05,-0.85,  0.0);
    glScaled(0.1,0.1,1.0);
    glPushMatrix();
    glRotatef(_angleWheel, 0.0, 0.0, 1.0);
    glScaled(0.5,0.5,1.0);
    glTranslatef(0.1, -0.1, 0.0);//Rotate about the the vector (1, 2, 3)
    glColor3ub(139,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(0.0,0.0);
    glVertex2f(0.9,0.1);
    glVertex2f(0.0,0.2);
    glEnd();
    glPopMatrix();



///SECOND BLADE
    glPushMatrix(); //Save the current state of transformations
    glRotatef(_angleWheel, 0.0, 0.0, 1.0);
    glScaled(0.5,0.5,1.0);
    glTranslatef(-0.1, -0.1, 0.0);//Rotate about the the vector (1, 2, 3)
    glBegin(GL_POLYGON);
    glVertex2f(0.0,0.0);
    glVertex2f(-0.9,0.1);
    glVertex2f(0.0,0.2);
    glEnd();
    glPopMatrix();


///THIRD BLADE
    glPushMatrix();
    glRotatef(_angleWheel, 0.0, 0.0, 1.0);
    glScaled(0.5,0.5,1.0);
    glTranslatef(-0.1, -0.1, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(0.0,0.0);
    glVertex2f(0.1,-0.9);
    glVertex2f(0.2,0.0);
    glEnd();
    glPopMatrix();


///FOURTH BLADE
    glPushMatrix();
    glRotatef(_angleWheel, 0.0, 0.0, 1.0);
    glScaled(0.5,0.5,1.0);
    glTranslatef(-0.1, 0.1, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(0.0,0.0);
    glVertex2f(0.1,0.9);
    glVertex2f(0.2,0.0);
    glEnd();
    glPopMatrix();
    glPopMatrix();

}

void playerWheelMoving()
{
    _angleWheel += speedWheel;
    if (_angleWheel > 360)
        {
            _angleWheel -= 360;
        }
}

void enemy1()
{
    glPushMatrix();
    glColor3ub(169,169,169);
    glTranslatef(enemy1Positionx, enemy1Positiony, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(0.002,-0.98);
    glVertex2f(0.045,-0.99);
    glVertex2f(0.053,-0.97);
    glVertex2f(0.05,-0.94);
    glVertex2f(0.04,-0.91);
    glVertex2f(0.0023,-0.93);
    glVertex2f(0.001,-0.96);
    glEnd();
    glPopMatrix();
}

void enemy1Move()
{
    ///Enemy Movement
    float collision2=enemy1Positiony-playerPositiony;
    ///FOR ENEMY 1
    if(((collision2>0.19 && collision2<0.21) || (collision2>0.09 && collision2<0.11) || (collision2>-0.01 && collision2<0.01)) &&  (abs(enemy1Positionx-playerPositionx)<0.09 || abs(enemy2Positionx-playerPositionx)<0.09) )
    {
        life--;
        if(life<=0)
        {
            gameOver=true;
        }

    }

    if(enemy1Positiony>-maxAxisY)

    {
        enemy1Positiony-=0.1;
    }

    else
        {
            enemy1Positiony=1.8;
            //score+=2;
            srand(time(0));
            enemy1Positionx=((float)(rand()%10))/10-((float)(rand()%10))/10; //randomly enemy coming
            srand(time(0)*5);
            enemy2Positionx=((float)(rand()%10))/10-((float)(rand()%10))/10;

            if(timer>100)
                {
                    timer=timer-100;
                }
        }
}


void enemy2()
{
    glPushMatrix();
    glColor3ub(169,169,169);
    glTranslatef(enemy2Positionx, enemy1Positiony, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(0.002,-0.98);
    glVertex2f(0.045,-0.99);
    glVertex2f(0.053,-0.97);
    glVertex2f(0.05,-0.94);
    glVertex2f(0.04,-0.91);
    glVertex2f(0.0023,-0.93);
    glVertex2f(0.001,-0.96);
    glEnd();
    glPopMatrix();
}

void ally1()
{
    glPushMatrix();
    glTranslatef(ally1Positionx, ally1Positiony, 0.0);
    glTranslatef(0.026, -0.38, 0.0);
    glScaled(0.028,0.028,1.0);
    glPushMatrix();
    glColor3f(0.0,1.0,1.0);
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
        {
            glColor3f(1.0,0.0,0.0);
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=0.85;
            float x = r * cos(A);
            float y = r * sin(A)-19.0;
            glVertex2f(x,y );
        }

	glEnd();
    glPopMatrix();

    glPushMatrix();
	glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
        {
            glColor3f(1.0,0.0,0.0);
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=0.85;
            float x = r * cos(A)+1.48;
            float y = r * sin(A)-19.0;
            glVertex2f(x,y );
        }

	glEnd();
    glPopMatrix();

    glPushMatrix();
    glScaled(3.35,2.5,1.0);
    glTranslatef(-0.29,-7.7, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(1.0,0.0,0.0);
	glVertex2f(0.0,0.0);
	glVertex2f(1.0,0.0);
	glVertex2f(0.5,-1.0);
	glEnd();
    glPopMatrix();
    glPopMatrix();
}
void ally1Move()
{
    float collision2=ally1Positiony-playerPositiony;
    ///FOR ALLY 1
    if(((collision2>0.19 && collision2<0.21) || (collision2>0.09 && collision2<0.11) || (collision2>-0.01 && collision2<0.01)) &&  abs(ally1Positionx-playerPositionx)<0.09 )
    {
        //RANDOM X AXIS
        srand(time(0)*3);
        ally1Positionx=((float)(rand()%10))/10-((float)(rand()%10))/10;

        if((abs(ally1Positionx-enemy1Positionx)<0.09 || abs(ally1Positionx-enemy2Positionx)<0.09) && abs(ally1Positiony-enemy1Positiony)<0.09)
        {
            ally1Positiony+=0.2;
        }
        ally1Positiony=2;
    }

    ///MOVEMENT
    ally1Positiony-=0.1;
    if(ally1Positiony<-0.1)
    {
        life=0;
        gameOver=true;
    }
}

void update(int value)
{
    if(!gameOver)
    {
        enemy1Move();
        ally1Move();
        //scoreUpMove();
        glutPostRedisplay();
        glutTimerFunc(timer, update, 0);
    }
}

void specialKeys(int key, int x, int y) {
    if(!gameOver)
    {
        switch (key)
        {

     case GLUT_KEY_UP:

          if(playerPositiony<maxAxisY-playerSizeY)
          {
              playerPositiony+=0.1;
          }
          break;

      case GLUT_KEY_DOWN:

          if(playerPositiony>=0.1)
          {
              playerPositiony-=0.1;
          }
          break;

       case GLUT_KEY_LEFT:

           if(playerPositionx>=-maxAxisX/2+playerSizeX-0.1)
           {
               playerPositionx-=0.1;
           }
          break;

      case GLUT_KEY_RIGHT:

          if(playerPositionx<maxAxisX/2-playerSizeX)
           {
               playerPositionx+=0.1;
           }
          break;
    }
}
    glutPostRedisplay();
}

void updateWheel(int value)
{
   if(!gameOver)
   {
        playerWheelMoving();
        glutPostRedisplay();
        glutTimerFunc(1, updateWheel, 0);
   }
}


//rain
void rain()
{
    glLineWidth(0.046);
    glBegin(GL_LINES);
    glColor3ub(255,255,255);
    glVertex2f(1.0,1.0);
    glVertex2f(0.995,0.975);

    glVertex2f(0.980,1.0);
    glVertex2f(0.975,0.975);

    glVertex2f(0.940,1.0);
    glVertex2f(0.935,0.98);

    glVertex2f(0.900,1.0);
    glVertex2f(0.895,0.98);

    glVertex2f(0.860,1.0);
    glVertex2f(0.855,0.98);

    glVertex2f(0.820,1.0);
    glVertex2f(0.815,0.98);

    glVertex2f(0.780,1.0);
    glVertex2f(0.775,0.98);

    glVertex2f(0.740,1.0);
    glVertex2f(0.735,0.98);

    glVertex2f(0.700,1.0);
    glVertex2f(0.695,0.98);

    glVertex2f(0.660,1.0);
    glVertex2f(0.655,0.98);

    glVertex2f(0.620,1.0);
    glVertex2f(0.615,0.98);

    glVertex2f(0.580,1.0);
    glVertex2f(0.575,0.98);

    glVertex2f(0.540,1.0);
    glVertex2f(0.535,0.98);

    glVertex2f(0.500,1.0);
    glVertex2f(0.495,0.98);

    glVertex2f(0.460,1.0);
    glVertex2f(0.455,0.98);

    glVertex2f(0.420,1.0);
    glVertex2f(0.415,0.98);

    glVertex2f(0.380,1.0);
    glVertex2f(0.375,0.98);

    glVertex2f(0.340,1.0);
    glVertex2f(0.335,0.98);

    glVertex2f(0.300,1.0);
    glVertex2f(0.295,0.98);

    glVertex2f(0.260,1.0);
    glVertex2f(0.255,0.98);

    glVertex2f(0.220,1.0);
    glVertex2f(0.215,0.98);

    glVertex2f(0.180,1.0);
    glVertex2f(0.175,0.98);

    glVertex2f(0.140,1.0);
    glVertex2f(0.135,0.98);

    glVertex2f(0.100,1.0);
    glVertex2f(0.095,0.98);

    glVertex2f(0.060,1.0);
    glVertex2f(0.055,0.98);

    glVertex2f(0.020,1.0);
    glVertex2f(0.015,0.98);

    glVertex2f(-0.020,1.0);
    glVertex2f(-0.025,0.98);

    glVertex2f(-0.060,1.0);
    glVertex2f(-0.065,0.98);

    glVertex2f(-0.100,1.0);
    glVertex2f(-0.105,0.98);

    glVertex2f(-0.140,1.0);
    glVertex2f(-0.145,0.98);

    glVertex2f(-0.180,1.0);
    glVertex2f(-0.185,0.98);

    glVertex2f(-0.220,1.0);
    glVertex2f(-0.225,0.98);

    glVertex2f(-0.260,1.0);
    glVertex2f(-0.265,0.98);

    glVertex2f(-0.300,1.0);
    glVertex2f(-0.305,0.98);

    glVertex2f(-0.340,1.0);
    glVertex2f(-0.345,0.98);

    glVertex2f(-0.380,1.0);
    glVertex2f(-0.385,0.98);

    glVertex2f(-0.420,1.0);
    glVertex2f(-0.425,0.98);

    glVertex2f(-0.460,1.0);
    glVertex2f(-0.465,0.98);

    glVertex2f(-0.500,1.0);
    glVertex2f(-0.505,0.98);

    glVertex2f(-0.540,1.0);
    glVertex2f(-0.545,0.98);

    glVertex2f(-0.580,1.0);
    glVertex2f(-0.585,0.98);

    glVertex2f(-0.620,1.0);
    glVertex2f(-0.625,0.98);

    glVertex2f(-0.660,1.0);
    glVertex2f(-0.665,0.98);

    glVertex2f(-0.700,1.0);
    glVertex2f(-0.705,0.98);

    glVertex2f(-0.740,1.0);
    glVertex2f(-0.745,0.98);

    glVertex2f(-0.780,1.0);
    glVertex2f(-0.785,0.98);

    glVertex2f(-0.820,1.0);
    glVertex2f(-0.825,0.98);

    glVertex2f(-0.860,1.0);
    glVertex2f(-0.865,0.98);

    glVertex2f(-0.900,1.0);
    glVertex2f(-0.905,0.98);

    glVertex2f(-0.940,1.0);
    glVertex2f(-0.945,0.98);

    glVertex2f(-0.980,1.0);
    glVertex2f(-0.985,0.98);
    glEnd();
}


///Scene

void display1()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
    ///fullsky
    glPushMatrix();
    glBegin(GL_POLYGON);
	glColor3ub(sky1,sky2,sky3);
	glVertex2f(-1.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(-1.0f, 0.0f);
	glEnd();
    glPopMatrix();

    int i;
	GLfloat x=0.7f; GLfloat y=0.7f; GLfloat radius =.1f;
	int triangleAmount = 20;
	GLfloat twicePi = 2.f * PI;
	glBegin(GL_TRIANGLE_FAN);
	    glColor3ub(sun1, sun2, sun3);
		glVertex2f(x, y);
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)),
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();

    glBegin(GL_POLYGON);//mati
	glColor3ub(255, 230, 128);
	glVertex2f(-1.0f, -0.6f);
	glVertex2f(1.0f,-0.6f);
	glVertex2f(1.0f, -1.0f);
	glVertex2f(-1.f, -1.0f);
	glEnd();

    glBegin(GL_POLYGON);//mati1
	glColor3ub(255, 217, 179);
	glVertex2f(-1.0f, -0.6f);
	glVertex2f(1.0f,-0.6f);
	glVertex2f(1.0f, -1.0f);
	glVertex2f(-1.f, -1.0f);
	glEnd();

	///water()
    glBegin(GL_QUADS);
    glColor3ub(0, 153, 153);
    glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, -0.5f);
	glVertex2f(-1.0f, -0.5f);
	glEnd();

    ///small boat
    glPushMatrix();
    glTranslatef(smallshipposition, 0.0, 0.0);
    glBegin(GL_POLYGON); //boatp
	glColor3ub(27, 75, 52);
	glVertex2f(0.6f, -0.0f);
	glVertex2f(0.63f, -0.02f);
	glVertex2f(0.65f, -0.02f);
    glVertex2f(0.68f, -0.0f);
    glEnd();



    glBegin(GL_TRIANGLES);//bpal
	glColor3ub(27, 75, 52);
	glVertex2f(0.63f, 0.0f);
	glVertex2f(0.65f, 0.1f);
	glVertex2f(0.65f, 0.0f);
    glEnd();
    glPopMatrix();

///big ship
    glPushMatrix();
    glTranslatef(bigshipposition, 0.0, 0.0);
    glBegin(GL_POLYGON);//hb
    glColor3ub(0, 0, 0);
	glVertex2f(-0.3f, -0.1f);
	glVertex2f(-0.3f, -0.03f);
	glVertex2f(0.3f, -0.03f);
    glVertex2f(0.3f, -0.1f);
    glEnd();

    glBegin(GL_POLYGON);//hb
    glColor3ub(178, 190, 181);
	glVertex2f(-0.28f, -0.03f);
	glVertex2f(0.28f, -0.03f);
	glVertex2f(0.28f, 0.05f);
	glVertex2f(-0.28f, 0.05f);
    glEnd();

    glBegin(GL_LINES);//bh
    glColor3ub(0,0,0);
    glVertex2f(0.28f, -0.03f);
	glVertex2f(-0.28f, -0.03f);
    glEnd();

    glBegin(GL_POLYGON);//bh
    glColor3ub(0, 0, 0);
    glVertex2f(-0.25f, 0.05f);
    glVertex2f(0.25f, 0.05f);
	glVertex2f(0.25f, 0.12f);
	glVertex2f(-0.25f, 0.12f);
    glEnd();

    glBegin(GL_LINES);//bh
    glColor3ub(0,0,0);
    glVertex2f(-0.25f, 0.05f);
    glVertex2f(0.25f, 0.05f);
    glEnd();

    glBegin(GL_POLYGON);//bh
    glColor3ub(178, 190, 181);
    glVertex2f(-0.23f, 0.12f);
    glVertex2f(-0.12f, 0.12f);
	glVertex2f(-0.12f, 0.17f);
	glVertex2f(-0.23f, 0.17f);
    glEnd();

    glBegin(GL_POLYGON);//bh
    glColor3ub(178, 190, 181);
    glVertex2f(0.23f, 0.12f);
    glVertex2f(0.12f, 0.12f);
	glVertex2f(0.12f, 0.17f);
	glVertex2f(0.23f, 0.17f);
    glEnd();

    glBegin(GL_POLYGON);//bh
    glColor3ub(178, 190, 181);
    glVertex2f(-0.09f, 0.12f);
    glVertex2f(0.09f, 0.12f);
	glVertex2f(0.09f, 0.17f);
	glVertex2f(-0.09f, 0.17f);
    glEnd();

    glBegin(GL_LINES);//bh
    glColor3ub(0,0,0);
    glVertex2f(-0.25f, 0.12f);
    glVertex2f(0.25f, 0.12f);
    glEnd();

    glBegin(GL_POLYGON);//bh
	glColor3ub(178, 190, 181);
	glVertex2f(-0.4f, -0.1f);
	glVertex2f(-0.35f, -0.25f);
	glVertex2f(0.35f, -0.25f);
    glVertex2f(0.4f, -0.1f);
    glEnd();

    glBegin(GL_POLYGON);//bh
	glColor3ub(0, 0, 0);
	glVertex2f(-0.35f, -0.25f);
	glVertex2f(0.35f, -0.25f);
	glVertex2f(0.34f,-0.30f);
	glVertex2f(-0.34f, -0.30f);
    glEnd();
    glPopMatrix();

    //tree
    glBegin(GL_QUADS);//coplant
	glColor3ub(77, 40, 0);
	glVertex2f(-0.8f, -0.75f);
	glVertex2f(-0.77f,-0.75f);
	glVertex2f(-0.77f, -0.9f);
	glVertex2f(-0.8f, -0.9f);
	glEnd();

    glBegin(GL_QUADS);//coplant2
	glColor3ub(77, 40, 0);
	glVertex2f(-0.77f, -0.3f);
	glVertex2f(-0.76f,-0.3f);
	glVertex2f(-0.77f, -0.75f);
	glVertex2f(-0.8f, -0.75f);
	glEnd();


    glBegin(GL_TRIANGLES);//copata1
	glColor3ub(0, 77, 0);
    glVertex2f(-0.77f, -0.3f);
    glVertex2f(-0.86f,-0.33f);
    glVertex2f(-0.8f, -0.36f);
	glEnd();

    glBegin(GL_TRIANGLES);//copata1
	glColor3ub(0, 77, 0);
    glVertex2f(-0.9f, -0.45f);
    glVertex2f(-0.86f,-0.33f);
    glVertex2f(-0.8f, -0.36f);
	glEnd();

    glBegin(GL_TRIANGLES);//copata2
	glColor3ub(0, 77, 0);
    glVertex2f(-0.77f, -0.3f);
    glVertex2f(-0.65f,-0.33f);
    glVertex2f(-0.68f, -0.4f);
	glEnd();

    glBegin(GL_TRIANGLES);//copata2
	glColor3ub(0, 77, 0);
    glVertex2f(-0.65f,-0.33f);
    glVertex2f(-0.68f, -0.4f);
    glVertex2f(-0.6f, -0.45f);
	glEnd();

    glBegin(GL_QUADS);//copata3
	glColor3ub(0, 77, 0);
    glVertex2f(-0.56f,-0.27f);
    glVertex2f(-0.67f, -0.2f);
    glVertex2f(-0.57f, -0.25f);
    glVertex2f(-0.77f, -0.3f);
	glEnd();

    glBegin(GL_QUADS);//copata4
	glColor3ub(0, 77, 0);
    glVertex2f(-0.90f,-0.28f);
    glVertex2f(-0.97f, -0.25f);
    glVertex2f(-0.87f, -0.2f);
    glVertex2f(-0.77f, -0.3f);
	glEnd();

	
	///cloud 1
	///circle 1
	glLoadIdentity();
    glPushMatrix();
    glTranslatef(positionCloud1, 0.0f, 0.0f);
    int i1;
	float x1=-0.1f; float y1=0.8f; float radius1 =0.05f;
	int polygonAmount1 = 20;
	float twicePi1 = 2.0f * PI;

	glBegin(GL_POLYGON);
	glColor3ub(250, 249, 245);
    glVertex2f(x1, y1);
    for(i1 = 0; i1 <= polygonAmount1;i1++) {
        glVertex2f(
                x1 + (radius1 * cos(i1 *  twicePi1 / polygonAmount1)),
            y1 + (radius1 * sin(i1 * twicePi1 / polygonAmount1))
        );
    }
	glEnd();

    ///circle 2
    int i2;
	float x2=-0.05f; float y2=0.85f; float radius2 =0.05f;
	int polygonAmount2 = 20;
	float twicePi2 = 2.0f * PI;

	glBegin(GL_POLYGON);
	glColor3ub(250, 249, 245);
    glVertex2f(x2, y2);
    for(i2 = 0; i2 <= polygonAmount2;i2++) {
        glVertex2f(
                x2 + (radius2 * cos(i2 *  twicePi2 / polygonAmount2)),
            y2 + (radius2 * sin(i2 * twicePi2 / polygonAmount2))
        );
    }
	glEnd();

	///circle 3
    int i3;
	float x3=0.0f; float y3=0.8f; float radius3 =0.05f;
	int polygonAmount3 = 20;
	float twicePi3 = 2.0f * PI;

	glBegin(GL_POLYGON);
	glColor3ub(250, 249, 245);
    glVertex2f(x3, y3);
    for(i3 = 0; i3 <= polygonAmount3;i3++) {
        glVertex2f(
                x3 + (radius3 * cos(i3 *  twicePi3 / polygonAmount3)),
            y3 + (radius3 * sin(i3 * twicePi3 / polygonAmount3))
        );
    }
	glEnd();

	///circle 4
    int i4;
	float x4=-0.03f; float y4=0.77f; float radius4 =0.05f;
	int polygonAmount4 = 20;
	float twicePi4 = 2.0f * PI;

	glBegin(GL_POLYGON);
	glColor3ub(250, 249, 245);
    glVertex2f(x4, y4);
    for(i4 = 0; i4 <= polygonAmount4;i4++) {
        glVertex2f(
                x4 + (radius4 * cos(i4 *  twicePi4 / polygonAmount4)),
            y4 + (radius4 * sin(i4 * twicePi4 / polygonAmount4))
        );
    }
	glEnd();
	glPopMatrix();
    glLoadIdentity();

	///cloud 2
	///circle 1
	glLoadIdentity();
    glPushMatrix();
    glTranslatef(positionCloud2, 0.0f, 0.0f);
    i1;
	x1=0.41f; y1=0.88f; radius1 =0.05f;
    polygonAmount1 = 20;
	twicePi1 = 2.0f * PI;

	glBegin(GL_POLYGON);
	glColor3ub(250, 249, 245);
    glVertex2f(x1, y1);
    for(i1 = 0; i1 <= polygonAmount1;i1++) {
        glVertex2f(
                x1 + (radius1 * cos(i1 *  twicePi1 / polygonAmount1)),
            y1 + (radius1 * sin(i1 * twicePi1 / polygonAmount1))
        );
    }
	glEnd();

    ///circle 2
    i2;
	x2=0.39f; y2=0.8f; radius2 =0.05f;
	polygonAmount2 = 20;
	twicePi2 = 2.0f * PI;

	glBegin(GL_POLYGON);
	glColor3ub(250, 249, 245);
    glVertex2f(x2, y2);
    for(i2 = 0; i2 <= polygonAmount2;i2++) {
        glVertex2f(
                x2 + (radius2 * cos(i2 *  twicePi2 / polygonAmount2)),
            y2 + (radius2 * sin(i2 * twicePi2 / polygonAmount2))
        );
    }
	glEnd();

	///circle 3
    i3;
	x3=0.46f; y3=0.85f; radius3 =0.05f;
	polygonAmount3 = 20;
	twicePi3 = 2.0f * PI;

	glBegin(GL_POLYGON);
	glColor3ub(250, 249, 245);
    glVertex2f(x3, y3);
    for(i3 = 0; i3 <= polygonAmount3;i3++) {
        glVertex2f(
                x3 + (radius3 * cos(i3 *  twicePi3 / polygonAmount3)),
            y3 + (radius3 * sin(i3 * twicePi3 / polygonAmount3))
        );
    }
	glEnd();

	///circle 4
    i4;
	x4=0.47f; y4=0.78f; radius4 =0.05f;
	polygonAmount4 = 20;
	twicePi4 = 2.0f * PI;

	glBegin(GL_POLYGON);
	glColor3ub(250, 249, 245);
    glVertex2f(x4, y4);
    for(i4 = 0; i4 <= polygonAmount4;i4++) {
        glVertex2f(
                x4 + (radius4 * cos(i4 *  twicePi4 / polygonAmount4)),
            y4 + (radius4 * sin(i4 * twicePi4 / polygonAmount4))
        );
    }
	glEnd();
	glPopMatrix();
	
	
	
	///rain
    if(rainStatus==true)
    {
        glLoadIdentity();
        glPushMatrix();
        glTranslatef(positionRain, positionRain, 0.0f);

        glTranslatef(0.0,-0.15,0.0);
        rain();

        glTranslatef(0.0,-0.15,0.0);
        rain();

        glTranslatef(0.0,-0.15,0.0);
        rain();

        glTranslatef(0.0,-0.15,0.0);
        rain();

        glTranslatef(0.0,-0.15,0.0);
        rain();

        glTranslatef(0.0,-0.15,0.0);
        rain();

        glTranslatef(0.0,-0.15,0.0);
        rain();

        glTranslatef(0.0,-0.15,0.0);
        rain();

        glTranslatef(0.0,-0.15,0.0);
        rain();

        glTranslatef(0.0,-0.15,0.0);
        rain();

        glTranslatef(0.0,-0.15,0.0);
        rain();

        glTranslatef(0.0,-0.15,0.0);
        rain();

        glTranslatef(0.0,-0.15,0.0);
        rain();

        glTranslatef(0.0,-0.15,0.0);
        rain();

        glTranslatef(0.0,-0.15,0.0);
        rain();

        glTranslatef(0.0,-0.15,0.0);
        rain();

        glTranslatef(0.0,-0.15,0.0);
        rain();

        glTranslatef(0.0,-0.15,0.0);
        rain();

        glTranslatef(0.0,-0.15,0.0);
        rain();

        glTranslatef(0.0,-0.15,0.0);
        rain();

        glTranslatef(0.0,-0.15,0.0);
        rain();

        glTranslatef(0.0,-0.15,0.0);
        rain();

        glTranslatef(0.0,-0.15,0.0);
        rain();

        glTranslatef(0.0,-0.15,0.0);
        rain();

        glTranslatef(0.0,-0.15,0.0);
        rain();
        glPopMatrix();
    }
}


void sceneautomaticupdate(int value)
{
    if(scenestatus==true)
    {
        sky1=38; sky2=154;sky3=214;
        sun1= 252; sun2=211; sun3= 3;
        daynightcounter--;
        if(daynightcounter==0)
        {
            scenestatus=false;
        }
    }
    if(scenestatus==false)
    {
        sky1=49; sky2=98; sky3=131;
        sun1= 255; sun2=255; sun3= 255;
        daynightcounter++;
        if(daynightcounter==2)
        {
            scenestatus=true;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(2000, sceneautomaticupdate, 0);
}



void shipmovingupdate(int value)
{
    bigshipposition+=0.0005;
    if(bigshipposition>=1.5)
    {
        bigshipposition=-1.4;
    }
    smallshipposition-=0.0003;
    if(smallshipposition<=-1.7)
    {
        smallshipposition=+0.8;
    }
    glutPostRedisplay();
    glutTimerFunc(1, shipmovingupdate, 0);
}

void updateCloud(int value)
{
    if(positionCloud1 < -1.5f)
    {
        positionCloud1 = 1.0f;
    }

    positionCloud1 -= speedCloud1;

    if(positionCloud2 < -1.5f)
    {
        positionCloud2 = 1.0f;
    }

    positionCloud2 -= speedCloud2;

    if(rainStatus==true)
    {
        if(positionRain < -0.02f )
        {
            positionRain = 0.02f;
        }

        positionRain += speedRain;
    }
    glutTimerFunc(100, updateCloud, 0);
}


void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
      case 'r':
      case 'R':
        if(rainStatus==true)
        {
            rainStatus=false;
        }
        else
        {
            rainStatus=true;
        }
         break;
   }
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(640, 420);
    glutCreateWindow("Game");
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutDisplayFunc(display);
    glutTimerFunc(timer, update, 0);
    glutTimerFunc(1, updateWheel, 0);
    glutTimerFunc(2000,sceneautomaticupdate, 0);
	glutTimerFunc(400, shipmovingupdate, 0);
	glutTimerFunc(100, updateCloud, 0);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;

}

