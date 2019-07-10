#include <GL/glew.h>      // glew.h deve vir antes
#include <GL/freeglut.h>  // do freeglut.h
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "peixe.h"
#include "texturas.h"

// callback de desenho (display)
GLint texturaCenario;
GLint texturaBarco;
GLint texturaArpao;
GLint texturaPeixe;
GLint texturaPeixe2;
GLint texturaMenu;
GLint texturaFim;



int ponto;

int modo=1; //variavel para pausar o jogo
float angulo = 1;//variavel para fazer o arpao se moviental em pendulo
int habilita = 1;//variavel para parar o arpao e faze-lo se jogar em direcao ao peixe
float linha = 0;//varavel que vai desenahr  a linha do arpao

//struct que tem os dados das coordenadas do peixe
typedef struct peixe{
	GLint texturaPeixe;
	float x, y;
	float larg, alt;
}peixe;
//desenha o menu quando aperta p
void desenhaMenu(){
	glBindTexture(GL_TEXTURE_2D, texturaMenu);//carregar a textura da fase 1
     glBegin(GL_TRIANGLE_FAN);
       glTexCoord2f(0, 0); glVertex3f( 0, 0,  0);
       glTexCoord2f(1, 0); glVertex3f( 100, 0,  0);
       glTexCoord2f(1, 1); glVertex3f( 100, 100,  0);
       glTexCoord2f(0, 1); glVertex3f( 0, 100,  0);
     glEnd();//fim do gl texture
}


//funcao para desenhar o peixe em um ponto especifico
void desenhaPeixe(struct peixe p){
	glPushMatrix();
	glTranslatef(p.x, p.y, 0);
	glBindTexture(GL_TEXTURE_2D, texturaPeixe);//carregar a textura da fase 1
     glBegin(GL_TRIANGLE_FAN);
       glTexCoord2f(0, 0); glVertex3f(  - p.larg/2,  - p.alt/2,  0);
       glTexCoord2f(1, 0); glVertex3f(  + p.larg/2, - p.alt/2,  0);
       glTexCoord2f(1, 1); glVertex3f(  + p.larg/2,  + p.alt/2,  0);
       glTexCoord2f(0, 1); glVertex3f(  - p.larg/2,  + p.alt/2,  0);
     glEnd();//fim do gal texture
     glPopMatrix();  
}

void desenhaPeixe2(struct peixe p){
	glPushMatrix();
	glTranslatef(p.x, p.y, 0);
	glBindTexture(GL_TEXTURE_2D, texturaPeixe2);//carregar a textura da fase 1
     glBegin(GL_TRIANGLE_FAN);
       glTexCoord2f(0, 0); glVertex3f(  - p.larg/2,  - p.alt/2,  0);
       glTexCoord2f(1, 0); glVertex3f(  + p.larg/2, - p.alt/2,  0);
       glTexCoord2f(1, 1); glVertex3f(  + p.larg/2,  + p.alt/2,  0);
       glTexCoord2f(0, 1); glVertex3f(  - p.larg/2,  + p.alt/2,  0);
     glEnd();//fim do gal texture
     glPopMatrix();  
}

//struct que tem os dados das coordenadas do arpao
typedef struct arpao{
	GLint texturaArpao;
	float x, y;
	float xABS, yABS;
	float larg, alt;
}arpao;
//variaveis para testar a colisao do arpao com o peixe
arpao anzol;
peixe obj,obj3;
arpao debug;

int colidiu(struct arpao a, struct peixe p){
	if((a.x + a.larg/2 > p.x - p.larg/2) && (p.x + p.larg/2 > a.x - a.larg/2) && (a.y + a.alt/2 > p.y - p.alt/2) && (p.y + p.alt/2 > a.y - a.alt/2)){
		ponto++;
		habilita = 1;
		return 1;
	}
	if((p.x + p.larg/2 > a.x - a.larg/2) && (a.x + a.larg/2 > p.x - p.larg/2) && (p.y + p.alt/2 > a.y - a.alt/2) && (a.y + a.alt/2 > p.y - p.alt/2)){

	}
	if(ponto ==2){
	 printf("Voce ganhou!!!");
}
}
//desenha o arpao no centro da tela fazendo a rotacao e a translacao quando se aperta espaço
void desenhaArpao(struct arpao a){
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaArpao);
    glColor3f(1, 1, 1);
	   glPushMatrix();
	 glTranslatef(a.x, a.y, 0);
		glBindTexture(GL_TEXTURE_2D, texturaArpao);//carregar a textura do arpao
        glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex3f( - a.larg/2,  - a.alt/2,  0);
        glTexCoord2f(1, 0); glVertex3f( + a.larg/2,  - a.alt/2,  0);
        glTexCoord2f(1, 1); glVertex3f( + a.larg/2,  + a.alt/2,  0);
        glTexCoord2f(0, 1); glVertex3f( - a.larg/2,  + a.alt/2,  0);
      glEnd();//fim do gl texture
     glPopMatrix();
}
 
