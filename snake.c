#include "snake.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* Variáveis globais */
Cobra* cabeca = NULL;
int dx = 1, dy = 0;
int comidaX, comidaY;
int pontuacao = 0;
int gameOver = 0;

/* Implementação das funções */

Cobra* nova_parte_cobra(int x, int y) {
    Cobra* parte = (Cobra*)malloc(sizeof(Cobra));
    if (!parte) {
        fprintf(stderr, "Erro\n");
        exit(1);
    }
    parte->x = x;
    parte->y = y;
    parte->proximo = NULL;
    return parte;
}

void reiniciar_cobra() {
    while (cabeca) {
        Cobra* temp = cabeca;
        cabeca = cabeca->proximo;
        free(temp);
    }
    cabeca = nova_parte_cobra(LARGURA_TELA / 2, ALTURA_TELA / 2);
}

void spawn_comida() {
    int valido = 0;
    while (!valido) {
        comidaX = rand() % (LARGURA_TELA - 2) + 1;
        comidaY = rand() % (ALTURA_TELA - 2) + 1;
        
        valido = 1;
        for (Cobra* c = cabeca; c; c = c->proximo) {
            if (c->x == comidaX && c->y == comidaY) {
                valido = 0;
                break;
            }
        }
    }
}

void desenhar_comida() {
    glColor3f(0.8f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2i(comidaX * TAMANHO_CELULA, comidaY * TAMANHO_CELULA);
        glVertex2i((comidaX + 1) * TAMANHO_CELULA, comidaY * TAMANHO_CELULA);
        glVertex2i((comidaX + 1) * TAMANHO_CELULA, (comidaY + 1) * TAMANHO_CELULA);
        glVertex2i(comidaX * TAMANHO_CELULA, (comidaY + 1) * TAMANHO_CELULA);
    glEnd();
}

int checar_colisao(int x, int y) {
    if (x < 1 || x >= LARGURA_TELA - 1 || y < 1 || y >= ALTURA_TELA - 1)
        return 1;
    
    for (Cobra* c = cabeca->proximo; c; c = c->proximo) {
        if (c->x == x && c->y == y)
            return 1;
    }
    return 0;
}

void mover_cobra() {
    int novo_x = cabeca->x + dx;
    int novo_y = cabeca->y + dy;

    if (checar_colisao(novo_x, novo_y)) {
        gameOver = 1;
        return;
    }

    Cobra* nova_cabeca = nova_parte_cobra(novo_x, novo_y);
    nova_cabeca->proximo = cabeca;
    cabeca = nova_cabeca;

    if (novo_x == comidaX && novo_y == comidaY) {
        pontuacao++;
        spawn_comida();
    } else {
        Cobra* atual = cabeca;
        while (atual->proximo->proximo) {
            atual = atual->proximo;
        }
        free(atual->proximo);
        atual->proximo = NULL;
    }
}

void desenhar_cobra() {
    glColor3f(0.0f, 0.7f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2i(cabeca->x * TAMANHO_CELULA, cabeca->y * TAMANHO_CELULA);
        glVertex2i((cabeca->x + 1) * TAMANHO_CELULA, cabeca->y * TAMANHO_CELULA);
        glVertex2i((cabeca->x + 1) * TAMANHO_CELULA, (cabeca->y + 1) * TAMANHO_CELULA);
        glVertex2i(cabeca->x * TAMANHO_CELULA, (cabeca->y + 1) * TAMANHO_CELULA);
    glEnd();

    glColor3f(0.0f, 0.5f, 0.0f);
    for (Cobra* c = cabeca->proximo; c; c = c->proximo) {
        glBegin(GL_QUADS);
            glVertex2i(c->x * TAMANHO_CELULA, c->y * TAMANHO_CELULA);
            glVertex2i((c->x + 1) * TAMANHO_CELULA, c->y * TAMANHO_CELULA);
            glVertex2i((c->x + 1) * TAMANHO_CELULA, (c->y + 1) * TAMANHO_CELULA);
            glVertex2i(c->x * TAMANHO_CELULA, (c->y + 1) * TAMANHO_CELULA);
        glEnd();
    }
}
/* Desenha as paredes do cenário */
void desenhar_barreiras() {
    glColor3f(0.25f, 0.25f, 0.5f);
     /* Paredes horizontais (superior e inferior) */
    for (int x = 0; x < LARGURA_TELA; x++) {
        glBegin(GL_QUADS);
            glVertex2i(x * TAMANHO_CELULA, 0);
            glVertex2i((x + 1) * TAMANHO_CELULA, 0);
            glVertex2i((x + 1) * TAMANHO_CELULA, TAMANHO_CELULA);
            glVertex2i(x * TAMANHO_CELULA, TAMANHO_CELULA);
            
            glVertex2i(x * TAMANHO_CELULA, (ALTURA_TELA - 1) * TAMANHO_CELULA);
            glVertex2i((x + 1) * TAMANHO_CELULA, (ALTURA_TELA - 1) * TAMANHO_CELULA);
            glVertex2i((x + 1) * TAMANHO_CELULA, ALTURA_TELA * TAMANHO_CELULA);
            glVertex2i(x * TAMANHO_CELULA, ALTURA_TELA * TAMANHO_CELULA);
        glEnd();
    }
     /* Paredes verticais (laterais) */
    for (int y = 1; y < ALTURA_TELA - 1; y++) {
        glBegin(GL_QUADS);
            glVertex2i(0, y * TAMANHO_CELULA);
            glVertex2i(TAMANHO_CELULA, y * TAMANHO_CELULA);
            glVertex2i(TAMANHO_CELULA, (y + 1) * TAMANHO_CELULA);
            glVertex2i(0, (y + 1) * TAMANHO_CELULA);
            
            glVertex2i((LARGURA_TELA - 1) * TAMANHO_CELULA, y * TAMANHO_CELULA);
            glVertex2i(LARGURA_TELA * TAMANHO_CELULA, y * TAMANHO_CELULA);
            glVertex2i(LARGURA_TELA * TAMANHO_CELULA, (y + 1) * TAMANHO_CELULA);
            glVertex2i((LARGURA_TELA - 1) * TAMANHO_CELULA, (y + 1) * TAMANHO_CELULA);
        glEnd();
    }
}

void texto_na_tela(float x, float y, const char* str) {
    glRasterPos2f(x, y);
    while (*str) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *str++);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    desenhar_barreiras();
    desenhar_cobra();
    desenhar_comida();

    char buffer[50];
    snprintf(buffer, sizeof(buffer), "Pontos: %d", pontuacao);
    glColor3f(1.0f, 1.0f, 1.0f);
    texto_na_tela(10, ALTURA_TELA * TAMANHO_CELULA - 20, buffer);

    if (gameOver) {
        glColor3f(1.0f, 0.3f, 0.3f);
        texto_na_tela(LARGURA_TELA * TAMANHO_CELULA / 2 - 50, 
                     ALTURA_TELA * TAMANHO_CELULA / 2 + 10, 
                     "Fim de Jogo!");
        
        texto_na_tela(LARGURA_TELA * TAMANHO_CELULA / 2 - 100, 
                     ALTURA_TELA * TAMANHO_CELULA / 2 - 20, 
                     "Pressione ENTER para recomecar");
    }

    glutSwapBuffers();
}

// Função principal de atualização do jogo
void timer(int valor) {
    if (!gameOver) {
        mover_cobra();
        glutPostRedisplay();
        glutTimerFunc(FPS, timer, 0);
    }
}

// Trata as teclas de direção (setas)
void teclado_especial(int tecla, int x, int y) {
    switch (tecla) {
        case GLUT_KEY_UP:    if (!dy) { dx = 0; dy = 1; } break;
        case GLUT_KEY_DOWN:  if (!dy) { dx = 0; dy = -1; } break;
        case GLUT_KEY_LEFT:  if (!dx) { dx = -1; dy = 0; } break;
        case GLUT_KEY_RIGHT: if (!dx) { dx = 1; dy = 0; } break;
    }
}

// Trata outras teclas (Enter para reiniciar)
void teclado(unsigned char key, int x, int y) {
    if (key == 13 && gameOver) { /* ENTER */
        reiniciar_cobra();
        dx = 1; dy = 0;
        gameOver = 0;
        pontuacao = 0;
        spawn_comida();
        glutTimerFunc(FPS, timer, 0); 
    }
}

void inicializar() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, LARGURA_TELA * TAMANHO_CELULA, 0, ALTURA_TELA * TAMANHO_CELULA);

    srand(time(NULL));
    reiniciar_cobra();
    spawn_comida();
}
