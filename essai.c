#include <stdio.h>

int main(){
    int i,c;
    char tab4[21][2];

    for(i=0,c=1;i<=20;i++,c++){
        tab4[i][1]='#';
        tab4[i][2]='#';
        if(c>7){
            printf("\n");
            c=1;
        }
        printf("%c ",tab4[i]);
    }
}