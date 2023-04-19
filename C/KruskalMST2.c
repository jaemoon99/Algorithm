#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES]; // 부모 노드

void set_init(int n) //각 정점의 집합관계 초기화
{
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}
// curr가 속하는 집합을 반환한다.
int set_find(int curr)
{
    if (parent[curr] == -1)
        return curr; // 루트 
    return parent[curr] = set_find(parent[curr]);
}

// 두개의 원소가 속한 집합을 합친다.
void set_union(int a, int b)
{
    parent[a] = b;
}

struct Edge { // 간선을 나타내는 구조체
    int start, end, weight;
};

typedef struct GraphType {
    int n, e; // 노드 & 간선의 개수
    struct Edge edges[2 * MAX_VERTICES];
} GraphType;

// 그래프 초기화 
void graph_init(GraphType* g, int n)
{
    g->n = n; g->e = 0;
}
// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end, int w)
{
    g->edges[g->e].start = start;
    g->edges[g->e].end = end;
    g->edges[g->e].weight = w;
    g->e++;
}
// qsort()에 사용되는 함수
int compare(const void* a, const void* b)
{
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight); // 간선의 가중치를 가지고 정렬
}

char names(int n) {
    char name_s = '1';
    switch (n)
    {
    case 1:
        name_s = 'a';
        break;
    case 2:
        name_s = 'b';
        break;
    case 3:
        name_s = 'c';
        break;
    case 4:
        name_s = 'd';
        break;
    case 5:
        name_s = 'e';
        break;
    case 6:
        name_s = 'f';
        break;
    default:
        break;
    }
    return name_s;
}

// kruskal의 최소 비용 신장 트리 프로그램
void kruskal(GraphType* g)
{
    int edge_accepted = 0; // 현재까지 선택된 간선의 수
    int uset, vset; // 정점 u와 정점 v의 집합 번호
    char name_u, name_s;
    struct Edge* e;

    set_init(g->n); // 집합 초기화
    qsort(g->edges, g->e, sizeof(struct Edge), compare); //간선의 가중치 오름차순 정렬

    printf("크루스칼 최소 신장 트리 알고리즘 \n");
    int i = 0;
    while (edge_accepted < (g->n - 1)) // 간선의 수 < (n-1)
    {
        e = g->edges + i;
        uset = set_find(e->start); // 정점 u의 집합 번호 
        vset = set_find(e->end); // 정점 v의 집합 번호
        if (uset != vset) { // 서로 속한 집합이 다르면
            name_u = names(uset);
            name_s = names(vset);
            printf("간선 (%c,%c) %d 선택\n", name_u, name_s, e->weight);
            //printf("간선 (%d,%d) %d 선택\n", e->start, e->end, e->weight);
            edge_accepted++;
            set_union(uset, vset); // 두개의 집합을 합친다.
        }
        i++;
    }
}
int main(void)
{
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g, 7);


   /*insert_edge(g, 0, 1, 29);
    insert_edge(g, 1, 2, 16);
    insert_edge(g, 0, 1, 29);
    insert_edge(g, 1, 2, 16);
    insert_edge(g, 2, 3, 12);
    insert_edge(g, 3, 4, 22);
    insert_edge(g, 4, 5, 27);
    insert_edge(g, 5, 0, 10);
    insert_edge(g, 6, 1, 15);
    insert_edge(g, 6, 3, 18);
    insert_edge(g, 6, 4, 25);*/
    insert_edge(g, 2, 3, 1); // b - c : 1
    insert_edge(g, 5, 6, 9); // e - f : 9
    insert_edge(g, 3, 6, 1); // c - f : 1
    insert_edge(g, 2, 6, 2); // b - f : 2
    insert_edge(g, 1, 4, 2); // a - d : 2
    insert_edge(g, 4, 5, 3); // d - e : 3
    insert_edge(g, 1, 5, 4); // a - e : 4
    insert_edge(g, 2, 4, 4); // b - d : 4
    insert_edge(g, 4, 6, 7); // d - f : 7
    insert_edge(g, 1, 2, 8); // a - b : 8 



    kruskal(g);
    free(g);
    return 0;
}