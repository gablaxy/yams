#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define JET 5
#define LIGNES 17
typedef int tab_jet[JET];
typedef char *feuille[LIGNES];

int jet_un_de(){
    srand(time(NULL));
    return rand() % 6+1;
}

void jet(tab_jet resultats){
    int i;
    for(i=0; i<JET; i++){
        sleep(1);
        resultats[i] = jet_un_de();
        
    }
}

void formater_nom(char j[15]){
    int nb_caract = 0;
    for(int i=0;j[i];i++){
        nb_caract++;
    }
    for(int i=nb_caract;i<15;i++){
        j[i]=' ';
    }
}

void demande_nom(char j1[15], char j2[15]){
    printf("nom joueur 1 ?\n");
    scanf("%s", j1);
    formater_nom(j1);
    printf("nom joueur 2 ?\n");
    scanf("%s", j2);
    formater_nom(j2);
    printf("%s %s\n",j1,j2);
}

int somme(tab_jet jet){
    int somme = 0;
    int i;
    for(i=0; i<JET; i++){
        somme = somme + jet[i]; //rajoute i à la somme des dés
    }
    return somme;
}

void affiche_jet(tab_jet jet){
    int i;
    for(i=0; i<JET; i++){
        printf("%d : %d\n", i, jet[i]);
    }
}

void affiche_tab(feuille score, feuille_score joueur1, feuille_score joueur2,char j1[15], char j2[15]){
    int i;
    printf("Scores               | %s | %s\n",j1,j2);
    for(i=0; i<LIGNES; i++){
        if(joueur1[i] == -1){
            printf("%s |    [ ]    |    [%d]\n", score[i], joueur2[i]);
        }else if(joueur2[i] == -1){
            printf("%s |    [%d]    |    [ ]\n", score[i], joueur1[i]);
        }else if(joueur1[i] == -1 && joueur2[i] == -1){
            printf("%s |    [ ]    |    [ ]\n", score[i]);
        }else{
            printf("%s |    [%d]    |    [%d]\n", score[i], joueur1[i], joueur2[i]);
        }
    }
}

void initialisation_score(feuille joueur1, feuille joueur2){
    int i;
    for(i=0; i<LIGNES; i++){
        joueur1[i] = "";
        joueur2[i] = "";
    }
}

bool menufin(){
    int val;
    printf("Choisissez :\n");
    printf("1 - Relancer une partie\n");
    printf("2 - Quitter\n");
    scanf("%d", &val);
    while(val < 1 || val > 2){
        printf("Erreur, rentrez 1 ou 2\n");
        scanf("%d", &val);
    }
    if(val == 1){
        return true;
    }else{
        return false;
    }
}

int main(){
    feuille feuille_score1, feuille_score2;
    feuille combinaisons = {
        "1 (total de 1)      ",
        "2 (total de 2)      ",
        "3 (total de 3)      ",
        "4 (total de 4)      ",
        "5 (total de 5)      ",
        "6 (total de 6)      ",
        "Bonus si > à 62 [35]",
        "Total supérieur     ",
        "Brelan [total]      ",
        "Carré [total]       ",
        "Full House [25]     ",
        "Petite suite [30]   ",
        "Grande suite [40]   ",
        "Yams [50]           ",
        "Chance [total]      ",
        "Total inférieur     ",
        "Total               " 
        };
    bool partie = true;
    tab_jet jet_courant;
    int somme_des = 0;
    char nom_joueur1[20], nom_joueur2[20];

    while(partie == true){
        demande_nom(nom_joueur1,nom_joueur2);
        
        
        jet(jet_courant);
        somme_des = somme(jet_courant);
        affiche_jet(jet_courant);
        printf("somme : %d\n", somme_des);

    
        initialisation_score(feuille_score1, feuille_score2);
        affiche_tab(combinaisons, feuille_score1, feuille_score2, nom_joueur1, nom_joueur2);
        partie = menufin();
    }
    return EXIT_SUCCESS;
}
