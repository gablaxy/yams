#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define JET 5
#define LIGNES 17
typedef int tab_jet[JET]; // tableau d'un jet de dé
typedef char *feuille[LIGNES]; // tableau des combinaisons à titre informatif pour les joueurs
typedef int feuille_score[LIGNES]; // tableau de score des joueurs

/**
 * @brief jette un dé
 * 
 * @return un entier qui correspond au résultat du lancer
 */
int jet_un_de(){
    
    return rand() % 6+1;
}

/**
 * @brief lance 5 fois un dés et stocke dans un tableau les résultats
 * 
 * @param tab_jet tableau d'entiers où stocker les résultat des 5 lancés
 */
void jet(tab_jet resultats){
    int i;
    for(i=0; i<JET; i++){
        resultats[i] = jet_un_de(); 
    }
}


/**
 * @brief demande deux pseudos et les affectent dans deux chaines de caractères
 * 
 * @param char chaines de caractère ( deux ) de 15 caractères max
 */
;void demande_nom(char j1[15], char j2[15]){
    bool stop = false;
    while(!stop){
        printf("nom joueur 1 ?\n");
        scanf("%s", j1);
        printf("nom joueur 2 ?\n");
        scanf("%s", j2);
        if(strlen(j1) > 15 || strlen(j2) > 15){
            printf("nom trop long rééssayez\n");
        }else{
            stop = true;
        }
    }
    printf("%s %s\n",j1,j2);
}


/**
 * @brief calcule la somme du jet qui vient d'être effectué
 * 
 * @param tab_jet tableau de 5 valeurs représentant 5 jets de dé 
 * @return la somme des 5 valeurs ( entier )
 */
int somme(tab_jet jet){
    int somme = 0;
    int i;
    for(i=0; i<JET; i++){
        somme = somme + jet[i];
    }
    return somme;
}

/**
 * @brief affiche le jet qui vient d'être effectué
 * 
 * @param tab_jet tableau de 5 valeurs représentant 5 jets de dé 
 * @param entier , la somme des 5 valeurs du tableau
 */
void affiche_jet(tab_jet jet, int somme){
    printf(" _____   _____   _____   _____   _____\n");
    printf("|     | |     | |     | |     | |     |\n");
    printf("|  %d  | |  %d  | |  %d  | |  %d  | |  %d  |\n",jet[0], jet[1], jet[2], jet[3], jet[4]);
    printf("|     | |     | |     | |     | |     |\n");
    printf(" ¯¯¯¯¯   ¯¯¯¯¯   ¯¯¯¯¯   ¯¯¯¯¯   ¯¯¯¯¯\n");
    printf("somme totale du jet : %d\n", somme);
}

/**
 * @brief affiche les feuille de score
 * 
 * @param feuille combinaisons
 * @param feuille_score tableau des scores du joueur 1
 * @param feuille_score tableau des scores du joueur 2
 * @param char pseudo du joueur 1 de 15 caractères maximum
 * @param char pseudo du joueur 2 de 15 caractères maximum
 */
void affiche_tab(feuille score, feuille_score joueur1, feuille_score joueur2,char j1[15], char j2[15]){
    int i;
    printf("     |Scores              |%10s|%10s|\n",j1,j2);
    for(i=0; i<LIGNES; i++){
        if(joueur1[i] == -1 && joueur2[i] == -1){ // met des trous si les case ne sont pas encore remplies/bloquées
            printf("%s|\t|\t|\n", score[i]);
        }else if(joueur1[i] == -1){
            printf("%s|\t|%2d\t|\n", score[i], joueur2[i]);
        }else if(joueur2[i] == -1){
            printf("%s|%2d\t|\t|\n", score[i], joueur1[i]);
        }else{
            printf("%s|%2d\t|%2d\t|\n", score[i], joueur1[i], joueur2[i]);
        }
    }
}


/**
 * @brief initialise les feuilles de score au début de la partie
 * 
 * @param feuille_score tableau des scores du joueur 1
 * @param feuille_score tableau des scores du joueur 2
 */
void initialisation_score(feuille_score joueur1, feuille_score joueur2){
    for(int i=0; i<LIGNES; i++){
        joueur1[i] = -1;
        joueur2[i] = -1;
    }
}

/**
 * @brief réinitialise à 0 le tableau des dés bloqués
 * 
 * @param tab_jet tableau qui contiendra les dés bloqués 
 */
void reset_tab_jet(tab_jet bloque){
    for(int i=0; i<JET; i++){
        bloque[i]=0;
    }
}

