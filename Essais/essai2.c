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


/* Madame, cette fonction vérifie que le plateau est bien impair et pas 1x1 */
bool dimensionsImpaires(int L,int C){
    if((L%2)!=0 && (C%2)!=0 && (L*C)>1) return true; // [cite: 14, 15]
    return false;
}


void menuPrincipal(int triche){
    printf(MAGENTA"====================================\n");
    printf("        BIENVENUE SUR MEMORYX\n");
    printf("====================================\n"RESET);
    printf(CYAN"1. Lancer une partie\n");
    printf("2. Mode Triche : %s\n",triche?"ACTIVE":"DESACTIVE");
    printf("3. Fermer le jeu\n"RESET);
    printf(MAGENTA"====================================\n"RESET);
}


/* Menu pour les modes demandés dans le sujet */
int menuJeu(){
    int choix;


    while(1){
        printf("\n"JAUNE"--- CHOIX DU MODE ---\n"RESET);
        printf("1. Duel (2 joueurs)\n");
        printf("2. Défi contre l'ordinateur\n");
        printf("3. Solitaire (Contre la montre)\n"); // [cite: 119]
        printf("Choix : ");
        scanf("%d",&choix);
        if(choix>=1 && choix<=3) return choix;
        printf(ROUGE"Invalide ! Tapez 1, 2 ou 3.\n"RESET);
    }
}


/* On garde les 3 niveaux de bot pour votre barème */
int menuBot(){
    int choix;


    while(1){
        printf("\n"CYAN"--- NIVEAU DU BOT ---\n"RESET);
        printf("1. Débutant (Aléatoire)\n");
        printf("2. Avancé (Mémoire)\n");
        printf("3. Maître (Trheur)\n");
        printf("Choix : ");
        scanf("%d",&choix);
        if(choix>=1 && choix<=3) return choix;
    }
}


/* Le Joker change de place avec une carte encore en jeu */
void permuterJoker(int T[],int posJoker,int R){
    int r;


    do{
        r=rand()%R; // [cite: 110]
    }while(T[r]==-1); // Doit être une carte sur le plateau [cite: 108]


    int tmp=T[posJoker];
    T[posJoker]=T[r];
    T[r]=tmp;
}


/* Initialisation avec la table P comme demandé dans le PDF */
void initialiserTableau(int T[],int L,int C){
    int i,R=L*C;
    int P[MAX];


    for(i=0;i<R;i++) P[i]=i; // Remplissage 0 à R-1 [cite: 71]


    for(i=0;i<R;i++){ // Mélange de la table P [cite: 72]
        int r=rand()%R;
        int tmp=P[i];
        P[i]=P[r];
        P[r]=tmp;
    }


    T[P[0]]=0; // Placement Joker [cite: 73]
    int val=1;


    for(i=1;i<R;i+=2){ // Placement des paires [cite: 73]
        T[P[i]]=val;
        T[P[i+1]]=val;
        val++;
    }
}


/* Affichage fixe : les cases -1 sont vides mais la grille reste */
void afficherPlateau(int T[],int visible[],int L,int C,int triche){
    int i,j,k=0;


    printf("\n    ");
    for(j=0;j<C;j++) printf(GRIS" %2d "RESET,j);
    printf("\n");


    for(i=0;i<L;i++){
        printf(GRIS"%2d |"RESET,i);
        for(j=0;j<C;j++){
            if(T[k]==-1) printf("    "); // Case vide 
            else if(triche==1 || visible[k]==1){
                if(T[k]==0) printf(ROUGE" JK "RESET);
                else printf(VERT" %2d "RESET,T[k]);
            }
            else printf(BLEU" %2d "RESET,k); // Affiche la position [cite: 56, 102]
            k++;
        }
        printf("\n");
    }
}


/* Le bot oublie les cartes quand elles sortent du jeu */
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


/* Mise à jour ou ajout dans la mémoire du robot */
void memoriserCarte(int mPos[],int mVal[],int *mNb,int pos,int val){
    for(int i=0;i<*mNb;i++){
        if(mPos[i]==pos){
            mVal[i]=val; // Correction si Joker est passé par là [cite: 125, 126]
            return;
        }
    }
    mPos[*mNb]=pos;
    mVal[*mNb]=val;
    (*mNb)++;
}


bool chercherPaire(int mPos[],int mVal[],int mNb,int *p1,int *p2){
    for(int i=0;i<mNb;i++)
        for(int j=i+1;j<mNb;j++)
            if(mVal[i]==mVal[j]){ *p1=mPos[i]; *p2=mPos[j]; return true; }
    return false;
}


