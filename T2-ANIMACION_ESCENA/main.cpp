#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define ENCENDIDO 1
#define APAGADO 0

using namespace std;

int contBajada = 0;

float angPerro = 0;
float angHumano = 0;
float angSer = 0;

int cont = 0;


// angulo de rotacion para la direccion de camara
float angle = 0.0f;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f, z=5.0f;
float moverNubes = 0;
// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

float trasladarPerro = 0;
float trasladarAuto = 0;

GLUquadricObj *tronco_Arbol = gluNewQuadric();

GLUquadricObj *puntero_pileta=gluNewQuadric();

GLUquadricObj *puntero_alacran=gluNewQuadric();

GLUquadricObj *p = gluNewQuadric();


float angulo_normal_pata1=50;

float moverCasca = 0;
float rotar = 310;
float moverCabeza = 0;
float moverCabeza2 = 0;
int y = 10;

float angulo_alacran=0;
float ejex=30;
float trasladar_ejex=100;
float ejez=0;
float trasladar_ejez=0;
float ejey=0;
float angulo_cola_alacran=320;
int estado_cola=0;
bool estado_colision=false;
int contador_colision_snake_alacran=0;

bool aux1 = false;
bool aux2 = false;
bool aux3 = false;


//HAROLD-HUMANO
float anguloHombro=0.0;
float anguloCodo=0.0;
float anguloMuneca=0.0;
float anguloCadera=45;
float anguloCadera2=-45;
float anguloRodilla=300;
float anguloTalon=0.0;
float angulo=180;
bool auxH= false;
bool auxC= false;
bool auxM= false;
bool auxCade= false;
bool auxCade2= false;
bool auxRodi= false;
bool auxTalon= false;

float posX_tronco=1;
float avan_X_tronco=1;
//FIN DE HAROLD -HUMANO

//INICIO PERRO
float moverCuerpo = 0;
float rotar_perro= 0;

float anguloPata_1=200;
float anguloPata_2=300;
bool auxP_1= false;
bool auxP_2= false;
//FIN DE PERRO


//CLARA
float angObjeto=0;
float rot=0,rot2=0;
float vX=20,vY=10,vZ=20;
bool limite=false;
float piR=90;
float trasX=0,trasY=0,trasZ=0;

float anguloCodo_Clara=0.0;//
float anguloCadera_Clara=45;
float anguloCadera_Clara2=-45;//
float anguloRodilla_Clara=300;//
bool auxC_Clara= false;//
bool auxCade_Clara= false;//
bool auxCade2_Clara= false;//
bool auxRodi_Clara= false;//

float pos_robot=0;
float ejex_Clara=30;//
float trasladar_ejex_Clara=100;//
float ejez_Clara=0;//
float trasladar_ejez_Clara=0;//
float ejey_Clara=0;//
//FIN DE CLARA

//ANTHONY
float trasladarObjeto = 40.0;
float trasladarObjetox = 205;
float trasladarz=0.0;
float anguloObjeto = 0;
float anguloAnillo = 90;
float anguloPata1=-70;
float anguloPata1_1=0;
float anguloPata1_2=0;
float anguloPata1_Tierra=0;
float anguloPata2=70;
float anguloPata2_1=0;
float anguloPata2_2=0;
float anguloPata2_Tierra=0;
float anguloLuz=180;
float anguloGiro=90;
float largoLuz=2;
float posLuz=0;
bool aux=false;
bool aux7=false;
bool aux8=false;
bool aux9=false;
bool aux4=false;
bool aux5=false;
bool aux6=false;
bool auxAbeja=false;
float abeja_x=0;
float abeja_y=5;
float abeja_z=100;
float angTronco = 0;
float angBrazo11 = 0;
float anguloCabeza=-30;
float anguloAntenaIzquierda=-40;
float anguloAntenaDerecha=-70;
float anguloFlageloIzquierdo=60;
float anguloFlageloDerecho=60;
float anguloCola=120;
float anguloAla=90;
float torax=120;
float an=0;
float rotarAbeja=50;
float anguloPataAbeja1=70;
float anguloPataAbeja1_2=20;
float anguloPataAbeja1_3=30;
float auxPata=false;
float auxPata1=false;
float auxPata2=false;
bool anguloAbeja=false;
bool angulo2=false;
bool angulo3=false;

float angulo_giro_abeja=180;
float posicion_x_abeja=0;
float posicion_y_abeja=30;
float posicion_z_abeja=0;

//FIN ANTHONY

//TELLO
float rueda = 0;
GLfloat spin=0.0;
//FIN TELLO
void inicializar(){

    glClearColor(0.643,0.835,0.894,0.0);
    glEnable(GL_DEPTH_TEST);
/*
    GLfloat light_pos[]={30,30,30};
    GLfloat light_color[]={1,0.2,1};
    GLfloat ambient_color[]={6,2};
    glLightfv(GL_LIGHT0,GL_POSITION,light_pos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
*/
}
void redimensionar(int w, int h) {
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
void coordenadas(){

    glBegin(GL_LINES);
        glColor3f (0.0, 1.0, 0.0); // Green for x axis
        glVertex3f(0,0,0);
        glVertex3f(120,0,0);
        glColor3f(1.0,0.0,0.0); // Red for y axis
        glVertex3f(0,0,0);
        glVertex3f(0,120,0);
        glColor3f(0.0,0.0,1.0); // Blue for z axis
        glVertex3f(0,0,0);
        glVertex3f(0,0,120);
    glEnd();

    // Dotted lines for the negative sides of x,y,z
    glEnable(GL_LINE_STIPPLE); 	// Enable line stipple to use a
    // dotted pattern for the lines
    glLineStipple(1, 0x0101); 	// Dotted stipple pattern for the lines
    glBegin(GL_LINES);

        glColor3f (0.0, 1.0, 0.0); 	// Green for x axis
        glVertex3f(-120,0,0);
        glVertex3f(0,0,0);

        glColor3f(1.0,0.0,0.0); 	// Red for y axis
        glVertex3f(0,0,0);
        glVertex3f(0,-120,0);

        glColor3f(0.0,0.0,1.0); 	// Blue for z axis
        glVertex3f(0,0,0);
        glVertex3f(0,0,-120);
    glEnd();
    glDisable(GL_LINE_STIPPLE); 	// Disable the line stipple
    glPopMatrix();
}
void suelo_parque(){
    //PISO
	glColor3f(0.690f, 0.768f, 0.427f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		//glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		//glColor3f(0.1f, 1.0f, 0.f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		//glColor3f(1.0f, 0.5f, 0.1f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();
	//FIN DE PISO
}
void prueba_cubo(){
    glColor3f(1.0f, 0.768f, 0.427f);
	glBegin(GL_QUADS);
        glVertex3f(-10,10,-10);
        glVertex3f(-10,-10,-10);
        glVertex3f(10,-10,-10);
        glVertex3f(10,10,-10);
	glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);

        glVertex3f(-10,10,-10);
        glVertex3f(10,10,-10);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(10,10,10);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-10,10,10);
    glEnd();

    glColor3f(0.0f, 0.5f, 1.0f);
    glBegin(GL_QUADS);

        glVertex3f(-10,10,10);
        glVertex3f(10,10,10);

        glVertex3f(10,-10,10);
        glVertex3f(-10,-10,10);
    glEnd();

     glColor3f(1.0f, 1.0f, 1.0f);
     glBegin(GL_QUADS);

        glVertex3f(-10,-10,-10);
        glVertex3f(-10,-10,10);
        glVertex3f(10,-10,10);
        glVertex3f(10,-10,-10);
    glEnd();
}
void arbol(){
     glPushMatrix();
        glColor3f(0.356,0.501,0.341);
        glTranslatef(0,4,0);
        glutSolidSphere(1,11,20);
     glPopMatrix();
     glPushMatrix();
        glColor3f(0.431,0.254,0.235);
        glTranslatef(0,4,0);
        glRotatef(90,1,0,0);
        gluCylinder(tronco_Arbol,0.1f,0.1f,4.0f,32,32);
     glPopMatrix();
}
void zona_de_paso(){
    glColor3f(0.69019,0.70980,0.72156);
    glBegin(GL_QUADS);
        glVertex3f(-100.0f,0.01f,-80.0f);
        glVertex3f(-80.0f,0.01f,-100.0f);

        glVertex3f(0.0f,0.01f,-20.0f);//*
        glVertex3f(-20.0f,0.01f,0.0f);//*
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(0.0f,0.01,20.0f);//*
        glVertex3f(20.0f,0.01,0.0f);//*

        glVertex3f(80.0f,0.01f,100.0f);
        glVertex3f(100.0f,0.01f,80.f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(100.0f,0.01f,-80.0f);
        glVertex3f(80.0f,0.01f,-100.0f);

        glVertex3f(0.0f,0.01,-20.0f);//*
        glVertex3f(20.0f,0.01,0.0f);//*
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(-100.0f,0.01f,80.0f);
        glVertex3f(-80.0f,0.01f,100.0f);

        glVertex3f(0.0f,0.01,20.0f);//*
        glVertex3f(-20.0f,0.01,0.0f);//*
    glEnd();
    //posicion central del parque
    glBegin(GL_QUADS);
        glVertex3f(-20.0f,0.01f,0.0f);
        glVertex3f(0.0f,0.01,-20.0f);

        glVertex3f(20.0f,0.01,0.0f);
        glVertex3f(0.0f,0.01,20.0f);

    glEnd();
}
void pileta_central(){
    glPushMatrix();
        glColor3f(0.69019,0.80980,0.72156);
        glTranslatef(0,3,0);
        glRotatef(90,1,0,0);
        gluCylinder(puntero_pileta,5.0f,5.0f,3.0f,32,32);
    glPopMatrix();
    glColor3f(0.8,0.5,1);
    //gluDisk(puntero_pileta,4,5,3,1);
}
void pista(){

    glBegin(GL_QUADS);
        glColor3f(0.0549f, 0.0666f, 0.0941f);
        glVertex3f(-130.0f,0.0f,-220.0f);
        glVertex3f(-100.0f,0.0f,-220.0f);

        glVertex3f(-100.0f,0.0f,220.0f);
        glVertex3f(-130.0f,0.0f,220.0f);
    glEnd();
    glBegin(GL_QUADS);
        glColor3f(0.0549f, 0.0666f, 0.0941f);
        glVertex3f(-220.0f,0.0f,-220.0f);
        glVertex3f(-200.0f,0.0f,-220.0f);

        glVertex3f(-200.0f,0.0f,220.0f);
        glVertex3f(-220.0f,0.0f,220.0f);
    glEnd();
    glBegin(GL_QUADS);
        glColor3f(0.0549f, 0.0666f, 0.0941f);
        glVertex3f(100.0f,0.0f,-220.0f);
        glVertex3f(130.0f,0.0f,-220.0f);

        glVertex3f(130.0f,0.0f,220.0f);
        glVertex3f(100.0f,0.0f,220.0f);
    glEnd();
    glBegin(GL_QUADS);
        glColor3f(0.0549f, 0.0666f, 0.0941f);
        glVertex3f(200.0f,0.0f,-220.0f);
        glVertex3f(220.0f,0.0f,-220.0f);

        glVertex3f(220.0f,0.0f,220.0f);
        glVertex3f(200.0f,0.0f,220.0f);
    glEnd();

    //**********************//

    glBegin(GL_QUADS);
        glColor3f(0.0549f, 0.0666f, 0.0941f);
        glVertex3f(-220.0f,0.0f,200.0f);
        glVertex3f(-220.0f,0.0f,220.0f);

        glVertex3f(220.0f,0.0f,220.0f);
        glVertex3f(220.0f,0.0f,200.0f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.0549f, 0.0666f, 0.0941f);
        glVertex3f(-220.0f,0.0f,100.0f);
        glVertex3f(-220.0f,0.0f,130.0f);

        glVertex3f(220.0f,0.0f,130.0f);
        glVertex3f(220.0f,0.0f,100.0f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.0549f, 0.0666f, 0.0941f);
        glVertex3f(-220.0f,0.0f,-130.0f);
        glVertex3f(-220.0f,0.0f,-100.0f);

        glVertex3f(220.0f,0.0f,-100.0f);
        glVertex3f(220.0f,0.0f,-130.0f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.0549f, 0.0666f, 0.0941f);
        glVertex3f(-220.0f,0.0f,-220.0f);
        glVertex3f(-220.0f,0.0f,-200.0f);

        glVertex3f(220.0f,0.0f,-200.0f);
        glVertex3f(220.0f,0.0f,-220.0f);
    glEnd();
}
void veredas(){
    //FONDO
    glBegin(GL_QUADS);
        glColor3f(0.69019,0.70980,0.72156);

        glVertex3f(-100.0f,0.0f,-130.0f);
        glVertex3f(100.0f,0.0f,-130.0f);

        glVertex3f(100.0f,0.0f,-200.0f);
        glVertex3f(-100.0f,0.0f,-200.0f);
    glEnd();
    //FRENTE
    glBegin(GL_QUADS);
        glColor3f(0.69019,0.70980,0.72156);

        glVertex3f(-100.0f,0.0f,130.0f);
        glVertex3f(100.0f,0.0f,130.0f);

        glVertex3f(100.0f,0.0f,200.0f);
        glVertex3f(-100.0f,0.0f,200.0f);
    glEnd();
    //DERECHA
    glBegin(GL_QUADS);
        glColor3f(0.69019,0.70980,0.72156);

        glVertex3f(-130.0f,0.0f,-100.0f);
        glVertex3f(-130.0f,0.0f,100.0f);

        glVertex3f(-200.0f,0.0f,100.0f);
        glVertex3f(-200.0f,0.0f,-100.0f);
    glEnd();

    //IZQUIERDA

    glBegin(GL_QUADS);
        glColor3f(0.69019,0.70980,0.72156);

        glVertex3f(130.0f,0.0f,-100.0f);
        glVertex3f(130.0f,0.0f,100.0f);

        glVertex3f(200.0f,0.0f,100.0f);
        glVertex3f(200.0f,0.0f,-100.0f);
    glEnd();

    //FONDO_DERECHA
    glBegin(GL_QUADS);
        glColor3f(0.69019,0.70980,0.72156);

        glVertex3f(-130.0f,0.0f,-130.0f);
        glVertex3f(-130.0f,0.0f,-200.0f);

        glVertex3f(-200.0f,0.0f,-200.0f);
        glVertex3f(-200.0f,0.0f,-130.0f);
    glEnd();

    //FONDO_IZQUIERDA
    glBegin(GL_QUADS);
        glColor3f(0.69019,0.70980,0.72156);

        glVertex3f(130.0f,0.0f,-130.0f);
        glVertex3f(200.0f,0.0f,-130.0f);

        glVertex3f(200.0f,0.0f,-200.0f);
        glVertex3f(130.0f,0.0f,-200.0f);
    glEnd();
    //FRENTE_DERECHA
    glBegin(GL_QUADS);
        glColor3f(0.69019,0.70980,0.72156);

        glVertex3f(-200.0f,0.0f,130.0f);
        glVertex3f(-130.0f,0.0f,130.0f);

        glVertex3f(-130.0f,0.0f,200.0f);
        glVertex3f(-200.0f,0.0f,200.0f);
    glEnd();
    //FRENTE_IZQUIERDA
    glBegin(GL_QUADS);
        glColor3f(0.69019,0.70980,0.72156);

        glVertex3f(130.0f,0.0f,130.0f);
        glVertex3f(200.0f,0.0f,130.0f);

        glVertex3f(200.0f,0.0f,200.0f);
        glVertex3f(130.0f,0.0f,200.0f);
    glEnd();
}
void piso_de_casa(){
    //FONDO
    glBegin(GL_QUADS);
        glColor3f(1,0,0);

        glVertex3f(-80.0f,0.1f,-150.0f);
        glVertex3f(80.0f,0.1f,-150.0f);

        glVertex3f(80.0f,0.1f,-180.0f);
        glVertex3f(-80.0f,0.1f,-180.0f);
    glEnd();
    //FRENTE
    glBegin(GL_QUADS);
        glColor3f(0,1,0);

        glVertex3f(-80.0f,0.1f,150.0f);
        glVertex3f(80.0f,0.1f,150.0f);

        glVertex3f(80.0f,0.1f,180.0f);
        glVertex3f(-80.0f,0.1f,180.0f);
    glEnd();
    //DERECHA
    glBegin(GL_QUADS);
        glColor3f(0,0,1);

        glVertex3f(-150.0f,0.1f,-80.0f);
        glVertex3f(-150.0f,0.1f,80.0f);

        glVertex3f(-180.0f,0.1f,80.0f);
        glVertex3f(-180.0f,0.1f,-80.0f);
    glEnd();

    //IZQUIERDA

    glBegin(GL_QUADS);
        glColor3f(1,0,1);

        glVertex3f(150.0f,0.1f,-80.0f);
        glVertex3f(150.0f,0.1f,80.0f);

        glVertex3f(180.0f,0.1f,80.0f);
        glVertex3f(180.0f,0.1f,-80.0f);
    glEnd();
}
void casa(){
    //FONDO
    glBegin(GL_QUADS);
        glColor3f(0.7490f, 0.6862f, 0.6235f);

        glVertex3f(-80.0f,0.0f,-150.0f);
        glVertex3f(80.0f,0.0f,-150.0f);

        glVertex3f(80.0f,40.0f,-150.0f);
        glVertex3f(-80.0f,40.0f,-150.0f);
    glEnd();
    glBegin(GL_QUADS);
        glColor3f(0.7490f, 0.6862f, 0.6235f);

        glVertex3f(80.0f,0.0f,-150.0f);
        glVertex3f(80.0f,40.0f,-150.0f);

        glVertex3f(80.0f,40.0f,-180.0f);
        glVertex3f(80.0f,0.0f,-180.0f);
    glEnd();
    glBegin(GL_QUADS);
        glColor3f(0.7490f, 0.6862f, 0.6235f);

        glVertex3f(80.0f,40.0f,-180.0f);
        glVertex3f(80.0f,0.0f,-180.0f);

        glVertex3f(-80.0f,0.0f,-180.0f);
        glVertex3f(-80.0f,40.0f,-180.0f);
    glEnd();
    glBegin(GL_QUADS);
        glColor3f(0.7490f, 0.6862f, 0.6235f);

        glVertex3f(-80.0f,0.0f,-180.0f);
        glVertex3f(-80.0f,40.0f,-180.0f);

        glVertex3f(-80.0f,40.0f,-150.0f);
        glVertex3f(-80.0f,0.0f,-150.0f);
    glEnd();

    //FIN DE FONDO

    //FRENTE
    glBegin(GL_QUADS);
        glColor3f(0,0.5647,0.7254);

        glVertex3f(-80.0f,0.0f,150.0f);
        glVertex3f(-80.0f,40.0f,150.0f);

        glVertex3f(80.0f,40.0f,150.0f);
        glVertex3f(80.0f,0.0f,150.0f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0,0.5647,0.7254);

        glVertex3f(-80.0f,0.0f,150.0f);
        glVertex3f(-80.0f,40.0f,150.0f);

        glVertex3f(-80.0f,40.0f,180.0f);
        glVertex3f(-80.0f,0.0f,180.0f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0,0.5647,0.7254);

        glVertex3f(-80.0f,0.0f,180.0f);
        glVertex3f(-80.0f,40.0f,180.0f);

        glVertex3f(80.0f,40.0f,180.0f);
        glVertex3f(80.0f,0.0f,180.0f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0,0.5647,0.7254);

        glVertex3f(80.0f,0.0f,180.0f);
        glVertex3f(80.0f,40.0f,180.0f);

        glVertex3f(80.0f,40.0f,150.0f);
        glVertex3f(80.0f,0.0f,150.0f);
    glEnd();

    //FIN DE FRENTE


    //DERECHA

    glBegin(GL_QUADS);
        glColor3f(0.4392,0.2509,0.2431);

        glVertex3f(-150.0f,0.0f,-80.0f);
        glVertex3f(-150.0f,0.0f,80.0f);

        glVertex3f(-150.0f,40.0f,80.0f);
        glVertex3f(-150.0f,40.0f,-80.0f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.4392,0.2509,0.2431);

        glVertex3f(-150.0f,0.0f,-80.0f);
        glVertex3f(-150.0f,40.0f,-80.0f);

        glVertex3f(-180.0f,40.0f,-80.0f);
        glVertex3f(-180.0f,0.0f,-80.0f);

    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.4392,0.2509,0.2431);

        glVertex3f(-180.0f,0.0f,-80.0f);
        glVertex3f(-180.0f,40.0f,-80.0f);

        glVertex3f(-180.0f,40.0f,80.0f);
        glVertex3f(-180.0f,0.0f,80.0f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.4392,0.2509,0.2431);

        glVertex3f(-180.0f,40.0f,80.0f);
        glVertex3f(-180.0f,0.0f,80.0f);

        glVertex3f(-150.0f,0.0f,80.0f);
        glVertex3f(-150.0f,40.0f,80.0f);
    glEnd();
    //FIN DE DERECHA

    //IZQUIERDA

    glBegin(GL_QUADS);
        glColor3f(0.6823,0.5254,0.5568);

        glVertex3f(150.0f,0.0f,-80.0f);
        glVertex3f(150.0f,0.0f,80.0f);

        glVertex3f(150.0f,40.0f,80.0f);
        glVertex3f(150.0f,40.0f,-80.0f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.6823,0.5254,0.5568);

        glVertex3f(150.0f,0.0f,80.0f);
        glVertex3f(150.0f,40.0f,80.0f);

        glVertex3f(180.0f,40.0f,80.0f);
        glVertex3f(180.0f,0.0f,80.0f);

    glEnd();
    glBegin(GL_QUADS);
        glColor3f(0.6823,0.5254,0.5568);

        glVertex3f(180.0f,0.0f,80.0f);
        glVertex3f(180.0f,40.0f,80.0f);

        glVertex3f(180.0f,40.0f,-80.0f);
        glVertex3f(180.0f,0.0f,-80.0f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.6823,0.5254,0.5568);

        glVertex3f(180.0f,40.0f,-80.0f);
        glVertex3f(180.0f,0.0f,-80.0f);

        glVertex3f(150.0f,0.0f,-80.0f);
        glVertex3f(150.0f,40.0f,-80.0f);

    glEnd();

    //DIAGONALES
    glBegin(GL_QUADS);
        glColor3f(0,1,1);

        glVertex3f(-180.0f,0.0f,-180.0f);
        glVertex3f(-180.0f,40.0f,-180.0f);

        glVertex3f(-180.0f,40.0f,-150.0f);
        glVertex3f(-180.0f,0.0f,-150.0f);
        //------------------------------
        glVertex3f(-180.0f,40.0f,-150.0f);
        glVertex3f(-180.0f,0.0f,-150.0f);

        glVertex3f(-150.0f,0.0f,-150.0f);
        glVertex3f(-150.0f,40.0f,-150.0f);
        //-------------------------------
        glVertex3f(-150.0f,0.0f,-150.0f);
        glVertex3f(-150.0f,40.0f,-150.0f);

        glVertex3f(-150.0f,40.0f,-180.0f);
        glVertex3f(-150.0f,0.0f,-180.0f);
        //-------------------------------
        glVertex3f(-150.0f,40.0f,-180.0f);
        glVertex3f(-150.0f,0.0f,-180.0f);

        glVertex3f(-180.0f,0.0f,-180.0f);
        glVertex3f(-180.0f,40.0f,-180.0f);
    glEnd();
}
void computePos(float deltaMove) {
	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}
