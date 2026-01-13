#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int a,b;
    
    printf("Veuillez insérez la hauteur et la longueur de la table de jeu\n");
    printf("Longueur : "); scanf("%d",&a);
    printf("Hauteur : "); scanf("%d",&b);

    int table[b][a];
    int i,j;
    int posx,posy,c=0;
    srand(time(NULL));

    while(1){
        c++;
        for(i=0;i<2;i++){
            while (1)
                {
                posx=rand()%a;
                posy=rand()%b;
                
                if(table[posx][posy]==NULL){
                    table[posx][posy]=c;
                    break;
                }
            }
        }
    }



    for(i=0;i<b;i++){
        for(j=0;j<a;j++){
            printf(" %d ",table[i][j]);
        }
        printf("\n");
    }
}