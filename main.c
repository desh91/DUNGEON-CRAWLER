#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
// fase 1 e 2 prontas
// Configurações globais fase  
#define TAM_FASE1 10
#define TAM_FASE2 20
#define TAM_FASE3 40
#define MAX_VIDAS 3
#define MAX_REINICIOS 3

// Funções auxiliares
void clearScreen() {
    system("cls");
}

void esperarEnter() {
    printf("\nPressione ENTER para continuar...");
    while (getchar() != '\n');
}

void exibirTela(const char* titulo, const char* mensagem) {
    clearScreen();
    printf("=== %s ===\n\n", titulo);
    printf("%s\n\n", mensagem);
    esperarEnter();
}

// Telas do jogo
void creditos() {
    exibirTela("CREDITOS", 
        "Desenvolvido por:\n"
        "- RAFAEL ARRUDA\n"
        "- GABRIEL TEIXEIRA\n"
        "- GUSTAVO ALENCAR\n\n"
        "Centro Universitario do Para\n"
        "Curso de Ciencia da Computacao\n"
        "Disciplina: Algaritmo e Codificacao de Sistemas");
}

void telaVitoria() {
    exibirTela("VITORIA",
        "Parabens! Voce completou todas as fases!\n"
        "Voce e um verdadeiro aventureiro!\n\n"
        "Obrigado por jogar!");
}

void telaDerrota() {
    exibirTela("DERROTA",
        "Voce foi derrotado!\n"
        "A masmorra venceu desta vez...\n\n"
        "Tente novamente quando estiver preparado!");
}

// Funções de movimento e lógica
void moverMonstroAleatorio(int *x, int *y, char mapa[][TAM_FASE3], int tamanho) {
    int direcao = rand() % 4;
    int novo_x = *x, novo_y = *y;
    
    switch(direcao) {
        case 0: novo_x--; break; // cima
        case 1: novo_x++; break; // baixo
        case 2: novo_y--; break; // esquerda
        case 3: novo_y++; break; // direita
    }
    
    // Verifica se a nova posição é válida
    if(novo_x >= 0 && novo_x < tamanho && novo_y >= 0 && novo_y < tamanho &&
       mapa[novo_x][novo_y] != '*' && mapa[novo_x][novo_y] != 'D' && 
       mapa[novo_x][novo_y] != '#' && mapa[novo_x][novo_y] != '=') {
        *x = novo_x;
        *y = novo_y;
    }
}

void moverMonstroV(int *vx, int *vy, int px, int py, char mapa[][TAM_FASE3], int tamanho) {
    int dx = px - *vx;
    int dy = py - *vy;
    
    // Tenta mover na direção com maior diferença primeiro
    if(abs(dx) >= abs(dy)) {
        // Movimento vertical
        if(dx > 0 && *vx+1 < tamanho && mapa[*vx+1][*vy] != '*' && 
           mapa[*vx+1][*vy] != 'D' && mapa[*vx+1][*vy] != '#' && mapa[*vx+1][*vy] != '=') {
            (*vx)++;
        }
        else if(dx < 0 && *vx-1 >= 0 && mapa[*vx-1][*vy] != '*' && 
                mapa[*vx-1][*vy] != 'D' && mapa[*vx-1][*vy] != '#' && mapa[*vx-1][*vy] != '=') {
            (*vx)--;
        }
        // Se não conseguiu mover verticalmente, tenta horizontalmente
        else if(dy > 0 && *vy+1 < tamanho && mapa[*vx][*vy+1] != '*' && 
                mapa[*vx][*vy+1] != 'D' && mapa[*vx][*vy+1] != '#' && mapa[*vx][*vy+1] != '=') {
            (*vy)++;
        }
        else if(dy < 0 && *vy-1 >= 0 && mapa[*vx][*vy-1] != '*' && 
                mapa[*vx][*vy-1] != 'D' && mapa[*vx][*vy-1] != '#' && mapa[*vx][*vy-1] != '=') {
            (*vy)--;
        }
    } else {
        // Movimento horizontal
        if(dy > 0 && *vy+1 < tamanho && mapa[*vx][*vy+1] != '*' && 
           mapa[*vx][*vy+1] != 'D' && mapa[*vx][*vy+1] != '#' && mapa[*vx][*vy+1] != '=') {
            (*vy)++;
        }
        else if(dy < 0 && *vy-1 >= 0 && mapa[*vx][*vy-1] != '*' && 
                mapa[*vx][*vy-1] != 'D' && mapa[*vx][*vy-1] != '#' && mapa[*vx][*vy-1] != '=') {
            (*vy)--;
        }
        // Se não conseguiu mover horizontalmente, tenta verticalmente
        else if(dx > 0 && *vx+1 < tamanho && mapa[*vx+1][*vy] != '*' && 
                mapa[*vx+1][*vy] != 'D' && mapa[*vx+1][*vy] != '#' && mapa[*vx+1][*vy] != '=') {
            (*vx)++;
        }
        else if(dx < 0 && *vx-1 >= 0 && mapa[*vx-1][*vy] != '*' && 
                mapa[*vx-1][*vy] != 'D' && mapa[*vx-1][*vy] != '#' && mapa[*vx-1][*vy] != '=') {
            (*vx)--;
        }
    }
}

