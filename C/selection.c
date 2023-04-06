#include <stdio.h>
#include <stdlib.h>

int count = 1;
int switch_count = 1;

int divide(int arr[], int left, int right)
{
    int pivotIndex = (rand() % (right - left + 1) + left); // pivot 인덱스 랜덤으로 설정
    int temp = arr[left]; 
    arr[left] = arr[pivotIndex];
    arr[pivotIndex] = temp;
    int pivot = arr[left]; // pivot값을 맨 왼쪽으로 옮김
    int i = left;          // i는 작은 값들이 위치할 구역의 끝 인덱스
    printf("피봇 값 : %d\n", pivot);
    // 배열의 두 번째부터 순회, 기준 값보다 작은 값이랑 교체
    for (int j = left + 1; j <= right; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            printf("switch_%d-%d : ", count - 1, switch_count);
            switch_count++;
            for (int ii = left; ii < right + 1; ii++)
            {
                printf("%d ", arr[ii]);
            }
            printf("\n");
        }
    }
    // 기준 값을 기준 값보다 작은 값(작은 값 중 제일 큰 값) 다음으로 이동시키고, 해당 위치를 반환
    int temp2 = arr[i];
    arr[i] = arr[left];
    arr[left] = temp2;
    printf("switch_%d-%d : ", count - 1, switch_count);
    switch_count++;
    for (int ii = left; ii < right + 1; ii++)
    {
        printf("%d ", arr[ii]);
    }
    printf("\n\n");
    switch_count = 1;
    return i;
}

int selection(int arr[], int left, int right, int k)
{
    // 분할한 배열의 요소가 하나면 반환
    if (left == right)
        return arr[left];

    // 배열을 분할하고, 분할한 구역의 크기(순서)를 구함
    int pivotIndex = divide(arr, left, right);
    int _k = pivotIndex - left + 1;

    // k와 구역의 순서가 일치하면 반환
    if (k == _k)
        return arr[pivotIndex];

    // k보다 작은 값들은 분할한 구역의 왼쪽에 존재하므로 왼쪽 구역에서 찾음
    else if (k < _k)
    {
        printf("%d번째_L_array: ", count);
        for (int i = left; i <= pivotIndex - 1; i++)
            printf("%d ", arr[i]);
        printf("\n");
        count++;
        return selection(arr, left, pivotIndex - 1, k);
    }

    // k보다 큰 값들은 분할한 구역의 오른쪽에 존재하므로 오른쪽 구역에서 찾음
    else
    {
        printf("%d번째_R_array: ", count);
        for (int i = pivotIndex + 1; i <= right; i++)
            printf("%d ", arr[i]);
        printf("\n");
        count++;
        return selection(arr, pivotIndex + 1, right, k - _k);
    }
}

int main()
{
    int arr[] = {6, 3, 11, 9, 12, 2, 8, 15, 18, 10, 7, 14};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("초기 배열 : ");
    for (int i = 0; i < 12; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("%d번째로 작은 수: %d\n", 10, selection(arr, 0, n - 1, 10));
    return 0;
}