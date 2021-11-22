#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>


#define JET 5
#define LIGNES 17
typedef int tab_jet[JET];//tableau d'1 = 0 jet de dé
typedef char *feuille[LIGNES];//tableau des combinaisons à titre informatif pour les joueurs
typedef int feuille_score[LIGNES]; //tableau de score des joueurs

//effectue 1 = 0 jet de dé random
int jet_un_de(){
    srand(time(NULL));
    return rand() % 6+1;
}

//effectue 5 jets de dés
void jet(tab_jet resultats){
    int i;
    for(i=0; i<JET; i++){
        sleep(1);
        resultats[i] = jet_un_de();
        
    }
}

//formate le nom pour pouvoir l'entrer dans le tableau et l'afficher 
void formater_nom(char j[15]){
    int nb_caract = 0;
    for(int i=0;j[i];i++){
        nb_caract++;
    }
    for(int i=nb_caract;i<15;i++){
        j[i]=' ';
    }
}

//demande les pseudos des joueurs
void demande_nom(char j1[15], char j2[15]){
    printf("nom joueur 1 ?\n");
    scanf("%s", j1);
    formater_nom(j1);
    printf("nom joueur 2 ?\n");
    scanf("%s", j2);
    formater_nom(j2);
    printf("%s %s\n",j1,j2);
}

//calcule la somme du jet qui vient d'être effectué
int somme(tab_jet jet){
    int somme = 0;
    int i;
    for(i=0; i<JET; i++){
        somme = somme + jet[i]; //rajoute i à la somme des dés
    }
    return somme;
}

//affiche le jet qui vient d'être effectué
void affiche_jet(tab_jet jet, int somme){
    for(int i=0; i<JET; i++){
        printf("%d : %d\n", i, jet[i]);
    }
    printf("somme : %d\n", somme);
}


//affiche les feuille de score ( avec des trous si les cases ne sont pas encore remplies )
void affiche_tab(feuille score, feuille_score joueur1, feuille_score joueur2,char j1[15], char j2[15]){
    int i;
    printf("Scores               | %s | %s\n",j1,j2);
    for(i=0; i<LIGNES; i++){
        if(joueur1[i] == -1 && joueur2[i] == -1){
            printf("%s |    [ ]          |    [ ]\n", score[i]);
        }else if(joueur1[i] == -1){
            printf("%s |    [ ]          |    [%d]\n", score[i], joueur2[i]);
        }else if(joueur2[i] == -1){
            printf("%s |    [%d]          |    [ ]\n", score[i], joueur1[i]);
        }else{
            printf("%s |    [%d]          |    [%d]\n", score[i], joueur1[i], joueur2[i]);
        }
    }
}

// initialise les feuilles de score au début de la partie
void initialisation_score(feuille_score joueur1, feuille_score joueur2){
    for(int i=0; i<LIGNES; i++){
        joueur1[i] = -1;
        joueur2[i] = -1;
    }
}

//remet à 0 le tableau des dés bloqués
void reset_tab_jet(tab_jet bloque){
    for(int i=0; i<JET; i++){
        bloque[i]=0;
    }
}

// Calcule les totaux des feuilles de score
void totaux(feuille_score joueur){
    int total_sup = 0;
    for(int i=0; i<7; i++){
        if(joueur[i] != -1){
            total_sup = total_sup + joueur[i];
        }
    }

    int total_inf = 0;
    for(int i=8; i<15; i++){
        if(joueur[i] != -1){
            total_inf = total_inf + joueur[i];
        }
    }

    joueur[16] = total_sup + total_inf;
}

//écrase les dés qui on été relancés alors qu'ils sont bloqués
void fusion(tab_jet jet_courant,tab_jet bloque){
    for(int i=0; i<JET; i++){
        if(bloque[i] != 0){
            jet_courant[i] = bloque[i];
        }
    }
}

//blocage des dés
void blocage(tab_jet jet_courant,tab_jet bloque){
    int val;
    bool stop = false;
    while(stop == false){
        printf("Quel dé voulez vous bloquer ( entrez -1 pour stopper la sélection)\n");
        scanf("%d", &val);
        if(val == -1){
            stop = true;
        }else if(val < 1 || val > 5){
            printf("erreur numéro de dé non valide, rééssayez\n");
        }else{
            bloque[val-1] = jet_courant[val-1];
        }
    }
}

