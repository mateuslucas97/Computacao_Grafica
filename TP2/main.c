//todas as bibliotecas usadas neste projeto
#include <GL/glew.h>      // glew.h deve vir antes
#include <GL/freeglut.h>  // do freeglut.h
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//inclusão dos arquivos auxiliares para usar obj's e a musica de fundo
#include "glm.h"
#include "glmint.h"
#include "musica.h"

//variaveis globais para elemento da cena
int mostraCamera = 1;                 //variavel para configurar a camera
int iluminacao = 0;                   //variavel para ativar a iluminação
int mudaanimal;                       //para trocar de camera de animal
int limiteanimal = 2;                 //variavel de controle para configurar a colisão
//variaveis para configurar a fonte de iluminação
GLfloat lPos[4]={0.00, 0.00, 0.00, 1.00 };
GLfloat lKa[4]={0.00, 0.5, 0.00, 1.00};
GLfloat lKd[4]={0.5, 0.5, 0.5, 1.00};
GLfloat lKs[4]={1.00, 1.00, 1.00, 1.00};
GLfloat mKd[4]={0,0,0,1};
GLfloat mKs[4]={0,0,0,1};
GLfloat mKe[4]={0,0,0,1};
float matAmbAndDif[4] = {1.0, 1.0, 1.0, 1.0};    //vetor cor ambiente e difusa: branca
float matShine[] = {5};                       // expoente especular (shininess)
float m = 0.2;  //intensidade da luz global
float globAmb[] = { 0.2, 0.2, 0.2, 1.0 };
float matSpec[] = { 1.0, 1.0, 1,0, 1.0 };       // cor especular: branca
 
//estrutura de dados para cada objeto da cena
//para os bichos com uma variavel para configura o angulo de visão
typedef struct b{
	float x,y,z;
	double angulo;

}bichos;
//para o celeiro
typedef struct c{
	int x,y,z;
}celeiro;
//para o chão 
typedef struct ch{
	int x,y,z;
}chao;
//para a camera e vetores de deslocamento para cada bicho
struct camera{
	float x, y, z;
}camera, vetor, vetor2;

//variaveis para controlar a camera com o ponteiro do mouse e variaveis para configurar a camera usando coordenadas esfericas
int xMouse = 0, yMouse = 0;
float phi = 90, teta = 0;

//variaveis para usar a importação de OBJ's e instancias das estruturas de dados dos objetos da cena
GLMmodel *vacaModel = NULL;
GLMmodel *celeiroModel = NULL;
GLMmodel *chaoModel = NULL;
GLMmodel *cercaModel = NULL;
GLMmodel *ceuModel = NULL;
bichos vacas;
bichos vacas2;
celeiro c;
chao ch;

//callback para desenhar uma vaca via OBJ
void desenhaVaca(bichos vaca){
	glTranslatef(vaca.x, vaca.y, vaca.z);
	glRotatef(vaca.angulo*180/M_PI, 0, 1, 0);
    glScalef(35/2, 25/2, 35/2); //tamanho da vaca
	if(!vacaModel){
        vacaModel = glmReadOBJ("./Cow/Obj/Cow.obj");
        glmScale(vacaModel, 200.0);
        if(!vacaModel)
            exit(0);
        glmUnitize(vacaModel);
        glmFacetNormals(vacaModel);
        glmVertexNormals(vacaModel, 90.0, 1);   //(model, angle, bool keep_existing)
    } 
//    glScalef(0.01, 0.01, 0.01);
    glmDraw(vacaModel, GLM_SMOOTH | GLM_TEXTURE | GLM_COLOR);
}

//callback para desenhar o celeiro
void desenhaCeleiro(celeiro c){
	if(!celeiroModel){
        celeiroModel = glmReadOBJ("./Red_Barn_15_PBR/Textures/textures/Rbarn15.obj");
        glmScale(celeiroModel, 200.0);
        if(!celeiroModel)
            exit(0);
        glmUnitize(celeiroModel);
        glmFacetNormals(celeiroModel);
        glmVertexNormals(celeiroModel, 90.0, 1);   //(model, angle, bool keep_existing)
    } 
//    glScalef(0.01, 0.01, 0.01);
    glmDraw(celeiroModel, GLM_SMOOTH | GLM_TEXTURE | GLM_COLOR);
}

//callback para desenhar o terreno
void desenhaChao(chao ch){
    glTranslatef(0,23,0);
	glScalef(100, 100, 100);
	if(!chaoModel){
        chaoModel = glmReadOBJ("./3DS - The Legend of Zelda Ocarina of Time 3D - Hyrule Field/untitled.obj");
        glmScale(chaoModel, 200.0);
        if(!chaoModel)
            exit(0);
        glmUnitize(chaoModel);
        glmFacetNormals(chaoModel);
        glmVertexNormals(chaoModel, 90.0, 1);   //(model, angle, bool keep_existing)
    } 
//    glScalef(0.01, 0.01, 0.01);
    glmDraw(chaoModel, GLM_SMOOTH | GLM_TEXTURE | GLM_COLOR);
}

