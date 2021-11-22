#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define JET 5;
typedef int jet[JET];

void demande_nom(char j1[20], char j2[20]){
    printf("nom joueur 1 ?\n");
    scanf("%s", j1);
    printf("nom joueur 2 ?\n");
    scanf("%s", j2);
}

void somme_des(jet jet_des, int somme_des){
    somme_des = 0;
    for(i=1, i<JET, i++){
        somme_des = somme_des + i; //rajoute i à la somme des dés
    }
}

bool menufin(){
    int val;
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
    char nom_joueur1[20], nom_joueur2[20];
    demande_nom(nom_joueur1,nom_joueur2);
    return EXIT_SUCCESS;
}
