/**
    UNIVERSIDADE FEDERAL DO VALE DO SAO FRANCISCO
    DISCIPLINA: COMPUTACAOO GRAFICA  TURMA: 2020.2
    PROFESSOR:  JORGE CAVALCANTE
    ALUNOS:     JOSE WESLLES
                MATHEUS ADHONNAY
                RAYANNE CAROLINE
*/

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <gl/glut.h>
#include <time.h>

//CORES USADAS NO FUNDO DO LABIRINTO
#define AZUL     0.25, 0.25, 0.5, 1.0
#define VERMELHO 1.65, 0.0, 0.0, 1.0
#define VERDE  0.0, 0.5, 0.0, 1.0
#define CINZA    0.5,0.5, 0.5, 1.0

#define PASSO 0.5     //MOSTRA O QUANTO O QUADRADO SE MOVIMENTA NO PLANO CARTESIANO
#define ESPESSURA 3 //ESPESSURA DA PAREDE DO LABIRINTO

GLfloat ro,go,bo; //RGB DO QUADRADRO
GLfloat rl,gl,bl; //RGB DAS PAREDES DO LABIRINTO

int max_verticais = 14;
int max_horizontais = 18;

int vidas = 3;
int cont =0;            //VARIAVEL USADA PARA CONTROLAR A MUDANÇA DE COR DO FUNDO DO LABIRINTO
char winLose[15] = " "; //MENSAGEM DE VITORIA/DERROTA




void Inicializa(void);
void Desenha(void);
bool colisaoVertical(void);
bool colisaoHorizontal(void);
void teclado(unsigned char , int , int );
void TecladoEspecial(int , int , int );
void Mouse(int , int ,int , int );
void DesenhaTexto(char *);

int main(int argc, char *argv[]){

    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400,400);
    glutCreateWindow("Atravessando o Labirinto");
    glutDisplayFunc(Desenha);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(TecladoEspecial);
    glutMouseFunc(Mouse);
    Inicializa();
    glutMainLoop();
}

void Inicializa (void){
    printf("\n-----------------------\n");
    printf("BEM VINDO AO LABIRINTO!!");
    printf("\n-----------------------\n");
    printf("Voce comeca com %d vidas.\n", vidas);
    glClearColor(CINZA);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,120,0,120);
    ro=0.04; go=0.75; bo=0.0;
    rl=0; gl=0; bl=0;

}

