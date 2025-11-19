#include <stdio.h>

int main(){
    int i;
    char tab4[21];

    for(i=0;i<=21;i++){
        tab4[i]='#';

        printf("%c ",tab4[i]);
        if(6<=i)printf("\n");
    }
}