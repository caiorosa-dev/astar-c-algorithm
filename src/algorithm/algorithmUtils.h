//
// Created by Caio on 06/07/2023.
//

#ifndef ASTARPROJECT_ALGORITHMUTILS_H
#define ASTARPROJECT_ALGORITHMUTILS_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "../config.h"
#include "../libs/utils.h"

typedef struct {
    int row;
    int col;
    int fScore;
    int gScore;
    int hScore;
} Node;

int calculateDistance(Node from, Node to) {
    return abs(from.col - to.col) + abs(from.row - to.row);
}

bool isNodeValid(Node node) {
    bool isValidColPosition = node.col < COLS && node.col >= 0;
    bool isValidRowPosition = node.row < ROWS && node.row >= 0;
    if (!isValidColPosition || !isValidRowPosition) {
        return false;
    }

    bool isUnblocked = grid[node.row][node.col] == 0;

    return isUnblocked;
}

void showPath(Node parents[][COLS], Node end, Node start, bool animate) {
    int row = end.row;
    int col = end.col;
    int count = 0;

    Node path[ROWS * COLS];

    while (!(parents[row][col].row == row && parents[row][col].col == col)) {
        path[count++] = parents[row][col];
        
        int parentRow = parents[row][col].row;
        int parentCol = parents[row][col].col;
        
        row = parentRow;
        col = parentCol;
    }

    for (int i = 0; i < (COLS + 2); ++i) {
        printf("___");
    }

    printf("\n");

    for (int rowI = 0; rowI < ROWS; ++rowI) {
        printf("[  ");
        for (int colI = 0; colI < COLS; ++colI) {
            char display = ' ';

            for (int i = 0; i < count; ++i) {
                Node node = path[i];

                if (node.row == rowI && node.col == colI) {
                    display = '*';
                }
            }

            if (end.row == rowI && end.col == colI) {
                display = '+';
            }

            if (start.row == rowI && start.col == colI) {
                display = '-';
            }

            if (grid[rowI][colI] == 1) {
                display = '|';
            }

            printf(" %c ", display);
            if (animate) {
                sleepMs(150);
            }
        }
        printf("  ]\n");
    }

    for (int i = 0; i < (COLS + 2); ++i) {
        printf("---");
    }

    if (animate) {
        sleepMs(150);
        clearTerminal();
        showPath(parents, end, start, false);
    }
}

void showGrid(Node start, Node end) {
    int counter = 0;
    for (int i = 0; i < (COLS + 2); ++i) {
        if (i > 0 && counter < COLS) {
            printf("_%d_", counter);
            counter++;
            continue;
        }
        printf("___");
    }
    printf("\n");

    for (int rowI = 0; rowI < ROWS; ++rowI) {
        printf("%d  ", rowI);
        for (int colI = 0; colI < COLS; ++colI) {
            char display = ' ';

            if (grid[rowI][colI] == 1) {
                display = '|';
            }

            if (end.row == rowI && end.col == colI) {
                display = '+';
            }

            if (start.row == rowI && start.col == colI) {
                display = '-';
            }

            printf(" %c ", display);
        }
        printf("  ]\n");
    }

    for (int i = 0; i < (COLS + 2); ++i) {
        printf("___");
    }
}

#endif //ASTARPROJECT_ALGORITHMUTILS_H
