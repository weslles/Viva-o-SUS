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

//COR DA PISTA
#define CINZA    0.5,0.5, 0.5, 1.0

#define PASSO 1     //MOSTRA O QUANTO O QUADRADO SE MOVIMENTA NO PLANO CARTESIANO


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
int cont =0;            //VARIAVEL USADA PARA CONTROLAR A MUDAN�A DE COR DO FUNDO DO LABIRINTO
char vacinado[15] = " "; //MENSAGEM DE VITORIA/DERROTA

float Pessoa[4][2]    =  {{2,23},
                        {8,23},
                        {8,26},
                        {2, 26}};
float PessoaAux[4][2]    =  {{2,23},
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
void criarMenu();

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
    //QUARTEIROES
    for(int i=0; i<68; i=i+4){
        glBegin(GL_QUADS);
            glVertex2f(vetx[i],vety[i]);
            glVertex2f(vetx[i+1],vety[i+1]); 
            glVertex2f(vetx[i+2],vety[i+2]); 
            glVertex2f(vetx[i+3],vety[i+3]); 
        glEnd();

    }
    glColor3f(0.3,0.3 ,0.3 );
    glBegin(GL_QUADS);
        glVertex2f(0,135);
        glVertex2f(120,135);
        glVertex2f(120,120);
        glVertex2f(0, 120);
    glEnd();

     //posto 1
     glColor3f(0.0,1.0 ,2.5 );
    glBegin(GL_QUADS);
        glVertex2f(100,90);  
        glVertex2f(105,90);  
        glVertex2f(105,80);  
        glVertex2f(100, 80); 
    glEnd();
    //PESSOA
    glColor3f(rl, gl, bl);
    glBegin(GL_QUADS);
        glVertex2f(Pessoa[0][0],Pessoa[0][1]);
        glVertex2f(Pessoa[1][0],Pessoa[1][1]);
        glVertex2f(Pessoa[2][0],Pessoa[2][1]);
        glVertex2f(Pessoa[3][0],Pessoa[3][1]);
    glEnd();

    // INSERE STRING VAZIA NA MARGEM SUPERIOR
     glColor3f(0.0f,0.0f,0.0f);
     DesenhaTexto(vacinado);
     glutSwapBuffers();

    glFlush();
}
bool vacinou(void){
    if((Pessoa[1][0] >=105 && Pessoa[1][1]>=80 && Pessoa[1][0]<= 110  && Pessoa[1][1] <= 87))
        return true;
    return false;
}

void teclado(unsigned char key, int x, int y){
    switch (key) {
            case 119:   //w (minusculo)
                for(int i= 0; i < 4; i++)
                Pessoa[i][1]+=PASSO;
                break;
            case 115: //s (minusculo)
                for(int i= 0; i < 4; i++)
                Pessoa[i][1]-=PASSO;

                break;
            case 97: //a (minusculo)
                if(Pessoa[0][0] < -5)
                {
                    Pessoa[0][0]=120;
                    Pessoa[1][0]=126;
                    Pessoa[2][0]=126;
                    Pessoa[3][0]=120;
                }
                for(int i= 0; i < 4; i++)
                    Pessoa[i][0]-=PASSO;

                break;
            case 100: //d (minusculo)
                for(int i= 0; i < 4; i++)
                Pessoa[i][0]+=PASSO;
    }
    glutPostRedisplay();
}

void TecladoEspecial(int key, int x, int y){
    switch(key){
        case GLUT_KEY_END: // CONFIRMAÇÃO DE VACINAÇÃO
            if(vacinou()){
                printf("\nVacinou\n");
                strcpy(vacinado, "Vacinou");
            }

        break;
        case GLUT_KEY_HOME: // VOLTAR A POSIÇÃO INICIAL
            for(int i=0; i<4; i++){
                    for(int j=0; j<2;j++)
                        Pessoa[i][j] = PessoaAux[i][j];
                }
                strcpy(vacinado, "");

        break;
        case GLUT_KEY_F11: // SAIR DO JOGO
            exit(0);

        break;

    }
    glutPostRedisplay();
}

void Mouse(int button, int state,int x, int y){
    if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_DOWN){
            criarMenu();
            glutPostRedisplay();
        }
    }
}

void DesenhaTexto(char *string){
  	glPushMatrix();
        // Posicao no universo onde o texto sera colocado
        glRasterPos2f(50,125);
        // Exibe caracter a caracter
        while(*string)
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*string++);
	glPopMatrix();
}


void menuCor(int op){
    switch(op){
        case 0:
            ro=0;
            go=0;
            bo=0.5;
            break;
        case 1:
            ro=0;
            go=0.5;
            bo=0;
            break;
    }
    glutPostRedisplay();
}

void MenuPrincipal (int op){

}
void criarMenu(){
    int menu, submenu;

    submenu = glutCreateMenu(menuCor);
    glutAddMenuEntry("Azul", 0);
    glutAddMenuEntry("Verde", 1);


    menu = glutCreateMenu(MenuPrincipal);
    glutAddSubMenu("Cor do Quarteirao", submenu);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
