#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
    srand((unsigned int)time(NULL));
    int tab1[20],tab2[20],tab3[20],i=0,j,n,exist;

    while(1){
        tab1[i]=i;
        printf("%d ",tab1[i]);
        i+=1;

        if(i>20) break;
    }

    printf("\n");

    for(i=0;i<21;i++){
        do{
            n=rand()%21+0;
            exist=0;

            for(j=0;j<i;j++){
                if(tab2[j]==n){exist=1;break;}
            }

        }while(exist==1);

        tab2[i]=n;
        printf("%d ",n);
    }

    printf("\n");

    for(i=0;i<21;i++){
        do{
            n=rand()%21+0;
            exist=0;

            for(j=0;j<i;j++){
                if(tab3[j]==n){exist=1;break;}
            }

        }while(exist==1);

        tab3[i]=n;
        printf("%d ",n);
    }
    printf("\n");

    int nb1,nb2,joueur,e

    while(1){
        e++;
        i=0;
        do{
            printf("\n");
            i++;
        } while (i<5);

        printf("=============\n");
        printf("Essai n°%d\n",e);
        printf("Joueur %d :\n",(joueur%2+1));        

        printf("\n");

        while(1){
            printf("Veuillez entrer un chiffre de la première table : ");
            scanf("%d",&n);
            if(0<n && n<20) break;
            else printf("Veuillez écrire un nombre entre 1 et 20\n");
        }
        printf("%d--->%d\n",n,tab2[n-1]);

        while(1){
            printf("Veuillez entrer un chiffre de la deuxième table : ");
            scanf("%d",&n);
            if(0<n && n<20) break;
            else printf("Veuillez écrire un nombre entre 1 et 20\n");
        }
         printf("%d--->%d\n",n,tab3[n-1]);


        break;
    }
    printf("\n");
}