/**
 * @brief Calcule les totaux des feuilles de score
 * 
 * @param feuille_score tableau des scores du joueur dont on veut faire les totaux
 */
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

/**
 * @brief renvoie le nombre d'occurence de x dans un tableau de nombres
 * 
 * @param entier x dont on veut compter le nombre d'occurences
 * @param tab_jet tableau de 5 valeurs représentant 5 jets de dé 
 * @return int nombre d'occurence de x dans le tableau
 */
int total_de_x(int x, tab_jet jet_courant){
    int nb_occurence = 0;
    for(int i=0; i<JET; i++){
        if(jet_courant[i] == x){
            nb_occurence = nb_occurence + 1;
        }
    }
    return nb_occurence;
}

/**
 * @brief renvoie la valeur qui apparait le plus de fois dans le lancé
 * 
 * @param tab_jet tableau de 5 valeurs représentant 5 jets de dé  
 * @return int la valeur qui a été tiré le plus de fois
 */
int plus_de_fois(tab_jet jet_courant){
    int nb_de[6]; // création d'un tableau pour répertorier le nombre d'apparition des valeurs possibles
    int val_max = 0;

    for(int i=0; i<6; i++){ // initialise à zéro tout le tableau
        nb_de[i]=0;
    }

    for(int j=0; j<JET; j++) // répertorie le nombre d'apparition des valeurs
        nb_de[jet_courant[j]-1] = nb_de[jet_courant[j]-1] + 1;

    int max = 0;
    max = nb_de[0];
    for(int y=0; y<JET; y++){ // cherche la valeur ayant le plus d'apparition
        if(max < nb_de[y]){
            max = nb_de[y];
            val_max = y+1;
        }
    }
    return val_max;
}

/**
 * @brief trie le tableau passé en paramètre
 * 
 * @param tab_jet tableau de 5 valeurs représentant 5 jets de dé  
 */
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

/**
 * @brief renvoie true si le tableau en paramètre est un full, sinon renvoie false
 * 
 * @param tab_jet tableau de 5 valeurs représentant 5 jets de dé  
 * @return true
 * @return false 
 */
bool full(tab_jet jet_courant){
    tri_jet(jet_courant);
    int max = 0;
    max = plus_de_fois(jet_courant);
    if(total_de_x(max,jet_courant) == 3){
        if(jet_courant[0]==jet_courant[1] || jet_courant[3]==jet_courant[4]){
            return true;
        }
    }
    return false;
}

/**
 * @brief renvoie true si le tableau en paramètre est une petite suite, sinon renvoie false
 * 
 * @param tab_jet tableau de 5 valeurs représentant 5 jets de dé   
 * @return true 
 * @return false 
 */
bool petite_suite(tab_jet jet_courant){
    tri_jet(jet_courant);
    if((jet_courant[0] == jet_courant[1] - 1) && (jet_courant[0] == jet_courant[2] - 2) && (jet_courant[0] == jet_courant[3] - 3)){
        return true;
    }else if((jet_courant[1] == jet_courant[2] - 1) && (jet_courant[0] == jet_courant[3] - 2) && (jet_courant[0] == jet_courant[4] - 3)){
        return true;
    }
    return false;
}

/**
 * @brief renvoie true si le tableau en paramètre est une grande suite, sinon renvoie false
 * 
 * @param tab_jet tableau de 5 valeurs représentant 5 jets de dé  
 * @return true 
 * @return false 
 */
bool grande_suite(tab_jet jet_courant){
    tri_jet(jet_courant);
    if((jet_courant[0] == jet_courant[1] - 1) && (jet_courant[0] == jet_courant[2] - 2) && (jet_courant[0] == jet_courant[3] - 3) && (jet_courant[0] == jet_courant[4] - 4)){
        return true;
    }
    return false;
}

/**
 * @brief affectation du score du jet qui vient d'être effectué dans la feuille de score du joueur
 * 
 * @param euille_score tableau des scores du joueur
 * @param tab_jet tableau de 5 valeurs représentant 5 jets de dé  
 * @param somme_des somme du tableau tab_jet contenant le résultat du lancé de dé
 */
void affectation_score(feuille_score joueur,tab_jet jet_courant, int somme_des){
    int num_case, nb_occurences, val_max;
    bool stop = false;
    printf("Choisissez dans quelle case vous voulez affecter votre score\n");
    scanf("%d", &num_case);
    while(stop == false){
        if(joueur[num_case] == -1){
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
        }else{
            printf("Numéro de case déjà pris, choisissez-en un autre !\n"); // si le nombre rentré n'est pas une valeur dispo
        }

    }
}

