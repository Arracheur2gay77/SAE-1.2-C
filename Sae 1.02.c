#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX 100

#define RESET "\033[0m"
#define ROUGE "\033[31m"
#define VERT "\033[32m"
#define JAUNE "\033[33m"
#define BLEU "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define GRIS "\033[90m"


/* validation des dimensions impaires pour autoriser le joker */
bool dimensionsImpaires(int L,int C){
    if((L%2)!=0 && (C%2)!=0 && (L*C)>1) return true; // cas L=C=1 exclu [cite: 15]
    return false;
}


/* affichage de l'interface principale du programme */
void menuPrincipal(int triche){
    printf(MAGENTA"====================================\n");
    printf("        APPLICATION MEMORYX\n");
    printf("====================================\n"RESET);
    printf(CYAN"1. Jouer une partie\n");
    printf("2. Mode Triche : %s\n",triche?"ACTIVE":"DESACTIVE");
    printf("3. Quitter le programme\n"RESET);
    printf(MAGENTA"====================================\n"RESET);
}


/* selection du mode de jeu : duel, bot ou solitaire */
int menuJeu(){
    int choix;

    while(1){
        printf("\n"JAUNE"--- MODES DE JEU ---\n"RESET);
        printf("1. Duel (2 joueurs)\n");
        printf("2. Joueur contre Bot\n");
        printf("3. Mode Solitaire\n");
        printf("Choix : ");
        scanf("%d",&choix);
        if(choix>=1 && choix<=3) return choix;
    }
}


/* selection de la difficulte de l'IA pour l'evaluation */
int menuBot(){
    int choix;

    while(1){
        printf("\n"CYAN"--- DIFFICULTE DU BOT ---\n"RESET);
        printf("1. Facile (Aleatoire)\n");
        printf("2. Normal (Memoire)\n");
        printf("3. Dieu (Acces direct a T)\n");
        printf("Choix : ");
        scanf("%d",&choix);
        if(choix>=1 && choix<=3) return choix;
    }
}


/* algorithme de permutation du joker avec une carte active */
void permuterJoker(int T[],int posJoker,int R){
    int r;

    do{
        r=rand()%R; // [cite: 110]
    }while(T[r]==-1); // cible obligatoirement une carte en jeu [cite: 108]

    int tmp=T[posJoker];
    T[posJoker]=T[r];
    T[r]=tmp;
}


/* initialisation de T via la table P conformement au sujet */
void initialiserTableau(int T[],int L,int C){
    int i,R=L*C,P[MAX];

    for(i=0;i<R;i++) P[i]=i; // [cite: 71]

    for(i=0;i<R;i++){ // permutation aleatoire des positions [cite: 72]
        int r=rand()%R;
        int tmp=P[i];
        P[i]=P[r];
        P[r]=tmp;
    }

    T[P[0]]=0; // placement du Joker [cite: 73]
    int val=1;

    for(i=1;i<R;i+=2){ // placement des paires identiques [cite: 73]
        T[P[i]]=val;
        T[P[i+1]]=val;
        val++;
    }
}


/* rendu du plateau : les cartes retirees (-1) laissent un espace vide */
void afficherPlateau(int T[],int visible[],int L,int C,int triche){
    int i,j,k=0;

    printf("\n    ");
    for(j=0;j<C;j++) printf(GRIS" %2d "RESET,j); //
    printf("\n");

    for(i=0;i<L;i++){
        printf(GRIS"%2d |"RESET,i);
        for(j=0;j<C;j++){
            if(T[k]==-1) printf("    "); // [cite: 100]
            else if(triche==1 || visible[k]==1){
                if(T[k]==0) printf(ROUGE" JK "RESET);
                else printf(VERT" %2d "RESET,T[k]);
            }
            else printf(BLEU" ## "RESET);
            k++;
        }
        printf("\n");
    }
}


/* mise a jour de la memoire du bot apres retrait d'une paire */
void nettoyerMemoire(int mPos[],int mVal[],int *mNb,int val){
    int i,j;

    for(i=0;i<*mNb;i++){
        if(mVal[i]==val){
            for(j=i;j<*mNb-1;j++){
                mPos[j]=mPos[j+1];
                mVal[j]=mVal[j+1];
            }
            (*mNb)--;
            i--; 
        }
    }
}


/* enregistrement des positions et valeurs pour le bot */
void memoriserCarte(int mPos[],int mVal[],int *mNb,int pos,int val){
    for(int i=0;i<*mNb;i++){
        if(mPos[i]==pos){
            mVal[i]=val; // [cite: 125]
            return;
        }
    }
    mPos[*mNb]=pos;
    mVal[*mNb]=val;
    (*mNb)++;
}


