#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

void affichetab(char tab[]);  // Déclaration correcte

int main(){
    srand((unsigned int)time(NULL));
    int tab1[20],tab2[21],tab3[21],i=0,j,n,exist;

    // Génération tab1
    while(1){
        tab1[i]=i;
        printf("%d ",tab1[i]);
        i+=1;
        if(i>20) break;
    }
    printf("\n");

    // Génération tab2
    for(i=0;i<21;i++){
        do{
            n=rand()%21;
            exist=0;
            for(j=0;j<i;j++){
                if(tab2[j]==n){exist=1;break;}
            }
        }while(exist==1);
        tab2[i]=n;
        printf("%d ",n);
    }
    printf("\n");

    // Génération tab3
    for(i=0;i<21;i++){
        do{
            n=rand()%21;
            exist=0;
            for(j=0;j<i;j++){
                if(tab3[j]==n){exist=1;break;}
            }
        }while(exist==1);
        tab3[i]=n;
        printf("%d ",n);
    }
    printf("\n\n\n");

    int c,e=0,joueur=0,comp,nb1,nb2;
    char tab4[21],tab5[21];
    
    // Remplir # # # # ...
    for(i=0;i<21;i++){
        tab4[i]='#';
        tab5[i]='#';
    }

    while(1){
        e++;
        printf("==========\n");
        printf("Essai n°%d\n",e);
        printf("Joueur n°%d\n\n\n",(joueur%2+1));

        printf("Première table :\n");
        affichetab(tab4);

        printf("\nDeuxième table :\n");
        affichetab(tab5);

        printf("\n");

        // Saisie nb1
        while(1){
            printf("Veuillez entrer un chiffre de la première table : ");
            scanf("%d",&nb1);
            if(nb1 > 0 && nb1 <= 21) break;
            else printf("Veuillez écrire un nombre entre 1 et 20\n");
        }

        // Joker ?
        while(1){
            if(tab2[nb1-1] == 0){
                printf("Joker ! Vous passez votre tour !");
                break;
            }
            printf("Veuillez entrer un chiffre de la deuxième table : ");
            scanf("%d",&nb2);
            if(nb2 > 0 && nb2 <= 21) break;
            else printf("Veuillez écrire un nombre entre 1 et 20\n");
        }

        tab4[nb1-1] = tab2[nb1-1];
        tab5[nb1-1] = tab3[nb1-1];

        break;
    }

    printf("\n");
    return 0;
}


// =====================================================
//            FONCTION D'AFFICHAGE DU TABLEAU
// =====================================================

void affichetab(char tab[]){
    int i, comp = 1, c;

    printf("    1   2   3   4   5   6   7");

    for(i=0, c=8; i<21; i++, c++){
        if(c>7){
            printf("\n%d   ", comp);
            c=1;
            comp++;
        }
        printf("%c   ", tab[i]);
    }
    printf("\n");
}