//Menu de choix qui propose de bloquer / relancer ou de valider le lancé effectué
bool validation_relance(){
    int val;
    printf("Choisissez : \n");
    printf("1 - Relancer les dés (possibilitée de bloquer les dés avant la relance)\n");
    printf("2 - Valider le lancer\n");
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

//Menu de fin qui demande si les joueurs veulent relancer une partie ou quitter
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
    feuille_score score1, score2;
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
    tab_jet des_bloques;
    char nom_joueur1[20], nom_joueur2[20];

    while(partie == true){
        demande_nom(nom_joueur1,nom_joueur2);
        initialisation_score(score1, score2);

        for(int i = 0; i < 2; i++){ // nb de tours de la partie 
            printf("Tour %d\n", i+1);
            
            //joueur 1
            printf("Au joueur 1 de jouer\n");
            int lances = 3;
            int somme_des = 0;

            affiche_tab(combinaisons, score1, score2, nom_joueur1, nom_joueur2);

            jet(jet_courant);
            somme_des = somme(jet_courant);
            affiche_jet(jet_courant,somme_des);

            do{
                if(validation_relance() == true){
                    reset_tab_jet(des_bloques);
                    blocage(jet_courant,des_bloques); // choix des dés bloqués

                    jet(jet_courant); // relance les dés
                    fusion(jet_courant,des_bloques); // fusionne les dés relancés avec les dés bloqués
                    somme_des = somme(jet_courant); // fait la somme du jet en cours
                    affiche_jet(jet_courant,somme_des);// affiche le nouveau jet
                    lances--;
                }else{
                    lances = 0;
                }
            }while(lances > 0);
            //affichage de sa feuille de score et du lancer en cours pour leur joueur
            affiche_tab(combinaisons, score1, score2, nom_joueur1, nom_joueur2);
            affiche_jet(jet_courant,somme_des);
            affectation_score(score1, jet_courant, somme_des);
            


            
            //joueur 2
            /*
            printf("Au joueur 2 de jouer\n");
            lances = 3;
            somme_des = 0;
            affiche_tab(combinaisons, score1, score2, nom_joueur1, nom_joueur2);
            */
            
            
        }
        partie = menufin();
    }
    return EXIT_SUCCESS;
}

#define JET 5
#define LIGNES 17
typedef int tab_jet[JET];//tableau d'un jet de dé
typedef char *feuille[LIGNES];//tableau des combinaisons à titre informatif pour les joueurs
typedef int feuille_score[LIGNES]; //tableau de score des joueurs

//effectue un jet de dé random
int jet_un_de(){
    srand(time(NULL));
    return rand() % 6+1;
}

//effectue 5 jets de dés
void jet(tab_jet resultats){
    int i;
    for(i=0; i<JET; i++){
        sleep(1);
        resultats[i] = jet_un_de();
        
    }
}

//formate le nom pour pouvoir l'entrer dans le tableau et l'afficher 
void formater_nom(char j[15]){
    int nb_caract = 0;
    for(int i=0;j[i];i++){
        nb_caract++;
    }
    for(int i=nb_caract;i<15;i++){
        j[i]=' ';
    }
}

//demande les pseudos des joueurs
void demande_nom(char j1[15], char j2[15]){
    printf("nom joueur 1 ?\n");
    scanf("%s", j1);
    formater_nom(j1);
    printf("nom joueur 2 ?\n");
    scanf("%s", j2);
    formater_nom(j2);
    printf("%s %s\n",j1,j2);
}

//calcule la somme du jet qui vient d'être effectué
int somme(tab_jet jet){
    int somme = 0;
    int i;
    for(i=0; i<JET; i++){
        somme = somme + jet[i]; //rajoute i à la somme des dés
    }
    return somme;
}

//affiche le jet qui vient d'être effectué
void affiche_jet(tab_jet jet, int somme){
    for(int i=0; i<JET; i++){
        printf("%d : %d\n", i, jet[i]);
    }
    printf("somme : %d\n", somme);
}