/* algorithme de decision du bot selon le niveau choisi */
int botChoisit(int diff,int T[],int visible[],int R,int mPos[],int mVal[],int mNb,int exclure){
    if(diff==3){ // niveau dieu : acces total [cite: 135]
        for(int i=0;i<R;i++){
            if(i!=exclure && T[i]!=-1 && visible[i]==0){
                for(int j=0;j<R;j++) if(i!=j && T[i]==T[j] && T[i]>0) return i;
            }
        }
    }

    if(diff>=2){ // recherche de paires en memoire [cite: 130]
        for(int i=0;i<mNb;i++){
            if(mPos[i]!=exclure && visible[mPos[i]]==0 && T[mPos[i]]!=-1){
                for(int j=0;j<mNb;j++) if(i!=j && mVal[i]==mVal[j]) return mPos[i];
            }
        }
    }

    int p; // strategie par defaut : hasard [cite: 134]
    do{ p=rand()%R; }while(T[p]==-1 || visible[p]==1 || p==exclure);
    return p;
}


/* moteur de jeu principal et gestion des evenements joker */
void lancerJeu(int triche,int mode,int diff){
    int L,C;

    while(1){
        printf("Saisir dimensions L et C (impairs) : ");
        scanf("%d %d",&L,&C);
        if(dimensionsImpaires(L,C)) break;
        printf(ROUGE"Dimensions non conformes[cite: 14, 15].\n"RESET);
    }

    int R=L*C,T[MAX],visible[MAX],score1=0,score2=0,reste=(R-1)/2,tour=0;
    int mPos[MAX],mVal[MAX],mNb=0;
    time_t debut=time(NULL);

    for(int i=0;i<R;i++) visible[i]=0;
    initialiserTableau(T,L,C);

    while(reste>0){
        int j=(mode==3)?0:tour%2; // gestion de l'ordre de passage [cite: 120]
        afficherPlateau(T,visible,L,C,triche);

        if(mode==3) printf(CYAN"Chronomètre : %lds\n"RESET,time(NULL)-debut); // [cite: 106]
        else printf(JAUNE"Score J1: %d | J2/Bot: %d\n"RESET,score1,score2);

        int p1,p2;

        if(mode==2 && j==1){ // tour du bot
            sleep(1);
            p1=botChoisit(diff,T,visible,R,mPos,mVal,mNb,-1);
            printf("Le bot choisit la position : %d\n",p1);
        }
        else do{ printf("Joueur %d, Pos 1 : ",j+1); scanf("%d",&p1); }while(p1<0||p1>=R||T[p1]==-1||visible[p1]==1);

        if(T[p1]==0){ // gestion du joker carte 1 [cite: 16, 84]
            printf(ROUGE"JOKER ! Permutation en cours...\n"RESET);
            permuterJoker(T,p1,R); tour++; sleep(2); continue;
        }

        visible[p1]=1;
        if(mode==2) memoriserCarte(mPos,mVal,&mNb,p1,T[p1]);
        afficherPlateau(T,visible,L,C,triche);

        if(mode==2 && j==1){ // bot choisit sa seconde carte
            sleep(1);
            p2=botChoisit(diff,T,visible,R,mPos,mVal,mNb,p1);
            printf("Le bot choisit la position : %d\n",p2);
        }
        else do{ printf("Joueur %d, Pos 2 : ",j+1); scanf("%d",&p2); }while(p2<0||p2>=R||T[p2]==-1||visible[p2]==1||p2==p1);

        if(T[p2]==0){ // gestion du joker carte 2 [cite: 16, 85]
            printf(ROUGE"JOKER ! Permutation et masquage...\n"RESET);
            visible[p1]=0; permuterJoker(T,p2,R); tour++; sleep(2); continue;
        }

        visible[p2]=1;
        if(mode==2) memoriserCarte(mPos,mVal,&mNb,p2,T[p2]);
        afficherPlateau(T,visible,L,C,triche);
        sleep(2); // delai de memorisation 

        if(T[p1]==T[p2]){ // validation de la paire [cite: 94]
            printf(VERT"Paire trouvee !\n"RESET);
            int v=T[p1]; T[p1]=-1; T[p2]=-1; // [cite: 100]
            if(j==0) score1++; else score2++;
            reste--;
            if(mode==2) nettoyerMemoire(mPos,mVal,&mNb,v); // [cite: 124]
        }
        else{
            printf(ROUGE"Echec.\n"RESET);
            visible[p1]=0; visible[p2]=0; tour++;
        }
    }

    printf(VERT"\n--- FIN DE LA PARTIE ---\n"RESET);
    if(mode==3) printf("Duree totale : %lds\n",time(NULL)-debut); // [cite: 106]
    else printf("Score final : J1 %d - J2 %d\n",score1,score2);
}


/* point d'entree du programme et boucle menu */
int main(){
    srand(time(NULL));
    int tr=0,ch;

    while(1){
        menuPrincipal(tr);
        printf("Action : ");

        if(scanf("%d",&ch)!=1){
            while(getchar()!='\n'); // purge du flux en cas d'erreur
            continue;
        }

        if(ch==1){ 
            int m=menuJeu(); 
            lancerJeu(tr,m,(m==2)?menuBot():0); 
        }
        else if(ch==2) tr=!tr;
        else if(ch==3) break;
    }

    return 0;
}