//callback para desenhar a cerca
void desenhaCerca(){
    glTranslatef(90, -115, -250);
    glScalef(90, 45, 200); //tamanho da cerca
	if(!cercaModel){
        cercaModel = glmReadOBJ("./Fence/fobj_fence.obj");
        glmScale(cercaModel, 200.0);
        if(!cercaModel)
            exit(0);
        glmUnitize(cercaModel);
        glmFacetNormals(cercaModel);
        glmVertexNormals(cercaModel, 90.0, 1);   //(model, angle, bool keep_existing)
    } 
//    glScalef(0.01, 0.01, 0.01);
    glmDraw(cercaModel, GLM_SMOOTH | GLM_TEXTURE | GLM_COLOR);
}

//callback para desenhar o ceu
void desenhaCeu(){
    glTranslatef(90, -115, -250);
    glScalef(4000, 4000, 4000); //tamanho da cerca
	if(!ceuModel){
        ceuModel = glmReadOBJ("./Ceu/TP2Sphere.obj");
        glmScale(ceuModel, 200.0);
        if(!ceuModel)
            exit(0);
        glmUnitize(ceuModel);
        glmFacetNormals(ceuModel);
        glmVertexNormals(ceuModel, 90.0, 1);   //(model, angle, bool keep_existing)
    } 
//    glScalef(0.01, 0.01, 0.01);
    glmDraw(ceuModel, GLM_SMOOTH | GLM_TEXTURE | GLM_COLOR);
}

//esta callback configura a camera usando o conceito de coordenadas esfericas
void posicionaCamera(int x, int y){
	double xMudanca, yMudanca;
	xMudanca = x - xMouse;
	yMudanca = y - yMouse;

	teta += xMudanca/150;
	phi-= yMudanca/150;

	if(phi >= 180){
		phi = 180;
	}

	xMouse = x;
	yMouse = y;
}

//esta callback sorteia um vetor de velocidade aleatorio para as vacas
void sorteiaVetor(char a, struct camera *v){
    v->z= 0.05+(rand() % 50)/60;
    v->x= 0.05+(rand() % 50)/60;
}

//callback para ativar ou desativar a iluminação (produz um efeito proximo de dia/noite)
void ilumina(){
    if(iluminacao == 1){
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT_MODEL_AMBIENT);
    }
    else
    {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT_MODEL_AMBIENT);
    }
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);
}

/*callback de animação das vacas
	aqui construimos um algoritmo para a nimação das vacas,
	quando as vacas estão andando e chegam nos limites da cerca
	um novo vetor de deslocamento é gerado, depois calculamos um novo
	angulo de visão para a vaca e camera mudarem de orientação ao bater
	na cerca
*/
void interacao(bichos *vaca, struct camera *v){

	double modulo = sqrt(pow(v->x,2) + pow(v->z,2));	//vetor unitario para a nova direção
	double aux_x = v->x/modulo; 						//variavel para armazenar o vetor de nova direção
	vaca->angulo = asin(aux_x);							//apontamos para a direção oposta do vetor de direção

	//toda a logica de colisão e mudança de direção, feit nos eixos X e Z
	if(v->z <0){
		vaca->angulo+= 180;
	}

    if(vaca->z > -163){
        if(v->z < 0){
            sorteiaVetor('z', v);
        v->z*= 1 ;
        }
        else{
            sorteiaVetor('z', v);
        v->z*= -1;
        }
        vaca->z = -164;
    }
    if(vaca->z < -398){
        if(v->z > 0){
            sorteiaVetor('z', v);
        v->z*= -1;
        }
        else{
            sorteiaVetor('z', v);
        v->z*= 1 ;
        }
        vaca->z = -397;
    }
    if(vaca->x > 163){
        if(v->x < 0){
            sorteiaVetor('x', v);
        v->x*= 1 ;
        }
        else{
        sorteiaVetor('x', v);
        v->x*= -1;
        }
        vaca->x = 162;
    }
    if(vaca->x < 23){
        if(v->x < 0){
            sorteiaVetor('x', v);
        v->x*= 1 ;
        }
        else{
        sorteiaVetor('x', v);
        v->x*= -1;
        }
        vaca->x = 24;
    }
    vaca->z += v->z;
    vaca->x += v->x;
}

