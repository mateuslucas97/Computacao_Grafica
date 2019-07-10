#include <GL/glew.h>      // glew.h deve vir antes
#include <GL/freeglut.h>  // do freeglut.h
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <stdlib.h>
#include "peixe.h"

GLuint texturaCenario;
GLuint texturaCenario2;
GLuint texturaArpao;

int habilita = 1;
int linha = 0;
/*
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
    "cenario.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
  );

  if (texturaCenario == 0) {
    printf("Erro carregando textura: '%s'\n", SOIL_last_result());
  }
}
*/
void initCenario2() {
  texturaCenario2 = SOIL_load_OGL_texture(
    "cenario2.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
  );

  if (texturaCenario2 == 0) {
    printf("Erro carregando textura: '%s'\n", SOIL_last_result());
  }
}

void desenhaMinhaCena() {

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

    glBindTexture(GL_TEXTURE_2D, texturaCenario2);//carregar a textura da fase 2
    glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0, 0); glVertex3f( 0, 0,  0);
      glTexCoord2f(1, 0); glVertex3f( 100, 0,  0);
      glTexCoord2f(1, 1); glVertex3f( 100, 100,  0);
      glTexCoord2f(0, 1); glVertex3f( 0, 100,  0);
     glEnd();//fim do gl textur


  if(habilita == 1){
    //angulo++;
  }
  else if(habilita ==0){
    angulo--;
  }
  else if(habilita == 2){
    //linha += 3;
  }
  else{
    //linha = 0;
  }
  if(angulo <= -90){
     habilita = 1;
  }
  else if(angulo >= 90){ 
      habilita = 0;
  }
    
    glPushMatrix();
    glTranslatef(45 , 47, 0);
    glScalef(0.1, 0.1, 1);
    //glRotatef(angulo, 0, 0, 1);
    glPushMatrix();
    glLineWidth(1);

    //glBegin(GL_TRIANGLE_FAN)
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_LINES);
    glColor3f(0,0,0);
    //glVertex3f(0,-linha,0);
    glVertex3f(0,30 ,0);
    glEnd();
    
    //glTranslatef(0, -linha, 0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaArpao);//carregar a textura do Arpao
    glColor3f(1,1,1);
    glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0, 0); glVertex3f( -20, -20,  0);
      glTexCoord2f(1, 0); glVertex3f( 20, -20,  0);
      glTexCoord2f(1, 1); glVertex3f( 20, 20,  0);
      glTexCoord2f(0, 1); glVertex3f( -20, 20,  0);
      glEnd();
      glPopMatrix();
      glPopMatrix();

     glutSwapBuffers();
    
}