//esta funcao faz o calculo do arpao em relacao ao peixe com valores absolutos
void calculaABS(){
	if(angulo<=0){
	anzol.xABS= 45- abs(sin(angulo)*linha);
	anzol.yABS= 47- abs(cos(angulo)*linha);
	}
	else{
		anzol.xABS= 45+ abs(sin(angulo)*linha);
		anzol.yABS= 47- abs(cos(angulo)*linha);
	}
	debug.x = anzol.xABS;
	debug.y = anzol.yABS;
}

//carregar a textura do peixe
void initPeixe(){
  texturaPeixe = SOIL_load_OGL_texture(
    "peixepalhaco.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
  );

  if (texturaPeixe == 0) {
    printf("Erro carregando textura: '%s'\n", SOIL_last_result());
  }
}

void initPeixe2(){
  texturaPeixe2 = SOIL_load_OGL_texture(
    "peixerosa.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
  );

  if (texturaPeixe2 == 0) {
    printf("Erro carregando textura: '%s'\n", SOIL_last_result());
  }
}

//carrega a textura do arpao
void initArpao(){
  texturaArpao = SOIL_load_OGL_texture(
    "arpao.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
  );

  if (texturaArpao == 0) {
    printf("Erro carregando textura: '%s'\n", SOIL_last_result());
  }
}

void initCenario() {
  texturaCenario = SOIL_load_OGL_texture(
    "ococ.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
  );

  if (texturaCenario == 0) {
    printf("Erro carregando textura: '%s'\n", SOIL_last_result());
  }
}

//carrega a textura da faze 2
void initBarco() {
  texturaBarco = SOIL_load_OGL_texture(
    "barcotransparente.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
  );

  if (texturaBarco == 0) {
    printf("Erro carregando textura: '%s'\n", SOIL_last_result());
  }
}

//carrega textura do menu principal
void initMenu() {
  texturaMenu = SOIL_load_OGL_texture(
    "menu_principal.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
  );

  if (texturaMenu == 0) {
    printf("Erro carregando textura: '%s'\n", SOIL_last_result());
  }
}



 int xANZOL;

//funcao onde a magia acontece, aqui tambem tem as funcoes de colisao
//e do calculo da linha em relacao ao peixe
void desenhaJogo(){

	anzol.x = xANZOL;
	colidiu(anzol, obj);
	colidiu(anzol, obj3);
	calculaABS();

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);//fundo branco
    glEnable(GL_TEXTURE_2D);//pra começar a usar as texturas
     glBindTexture(GL_TEXTURE_2D, texturaCenario);//carregar a textura da fase 1
     glBegin(GL_TRIANGLE_FAN);
       glTexCoord2f(0, 0); glVertex3f( 0, 0,  0);
       glTexCoord2f(1, 0); glVertex3f( 100, 0,  0);
       glTexCoord2f(1, 1); glVertex3f( 100, 100,  0);
       glTexCoord2f(0, 1); glVertex3f( 0, 100,  0);
     glEnd();//fim do gl texture  

    glPushMatrix();
    	glTranslatef(xANZOL , 47, 0);
    	//glScalef(0.5, 0.5, 1);
   
    glBindTexture(GL_TEXTURE_2D, texturaBarco);//carregar a textura do
    glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0, 0); glVertex3f( 0, 0,  0);
      glTexCoord2f(1, 0); glVertex3f( 45/2, 0,  0);
      glTexCoord2f(1, 1); glVertex3f( 45/2, 47/2,  0);
      glTexCoord2f(0, 1); glVertex3f( 0, 47/2,  0);
     glEnd();//fim do gl textura
    glPopMatrix();
    
    
  //animacao do efeito pendulo, a variavel habilita serve para habilitar a animacao
  // a variavel angulo é o limite de variacao do efeito pendulo
  if(habilita == 1){
 //   angulo++;
  	anzol.y += 0.9;
  	if(anzol.y >= 47){
  		habilita = 0.3;
  	}
  }
  else if(habilita ==0){
   // angulo--;
  }
  else if(habilita == 2){
    anzol.y -= 0.3;
    if(anzol.y < 0){
    	habilita = 1;
    } //se nao estiver em nenhuma das extremidades lança o arpao
  }
  else{
    linha = 0; //se estuver
  }
  if(angulo <= -90){
     habilita = 1;
  }
  else if(angulo >= 90){ 
      habilita = 0; //se nao estiver nas estremidades para a movimentacao e lança o       	
  }

    //faz a rotacao e a translacao do arpao quando se aperta espaco   
    glPushMatrix();
    	glTranslatef(45 , 47, 0);
    	glScalef(0.5, 0.5, 1);
    	glRotatef(angulo, 0, 0, 1);
    	glPushMatrix();
    	glLineWidth(1);

    //desenha a linha do anzol quando se aperta o espaco em cima do arpao
    	glDisable(GL_TEXTURE_2D);
    //	glBegin(GL_LINES);
    //	glColor3f(0,0,0);
    //	glVertex3f(xANZOL,-linha*10,0);
    //	glVertex3f(xANZOL,30 ,0);
    //	glEnd();
    	glPopMatrix();
    glPopMatrix();
    
    desenhaArpao(anzol);
    desenhaPeixe(obj);
    desenhaPeixe2(obj3);
    colidiu(anzol, obj);
    colidiu(anzol, obj3);
}


