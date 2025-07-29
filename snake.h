#ifndef SNAKE_H
#define SNAKE_H

#include <GL/glut.h>

/* Constantes do jogo */
#define LARGURA_TELA 40    /* Largura em c�lulas */
#define ALTURA_TELA 30     /* Altura em c�lulas */
#define TAMANHO_CELULA 20  /* Tamanho em pixels de cada c�lula */
#define FPS 100            /* Velocidade do jogo (ms por frame), Op��o minha para fazer as coisas mais simples */

/* Estrutura da cobra */
typedef struct Cobra {
    int x, y;              /* Posi��o na grade */
    struct Cobra* proximo; /* Pr�xima parte do corpo */
} Cobra;

/* Vari�veis globais */
extern Cobra* cabeca;
extern int dx, dy;
extern int comidaX, comidaY;
extern int pontuacao;
extern int gameOver;

/* Fun��es da cobra */
Cobra* nova_parte_cobra(int x, int y);
void mover_cobra();
void desenhar_cobra();
void reiniciar_cobra();

/* Fun��es de jogo */
void spawn_comida();
void desenhar_comida();
void desenhar_barreiras();
int checar_colisao(int x, int y);

/* Fun��es auxiliares de texto*/
void texto_na_tela(float x, float y, const char* str);

/* Callbacks */
void display();
void timer(int valor);     
void teclado_especial(int tecla, int x, int y);
void teclado(unsigned char key, int x, int y);
void inicializar();

#endif
