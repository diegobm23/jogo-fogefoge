#define CIMA 'w'
#define BAIXO 's'
#define DIREITA 'd'
#define ESQUERDA 'a'

int acabou();
void mover(char comando);
int validardirecao(char comando);
void andarfantasma();
int escolherdirecaofantasma(int xorigem, int yorigem, int* xdestino, int*ydestino);
