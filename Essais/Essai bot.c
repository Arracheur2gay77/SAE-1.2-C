#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void affichetab(int tab[]);
void memoirebot(int tab1[], int tab2[], int n1, int n2);
void bot(int tab4[], int tab5[], int *n1, int *n2);

int main(){
    srand((unsigned int)time(NULL));

    int tab1[21], tab2[21], tab3[21];
    int i, j, n, exist;

    // Initialisation tab1 de 1 à 21
    for(i=0; i<21; i++){
        tab1[i] = i+1;
        printf("%d ", tab1[i]);
    }
    printf("\n\n");

    // Remplissage aléatoire de tab2 sans répétition
    for(i=0; i<21; i++){
        do{
            n = rand()%21 + 1;
            exist = 0;
            for(j=0; j<i; j++){
                if(tab2[j] == n){ exist=1; break; }
            }
        } while(exist == 1);
        tab2[i] = n;
        printf("%d ", tab2[i]);
    }
    printf("\n\n");

    // Remplissage aléatoire de tab3 sans répétition
    for(i=0; i<21; i++){
        do{
            n = rand()%21 + 1;
            exist = 0;
            for(j=0; j<i; j++){
                if(tab3[j] == n){ exist=1; break; }
            }
        } while(exist == 1);
        tab3[i] = n;
        printf("%d ", tab3[i]);
    }
    printf("\n\n\n");

    int e = 0, joueur = 0, nb1 = 0, nb2 = 0;
    int trouvej1 = 0, trouvej2 = 0;
    int tab4[21], tab5[21];

    // Initialiser tab4 et tab5 à 0 = caché
    for(i=0; i<21; i++){
        tab4[i] = 0;
        tab5[i] = 0;
    }

    while(1){
        e++;
        joueur = e % 2;

        printf("==========\n");
        printf("Points joueur 1 : %d\n", trouvej1);
        printf("Points joueur 2 : %d\n", trouvej2);
        printf("Essai n°%d\n", e);
        printf("Joueur n°%d\n\n\n", joueur + 1);

        printf("Première table :\n");
        affichetab(tab4);
        printf("\nDeuxième table :\n");
        affichetab(tab5);
        printf("\n");

        if(joueur == 1){
            while(1){
                printf("Veuillez entrer un chiffre de la première table (1 à 21) : ");
                scanf("%d", &nb1);
                if(nb1 >= 1 && nb1 <= 21) break;
                printf("Erreur : entrez un nombre entre 1 et 21 !\n");
            }

            if(tab2[nb1-1] == 0){
                printf("JOKER ! Vous passez votre tour.\n");
                continue;
            }

            while(1){
                printf("Veuillez entrer un chiffre de la deuxième table (1 à 21) : ");
                scanf("%d", &nb2);
                if(nb2 >= 1 && nb2 <= 21) break;
                printf("Erreur : entrez un nombre entre 1 et 21 !\n");
            }
        }
        else {
            bot(tab4, tab5, &nb1, &nb2);
            printf("Bot choisi : %d (première table), %d (deuxième table)\n", nb1, nb2);
        }

        // Mise à jour des tableaux avec les valeurs trouvées
        tab4[nb1 - 1] = tab2[nb1 - 1];
        tab5[nb2 - 1] = tab3[nb2 - 1];

        printf("\n=== Mise à jour des tableaux ===\n\n");
        printf("Première table :\n");
        affichetab(tab4);
        printf("\nDeuxième table :\n");
        affichetab(tab5);
        printf("\n");

        memoirebot(tab4, tab5, nb1, nb2);

        sleep(1);

        if(tab4[nb1 - 1] == tab5[nb2 - 1]){
            printf("Bravo, vous avez trouvé une combinaison !\n");
            if(joueur == 1) trouvej1++;
            else trouvej2++;
        }
        else{
            tab4[nb1 - 1] = 0;
            tab5[nb2 - 1] = 0;
        }

        sleep(2);
    }

    return 0;
}

// Mémoire du bot : ici tu peux adapter ta stratégie (exemple basique)
void memoirebot(int tab1[], int tab2[], int n1, int n2){
    // Cette fonction peut mémoriser les coups du bot, actuellement vide.
    // Si tu veux mémoriser, il faut une structure globale.
    (void)tab1; (void)tab2; (void)n1; (void)n2; // pour éviter warnings
}

// Le bot choisit deux indices non découverts aléatoirement
void bot(int tab4[], int tab5[], int *n1, int *n2){
    int i, tries = 0;
    do {
        *n1 = rand() % 21 + 1;
        tries++;
    } while(tab4[*n1 - 1] != 0 && tries < 100);

    tries = 0;
    do {
        *n2 = rand() % 21 + 1;
        tries++;
    } while(tab5[*n2 - 1] != 0 && tries < 100);
}

void affichetab(int tab[]){
    int i, ligne = 1, c;

    printf("    1   2   3   4   5   6   7");

    for(i = 0, c = 8; i < 21; i++, c++){
        if(c > 7){
            printf("\n%d   ", ligne);
            c = 1;
            ligne++;
        }
        if(tab[i] == 0)
            printf("##  ");
        else
            printf("%2d  ", tab[i]);
    }
    printf("\n");
}
