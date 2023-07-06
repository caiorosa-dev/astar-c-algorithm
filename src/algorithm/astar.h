#include "../config.h"
#include "algorithmUtils.h"

Node parents[ROWS][COLS];

Node calculateScores(Node node, Node end, bool hasParents) {
    node.hScore = calculateDistance(node, end);
    node.gScore = 0;
    if (hasParents) {
        node.gScore = parents[node.row][node.col].gScore + 1;
    }
    node.fScore = node.gScore + node.hScore;

    return node;
}

void runAStarAlgorithm(Node start, Node end) {
        if (!isNodeValid(start) || !isNodeValid(end)) {
        printf("Posicao inicial ou final invalida!\n");
        return;
    }

    if (start.col == end.col && end.row == start.row) {
        printf("Voce ja esta no destino!\n");
        return;
    }

    int closedList[ROWS][COLS];
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            closedList[row][col] = 0;
        }
    }

    Node openList[ROWS * COLS];
    int openListSize = 0;

    start = calculateScores(start, end, false);
    openList[openListSize++] = start;

    while (openListSize > 0) {
        // Primeiro se procura pelo ponto mais próximo disponível
        int minFScore = 0;
        for (int i = 1; i < openListSize; i++) {
            if (openList[i].fScore < openList[minFScore].fScore) {
                minFScore = i;
            }
        }

        Node currentNode = openList[minFScore];
        // Forma de remover o ponto atual da lista
        openList[minFScore] = openList[openListSize - 1];
        openListSize--;
        closedList[currentNode.row][currentNode.col] = 1;

        // Aqui é realizada a procura por vizinhos
        int exploreRow[] = {-1, 1, 0, 0}; // Cima e baixo
        int exploreCol[] = {0, 0, -1, 1}; // Esquerda e direita

        for (int i = 0; i < 4; ++i) {
            Node neighbor;

            neighbor.row = currentNode.row + exploreRow[i];
            neighbor.col = currentNode.col + exploreCol[i];

            if (isNodeValid(neighbor)) {
                // Se o destino for o vizinho, chegamos ao final
                if (calculateDistance(neighbor, end) == 0) {
                    parents[neighbor.row][neighbor.col] = currentNode;
                    showPath(parents, end, start, true);
                    return;
                }

                if (!closedList[neighbor.row][neighbor.col]) {
                    parents[neighbor.row][neighbor.col] = currentNode;
                    neighbor = calculateScores(neighbor, end, true);

                    bool inOpenList = false;

                    // Verificar se o vizinho já está na lista aberta
                    for (int j = 0; j < openListSize; j++) {
                        if (openList[j].row == neighbor.row && openList[j].col == neighbor.col) {
                            inOpenList = true;

                            // Se o novo caminho para o vizinho é melhor, atualiza os valores
                            if (neighbor.fScore < openList[j].fScore) {
                                openList[j].fScore = neighbor.fScore;
                                openList[j].gScore = neighbor.gScore;
                                openList[j].hScore = neighbor.hScore;
                            }
                            break;
                        }
                    }

                    if (!inOpenList) {
                        openList[openListSize++] = neighbor;
                    }
                }
            }
        }
    }

    printf("Nao foi possivel encontrar um caminho\n\n");
}