//callback para carregar todos os elementos do jogo
void desenhaCena(){
    ilumina();						//o modelo de iluminação
    interacao(&vacas, &vetor);		//o modelo de comportamento da vaca nº1
    interacao(&vacas2, &vetor2);	//o modelo de comportamento da vaca nº2

    //variaveis da camera para todos os eixos (mais uma vez, o lance de coordenadas esfericas)
	camera.x = 100*sin(phi)*cos(teta);
	camera.z = 100*sin(phi)*sin(teta);
	camera.y = 100*cos(phi);

	//funções de inicialização do OpenGL
	glEnable(GL_TEXTURE_2D);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//configuração das cameras da cena
    switch(mostraCamera){
        case 1:				//a canera estática da cena
            gluLookAt(0.0, 0.0, 300.0,
			  	      0.0, 0.0, 0.0,
			          0.0, 1.0, 0.0);
              break;
        case 2:				//camera que fica nas vacas, elas se deslocam juntas
            switch (mudaanimal){
                case 1:
                gluLookAt(vacas.x,vacas.y+10,vacas.z+35, camera.x+vacas.x, camera.y+vacas.y+10, camera.z+vacas.z+35, 0,1,0);
                break;
                case 2:
                gluLookAt(vacas2.x,vacas2.y+10,vacas2.z+35, camera.x+vacas2.x, camera.y+vacas2.y+10, camera.z+vacas2.z+35, 0,1,0);
                break;
            }
            break;
        case 3:		//camera do mundo em pespecctiva esferica
        gluLookAt(camera.x*10, camera.y*10,camera.z*10,0,0,0,0,1,0);
        break;

    }
    glColor4f(0,0,0,0);
    //carrega o ceu
    glPushMatrix();
    desenhaCeu();
    glPopMatrix();

    //carrega a vaca nº1
	glPushMatrix();
    desenhaVaca(vacas);
	glPopMatrix();

	//carrega a vaca nº2
    glPushMatrix();
    desenhaVaca(vacas2);
    glPopMatrix();

    //carrega o celeiro
	glPushMatrix();
	glTranslatef(10, -100 ,10); //posicão do celeiro
	glScalef(80, 80, 80); //tamanho do celeiro
	desenhaCeleiro(c);
	glPopMatrix();

	//carrega o terreno
	glPushMatrix();
	glTranslatef(0, -1300 ,-400); //posicão do chao
	glScalef(80, 80, 80); //tamanho do chao
	desenhaChao(ch);
	glPopMatrix();

	//carrega a cerca
    glPushMatrix();
    desenhaCerca();
    glPopMatrix();

	glutSwapBuffers();
}

//teclas de ação da cena
void specialKeys(unsigned char key, int x, int y){
	switch(key) {
    case 27:      // Tecla "ESC"
        exit(0);  // Sai da aplicação
        break;  
    case '1':				//tecla 1
        mostraCamera = 1;	//mostra a camera estática
        break;
    case '2':				//tecla 2
        mostraCamera = 2;	//mostra a camera da vaca nº1
        break;
    case'3':                //tecla 3
    mostraCamera = 3;		//mostra a cemra global
    case 'c':      			//tecla "c" mosrtra a camera da outra vaca
        mudaanimal++;
        if(mudaanimal > limiteanimal)
        mudaanimal = 1;
        break;
    case 'l':					//tecla "l"
        if(iluminacao == 0)		//ativa/desativa a luz da cena
        iluminacao = 1;
        else
        {
            iluminacao = 0;
        }
        
         default:
        break;
    }
}

//callback para desenhar cada frame de animação
void atualizaFrame(int frame){
    glutPostRedisplay();
    glutTimerFunc(16, atualizaFrame, 0);
}

//callback de proporção do tamanho da tela
void redimensionada(int width, int height) {
    int razao= 16/9;
    width= razao* height;
   glViewport(0, 0, 1920, 1080);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, 16.0f/9.0f, 0.2, 10350.0);

   glMatrixMode(GL_MODELVIEW);
}

//callback para inicializar todos os objetos da cena
void inicializa(){
	//para associar um material para cada objeto e aplicar a iluminação
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mKd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mKs);
    glMaterialfv(GL_FRONT, GL_EMISSION, mKe);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    //para gerar uma velociade aleatoria para as vacas
    srand(time(0));
    //incializa cada varial com um valor e posição iniciais
    mudaanimal = 1;
    vetor.x = 0.5;
    vetor.z = 0.5;
    vetor2.x = -0.5;
    vetor2.z = -0.5;
	vacas.x = 73, vacas.y = -103, vacas.z = -336;
    vacas2.x = 73, vacas2.y = -103, vacas2.z = -336;
    vacas.angulo = 0, vacas2.angulo = 0;

    /*!!!!EASTER EGG ALLERT!!!
    para tocar uma música de fundo
    */
    tocar_musica("./RomaniRanch.ogg", -1);
}

//função principal
int main(int argc, char** argv) {

   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
   glutInitWindowSize(1600, 900);
   glutCreateWindow("Fazenda");
   glEnable(GL_DEPTH_TEST);
   glClearColor(1, 1, 1, 1); // branco
   glutDisplayFunc(desenhaCena);
   glutKeyboardFunc(specialKeys);
   glutReshapeFunc(redimensionada);

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glutSetCursor(GLUT_CURSOR_NONE);

   glutTimerFunc(0, atualizaFrame, 0);
   glutPassiveMotionFunc(posicionaCamera);
   inicializa();
   glutMainLoop();
   return 0;  
}