#include <stdio.h>

#define MAX_ITEMS 100

typedef struct {
    int weight;
    int value;
} Item;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsack(int capacity, Item items[], int n) {
    int dp[MAX_ITEMS + 1][capacity + 1]; // 동적 프로그래밍을 위한 배열

    // 모든 아이템에 대해 계산
    for (int i = 0; i <= n; i++) {
        // 용량 값에 따라 계산
        for (int w = 0; w <= capacity; w++) {
            // 첫 번째 아이템이거나 용량이 0인 경우
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            // 현재 아이템의 무게가 현재 용량보다 작거나 같은 경우
            else if (items[i - 1].weight <= w)
                // 현재 아이템을 포함할지 여부를 결정하고, 더 큰 가치를 선택
                dp[i][w] = max(items[i - 1].value + dp[i - 1][w - items[i - 1].weight], dp[i - 1][w]);
            // 현재 아이템의 무게가 현재 용량보다 큰 경우
            else
                // 이전 아이템까지의 가치와 동일한 가치 선택
                dp[i][w] = dp[i - 1][w];
            
            printf("\t%d",dp[i][w]);
        }
        printf("\n");
    }
    return dp[n][capacity]; // 최대 가치 반환
}

int main() {
    int capacity = 10; // 용량 값
    Item items[] = { // 아이템 배열
        {5, 10},
        {4, 40},
        {6, 30},
        {3, 50}
    };
    int numItems = sizeof(items) / sizeof(items[0]); // 아이템 개수

    int maxValue = knapsack(capacity, items, numItems); // knapsack 알고리즘으로 최대 가치 계산

    printf("최대 가치  : %d\n", maxValue); // 최대 값 출력

    return 0;
}
