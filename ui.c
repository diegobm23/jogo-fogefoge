#include <stdio.h>
#include "mapa.h"

char desenhofantasma[4][7] = {
    {" .-.  " },
    {"| OO| " },
    {"|   | " },
    {"'^^^' " }
};

char desenhoparede[4][7] = {
    {"......" },
    {"......" },
    {"......" },
    {"......" }
};

char desenhoheroi[4][7] = {
    {" .--. "  },
    {"/ _.-'"  },
    {"\\  '-." },
    {" '--' "  }
};

char desenhopilula[4][7] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}
};

char desenhovazio[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}
};

void imprimirparte(char desenho[4][7], int parte) {
    printf("%s", desenho[parte]);
}

void imprimirmapa(MAPA* m) {
    for(int i = 0; i < m->linhas; i++) {

        for(int parte = 0; parte < 4; parte++) {
            for(int j = 0; j < m->colunas; j++) {

                switch(m->matriz[i][j]) {
                    case FANTASMA:
                        imprimirparte(desenhofantasma, parte);
                        break;
                    case HEROI:
                        imprimirparte(desenhoheroi, parte);
                        break;
                    case PILULA:
                        imprimirparte(desenhopilula, parte);
                        break;
                    case PAREDE_VERTICAL:
                    case PAREDE_HORIZONTAL:
                        imprimirparte(desenhoparede, parte);
                        break;
                    case VAZIO:
                        imprimirparte(desenhovazio, parte);
                        break;
                }

            }
            printf("\n");
        }

    }
}
