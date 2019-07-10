#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
int vezes=2;
int numLados=50;
float r=0.01;

void defineCor(int n){
    if(n==1){
        glColor3f(0.5, 0.8, 0.2); //verde
    }else{
        glColor3f(0, 0, 0); //preto
    }
}

void ladosPoligono(int n){
    double t=0.0;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_STRIP);
    for(int i=0;i<40*n;i++){
    r += 0.001;
        glVertex3f((0.5+r*cos(t)),(0.5+r*sin(t)), 0);
        t+=2*M_PI/numLados;
    }
    glEnd();
    glFlush();

}

void desenhaMinhaCena() {
    glClear(GL_COLOR_BUFFER_BIT);
    ladosPoligono(numLados);
}

void inicializar() {
    glClearColor(1, 1, 1, 1);
}

void redimensionada(int width, int height) {
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, 1, 0, 1, 1, -1);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void teclaPressionada(unsigned char key, int x, int y) {
    switch(key) {
    case 27:
        exit(0);
        break;
    case '+':
        numLados++;
        ladosPoligono(numLados);
        break;
    case '-':
        if(numLados>3){
            numLados--;
            ladosPoligono(numLados);
        }
        break;
    case 99:
        if(vezes%2==0){
            glPolygonMode(GL_FRONT, GL_LINE);
            defineCor(0);
            ladosPoligono(numLados);
        }else
        {
            glPolygonMode(GL_FRONT, GL_FILL);
            defineCor(1);
            glutPostRedisplay();
        }
        vezes++;
        break;
    default:
        break;
    }
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);

   glutInitContextVersion(1, 1);
   glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100);

   glutCreateWindow("poligono regular");
   defineCor(1);
   glutDisplayFunc(desenhaMinhaCena);
   glutReshapeFunc(redimensionada);
   glutKeyboardFunc(teclaPressionada);

   inicializar();

   glutMainLoop();
   return 0;
}
