#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Global Variable :
int position = 0;
char result[5][10];

void deleteItem(int i, int j, char data[10][10])
{

    for (int x = j + 1; x < position; x++)
    {
        strcpy(data[x - 1], data[x]);
    }
    position--;
    strcpy(data[position], "");

    if (!strcmp(data[i], data[j]))
        deleteItem(i, j, data);
}

void generateWord(char data[10][10], char symbols[5][2])
{
    char allWordsp[position + 4][10];

    for (int i = 0; i < position; i++)
        strcpy(allWordsp[i], data[i]);
    for (int j = 0; j < 5; j++)
        strcpy(allWordsp[position + j], symbols[j]);

    for (int z = 0; z < 5; z++)
        strcpy(result[z], allWordsp[rand() % (position + 3)]);

    for (int i = 0; i < 5; i++)
        printf("%s", result[i]);
    printf("\n");
}

int main()
{
    int choice;
    char input[10], data[10][10] = {}, symbols[5][2] = {"@", "#", "&", "$"};

    while (1)
    {
        // Menu :
        printf("=======================================\n");
        printf(" Menu d'application\n");
        printf("=======================================\n");
        printf("[1] afficher les donnees\n[2] ajouter une donnee\n[3] rechercher sur une donnee\n[4] supprimer une donnee\n[5] supprimer les donnees repetes\n[6] genere le wordlist\n");
        printf("=======================================\n");
        printf("Tapez votre choix [1-6] : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (!position)
            {
                printf("No Data available\n");
                break;
            }
            for (int i = 0; i < position; i++)
                printf("%s\n", data[i]);
            break;
        case 2:
            if (position == 9)
            {
                printf("Can't add more data, Please remove some data\n");
                break;
            }
            printf("-> ");
            scanf("%s", data[position]);
            strlwr(data[position]);
            position++;
            break;
        case 3:
        {
            bool exist = false;
            if (!position)
            {
                printf("No Data available\n");
                break;
            }
            printf("-> ");
            scanf("%s", input);

            for (int j = 0; j < position; j++)
            {
                if (!strcmp(strlwr(input), data[j]))
                {
                    exist = true;
                    printf("Your entry is exit: %s\n", data[j]);
                    break;
                }
            }
            if (!exist)
                printf("Not exist\n");

            break;
        }
        case 4:
            if (!position)
            {
                printf("No Data available\n");
                break;
            }
            printf("-> ");
            scanf("%s", input);

            for (int i = 0; i < position; i++)
            {
                if (!strcmp(strlwr(input), data[i]))
                {
                    for (int x = i + 1; x < position; x++)
                        strcpy(data[i], data[x]);
                    printf("Item deleted successfully\n");
                    position--;
                    strcpy(data[position], "");
                    break;
                }
            }
            break;
        case 5:
            if (!position)
            {
                printf("No Data available\n");
                break;
            }

            for (int i = 0; i < position; i++)
            {
                for (int j = i + 1; j < position; j++)
                {
                    if (!strcmp(data[i], data[j]))
                    {
                        deleteItem(i, j, data);
                    }
                }
            }

            printf("Done.\n");
            break;
        case 6:
        {
            int n;
            if (!position)
            {
                printf("No Data available\n");
                break;
            }
            printf("How many results do you need: ");
            scanf("%d", &n);
            for (int i = 1; i <= n; i++)
                generateWord(data, symbols);
            break;
        }
        default:
            printf("Please enter a valid number\n");
        }
    }

    return 0;
}