void computeDir(float deltaAngle) {
	angle += deltaAngle;
	lx = sin(angle);
	lz = -cos(angle);
}
void caminar_rey_escorpion(int i){
   if(y==0){
    if(trasladar_ejex<=100  && angulo_alacran==0 &&(trasladar_ejez<=100 && trasladar_ejez>=-100)){
        trasladar_ejex--;
        ejex=30;ejey=0;ejez=0;
        if(trasladar_ejex==-100){
        trasladar_ejex++;
        angulo_alacran=180;
        ejex=0;ejey=30;ejez=0;
        }
    }
    if(angulo_alacran==180 && trasladar_ejex>=-100 &&(trasladar_ejez<=100 && trasladar_ejez>=-100)){
        trasladar_ejex++;
        ejex=0;ejey=30;ejez=0;
        if(trasladar_ejex==100){
            angulo_alacran=0;
            ejex=30;ejey=0;ejez=0;
        }

    }

    if(angulo_alacran==90 && trasladar_ejez>=-100 &&(trasladar_ejex<=100 && trasladar_ejex>=-100)){
        trasladar_ejez++;
        ejex=0;ejey=30;ejez=0;
        if(trasladar_ejez==100){
            angulo_alacran=270;
            ejex=0;ejey=30;ejez=0;
        }
    }
    if(angulo_alacran==270 && trasladar_ejez<=100 && (trasladar_ejex<=100 && trasladar_ejex>=-100)){
        trasladar_ejez--;
        ejex=0;ejey=30;ejez=0;
        if(trasladar_ejez==-100){
            angulo_alacran=90;
            ejex=0;ejey=30;ejez=0;
        }
    }
   }
   //cout<<"POSICION X  "<<trasladar_ejex<<" POSICION Y "<<trasladar_ejez<< endl;
    glutTimerFunc(100,caminar_rey_escorpion,2);
    glutPostRedisplay();
}
void rey_escorpion(){
    glTranslatef(0,1.8,0);
    glPushMatrix();//INICIO DE CUERPO
        glColor3f(0,0,0);
        glPushMatrix();
            glRotatef(90,0,5,0);
            glColor3f(0.5,0.5,0.5);
            gluCylinder(puntero_alacran,1,0.8,4,32,32);
            //glColor3f(1,1,1);
            glColor3f(0.6392,0.5529,0.4627);
            glutSolidSphere(1,10,20);
            glTranslatef(0,0,4);
            //glColor3f(0.6392,0.5529,0.4627);
            //glColor3f(1,0,1);
            glutSolidSphere(1,10,20);

            glColor3f(0.6392,0.5529,0.4627);
            glRotatef(angulo_cola_alacran,1,0,0);
            glPushMatrix();
                glTranslatef(0,1,1);
                //glColor3f(0.7,0.7,0);
                glScaled(0.5,0.5,0.5);
                glutSolidDodecahedron();

                glTranslatef(0,2,1);
                //glColor3f(0.7,0.7,0);
                glScaled(1,1,1);
                glutSolidDodecahedron();

                glTranslatef(0,2.5,1);
                //glColor3f(0.7,0.7,0);
                glScaled(1,1,1);
                glutSolidDodecahedron();

                glTranslatef(0,2.7,-0.5);
                //glColor3f(0.8,0.7,0.5);
                glScaled(1,1,1);
                glutSolidDodecahedron();

                glRotatef(180,0,1,0);
                glTranslatef(0,0,1);
                glColor3f(0,1,0);
                glutSolidCone(1,3,4,4);
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();//INICIO DE PATAS DERECHAS
            glPushMatrix();//inicio de pata1-1
                //glColor3f(1,0,0);
                glColor3f(0.6392,0.5529,0.4627);
                gluCylinder(puntero_alacran,0.1f,0.1f,2.0f,32,32);
                glColor3f(0,0,0);
                glTranslatef(0,0,2);
                glutSolidSphere(0.1,10,20);
                glPushMatrix();//inicion de pata1-2
                    //glColor3f(0,1,0);
                    glColor3f(0.6392,0.5529,0.4627);
                    glRotatef(angulo_normal_pata1,5,0,0);
                    gluCylinder(puntero_alacran,0.1f,0.1f,1,32,32);
                    glColor3f(0,0,0);
                    glTranslatef(0,0,1);
                    glutSolidSphere(0.1,10,20);
                    glPushMatrix();//inicio de pata1-3
                        //glColor3f(0,0,1);
                        glColor3f(0.6392,0.5529,0.4627);
                        glRotatef(45,10,0,0);
                        gluCylinder(puntero_alacran,0.1f,0.1f,1,32,32);
                        glColor3f(0,0,0);
                        glTranslatef(0,0,1);
                        glutSolidSphere(0.1,10,20);
                        glPushMatrix();//inicio de pata1-4
                            glColor3f(1,0,0);
                            glRotatef(90,-3,0,0);
                            gluCylinder(puntero_alacran,0.1f,0.03f,1,32,32);
                        glPopMatrix();//fin de pata1-4
                    glPopMatrix();//fin de pata1-3
                glPopMatrix();//fin de pata1-2
        glPopMatrix();//fin de pata1-1

        glPushMatrix();//inicio de pata2-1
            //glColor3f(1,1,0);
            glColor3f(0.6392,0.5529,0.4627);
            glTranslatef(1,0,0);
            gluCylinder(puntero_alacran,0.1f,0.1f,2.0f,32,32);
            glColor3f(0,0,0);
            glTranslatef(0,0,2);
            glutSolidSphere(0.1,10,20);
            glPushMatrix();//inicio de pata2-2
                //glColor3f(0,0,1);
                glColor3f(0.6392,0.5529,0.4627);
                glRotatef(angulo_normal_pata1,5,0,0);
                gluCylinder(puntero_alacran,0.1f,0.1f,1,32,32);
                glTranslatef(0,0,1);
                glColor3f(0,0,0);
                glutSolidSphere(0.1,10,20);
                glPushMatrix();//inicio de pata2-3
                    //glColor3f(0,1,0);
                    glColor3f(0.6392,0.5529,0.4627);
                    glRotatef(45,10,0,0);
                    gluCylinder(puntero_alacran,0.1f,0.1f,1,32,32);
                    glColor3f(0,0,0);
                    glTranslatef(0,0,1);
                    glutSolidSphere(0.1,10,20);
                    glPushMatrix();//inicio de pata2-4
                        glColor3f(1,0,0);
                        glRotatef(90,-3,0,0);
                        gluCylinder(puntero_alacran,0.1f,0.03f,1,32,32);
                    glPopMatrix();//fin de pata2-4
                glPopMatrix();//fin de pata2-3
            glPopMatrix();//fin de pata2-2
        glPopMatrix();//fin de pata2-2

        glPushMatrix();//inicio pata3-1
            //glColor3f(1,1,0);
            glColor3f(0.6392,0.5529,0.4627);
            glTranslatef(2,0,0);
            gluCylinder(puntero_alacran,0.1f,0.1f,2.0f,32,32);
            glColor3f(0,0,0);
            glTranslatef(0,0,2);
            glutSolidSphere(0.1,10,20);
            glPushMatrix();//inicio pata3-2
                //glColor3f(0,0,1);
                glColor3f(0.6392,0.5529,0.4627);
                glRotatef(angulo_normal_pata1,5,0,0);
                gluCylinder(puntero_alacran,0.1f,0.1f,1,32,32);
                glTranslatef(0,0,1);
                glColor3f(0,0,0);
                glutSolidSphere(0.1,10,20);
                glPushMatrix();//inicio pata3-3
                    //glColor3f(0,1,0);
                    glColor3f(0.6392,0.5529,0.4627);
                    glRotatef(45,10,0,0);
                    gluCylinder(puntero_alacran,0.1f,0.1f,1,32,32);
                    glColor3f(0,0,0);
                    glTranslatef(0,0,1);
                    glutSolidSphere(0.1,10,20);
                    glPushMatrix();//inicio pata3-4
                        glColor3f(1,0,0);
                        glRotatef(90,-3,0,0);
                        gluCylinder(puntero_alacran,0.1f,0.03f,1,32,32);
                    glPopMatrix();//fin de pata3-4
                glPopMatrix();//fin de pata3-3
            glPopMatrix();//fin pata3-2
        glPopMatrix();//fin de pata3-1
        glPopMatrix();//FIN DE PATAS DERECHAS

        glPopMatrix();//INICIO DE PATAS IZQUIERDAS
            glPushMatrix();//INICIO DE PATA1-1
                //glColor3f(1,0,1);
                glColor3f(0.6392,0.5529,0.4627);
                glTranslatef(0,0,-2);
                gluCylinder(puntero_alacran,0.1f,0.1f,2.0f,32,32);
                glColor3f(0,0,0);
                glutSolidSphere(0.1,10,20);
                glPushMatrix();//INICIO DE PATA1-2
                    //glColor3f(0,0,1);
                    glColor3f(0.6392,0.5529,0.4627);
                    glRotatef(angulo_normal_pata1,-5,0,0);
                    glTranslatef(0,0,-1);
                    gluCylinder(puntero_alacran,0.1f,0.1f,1,32,32);
                    glColor3f(0,0,0);
                    glutSolidSphere(0.1,10,20);
                    glPushMatrix();//INICIO DE PATA1-3
                        //glColor3f(0,1,0);
                        glColor3f(0.6392,0.5529,0.4627);
                        glRotatef(225,-5,0,0);
                        gluCylinder(puntero_alacran,0.1f,0.1f,1,32,32);
                        glColor3f(0,0,0);
                        glTranslatef(0,0,1);
                        glutSolidSphere(0.1,10,20);
                        glPushMatrix();//INICIO DE PATA1-4
                            /*glColor3f(1,0,1);
                            glRotatef(90,-1,0,0);
                            gluCylinder(puntero_alacran,0.1f,0.03f,1,32,32);*/
                            glColor3f(1,0,0);
                            glRotatef(90,5,0,0);
                            gluCylinder(puntero_alacran,0.1f,0.03f,1,32,32);
                        glPopMatrix();//FIN DE PATA1-4
                    glPopMatrix();//FIN DE PATA1-3
                glPopMatrix();//FIN DE PATA1-2
            glPopMatrix();//FIN DE PATA1-1

                glPushMatrix();//INICIO DE PATA2-1
                    //glColor3f(1,0,1);
                    glColor3f(0.6392,0.5529,0.4627);
                    glTranslatef(1,0,-2);
                    gluCylinder(puntero_alacran,0.1f,0.1f,2.0f,32,32);
                    glColor3f(0,0,0);
                    glutSolidSphere(0.1,10,20);
                    glPushMatrix();//INICIO DE PATA2-2
                        //glColor3f(0,0,1);
                        glColor3f(0.6392,0.5529,0.4627);
                        glRotatef(angulo_normal_pata1,-5,0,0);
                        glTranslatef(0,0,-1);
                        gluCylinder(puntero_alacran,0.1f,0.1f,1,32,32);
                        glColor3f(0,0,0);
                        glutSolidSphere(0.1,10,20);
                        glPushMatrix();//INICIO DE PATA2-3
                            //glColor3f(0,1,0);
                            glColor3f(0.6392,0.5529,0.4627);
                            glRotatef(225,-5,0,0);
                            gluCylinder(puntero_alacran,0.1f,0.1f,1,32,32);
                            glColor3f(0,0,0);
                            glTranslatef(0,0,1);
                            glutSolidSphere(0.1,10,20);
                            glPushMatrix();//INICIO DE PATA2-4
                                glColor3f(1,0,0);
                                glRotatef(90,5,0,0);
                                gluCylinder(puntero_alacran,0.1f,0.03f,1,32,32);
                            glPopMatrix();//FIN DE PATA2-4
                        glPopMatrix();//FIN DE PATA2-3
                    glPopMatrix();//FIN DE PATA2-2
                glPopMatrix();//FIN DE PATA2-1

                glPushMatrix();//INICIO DE PATA3-1
                    //glColor3f(1,0,1);
                    glColor3f(0.6392,0.5529,0.4627);
                    glTranslatef(2,0,-2);
                    gluCylinder(puntero_alacran,0.1f,0.1f,2.0f,32,32);
                    glColor3f(0,0,0);
                    glutSolidSphere(0.1,10,20);
                    glPushMatrix();//INICIO DE PATA3-2
                        //glColor3f(0,0,1);
                        glColor3f(0.6392,0.5529,0.4627);
                        glRotatef(angulo_normal_pata1,-5,0,0);
                        glTranslatef(0,0,-1);
                        gluCylinder(puntero_alacran,0.1f,0.1f,1,32,32);
                        glColor3f(0,0,0);
                        glutSolidSphere(0.1,10,20);
                        glPushMatrix();//INICIO DE PATA3-3
                            //glColor3f(0,1,0);
                            glColor3f(0.6392,0.5529,0.4627);
                            glRotatef(225,-5,0,0);
                            gluCylinder(puntero_alacran,0.1f,0.1f,1,32,32);
                            glColor3f(0,0,0);
                            glTranslatef(0,0,1);
                            glutSolidSphere(0.1,10,20);
                            glPushMatrix();//INICIO DE PATA3-4
                                glColor3f(1,0,0);
                                glRotatef(90,5,0,0);
                                gluCylinder(puntero_alacran,0.1f,0.03f,1,32,32);
                            glPopMatrix();//FIN DE PATA3-4
                        glPopMatrix();//FIN DE PATA3-3
                    glPopMatrix();//FIN DE PATA3-2
                glPopMatrix();//FIN DE PATA3-1
        glPushMatrix();//FIN DE PATAS IZQUIERDAS

    glPopMatrix();//FIN DE CUERPO
}
void serpiente(){
    glRotatef(-90,0,1,0);
  //glRotatef(-160,1,0,0);
//--------------------------------------------------------------

  //PUNTO CENTRAL
  glPushMatrix();
      glRotatef(angSer,0,0,1);
      glColor3f(1,1,0);
      glTranslatef(0,1.5,-10);
      glutSolidSphere(1.5,8,8);
//--------------------------------------------------------------

      //2. CUELLO 1
      glPushMatrix();
        glColor3f(0,0,0);
        glRotatef(-90,1,0,0);
        glRotatef(moverCabeza,1,0,0);
        gluCylinder(p,1.5,1.5,7,8,8);

        //3. CONEXIÓN CUELLO/CABEZA
        glPushMatrix();
          glColor3f(0,0,0);
          glTranslatef(0,0,6.8);
          glutSolidSphere(1.5,8,8);


          //4. CABEZA 1
          glPushMatrix();
            glColor3f(0,0,0);
            glRotatef(-90,1,0,0);
            glRotatef(moverCabeza2,1,0,0);
            gluCylinder(p,1.5,1.5,7,8,8);

            //5. "NARIZ"
            glPushMatrix();
              glColor3f(0,0,0);
              glTranslatef(0,0,7);
              glutSolidSphere(1.5,8,8);

              //OJO1
              glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(1.5,0,-2);
                glutSolidSphere(0.5,8,8);
                glPopMatrix();

              //OJO2
              glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(-1.5,0,-2);
                glutSolidSphere(0.5,8,8);
                glPopMatrix();

            glPopMatrix();
         glPopMatrix();
        glPopMatrix();
      glPopMatrix();


//--------------------------------------------------------------

      //CONEXIÓN AYUDA
      glPushMatrix();
      glColor3f(1,1,0);
      glRotatef(moverCabeza,0,1,0);
      glutSolidSphere(1.5,8,8);

        //6. CUERPO 1
        glPushMatrix();
          glColor3f(0,0,0);
          glTranslatef(0,0,7);
          glRotatef(-180,1,0,0);
          gluCylinder(p,1.5,1.5,7,8,8);

          //7. CONEXIÓN CUERPO1/CUERPO2
          glPushMatrix();
            glColor3f(0,0,0);
            glRotatef(moverCabeza,0,1,0);
            glutSolidSphere(1.5,8,8);

            //8. CUERPO 2
            glPushMatrix();
              glColor3f(0,0,0);
              glRotatef(-180,1,0,0);
              gluCylinder(p,1.5,1.5,7,8,8);

              //9. CONEXIÓN CUERPO2/CUERPO3
              glPushMatrix();
                glColor3f(0,0,0);
                glTranslatef(0,0,7);
                glRotatef(moverCabeza2,0,1,0);
                glutSolidSphere(1.5,8,8);

                //10. CUERPO 3
                glPushMatrix();
                  glColor3f(0,0,0);
                  glTranslatef(0,0,7);
                  glRotatef(-180,0,0,0);
                  gluCylinder(p,1.5,1.5,7,8,8);

                  //11. CONEXIÓN CUERPO3/COLA
                  glPushMatrix();
                    glColor3f(0,0,0);
                    glutSolidSphere(1.5,8,8);

                    //12. COLA
                    glPushMatrix();
                      glColor3f(1,1,1);
                      glRotatef(-150,-7,-1,0);
                      glRotatef(moverCasca,0,1,0);
                      gluCylinder(p,1.5,1.5,1,8,8);

                      //4.1 Anillo 1
                      glPushMatrix();
                        glColor3f(1,1,1);
                        glTranslatef(0,0,1);
                        glRotatef(10,-7,-1,0);
                        gluCylinder(p,1.4,1.4,1,8,8);

                        //4.2 Anillo 2
                        glPushMatrix();
                          glColor3f(1,1,1);
                          glTranslatef(0,0,1);
                          glRotatef(10,-7,-1,0);
                          gluCylinder(p,1.3,1.3,1,8,8);

                          //4.3 Anillo 3
                          glPushMatrix();
                            glColor3f(1,1,1);
                            glTranslatef(0,0,1);
                            glRotatef(10,-7,-1,0);
                            gluCylinder(p,1.2,1.2,1,8,8);

                            //4.4 Anillo 4
                            glPushMatrix();
                              glColor3f(1,1,1);
                              glTranslatef(0,0,1);
                              glRotatef(10,-7,-1,0);
                              gluCylinder(p,1.1,1.1,1,8,8);

                              //4.5 Anillo 5
                              glPushMatrix();
                                glColor3f(1,1,1);
                                glTranslatef(0,0,1);
                                glRotatef(10,-7,-1,0);
                                gluCylinder(p,1,1,1,8,8);

                                //4.6 Anillo 6
                                glPushMatrix();
                                  glColor3f(1,1,1);
                                  glTranslatef(0,0,1);
                                  glutSolidSphere(1,8,8);

                                  //4.7 Bolita
                                  glPushMatrix();
                                    glColor3f(1,1,1);
                                    glTranslatef(0,0,1);
                                    glutSolidSphere(0.5,8,8);

                                  glPopMatrix();
                                glPopMatrix();
                              glPopMatrix();
                            glPopMatrix();
                          glPopMatrix();
                        glPopMatrix();
                      glPopMatrix();
                    glPopMatrix();
                  glPopMatrix();
                glPopMatrix();
              glPopMatrix();
            glPopMatrix();
          glPopMatrix();
        glPopMatrix();
      glPopMatrix();

//--------------------------------------------------------------
     glPopMatrix();
}
//INICIO DE MOVIMIENTO HAROLD
void moverTronco(int i){

    if (angHumano==-180){
        posX_tronco=posX_tronco-1;
    }
    glutTimerFunc(100,moverTronco,15);
    glutPostRedisplay();
}
void moverHombro(int i){
    if(anguloHombro==180 || auxH){
        anguloHombro-=10;
        auxH=true;
        if(anguloHombro==-40)
            auxH=false;
    }else if(!auxH)
        anguloHombro+=10;

    glutPostRedisplay();
    glutTimerFunc(200,moverHombro,8);
}
void moverCodo(int i){
    if(anguloCodo==160 || auxC){
        anguloCodo-=10;
        auxC=true;
        if(anguloCodo==0)
            auxC=false;
    }else if(!auxC)
        anguloCodo+=10;

    glutPostRedisplay();
    glutTimerFunc(70,moverCodo,9);
}
void moverMuneca(int i){
    if(anguloMuneca==90 || auxM){
        anguloMuneca-=10;
        auxM=true;
        if(anguloMuneca==-90)
            auxM=false;
    }else if(!auxM)
        anguloMuneca+=10;

    glutPostRedisplay();
    glutTimerFunc(333,moverMuneca,10);
}
void moverCadera(int i){
    if(anguloCadera==45 || auxCade){
        anguloCadera-=10;
        auxCade=true;
        if(anguloCadera==-45)
            auxCade=false;
    }else if(!auxCade)
        anguloCadera+=10;

    glutPostRedisplay();
    glutTimerFunc(120,moverCadera,11);
}
void moverCadera2(int i){
    if(anguloCadera2==-45 || auxCade2){
        anguloCadera2+=10;
        auxCade2=true;
        if(anguloCadera2==45)
            auxCade2=false;
    }else if(!auxCade2)
        anguloCadera2-=10;

    glutPostRedisplay();
    glutTimerFunc(120,moverCadera2,12);
}
void moverRodilla(int i){
    if(anguloRodilla==290 || auxRodi){
        anguloRodilla+=10;
        auxRodi=true;
        if(anguloRodilla==360)
            auxRodi=false;
    }else if(!auxRodi)
        anguloRodilla-=10;

    glutPostRedisplay();
    glutTimerFunc(150,moverRodilla,13);
}
void moverTalon(int i){
    if(anguloTalon==-90 || auxTalon){
        anguloTalon+=10;
        auxTalon=true;
        if(anguloTalon==10)
            auxTalon=false;
    }else if(!auxTalon)
        anguloTalon-=10;

    glutPostRedisplay();
    glutTimerFunc(200,moverTalon,14);
}
//FIN FUNCIONES DE MOVIMIENTO - HAROLD
void humano_harold(){

    glPushMatrix();//TRONCO
        glColor3f(0.4,0.54,0.8);
        glTranslated(posX_tronco,0,0);
        glRotatef(angHumano,0,1,0);
        glRotatef(90,2,0,0);
        gluCylinder(p, 2.0, 2.0, 6, 16, 16);

        //CUELLO
        glPushMatrix();
            glColor3f(0.9,0.75,0.68);
            glTranslated(0,0,-1);
            gluCylinder(p, 1.0, 1.0, 1, 16, 16);
                //CABEZA
                glPushMatrix();
                    glColor3f(0.9,0.75,0.68);
                    glTranslated(0,0,-1);
                    glutSolidSphere(2,10,10);
                        //OJO derecho
                        glPushMatrix();
                            glColor3f(0,0,0);
                            glTranslated(1.5,1.2,-1);
                            glutSolidSphere(0.5,10,10);
                        glPopMatrix();
                        //OJO Izquierda
                        glPushMatrix();
                            glColor3f(0,0,0);
                            glTranslated(1.5,-1.2,-1);
                            glutSolidSphere(0.5,10,10);
                        glPopMatrix();
                glPopMatrix();
        glPopMatrix();
//-----------------------------------------------
            glPushMatrix();//HOMBRO1
            glColor3f(0.4,0.54,0.8);
            glTranslated(0,2.1,1);
            glRotatef(anguloHombro,0,1,1);
            glutSolidSphere(1,10,10);

                glPushMatrix();//BICEP
                glColor3f(0.4,0.54,0.8);
                gluCylinder(p, 1.0, 1.0, 3.5, 16, 16);

                    glPushMatrix();//CODO
                    glColor3f(0.4,0.54,0.8);
                    glTranslated(0,0,4);
                    glRotatef(anguloCodo,0,1,0);
                    glutSolidSphere(1,10,10);

                        glPushMatrix();//ANTEBRAZO
                        glColor3f(0.4,0.54,0.8);
                        gluCylinder(p, 1.0, 0.7, 3.5, 16, 16);

                            glPushMatrix();//MUÑECA
                            glColor3f(0.4,0.54,0.8);
                            glTranslated(0,0,3.6);
                            glRotatef(anguloMuneca,0,1,0);
                            glutSolidSphere(0.7,10,10);

                                glPushMatrix();//MANO
                                    glColor3f(0.9,0.75,0.68);
                                    gluCylinder(p, 0.6, 0.8, 1, 32, 32);

                                    glPushMatrix();//NUDILLO 1
                                        glColor3f(0.9,0.75,0.68);
                                        glTranslated(-0.5,0.8,1);
                                        glRotatef(anguloCodo,0,1,0);
                                        glutSolidSphere(0.3,10,10);

                                            glPushMatrix();//DEDO1
                                                glColor3f(0.9,0.75,0.68);
                                                gluCylinder(p, 0.2, 0.2, 1, 16, 16);
                                            glPopMatrix();
                                    glPopMatrix();

                                    glPushMatrix();//NUDILLO 2
                                        glColor3f(0.9,0.75,0.68);
                                        glTranslated(0.4,0.9,1);
                                        glRotatef(anguloCodo,0,1,0);
                                        glutSolidSphere(0.3,10,10);

                                            glPushMatrix();//DEDO1
                                                glColor3f(0.9,0.75,0.68);
                                                gluCylinder(p, 0.2, 0.2, 1, 16, 16);
                                            glPopMatrix();

                                    glPopMatrix();

                                    glPushMatrix();//NUDILLO 3
                                        glColor3f(0.9,0.75,0.68);
                                        glTranslated(0.8,0.3,1);
                                        glRotatef(anguloCodo,0,1,0);
                                        glutSolidSphere(0.3,10,10);

                                            glPushMatrix();//DEDO1
                                                glColor3f(0.9,0.75,0.68);
                                                gluCylinder(p, 0.2, 0.2, 1, 16, 16);
                                            glPopMatrix();
                                    glPopMatrix();

                                    glPushMatrix();//NUDILLO 4
                                        glColor3f(0.9,0.75,0.68);
                                        glTranslated(0.8,-0.5,1);
                                        glRotatef(anguloCodo,0,1,0);
                                        glutSolidSphere(0.3,10,10);

                                            glPushMatrix();//DEDO1
                                                glColor3f(0.9,0.75,0.68);
                                                gluCylinder(p, 0.2, 0.2, 1, 16, 16);
                                            glPopMatrix();
                                    glPopMatrix();
                                glPopMatrix();
                            glPopMatrix();
                        glPopMatrix();
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
            //--------------------------------------
            //HOMBRO 2
            glPushMatrix();
                glColor3f(0.4,0.54,0.8);
                glTranslated(0,-2.8,1);
                glRotatef(anguloHombro,0,1,0);
                glutSolidSphere(1,10,10);
                    //BISECP
                    glPushMatrix();
                        glColor3f(0.4,0.54,0.8);
                        gluCylinder(p, 1.0, 1.0, 3.5, 16, 16);
                            //CODO
                            glPushMatrix();
                                glColor3f(0.4,0.54,0.8);
                                glTranslated(0,0,4);
                                glRotatef(anguloCodo,0,1,0);
                                glutSolidSphere(1,10,10);
                                    //ANTEBRAZO
                                    glPushMatrix();
                                        glColor3f(0.4,0.54,0.8);
                                        gluCylinder(p, 1.0, 0.7, 3.5, 16, 16);
                                            //MUÑECA
                                            glPushMatrix();
                                                glColor3f(0.4,0.54,0.8);
                                                glTranslated(0,0,3.6);
                                                glRotatef(anguloMuneca,0,1,0);
                                                glutSolidSphere(0.7,10,10);
                                                    //MANO
                                                    glPushMatrix();
                                                        glColor3f(0.9,0.75,0.68);
                                                        gluCylinder(p, 0.6, 0.8, 1, 32, 32);
                                                            //NUDILLO 1
                                                            glPushMatrix();
                                                                glColor3f(0.9,0.75,0.68);
                                                                glTranslated(-0.5,0.8,1);
                                                                glRotatef(anguloCodo,0,1,0);
                                                                glutSolidSphere(0.3,10,10);
                                                                    //DEDO1
                                                                    glPushMatrix();
                                                                        glColor3f(0.9,0.75,0.68);
                                                                        gluCylinder(p, 0.2, 0.2, 1, 16, 16);
                                                                    glPopMatrix();
                                                            glPopMatrix();
                                                            //NUDILLO 2
                                                            glPushMatrix();
                                                                glColor3f(0.9,0.75,0.68);
                                                                glTranslated(0.4,0.9,1);
                                                                glRotatef(anguloCodo,0,1,0);
                                                                glutSolidSphere(0.3,10,10);
                                                                    //DEDO1
                                                                    glPushMatrix();
                                                                        glColor3f(0.9,0.75,0.68);
                                                                        gluCylinder(p, 0.2, 0.2, 1, 16, 16);
                                                                    glPopMatrix();
                                                            glPopMatrix();

                                                            //NUDILLO 3
                                                            glPushMatrix();
                                                                glColor3f(0.9,0.75,0.68);
                                                                glTranslated(0.8,0.3,1);
                                                                glRotatef(anguloCodo,0,1,0);
                                                                glutSolidSphere(0.3,10,10);
                                                                    //DEDO1
                                                                    glPushMatrix();
                                                                        glColor3f(0.9,0.75,0.68);
                                                                        gluCylinder(p, 0.2, 0.2, 1, 16, 16);
                                                                    glPopMatrix();
                                                            glPopMatrix();

                                                            //NUDILLO 4
                                                            glPushMatrix();
                                                                glColor3f(0.9,0.75,0.68);
                                                                glTranslated(0.8,-0.5,1);
                                                                glRotatef(anguloCodo,0,1,0);
                                                                glutSolidSphere(0.3,10,10);
                                                                //DEDO1
                                                                glPushMatrix();//DEDO1
                                                                    glColor3f(0.9,0.75,0.68);
                                                                    gluCylinder(p, 0.2, 0.19, 0.8, 16, 16);
                                                                glPopMatrix();
                                                            glPopMatrix();
                                                    glPopMatrix();
                                            glPopMatrix();
                                    glPopMatrix();
                            glPopMatrix();
                    glPopMatrix();
            glPopMatrix();
            //--------------------PIERNA DERECHA-------------------------------------------
            //CADERA
            glPushMatrix();
                glColor3f(0.9,0.819,0.529);
                glTranslated(0,2.1,6);
                glRotatef(anguloCadera,0,1,0);
                glutSolidSphere(1,10,10);
                    //MUSLO
                    glPushMatrix();
                        glColor3f(0.9,0.819,0.529);
                        gluCylinder(p, 1.0, 1.0, 3.5, 16, 16);
                            //RODILLA
                            glPushMatrix();
                                glColor3f(0.9,0.819,0.529);
                                glTranslated(0,0,4);
                                glRotatef(anguloRodilla,0,1,0);
                                glutSolidSphere(1,10,10);
                                    //PANTORRILLA
                                    glPushMatrix();
                                        glColor3f(0.9,0.819,0.529);
                                        gluCylinder(p, 1.0, 0.7, 3.5, 16, 16);
                                            //TALON
                                            glPushMatrix();
                                                glColor3f(0,0,0);
                                                glTranslated(0,0,3.6);
                                                glRotatef(anguloTalon,0,1,0);
                                                glutSolidSphere(0.7,10,10);
                                                    //PIE
                                                    glPushMatrix();
                                                        glColor3f(0,0,0);
                                                        glRotatef(90,0,1,0);
                                                        gluCylinder(p, 0.7, 0.7, 2.8, 16, 16);
                                                    glPopMatrix();
                                            glPopMatrix();
                                    glPopMatrix();
                            glPopMatrix();
                    glPopMatrix();
            glPopMatrix();

            //---------------------------PIERNA IZQUIERDA------------
            //CADERA
            glPushMatrix();
                glColor3f(0.9,0.819,0.529);
                glTranslated(0,-1.9,6);
                glRotatef(anguloCadera2,0,1,0);
                glutSolidSphere(1,10,10);
                    //MUSLO
                    glPushMatrix();
                        glColor3f(0.9,0.819,0.529);
                        gluCylinder(p, 1.0, 1.0, 3.5, 16, 16);
                            //RODILLA
                            glPushMatrix();
                                glColor3f(0.9,0.819,0.529);
                                glTranslated(0,0,4);
                                glRotatef(anguloRodilla,0,1,0);
                                glutSolidSphere(1,10,10);
                                    //PANTORRILLA
                                    glPushMatrix();
                                        glColor3f(0.9,0.819,0.529);
                                        gluCylinder(p, 1.0, 0.7, 3.5,16,16);
                                            //TALON
                                            glPushMatrix();
                                                glColor3f(0,0,0);
                                                glTranslated(0,0,3.6);
                                                glRotatef(anguloTalon,0,1,0);
                                                glutSolidSphere(0.7,10,10);
                                                    //PIE
                                                    glPushMatrix();
                                                        glColor3f(0,0,0);
                                                        glRotatef(90,0,1,0);
                                                        gluCylinder(p, 0.7, 0.7, 2.8, 16, 16);
                                                    glPopMatrix();
                                            glPopMatrix();
                                    glPopMatrix();
                            glPopMatrix();
                    glPopMatrix();
            glPopMatrix();
    glPopMatrix();
}

