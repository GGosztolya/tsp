#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int number_of_cities;

int max_mask;

int **dist;
int **memo;
int rows = 0;
int cols = 0;

void parse_input()
{
    scanf("%d", &number_of_cities);

    max_mask = 1 << number_of_cities;

    rows = number_of_cities;
    cols = number_of_cities;
    dist = (int **) malloc(rows * sizeof(int *));
    memo = (int **) malloc(rows * sizeof(int *));
    for(int i = 0; i < rows; i++)
    {
        dist[i] = malloc(cols * sizeof(int));
        memo[i] = malloc(max_mask * sizeof(int));

        for(int j = 0; j < max_mask; j++)
        {
            memo[i][j] = -1;
        }
    }

    for(int i = 0; i < number_of_cities; i++)
    {   
        for(int j = 0; j < (number_of_cities - 1); j++)
        {
            int start, end, length;
            scanf("%d %d %d", &start, &end, &length);

            dist[start - 1][end - 1] = length;
        }
    }
}

int tsp(int current, int visited)
{
    if (visited == (1 << number_of_cities) - 1) return dist[current][0];

    if (memo[current][visited] != -1) return memo[current][visited];

    int min_distance = INT_MAX;
    for (int next = 0; next < number_of_cities; next++)
    {
        if ((visited & (1 << next)) == 0)
        {
            int distance = dist[current][next] + tsp(next, visited | (1 << next));
            if (distance < min_distance)
            {
                min_distance = distance;
            }
        }
    }

    return memo[current][visited] = min_distance;
}

void clean_up()
{
    for(int i = 0; i < rows; i++)
    {
        free(dist[i]);
        free(memo[i]);
    }

    free(dist);
    free(memo);
}

int main()
{
    parse_input();
    printf("%d", tsp(0, 1));
    clean_up();

    return 0;
}