// Fases do jogo
void vila() {
    char mapa[TAM_FASE1][TAM_FASE1] = {
        "********D*",
        "*P *     *",
        "* * * ** *",
        "* *   *  *", 
        "*  ***** *", 
        "*    P   *", 
        "* *****  *",
        "*     * **", 
        "*     * @*",
        "**********"
    };
    
    int px = 8, py = 1;
    int temChave = 0;

    while (1) {
        clearScreen();
        printf("=== VILA (TUTORIAL) ===\n");
        printf("Use WASD para mover, I para interagir\n\n");
        
        int i,j;
        for(i = 0; i < TAM_FASE1; i++) {
            for(j = 0; j < TAM_FASE1; j++) {
                if (i == px && j == py) printf("&");
                else printf("%c", mapa[i][j]);
            }
            printf("\n");
        }

        if (px == 0 && py == 8 && temChave) {
            printf("\nVoce saiu da vila! Prepare-se para a masmorra!\n");
            Sleep(2000);
            return;
        }

        char move = getch();
        switch(tolower(move)) {
            case 'w':
                if(px > 0 && mapa[px-1][py] != '*') px--;
                break;
            case 'a':
                if(py > 0 && mapa[px][py-1] != '*') py--;
                break;
            case 's':
                if(px < TAM_FASE1-1 && mapa[px+1][py] != '*') px++;
                break;
            case 'd':
                if(py < TAM_FASE1-1 && mapa[px][py+1] != '*') py++;
                break;
            case 'i':
                if((px == 1 && py == 1) || (px == 5 && py == 5)) {
                    exibirTela("DICA DO NPC", 
                        "Bem-vindo aventureiro!\n"
                        "Encontre a chave (@) e use 'I' para pega-la.\n"
                        "Leve-a ate a porta (D) para sair da vila.");
                }
                else if(px == 8 && py == 8) {
                    temChave = 1;
                    mapa[px][py] = ' ';
                    mapa[0][8] = '=';
                    printf("\nVoce pegou a chave! A porta esta aberta agora!\n");
                    Sleep(1500);
                }
                break;
        }
    }
}

void fase1(int *vidas, int *reinicios) {
    char mapa[TAM_FASE1][TAM_FASE1] = {
        "********D*",
        "*   *    *",
        "* * * ****",
        "* *   *  *", 
        "* ********", 
        "*        *", 
        "* *****  *",
        "*     * **", 
        "*     * @*",
        "**********"
    };
    
    int px = 8, py = 1;
    int temChave = 0;

    while (1) {
        clearScreen();
        printf("=== FASE 1 ===\n");
        printf("Vidas: %d | Reinicios: %d/%d\n\n", *vidas, *reinicios, MAX_REINICIOS);
        
        int i,j;
        for(i = 0; i < TAM_FASE1; i++) {
            for(j = 0; j < TAM_FASE1; j++) {
                if(i == px && j == py) printf("&");
                else printf("%c", mapa[i][j]);
            }
            printf("\n");
        }

        if(px == 0 && py == 8 && temChave) {
            printf("\nFase 1 completada!\n");
            Sleep(2000);
            return;
        }

        char move = getch();
        switch(tolower(move)) {
            case 'w':
                if(px > 0 && mapa[px-1][py] != '*' && mapa[px-1][py] != 'D') px--;
                break;
            case 'a':
                if(py > 0 && mapa[px][py-1] != '*' && mapa[px][py-1] != 'D') py--;
                break;
            case 's':
                if(px < TAM_FASE1-1 && mapa[px+1][py] != '*' && mapa[px+1][py] != 'D') px++;
                break;
            case 'd':
                if(py < TAM_FASE1-1 && mapa[px][py+1] != '*' && mapa[px][py+1] != 'D') py++;
                break;
            case 'i':
                if(px == 8 && py == 8) {
                    temChave = 1;
                    mapa[px][py] = ' ';
                    mapa[0][8] = '=';
                    printf("\nChave coletada! Porta destrancada!\n");
                    Sleep(1500);
                }
                break;
        }

        if(mapa[px][py] == '#') {
            (*reinicios)++;
            (*vidas)--;
            
            if(*reinicios >= MAX_REINICIOS || *vidas <= 0) {
                telaDerrota();
                *reinicios = 0;
                return;
            }
            
            px = 8; py = 1;
            printf("\nEspinho! -1 vida. Reiniciando fase...\n");
            Sleep(1500);
        }
    }
}

