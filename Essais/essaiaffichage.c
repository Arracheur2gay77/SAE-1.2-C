#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>

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
    printf("\n\n\n");

    int c,e=0,joueur=0,comp=1;
    char tab4[21];
    
    for(i=0,c=1;i<=20;i++,c++){
        tab4[i]='#';
        if(c>7){
            printf("\n");
            c=1;
        }
        printf("%c ",tab4[i]);
    }
    while(1){
        e++;
        printf("==========\n");
        printf("Essai n°%d\n",e);
        printf("Joueur n°%d\n\n\n",(joueur%2+1));

        printf("Première table :\n");
        printf("   1  2  3  4  5  6  7\n");
        for(i=0,c=8;i<=20;i++,c++){
            printf("%c  ",tab4[i]);
            if(c>7){
            printf("\n%d  ",comp);
            c=1;
            comp++;
        }
        }
        break;
    }

    printf("\n");
}