//INICIO DE PERRO

void moverPata_1(int i){
    if(anguloPata_1==200 || auxP_1){
        anguloPata_1+=10;
        auxP_1=true;
        if(anguloPata_1==300)
            auxP_1=false;
    }else if(!auxP_1)
        anguloPata_1-=10;

    glutPostRedisplay();
    glutTimerFunc(120,moverPata_1,23);
}
void moverPata_2(int i){
    if(anguloPata_2==300 || auxP_2){
        anguloPata_2-=10;
        auxP_2=true;
        if(anguloPata_2==200)
            auxP_2=false;
    }else if(!auxP_2)
        anguloPata_2+=10;

    glutPostRedisplay();
    glutTimerFunc(120,moverPata_2,24);
}

float anguloRodilla_P1=0;
float anguloRodilla_P2=80;
bool auxP_R_1= false;
bool auxP_R_2= false;

void moverRodilla_Pierna1(int i){
    if(anguloRodilla_P1==80 || auxP_R_1){
        anguloRodilla_P1-=10;
        auxP_R_1=true;
        if(anguloRodilla_P1==0)
            auxP_R_1=false;
    }else if(!auxP_R_1)
        anguloRodilla_P1+=10;

    glutPostRedisplay();
    glutTimerFunc(150,moverRodilla_Pierna1,25);
}

