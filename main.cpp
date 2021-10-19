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

#define PASSO 1     //MOSTRA O QUANTO O QUADRADO SE MOVIMENTA NO PLANO CARTESIANO
#define ESPESSURA 3 //ESPESSURA DA PAREDE DO LABIRINTO

GLfloat ro,go,bo; //RGB DO QUADRADRO
GLfloat rl,gl,bl; //RGB DAS PAREDES DO LABIRINTO

int max_verticais = 14;
int max_horizontais = 18;
int vetx[68] = {0,10,10,0,0,20,20,0,20,50,50,20,20,50,50,20,60,90,90,60,100,120,120,
                100,60,90,90,60,0,20,20,0,20,50,50,20,0,10,10,0,0,10,10,0,20,90,90,
                20,60,90,90,60,60,120,120,60,100,120,120,100,100,120,120,100,100,120,120,100};
int vety[68] = {0,0,20,20,30,30,45,45,10,10,0,0,45,45,20,20,10,10,0,0,20,20,0,0,65,
                65,20,20,55,55,70,70,55,55,90,90,80,80,100,100,120,120,110,110,110,
                110,100,100,100,100,75,75,65,65,55,55,45,45,30,30,120,120,110,110,100,100,75,75};

int vidas = 3;
int cont =0;            //VARIAVEL USADA PARA CONTROLAR A MUDANÇA DE COR DO FUNDO DO LABIRINTO
char winLose[15] = " "; //MENSAGEM DE VITORIA/DERROTA

float Pessoa[4][2]    =  {{2,23},
                        {8,23},
                        {8,26},
                        {2, 26}};





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
    gluOrtho2D(0,120,0,135);
    ro=0.04; go=0.75; bo=0.0;
    rl=0; gl=0; bl=0;

}
void Desenha(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(ro, go, bo);
    //QUARTEIRÕES
    for(int i=0; i<68; i=i+4){
        glBegin(GL_QUADS);
            glVertex2f(vetx[i],vety[i]); // A(2,19)
            glVertex2f(vetx[i+1],vety[i+1]); // B(12,19)
            glVertex2f(vetx[i+2],vety[i+2]); // C(12,29)
            glVertex2f(vetx[i+3],vety[i+3]); // D(2,29)
        glEnd();

    }
    glColor3f(0.3,0.3 ,0.3 );
    glBegin(GL_QUADS);
        glVertex2f(0,135); // A(2,19)
        glVertex2f(120,135); // B(12,19)
        glVertex2f(120,120); // C(12,29)
        glVertex2f(0, 120); // D(2,29)
    glEnd();

     //posto 1
     glColor3f(0.0,1.0 ,2.5 );
    glBegin(GL_QUADS);
        glVertex2f(100,90); // A(2,19)
        glVertex2f(105,90); // B(12,19)
        glVertex2f(105,80); // C(12,29)
        glVertex2f(100, 80); // D(2,29)
    glEnd();
    //PESSOA
    glColor3f(rl, gl, bl);
    glBegin(GL_QUADS);
        glVertex2f(Pessoa[0][0],Pessoa[0][1]);
        glVertex2f(Pessoa[1][0],Pessoa[1][1]);
        glVertex2f(Pessoa[2][0],Pessoa[2][1]);
        glVertex2f(Pessoa[3][0],Pessoa[3][1]);
    glEnd();

    glFlush();
}
bool vacinou(void){
    if((Pessoa[1][0] >=105 && Pessoa[1][1]>=80 && Pessoa[1][0]<= 110  && Pessoa[1][1] <= 87))
        return true;
    return false;
}

bool colisaoVertical(void){

    for (int i=0; i<68; i++){
        if(Pessoa[0][1] > vety[i]){
            return true;
        }
    }
        return false;
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
    switch(key){
        case GLUT_KEY_UP:
            for(int i= 0; i < 4; i++)
                Pessoa[i][1]+=PASSO;
                if(vacinou())
                    printf("\Vacinou\n");

        break;
        case GLUT_KEY_DOWN:

            strcpy(winLose, " ");
            for(int i= 0; i < 4; i++)
                Pessoa[i][1]-=PASSO;
                if(vacinou())
                    printf("\Vacinou\n");

        break;
        case GLUT_KEY_LEFT:
            strcpy(winLose, " ");
            if(Pessoa[0][0] < -5)
            {
                Pessoa[0][0]=120;
                Pessoa[1][0]=126;
                Pessoa[2][0]=126;
                Pessoa[3][0]=120;
            }
            for(int i= 0; i < 4; i++)
                Pessoa[i][0]-=PASSO;
                if(vacinou())
                    printf("\Vacinou\n");
        break;
        case GLUT_KEY_RIGHT:
            strcpy(winLose, " ");
            for(int i= 0; i < 4; i++)
                Pessoa[i][0]+=PASSO;
                if(vacinou())
                    printf("\Vacinou\n");
        break;
    }
    glutPostRedisplay();
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
