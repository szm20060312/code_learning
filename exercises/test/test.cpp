#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#define MAX_VERTICES 50
#define MAX_NAME_LEN 50
#define INF INT_MAX

// 图结构定义
typedef struct {
    char name[MAX_NAME_LEN];   // 顶点名称
    int index;                 // 顶点索引
} Vertex;

typedef struct {
    int vertexCount;           // 顶点数量
    Vertex vertices[MAX_VERTICES]; // 顶点数组
    int adjMatrix[MAX_VERTICES][MAX_VERTICES]; // 邻接矩阵
    int originalMatrix[MAX_VERTICES][MAX_VERTICES]; // 原始邻接矩阵备份
} Graph;

// 函数声明
void initGraph(Graph *g);
int findVertexIndex(Graph *g, const char *name);
void readGraphFromFile(Graph *g, const char *filename);
void dijkstra(Graph *g, int start, int end, int path[]);
void printPath(Graph *g, int path[], int end);
void randomlyBlockRoad(Graph *g);
void saveResultToFile(Graph *g, int path[], int end, const char *filename);

int main() {
    Graph campusGraph;
    initGraph(&campusGraph);
    
    // 从文件读取图数据
    readGraphFromFile(&campusGraph, "path.txt");
    
    char startName[MAX_NAME_LEN], endName[MAX_NAME_LEN];
    int startIdx, endIdx;
    
    // 用户输入
    printf("请输入起点位置: ");
    scanf("%s", startName);
    printf("请输入终点位置: ");
    scanf("%s", endName);
    
    // 查找顶点索引
    startIdx = findVertexIndex(&campusGraph, startName);
    endIdx = findVertexIndex(&campusGraph, endName);
    
    if (startIdx == -1 || endIdx == -1) {
        printf("错误：输入的起点或终点不存在！\n");
        return 1;
    }
    
    // 路径数组（存储前驱节点）
    int path[MAX_VERTICES];
    
    // 计算最短路径
    dijkstra(&campusGraph, startIdx, endIdx, path);
    
    // 输出最短路径
    printf("\n最短路径: ");
    printPath(&campusGraph, path, endIdx);
    printf("\n");
    
    // 保存结果到文件
    saveResultToFile(&campusGraph, path, endIdx, "result.txt");
    
    // 随机道路封闭模拟
    printf("\n正在模拟随机道路封闭...\n");
    randomlyBlockRoad(&campusGraph);
    
    // 重新计算最短路径
    dijkstra(&campusGraph, startIdx, endIdx, path);
    
    // 输出重新规划后的路径
    printf("\n重新规划后的路径: ");
    printPath(&campusGraph, path, endIdx);
    printf("\n");
    
    return 0;
}

// 初始化图
void initGraph(Graph *g) {
    g->vertexCount = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adjMatrix[i][j] = INF;
            g->originalMatrix[i][j] = INF;
        }
    }
}

// 查找顶点索引
int findVertexIndex(Graph *g, const char *name) {
    for (int i = 0; i < g->vertexCount; i++) {
        if (strcmp(g->vertices[i].name, name) == 0) {
            return i;
        }
    }
    return -1; // 未找到
}

// 从文件读取图数据
void readGraphFromFile(Graph *g, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("无法打开文件");
        exit(EXIT_FAILURE);
    }
    
    // 读取顶点数量
    fscanf(file, "%d", &g->vertexCount);
    
    // 读取顶点名称
    for (int i = 0; i < g->vertexCount; i++) {
        fscanf(file, "%s", g->vertices[i].name);
        g->vertices[i].index = i;
    }
    
    // 读取邻接关系
    char line[256];
    fgets(line, sizeof(line), file); // 跳过换行符
    
    for (int i = 0; i < g->vertexCount; i++) {
        if (fgets(line, sizeof(line), file) == NULL) break;
        
        char *token = strtok(line, " \t\n");
        if (token == NULL) continue;
        
        int fromIdx = findVertexIndex(g, token);
        if (fromIdx == -1) continue;
        
        token = strtok(NULL, " \t\n");
        while (token != NULL) {
            int toIdx = findVertexIndex(g, token);
            if (toIdx != -1) {
                // 默认权重为1
                g->adjMatrix[fromIdx][toIdx] = 1;
                g->adjMatrix[toIdx][fromIdx] = 1;
            }
            token = strtok(NULL, " \t\n");
        }
    }
    
    // 备份原始邻接矩阵
    for (int i = 0; i < g->vertexCount; i++) {
        for (int j = 0; j < g->vertexCount; j++) {
            g->originalMatrix[i][j] = g->adjMatrix[i][j];
        }
    }
    
    fclose(file);
}