void moverRodilla_Pierna2(int i){
    if(anguloRodilla_P2==80 || auxP_R_2){
        anguloRodilla_P2-=10;
        auxP_R_2=true;
        if(anguloRodilla_P2==0)
            auxP_R_2=false;
    }else if(!auxP_R_2)
        anguloRodilla_P2+=10;

    glutPostRedisplay();
    glutTimerFunc(150,moverRodilla_Pierna2,26);
}

float anguloPata_3=290;
bool auxP_3= false;

void moverPierna3(int i){
    if(anguloPata_3==320|| auxP_3){
        anguloPata_3-=10;
        auxP_3=true;
        if(anguloPata_3==250)
            auxP_3=false;
    }else if(!auxP_3)
        anguloPata_3+=10;

    glutPostRedisplay();
    glutTimerFunc(155,moverPierna3,27);
}

float anguloPata_4=290;
bool auxP_4= false;

void moverPierna4(int i){
    if(anguloPata_4==250 || auxP_4){
        anguloPata_4+=10;
        auxP_4=true;
        if(anguloPata_4==320)
            auxP_4=false;
    }else if(!auxP_4)
        anguloPata_4-=10;
    glutPostRedisplay();
    glutTimerFunc(155,moverPierna4,28);
}

float anguloRodilla_P3=340;
bool auxP_R_3= false;
void moverRodilla_Pierna3(int i){
    if(anguloRodilla_P3==340|| auxP_R_3){
        anguloRodilla_P3+=10;
        auxP_R_3=true;
        if(anguloRodilla_P3==360)
            auxP_R_3=false;
    }else if(!auxP_R_3)
        anguloRodilla_P3-=10;

    glutPostRedisplay();
    glutTimerFunc(200,moverRodilla_Pierna3,29);
}

float anguloRodilla_P4=340;
bool auxP_R_4= false;
void moverRodilla_Pierna4(int i){
    if(anguloRodilla_P4==340|| auxP_R_4){
        anguloRodilla_P4+=10;
        auxP_R_4=true;
        if(anguloRodilla_P4==360)
            auxP_R_4=false;
    }else if(!auxP_R_4)
        anguloRodilla_P4-=10;

    glutPostRedisplay();
    glutTimerFunc(200,moverRodilla_Pierna4,30);
}

float anguloCuello_1=90;
bool auxCuello_1= false;
void moverCuello1_1(int i){
    if(anguloCuello_1==90|| auxCuello_1){
        anguloCuello_1+=10;
        auxCuello_1=true;
        if(anguloCuello_1==100)
            auxCuello_1=false;
    }else if(!auxCuello_1)
        anguloCuello_1-=10;

    glutPostRedisplay();
    glutTimerFunc(200,moverCuello1_1,31);
}

void perro(){


    glPushMatrix();//TRONCO
        glColor3f(0.9,0.71,0.494);
        //glTranslated(posX_tronco,0,0);
        glRotatef(angPerro,0,1,0);
        gluCylinder(p, 1.7, 2.0, 6, 16, 16);
        //-------------------------------------------------------------
            //CUELLO
           {
               glPushMatrix();
                glColor3f(0.9,0.71,0.494);
                glTranslated(0,2,5);
                glRotatef(-120,1,1,1);
                glutSolidSphere(1,10,10);
                    //CUELLO_1
                    glPushMatrix();
                        glColor3f(0.9,0.71,0.494);
                        gluCylinder(p, 1, 0.9, 2, 16, 16);
                            //CUELLO_3
                            glPushMatrix();
                                glColor3f(0.9,0.71,0.494);
                                glTranslated(0,0,2);
                                glRotatef(anguloCuello_1,1,1,1);
                                glutSolidSphere(1,10,10);
                                    //CABEZA
                                    glPushMatrix();
                                        glColor3f(0.9,0.71,0.494);
                                        gluCylinder(p, 1, 0.7, 2, 16, 16);
                                            //HOCICO
                                            glPushMatrix();
                                                glColor3f(0.9,0.71,0.494);
                                                glTranslated(0,0,2);
                                                glutSolidCone(0.7,1,16,16);
                                            glPopMatrix();
                                            //OJO_1
                                            glPushMatrix();
                                                glColor3f(0,0,0);
                                                glTranslated(-0.5,0.7,1);
                                                glutSolidSphere(0.2,10,10);
                                            glPopMatrix();
                                            //OJO_2
                                            glPushMatrix();
                                                glColor3f(0,0,0);
                                                glTranslated(0.5,0.7,1);
                                                glutSolidSphere(0.2,10,10);

                                            glPopMatrix();
                                            //OREJA_1
                                            glPushMatrix();
                                                glColor3f(0.9,0.71,0.494);
                                                glTranslated(0.7,0.8,0);
                                                glutSolidSphere(0.2,10,10);
                                                    glPushMatrix();
                                                        glColor3f(0.9,0.71,0.494);
                                                        glTranslated(0,0,-2);
                                                        gluCylinder(p, 0.5, 0.2, 2, 16, 16);
                                                    glPopMatrix();
                                            glPopMatrix();
                                            //OREJA_2
                                            glPushMatrix();
                                                glColor3f(0.9,0.71,0.494);
                                                glTranslated(-0.7,0.8,0);
                                                glutSolidSphere(0.2,10,10);
                                                    glPushMatrix();
                                                        glColor3f(0.9,0.71,0.494);
                                                        glTranslated(0,0,-2);
                                                        gluCylinder(p, 0.5, 0.2, 2, 16, 16);
                                                    glPopMatrix();
                                            glPopMatrix();
                                    glPopMatrix();
                            glPopMatrix();
                    glPopMatrix();
            glPopMatrix();
           }
    //------------------------------------------------------------------
            //PIERNA 1
           {
               glPushMatrix();
                glColor3f(0.9,0.71,0.494);
                glTranslated(1,-2,5);
                glRotatef(anguloPata_1,2,0,0);
                glutSolidSphere(0.7,10,10);
                    //muslo1
                    glPushMatrix();
                        glColor3f(0.9,0.71,0.494);
                        glTranslated(0,0,-2);
                        gluCylinder(p, 0.5, 0.7, 2, 16, 16);
                            //rodilla
                            glPushMatrix();
                                glColor3f(0.9,0.71,0.494);
                                glTranslated(0,0,0);
                                glRotatef(anguloRodilla_P1,2,0,0);
                                glutSolidSphere(0.5,10,10);
                                    //pierna1.2
                                    glPushMatrix();
                                        glColor3f(0.9,0.71,0.494);
                                        glTranslated(0,0,-2.1);
                                        gluCylinder(p, 0.3, 0.5, 2, 16, 16);
                                            //talon
                                            glPushMatrix();
                                                glColor3f(0.9,0.71,0.494);
                                                glTranslated(0,0,-0.2);
                                                glRotatef(270,2,0,0);
                                                glutSolidSphere(0.3,10,10);
                                                    //pie
                                                    glPushMatrix();
                                                        glColor3f(0.9,0.71,0.494);
                                                        glTranslated(0,0,-1);
                                                        //glRotatef(90,2,0,0);
                                                        gluCylinder(p, 0.5, 0.3, 1, 16, 16);
                                                    glPopMatrix();
                                            glPopMatrix();
                                    glPopMatrix();
                            glPopMatrix();
                    glPopMatrix();
            glPopMatrix();
           }


            {//PIERNA 2
                glPushMatrix();
                glColor3f(0.9,0.71,0.494);
                glTranslated(-1,-2,5);
                glRotatef(anguloPata_2,2,0,0);
                glutSolidSphere(0.7,10,10);
                    //pierna2.1
                    glPushMatrix();
                        glColor3f(0.9,0.71,0.494);
                        glTranslated(0,0,-2);
                        gluCylinder(p, 0.5, 0.7, 2, 16, 16);
                            //rodilla
                            glPushMatrix();
                                glColor3f(0.9,0.71,0.494);
                                glTranslated(0,0,0);
                                glRotatef(anguloRodilla_P2,2,0,0);
                                glutSolidSphere(0.5,10,10);
                                    //pierna2.2
                                    glPushMatrix();
                                        glColor3f(0.9,0.71,0.494);
                                        glTranslated(0,0,-2.1);
                                        gluCylinder(p, 0.3, 0.5, 2, 16, 16);
                                            //talon
                                            glPushMatrix();
                                                glColor3f(0.9,0.71,0.494);
                                                glTranslated(0,0,-0.2);
                                                glRotatef(270,2,0,0);
                                                glutSolidSphere(0.3,10,10);
                                                    //pie
                                                    glPushMatrix();
                                                        glColor3f(0.9,0.71,0.494);
                                                        glTranslated(0,0,-1);
                                                        //glRotatef(90,2,0,0);
                                                        gluCylinder(p, 0.5, 0.3, 1, 16, 16);
                                                    glPopMatrix();
                                            glPopMatrix();
                                    glPopMatrix();
                            glPopMatrix();
                    glPopMatrix();
            glPopMatrix();
            }


            {//PIERNA 3
                glPushMatrix();
                glColor3f(0.9,0.71,0.494);
                glTranslated(1,-2,1);
                glRotatef(anguloPata_3,2,0,0);
                glutSolidSphere(0.7,10,10);
                    //pierna3.1
                    glPushMatrix();
                        glColor3f(0.9,0.71,0.494);
                        glTranslated(0,0,-2);
                        gluCylinder(p, 0.5, 0.7, 2, 16, 16);
                            //rodilla
                            glPushMatrix();
                                glColor3f(0.9,0.71,0.494);
                                glTranslated(0,0,0);
                                glRotatef(anguloRodilla_P3,2,0,0);
                                glutSolidSphere(0.5,10,10);
                                    //pierna2.2
                                    glPushMatrix();
                                        glColor3f(0.9,0.71,0.494);
                                        glTranslated(0,0,-2.1);
                                        gluCylinder(p, 0.3, 0.5, 2, 16, 16);
                                            //talon
                                            glPushMatrix();
                                                glColor3f(0.9,0.71,0.494);
                                                glTranslated(0,0,-0.2);
                                                glRotatef(270,2,0,0);
                                                glutSolidSphere(0.3,10,10);
                                                    //pie
                                                    glPushMatrix();
                                                        glColor3f(0.9,0.71,0.494);
                                                        glTranslated(0,0,-1);
                                                        //glRotatef(90,2,0,0);
                                                        gluCylinder(p, 0.5, 0.3, 1, 16, 16);
                                                    glPopMatrix();
                                            glPopMatrix();
                                    glPopMatrix();
                            glPopMatrix();
                    glPopMatrix();
            glPopMatrix();
            }


            {//PIERNA 4
                glPushMatrix();
                glColor3f(0.9,0.71,0.494);
                glTranslated(-1,-2,1);
                glRotatef(anguloPata_4,2,0,0);
                glutSolidSphere(0.7,10,10);
                    //pierna4.1
                    glPushMatrix();
                        glColor3f(0.9,0.71,0.494);
                        glTranslated(0,0,-2);
                        gluCylinder(p, 0.5, 0.7, 2, 16, 16);
                            //rodilla
                            glPushMatrix();
                                glColor3f(0.9,0.71,0.494);
                                glTranslated(0,0,0);
                                glRotatef(anguloRodilla_P4,2,0,0);
                                glutSolidSphere(0.5,10,10);
                                    //pierna2.2
                                    glPushMatrix();
                                        glColor3f(0.9,0.71,0.494);
                                        glTranslated(0,0,-2.1);
                                        gluCylinder(p, 0.3, 0.5, 2, 16, 16);
                                            //talon
                                            glPushMatrix();
                                                glColor3f(0.9,0.71,0.494);
                                                glTranslated(0,0,-0.2);
                                                glRotatef(270,2,0,0);
                                                glutSolidSphere(0.3,10,10);
                                                    //pie
                                                    glPushMatrix();
                                                        glColor3f(0.9,0.71,0.494);
                                                        glTranslated(0,0,-1);
                                                        //glRotatef(90,2,0,0);
                                                        gluCylinder(p, 0.5, 0.3, 1, 16, 16);
                                                    glPopMatrix();
                                            glPopMatrix();
                                    glPopMatrix();
                            glPopMatrix();
                    glPopMatrix();
            glPopMatrix();
            }



            {//COLA
                glPushMatrix();
                glColor3f(0.9,0.71,0.494);
                glTranslated(0,2,0);
                glRotatef(anguloCuello_1,2,0,0);
                glutSolidSphere(0.5,10,10);
                    //cola1
                    glPushMatrix();
                        glColor3f(0.9,0.71,0.494);
                        //glTranslated(0,0,0);
                        //glRotatef(,2,0,0);
                        gluCylinder(p, 0.5, 0.3, 2, 16, 16);
                            //cola1.2
                            glPushMatrix();
                                glColor3f(0.9,0.71,0.494);
                                glTranslated(0,0,2.2);
                                glRotatef(anguloCuello_1,2,0,0);
                                glutSolidSphere(0.3,10,10);
                                    //cola1.2
                                    glPushMatrix();
                                        glColor3f(0.9,0.71,0.494);
                                        //glTranslated(0,0,0);
                                        //glRotatef(,2,0,0);
                                        gluCylinder(p, 0.3, 0.1, 2, 16, 16);
                                    glPopMatrix();
                            glPopMatrix();
                    glPopMatrix();
            glPopMatrix();
    glPopMatrix();
            }
}