void fase2(int *vidas, int *reinicios) {
    
    char mapa[TAM_FASE2][TAM_FASE2] = {
        "********************",
        "*                  *",
        "* #### ###### #### *",
        "* #  #   O     #   *", 
        "* #  ### * ### # # *", 
        "* #      *     # # *", 
        "* ###### * ##### # *",
        "* #      *     # # *", 
        "* # #### * ### # # *",
        "* #      *   # # # *",
        "* # #### #### # ## *",
        "* #              # *", 
        "* ## ########### # *", 
        "* #            D # *", 
        "* # ########### ## *",
        "* #          #  #  *", 
        "* # # # # ## #     *",
        "* # # #   #  #     *", 
        "* # # ######      @*",
        "********************",
    };
    
    int px = 18, py = 1;  // Posição inicial do jogador
    int temChave = 0;
    int m_x = 10, m_y = 5;  // Posição inicial do monstro
    int botaoAtivado = 0;

    while (1) {
        clearScreen();
        printf("=== FASE 2 ===\n");
        printf("Vidas: %d | Reinicios: %d/%d\n", *vidas, *reinicios, MAX_REINICIOS);
        printf("Dica: Procure o botao (O) para abrir a passagem bloqueada!\n");
        printf("Cuidado com os espinhos (#)!\n\n");

        // Exibe o mapa
        int i,j;
        for(i = 0; i < TAM_FASE2; i++) {
            for(j = 0; j < TAM_FASE2; j++) {
                if(i == px && j == py) printf("&");
                else if(i == m_x && j == m_y) printf("X");
                else printf("%c", mapa[i][j]);
            }
            printf("\n");
        }

        // Verifica vitória
        if(px == 13 && py == 17 && temChave) {
            printf("\nFase 2 completada!\n");
            Sleep(2000);
            return;
        }

        // Captura movimento do jogador
        char move = getch();
        switch(tolower(move)) {
            case 'w':
                if(px > 0 && mapa[px-1][py] != '*' && mapa[px-1][py] != 'D') px--;
                break;
            case 'a':
                if(py > 0 && mapa[px][py-1] != '*' && mapa[px][py-1] != 'D') py--;
                break;
            case 's':
                if(px < TAM_FASE2-1 && mapa[px+1][py] != '*' && mapa[px+1][py] != 'D') px++;
                break;
            case 'd':
                if(py < TAM_FASE2-1 && mapa[px][py+1] != '*' && mapa[px][py+1] != 'D') py++;
                break;
            case 'i':
                // Interação com chave
                if(px == 18 && py == 18) {
                    temChave = 1;
                    mapa[px][py] = ' ';
                    mapa[13][17] = '=';
                    printf("\nChave coletada! Porta aberta!\n");
                    Sleep(1500);
                }
                // Interação com botão O
                else if(px == 3 && py == 9 && !botaoAtivado) {
                    botaoAtivado = 1;
                    // Remove a barreira bloqueada (asteriscos na linha do meio)
                    int i;
                    for( i = 4; i <= 11; i++) {
                        if(mapa[i][9] == '*') mapa[i][9] = ' ';
                    }
                    printf("\nBotao ativado! Passagem secreta aberta!\n");
                    Sleep(1500);
                }
                break;
        }

        // Movimento do monstro aleatório
        moverMonstroAleatorio(&m_x, &m_y, (char(*)[TAM_FASE3])mapa, TAM_FASE2);

        // Verifica colisão com espinhos após o movimento
        if(mapa[px][py] == '#') {
            (*reinicios)++;
            (*vidas)--;
            
            printf("\nVoce pisou em espinhos! -1 vida. Reiniciando fase...\n");
            Sleep(2000);
            
            if(*reinicios >= MAX_REINICIOS || *vidas <= 0) {
                telaDerrota();
                *reinicios = 0;
                return;
            }
            
            // Reinicia posições
            px = 18; py = 1;
            m_x = 10; m_y = 5;
            // Mantém progresso do botão e chave
            continue;
        }

        // Verifica colisão com monstro
        if(px == m_x && py == m_y) {
            (*reinicios)++;
            (*vidas)--;
            
            printf("\nVoce foi capturado pelo monstro! -1 vida. Reiniciando...\n");
            Sleep(2000);
            
            if(*reinicios >= MAX_REINICIOS || *vidas <= 0) {
                telaDerrota();
                *reinicios = 0;
                return;
            }
            
            // Reinicia posições
            px = 18; py = 1;
            m_x = 10; m_y = 5;
        }
    }
}

