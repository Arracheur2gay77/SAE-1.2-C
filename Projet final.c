#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

void affichetab(char tab[]);

int main(){
    srand((unsigned int)time(NULL));

    int tab1[21],tab2[21],tab3[21];
    int i,j,n,exist;

    for(i=0;i<21;i++){
        tab1[i]=i+1;
        printf("%d ",tab1[i]);
    }

    printf("\n\n");

    for(i=0;i<21;i++){
        do{
            n=rand()%21+1;
            exist=0;
            for(j=0;j<i;j++){
                if(tab2[j]==n){exist=1;break;}
            }
        }while(exist==1);
        tab2[i]=n;
        printf("%d ",tab2[i]);
    }

    printf("\n\n");

    for(i=0;i<21;i++){
        do{
            n=rand()%21+1;
            exist=0;
            for(j=0;j<i;j++){
                if(tab3[j]==n){exist=1;break;}
            }
        }while(exist==1);
        tab3[i]=n;
        printf("%d ",tab3[i]);
    }

    printf("\n\n\n");

    int e=0,joueur=0,nb1,nb2;
    char tab4[21],tab5[21];

    while(1){
        e++;
        joueur=e%2;

        printf("==========\n");
        printf("Essai n°%d\n",e);
        printf("Joueur n°%d\n\n\n",joueur+1);

        for(i=0;i<21;i++){
            tab4[i]='#';
            tab5[i]='#';
        }

        //(Fonction pour réatribuer les chiffres a leur emplacement si trouvé)

        printf("Première table :\n");
        affichetab(tab4);

        printf("\nDeuxième table :\n");
        affichetab(tab5);
        printf("\n");

        while(1){
            printf("Veuillez entrer un chiffre de la première table (1 à 21) : ");
            scanf("%d",&nb1);
            if(nb1>=1 && nb1<=21) break;
            printf("Erreur : entrez un nombre entre 1 et 21 !\n");
        }

        if(tab2[nb1-1]==0){
            printf("JOKER ! Vous passez votre tour.\n");
            continue;
        }

        while(1){
            printf("Veuillez entrer un chiffre de la deuxième table (1 à 21) : ");
            scanf("%d",&nb2);
            if(nb2>=1 && nb2<=21) break;
            printf("Erreur : entrez un nombre entre 1 et 21 !\n");
        }

        tab4[nb1-1]=tab2[nb1-1];
        tab5[nb2-1]=tab3[nb2-1];

        printf("\n=== Mise à jour des tableaux ===\n\n");

        printf("Première table :\n");
        affichetab(tab4);

        printf("\nDeuxième table :\n");
        affichetab(tab5);
        printf("\n");
    
        sleep(10);
    }

    return 0;
}

void affichetab(char tab[]){
    int i, ligne = 1, c;

    printf("    1   2   3   4   5   6   7");

    for(i=0, c=8; i<21; i++, c++){
        if(c>7){
            printf("\n%d   ", ligne);
            c=1;
            ligne++;
        }
        printf("%c   ", tab[i]);
    }
    printf("\n");
}