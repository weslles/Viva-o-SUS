/**
    UNIVERSIDADE FEDERAL DO VALE DO SAO FRANCISCO
    DISCIPLINA: COMPUTACAOO GRAFICA  TURMA: 2020.2
    PROFESSOR:  JORGE CAVALCANTE
    ALUNOS:     JOSE WESLLES
                MATTHEUS ADHONNAY
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


GLfloat ro,go,bo; //RGB DO QUARTEIRÃO
GLfloat rc,gc,bc; //RGB DO CORPO DA PESSOA

int vetx[68] = {0,10,10,0,0,20,20,0,20,50,50,20,20,50,50,20,60,90,90,60,100,120,120,
                100,60,90,90,60,0,20,20,0,20,50,50,20,0,10,10,0,0,10,10,0,20,90,90,
                20,60,90,90,60,60,120,120,60,100,120,120,100,100,120,120,100,100,120,120,100};
int vety[68] = {0,0,20,20,30,30,45,45,10,10,0,0,45,45,20,20,10,10,0,0,20,20,0,0,65,
                65,20,20,55,55,70,70,55,55,90,90,80,80,100,100,120,120,110,110,110,
                110,100,100,100,100,75,75,65,65,55,55,45,45,30,30,120,120,110,110,100,100,75,75};

int vidas = 3;
char vacinado[15] = " "; //MENSAGEM DE VITORIA/DERROTA
char contVacinas[30] = "";
int xc, yc, zc;

float Pessoa[4][2]    =  {{2,23},
                        {8,23},
                        {8,26},
                        {2, 26}};
float PessoaAux[4][2]    =  {{2,23},
                        {8,23},
                        {8,26},
                        {2, 26}};

int a =80, b=87,c=105;




void Inicializa(void);
void Desenha(void);
void teclado(unsigned char , int , int );
void TecladoEspecial(int , int , int );
void Mouse(int , int ,int , int );
void DesenhaTexto(char *);
void criarMenu();
void textoVacinaRestante(char *);

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

    glClearColor(CINZA);
    gluOrtho2D(0,120,0,135);
    ro=0.04; go=0.75; bo=0.0;
    rc=0; gc=0; bc=0;
    strcpy(contVacinas, "Vacinas Restantes: 2");
    xc=0;
    yc=0;
    zc=0;

}
void desenhaPosto(void){
    glColor3f(0.0,1.0 ,2.5 );
    glBegin(GL_QUADS);
        glVertex2f(100,90);
        glVertex2f(105,90);
        glVertex2f(105,80);
        glVertex2f(100, 80);
    glEnd();

}
void desenhaCorpo(void){
    glColor3f(rc, gc, bc);
    glBegin(GL_QUADS);
        glVertex2f(Pessoa[0][0],Pessoa[0][1]);
        glVertex2f(Pessoa[1][0],Pessoa[1][1]);
        glVertex2f(Pessoa[2][0],Pessoa[2][1]);
        glVertex2f(Pessoa[3][0],Pessoa[3][1]);
    glEnd();
}
void Desenha(void){


    glColor3f(ro, go, bo);

    glClear(GL_COLOR_BUFFER_BIT);

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

    glPushMatrix();
        glTranslatef(xc,yc,zc);
        desenhaPosto();
    glPopMatrix();

    //PESSOA
   desenhaCorpo();

    // INSERE STRING VAZIA NA MARGEM SUPERIOR
     glColor3f(2.5f,2.5f,2.5f);
     DesenhaTexto(vacinado);
     glutSwapBuffers();
     // INSERE STRING VAZIA NA MARGEM SUPERIOR
     glColor3f(2.5f,2.5f,2.5f);
     textoVacinaRestante(contVacinas);
     glutSwapBuffers();

    glFlush();
}
bool vacinou(void){
    if(( Pessoa[1][1] >= a &&
         Pessoa[1][1] <= b &&
         Pessoa[1][0] == c ))

        return true;
    return false;
}

void teclado(unsigned char key, int x, int y){
    switch (key) {
            case 119:   //w (minusculo)
                for(int i= 0; i < 4; i++)
                    Pessoa[i][1]+=PASSO;
                if(vacinou())
                    strcpy(vacinado, "Aperte END para ser vacinado");
                else
                    strcpy(vacinado, " ");
                break;
            case 115: //s (minusculo)
                for(int i= 0; i < 4; i++)
                Pessoa[i][1]-=PASSO;
                if(vacinou())
                    strcpy(vacinado, "Aperte END para ser vacinado");
                else
                    strcpy(vacinado, " ");

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
                if(vacinou())
                    strcpy(vacinado, "Aperte END para ser vacinado");
                else
                    strcpy(vacinado, " ");

                break;
            case 100: //d (minusculo)
                for(int i= 0; i < 4; i++)
                    Pessoa[i][0]+=PASSO;
                if(vacinou())
                    strcpy(vacinado, "Aperte END para ser vacinado");
                else
                    strcpy(vacinado, " ");
                    break;
    }
    glutPostRedisplay();
}

int i=1;

void TecladoEspecial(int key, int x, int y){
    switch(key){
        case GLUT_KEY_END: // CONFIRMAÇÃO DE VACINAÇÃO
            if(vacinou()){
                strcpy(vacinado, "Vacinou");
                a=55;
                b=62;
                c=51;

                xc=-55;
                yc=-25;
                zc=0;
                if(i==1){
                    strcpy(contVacinas, "Vacinas Restantes: 1");
                    i=0;
                }
                else{
                    strcpy(vacinado, "Parabéns! 100% Imunizado");
                    strcpy(contVacinas, "Vacinas Restantes: 0");
                }




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
    if(button == GLUT_RIGHT_BUTTON){
        if(state == GLUT_DOWN){
            criarMenu();
            glutPostRedisplay();
        }
    }
}

void DesenhaTexto(char *string){
  	glPushMatrix();
        // Posicao no universo onde o texto sera colocado
        glRasterPos2f(40,122);
        // Exibe caracter a caracter
        while(*string)
             glutBitmapCharacter(GLUT_BITMAP_9_BY_15,*string++);
	glPopMatrix();
}
void textoVacinaRestante(char *string){
  	glPushMatrix();
        // Posicao no universo onde o texto sera colocado
        glRasterPos2f(2,130);
        // Exibe caracter a caracter
        while(*string)
             glutBitmapCharacter(GLUT_BITMAP_9_BY_15,*string++);
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