//FIN DE PERRO

//INICIO DE MOVIMIENTO CLARA
void tronco(){
	glColor3f(0,1,1);
	glutSolidSphere (2,15,30);
}
void abdomen(){
	glColor3f(147.0/255.0,149.0/255.0,1);
	glutSolidTorus(0.3,2,15,30);
}
void cadera(){
	glColor3f(147.0/255.0,149.0/255.0,1);
	glutSolidSphere (0.95,15,30);
}
void pierna(){
	glColor3f(0,1,1);
	gluCylinder(p,0.5,0.5,2.5,16,16);
}
void arosPierna(){
	glColor3f(124.0/255.0,128.0/255.0,129.0/255.0);
	glutSolidTorus(0.1,0.6,15,30);
}
void rodilla(){
	glColor3f(147.0/255.0,149.0/255.0,1);
	glutSolidSphere (0.8,15,30);
}
void talon(){
	glColor3f(147.0/255.0,149.0/255.0,1);
	glutSolidSphere (0.7,15,30);
}
void cuello(){
	glColor3f(124.0/255.0,128.0/255.0,129.0/255.0);
	gluCylinder(p,0.3,0.3,1,16,16);
}
void cara(){
    glColor3f(0,1,1);
	gluCylinder(p,1.5,1.5,1.5,16,16);
}
void hombro(){
	glColor3f(147.0/255.0,149.0/255.0,1);
	glutSolidSphere (0.8,15,30);
}
void antebrazo(){
	glColor3f(0,1,1);
	gluCylinder(p,0.4,0.4,3,16,16);
}
void brazo(){
	glColor3f(0,1,1);
	gluCylinder(p,0.4,0.3,4.7,16,16);
}
void caminar(int i){

    if(trasladar_ejex_Clara<=100  && pos_robot==0 &&(trasladar_ejez_Clara<=100 && trasladar_ejez_Clara>=-100)){
        trasladar_ejex_Clara--;
        ejex_Clara=30;ejey_Clara=0;ejez_Clara=0;
        if(trasladar_ejex_Clara==-100){
        trasladar_ejex_Clara++;
        pos_robot=180;
        ejex_Clara=0;ejey_Clara=30;ejez_Clara=0;
        }
    }

    if(pos_robot==180 && trasladar_ejex_Clara>=-100 &&(trasladar_ejez_Clara<=100 && trasladar_ejez_Clara>=-100)){
        trasladar_ejex_Clara++;
        ejex_Clara=0;ejey_Clara=30;ejez_Clara=0;
        if(trasladar_ejex_Clara==100){
            pos_robot=0;
            ejex_Clara=30;ejey_Clara=0;ejez_Clara=0;
        }

    }

    if(pos_robot==90 && trasladar_ejez_Clara>=-100 &&(trasladar_ejex_Clara<=100 && trasladar_ejex_Clara>=-100)){
        trasladar_ejez_Clara++;
        ejex_Clara=0;ejey_Clara=30;ejez_Clara=0;
        if(trasladar_ejez_Clara==100){
            pos_robot=270;
            ejex_Clara=0;ejey_Clara=30;ejez_Clara=0;
        }


    }
    if(pos_robot==270 && trasladar_ejez_Clara<=100 && (trasladar_ejex_Clara<=100 && trasladar_ejex_Clara>=-100)){
        trasladar_ejez_Clara--;
        ejex_Clara=0;ejey_Clara=30;ejez_Clara=0;
        if(trasladar_ejez_Clara==-100){
            pos_robot=90;
            ejex_Clara=0;ejey_Clara=30;ejez_Clara=0;
        }

    }
    glutTimerFunc(100,caminar,16);
    glutPostRedisplay();
}

void robot_karateka(){
    glTranslatef(trasladar_ejex_Clara,0,trasladar_ejez_Clara);
    glRotatef(pos_robot,ejex_Clara,ejey_Clara,ejez_Clara);

    //tronco
    glPushMatrix();

        glTranslatef(trasX+0.8,trasY+10,trasZ+0);
        tronco();

        //hombroDer
        glPushMatrix();
            glTranslatef(0,0.8,2);
            hombro();

                //Brazo
                glPushMatrix();
                    glTranslatef(0,0,0.3);
                    glRotatef(45,1,0,0);
                    antebrazo();
                glPopMatrix();

                    //codo
                    glPushMatrix();
                        glTranslatef(0,-2,2.4);
                        glRotatef(anguloCodo,-1,0,-1);
                        rodilla();
                    //glPopMatrix();

                        //Antebrazo
                        glPushMatrix();
                            glTranslatef(0,0,0);
                            glRotatef(45,1,0,0);
                            brazo();

                            //mano
                            glPushMatrix();
                                glTranslatef(0,0,5);
                                //glRotatef(135,1,0,0);
                                //glScalef(0.8,1,0.5);
                                glutSolidCube(1);

                                //Objeto
                                glPushMatrix();
                                    glColor3f(1,1,1);
                                    glTranslatef(0,0,0.5);

                                    gluCylinder(p,0.2,0.2,3,16,16);

                                    //O1
                                    glPushMatrix();
                                        glTranslatef(0,0,3);
                                        glRotated(angObjeto,-1,-1,-1);
                                        glutSolidSphere(0.5,15,30);

                                        //O2
                                        glPushMatrix();
                                            glTranslatef(0,0,0.5);
                                            gluCylinder(p,0.2,0.2,3,16,16);
                                        glPopMatrix();
                                    glPopMatrix();
                                glPopMatrix();
                            glPopMatrix();
                        glPopMatrix();
                    glPopMatrix();
				glPopMatrix();

        //hombroIzq
        glPushMatrix();
            glTranslatef(0,0.8,-2);
            hombro();

            //Brazo
            glPushMatrix();
                glTranslatef(0,0,0);
                glRotatef(135,1,0,0);
                antebrazo();
            glPopMatrix();

                //codo
                glPushMatrix();
                    glTranslatef(0,-2,-2.3);
                    rodilla();
                glPopMatrix();

                    //Antebrazo
                    glPushMatrix();
                        glTranslatef(0,-2,-2.5);
                        glRotatef(60,1,0,0);
                        brazo();
                    glPopMatrix();

                        //mano
                        glPushMatrix();
                            glTranslatef(0,-6.3,0.2);
                            //glRotatef(135,1,0,0);
                            glScalef(0.8,1,-1.3);
                            glutSolidCube(1);
                        glPopMatrix();
            glPopMatrix();
        glPopMatrix();

        //abdomen1
        glPushMatrix();
			glTranslatef(trasX+0.8,trasY+8.5,trasZ+0);
			glRotatef(90,1,0,0);
			abdomen();
        glPopMatrix();

        //abdomen2
        glPushMatrix();
			glTranslatef(trasX+0.8,trasY+5.5,trasZ+0);
			glRotatef(90,1,0,0);
			abdomen();
        glPopMatrix();

        //AbdomenRelleno
        for(float i=-8.3;i<=-5.7;i=i+0.25){
            glPushMatrix();
                glRotatef(90,1,0,0);
                glTranslatef(trasX+0.8,trasZ+0,-trasY+i);
                glColor3f(99.0/255.0,99.0/255.0,99.0/255.0);
                glutSolidTorus(0.07,1.8,15,30);
            glPopMatrix();
        }

        //apendice
        glPushMatrix();
			glTranslatef(trasX+0.8,trasY+4.5,trasZ+0);
			glColor3f(0,1,1);
			glutSolidSphere (2,15,30);
        glPopMatrix();

        //caderaDer
        glPushMatrix();
			glTranslatef(trasX+0.8,trasY+3,trasZ+1.05);
			glRotatef(anguloCadera,0,0,1);
			cadera();

			//piernaDer1
			glPushMatrix();
                glRotatef(90,1,0,0);
                glTranslatef(0,0,0);
                pierna();

				//arosPierna
				for(float i=0;i<=2.5;i=i+0.4){
					glPushMatrix();
                        glTranslatef(0,0,i);
                        arosPierna();
					glPopMatrix();
				}

				//rodillaDer
				glPushMatrix();
                    glTranslatef(0,0,3);
                    glRotatef(anguloRodilla,0,0,1);
                    rodilla();

                    //piernaDer2
					glPushMatrix();
                        pierna();

                        //TalonDer
						glPushMatrix();
							glRotatef(0,1,0,0);
							glTranslatef(0,0,3);
							talon();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
        glPopMatrix();

        //caderaIzq
        glPushMatrix();
			glTranslatef(trasX+0.8,trasY+3,trasZ-1.05);
			glRotatef(anguloCadera2,0,0,1);
			cadera();

			//piernaIzq1
            glPushMatrix();
				glRotatef(90,1,0,0);
				glTranslatef(0,0,0);
				pierna();

                //arosPierna
                for(float i=0;i<=2.5;i=i+0.4){
                    glPushMatrix();
                    glTranslatef(0,0,i);
                    arosPierna();
                    glPopMatrix();
                }

                //rodillaIzq
                glPushMatrix();
					glTranslatef(0,0,3);
					glRotatef(anguloRodilla,0,0,1);
					rodilla();

					//piernaIzq2
                    glPushMatrix();
						//glRotatef(0,1,0,0);
						//glTranslatef(0,0,0);
						pierna();

						//TalonIzq
						glPushMatrix();
							glRotatef(0,1,0,0);
							glTranslatef(0,0,3);
							talon();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
        glPopMatrix();

    //cara
    glPushMatrix();
        glRotatef(270,1,0,0);
        glTranslatef(trasX+0.8,-trasZ+0,trasY+12.5);
        cara();

        //cuello
        glPushMatrix();
            //glRotatef(0,1,0,0);
            glTranslatef(0,0,-0.8);
            cuello();
        glPopMatrix();

        glPushMatrix();
			glTranslatef(0,0,1.5);
			glColor3f(0,1,1);
			gluCylinder(p,1.5,1.3,0.4,16,16);

			//lentes
			glPushMatrix();
                glTranslatef(0,0,0);
                glColor3f(1,0,0);
                gluCylinder(p,1.3,1.3,0.9,16,16);

                //frente
                glPushMatrix();
                    glTranslatef(0,0,0.9);
                    glColor3f(0,1,1);
                    gluCylinder(p,1.3,1.3,0.4,16,16);
                glPopMatrix();

                //cabecera
                glPushMatrix();
                    glTranslatef(-0.1,0,0);
                    glColor3f(0,1,1);
                    glutSolidSphere (1.3,16,16);
                glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();

}

//NUBES

void nubes(){
    glPushMatrix();  /// NUBE

      glColor4f(0,1,1,1);
      glutSolidSphere(2,8,8);

      glPushMatrix();
        glColor4f(0,1,1,1);
        glTranslatef(0,0,-2);
        glutSolidSphere(2,8,8);
      glPopMatrix();

      glPushMatrix();
        glColor4f(0,1,1,1);
        glTranslatef(0,-2,2);
        glutSolidSphere(2,8,8);
      glPopMatrix();

      glPushMatrix();
        glColor4f(0,1,1,1);
        glTranslatef(0,-2,-1);
        glutSolidSphere(2,8,8);
      glPopMatrix();

      glPushMatrix();
        glColor4f(0,1,1,1);
        glTranslatef(0,-2,-4);
        glutSolidSphere(2,8,8);
      glPopMatrix();

glPopMatrix();
}

void rotarT1(int i){
    piR = piR + 5;
    if (piR==125){
        piR = piR - 5;
    }
    else{
        piR=piR-5;
    }
    glutPostRedisplay();
    glutTimerFunc(50,rotarT1,17);
}
void moverCodo_Clara(int i){
    if(anguloCodo_Clara==160 || auxC_Clara){
        anguloCodo_Clara-=10;
        auxC_Clara=true;
        if(anguloCodo_Clara==0)
            auxC_Clara=false;
    }else if(!auxC_Clara)
        anguloCodo_Clara+=10;

    glutPostRedisplay();
    glutTimerFunc(70,moverCodo_Clara,18);
}
void moverCadera_Clara(int i){
    if(anguloCadera_Clara==45 || auxCade_Clara){
        anguloCadera_Clara-=10;
        auxCade_Clara=true;
        if(anguloCadera_Clara==-45)
            auxCade_Clara=false;
    }else if(!auxCade_Clara)
        anguloCadera_Clara+=10;

    glutPostRedisplay();
    glutTimerFunc(120,moverCadera_Clara,19);
}
void moverCadera2_Clara(int i){
    if(anguloCadera_Clara2==-45 || auxCade2_Clara){
        anguloCadera_Clara2+=10;
        auxCade2_Clara=true;
        if(anguloCadera_Clara2==45)
            auxCade2_Clara=false;
    }else if(!auxCade2_Clara)
        anguloCadera_Clara2-=10;

    glutPostRedisplay();
    glutTimerFunc(120,moverCadera2_Clara,20);
}
void moverRodilla_Clara(int i){
    if(anguloRodilla_Clara==290 || auxRodi_Clara){
        anguloRodilla_Clara+=10;
        auxRodi_Clara=true;
        if(anguloRodilla_Clara==360)
            auxRodi_Clara=false;
    }else if(!auxRodi_Clara)
        anguloRodilla_Clara-=10;

    glutPostRedisplay();
    glutTimerFunc(150,moverRodilla_Clara,21);
}
void moverObjeto(int i){
    if(angObjeto==160 || auxC_Clara){
        angObjeto-=10;
        auxC_Clara=true;
        if(angObjeto==0)
            auxC_Clara=false;
    }else if(!auxC_Clara)
        angObjeto+=10;

    glutPostRedisplay();
    glutTimerFunc(70,moverObjeto,22);
}
//FIN DE MOVIMIENTO CLARA

