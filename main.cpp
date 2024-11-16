#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <queue> 
using namespace std;

int** createG(int size) {
    int** G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; ++i) {
        G[i] = (int*)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; ++i) {
        for (int j = i; j < size; ++j) {
            G[i][j] = rand() % 2;
            G[j][i] = (i == j) ? 0 : G[i][j];
        }
    }
    return G;
}

void printG(int** G, int size) {
    printf("  ");
    for (int i = 0; i < size; ++i) printf("%d ", i);
    printf("\n");
    for (int i = 0; i < size; ++i) {
        printf("%d ", i);
        for (int j = 0; j < size; ++j) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


void BFS(int** G, int size, int* vis, int s) {
    queue <int> q;
    q.push(s);
    vis[s] = 1;

    while (!q.empty()) {
        s = q.front();
        q.pop();
        printf("%d ", s);
        for (int i = 0; i < size; ++i) {
            if (G[s][i] && !vis[i]) {
                q.push(i);
                vis[i] = 1;

            }
        }
    }
    for (int i = 0; i < size; ++i) {
        if (!vis[i]) {
            printf("\n");
            BFS(G, size, vis, i);
        }
    }
   

}

int main() {
    setlocale(LC_ALL, "Rus");
    int n = 4;
    int** M1 = NULL;
    printf("Введите количество вершин: ");
    srand(time(NULL));

    //scanf("%d", &n);
    int* vis = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) vis[i] = 0;
    printf("\n");

    M1 = createG(n);
    printf("Граф G1\n");
    printG(M1, n);
    BFS(M1, n, vis, 0);
}