// callback de desenho (display)
//faz o pause do jogo
void desenhaMinhaCena() {
	switch(modo){
		case 0:
		desenhaMenu();
			break;
		case 1:
			desenhaJogo();
			break;
	}
     glutSwapBuffers();   
}

//callback para o evento "reshape"
void redimensionada(int width, int height) {
    int razao= 16/9;
    width= razao* height;
   glViewport(0, 0, width, height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0,  100, 0,  100, -1, 1);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

//faz a corda ser denhada a 60fps
void atualizaFrame(int frame){
    glutPostRedisplay();
    glutTimerFunc(16, atualizaFrame, 0);
}

void inicializa() {
	//inicia as texturas
   initMenu();
   initArpao();
   initCenario();
   initBarco();
   initPeixe();
   initPeixe2();
   //initFim();
   anzol.larg = 4;
   anzol.alt = 4;
   anzol.x = 45;
   anzol.y = 47;
   linha=0;
   angulo=0;
   habilita=1;
   anzol.xABS= 45;
   anzol.yABS= 47;
   obj.x = 15;
   obj.y = 30;
   obj.larg= 6;
   obj.alt= 6;

   obj3.x = 60;
   obj3.y = 30;
   obj3.larg= 12;
   obj3.alt= 6;
   
   debug.alt = 4;
   debug.larg = 4;
   xANZOL =45;

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
   glClearColor(1, 1, 1, 1); // branco
}

//callback de "keyboard"
void teclaPressionada(unsigned char key, int x, int y) {
    // vê qual tecla foi pressionada
    switch(key) {
    case 27:      // Tecla "ESC"
        exit(0);  // Sai da aplicação
        break;  
    case' ':         //tecla espaço
        habilita = 2;//lança o arpao
        break;
    case'p':
    case 'P':               //tecla p
    	if(modo==0) modo=1; //pausa o jogo
    	else modo=0;
    break;	
    case 'R':               //tecla r
    case 'r':               // reinicia o jogo
    inicializa();
    break;
    case 'a':
    case 'A':
    if(xANZOL > 0 ){
    	xANZOL--;
    }
    break;
    case 'd':
    case 'D':
    if(xANZOL < 100){
    	xANZOL++;
    }
    default:
        break;
    }

}

// função principal
int main(int argc, char** argv) {
   glutInit(&argc, argv);

   glutInitContextVersion(1, 1);
   glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
   glutInitWindowSize(800, 600);
   glutInitWindowPosition(100, 100);

   glutCreateWindow("Pescaria");

   // registra callbacks para alguns eventos
   glutDisplayFunc(desenhaMinhaCena);
   glutReshapeFunc(redimensionada);
   glutKeyboardFunc(teclaPressionada);
   
   // configura valor inicial de algumas
   // variáveis de estado do OpenGL
   inicializa();
   glutTimerFunc(0, atualizaFrame, 0);
   glutMainLoop();
   return 0;
   }