//affiche les feuille de score ( avec des trous si les cases ne sont pas encore remplies )
void affiche_tab(feuille score, feuille_score joueur1, feuille_score joueur2,char j1[15], char j2[15]){
    int i;
    printf("Scores               | %s | %s\n",j1,j2);
    for(i=0; i<LIGNES; i++){
        if(joueur1[i] == -1 && joueur2[i] == -1){
            printf("%s |    [ ]          |    [ ]\n", score[i]);
        }else if(joueur1[i] == -1){
            printf("%s |    [ ]          |    [%d]\n", score[i], joueur2[i]);
        }else if(joueur2[i] == -1){
            printf("%s |    [%d]          |    [ ]\n", score[i], joueur1[i]);
        }else{
            printf("%s |    [%d]          |    [%d]\n", score[i], joueur1[i], joueur2[i]);
        }
    }
}

// initialise les feuilles de score au début de la partie
void initialisation_score(feuille_score joueur1, feuille_score joueur2){
    for(int i=0; i<LIGNES; i++){
        joueur1[i] = -1;
        joueur2[i] = -1;
    }
}

//remet à 0 le tableau des dés bloqués
void reset_tab_blocage(tab_jet bloque){
    for(int i=0; i<JET; i++){
        bloque[i]=0;
    }
}

// Calcule les totaux des feuilles de score
void totaux(feuille_score joueur){
    int total_sup = 0;
    for(int i=0; i<7; i++){
        if(joueur[i] != -1){
            total_sup = total_sup + joueur[i];
        }
    }

    int total_inf = 0;
    for(int i=8; i<15; i++){
        if(joueur[i] != -1){
            total_inf = total_inf + joueur[i];
        }
    }

    joueur[16] = total_sup + total_inf;
}

//affectation du score du jet qui vient d'être effectué dans la feuille de score du joueur
void affectation_score(){

}

//écrase les dés qui on été relancés alors qu'ils sont bloqués
void fusion(tab_jet jet_courant,tab_jet bloque){
    for(int i=0; i<JET; i++){
        if(bloque[i] != 0){
            jet_courant[i] = bloque[i];
        }
    }
}

//blocage des dés
void blocage(tab_jet jet_courant,tab_jet bloque){
    int val;
    bool stop = false;
    while(stop == false){
        printf("Quel dé voulez vous bloquer ( entrez -1 pour stopper la sélection)\n");
        scanf("%d", &val);
        if(val == -1){
            stop = true;
        }else if(val < 1 || val > 5){
            printf("erreur numéro de dé non valide, rééssayez\n");
        }else{
            bloque[val-1] = jet_courant[val-1];
        }
    }
}

//Menu de choix qui propose de bloquer / relancer ou de valider le lancé effectué
bool validation_relance(){
    int val;
    printf("Choisissez : \n");
    printf("1 - Relancer les dés (possibilitée de bloquer les dés avant la relance)\n");
    printf("2 - Valider le lancer\n");
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

//Menu de fin qui demande si les joueurs veulent relancer une partie ou quitter
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
    feuille_score score1, score2;
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
    tab_jet des_bloques;
    char nom_joueur1[20], nom_joueur2[20];

    while(partie == true){
        demande_nom(nom_joueur1,nom_joueur2);
        initialisation_score(score1, score2);

        for(int i = 0; i < 2; i++){ // nb de tours de la partie 
            printf("Tour %d\n", i+1);
            
            //joueur 1
            printf("Au joueur 1 de jouer\n");
            int lances = 3;
            int somme_des = 0;

            affiche_tab(combinaisons, score1, score2, nom_joueur1, nom_joueur2);

            jet(jet_courant);
            somme_des = somme(jet_courant);
            affiche_jet(jet_courant,somme_des);

            do{
                if(validation_relance() == true){
                    reset_tab_blocage(des_bloques);
                    blocage(jet_courant,des_bloques); // choix des dés bloqués

                    jet(jet_courant); // relance les dés
                    fusion(jet_courant,des_bloques); // fusionne les dés relancés avec les dés bloqués
                    somme_des = somme(jet_courant); // fait la somme du jet en cours
                    lances--;
                }else{
                    lances = 0;

                }
                //affichage de sa feuille de score et du lancer en cours pour leur joueur
                affiche_tab(combinaisons, score1, score2, nom_joueur1, nom_joueur2);
                affiche_jet(jet_courant,somme_des);


            }while(lances > 0);
            


            
            //joueur 2
            /*
            printf("Au joueur 2 de jouer\n");
            lances = 3;
            somme_des = 0;
            affiche_tab(combinaisons, score1, score2, nom_joueur1, nom_joueur2);
            */
            
            
        }
        partie = menufin();
    }
    return EXIT_SUCCESS;
}
