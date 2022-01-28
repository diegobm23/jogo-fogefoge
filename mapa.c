#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

void copiarmapa(MAPA* origem, MAPA* destino) {
  destino->linhas = origem->linhas;
  destino->colunas = origem->colunas;
  alocarmapa(destino);

  for (int i = 0; i < destino->linhas; i++) {
    strcpy(destino->matriz[i], origem->matriz[i]);
  }
}

void andarnomapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino) {
  char personagem = m->matriz[xorigem][yorigem];
  m->matriz[xdestino][ydestino] = personagem;
  m->matriz[xorigem][yorigem] = VAZIO;
}

int validarlimites(MAPA* m, int x, int y) {
  return (x <= m->linhas && y <= m->colunas);
}

int validarparede(MAPA* m, int x, int y) {
  return m->matriz[x][y] == PAREDE_VERTICAL ||
         m->matriz[x][y] == PAREDE_HORIZONTAL;
}

int verificarpersonagem(MAPA* m, char personagem, int x, int y) {
  return m->matriz[x][y] == personagem;
}

int validarpodeandar(MAPA* m, char personagem, int x, int y) {
  return ( validarlimites(m, x, y) &&
           !validarparede(m, x, y) &&
           !verificarpersonagem(m, personagem, x, y) );
}

int encontrarheroi(MAPA* m, POSICAO* p, char heroi) {
  for (int i = 0; i < m->linhas; i++) {
    for (int j = 0; j <  m->colunas; j++) {
      if ( m->matriz[i][j] == heroi) {
        p->x = i;
        p->y = j;
        return 1;
      }
    }
  }

  return 0;
}

void alocarmapa(MAPA* m) {
  m->matriz = malloc(sizeof(char*) * m->linhas);

  for (int i = 0; i < m->linhas; i++) {
    m->matriz[i] = malloc(sizeof(char) * (m->colunas + 1));
  }
}

void lermapa(MAPA* m) {
  FILE* file = fopen("mapa.txt", "r");

  if (file == 0) {
    printf("Erro ao abrir o arquivo do mapa.");
    exit(0);
  }

  fscanf(file, "%d %d", &(m->linhas), &(m->colunas));

  alocarmapa(m);

  for (int i = 0; i < 5; i++) {
    fscanf(file, "%s", m->matriz[i]);
  }

  fclose(file);
}

void liberarmapa(MAPA* m) {
  for (int i = 0; i < m->linhas; i++) {
    free(m->matriz[i]);
  }

  free(m->matriz);
}

void imprimirmapa(MAPA* m) {
  for (int i = 0; i < 5; i++) {
    printf("%s\n", m->matriz[i]);
  }
}
