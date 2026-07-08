/*
 * EXERCICE : FILTER
 * * DESCRIPTION :
 * Lire depuis stdin et écrire sur stdout, mais en remplaçant toutes les occurrences
 * d'une chaîne de caractères donnée par des astérisques (*) de la même longueur.
 * * CONCEPTS CLÉS :
 * 1. LECTURE DYNAMIQUE : read() avec un buffer variable
 * 2. RECHERCHE DE MOTIFS : strstr() ou memmem()
 * 3. GESTION DE LA MÉMOIRE : realloc() pour un buffer dynamique
 * 4. GESTION DES ERREURS : perror() pour les erreurs système
 * * ALGORITHME :
 * 1. Lire tout le contenu de stdin dans un buffer dynamique
 * 2. Rechercher toutes les occurrences du motif
 * 3. Remplacer chaque occurrence par des astérisques
 * 4. Écrire le résultat sur stdout
 */

#define _GNU_SOURCE  // Pour memmem()
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// Fonction pour trouver et remplacer toutes les occurrences
void ft_filter(char *buffer, const char *target)
{
    int i = 0;
    int target_len = strlen(target);
    int j, k;

    /*
     * ALGORITHME DE RECHERCHE ET REMPLACEMENT :
     * - Parcourir le buffer caractère par caractère
     * - À chaque position, vérifier si cela correspond au motif
     * - Si cela correspond, écrire des astérisques et sauter la longueur du motif
     * - Si cela ne correspond pas, écrire le caractère d'origine
     */

    while (buffer[i])
    {
        j = 0;
        // Vérifier s'il y a une correspondance à partir de la position actuelle
        while (target[j] && (buffer[i + j] == target[j]))
            j++;

        if (j == target_len) // Correspondance complète trouvée
        {
            // Écrire des astérisques à la place du motif
            k = 0;
            while (k < target_len)
            {
                write(1, "*", 1);
                k++;
            }
            i += target_len; // Sauter le motif complet
        }
        else
        {
            // Pas de correspondance, écrire le caractère d'origine
            write(1, &buffer[i], 1);
            i++;
        }
    }
}

int main(int argc, char **argv)
{
    /*
     * VALIDATION DES ARGUMENTS :
     * - Il doit y avoir exactement 1 argument
     * - L'argument ne peut pas être vide
     */
    if (argc != 2 || argv[1][0] == '\0')
        return 1;

    /*
     * LECTURE DYNAMIQUE DE STDIN :
     * - Utiliser un buffer temporaire pour lire par blocs (chunks)
     * - Utiliser realloc() pour agrandir le buffer principal
     * - Suivre le total des octets lus
     */
    char temp[BUFFER_SIZE];
    char *result = NULL;
    char *buffer;
    int total_read = 0;
    ssize_t bytes;

    // Lire depuis stdin jusqu'à la fin de fichier (EOF)
    while ((bytes = read(0, temp, BUFFER_SIZE)) > 0)
    {
        // Agrandir le buffer principal pour accueillir les nouvelles données
        buffer = realloc(result, total_read + bytes + 1);
        if (!buffer)
        {
            free(result);
            perror("realloc");
            return 1;
        }

        result = buffer;

        // Copier les nouvelles données dans le buffer principal
        memmove(result + total_read, temp, bytes);
        total_read += bytes;
        result[total_read] = '\0'; // Assurer la terminaison par un caractère nul
    }

    // Vérifier les erreurs de lecture
    if (bytes < 0)
    {
        perror("read");
        free(result);
        return 1;
    }
    // Si rien n'a été lu, quitter sans erreur
    if (!result)
        return 0;

    // Traiter le buffer et appliquer le filtre
    ft_filter(result, argv[1]);

    // Libérer la mémoire
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