//TELLO
void automovil(){
    glPushMatrix();
            glColor3f(.2546,.125,.9124);
            glTranslatef(0,0,4);
            glTranslated(trasladarAuto,0,0);
            glutSolidSphere(0.5,8,8);
        glPushMatrix();
            glColor3f(.2546,.125,.9124);
            glTranslatef(0,0,8);
            glRotatef(rueda,0,0,1);
            gluCylinder(p, 0, 2, 0.5, 15, 15);
        glPopMatrix();
        glPushMatrix();
            glColor3f(.2546,.125,.9124);
            glTranslatef(0,0,0);
            glRotatef(rueda,0,0,1);
            gluCylinder(p, 0, 2, 0.5, 15, 15);
        glPopMatrix();
        glPushMatrix();
            glColor3f(.2546,.125,.9124);
            glTranslatef(14,0,8);
            glRotatef(rueda,0,0,1);
            gluCylinder(p, 0, 2, 0.5, 15, 15);
        glPopMatrix();
        glPushMatrix();
            glColor3f(.2546,.125,.9124);
            glTranslatef(14,0,0);
            glRotatef(rueda,0,0,1);
            gluCylinder(p, 0, 2, 0.5, 15, 15);
        glPopMatrix();
        glPushMatrix();
              glColor3f(1,1,0);
              glTranslatef(5.3,1.2,4.2);
              glScaled(7,1.2,2);
              glutSolidCube(3);
        glPopMatrix();
        glPushMatrix();
              glColor3f(1,1,0);
              glTranslatef(6,4.5,4.2);
              glScaled(3,1.2,2);
              glutSolidCube(3);
        glPopMatrix();
        glPopMatrix();
}
void rotarRueda(int i){
    rueda = rueda + 1;
    glutPostRedisplay();
    glutTimerFunc(200,rotarRueda,33);
}
void camion(){
    glPushMatrix();
            glColor3f(.2546,.125,.9124);
            glTranslatef(0,0,9);
            glRotatef(rueda,0,0,1);
            gluCylinder(p, 0, 3, 0.5, 15, 15);
        glPopMatrix();
        glPushMatrix();
            glColor3f(.2546,.125,.9124);
            glTranslatef(0,0,0);
            glRotatef(rueda,0,0,1);
            gluCylinder(p, 0, 3, 0.5, 15, 15);
        glPopMatrix();
        glPushMatrix();
            glColor3f(.2546,.125,.9124);
            glTranslatef(17.5,0,9);
            glRotatef(rueda,0,0,1);
            gluCylinder(p, 0, 3, 0.5, 15, 15);
        glPopMatrix();
        glPushMatrix();
            glColor3f(.2546,.125,.9124);
            glTranslatef(17.5,0,0);
            glRotatef(rueda,0,0,1);
            gluCylinder(p, 0, 3, 0.5, 15, 15);
        glPopMatrix();
        glPushMatrix();
              glColor3f(1,1,0);
              glTranslatef(7,1.2,4.2);
              glScaled(10,1.2,2.3);
              glutSolidCube(3);
        glPopMatrix();
        glPushMatrix();
              glColor3f(1,1,0);
              glTranslatef(17.5,4.5,4.2);
              glScaled(3,2.5,2.3);
              glutSolidCube(3);
        glPopMatrix();
         glPushMatrix();
              glColor3f(.2546,.125,.9124);
              glTranslatef(1,6.7,4.2);
              glScaled(8,3.5,2.8);
              glutSolidCube(3);
        glPopMatrix();
}
void trailer(){
    glPushMatrix();
            glColor3f(.2546,.125,.9124);
            glTranslatef(0,0,14);
            glRotatef(rueda,0,0,1);
            gluCylinder(p, 0, 4, 0.5, 15, 15);
        glPopMatrix();
        glPushMatrix();
            glColor3f(.2546,.125,.9124);
            glTranslatef(0,0,0);
            glRotatef(rueda,0,0,1);
            gluCylinder(p, 0, 4, 0.5, 15, 15);
        glPopMatrix();
        glPushMatrix();
            glColor3f(.2546,.125,.9124);
            glTranslatef(10.5,0,14);
            glRotatef(rueda,0,0,1);
            gluCylinder(p, 0, 4, 0.5, 15, 15);
        glPopMatrix();
        glPushMatrix();
            glColor3f(.2546,.125,.9124);
            glTranslatef(10.5,0,0);
            glRotatef(rueda,0,0,1);
            gluCylinder(p, 0, 4, 0.5, 15, 15);
        glPopMatrix();
         glPushMatrix();
            glColor3f(.2546,.125,.9124);
            glTranslatef(35,0,14);
            glRotatef(rueda,0,0,1);
            gluCylinder(p, 0, 4, 0.5, 15, 15);
        glPopMatrix();
        glPushMatrix();
            glColor3f(.2546,.125,.9124);
            glTranslatef(35,0,0);
            glRotatef(rueda,0,0,1);
            gluCylinder(p, 0, 4, 0.5, 15, 15);
        glPopMatrix();
        glPushMatrix();
              glColor3f(1,1,0);
              glTranslatef(18,2.4,7);
              glScaled(16,1.2,4.4);
              glutSolidCube(3);
        glPopMatrix();
        glPushMatrix();
              glColor3f(1,1,0);
              glTranslatef(37.5,7.5,7);
              glScaled(3,5,4.4);
              glutSolidCube(3);
        glPopMatrix();
        glPushMatrix();
            glColor3f(.2546,.125,.9124);
            glTranslatef(-3,11.5,8);
            glRotatef(90,0,1,0);
            gluCylinder(p, 8, 8, 35, 100, 100);
        glPopMatrix();
        glPushMatrix();
            glColor3f(.2546,.125,.9124);
            glTranslatef(31,11.5,8);
            glRotatef(90,0,1,0);
            gluCylinder(p, 0, 8, 0, 100, 100);
        glPopMatrix();
        glPushMatrix();
            glColor3f(.2546,.125,.9124);
            glTranslatef(-2,11.5,8);
            glRotatef(90,0,1,0);
            gluCylinder(p, 0, 8, 0, 100, 100);
        glPopMatrix();
}
//FIN TELLO



void mover_pata_derecha(int i){
    if(angulo_normal_pata1>=45 && angulo_normal_pata1<=51){
        angulo_normal_pata1+=2;
    }
    else{
        angulo_normal_pata1=45;
    }

    glutPostRedisplay();
    glutTimerFunc (100, mover_pata_derecha, 1);
}
void mover_cola_alacran(int i){

    if(angulo_cola_alacran>=320 && estado_cola==0){
        angulo_cola_alacran=angulo_cola_alacran+1;
        if(angulo_cola_alacran==360){
            angulo_cola_alacran=0;
            estado_cola=1;
            //printf("PRIMER IF ---> interno \n");
        }
        //printf("PRIMER IF \n");
    }

    if(angulo_cola_alacran>=0 && estado_cola==1){
        angulo_cola_alacran=angulo_cola_alacran+1;
        if(angulo_cola_alacran==60){
            estado_cola=0;
            //printf("SEGUNDO IF ---> INTERNO \n");
        }
        //printf("SEGUNDO IF \n");
    }
/*
    if(estado_cola==0){
        angulo_cola_alacran=angulo_cola_alacran-1;
    }
*/
/*
    if(angulo_cola_alacran<=60 && estado_cola==0){
        angulo_cola_alacran=angulo_cola_alacran-1;
        if(angulo_cola_alacran==0){
            angulo_cola_alacran=360;
            estado_cola=1;
            printf("TERCER IF ---> INTERNO  \n");
        }
        printf("TERCER IF \n");
    }

    if(angulo_cola_alacran<=360 && estado_cola==1){
        angulo_cola_alacran=angulo_cola_alacran-1;
        if(angulo_cola_alacran==320){
            estado_cola=0;
            printf("CUARTO IF ---> INTERNO \n");
        }
        printf("CUARTO IF \n");
    }
*/
    glutPostRedisplay();
    glutTimerFunc (1000, mover_cola_alacran, 3);
}


void moverNube(int ){

        moverNubes+=2;
    if(moverNubes==90.0){

            moverNubes=20.0;
    }

  glutPostRedisplay();
    glutTimerFunc(70,moverNube,32);

}

void ovni(){

    glPushMatrix(); /// CIRCULO CENTRAL
    {

        glRotatef(anguloGiro, 1,0,0);
        glRotatef(anguloAnillo, 0,0 ,1);
        glColor3ub(241,45, 247);
        glutSolidSphere(3,80,80);

        glPushMatrix(); /// ABDUCCION_LUZ
        {
            glColor3f(0,1,0);
           glTranslatef(0,0,posLuz);
           glRotatef(anguloLuz,0,0,0);
           glutWireCone(3,largoLuz,6,8);
        }
        glPopMatrix();

        glutWireCone(1,3,4,5);

        glPushMatrix(); /// ANILLO
        {
            glColor3ub(255,35, 35);
           glutSolidTorus(1,4,80,80);

            glPushMatrix(); /// CIRCULO1
            {
                glTranslatef(4.5,0,-0.4);
                glColor3ub(34,208, 15);
                gluSphere(gluNewQuadric(),0.8, 50, 50);

                glTranslatef(0.5,0,-0.4);
                glColor3ub(16,95,7);
                gluSphere(gluNewQuadric(),0.3, 50, 50);
            }
            glPopMatrix();

           glPushMatrix(); /// CIRCULO2
            {
                glTranslatef(-4.5,0,-0.4);
                glColor3ub(34,208, 15);
                gluSphere(gluNewQuadric(),0.8, 50, 50);

                glTranslatef(-0.5,0,-0.4);
                glColor3ub(16,95,7);
                gluSphere(gluNewQuadric(),0.3, 50, 50);
            }
            glPopMatrix();

            glPushMatrix(); /// CIRCULO3
            {
                glTranslatef(0,4.5,-0.4);
                glColor3ub(34,208, 15);
                gluSphere(gluNewQuadric(),0.8, 50, 50);

                glTranslatef(0,0.5,-0.4);
                glColor3ub(16,95,7);
                gluSphere(gluNewQuadric(),0.3, 50, 50);
            }
            glPopMatrix();


            glPushMatrix(); /// CIRCULO4
            {
                glTranslatef(0,-4.5,-0.4);
                glColor3ub(34,208, 15);
                gluSphere(gluNewQuadric(),0.8, 50, 50);

                glTranslatef(0,-0.5,-0.4);
                glColor3ub(16,95,7);
                gluSphere(gluNewQuadric(),0.3, 50, 50);

            }
            glPopMatrix();
        }glPopMatrix();

          glPushMatrix(); /// DISCO
          {
        glRotatef(anguloObjeto, 0,0,1);
        glColor3ub(255,255,255);
        gluDisk(gluNewQuadric(),6, 8, 10, 40 );
        glColor3ub(50,50,50);
        gluDisk(gluNewQuadric(),4, 9, 40, 1 );

             glPushMatrix(); /// circuloG1
            {
                glTranslatef(8.5,0,0);
                glColor3ub(34,208, 15);
                glutSolidSphere(0.5, 50, 50);

                glTranslatef(0.3,0,-0.3);
                glColor3ub(16,95,7);
                glutSolidSphere(0.2, 50, 50);

            }
            glPopMatrix();

            glPushMatrix(); /// circuloG2
            {
                glTranslatef(-8.5,0,0);
                glColor3ub(34,208, 15);
                glutSolidSphere(0.5, 50, 50);

                glTranslatef(-0.3,0,-0.3);
                glColor3ub(16,95,7);
               glutSolidSphere(0.2, 50, 50);

            }
            glPopMatrix();

             glPushMatrix(); /// circuloG3
            {
                glTranslatef(0,8.5,0);
                glColor3ub(34,208, 15);
                glutSolidSphere(0.5, 50, 50);

                glTranslatef(0.1,0.3,-0.3);
                glColor3ub(16,95,7);
                glutSolidSphere(0.2, 50, 50);

            }
            glPopMatrix();

             glPushMatrix(); /// circuloG4
            {
                glTranslatef(0,-8.5,0);
                glColor3ub(34,208, 15);
                glutSolidSphere(0.5, 50, 50);

                glTranslatef(-0.1,-0.3,-0.3);
                glColor3ub(16,95,7);
                glutSolidSphere(0.2, 50, 50);

            }
            glPopMatrix();


            glPushMatrix(); ///PATA_OVNI1
            {
                glTranslatef(0,-8.5,0);
                glutSolidSphere(0.3, 20,20);
                glColor3ub(255,160,0);
                glRotatef(anguloPata1,1,0,0);
                gluCylinder(gluNewQuadric(),0.2,0.2,1,100,100);

                glPushMatrix(); ///PATA_OVNI_1.1
                {
                    glTranslatef(0,0,1);
                    glColor3f(1,0,0);
                    glutSolidSphere(0.3, 20,20);
                    glColor3ub(255,160,0);
                    glRotatef(anguloPata1_1,1,0,0);
                    gluCylinder(gluNewQuadric(),0.2,0.2,1,100,100);

                    glPushMatrix(); ///PATA_OVNI_1.1.1
                    {

                      glTranslatef(0,0,1);
                      glColor3f(1,0,0);
                      glutSolidSphere(0.3, 20,20);
                      glColor3ub(255,160,0);
                      glRotatef(anguloPata1_2,1,0,0);
                      gluCylinder(gluNewQuadric(),0.2,0.2,1,100,100);

                      glPushMatrix(); ///PATA_OVNI1_TIERRA
                      {
                          glTranslatef(0,0,1);
                          glColor3f(1,0,0);
                          glutSolidSphere(0.2, 20,20);
                          glColor3ub(255,160,0);
                          glRotatef(anguloPata1_Tierra,1,0,0);
                          glutSolidCone(0.5,1,3,2);

                      }
                      glPopMatrix();
                    }
                    glPopMatrix();
                }
                glPopMatrix();
            }
            glPopMatrix();


            glPushMatrix(); ///PATA_OVNI2
            {
                glTranslatef(0,8.5,0);
                glutSolidSphere(0.3, 20,20);
                glColor3ub(255,160,0);
                glRotatef(anguloPata2,1,0,0);
                gluCylinder(gluNewQuadric(),0.2,0.2,1,100,100);

                glPushMatrix(); ///PATA_OVNI_2.1
                {
                    glTranslatef(0,0,1);
                    glColor3f(1,0,0);
                    glutSolidSphere(0.3, 20,20);
                    glColor3ub(255,160,0);
                    glRotatef(anguloPata2_1,1,0,0);
                    gluCylinder(gluNewQuadric(),0.2,0.2,1,100,100);

                    glPushMatrix(); ///PATA_OVNI_2.1.1
                    {
                      glTranslatef(0,0,1);
                      glColor3f(1,0,0);
                      glutSolidSphere(0.3, 20,20);
                      glColor3ub(255,160,0);
                      glRotatef(anguloPata2_2,1,0,0);
                      gluCylinder(gluNewQuadric(),0.2,0.2,1,100,100);

                      glPushMatrix(); ///PATA_OVNI2_TIERRA
                      {
                          glTranslatef(0,0,1);
                          glColor3f(1,0,0);
                          glutSolidSphere(0.2, 20,20);
                          glColor3ub(255,160,0);
                          glRotatef(anguloPata2_Tierra,1,0,0);
                          glutSolidCone(0.5,1,3,2);
                      }
                      glPopMatrix();
                    }
                    glPopMatrix();
                }
                glPopMatrix();
            }
            glPopMatrix();

              glPushMatrix(); ///PATA_OVNI3
            {
                glTranslatef(8.5,0,0);
                glutSolidSphere(0.3, 20,20);
                glColor3ub(255,160,0);
                glRotatef(anguloPata1,0,1,0);
                gluCylinder(gluNewQuadric(),0.2,0.2,1,100,100);

                glPushMatrix(); ///PATA_OVNI_3.1
                {
                    glTranslatef(0,0,1);
                    glColor3f(1,0,0);
                    glutSolidSphere(0.3, 20,20);
                    glColor3ub(255,160,0);
                    glRotatef(anguloPata1_1,0,1,0);
                    gluCylinder(gluNewQuadric(),0.2,0.2,1,100,100);

                    glPushMatrix(); ///PATA_OVNI_3.1.1
                    {

                      glTranslatef(0,0,1);
                      glColor3f(1,0,0);
                      glutSolidSphere(0.3, 20,20);
                      glColor3ub(255,160,0);
                      glRotatef(anguloPata1_2,0,1,0);
                      gluCylinder(gluNewQuadric(),0.2,0.2,1,100,100);

                      glPushMatrix(); ///PATA_OVNI3_TIERRA
                      {
                          glTranslatef(0,0,1);
                          glColor3f(1,0,0);
                          glutSolidSphere(0.2, 20,20);
                          glColor3ub(255,160,0);
                          glRotatef(anguloPata1_Tierra,0,1,0);
                          glutSolidCone(0.5,1,3,2);
                      }
                      glPopMatrix();
                    }
                    glPopMatrix();
                }
                glPopMatrix();
            }
            glPopMatrix();

               glPushMatrix(); ///PATA_OVNI4
            {
                glTranslatef(-8.5,0,0);
                glutSolidSphere(0.3, 20,20);
                glColor3ub(255,160,0);
                glRotatef(anguloPata2,0,1,0);
                gluCylinder(gluNewQuadric(),0.2,0.2,1,100,100);

                glPushMatrix(); ///PATA_OVNI_4.1
                {
                    glTranslatef(0,0,1);
                    glColor3f(1,0,0);
                    glutSolidSphere(0.3, 20,20);
                    glColor3ub(255,160,0);
                    glRotatef(anguloPata2_1,0,1,0);
                    gluCylinder(gluNewQuadric(),0.2,0.2,1,100,100);

                    glPushMatrix(); ///PATA_OVNI_4.1.1
                    {

                      glTranslatef(0,0,1);
                      glColor3f(1,0,0);
                      glutSolidSphere(0.3, 20,20);
                      glColor3ub(255,160,0);
                      glRotatef(anguloPata2_2,0,1,0);
                      gluCylinder(gluNewQuadric(),0.2,0.2,1,100,100);

                      glPushMatrix(); ///PATA_OVNI4_TIERRA
                      {
                          glTranslatef(0,0,1);
                          glColor3f(1,0,0);
                          glutSolidSphere(0.2, 20,20);
                          glColor3ub(255,160,0);
                          glRotatef(anguloPata2_Tierra,0,1,0);
                          glutSolidCone(0.5,1,3,2);
                      }
                      glPopMatrix();
                    }
                    glPopMatrix();
                }
                glPopMatrix();
            }
            glPopMatrix();

          }
          glPopMatrix();
    }
    glPopMatrix();

}