void fase3(int *vidas, int *reinicios) {
    // Mapa da fase 3
    char mapa[TAM_FASE3][TAM_FASE3] = {
        "****************************************",
        "*&                                   D *",
        "* ##### ##### ##### ##### ##### ###### *",
        "* #   # #   # #   # #   # #   # #     #*",
        "* # # # # # # # # # # # # # # # # ##  #*",
        "* # # # # # # # # # # # # # # # # ##  #*",
        "* # # ##### # ##### # ##### # #####   #*",
        "* # #       #       #       #         #*",
        "* # ####### ####### ####### #######   #*",
        "* #                                   #*",
        "* # ####### >     O       ####### #    *",
        "* #         #           #         #    *",
        "* # ####### # ##### ##### ####### #    *",
        "* # #     # # #   # #   # # #     #    *",
        "* # # ### # # # # # # # # # # ### #    *",
        "* # # # # # # # # # # # # # # # # #    *",
        "* # # # # # # # # # # # # # # # # #    *",
        "* # # # # # # # ### ### # # # # # #    *",
        "* # # # # # # #       # # # # # # #    *",
        "* # # # # # # # ##### # # # # # # #    *",
        "* # # # # # # # #   # # # # # # # #    *",
        "* # # # # # # # # @ # # # # # # # #    *",
        "* # # # # # # # #   # # # # # # # #    *",
        "* # # # # # # # ##### # # # # # # #    *",
        "* # # # # # # #       # # # # # # #    *",
        "* # # # # # # ######### # # # # # #    *",
        "* # # # # # #           # # # # # #    *",
        "* # # # # # ##### ##### # # # # # #    *",
        "* # # # # #     # #     # # # # # #    *",
        "* # # # # # ### # # ### # # # # # #    *",
        "* # # # # # # # #># # # # # # # # #    *",
        "* # # # # # # ##### # ##### # # # #    *",
        "* # #   # # #       #       # #   #    *",
        "* # ##### # ##### ##### ##### #####    *",
        "* #       #                 #          *",
        "* # ####### ############### #######    *",
        "* #                                   #*",
        "* ##### ##### ##### ##### ##### #####  *",
        "*                                     #*",
        "****************************************",
    };
    
    int px = 1, py = 1;  // Posição inicial do jogador (canto superior esquerdo)
    int chavesColetadas = 0;
    int totalChaves = 1;  
    int m1_x = 6, m1_y = 6;   // Monstro aleatório 1 
    int m2_x = 33, m2_y = 33; // Monstro aleatório 2 
    int mV_x = 20, mV_y = 20; // Monstro inteligente V 
    int armadilhaDesativada = 0;
    int portaAberta = 0;
    int contadorMovimento = 0; // Para controlar movimento do monstro V

    while (1) {
        clearScreen();
        printf("=== FASE 3 - MASMORRA FINAL ===\n");
        printf("Vidas: %d | Reinicios: %d/%d | Chaves: %d/%d\n", 
              *vidas, *reinicios, MAX_REINICIOS, chavesColetadas, totalChaves);
        printf("Objetivo: Colete a chave (@) e va para a porta (D) no canto superior direito!\n");
        printf("Use o botao (O) para abrir passagens e os teletransportes (>) para se mover rapidamente!\n");
        printf("Cuidado: X=monstro aleatorio, V=monstro inteligente!\n\n");

        // Exibe o mapa
        int i,j;
        for(i = 0; i < TAM_FASE3; i++) {
            for(j = 0; j < TAM_FASE3; j++) {
                if(i == px && j == py) {
                    printf("&");
                }
                else if(i == m1_x && j == m1_y) {
                    printf("X");
                }
                else if(i == m2_x && j == m2_y) {
                    printf("X");
                }
                else if(i == mV_x && j == mV_y) {
                    printf("V");
                }
                else {
                    printf("%c", mapa[i][j]);
                }
            }
            printf("\n");
        }

        // Verifica condição de vitória (chegada na porta aberta)
        if(px == 1 && py == 38 && portaAberta) {
            telaVitoria();
            return;
        }

        // Captura movimento do jogador
        char move = getch();
        int novo_px = px, novo_py = py;
        int jogadorMoveu = 0;
        
        switch(tolower(move)) {
            case 'w':
                novo_px = px - 1;
                jogadorMoveu = 1;
                break;
            case 'a':
                novo_py = py - 1;
                jogadorMoveu = 1;
                break;
            case 's':
                novo_px = px + 1;
                jogadorMoveu = 1;
                break;
            case 'd':
                novo_py = py + 1;
                jogadorMoveu = 1;
                break;
            case 'i':
                // Interação com a chave
                if(mapa[px][py] == '@') {
                    chavesColetadas++;
                    mapa[px][py] = ' '; // Remove a chave do mapa
                    printf("\nChave coletada! A porta final foi aberta!\n");
                    printf("Va para a porta (D) no canto superior direito para vencer!\n");
                    
                    // Abre a porta
                    mapa[1][38] = '=';
                    portaAberta = 1;
                    Sleep(2000);
                }
                // Interação com o botão - abre passagens úteis
                else if(px == 10 && py == 18 && !armadilhaDesativada) {
                    armadilhaDesativada = 1;
                    printf("\nBotao ativado! Passagens secretas abertas!\n");
                    
                    // Abre passagens estratégicas para facilitar navegação
                    // Passagem horizontal central
                    int j;
                    for(j = 8; j <= 32; j++) {
                        if(mapa[20][j] == '#') {
                            mapa[20][j] = ' ';
                        }
                    }
                    
                    // Passagem vertical central
                    int i;
                    for(i = 8; i <= 32; i++) {
                        if(mapa[i][20] == '#') {
                            mapa[i][20] = ' ';
                        }
                    }
                    
                    printf("Agora voce pode atravessar o centro do labirinto!\n");
                    Sleep(2000);
                }
                else {
                    printf("\nNao ha nada para interagir aqui.\n");
                    Sleep(1000);
                }
                break;
        }

        // Verifica se o movimento é válido
        if(novo_px >= 0 && novo_px < TAM_FASE3 && novo_py >= 0 && novo_py < TAM_FASE3) {
            char destino = mapa[novo_px][novo_py];
            
            // Pode mover para espaços vazios, chave, botão, teletransporte, porta aberta
            if(destino != '*' && !(destino == 'D' && !portaAberta)) {
                px = novo_px;
                py = novo_py;
            }
        }

        // Sistema de Teletransportes 
        if(px == 10 && py == 12) {  // Teletransporte esquerdo
            px = 30; py = 17;  // para teletransporte direito
            printf("\n>>> TELETRANSPORTADO! <<<\n");
            Sleep(1000);
        }
        else if(px == 30 && py == 17) {  // Teletransporte direito
            px = 10; py = 12;  // para teletransporte esquerdo
            printf("\n>>> TELETRANSPORTADO! <<<\n");
            Sleep(1000);
        }

        // Movimento dos monstros
        if(jogadorMoveu) {
            contadorMovimento++;
            
            // Monstros aleatórios se movem sempre
            moverMonstroAleatorio(&m1_x, &m1_y, mapa, TAM_FASE3);
            moverMonstroAleatorio(&m2_x, &m2_y, mapa, TAM_FASE3);
            
            // Monstro inteligente V se move a cada 3 movimentos (mais balanceado)
            if(contadorMovimento % 3 == 0) {
                moverMonstroV(&mV_x, &mV_y, px, py, mapa, TAM_FASE3);
            }
        }

        // Verifica colisões com monstros
        int colidiu = 0;
        
        if((px == m1_x && py == m1_y) || (px == m2_x && py == m2_y)) {
            printf("\n>>> Voce foi capturado por um monstro! <<<\n");
            colidiu = 1;
        }
        else if(px == mV_x && py == mV_y) {
            printf("\n>>> O monstro inteligente te encontrou! <<<\n");
            colidiu = 1;
        }
        else if(mapa[px][py] == '#') {
            printf("\n>>> Voce pisou em espinhos! <<<\n");
            colidiu = 1;
        }
        if(colidiu) {
            (*reinicios)++;
            (*vidas)--;
            
            printf("Perdeu uma vida! Reiniciando fase em 3 segundos...\n");
            Sleep(3000);
            
            // Verifica derrota
            if(*reinicios >= MAX_REINICIOS || *vidas <= 0) {
                telaDerrota();
                *reinicios = 0;
                return;
            }
            
            // Reinicia posições (mantém progresso das chaves e botão)
            px = 1; py = 1;
            m1_x = 6; m1_y = 6;
            m2_x = 33; m2_y = 33;
            mV_x = 20; mV_y = 20;
            contadorMovimento = 0;
        }
        
        // Dicas para o jogador
        if(mapa[px][py] == '@') {
            printf(">>> Pressione 'I' para coletar a chave! <<<\n");
        }
        else if(px == 10 && py == 19 && !armadilhaDesativada) {
            printf(">>> Pressione 'I' para ativar o botao e abrir passagens! <<<\n");
        }
        else if((px == 10 && py == 17) || (px == 10 && py == 23)) {
            printf(">>> Teletransporte ativo! Mova-se para ser transportado! <<<\n");
        }
        else if(px == 1 && py == 38 && !portaAberta) {
            printf(">>> Porta trancada! Voce precisa da chave primeiro! <<<\n");
        }
        else if(px == 1 && py == 38 && portaAberta) {
            printf(">>> Porta aberta! Mova-se para vencer o jogo! <<<\n");
        }
    }
}
// Menu principal
void menuPrincipal() {
    int vidas = MAX_VIDAS;
    int reinicios = 0;

    while (1) {
        clearScreen();
        printf("=== DUNGEON CRAWLER ===\n\n");
        printf("1. Jogar\n");
        printf("2. Tutorial\n");
        printf("3. Creditos\n");
        printf("4. Sair\n\n");
        printf("Escolha: ");
        
        int opcao;
        if(scanf("%d", &opcao) != 1) {
            while(getchar() != '\n');
            printf("Entrada invalida! Digite um numero.\n");
            Sleep(1000);
            continue;
        }
        while(getchar() != '\n');

        switch(opcao) {
            case 1:
                vila();
                fase1(&vidas, &reinicios);
                if(vidas > 0 && reinicios < MAX_REINICIOS) {
                    fase2(&vidas, &reinicios);
                    if(vidas > 0 && reinicios < MAX_REINICIOS) {
                        fase3(&vidas, &reinicios);
                    }
                }
                vidas = MAX_VIDAS;
                reinicios = 0;
                break;
            case 2:
                exibirTela("TUTORIAL",
                    "Controles:\n"
                    "W - Cima\nA - Esquerda\nS - Baixo\nD - Direita\n"
                    "I - Interagir\n\n"
                    "Elementos:\n"
                    "& - Voce\n* - Parede\n@ - Chave\nD - Porta\n= - Porta aberta\n"
                    "O - Botao\n# - Espinhos\n> - Teletransporte\n"
                    "X - Monstro fraco\nV - Monstro forte\nP - NPC\n\n"
                    "Objetivo: Colete chaves para abrir portas e chegue ao final!");
                break;
            case 3:
                creditos();
                break;
            case 4:
                printf("Saindo do jogo...\n");
                exit(0);
            default:
                printf("Opcao invalida! Tente novamente.\n");
                Sleep(1000);
        }
    }
}

int main() {
    
    srand(time(NULL));
    SetConsoleTitle("Dungeon Crawler - Projeto");

    // Inicia o jogo
    menuPrincipal();
    return 0;
}
