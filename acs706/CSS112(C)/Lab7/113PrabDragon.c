#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 26
#define INF 1e9f

int N;
float graph[MAX][MAX];
bool visited[MAX];
int useChar; // 1 = A,B,C..., 0 = 1,2,3...

// --------------------- Convert ---------------------

// string → index 0-based
int toIndex(char s[])
{
    if (isdigit(s[0]))
    {
        int x = atoi(s);
        return x - 1; // Node start from 1
    }
    char c = toupper(s[0]);
    if (c >= 'A' && c <= 'Z')
        return c - 'A';
    return -1;
}

// index → print node
void printNode(int idx)
{
    if (useChar)
        printf("%c", 'A' + idx);
    else
        printf("%d", idx + 1);
}

// --------------------- DFS -------------------------
void DFS(int u)
{
    visited[u] = true;
    for (int v = 0; v < N; v++)
    {
        if (!visited[v] && graph[u][v] < INF)
        {
            printf("Edge in DFS Spanning Tree: ");
            printNode(u);
            printf(" - ");
            printNode(v);
            printf("\n");
            DFS(v);
        }
    }
}

// --------------------- BFS -------------------------
void BFS(int start)
{
    bool vis[MAX] = {false};
    int queue[MAX], front = 0, rear = 0;

    vis[start] = true;
    queue[rear++] = start;

    while (front < rear)
    {
        int u = queue[front++];
        for (int v = 0; v < N; v++)
        {
            if (!vis[v] && graph[u][v] < INF)
            {
                printf("Edge in BFS Spanning Tree: ");
                printNode(u);
                printf(" - ");
                printNode(v);
                printf("\n");

                vis[v] = true;
                queue[rear++] = v;
            }
        }
    }
}

// --------------------- Dijkstra --------------------
void Dijkstra(int start, int end)
{
    float dist[MAX];
    int prev[MAX];
    bool used[MAX];

    for (int i = 0; i < N; i++)
    {
        dist[i] = INF;
        prev[i] = -1;
        used[i] = false;
    }

    dist[start] = 0;

    for (int k = 0; k < N - 1; k++)
    {
        int u = -1;
        float best = INF;

        for (int i = 0; i < N; i++)
            if (!used[i] && dist[i] < best)
                best = dist[i], u = i;

        if (u == -1)
            break;
        used[u] = true;

        for (int v = 0; v < N; v++)
            if (graph[u][v] < INF)
            {
                float nd = dist[u] + graph[u][v];
                if (nd < dist[v])
                {
                    dist[v] = nd;
                    prev[v] = u;
                }
            }
    }

    printf("\nShortest Path Distance = %.2f\n", dist[end]);

    int path[MAX], len = 0;
    for (int v = end; v != -1; v = prev[v])
        path[len++] = v;

    printf("Path: ");
    for (int i = len - 1; i >= 0; i--)
    {
        printNode(path[i]);
        if (i)
            printf(" -> ");
    }
    printf("\n");
}

// --------------------- Prim MST --------------------
void Prim(int start)
{
    float key[MAX];
    int parent[MAX];
    bool mst[MAX];

    for (int i = 0; i < N; i++)
    {
        key[i] = INF;
        parent[i] = -1;
        mst[i] = false;
    }

    key[start] = 0;

    for (int count = 0; count < N - 1; count++)
    {
        int u = -1;
        float best = INF;

        for (int i = 0; i < N; i++)
            if (!mst[i] && key[i] < best)
                best = key[i], u = i;

        mst[u] = true;

        for (int v = 0; v < N; v++)
            if (!mst[v] && graph[u][v] < INF && graph[u][v] < key[v])
            {
                key[v] = graph[u][v];
                parent[v] = u;
            }
    }

    printf("\nPrim MST:\n");

    for (int i = 0; i < N; i++)
        if (parent[i] != -1)
        {
            printNode(parent[i]);
            printf(" - ");
            printNode(i);
            printf(" (%.2f)\n", key[i]);
        }
}

// --------------------- Kruskal MST -----------------
int uf[MAX];

int findUF(int x)
{
    if (uf[x] == x)
        return x;
    return uf[x] = findUF(uf[x]);
}

void uni(int a, int b)
{
    a = findUF(a);
    b = findUF(b);
    if (a != b)
        uf[b] = a;
}

typedef struct
{
    int u, v;
    float w;
} Edge;

void Kruskal()
{
    Edge edges[300];
    int ec = 0;

    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            if (graph[i][j] < INF)
                edges[ec++] = (Edge){i, j, graph[i][j]};

    // sort edges ascending
    for (int i = 0; i < ec; i++)
        for (int j = i + 1; j < ec; j++)
            if (edges[j].w < edges[i].w)
            {
                Edge tmp = edges[i];
                edges[i] = edges[j];
                edges[j] = tmp;
            }

    for (int i = 0; i < N; i++)
        uf[i] = i;

    printf("\nKruskal MST:\n");

    for (int i = 0; i < ec; i++)
    {
        int u = edges[i].u;
        int v = edges[i].v;

        if (findUF(u) != findUF(v))
        {
            uni(u, v);
            printNode(u);
            printf(" - ");
            printNode(v);
            printf(" (%.2f)\n", edges[i].w);
        }
    }
}

// --------------------- MAIN ------------------------

int main()
{
    int E;
    char A[10], B[10];

    printf("Use character nodes? (1=A,B,C  /  0=1,2,3): ");
    scanf("%d", &useChar);

    printf("Number of nodes: ");
    scanf("%d", &N);

    // init graph
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            graph[i][j] = INF;

    printf("Number of edges: ");
    scanf("%d", &E);

    for (int i = 0; i < E; i++)
    {
        float w;
        printf("Edge %d (u v w): ", i + 1);
        scanf("%s %s %f", A, B, &w);

        int u = toIndex(A);
        int v = toIndex(B);

        graph[u][v] = graph[v][u] = w;
    }

    printf("\n===== MENU =====\n");
    printf("1. DFS\n");
    printf("2. BFS\n");
    printf("3. Dijkstra\n");
    printf("4. Prim\n");
    printf("5. Kruskal\n");
    printf("Select: ");

    int choice;
    scanf("%d", &choice);

    printf("Start node: ");
    scanf("%s", A);
    int start = toIndex(A);

    if (choice == 1)
    {
        for (int i = 0; i < N; i++)
            visited[i] = false;
        DFS(start);
    }
    else if (choice == 2)
        BFS(start);
    else if (choice == 3)
    {
        printf("End node: ");
        scanf("%s", B);
        int end = toIndex(B);
        Dijkstra(start, end);
    }
    else if (choice == 4)
        Prim(start);
    else if (choice == 5)
        Kruskal();

    return 0;
}