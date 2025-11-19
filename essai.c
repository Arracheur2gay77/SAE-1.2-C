#include <stdio.h>

int main(){
    int i,c;
    char tab4[21];

    for(i=0,c=1;i<=21;i++,c++){
        tab4[i]='#';
        if(c>6){
            printf("\n");
            c=1;
        }
        printf("%c",tab4[i]);
    }
}