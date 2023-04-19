// #include <stdio.h>
// #define MAXSIZE 6

// int graph[MAXSIZE][MAXSIZE] = {
//     //  A, B, C, D, E, F
//     {0, 3, 0, 2, 4, 0}, // A in
//     {3, 0, 1, 4, 0, 2}, // B in
//     {0, 1, 0, 0, 0, 1}, // C in
//     {2, 4, 0, 0, 5, 7}, // D in
//     {4, 0, 0, 5, 0, 9}, // E in
//     {0, 2, 1, 7, 9, 0}, // F in
// };

// int sel_arr[MAXSIZE];
// int top = 0;

// void append_value(int value)
// {
//     sel_arr[top] = value;
//     top++;
// }

// int remove_dup_value(int remove_value)
// {
//     int count = 0;
//     for (int i = 0; i < top + 1; i++)
//     {
//         if (sel_arr[i] == remove_value)
//         {
//             count++;
//         }
//     }
//     if (count == 0)
//     {
//         return 0;
//     }
//     else
//     {
//         return 1;
//     }
// }

// void prim(int first_value)
// {
//     int index_value = 0;
//     int value = 100;
//     int arr_count = 0;
//     for (int i = 0; i < 6; i++)
//     {
//         if (graph[first_value][i] != 0)
//         {
//             if (value > graph[first_value][i] && arr_count == 0)
//             {
//                 index_value = i;
//                 arr_count++;
//             }
//             else if (graph[first_value][index_value] > graph[first_value][i])
//             {
//                 index_value = i;
//             }
//         }
//     }
//     int remove_result = remove_dup_value(index_value);
//     if (remove_result == 0)
//     {
//         if (index_value == 0)
//         {
//             printf("%s - %d\n", "A", index_value);
//         }
//         else if (index_value == 1)
//         {
//             printf("%s - %d\n", "B", index_value);
//         }
//         else if (index_value == 2)
//         {
//             printf("%s - %d\n", "C", index_value);
//         }
//         else if (index_value == 3)
//         {
//             printf("%s - %d\n", "D", index_value);
//         }
//         else if (index_value == 4)
//         {
//             printf("%s - %d\n", "E", index_value);
//         }
//         else
//         {
//             printf("%s - %d\n", "F", index_value);
//         }
//         append_value(index_value);
//     }
// }

// int main()
// {
//     prim(2);
//     return 0;
// }

#include <stdio.h>
#define MAX_NODES 6
#define MAX_INT 99999
#define NOTDEF -1
#define OUTOFQ -1

// 그래프 구조
int graph[MAX_NODES][MAX_NODES] = {
    //  A, B, C, D, E, F
    {0, 3, 0, 2, 4, 0}, // A in
    {3, 0, 1, 4, 0, 2}, // B in
    {0, 1, 0, 0, 0, 1}, // C in
    {2, 4, 0, 0, 5, 7}, // D in
    {4, 0, 0, 5, 0, 9}, // E in
    {0, 2, 1, 7, 9, 0}, // F in
};

int key[MAX_NODES]; // 노드가중치
int pred[MAX_NODES]; // 부모노드 가중치
int Q[MAX_NODES]; // 우선순위 큐
int Qcount; // 큐 원소 개수

void PQinit() // 초기화
{
    Qcount = 0;
}

void PQinsert(int a) // 삽입함수
{
    Q[a] = 0;
    Qcount++;
}

int PQdelmin() // 큐에서 가중치가 작은 수 삭제
{
    int i;
    int min = MAX_INT; //임시 최소값 초기화
    int saveindex = OUTOFQ; // 저장인덱스 초기화
    for (i = 0; i < MAX_NODES; i++)
    {
        if (Q[i] == OUTOFQ)
            continue;
        if (key[i] < min) // 가중치가 최소 가중치보다 작으면
        {
            saveindex = i; // 인덱스 저장
            min = key[i]; // 가중치를 최소 가중치로 적용
        }
    }
    if (saveindex == OUTOFQ)
        return OUTOFQ;
    Q[saveindex] = OUTOFQ; //최소 가중치의 원소를 -1로 초기화
    Qcount--; // 원소 삭제
    return saveindex; //저장된 인덱스 반환
}

int PQisempty() // 공백 확인 함수
{
    if (Qcount == 0)
        return 1;
    return 0;
}

void PQdeckey(int w, int newkey) // 가중치 변경
{
    key[w] = newkey;
}

void Prim(int start)
{
    int i, v, w;
    PQinit(); // 큐 초기화
    for (i = 0; i < MAX_NODES; i++) // 모든 노드 초기화
    {
        key[i] = MAX_INT;
        pred[i] = NOTDEF;
        PQinsert(i);
    }

    key[start] = 0;
    for (; !PQisempty();)
    {
        v = PQdelmin(); // vertex설정
        printf("%d %c\n", v, v + 'A'); // 지정된 v출력
        for (w = 0; w < MAX_NODES; w++)
        {
            if ((graph[v][w] != 0) && (key[w] > graph[v][w])) // 연결된 가중치가 0이 아니면서 제일 작은 경우
            {
                PQdeckey(w, graph[v][w]); // 현재 가중치에서 제일 작은 가중치로 변경
                pred[w] = v;
            }
        }
    }
}

int main()
{
    Prim(2);
    return 0;
}