/* IA avec les 3 comportements distincts */
void tourBot(int diff,int T[],int visible[],int R,int mPos[],int mVal[],int mNb,int *p1,int *p2){
    if(diff==3){ // Mode Dieu : il triche sans regarder la mémoire
        for(int i=0;i<R;i++)
            for(int j=i+1;j<R;j++)
                if(T[i]==T[j] && T[i]>0 && visible[i]==0 && visible[j]==0){ *p1=i; *p2=j; return; }
    }


    if(diff>=2 && chercherPaire(mPos,mVal,mNb,p1,p2)) return; // Utilise sa mémoire [cite: 130]


    do{ *p1=rand()%R; }while(T[*p1]==-1 || visible[*p1]==1);
    do{ *p2=rand()%R; }while(T[*p2]==-1 || visible[*p2]==1 || *p2==*p1);
}


/* Fonction de jeu principale */
void lancerJeu(int triche,int mode,int diff){
    int L,C;


    while(1){
        printf("Dimensions L et C (impairs) : ");
        scanf("%d %d",&L,&C);
        if(dimensionsImpaires(L,C)) break;
        printf(ROUGE"Erreur : nombres impairs et produit > 1 requis !\n"RESET);
    }


    int R=L*C,T[MAX],visible[MAX],score1=0,score2=0,reste=(R-1)/2,tour=0;
    int mPos[MAX],mVal[MAX],mNb=0;
    time_t debut=time(NULL);


    for(int i=0;i<R;i++) visible[i]=0;
    initialiserTableau(T,L,C);


    while(reste>0){
        int j=(mode==3)?0:tour%2; // Joueur 1 (0) ou 2/Bot (1)
        afficherPlateau(T,visible,L,C,triche);


        if(mode==3) printf(CYAN"Temps écoulé : %lds\n"RESET,time(NULL)-debut); // 
        else printf(JAUNE"Score J1: %d | J2/Bot: %d\n"RESET,score1,score2);


        int p1,p2;


        if(mode==2 && j==1){ // Tour du bot
            tourBot(diff,T,visible,R,mPos,mVal,mNb,&p1,&p2);
            printf("Le Bot choisit la position %d...\n",p1); sleep(1);
        }
        else{
            do{
                printf("Joueur %d, choisissez Pos 1 : ",j+1);
                scanf("%d",&p1);
            }while(p1<0||p1>=R||T[p1]==-1||visible[p1]==1);
        }


        if(T[p1]==0){ // Cas Joker première carte [cite: 84]
            printf(ROUGE"JOKER ! La carte se déplace...\n"RESET);
            permuterJoker(T,p1,R); tour++; sleep(2); continue;
        }


        visible[p1]=1;
        if(mode==2) memoriserCarte(mPos,mVal,&mNb,p1,T[p1]);
        afficherPlateau(T,visible,L,C,triche);


        if(mode==2 && j==1){
            printf("Le Bot choisit la position %d...\n",p2); sleep(1);
        }
        else{
            do{
                printf("Joueur %d, choisissez Pos 2 : ",j+1);
                scanf("%d",&p2);
            }while(p2<0||p2>=R||T[p2]==-1||visible[p2]==1||p2==p1);
        }


        if(T[p2]==0){ // Cas Joker deuxième carte [cite: 85]
            printf(ROUGE"JOKER ! Mauvaise pioche...\n"RESET);
            visible[p1]=0; permuterJoker(T,p2,R); tour++; sleep(2); continue;
        }


        visible[p2]=1;
        if(mode==2) memoriserCarte(mPos,mVal,&mNb,p2,T[p2]);
        afficherPlateau(T,visible,L,C,triche);
        sleep(2); // Temps d'observation [cite: 93]


        if(T[p1]==T[p2]){
            printf(VERT"PAIRE TROUVÉE !\n"RESET);
            int v=T[p1];
            T[p1]=-1; T[p2]=-1; // Cartes retirées [cite: 81, 100]
            if(j==0) score1++; else score2++;
            reste--;
            if(mode==2) nettoyerMemoire(mPos,mVal,&mNb,v);
        }
        else{
            printf(ROUGE"RATÉ !\n"RESET);
            visible[p1]=0; visible[p2]=0; tour++;
        }
    }


    printf(VERT"\n--- PARTIE FINIE ---\n"RESET);
    if(mode==3) printf("Bravo ! Temps final : %lds\n",time(NULL)-debut);
    else printf("Score final -> J1: %d | J2: %d\n",score1,score2);
}


int main(){
    srand(time(NULL));
    int tr=0,ch;


    while(1){
        menuPrincipal(tr);
        printf("Action : ");


        if(scanf("%d",&ch)!=1){
            while(getchar()!='\n'); // Sécurité si on tape des lettres
            continue;
        }


        if(ch==1){ 
            int m=menuJeu(); 
            lancerJeu(tr,m,(m==2)?menuBot():0); 
        }
        else if(ch==2) tr=!tr;
        else if(ch==3) break;
        else printf(ROUGE"Choix inconnu !\n"RESET);
    }


    return 0;
}