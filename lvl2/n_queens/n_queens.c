#include <stdio.h>
#include <stdlib.h>

// Vérifie si l'on peut placer une reine à la position (col, row)
static int is_safe(int *board, int col, int row)
{
    int i = 0;
    while (i < col)
    {
        int diff_row = board[i] - row;
        if (diff_row < 0)
            diff_row = -diff_row;

        int diff_col = col - i;

        // 1. Même ligne : board[i] == row
        // 2. Même diagonale : la distance des lignes == la distance des colonnes
        if (board[i] == row || diff_row == diff_col)
            return 0;

        i++;
    }
    return 1;
}

static void solve(int *board, int col, int n)
{
    // Condition d'arrêt : toutes les colonnes contiennent une reine
    if (col == n)
    {
        int i = 0;
        while (i < n)
        {
            if (i == n - 1)
                fprintf(stdout, "%d", board[i]);
            else
                fprintf(stdout, "%d ", board[i]);
            i++;
        }
        fprintf(stdout, "\n");
        return;
    }

    // Essayer chaque ligne pour la colonne actuelle
    int row = 0;
    while (row < n)
    {
        if (is_safe(board, col, row))
        {
            board[col] = row;
            solve(board, col + 1, n); // Passer à la colonne suivante
        }
        row++;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 0;

    int n = atoi(argv[1]);
    if (n <= 0)
        return 0;

    int *board = (int *)malloc(sizeof(int) * n);
    if (!board)
        return 1;

    solve(board, 0, n);

    free(board);
    return 0;
}
