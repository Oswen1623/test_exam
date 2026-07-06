#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int *set;
    int size;
    int target;
    int total_combinations;
    int found;
    int current_sum;
    int first;

    if (argc < 3)
    {
        printf("\n");
        return (0);
    }
    target = atoi(argv[1]);
    size = argc - 2;
    set = malloc(size * sizeof(int));
    if (!set)
        return (1);

    int i = 0;
    while (i < size)
    {
        set[i] = atoi(argv[i + 2]);
        i++;
    }

    total_combinations = 1 << size;
    found = 0;

    int mask = 0;
    while (mask < total_combinations)
    {
        current_sum = 0;
        i = 0;
        while (i < size)
        {
            if ((mask >> i) & 1)
                current_sum += set[i];
            i++;
        }

        if (current_sum == target)
        {
            first = 1;
            i = 0;
            while (i < size)
            {
                if ((mask >> i) & 1)
                {
                    if (!first)
                        printf(" ");
                    printf("%d", set[i]);
                    first = 0;
                }
                i++;
            }
            printf("\n");
            found = 1;
        }
        mask++;
    }

    if (!found)
        printf("\n");

    free(set);
    return (0);
}
