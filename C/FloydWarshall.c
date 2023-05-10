#include <stdio.h>
#include <stdbool.h>
#define INF 100000000
int number = 5;
int d[5];
int prev[5];
bool visited[5];
int arr[5][5] = {
    {0, 4, 2, 5, INF},
    {INF, 0, 1, INF, 4},
    {1, 3, 0, 1, 2},
    {-2, INF, INF, 0, 2},
    {INF, -3, 3, 1, 0}
};

void floydwarshall() {
    int d[number][number]; // 결과 그래프를 입력으로 초기화
    for (int i = 0 ; i < number ; i++) {
        for (int  j = 0 ; j < number ; j++) {
            d[i][j] = arr[i][j];
        }
    }
    // k = 거쳐가는 노드
    for (int k = 0 ; k < number ; k++) {
        // i = 출발노드
        for (int i = 0 ; i < number ; i++) {
            // j = 도착 노드
            for (int j = 0 ; j < number ; j++) {
                if (d[i][k] + d[k][j] < d[i][j]) { // 한번에 가는 것보다 둘러가는게 더 적을 경우
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
    // 결과 출력
    printf("FloyWarshall Result\n");
    for (int i = 0 ; i < number ; i++) {
        for (int j = 0 ; j < number ; j++) {
            printf("%d ", d[i][j]);
        }
        printf("\n");
    }
}
void dijkstra(int start) {
    // 출발점으로부터의 최소 비용 초기화
    for (int i = 0; i < 5; i++) {
        d[i] = arr[start][i];
        visited[i] = false;
        prev[i] = start; // 모든 노드의 이전 노드는 출발 노드로 설정
    }
    visited[start] = true; // 출발 노드는 이미 방문한 것으로 처리
    
    // 출발점에서부터 모든 노드까지의 최소 비용 계산
    for (int i = 0; i < 4; i++) { // 출발점은 이미 처리한 것으로 카운트되므로 4번만 반복
        int min_cost = INF; // 아직 방문하지 않은 노드 중 최소 비용을 가진 노드 선택
        int current_node = 0;
        for (int j = 0; j < 5; j++) {
            if (!visited[j] && d[j] < min_cost) {
                min_cost = d[j];
                current_node = j;
            }
        }
        visited[current_node] = true; // 선택한 노드를 방문한 것으로 처리
        
        // 선택한 노드의 이웃 노드들의 최소 비용 갱신
        for (int k = 0; k < 5; k++) {
            if (!visited[k] && d[current_node] + arr[current_node][k] < d[k]) {
                d[k] = d[current_node] + arr[current_node][k];
                prev[k] = current_node; // 해당 노드까지의 최단 경로 상 이전 노드를 갱신
            }
        }
    }
    // 결과 출력
    printf("Dijkstra Result(start : %d) : ", start+1);
    for (int i = 0 ; i < number ; i++) {
        printf("%d ", d[i]);
    }
}
int main(void) {
    floydwarshall();
    printf("------------------------------------------\n");
    for (int i = 0 ; i < number ; i++) {
        dijkstra(i);
        printf("\n");
    }
}