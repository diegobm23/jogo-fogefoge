#ifndef _MAPA_H_
#define _MAPA_H_

#define HEROI '@'
#define FANTASMA 'F'
#define VAZIO '.'
#define PAREDE_VERTICAL '|'
#define PAREDE_HORIZONTAL '-'
#define PILULA 'P'

struct mapa {
  char** matriz;
  int linhas;
  int colunas;
};

typedef struct mapa MAPA;

struct posicao {
  int x;
  int y;
};

typedef struct posicao POSICAO;

void alocarmapa(MAPA* m);
void lermapa(MAPA* m);
void liberarmapa(MAPA* m);
int encontrarheroi(MAPA* m, POSICAO* p, char heroi);
int validarlimites(MAPA* m, int x, int y);
int validarparede(MAPA* m, int x, int y);
int verificarpersonagem(MAPA* m, char personagem, int x, int y);
void andarnomapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino);
void copiarmapa(MAPA* origem, MAPA* destino);
int validarpodeandar(MAPA* m, char personagem, int x, int y);

#endif
