// #include <stdio.h>
// #include <stdlib.h>

// int divide(int num, int arr[])
// {
//     int d_num = sizeof(arr) / sizeof(int);
//     int fir_arr_size, sec_arr_size;
//     if (d_num % 2 == 0)
//     {
//         fir_arr_size, sec_arr_size = d_num / 2;
//     }
//     else
//     {
//         fir_arr_size = d_num / 2;
//         sec_arr_size = d_num / 2 + 1;
//     }
//     int fir[fir_arr_size];
//     int sec[sec_arr_size];
//     int arr_index = 0;
//     for (int i = 0; i < fir_arr_size; i++)
//     {
//         fir[i] = arr[arr_index];
//         arr_index++;
//     }
//     for (int j = 0; j < sec_arr_size; j++)
//     {
//         sec[j] = arr[arr_index];
//         arr_index++;
//     }
//     return fir, sec;
// }

// int* merge(int fir_arr[], int sec_arr[]) {
//     int fir_len = (sizeof(fir_arr)/sizeof(int));
//     int sec_len = (sizeof(sec_arr)/sizeof(int));
//     int *result = malloc((fir_len + sec_len) * sizeof(int));
//     int result_index = 0;
//     for (int i = 0; i < fir_len; i++)
//     {
//         result[result_index] = fir_arr[i];
//         result_index++;
//     }
//     for (int i = 0; i < sec_len; i++)
//     {
//         result[result_index] = sec_arr[i];
//         result_index++;
//     }
//     return result;
// }
// int main(void)
// {
//     int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//     int b[4] = {11, 12, 13, 14};
//     int *c;
//     c = merge(a, b);
//     for (int i = 0; i < 14; i++)
//     {
//         printf("%d ", c[i]);
//     }
//     printf("\n");
//     free(c);
//     return 0;
// }

#include <stdio.h>
#define MAX_SIZE 8
int sorted[MAX_SIZE]; // 추가적인 공간이 필요

// i: 정렬된 왼쪽 리스트에 대한 인덱스
// j: 정렬된 오른쪽 리스트에 대한 인덱스
// k: 정렬될 리스트에 대한 인덱스
/* 2개의 인접한 배열 list[left...mid]와 list[mid+1...right]의 합병 과정 */
/* (실제로 숫자들이 정렬되는 과정) */
void merge(int list[], int left, int mid, int right)
{
    int i, j, k, l;
    i = left;
    j = mid + 1;
    k = left;

    /* 분할 정렬된 list의 합병 */
    while (i <= mid && j <= right)
    {
        if (list[i] <= list[j])
            sorted[k++] = list[i++];
        else
            sorted[k++] = list[j++];
    }

    // 남아 있는 값들을 일괄 복사
    if (i > mid)
    {
        for (l = j; l <= right; l++)
            sorted[k++] = list[l];
    }
    // 남아 있는 값들을 일괄 복사
    else
    {
        for (l = i; l <= mid; l++)
            sorted[k++] = list[l];
    }

    // 배열 sorted[](임시 배열)의 리스트를 배열 list[]로 재복사
    for (l = left; l <= right; l++)
    {
        list[l] = sorted[l];
    }
}

// 합병 정렬
void merge_sort(int list[], int left, int right)
{
    int mid;

    if (left < right)
    {
        mid = (left + right) / 2;         // 중간 위치를 계산하여 리스트를 균등 분할 -분할(Divide)
        merge_sort(list, left, mid);      // 앞쪽 부분 리스트 정렬 -정복(Conquer)
        merge_sort(list, mid + 1, right); // 뒤쪽 부분 리스트 정렬 -정복(Conquer)
        merge(list, left, mid, right);    // 정렬된 2개의 부분 배열을 합병하는 과정 -결합(Combine)
    }
}

int main()
{
    int i;
    int n = MAX_SIZE;
    int lst[8] = {21, 10, 12, 20, 25, 13, 15, 22};

    // 합병 정렬 수행(left: 배열의 시작 = 0, right: 배열의 끝 = 7)
    merge_sort(lst, 0, n - 1);

    // 정렬 결과 출력
    for (i = 0; i < n; i++)
    {
        printf("%d\n", lst[i]);
    }
}