/**
 * @brief écrase les dés qui on été relancés si ils ont déjà été bloqués
 * 
 * @param jet_courant tableau de 5 valeurs représentant 5 jets de dé
 * @param bloque tableau de 5 valeurs représentant 5 dés bloqués ou non
 */
void fusion(tab_jet jet_courant,tab_jet bloque){
    for(int i=0; i<JET; i++){
        if(bloque[i] != 0){
            jet_courant[i] = bloque[i]; // affecte la valeur des dés bloqués dans le tableau du jet qui vient d'être effectué
        }
    }
}

/**
 * @brief blocage des dés
 * 
 * @param jet_courant tableau de 5 valeurs représentant 5 jets de dé
 * @param bloque tableau de 5 valeurs représentant 5 dés bloqués ou non 
 */
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

/**
 * @brief Menu de choix qui propose de bloquer / relancer ou de valider le lancé effectué
 * 
 * @return true bloque / relance les dés
 * @return false valide le lancé
 */
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

/**
 * @brief Menu de fin qui demande si les joueurs veulent relancer une partie ou quitter
 * 
 * @return true si relance d'une partie
 * @return false si quitter
 */
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

/**
 * @brief Affichage du vainqueur et des pts
 * 
 * @param feuille_score tableau des scores du joueur 1
 * @param feuille_score tableau des scores du joueur 2
 * @param char pseudo du joueur 1 de 15 caractères maximum
 * @param char pseudo du joueur 2 de 15 caractères maximum
 */
void affiche_vainqueur(feuille_score score1, feuille_score score2, char joueur1[15], char joueur2[15]){
    if(score1[16] > score2[16]){
        printf("%s : %d points | %s : %d points\n",joueur1,score1[16],joueur2,score2[16];)
        printf("Le vainqueur est le %s\n",joueur1);
    }else if(score1[16] < score2[16]){
        printf("%s : %d points | %s : %d points\n",joueur1,score1[16],joueur2,score2[16];)
        printf("Le vainqueur est le %s\n",joueur2);
    }else{
        printf("%s : %d points | %s : %d points\n",joueur1,score1[16],joueur2,score2[16];)
        printf("Égalité !\n");
    }
}

int main(){

    srand(time(NULL));
    feuille_score score1, score2;
    feuille combinaisons = {
        "n°1  |1 (total de 1)      ",
        "n°2  |2 (total de 2)      ",
        "n°3  |3 (total de 3)      ",
        "n°4  |4 (total de 4)      ",
        "n°5  |5 (total de 5)      ",
        "n°6  |6 (total de 6)      ",
        "n°7  |Bonus si > à 62 [35]",
        "n°8  |Total supérieur     ",
        "n°9  |Brelan [total]      ",
        "n°10 |Carré [total]       ",
        "n°11 |Full House [25]     ",
        "n°12 |Petite suite [30]   ",
        "n°13 |Grande suite [40]   ",
        "n°14 |Yams [50]           ",
        "n°15 |Chance [total]      ",
        "n°16 |Total inférieur     ",
        "n°17 |Total               " 
        };

    
    bool partie = true;
    tab_jet jet_courant;
    tab_jet des_bloques;
    char nom_joueur1[15], nom_joueur2[15];
    
    while(partie == true){
        demande_nom(nom_joueur1,nom_joueur2);
        initialisation_score(score1, score2);

        for(int i = 0; i < 13; i++){ // nb de tours de la partie 
            printf("Tour %d\n", i+1);
            printf("------------------------------------\n");

            //joueur 1
            printf("Au tour joueur 1 de jouer\n");
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

            //affichage de sa feuille de score et du lancer en cours pour le joueur
            affiche_tab(combinaisons, score1, score2, nom_joueur1, nom_joueur2);
            affiche_jet(jet_courant,somme_des);

            affectation_score(score1, jet_courant, somme_des);
            
            printf("------------------------------------\n");
            //joueur 2
   
            printf("Au tour joueur 2 de jouer\n");
            lances = 3;
            somme_des = 0;

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

            //affichage de sa feuille de score et du lancer en cours pour le joueur
            affiche_tab(combinaisons, score1, score2, nom_joueur1, nom_joueur2);
            affiche_jet(jet_courant,somme_des);

            affectation_score(score2, jet_courant, somme_des);
        }
        affiche_vainqueur(score1, score2, nom_joueur1, nom_joueur2);
        partie = menufin();
    }
    return EXIT_SUCCESS;
}
