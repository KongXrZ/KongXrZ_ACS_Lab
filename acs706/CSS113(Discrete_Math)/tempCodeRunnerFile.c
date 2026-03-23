#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100
#define INF 1e9f

int N, M;
float G[MAX][MAX];

//แปลงชื่อของNode
int usechar; // 1 = A,B,C, 0 = 1,2,3
int toIndex(char s[]) {
    if (isdigit(s[0])) return atoi(s) - 1;
    return toupper(s[0]) - 'A';
}
void printNode(int idx) {
    if (usechar) printf("%c", 'A' + idx);
    else printf("%d", idx + 1);
}

void DFS_Rec(int u, bool visited[]) {
    visited[u] = true;
    for (int v = 0; v < N; v++) {
        if (G[u][v] < INF && !visited[v]) {
            printNode(u); printf(" - "); printNode(v);
            printf(" (weight %.2f)\n", G[u][v]);
            DFS_Rec(v, visited);
        }
    }
}

void BFS(int start) {
    bool visited[MAX] = {false};
    int queue[MAX], front = 0, rear = 0;
    visited[start] = true;
    queue[rear++] = start;

    printf("\nBFS Spanning Tree:\n");
    while (front < rear) {
        int u = queue[front++];
        for (int v = 0; v < N; v++) {
            if (G[u][v] < INF && !visited[v]) {
                visited[v] = true;
                queue[rear++] = v;
                printNode(u); printf(" - "); printNode(v);
                printf(" (weight %.2f)\n", G[u][v]);
            }
        }
    }
}

void Dijkstra(int start, int target) {
    float dist[MAX];
    int parent[MAX];
    bool visited[MAX] = {false};

    for (int i = 0; i < N; i++) {
        dist[i] = INF;
        parent[i] = -1;//กันไปซ้อนกับค่าของNodeแรกจริงๆ (index = 0)
    }
    dist[start] = 0;

    for (int i = 0; i < N; i++) {
        int u = -1;
        for (int j = 0; j < N; j++)
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) u = j;

        if (dist[u] == INF) break;
        visited[u] = true;

        for (int v = 0; v < N; v++) {
            if (G[u][v] < INF && dist[u] + G[u][v] < dist[v]) {
                dist[v] = dist[u] + G[u][v];
                parent[v] = u;
            }
        }
    }

    printf("\nShortest Path: ");
    if (dist[target] == INF) printf("No Path\n");
    else {
        printf("Distance = %.2f\nPath: ", dist[target]);
        int path[MAX], len = 0;
        for (int v = target; v != -1; v = parent[v]) path[len++] = v;
        for (int i = len - 1; i >= 0; i--) {
            printNode(path[i]);
            if (i > 0) printf(" -> ");
        }
        printf("\n");
    }
}

void Prim(int start) {
    float key[MAX]; //weight
    int parent[MAX];
    bool inMST[MAX] = {false};
    for (int i = 0; i < N; i++) { key[i] = INF; parent[i] = -1; }
    key[start] = 0;

    float totalWeight = 0;
    printf("\nPrim MST:\n");
    for (int i = 0; i < N; i++) {
        int u = -1;
        for (int j = 0; j < N; j++)
            if (!inMST[j] && (u == -1 || key[j] < key[u])) u = j;
        
        if (u == -1 || key[u] == INF) break;
        inMST[u] = true;
        if (parent[u] != -1) {
            printNode(parent[u]); printf(" - "); printNode(u);
            printf(" (weight %.2f)\n", key[u]);
            totalWeight += key[u];
        }

        for (int v = 0; v < N; v++)
            if (G[u][v] < INF && !inMST[v] && G[u][v] < key[v]) {
                key[v] = G[u][v];
                parent[v] = u;
            }
    }
    printf("Total Weight: %.2f\n", totalWeight);
}

//Kruskal Logic
typedef struct { int u, v; float w; } Edge;
int parentUF[MAX];
int find(int x) { return (parentUF[x] == x) ? x : (parentUF[x] = find(parentUF[x])); }

void Kruskal() {
    Edge edges[MAX * MAX];
    int edgeCount = 0;
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            if (G[i][j] < INF) edges[edgeCount++] = (Edge){i, j, G[i][j]};

    for (int i = 0; i < edgeCount; i++)
        for (int j = i + 1; j < edgeCount; j++)
            if (edges[j].w < edges[i].w) { Edge t = edges[i]; edges[i] = edges[j]; edges[j] = t; }

    for (int i = 0; i < N; i++) parentUF[i] = i;

    float total = 0;
    printf("\nKruskal MST:\n");
    for (int i = 0; i < edgeCount; i++) {
        int rootU = find(edges[i].u), rootV = find(edges[i].v);
        if (rootU != rootV) {
            parentUF[rootV] = rootU;
            printNode(edges[i].u); printf(" - "); printNode(edges[i].v);
            printf(" (weight %.2f)\n", edges[i].w);
            total += edges[i].w;
        }
    }
    printf("Total Weight: %.2f\n", total);
}


int main() {
    char uStr[10], vStr[10];
    printf("Use node names as (1:A,B,C / 0:1,2,3): ");
    scanf("%d", &usechar);
    printf("Enter number of Nodes and Edges (Ex.: 5 4): ");
    scanf("%d %d", &N, &M);
    if (N > MAX) { printf("Error!!! Max nodes is %d\n", MAX); return 1; }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) G[i][j] = (i == j) ? 0 : INF;

    printf("Enter edges (u v weight):\n");
    for (int i = 0; i < M; i++) {
        float w;
        scanf("%s %s %f", uStr, vStr, &w);
        int u = toIndex(uStr), v = toIndex(vStr);
        if (u < 0 || u >= N || v < 0 || v >= N) {
            printf("Error: Invalid node index\n");
            return 1;}
        G[u][v] = G[v][u] = w;
    }

    int choice;
    while (1) {
        printf("\n--- MENU ---\n1.DFS 2.BFS 3.Dijkstra 4.Prim 5.Kruskal 0.Exit\nSelect: ");
        scanf("%d", &choice);
        if (choice == 0) break;
        if (choice < 0 || choice > 5){
            printf("Error!!! We don't have this menu try again.");
            continue;
        }

        printf("Enter Start Node: ");
        scanf("%s", uStr);
        int s = toIndex(uStr);

        if (choice == 1) { 
            bool vis[MAX] = {false}; //visited out recursion
            printf("\nDFS Spanning Tree:\n"); 
            DFS_Rec(s, vis); 
        }
        else if (choice == 2) BFS(s);
        else if (choice == 3) {
            printf("Enter Target Node: ");
            scanf("%s", vStr);
            Dijkstra(s, toIndex(vStr));
        }
        else if (choice == 4) Prim(s);
        else if (choice == 5) Kruskal();
    }

    return 0;
}