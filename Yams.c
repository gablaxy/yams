#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define JET 5
#define LIGNES 17
typedef int tab_jet[JET]; // tableau d'un jet de dé
typedef char *feuille[LIGNES]; // tableau des combinaisons à titre informatif pour les joueurs
typedef int feuille_score[LIGNES]; // tableau de score des joueurs

// effectue un jet de dé random
int jet_un_de(){
    srand(time(NULL));
    return rand() % 6+1;
}

// effectue 5 jets de dés
void jet(tab_jet resultats){
    int i;
    for(i=0; i<JET; i++){
        sleep(1);
        resultats[i] = jet_un_de(); 
    }
}

//demande des pseudos
void demande_nom(char j1[15], char j2[15]){
    printf("nom joueur 1 ?\n");
    scanf("%s", j1);
    printf("nom joueur 2 ?\n");
    scanf("%s", j2);
    printf("%s %s\n",j1,j2);
}

//calcule la somme du jet qui vient d'être effectué
int somme(tab_jet jet){
    int somme = 0;
    int i;
    for(i=0; i<JET; i++){
        somme = somme + jet[i];
    }
    return somme;
}

//affiche le jet qui vient d'être effectué
void affiche_jet(tab_jet jet, int somme){
    printf(" _____   _____   _____   _____   _____\n");
    printf("|     | |     | |     | |     | |     |\n");
    printf("|  %d  | |  %d  | |  %d  | |  %d  | |  %d  |\n",jet[0], jet[1], jet[2], jet[3], jet[4]);
    printf("|     | |     | |     | |     | |     |\n");
    printf(" ¯¯¯¯¯   ¯¯¯¯¯   ¯¯¯¯¯   ¯¯¯¯¯   ¯¯¯¯¯\n");
    printf("somme totale du jet : %d\n", somme);
}