void abeja(){

glTranslatef(0,abeja_y,0);
    ///CUERPO///
glPushMatrix();{
    glRotated(rotarAbeja,0,1,0);
    glPushMatrix();{
        ///CABEZA///
    glColor3ub(0,0,0);
    glTranslated(0,6,2);
    glRotatef(anguloCabeza,0,1,0);
    glScaled(0.6,0.6,0.6);
    glPushMatrix();
    glScaled(1.02,1.02,1.02);
    glutWireDodecahedron();;
    glPopMatrix();
    glColor3ub(255,160,0);
    glutSolidDodecahedron();

     ///ANTENA DERECHA///
     glPushMatrix();
     {

      glTranslatef(0.4,2,0);
      glRotatef(anguloAntenaDerecha,1,1,0);
      glColor3ub(175,109,73);
    glutSolidSphere(0.3, 20,20);
       glColor3ub(255,160,0);
      gluCylinder(p,0.2,0.2,3,100,100);

       ///FLAGELO///
       glPushMatrix();
       {
          glTranslatef(0,0,3);
          glRotatef(anguloFlageloDerecho,1,1,0);
          glColor3ub(255,160,0);
          gluCylinder(p,0.2,0.2,4,100,100);
          glColor3ub(175,109,73);
          glutSolidSphere(0.3, 20,20);

       }
       glPopMatrix();
     }
     glPopMatrix();


      ///ANTENA IZQUIERDA///
     glPushMatrix();
     {
      glTranslatef(0.4,1,1.2);
      glRotatef(anguloAntenaIzquierda,1,an,0);
      glColor3ub(175,109,73);
        glutSolidSphere(0.3, 20,20);
       glColor3ub(255,160,0);
      gluCylinder(p,0.2,0.2,3,100,100);

       ///FLAGELO///
       glPushMatrix();
       {
          glTranslatef(0,0,3);
          glRotatef(anguloFlageloIzquierdo,1,1,0);
          glColor3ub(255,160,0);
          gluCylinder(p,0.2,0.2,4,100,100);
          glColor3ub(175,109,73);
          glutSolidSphere(0.3, 20,20);
       }
       glPopMatrix();
     }
     glPopMatrix();

    }
    glPopMatrix();


     glPushMatrix();{
       ///TORAX///
      glScaled(3,2,1);
       glColor3f(1,0,0);
       glTranslated(1,3,2);
       glRotatef(torax,1,1,1);
       glColor3ub(0,0,0);
       glPushMatrix();
       glScaled(1.02,1.02,1.02);
       glutWireIcosahedron();
       glPopMatrix();
       glColor3ub(255,160,0);
       glutSolidIcosahedron();

       glPushMatrix();
       {
           ///ALA DERECHA///
            glColor3f(1,1,1);
            glRotated(anguloAla,0,0.5,0);
            glScaled(0.2,0.2,0.2);
            glTranslatef(4,0,2);
            glutWireCone(2,10,2,100);




       }
       glPopMatrix();

         glPushMatrix();
       {
           ///ALA IZQUIERDA///
            glColor3f(1,1,1);
            glRotated(anguloAla,0,0.5,0);
            glScaled(0.2,0.2,0.2);
            glTranslatef(4,2,2);
            glutWireCone(2,10,2,100);




       }
       glPopMatrix();

       glPushMatrix(); ///PATA 1
       {
           glScaled(0.2,0.2,0.2);
            glTranslatef(0,8.5,0);
            glColor3ub(255,160,0);
            glRotatef(anguloPataAbeja1,1,0,0);
            gluCylinder(gluNewQuadric(),0.2,0.2,4,100,100);
            glPushMatrix();///PATA1_2
            {

                 glRotatef(180,0,1,0);
                 glTranslatef(0,0,0);
                    glColor3ub(175,109,73);
                    glutSolidSphere(0.3, 20,20);
                    glColor3ub(255,160,0);
                    glRotatef(anguloPataAbeja1_2,0,1,0);
                    gluCylinder(gluNewQuadric(),0.2,0.2,4,100,100);
            glPushMatrix();///PATA1_3
            {
                glTranslatef(0,0,4);
                      glColor3ub(175,109,73);
                      glutSolidSphere(0.3, 20,20);
                      glColor3ub(255,160,0);
                      glRotatef(anguloPataAbeja1_3,0,1,0);
                      gluCylinder(gluNewQuadric(),0.2,0.2,5,100,100);

                      glPushMatrix();///PATA1_TIERRA
                      {
                          glScaled(2,2,2);
                            glTranslatef(0,0,2.5);
                            glColor3ub(175,109,73);
                            glRotatef(-70,1,0,0);
                            gluCylinder(gluNewQuadric(),0.1,0.03,1,32,32);
                            glRotatef(70,1,0,0);
                            gluCylinder(gluNewQuadric(),0.1,0.03,1,32,32);
                      }
                      glPopMatrix();
                      }
                   glPopMatrix();
                }glPopMatrix();


       }
       glPopMatrix();


         glPushMatrix(); ///PATA 2
       {
           glScaled(0.2,0.2,0.2);
            glTranslatef(0,8.5,-3);
            glColor3ub(255,160,0);
            glRotatef(anguloPataAbeja1,1,0,0);
            gluCylinder(gluNewQuadric(),0.2,0.2,4,100,100);
            glPushMatrix();///PATA2_2
            {

                 glRotatef(180,0,1,0);
                 glTranslatef(0,0,0);
                    glColor3ub(175,109,73);
                    glutSolidSphere(0.3, 20,20);
                    glColor3ub(255,160,0);
                    glRotatef(anguloPataAbeja1_2,0,1,0);
                    gluCylinder(gluNewQuadric(),0.2,0.2,4,100,100);
            glPushMatrix();///PATA2_3
            {
                glTranslatef(0,0,4);
                      glColor3ub(175,109,73);
                      glutSolidSphere(0.3, 20,20);
                      glColor3ub(255,160,0);
                      glRotatef(anguloPataAbeja1_3,0,1,0);
                      gluCylinder(gluNewQuadric(),0.2,0.2,5,100,100);

                      glPushMatrix();///PATA2_TIERRA
                      {
                          glScaled(2,2,2);
                            glTranslatef(0,0,2.5);
                            glColor3ub(175,109,73);
                            glRotatef(-70,1,0,0);
                            gluCylinder(gluNewQuadric(),0.1,0.03,1,32,32);
                            glRotatef(70,1,0,0);
                            gluCylinder(gluNewQuadric(),0.1,0.03,1,32,32);
                      }
                      glPopMatrix();
            }
            glPopMatrix();

            }glPopMatrix();
       }
       glPopMatrix();
        glPushMatrix(); ///PATA 3
       {
           glRotatef(200,1,0,0);
           glScaled(0.2,0.2,0.2);
            glTranslatef(0,8.5,0);
            glColor3ub(255,160,0);
            glRotatef(anguloPataAbeja1,1,0,0);
            gluCylinder(gluNewQuadric(),0.2,0.2,4,100,100);
            glPushMatrix();///PATA3_2
            {

                 glRotatef(180,0,1,0);
                 glTranslatef(0,0,0);
                    glColor3ub(175,109,73);
                    glutSolidSphere(0.3, 20,20);
                    glColor3ub(255,160,0);
                    glRotatef(anguloPataAbeja1_2,0,1,0);
                    gluCylinder(gluNewQuadric(),0.2,0.2,4,100,100);
            glPushMatrix();///PATA3_3
            {
                glTranslatef(0,0,4);
                      glColor3ub(175,109,73);
                      glutSolidSphere(0.3, 20,20);
                      glColor3ub(255,160,0);
                      glRotatef(anguloPataAbeja1_3,0,1,0);
                      gluCylinder(gluNewQuadric(),0.2,0.2,5,100,100);

                      glPushMatrix();///PATA3_TIERRA
                      {
                          glScaled(2,2,2);
                            glTranslatef(0,0,2.5);
                            glColor3ub(175,109,73);
                            glRotatef(-70,1,0,0);
                            gluCylinder(gluNewQuadric(),0.1,0.03,1,32,32);
                            glRotatef(70,1,0,0);
                            gluCylinder(gluNewQuadric(),0.1,0.03,1,32,32);

                      }
                      glPopMatrix();
            }
            glPopMatrix();
        }glPopMatrix();
       }
       glPopMatrix();
        glPushMatrix(); ///PATA 4
       {
           glRotatef(200,1,0,0);
           glScaled(0.2,0.2,0.2);
            glTranslatef(0,8.5,-3);
            glColor3ub(255,160,0);
            glRotatef(anguloPataAbeja1,1,0,0);
            gluCylinder(gluNewQuadric(),0.2,0.2,4,100,100);
            glPushMatrix();///PATA4_2
            {

                 glRotatef(180,0,1,0);
                 glTranslatef(0,0,0);
                    glColor3ub(175,109,73);
                    glutSolidSphere(0.3, 20,20);
                    glColor3ub(255,160,0);
                    glRotatef(anguloPataAbeja1_2,0,1,0);
                    gluCylinder(gluNewQuadric(),0.2,0.2,4,100,100);
            glPushMatrix();///PATA4_3
            {
                glTranslatef(0,0,4);
                      glColor3ub(175,109,73);
                      glutSolidSphere(0.3, 20,20);
                      glColor3ub(255,160,0);
                      glRotatef(anguloPataAbeja1_3,0,1,0);
                      gluCylinder(gluNewQuadric(),0.2,0.2,5,100,100);

                      glPushMatrix();///PATA4_TIERRA
                      {
                          glScaled(2,2,2);
                            glTranslatef(0,0,2.5);
                            glColor3ub(175,109,73);
                            glRotatef(-70,1,0,0);
                            gluCylinder(gluNewQuadric(),0.1,0.03,1,32,32);
                            glRotatef(70,1,0,0);
                            gluCylinder(gluNewQuadric(),0.1,0.03,1,32,32);

                      }
                      glPopMatrix();
            }
            glPopMatrix();
            }glPopMatrix();
       }
       glPopMatrix();
   }
   glPopMatrix();



    glPushMatrix();{
        ///COLA///
    glTranslated(5,6,2);
    glRotatef(anguloCola,0,1,0);
    glPushMatrix();
       glScaled(1.02,1.02,1.02);
    glColor3ub(0,0,0);
    glutWireCone(1.5,6,10,5);
    glPopMatrix();
    glColor3ub(255,160,0);
    glutSolidCone(1.5,6,10,5);
    }
    glPopMatrix();
}
glPopMatrix();
}

void moverPataAbeja1(int ){
if(anguloPataAbeja1==70 || auxPata){
    anguloPataAbeja1+=5;
    auxPata=true;
    if(anguloPataAbeja1==90)auxPata=false;
}else anguloPataAbeja1-=5;
glutPostRedisplay();
glutTimerFunc(200,moverPataAbeja1,30);
}

void moverPataAbeja2(int ){
if(anguloPataAbeja1_2==20 || auxPata1){
    anguloPataAbeja1_2-=5;
    auxPata1=true;
    if(anguloPataAbeja1_2==-30)auxPata1=false;
}else anguloPataAbeja1_2+=5;
glutPostRedisplay();
glutTimerFunc(200,moverPataAbeja2,30);
}

void moverPataAbeja3(int ){
if(anguloPataAbeja1_3==30 || auxPata2){
    anguloPataAbeja1_3+=5;
    auxPata2=true;
    if(anguloPataAbeja1_3==60)auxPata2=false;
}else anguloPataAbeja1_3-=5;
glutPostRedisplay();
glutTimerFunc(200,moverPataAbeja3,30);
}

void moverTorax(int ){
if(torax==120 || anguloAbeja){
    torax+=2;
    anguloAbeja=true;
if(torax==126) anguloAbeja=false;
}else torax-=2;
glutPostRedisplay();
glutTimerFunc(200,moverTorax,8);

}
void moverAlaIzquierda(int ){
if(anguloAla==90 || angulo3){
    anguloAla-=10;
    angulo3=true;
    if(anguloAla==0) angulo3=false;
}else anguloAla+=10;
glutPostRedisplay();
glutTimerFunc(1,moverAlaIzquierda,7);
}
void moverCola(int ){
if(anguloCola==120 || anguloAbeja){
    anguloCola-=2;
    anguloAbeja=true;
    if(anguloCola==-120) anguloAbeja=false;
}else anguloCola+=2;
glutPostRedisplay();
glutTimerFunc(100,moverCola,6);

}
void moverCabezaAbeja(int ){
if(anguloCabeza==-30 || anguloAbeja){
    anguloCabeza+=2;
    anguloAbeja=true;
    if(anguloCabeza==0) anguloAbeja=false;
}else anguloCabeza-=2;
    glutPostRedisplay();
    glutTimerFunc(300,moverCabezaAbeja,1);
}

void moverAntenaDerecha( int){
if(anguloAntenaDerecha==-70 || anguloAbeja){
    anguloAntenaDerecha+=2;
    anguloAbeja=true;
    if(anguloAntenaDerecha==0) anguloAbeja=false;
}else anguloAntenaDerecha-=2;

 glutPostRedisplay();
    glutTimerFunc(90,moverAntenaDerecha,2);
}

void moverFlageloDerecho(int ){
if(anguloFlageloDerecho==60 || angulo2){
    anguloFlageloDerecho-=5;
    angulo2=true;
    if(anguloFlageloDerecho==0) angulo2=false;

}else anguloFlageloDerecho+=5;
glutPostRedisplay();
 glutTimerFunc(20,moverFlageloDerecho,4);
}
void moverFlageloIzquierdo(int ){
if(anguloFlageloIzquierdo==60 || angulo2){
    anguloFlageloIzquierdo-=5;
    angulo2=true;
    if(anguloFlageloIzquierdo==0) angulo2=false;
}else anguloFlageloIzquierdo+=5;
  glutPostRedisplay();
 glutTimerFunc(20,moverFlageloIzquierdo,5);
}
void moverAntenaIzquierda( int){
if(anguloAntenaIzquierda==-40 || anguloAbeja){
    anguloAntenaIzquierda+=2;
    anguloAbeja=true;
    if(anguloAntenaIzquierda==0) anguloAbeja=false;
}else anguloAntenaIzquierda-=2;

 glutPostRedisplay();
    glutTimerFunc(90,moverAntenaIzquierda,3);
}
void trasladarAbeja(int ){
    if(abeja_z>-20 && auxAbeja==false){
        abeja_z=abeja_z-2;
        if(abeja_z==-20){
            auxAbeja=true;
            angulo_giro_abeja=360;posicion_x_abeja=30;posicion_y_abeja=0;posicion_z_abeja=0;
        }
    }
    if(abeja_z<=60 && auxAbeja==true){
        abeja_z=abeja_z+2;
        if(abeja_z==60){
            auxAbeja=false;
            angulo_giro_abeja=180;posicion_x_abeja=0;posicion_y_abeja=30;posicion_z_abeja=0;
        }
    }
     glutPostRedisplay();
    glutTimerFunc(300,trasladarAbeja,40);
}

