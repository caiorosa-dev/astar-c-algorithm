#include "src/algorithm/astar.h"

int main( )
{
    Node start;
    start.row = 0;
    start.col = 0;

    Node end;
    end.row = 4;
    end.col = 4;

    printf("Ola! Bem vindo ao algoritmo A*, abaixo segue a GRID utilizada para a busca do caminho.\n");
    printf("-------------------------------------------------------\n\n");
    showGrid(start, end);
    printf("\n\nLegenda:\n- Inicio do caminho\n+ Chegada do caminho\n| Parede (caminho nao livre)\n[ e ] Delimitadores horizontais da matriz\n_ Delimitadores verticais da matriz");
    printf("\n\nAperte ENTER para continuar.");
    printf("\n-------------------------------------------------------");

    readChar();
    clearTerminal();

    printf("-------------------------------------------------------\n");
    printf("Construindo caminho...\n\n");
    runAStarAlgorithm(start, end);

    printf("\nCaminho finalizado.\n\nTrabalho feito por: \nCaio Furtado Rosa (https://caiorosadev.com)\nProjeto: https://github.com/caiorosa-dev/astar-c-algorithm");
    printf("\n-------------------------------------------------------");
    return 0;
}
