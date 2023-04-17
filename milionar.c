#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

int* poradi_otazky();
int moznost(FILE *soubor, char odpoved[100]);
int kontrola(char volba, char moznost[4][100], char odpoved[100]);

#define MAX_LENGTH 100

int skore = 0;

int main()
{
    srand(time(NULL));
    int* poradi = poradi_otazky();
    char nazev[MAX_LENGTH], jmeno[MAX_LENGTH];

    printf("Vitejte v hre Ja su milionar!\n");
    printf("Zadejte vase jmeno: ");
    scanf("%[^\n]s", jmeno);
    fflush(stdin);
    system("cls");

    
    for (int i = 0; i < 15; i++)
    {
        sprintf(nazev, "./otazky/otazka%d.txt", poradi[i]);
        FILE *soubor = fopen(nazev, "r");

        //chybová hláška
        if (soubor == NULL)
        {
            printf("Chyba: Nepodarilo se otevrit soubor.\n");
            return 1;
        }

        //načtení otázky a odpovědi
        char otazka[MAX_LENGTH], odpoved[MAX_LENGTH], moznost1[MAX_LENGTH], moznost2[MAX_LENGTH], moznost3[MAX_LENGTH], moznost4[MAX_LENGTH];

        fgets(otazka, MAX_LENGTH, soubor);
        fgets(odpoved, MAX_LENGTH, soubor);

        //vypsání otázky
        printf("%d otazka: %s", i+1, otazka);

        moznost(soubor, odpoved);

        fclose(soubor);
        
    }

    //vložení jména a skóre do souboru
    printf("Konec hry! Vase celkove skore je: %d\n", skore);
    system("pause");
    FILE *soubor = fopen("skore.txt", "a");
    fprintf(soubor, "hrac: %s skore: %d \n", jmeno, skore);
    fclose(soubor);

    free(poradi);
    
    return 0;
}

int* poradi_otazky()
{
    //vygeneruj čísla 1-15 do pole poradi, čísla se nesmí opakovat, vždy dojde k nového čísla
    int* poradi = (int*) malloc(15 * sizeof(int));
    int i = 0;
    while (i < 15)
    {
        int j = 0;
        int cislo = rand() % 15 + 1;
        while (j < i)
        {
            if (poradi[j] == cislo)
            {
                break;
            }
            j++;
        }
        if (j == i)
        {
            poradi[i] = cislo;
            //vygenerované číslo se přidělí k otázce ze složky otazky
            char nazev[MAX_LENGTH];
            i++;
        }
    }
    
    return poradi;
    
}

int moznost(FILE *soubor, char odpoved[100])
{
    char moznost[4][MAX_LENGTH], volba;

    //načtení možností
    for (int i = 0; i < 4; i++)
    {
        fgets(moznost[i], MAX_LENGTH, soubor);
    }

    //uživatelova volba
    for (int i = 0; i < 4; i++)
    {
        printf("%c . %s", 65+i, moznost[i]);
    }
    printf("\nVase volba: ");
    scanf("%c", &volba);
    fflush(stdin);

    //porovnání odpovědi s možností
    kontrola(volba, moznost, odpoved);

    system("pause");
    system("cls");

    return 0;
}

int kontrola(char volba, char moznost[4][100], char odpoved[100])
{
    if (volba == 'A' || volba == 'a')
    {
        if (strcmp(moznost[0], odpoved) == 0)
        {
            printf("Spravne!\n");
            skore++;
        }
        else
        {
            printf("Spatne!\n");
            printf("spravna odpoved: %s", odpoved);
        }
    }
    else if (volba == 'B' || volba == 'b')
    {
        if (strcmp(moznost[1], odpoved) == 0)
        {
            printf("Spravne!\n");
            skore++;
        }
        else
        {
            printf("Spatne!\n");
            printf("spravna odpoved: %s", odpoved);
            
        }
    }
    else if (volba == 'C' || volba == 'c')
    {
        if (strcmp(moznost[2], odpoved) == 0)
        {
            printf("Spravne!\n");
            skore++;
        }
        else
        {
            printf("Spatne!\n");
            printf("spravna odpoved: %s", odpoved);
        }
    }
    else if (volba == 'D' || volba == 'd')
    {
        if (strcmp(moznost[3], odpoved) == 0)
        {
            printf("Spravne!\n");
            skore++;
        }
        
        else
        {
            printf("Spatne!\n");
            printf("spravna odpoved: %s", odpoved);
        }
    }

    return 0;
}
