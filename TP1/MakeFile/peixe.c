#include <GL/glew.h>      // glew.h deve vir antes
#include <GL/freeglut.h>  // do freeglut.h
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <stdlib.h>


GLint texturaPeixe;

void carregaPeixes(){
	texturaPeixe = SOIL_load_OGL_texture(
    "peixe2.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y
  );

  if (texturaPeixe == 0) {
    printf("Erro carregando textura: '%s'\n", SOIL_last_result());
  }
}