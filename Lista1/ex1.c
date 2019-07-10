#include <GL/glew.h>      // glew.h deve vir antes
#include <GL/freeglut.h>  // do freeglut.h

// callback de desenho (display)
void desenhaMinhaCena() {
    glClear(GL_COLOR_BUFFER_BIT);
   

    // desenha um POLYGON por seus vértices
      
    
    for(int i =0; i < 3; i++){
       for(int j = 0; j < 3; j++){
         glColor3f(0.8*i, 1.5*j, 0.2*i);
        // NOVIDADE: antes os valores eram -0.5, 0.5 
     glBegin(GL_TRIANGLE_STRIP);
        glVertex3f((40*i)+10, (40*j)+10, 0);
        glVertex3f((40*i)+40, (40*j)+10, 0);
         glVertex3f((40*i)+10, (40*j)+40, 0);
        glVertex3f((40*i)+40, (40*j)+40, 0);
        glEnd();
       }
       
      }
   
    glFlush();
    
}

// NOVIDADE: uma função que vamos chamar dentro
//    do "main"
// Inicia algumas variáveis de estado do OpenGL
void inicializa() {
    // define qual é a cor do fundo
    glClearColor(1, 1, 1, 1); // branco

    // desenho preenchido vs. contorno
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

// NOVIDADE: callback para o evento "reshape"
void redimensionada(int width, int height) {
   glViewport(0, 0, width, height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, 140, 0, 140, -1, 1);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

// NOVIDADE: callback de "keyboard"
void teclaPressionada(unsigned char key, int x, int y) {
    // vê qual tecla foi pressionada
    switch(key) {
    case 27:      // Tecla "ESC"
        exit(0);  // Sai da aplicação
        break;
    default:
        break;
    }
}

// função principal
int main(int argc, char** argv) {
   glutInit(&argc, argv);

   glutInitContextVersion(1, 1);
   glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100);

   glutCreateWindow("Exercicio 1");

   // registra callbacks para alguns eventos
   glutDisplayFunc(desenhaMinhaCena);
   glutReshapeFunc(redimensionada);  
   glutKeyboardFunc(teclaPressionada);

   // configura valor inicial de algumas
   // variáveis de estado do OpenGL
   inicializa();

   glutMainLoop();
   return 0;
}
