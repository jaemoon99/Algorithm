#include <stdio.h>
#include <limits.h>
#define V 10
#define INF 99999

char region[10][10] = { "천안", "논산", "서울", "광주", "대전", "원주", "강릉", "대구", "포항", "부산" };

// 최소 거리를 찾는 함수
int minDistance(int dist[], int sptSet[]) {
    int min = INF, min_index;
    for (int v = 0; v < V; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

// 결과를 출력하는 함수
void printSolution(int dist[]) {
    printf("Vertex \t Distance from Seoul\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// 다익스트라 알고리즘 함수
void dijkstra(int graph[V][V], int src) {
    int dist[V]; // 최단 거리를 저장하는 배열
    int sptSet[V]; // 방문한 정점을 저장하는 배열

    // 모든 정점에 대해 초기 거리를 무한대로 설정하고 방문하지 않은 것으로 초기화
    for (int i = 0; i < V; i++)
        dist[i] = INF, sptSet[i] = 0;

    // 시작 정점의 거리를 0으로 설정
    dist[src] = 0;

    // 모든 정점에 대해
    for (int count = 0; count < V - 1; count++) {
        // 아직 방문하지 않은 정점 중 거리가 가장 작은 정점을 선택
        int u = minDistance(dist, sptSet);

        // 선택한 정점을 방문 처리
        sptSet[u] = 1;

        // 선택한 정점을 기준으로 인접한 정점의 거리를 업데이트
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // 결과를 출력
    printSolution(dist);
}

int main() {

    int graph[V][V] = {
        {0, 4, 12, 0, 10, 0, 0, 0, 0, 0},
        {4, 0, 0, 13, 3, 0, 0, 0, 0, 0},
        {12, 0, 0, 0, 0, 15, 0, 0, 0, 0},
        {0, 13, 0, 0, 0, 0, 0, 0, 0, 15},
        {10, 3, 0, 0, 0, 0, 0, 10, 0, 0},
        {0, 0, 15, 0, 0, 0, 21, 7, 0, 0},
        {0, 0, 0, 0, 0, 21, 0, 0, 25, 0},
        {0, 0, 0, 0, 10, 7, 0, 0, 19, 9},
        {0, 0, 0, 0, 0, 0, 25, 19, 0, 5},
        {0, 0, 0, 15, 0, 0, 0, 9, 5, 0}
    };

    dijkstra(graph, 8); // 서울은 인덱스 2에 해당합니다

    return 0;
}