#define _GNU_SOURCE
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void ft_filter(char *buffer, const char *target)
{
    int i = 0;
    int target_len = strlen(target);
    int j, k;

    while (buffer[i])
    {
        j = 0;
        while (target[j] && (buffer[i + j] == target[j]))
            j++;

        if (j == target_len)
        {
            k = 0;
            while (k < target_len)
            {
                write(1, "*", 1);
                k++;
            }
            i += target_len;
        }
        else
        {
            write(1, &buffer[i], 1);
            i++;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 2 || argv[1][0] == '\0')
        return 1;

    char temp[BUFFER_SIZE];
    char *result = NULL;
    char *buffer;
    int total_read = 0;
    ssize_t bytes;

    while ((bytes = read(0, temp, BUFFER_SIZE)) > 0)
    {
        buffer = realloc(result, total_read + bytes + 1);
        if (!buffer)
        {
            free(result);
            perror("realloc");
            return 1;
        }

        result = buffer;

        memmove(result + total_read, temp, bytes);
        total_read += bytes;
        result[total_read] = '\0';
    }
    if (bytes < 0)
    {
        perror("read");
        free(result);
        return 1;
    }
    if (!result)
        return 0;
    ft_filter(result, argv[1]);
    free(result);
    return 0;
}

/*
 * POINTS CLÉS POUR L'EXAMEN :
 * * 1. GESTION DE LA MÉMOIRE :
 * - Toujours vérifier le retour de malloc/realloc
 * - Libérer la mémoire en cas d'erreur
 * - Utiliser memmove() au lieu de memcpy() en cas de chevauchement
 * * 2. GESTION DES ERREURS :
 * - Utiliser perror() pour les erreurs système
 * - Retourner les codes d'erreur appropriés
 * - Valider les arguments avant de les utiliser
 * * 3. LECTURE DYNAMIQUE :
 * - Le buffer doit pouvoir se remplir avec n'importe quelle quantité de données
 * - Utiliser realloc() pour l'agrandir selon les besoins
 * - Maintenir un caractère de fin de chaîne (\0) valide
 * * 4. ALGORITHME EFFICACE :
 * - Recherche simple caractère par caractère
 * - Éviter d'utiliser des fonctions non autorisées
 * - Écrire directement sur stdout sans stocker le résultat
 */