#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <queue> 
using namespace std;

typedef struct node {
    int data;
    struct node* next;
} node;

void push(node** queue, int data) {
    node* current = *queue;
    if (current) {
        while (current->next) {
            current = current->next;
        }
    }
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;
    if (current) current->next = newNode;
    else *queue = newNode;
}

void pop(node** queue) {
    node* current = *queue;
    *queue = (*queue)->next;
    free(current);
}


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

node** createAdj(int** G, int size) {
    node** A = (node**)malloc(size * sizeof(node*));
    for (int i = 0; i < size; ++i) {
        A[i] = NULL;
        node* tail = NULL;
        for (int j = 0; j < size; ++j) {
            if (G[i][j] == 1) {
                node* newNode = (node*)malloc(sizeof(node));
                newNode->data = j;
                newNode->next = NULL;
                if (tail == NULL) {
                    A[i] = newNode;
                }
                else {
                    tail->next = newNode;
                }
                tail = newNode;
            }
        }
    }
    return A;
}

void printAdj(node** A, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d: ", i);
        node* current = A[i];
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
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
        //printf("%d ", s);
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

void BFSA(node** A, int size, int* vis, int s) {
    queue <int> q;
    q.push(s);
    vis[s] = 1;
    node* current = NULL;
    while (!q.empty()) {
        current = A[q.front()];
        //printf("%d ", q.front());
        q.pop();

        while (current) {
            if (!vis[current->data]) {
                q.push(current->data);
                vis[current->data] = 1;
            }
            current = current->next;
        }
    }
    for (int i = 0; i < size; ++i) {
        if (!vis[i]) {
            printf("\n");
            BFSA(A, size, vis, i);
        }
    }
}

void BFSN(int** G, int size, int* vis, int s) {
    node* q = NULL;
    push(&q,s);
    vis[s] = 1;

    while (q) {
        s = q->data;
        pop(&q);
        //printf("%d ", s);
        for (int i = 0; i < size; ++i) {
            if (G[s][i] && !vis[i]) {
                push(&q, i);
                vis[i] = 1;

            }
        }
    }
    for (int i = 0; i < size; ++i) {
        if (!vis[i]) {
            printf("\n");
            BFSN(G, size, vis, i);
        }
    }
}

int main() {

    clock_t start, end;
    setlocale(LC_ALL, "Rus");
    int n = 10000;
    int** M1 = NULL;
    //node** A1 = NULL;
    //printf("Введите количество вершин: ");
    srand(time(NULL));

    //scanf("%d", &n);
    int* vis = (int*)malloc(sizeof(int) * n);

    M1 = createG(n);
    //A1 = createAdj(M1, n);
    //printf("Граф G1\n");
    //printG(M1, n);

    //printAdj(A1, n);
    //for (int i = 0; i < n; ++i) vis[i] = 0;
    //BFSA(A1, n, vis, 0);
    //printf("\n");

    for (int i = 0; i < n; ++i) vis[i] = 0;
    FILE* file = fopen("result.csv", "w");

    start = clock();
    //printf("\n");
    BFS(M1, n, vis, 0);
    //printf("\n");
    end = clock();
    float spent_time = (float)(end - start) / CLOCKS_PER_SEC;
    printf("BFS;%.3f;\n", spent_time);
    fprintf(file, "BFS;%.3f;\n", spent_time);
    for (int i = 0; i < n; ++i) vis[i] = 0;
    start = clock();
    //printf("\n");
    BFSN(M1, n, vis, 0);
    //printf("\n");
    end = clock();
    spent_time = (float)(end - start) / CLOCKS_PER_SEC;
    printf("BFSN;% .3f;", spent_time);
    fprintf(file, "BFSN;%.3f;\n", spent_time);
    fclose(file);

    free(M1);
    //free(A1);
    free(vis);
}