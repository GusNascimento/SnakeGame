#include "snake.h"

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(LARGURA_TELA * TAMANHO_CELULA, ALTURA_TELA * TAMANHO_CELULA);
    glutCreateWindow("Jogo da Cobrinha - Projeto de Computacao Grafica");

    inicializar();

    glutDisplayFunc(display);
    glutSpecialFunc(teclado_especial);
    glutKeyboardFunc(teclado);
    glutTimerFunc(FPS, timer, 0);  

    glutMainLoop();
    return 0;
}
