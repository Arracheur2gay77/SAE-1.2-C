#include <stdio.h>
#include<stdlib.h>
#include<time.h>

int main (){
    int tab[20],i,j,exist,n;

    for(i=0;i<21;i++){
        do{
            n=rand()%21+0;
            exist=0;

            for(j=0;j<i;j++){
                if(tab[j]==n){exist=1;break;}
            }

        }while(exist==1);

        tab[i]=n;
        printf("%d ",n);
    }
    printf("\n");
    while(1){
        printf("Veuillez entrer un chiffre de la première table :");
        break;
    }
}