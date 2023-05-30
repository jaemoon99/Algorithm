#include <stdio.h>
#include <string.h>

int matrix[4][2] = { {10, 20}, {20, 5}, {5, 15}, {15, 30} };  // 박스 사이즈
char* matrix_name[4] = { "A1", "A2", "A3", "A4" };  // 박스 이름
int dp[4][4];  // 실제 값

int min(int x, int y) { //최소값 비교
    return x < y ? x : y;
}

int mat(int n) {
    for (int i = 0; i < n; i++) {
        dp[i][i] = 0;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i < n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = 10000000;
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + matrix[i][0] * matrix[k][1] * matrix[j][1];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    dp[j][i] = k;
                }
            }
        }
    }

    return dp[0][n - 1];
}

void printOptimalParenthesis(int i, int j) {
    if (i == j) {
        printf("%s", matrix_name[i]);
        return;
    }

    printf("(");
    printOptimalParenthesis(i, dp[j][i]);
    printOptimalParenthesis(dp[j][i] + 1, j);
    printf(")");
}

int main() {
    int n = 4;
    int ans = mat(n);

    printf("-------- dp[i][j] -------------\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", dp[i][j]);
        }
        printf("\n");
    }

    printf("[1][4]의 값: %d\n", ans);

    printf("최적의 행렬 곱셈 순서: ");
    printOptimalParenthesis(0, n - 1);
    printf("\n");

    return 0;
}