// affiche les feuille de score
void affiche_tab(feuille score, feuille_score joueur1, feuille_score joueur2,char j1[15], char j2[15]){
    int i;
    printf("          |Scores               |  %15s| %15s|\n",j1,j2);
    for(i=0; i<LIGNES; i++){
        if(joueur1[i] == -1 && joueur2[i] == -1){ // met des trous si les case ne sont pas encore remplies/bloquées
            printf("%s |       [ ]       |       [ ]      |\n", score[i]);
        }else if(joueur1[i] == -1){
            printf("%s |       [ ]       |       [%d]      |\n", score[i], joueur2[i]);
        }else if(joueur2[i] == -1){
            printf("%s |       [%d]       |      [ ]      |\n", score[i], joueur1[i]);
        }else{
            printf("%s |       [%d]       |       [%d]      |\n", score[i], joueur1[i], joueur2[i]);
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

// réinitialise à 0 le tableau des dés bloqués
void reset_tab_jet(tab_jet bloque){
    for(int i=0; i<JET; i++){
        bloque[i]=0;
    }
}

// Calcule les totaux des feuilles de score
void totaux(feuille_score joueur){
    int total_sup = 0;
    for(int i=0; i<7; i++){ // calcul et affectation du total supérieur
        if(joueur[i] != -1){
            total_sup = total_sup + joueur[i];
        }
    }

    int total_inf = 0;
    for(int i=8; i<15; i++){ // calcul et affectation du total inférieur
        if(joueur[i] != -1){
            total_inf = total_inf + joueur[i];
        }
    }

    joueur[16] = total_sup + total_inf; // calcul et affectation du total
}

// renvoie le nombre d'occurence de x dans un tableau de nombres
int total_de_x(int x, tab_jet jet_courant){
    int nb_occurence = 0;
    for(int i=0; i<JET; i++){
        if(jet_courant[i] == x){
            nb_occurence = nb_occurence + 1;
        }
    }
    return nb_occurence;
}

//renvoie la valeur qui apparait le plus de fois dans le lancé
int plus_de_fois(tab_jet jet_courant){
    int nb_de[6]; // création d'un tableau pour répertorier le nombre d'apparition des valeurs possibles
    int val_max;

    for(int i=0; i<6; i++){ // initialise à zéro tout le tableau
        nb_de[i]=0;
    }

    for(int j=0; j<JET; j++) // répertorie le nombre d'apparition des valeurs
        nb_de[jet_courant[j]-1] = nb_de[jet_courant[j]-1] + 1;

    int max = jet_courant[0];
    for(int y=0; y<JET; y++){ // cherche la valeur ayant le plus d'apparition
        if(max < nb_de[y]){
            max = nb_de[y];
            val_max = y+1;
        }
    }
    return val_max;
}

// trie le jet courant
void tri_jet(tab_jet jet_courant){
    int min, x;

    for (int  i=0; i<JET - 1; i++){
        min = i;
        for (int j = i + 1; j<JET; j++)
            if (jet_courant[j] < jet_courant[min])
                min = j;
        x = jet_courant[i];
        jet_courant[i] = jet_courant[min];
        jet_courant[min] = x;
    }
}

// renvoie true si c'est un full, false sinon
bool full(tab_jet jet_courant){
    tri_jet(jet_courant);
    int val_max = plus_de_fois(jet_courant);
    if(total_de_x(val_max,jet_courant) == 3){
        if(jet_courant[0]==jet_courant[1] || jet_courant[3]==jet_courant[4]){
            return true;
        }
    }
    return false;
}

// renvoie true si c'est une petite suite, false sinon
bool petite_suite(tab_jet jet_courant){
    tri_jet(jet_courant);
    if((jet_courant[0] == jet_courant[1] - 1) && (jet_courant[0] == jet_courant[2] - 2) && (jet_courant[0] == jet_courant[3] - 3)){
        return true;
    }else if((jet_courant[1] == jet_courant[2] - 1) && (jet_courant[0] == jet_courant[3] - 2) && (jet_courant[0] == jet_courant[4] - 3)){
        return true;
    }
    return false;
}

// renvoie true si c'est une grande suite, false sinon
bool grande_suite(tab_jet jet_courant){
    tri_jet(jet_courant);
    if((jet_courant[0] == jet_courant[1] - 1) && (jet_courant[0] == jet_courant[2] - 2) && (jet_courant[0] == jet_courant[3] - 3) && (jet_courant[0] == jet_courant[4] - 4)){
        return true;
    }
    return false;
}

//affectation du score du jet qui vient d'être effectué dans la feuille de score du joueur
void affectation_score(feuille_score joueur,tab_jet jet_courant, int somme_des){
    int num_case, nb_occurences, val_max;
    bool stop = false;
    printf("Choisissez dans quelle case vous voulez affecter votre score\n");
    scanf("%d", &num_case);

    while(stop == false){
        switch (num_case){ // test si les combinaisons sont valides
            case 1: // total de 1
                nb_occurences = total_de_x(1,jet_courant);
                if(nb_occurences > 0){
                    joueur[num_case - 1] = nb_occurences;
                    stop = true;
                }else{
                    printf("Combinaison impossible, entrez une autre case.\n");
                }
                break;

            case 2: // total de 2
                nb_occurences = total_de_x(2,jet_courant);
                if(nb_occurences > 0){
                    joueur[num_case - 1] = nb_occurences*2;
                    stop = true;
                }else{
                    printf("Combinaison impossible, entrez une autre case.\n");
                }
                break;

            case 3: // total de 3
                nb_occurences = total_de_x(3,jet_courant);
                if(nb_occurences > 0){
                    joueur[num_case - 1] = nb_occurences*3;
                    stop = true;
                }else{
                    printf("Combinaison impossible, entrez une autre case.\n");
                }                
                break;

            case 4: // total de 4
                nb_occurences = total_de_x(4,jet_courant);
                if(nb_occurences > 0){
                    joueur[num_case - 1] = nb_occurences*4;
                    stop = true;
                }else{
                    printf("Combinaison impossible, entrez une autre case.\n");
                }                
                break;

            case 5: // total de 5
                nb_occurences = total_de_x(5,jet_courant);
                if(nb_occurences > 0){
                    joueur[num_case - 1] = nb_occurences*5;
                    stop = true;
                }else{
                    printf("Combinaison impossible, entrez une autre case.\n");
                }                
                break;

            case 6: // total de 6
                nb_occurences = total_de_x(6,jet_courant);
                if(nb_occurences > 0){
                    joueur[num_case - 1] = nb_occurences*6;
                    stop = true;
                }else{
                    printf("Combinaison impossible, entrez une autre case.\n");
                }                
                break;

            case 9: // brelan
                val_max = plus_de_fois(jet_courant);
                nb_occurences = total_de_x(val_max,jet_courant);
                if(nb_occurences > 2){
                    joueur[num_case - 1] = 3*val_max;
                    stop = true;
                }else{
                    printf("Combinaison impossible, entrez une autre case.\n");
                }                
                break;

            case 10: // carré
                val_max = plus_de_fois(jet_courant);
                nb_occurences = total_de_x(val_max,jet_courant);
                if(nb_occurences > 3){
                    joueur[num_case - 1] = 4*val_max;
                    stop = true;
                }else{
                    printf("Combinaison impossible, entrez une autre case.\n");
                }                
                break;

            case 11: // full house
                if(full(jet_courant) == true){
                    joueur[num_case - 1] = 25;
                    stop = true;
                }else{
                    printf("Combinaison impossible, entrez une autre case.\n");
                }       
                break;

            case 12: // petite suite 
                if(petite_suite(jet_courant) == true){
                    joueur[num_case - 1] = 30;
                    stop = true;
                }else{
                    printf("Combinaison impossible, entrez une autre case.\n");
                }           
                break;

            case 13: // grande suite    
                if(grande_suite(jet_courant) == true){
                    joueur[num_case - 1] = 30;
                    stop = true;
                }else{
                    printf("Combinaison impossible, entrez une autre case.\n");
                }       
                break;

            case 14: // yams
                val_max = plus_de_fois(jet_courant);
                nb_occurences = total_de_x(val_max,jet_courant);
                if(nb_occurences == 5){
                    joueur[num_case - 1] = 50;
                    stop = true;
                }else{
                    printf("Combinaison impossible, entrez une autre case.\n");
                }             
                break;

            case 15: // chance  
                joueur[num_case - 1] = somme_des;
                stop = true;        
                break;
                
            default:
                printf("Numéro de case invalide, choisissez-en un autre !\n"); // si le nombre rentré n'est pas une valeur dispo
                break;
        }
        if(stop == false){
            printf("Choisissez dans quelle case vous voulez affecter votre score\n");
            scanf("%d", &num_case);
        }
    }
}

//écrase les dés qui on été relancés alors qu'ils sont bloqués
void fusion(tab_jet jet_courant,tab_jet bloque){
    for(int i=0; i<JET; i++){
        if(bloque[i] != 0){
            jet_courant[i] = bloque[i]; // affecte la valeur des dés bloqués dans le tableau du jet qui vient d'être effectué
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
            bloque[val-1] = jet_courant[val-1]; // sauvegarde la valeur du dé bloqué dans un tableau
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
        "case n°1  |1 (total de 1)      ",
        "case n°2  |2 (total de 2)      ",
        "case n°3  |3 (total de 3)      ",
        "case n°4  |4 (total de 4)      ",
        "case n°5  |5 (total de 5)      ",
        "case n°6  |6 (total de 6)      ",
        "case n°7  |Bonus si > à 62 [35]",
        "case n°8  |Total supérieur     ",
        "case n°9  |Brelan [total]      ",
        "case n°10 |Carré [total]       ",
        "case n°11 |Full House [25]     ",
        "case n°12 |Petite suite [30]   ",
        "case n°13 |Grande suite [40]   ",
        "case n°14 |Yams [50]           ",
        "case n°15 |Chance [total]      ",
        "case n°16 |Total inférieur     ",
        "case n°17 |Total               " 
        };

    bool partie = true;
    tab_jet jet_courant;
    tab_jet des_bloques;
    char nom_joueur1[20], nom_joueur2[20];

    while(partie == true){
        //demande_nom(nom_joueur1,nom_joueur2);
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