// Dijkstra算法实现
void dijkstra(Graph *g, int start, int end, int path[]) {
    int dist[MAX_VERTICES];
    int visited[MAX_VERTICES] = {0};
    
    // 初始化
    for (int i = 0; i < g->vertexCount; i++) {
        dist[i] = INF;
        path[i] = -1;
    }
    dist[start] = 0;
    
    for (int count = 0; count < g->vertexCount - 1; count++) {
        // 找到最小距离的顶点
        int minDist = INF, minIndex = -1;
        for (int v = 0; v < g->vertexCount; v++) {
            if (!visited[v] && dist[v] < minDist) {
                minDist = dist[v];
                minIndex = v;
            }
        }
        
        if (minIndex == -1) break;
        visited[minIndex] = 1;
        
        // 更新相邻顶点距离
        for (int v = 0; v < g->vertexCount; v++) {
            if (!visited[v] && g->adjMatrix[minIndex][v] != INF && 
                dist[minIndex] != INF && 
                dist[minIndex] + g->adjMatrix[minIndex][v] < dist[v]) {
                dist[v] = dist[minIndex] + g->adjMatrix[minIndex][v];
                path[v] = minIndex;
            }
        }
    }
    
    // 输出最短距离
    if (dist[end] == INF) {
        printf("\n从 %s 到 %s 没有路径!\n", g->vertices[start].name, g->vertices[end].name);
    } else {
        printf("\n从 %s 到 %s 的最短距离: %d\n", 
              g->vertices[start].name, g->vertices[end].name, dist[end]);
    }
}

// 打印路径
void printPath(Graph *g, int path[], int end) {
    if (path[end] == -1) {
        printf("%s", g->vertices[end].name);
        return;
    }
    
    // 递归打印路径
    printPath(g, path, path[end]);
    printf(" -> %s", g->vertices[end].name);
}

// 随机封闭道路
void randomlyBlockRoad(Graph *g) {
    srand(time(NULL));
    
    // 随机选择一条存在的边
    int from, to;
    int attempts = 0;
    
    do {
        from = rand() % g->vertexCount;
        to = rand() % g->vertexCount;
        attempts++;
    } while ((g->adjMatrix[from][to] == INF || from == to) && attempts < 100);
    
    if (attempts >= 100) {
        printf("没有找到可封闭的道路！\n");
        return;
    }
    
    printf("道路 %s 到 %s 因维修封闭！\n", 
          g->vertices[from].name, g->vertices[to].name);
    
    // 封闭道路
    g->adjMatrix[from][to] = INF;
    g->adjMatrix[to][from] = INF;
}

// 保存结果到文件
void saveResultToFile(Graph *g, int path[], int end, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("无法创建结果文件");
        return;
    }
    
    fprintf(file, "校园最短路径结果\n\n");
    
    // 找到起点
    int start = end;
    while (path[start] != -1) {
        start = path[start];
    }
    
    fprintf(file, "从 %s 到 %s 的路径:\n", 
           g->vertices[start].name, g->vertices[end].name);
    
    // 打印路径到文件
    if (path[end] == -1 && start != end) {
        fprintf(file, "没有路径！");
    } else {
        // 使用栈反向存储路径
        int stack[MAX_VERTICES], top = -1;
        int current = end;
        
        while (current != -1) {
            stack[++top] = current;
            current = path[current];
        }
        
        // 输出路径
        while (top >= 0) {
            fprintf(file, "%s", g->vertices[stack[top]].name);
            if (top > 0) fprintf(file, " -> ");
            top--;
        }
    }
    
    fclose(file);
    printf("\n结果已保存到 %s\n", filename);
    
}