void renderScene(void) {

	if (deltaMove)
		computePos(deltaMove);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(	x, 1.0f, z,x+lx, 1.0f,  z+lz,0.0f, 1.0f,  0.0f);
	//gluLookAt(80,30,10, 0,0,0, 0,1,0);
	//gluLookAt(30,12,20, 0,0,0, 0,1,0);
	//gluLookAt(110+x,10,z,  x+lx,0,z+lz,  0.0f,1.0f,0.0f);
    gluLookAt(	100, 0, 70,x+lx, 1.0f,  z+lz,0.0f, 1.0f,  0.0f);
	//gluLookAt(	x, 80, z,x+lx, 1.0f,  z+lz,0.0f, 1.0f,  0.0f);

	coordenadas();
	//gluLookAt(0,100,0,     0,50,0,   4000,4000,4000);
	arbol();
	suelo_parque();

	zona_de_paso();
	//pileta_central();
	pista();
	veredas();
	piso_de_casa();
	casa();
	glPushMatrix();
        glTranslatef(-30,2.8,30);
        glRotatef(45,0,30,0);
        glScaled(0.2,0.2,0.2);
        humano_harold();
	glPopMatrix();

	glPushMatrix();
        glTranslatef(40,0.7,-30);
        glScaled(0.2,0.2,0.2);
        robot_karateka();
	glPopMatrix();

	glPushMatrix();
	   if(cont<=7){ ///CORREGIR
        glTranslatef(-trasladar_ejex,0,-trasladar_ejez);
        glRotatef(angulo_alacran,ejex,ejey,ejez);
        serpiente();
	   }else{
        glTranslatef(-trasladar_ejex,y,-trasladar_ejez);
        angSer=90;
	   }
	glPopMatrix();

	glPushMatrix();
      glTranslatef(trasladar_ejex,y,trasladar_ejez);
      glRotatef(angulo_alacran,ejex,ejey,ejez);
      if(contBajada>=10){
      rey_escorpion();
      }
    glPopMatrix();
	glPushMatrix();
        glTranslatef(-45,1.2,-20);
        glScaled(0.2,0.2,0.2);
        glRotated(90,0,1,0);
        if(angPerro == -180){
            glTranslatef(1,0,trasladarPerro);
            trasladarPerro=trasladarPerro-1;
        }
        perro();
	glPopMatrix();
	glPushMatrix();
        glScaled(0.5, 0.5, 0.5);
        glTranslatef(trasladarObjetox,trasladarObjeto,trasladarz);
        ovni();
	glPopMatrix();

	glPushMatrix();
	  if(cont>=7 && angSer==90){
        glTranslatef(abeja_x,abeja_y,abeja_z);
        glRotatef(angulo_giro_abeja,posicion_x_abeja,posicion_y_abeja,posicion_z_abeja);
        glScaled(0.2, 0.2, 0.2);
        abeja();
	  }
	glPopMatrix();

	glPushMatrix();
        glTranslatef(-110,1,-110);
        glScaled(0.3,0.3,0.3);
        automovil();
        if(angPerro == -180){
            glTranslatef(1,0,trasladarAuto);
            trasladarAuto=trasladarAuto+1;
        }


	glPopMatrix();

	glPushMatrix();
        glTranslatef(80,1.3,60);
        glScaled(0.5,0.5,0.5);
        camion();
	glPopMatrix();

	glPushMatrix();
        glTranslatef(80,1,-40);
        glScaled(0.3,0.3,0.3);
        trailer();
	glPopMatrix();
	//DIBUJAR NUBES

	for(int i = -2; i < 10; i++)
		for(int j=-3; j < 10; j++) {
			glPushMatrix();
			glTranslatef(i*moverNubes,20,j * 30.0);
			nubes();
			glPopMatrix();
		}

    //DIBUJAR 36 ARBOLES
	for(int i = -3; i < 3; i++)
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*25.0,0,j * 30.0);
			arbol();
			glPopMatrix();
		}


	glutSwapBuffers();
}

void pressKey(int key, int xx, int yy) {
	switch (key) {
		case GLUT_KEY_LEFT : deltaAngle = -0.01f; break;
		case GLUT_KEY_RIGHT : deltaAngle = 0.01f; break;
		case GLUT_KEY_UP : deltaMove = 5.0f; break;
		case GLUT_KEY_DOWN : deltaMove = -5.0f; break;
	}
}
void releaseKey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT :
		case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : deltaMove = 0;break;
	}
}
void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;

		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}
void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else  {// state = GLUT_DOWN
			xOrigin = x;
		}
	}
}
void luzYMaterial(){
    const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

    const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
    const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
    const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat high_shininess[] = { 100.0f };

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void moverCascabel(int i){
    if(moverCasca==20 || aux2){
            moverCasca-=4;
            aux2 = true;
            if(moverCasca==-16)
                aux2 = false;
    }else if(!aux2){
        moverCasca+=4;

    }
    glutPostRedisplay();
    glutTimerFunc(100,moverCascabel,6);
}
void moverCab(int i){
    if(moverCabeza==20 || aux1){
            moverCabeza-=4;
            aux1 = true;
            if(moverCabeza==-16)
                aux1 = false;
    }else if(!aux1){
        moverCabeza+=4;

    }
    glutPostRedisplay();
    glutTimerFunc(100,moverCab,4);
}
void moverCab2(int i){
    if(moverCabeza2==-20 || aux1){
            moverCabeza2+=8;
            aux1 = true;
            if(moverCabeza2==16)
                aux1 = false;
    }else if(!aux1){
        moverCabeza2-=8;

    }
    glutPostRedisplay();
    glutTimerFunc(100,moverCab2,5);
}

void detectar_colision_snake_scorpion(int i){

    if(abs(-trasladar_ejex-trasladar_ejex)+abs(-trasladar_ejez-trasladar_ejez)<12){
        estado_colision=true;
        glutTimerFunc(10,moverTronco,15);
        angHumano = -180;
        cont++;
        contador_colision_snake_alacran++;
    }
    if(estado_colision && contador_colision_snake_alacran==1){
        angulo_alacran=270;
        angPerro = -180;
        cont++;
        ejex=0;ejey=20;ejez=0;
        estado_colision=false;
    }
    if(estado_colision && contador_colision_snake_alacran==2){
        angulo_alacran=-45;
        cont++;
        ejex=0;ejey=20;ejez=0;
        estado_colision=false;
    }
    if(estado_colision && contador_colision_snake_alacran==3){
        angulo_alacran=0;
        cont++;
        ejex=20;ejey=0;ejez=0;
        estado_colision=false;
    }
    if(estado_colision && contador_colision_snake_alacran==4){
        angulo_alacran=45;
        cont++;
        ejex=0;ejey=20;ejez=0;
        estado_colision=false;
    }
    if(contador_colision_snake_alacran>4){
        angulo_alacran=0;
        cont++;
        ejex=20;ejey=0;ejez=0;
        estado_colision=false;
        contador_colision_snake_alacran=0;
    }
    glutPostRedisplay();
    glutTimerFunc(100,detectar_colision_snake_scorpion,7);

}


void evento_menu(int opcion){
    switch(opcion){
        case ENCENDIDO:
            luzYMaterial();
            break;
        case APAGADO:
            glDisable(GL_LIGHT0);
            glDisable(GL_NORMALIZE);
            glDisable(GL_COLOR_MATERIAL);
            glDisable(GL_LIGHTING);
            break;
    }
}

void moverPataTierra(int ){
if(anguloPata1_Tierra==0 || aux5){
    anguloPata1_Tierra-=6;
    anguloPata2_Tierra+=6;
    aux5=true;
    if(anguloPata1_Tierra==-90) aux5=false;
    }else{
    anguloPata1_Tierra+=6;
    anguloPata2_Tierra-=6;}
    glutPostRedisplay();
    //glutTimerFunc(100,moverPataTierra,9);
}
void Abduccion(int ){
if(posLuz==0 ||aux7){

    posLuz+=2;
    aux7=true;
    if(posLuz==16) aux7=false;
}else  posLuz-=2;
if(largoLuz==2 || aux9){
   largoLuz+=2;
    aux9=true;
   if(largoLuz==18) aux9=false;
}else largoLuz-=2;
glutPostRedisplay();
    //glutTimerFunc(300,Abduccion,5);
}
/// PATAS 1 Y 2
void moverPata(int ){
if(anguloPata1==-70 || aux){
    anguloPata1+=3;
    aux=true;
    if(anguloPata1==50) aux=false;
} else anguloPata1-=3;
glutPostRedisplay();
//glutTimerFunc(100,moverPata,4);
}

void moverPata1_1(int ){
if(anguloPata1_1==0 || aux8){
    anguloPata1_1+=10;
    aux8=true;
    if(anguloPata1_1==80) aux8=false;
} else anguloPata1_1-=10;
glutPostRedisplay();
//glutTimerFunc(100,moverPata1_1,8);

}
void moverPata1_2(int ){
if(anguloPata1_2==0 || aux4){
    anguloPata1_2-=10;
    aux4=true;
    if(anguloPata1_2==-50) aux4=false;
} else anguloPata1_2+=10;
glutPostRedisplay();
//glutTimerFunc(100,moverPata1_2,11);
}

///PATAS 3 Y 4
void moverPata3(int ){
if(anguloPata2==70 || aux5){
    anguloPata2-=3;
    aux5=true;
    if(anguloPata2==-50) aux5=false;
} else anguloPata2+=3;
glutPostRedisplay();
//glutTimerFunc(100,moverPata3,14);
}
void moverPata2_1(int ){
if(anguloPata2_1==0 ||aux6){
    anguloPata2_1-=10;
    aux6=true;
    if(anguloPata2_1==-80) aux6=false;
}else anguloPata2_1+=10;
glutPostRedisplay();
//glutTimerFunc(100,moverPata2_1,15);
}
void moverPata2_2(int ){
if(anguloPata2_2==0 || aux6){
    anguloPata2_2+=10;
    aux6=true;
    if(anguloPata2_2==50) aux6=false;
} else anguloPata2_2-=10;

glutPostRedisplay();
//glutTimerFunc(100,moverPata2_2,16);
}
void traslateObject (int ){
    trasladarObjeto+=0.2;
    glutPostRedisplay();
    //glutTimerFunc(60,traslateObject,1);
}
void rotateRing (int ){
    anguloAnillo-= 10;
    glutPostRedisplay();
   //glutTimerFunc(12,rotateRing,2);
}
void rotateObject (int ){
    anguloObjeto+=20;
    glutPostRedisplay();
    //glutTimerFunc(12,rotateObject,3);
}
void sube(int ){

 if(posLuz>=2 || largoLuz>=4){
    posLuz=0;
    largoLuz=2;
 }
glutPostRedisplay();
    //glutTimerFunc(300,sube,7);
}

///PRESIONAR CONTINUAMENTE
void releaseKey1(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT :
		    //glutTimerFunc(60,traslateObject,1);
		    break;
		case GLUT_KEY_RIGHT :
		    glutTimerFunc(300,Abduccion,5);
		    break;
		case GLUT_KEY_UP :
		   //glutTimerFunc(300,sube,7);
		     break;
		case GLUT_KEY_DOWN :

		     break;

	}
	glutPostRedisplay ();
}
void moverOvniy1(int ){
trasladarObjeto+=0.2;
glutPostRedisplay();
glutTimerFunc(80,moverOvniy1,20);
glutTimerFunc(1,rotateRing,2);
    glutTimerFunc(1,rotateObject,3);
}
void moverOvniy2(int ){
trasladarObjeto-=0.2;
glutPostRedisplay();
glutTimerFunc(80,moverOvniy2,21);
}
void moverOvnix1(int ){
trasladarObjetox+=0.2;
glutPostRedisplay();
glutTimerFunc(80,moverOvnix1,22);
glutTimerFunc(1,rotateRing,2);
    glutTimerFunc(1,rotateObject,3);
}
void moverOvnix2(int ){
trasladarObjetox-=0.2;
glutPostRedisplay();
glutTimerFunc(80,moverOvnix2,23);
glutTimerFunc(1,rotateRing,2);
glutTimerFunc(1,rotateObject,3);
}
void moverOvniz1(int ){

trasladarz+=0.2;
        glutPostRedisplay();
        glutTimerFunc(80,moverOvniz1,24);
        glutTimerFunc(1,rotateRing,2);
        glutTimerFunc(1,rotateObject,3);
}
void moverOvniz2(int ){

trasladarz-=0.2;
        glutPostRedisplay();
        glutTimerFunc(80,moverOvniz2,25);
        glutTimerFunc(1,rotateRing,2);
        glutTimerFunc(1,rotateObject,3);
}
void anguloGir(int ){


 anguloGiro+=5;
  glutPostRedisplay();
  glutTimerFunc(20,anguloGir,30);
 }
void anguloGir2(int ){


 anguloGiro-=5;
  glutPostRedisplay();
  glutTimerFunc(20,anguloGir2,31);
 }
void bajarEsc(int ){
    if(y<=10 && y>=2){
        y = y-2;
    }
    glutTimerFunc(50,bajarEsc,32);
}
void manejarTeclado ( unsigned char tecla, int x, int y){
    switch (tecla)
    {
    case 'o':
          glutTimerFunc(20,anguloGir,30);
        break;
    case 'p':
        glutTimerFunc(20,anguloGir2,31);
        break;
    case 'q':
        glutTimerFunc(80,moverOvnix2,23);


        break;
    case 'e':
        glutTimerFunc(80,moverOvnix1,22);
        break;

        case 'w' : glutTimerFunc(80,moverOvniy1,20);

         break;
        case 'a' :
             glutTimerFunc(80,moverOvniz1,24);

             break;
        case 'd':
              glutTimerFunc(80,moverOvniz2,25);

            break;
        case 's' :glutTimerFunc(80,moverOvniy2,21);
        break;
        case 'x':
            glutTimerFunc(90,moverPata,4);
            glutTimerFunc(90,moverPata3,14);

            break;
        case 'c':
            glutTimerFunc(100,moverPata1_1,8);
            glutTimerFunc(100,moverPata2_1,15);
            break;
        case 'v':
            glutTimerFunc(100,moverPata1_2,11);
            glutTimerFunc(100,moverPata2_2,16);
            break;
        case 'b':
            glutTimerFunc(20,moverPataTierra,9);
            break;
        case 'r':
            contBajada = contBajada + 1;
            glutTimerFunc(300,Abduccion,5);
            if(contBajada == 20){
            glutTimerFunc(50,bajarEsc,32);
            glutTimerFunc(100,caminar_rey_escorpion,2);
            }
            break;
        case 'i':
            glutTimerFunc(300,sube,7); ///INTERRUMPE ACCION DE ABDUCCIR
            break;
    }
    glutPostRedisplay ();
}
void menu_principal(){
    int menu;
    menu=glutCreateMenu(evento_menu);
    glutAddMenuEntry("ENCENDER LUCES",ENCENDIDO);
    glutAddMenuEntry("APAGAR LUCES",APAGADO);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,500);
	glutCreateWindow("T2");
    inicializar();

    menu_principal();

	glutDisplayFunc(renderScene);
	glutReshapeFunc(redimensionar);
	///glutIdleFunc(renderScene);

	glutSpecialFunc(pressKey);

	glutIgnoreKeyRepeat(1);
    glutSpecialUpFunc(releaseKey);

    glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	glEnable(GL_DEPTH_TEST);

	glutTimerFunc (100, mover_pata_derecha, 1);
    glutTimerFunc (1000, mover_cola_alacran, 3);
    glutTimerFunc(100,moverCab,4);
    glutTimerFunc(100,moverCab2,5);
    glutTimerFunc(50,moverCascabel,6);
    glutTimerFunc(100,detectar_colision_snake_scorpion,7);


    //HAROLD
        glutTimerFunc(20,moverHombro,8);
        glutTimerFunc(20,moverCodo,9);
        glutTimerFunc(20,moverMuneca,10);
        glutTimerFunc(20,moverCadera,11);
        glutTimerFunc(20,moverCadera2,12);
        glutTimerFunc(20,moverRodilla,13);
        glutTimerFunc(20,moverTalon,14);
    //FIN HAROLD

    //CLARA
        glutTimerFunc(100,caminar,16);
        glutTimerFunc(100,rotarT1,17);

        glutTimerFunc(20,moverCodo_Clara,18);
        glutTimerFunc(20,moverCadera_Clara,19);
        glutTimerFunc(20,moverCadera2_Clara,20);
        glutTimerFunc(20,moverRodilla_Clara,21);
        glutTimerFunc(70,moverObjeto,22);
    //FIN CLARA

    //INICIO PERRO
        glutTimerFunc(90,moverPata_1,23);
        glutTimerFunc(90,moverPata_2,24);
        glutTimerFunc(200,moverRodilla_Pierna1,25);
        glutTimerFunc(200,moverRodilla_Pierna2,26);
        glutTimerFunc(250,moverPierna3,27);
        glutTimerFunc(250,moverPierna4,28);
        glutTimerFunc(250,moverRodilla_Pierna3,29);
        glutTimerFunc(250,moverRodilla_Pierna4,30);
        glutTimerFunc(200,moverCuello1_1,31);
    //FIN DE PERRO
    //glutSpecialUpFunc(releaseKey1);

    //INICIO_TELLO
    glutTimerFunc(500,rotarRueda,33);
    //FIN TELLO
    glutKeyboardFunc(manejarTeclado);
    //INICIO DE ANTHONY
    glutKeyboardFunc(manejarTeclado);
    glutTimerFunc(200,moverNube,32);
     glutTimerFunc(300,moverCabezaAbeja,1);
    glutTimerFunc(90,moverAntenaDerecha,2);
    glutTimerFunc(90,moverAntenaIzquierda,3);
    glutTimerFunc(20,moverFlageloDerecho,4);
    glutTimerFunc(20,moverFlageloIzquierdo,5);
    glutTimerFunc(100,moverCola,6);
    glutTimerFunc(1,moverAlaIzquierda,7);
    glutTimerFunc(200,moverTorax,8);
    glutTimerFunc(200,moverPataAbeja1,30);
    glutTimerFunc(200,moverPataAbeja2,30);
    glutTimerFunc(200,moverPataAbeja3,30);
     glutTimerFunc(90,trasladarAbeja,40);
	glutMainLoop();

	return 1;
}
