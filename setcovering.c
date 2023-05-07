#include <stdio.h>
#include <stdbool.h>

// 전체 원소를 나타내는 배열
int universe[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// 집합을 나타내는 배열
int sets[][6] = {
    {1, 2, 3, 8},
    {1, 2, 3, 4, 8},
    {1, 2, 3, 4},
    {2, 3, 4, 5, 7, 8},
    {4, 5, 6, 7},
    {5, 6, 7, 9, 10},
    {4, 5, 6, 7},
    {1, 2, 4, 8},
    {6, 9},
    {6, 10}
};

// 전체 원소의 개수
int num_universe_elements = sizeof(universe) / sizeof(universe[0]);

// 집합의 개수
int num_sets = sizeof(sets) / sizeof(sets[0]);

// 각 원소가 커버되었는지를 나타내는 배열
bool covered[10];

int main()
{
    int num_covered = 0; // 커버된 원소의 개수
    int num_chosen = 0; // 선택된 집합의 개수
    int chosen_sets[6]; // 선택된 집합을 저장하는 배열

    // 모든 원소가 커버될 때까지 반복
    while (num_covered < num_universe_elements)
    {
        int best_set_index = -1; // 가장 많은 원소를 커버하는 집합의 인덱스
        int best_set_covered = 0; // 가장 많은 원소를 커버하는 집합이 커버하는 원소의 개수

        // 모든 집합에 대해 반복
        for (int i = 0; i < num_sets; i++)
        {
            int num_covered_by_set = 0; // 현재 집합이 커버하는 원소의 개수

            // 현재 집합에 속한 모든 원소에 대해 반복
            for (int j = 0; j < 5; j++)
            {
                int element = sets[i][j]; // 현재 집합의 j번째 원소

                // 전체 원소 중 현재 원소를 찾아서 커버되지 않았다면 커버된 원소의 개수를 증가시킴
                for (int k = 0; k < num_universe_elements; k++)
                {
                    if (universe[k] == element && !covered[k])
                    {
                        num_covered_by_set++;
                        break;
                    }
                }
            }

            // 현재 집합이 이전까지 찾은 집합보다 더 많은 원소를 커버

            if (num_covered_by_set > best_set_covered)
            {
                best_set_index = i;
                best_set_covered = num_covered_by_set;
            }
        }

        chosen_sets[num_chosen++] = best_set_index;

        for (int i = 0; i < 5; i++)
        {
            int element = sets[best_set_index][i];

            for (int j = 0; j < num_universe_elements; j++)
            {
                if (universe[j] == element)
                {
                    covered[j] = true;
                    num_covered++;
                }
            }
        }
    }

    printf("Chosen sets:\n");

    for (int i = 0; i < num_chosen; i++)
    {
        printf("S%d ", chosen_sets[i] + 1);
    }

    printf("\n");

    return 0;
}