void Desenha(void){
    glClear(GL_COLOR_BUFFER_BIT);

    //DESENHA UM QUADRADO DENTRO DO LABIRINTO
    glColor3f(ro, go, bo);
    //figura 1
    glBegin(GL_QUADS);
        glVertex2f(0,0); // A(2,19)
        glVertex2f(10,0); // B(12,19)
        glVertex2f(10,20); // C(12,29)
        glVertex2f(0,20); // D(2,29)
    glEnd();

    //figura 2
    glBegin(GL_QUADS);
        glVertex2f(0,30); // A(2,19)
        glVertex2f(20,30); // B(12,19)
        glVertex2f(20,45); // C(12,29)
        glVertex2f(0,45); // D(2,29)
    glEnd();
    //figura 3
    glBegin(GL_QUADS);
        glVertex2f(20,10); // A(2,19)
        glVertex2f(50,10); // B(12,19)
        glVertex2f(50,0); // C(12,29)
        glVertex2f(20,0); // D(2,29)
    glEnd();
   //figura 4
    glBegin(GL_QUADS);
        glVertex2f(20,45); // A(2,19)
        glVertex2f(50,45); // B(12,19)
        glVertex2f(50,20); // C(12,29)
        glVertex2f(20,20); // D(2,29)
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(60,10); // A(2,19)
        glVertex2f(90,10); // B(12,19)
        glVertex2f(90,0); // C(12,29)
        glVertex2f(60,0); // D(2,29)
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(100,20); // A(2,19)
        glVertex2f(120,20); // B(12,19)
        glVertex2f(120,0); // C(12,29)
        glVertex2f(100,0); // D(2,29)
    glEnd();

    //figura 7
    glBegin(GL_QUADS);
        glVertex2f(60,65); // A(2,19)
        glVertex2f(90,65); // B(12,19)
        glVertex2f(90,20); // C(12,29)
        glVertex2f(60,20); // D(2,29)
    glEnd();
    //figura 8
    glBegin(GL_QUADS);
        glVertex2f(0,55); // A(2,19)
        glVertex2f(20,55); // B(12,19)
        glVertex2f(20,70); // C(12,29)
        glVertex2f(0,70); // D(2,29)
    glEnd();
    //figura 9
    glBegin(GL_QUADS);
        glVertex2f(20,55); // A(2,19)
        glVertex2f(50,55); // B(12,19)
        glVertex2f(50,90); // C(12,29)
        glVertex2f(20,90); // D(2,29)
    glEnd();

     //figura 10
    glBegin(GL_QUADS);
        glVertex2f(0,80); // A(2,19)
        glVertex2f(10,80); // B(12,19)
        glVertex2f(10,100); // C(12,29)
        glVertex2f(0,100); // D(2,29)
    glEnd();
    //figura 11
    glBegin(GL_QUADS);
        glVertex2f(0,120); // A(2,19)
        glVertex2f(10,120); // B(12,19)
        glVertex2f(10,110); // C(12,29)
        glVertex2f(0,110); // D(2,29)
    glEnd();

    //figura 12
    glBegin(GL_QUADS);
        glVertex2f(20,110); // A(2,19)
        glVertex2f(90,110); // B(12,19)
        glVertex2f(90,100); // C(12,29)
        glVertex2f(20,100); // D(2,29)
    glEnd();
    //figura 13
    glBegin(GL_QUADS);
        glVertex2f(60,100); // A(2,19)
        glVertex2f(90,100); // B(12,19)
        glVertex2f(90,75); // C(12,29)
        glVertex2f(60,75); // D(2,29)
    glEnd();
    //figura 14
     glBegin(GL_QUADS);
        glVertex2f(60,65); // A(2,19)
        glVertex2f(120,65); // B(12,19)
        glVertex2f(120,55); // C(12,29)
        glVertex2f(60,55); // D(2,29)
    glEnd();
    //figura 15
     glBegin(GL_QUADS);
        glVertex2f(100,45); // A(2,19)
        glVertex2f(120,45); // B(12,19)
        glVertex2f(120,30); // C(12,29)
        glVertex2f(100, 30); // D(2,29)
    glEnd();
    //figura 16
    glBegin(GL_QUADS);
        glVertex2f(100,120); // A(2,19)
        glVertex2f(120,120); // B(12,19)
        glVertex2f(120,110); // C(12,29)
        glVertex2f(100, 110); // D(2,29)
    glEnd();
    //figura 17
    glBegin(GL_QUADS);
        glVertex2f(100,100); // A(2,19)
        glVertex2f(120,100); // B(12,19)
        glVertex2f(120,75); // C(12,29)
        glVertex2f(100, 75); // D(2,29)
    glEnd();
    //posto de vacinação
    //posto 1
     glColor3f(0.0,1.0 ,2.5 );
    glBegin(GL_QUADS);
        glVertex2f(100,90); // A(2,19)
        glVertex2f(105,90); // B(12,19)
        glVertex2f(105,80); // C(12,29)
        glVertex2f(100, 80); // D(2,29)
    glEnd();


    // INSERE STRING VAZIA NO CANTO SUPERIOR DIREITO DO LABIRINTO
     glColor3f(0.0f,0.0f,0.0f);
     DesenhaTexto(winLose);
     glutSwapBuffers();

    glFlush();
}

bool colisaoVertical(void){

        return true;
}

bool colisaoHorizontal(void){

        return true;
}

void teclado(unsigned char key, int x, int y){
    switch (key) {
            case 27:
                system("cls");
                printf("\n-----------------------\n");
                printf("SENTIREMOS SUA FALTA!!");
                printf("\n-----------------------\n");
                exit(0);
                break;
    }
    glutPostRedisplay();
}

void TecladoEspecial(int key, int x, int y){


}

void Mouse(int button, int state,int x, int y){
    if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_DOWN){

            //MUDAN�A DE COR DO OBJETO


            //MUDAN�A DE COR DAS LINHAS DO LABIRINTO


            //MUDAN�A DE COR DO FUNDO DO LABIRINTO
            switch (cont){
                case 0:

                    cont++;
                    break;
                case 1:

                    cont++;
                    break;

                case 2:

                    cont++;
                    break;

                case 3:

                    cont =0;
                    break;

               }
            glutPostRedisplay();
        }
    }
}

void DesenhaTexto(char *string){
  	glPushMatrix();
        // Posição no universo onde o texto será colocado
        glRasterPos2f(70,125);
        // Exibe caracter a caracter
        while(*string)
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*string++);
	glPopMatrix();
}
