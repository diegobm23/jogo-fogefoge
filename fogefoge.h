#ifndef _FOGEFOGE_H_
#define _FOGEFOGE_H_

#define CIMA 'w'
#define BAIXO 's'
#define DIREITA 'd'
#define ESQUERDA 'a'
#define BOMBA 'b'

int acabou();
void mover(char comando);
int validardirecao(char comando);
void andarfantasma();
int escolherdirecaofantasma(int xorigem, int yorigem, int* xdestino, int* ydestino);
void explodirpilula2(int x, int y, int somax, int somay, int qtd);
void explodirpilula();

#endif
