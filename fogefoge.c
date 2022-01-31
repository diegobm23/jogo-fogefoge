#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "fogefoge.h"
#include "mapa.h"
#include "ui.h"

MAPA m;
POSICAO heroi;
int tempilula = 0;

int acabou() {
  POSICAO pos;
  int perdeu = !encontrarheroi(&m, &pos, HEROI);
  int ganhou = !encontrarheroi(&m, &pos, FANTASMA);

  return ganhou || perdeu;
}

int escolherdirecaofantasma(int xorigem, int yorigem, int* xdestino, int* ydestino) {
  int opcoes[4][2] = {
        { xorigem   , yorigem+1 },
        { xorigem+1 , yorigem   },
        { xorigem   , yorigem-1 },
        { xorigem-1 , yorigem   }
  };

  srand(time(0));

  for (int i = 0; i < 10; i++) {
    int posicao = rand() % 4;

    if (validarpodeandar(&m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1])) {
      *xdestino = opcoes[posicao][0];
      *ydestino = opcoes[posicao][1];
      return 1;
    }
  }

  return 0;
}

void andarfantasma() {
  MAPA copia;
  copiarmapa(&m, &copia);

  for (int i = 0; i < m.linhas; i++) {
    for (int j = 0; j < m.colunas; j++) {

      if (copia.matriz[i][j] == FANTASMA) {
        int xdestino;
        int ydestino;
        int encontrou = escolherdirecaofantasma(i, j, &xdestino, &ydestino);

        if (encontrou) {
          andarnomapa(&m, i, j, xdestino, ydestino);
        }

      }
    }
  }

  liberarmapa(&copia);
}

int validardirecao(char comando) {
  return (comando == ESQUERDA ||
          comando == CIMA ||
          comando == DIREITA ||
          comando == BAIXO);
}

void mover(char comando) {
  if (!validardirecao(comando)) return;

  int proximox = heroi.x;
  int proximoy = heroi.y;

  switch(comando) {
    case ESQUERDA:
      proximoy--;
      break;
    case CIMA:
      proximox--;
      break;
    case BAIXO:
      proximox++;
      break;
    case DIREITA:
      proximoy++;
      break;
  }

  if (!validarpodeandar(&m, HEROI, proximox, proximoy))
    return;

  if (verificarpersonagem(&m, PILULA, proximox, proximoy)) {
    tempilula = 1;
  }

  andarnomapa(&m, heroi.x, heroi.y, proximox, proximoy);
  heroi.x = proximox;
  heroi.y = proximoy;
}

void explodirpilula() {
  explodirpilula2(heroi.x, heroi.y, 0, 1, 3);
  explodirpilula2(heroi.x, heroi.y, 0, -1, 3);
  explodirpilula2(heroi.x, heroi.y, 1, 0, 3);
  explodirpilula2(heroi.x, heroi.y, -1, 0, 3);
}

void explodirpilula2(int x, int y, int somax, int somay, int qtd) {

  if (qtd == 0) return;

  int novox = x + somax;
  int novoy = y + somay;

  if (!validarlimites(&m, novox, novoy)) return;
  if (validarparede(&m, novox, novoy)) return;

  m.matriz[novox][novoy] = VAZIO;
  explodirpilula2(novox, novoy, somax, somay, qtd - 1);
}

int main() {
  lermapa(&m);
  encontrarheroi(&m, &heroi, HEROI);

  do {
    printf("Tem pilula %s \n", (tempilula ? "SIM" : "NAO"));
    imprimirmapa(&m);

    char comando;
    scanf(" %c", &comando);
    mover(comando);

    if (comando == BOMBA) explodirpilula();

    andarfantasma();
  } while (!acabou());

  liberarmapa(&m);
}
