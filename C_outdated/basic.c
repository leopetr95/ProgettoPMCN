#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "basic.h"
#include "parser.h"

double*alloc_array_double(int lenght){
    if(lenght<=0){
        handle_error_with_exit("error in parameter\n");
    }
    double *array=malloc(sizeof(double)*(lenght));
    if(array==NULL){
        handle_error_with_exit("error in malloc\n");
    }
    memset(array,0,sizeof(double)*lenght);
    return array;
}
void free_all_memory(double*tr_batch){ //necessario indicare tutte le variabili del sistema.
    free(tr_batch);
}
void handle_error_with_exit(char*error_string){//uccide il processo dopo essersi accorto di un errore
    if(error_string==NULL){
        printf("error string is NULL\n");
        exit(EXIT_FAILURE);
    }
    printf("%s",error_string);
    exit(EXIT_FAILURE);
}
void check_state_variables_during_simulation(int N, struct state state){ //da modificare per aggiungere i controlli da eseguire durante la simulazione.
    if(state.num_balls_icecream_type1 < 0 || state.num_balls_icecream_type2 < 0 || state.num_balls_icecream_type3 < 0){
        handle_error_with_exit("During Simulation Error 1: Not Enough Ice Cream Balls\n");
    }
    return;
}


void check_state_variables_after_simulation(struct state state){
    if(state.num_user_cassa != 0){ //da modificare per aggiungere i controlli da eseguire dopo la simulazione
        handle_error_with_exit("After Simulation Error 1: Not Enough Ice Cream Balls\n");
    }
    return;
}

double max(double i,double j){//ritorna il valore massimo tra i e j
    if(i<=j){
        return j;
    }
    return i;
}

double min(double i,double j,char *index){//ritorna il valore massimo tra i e j e riempie index
    //if index==NULL ignore
    if(i<=j) {
        if (index != NULL){
            *index = 1;
        }
        return i;
    }
    else if(index!=NULL){
        *index=2;
    }
    return j;
}

double min3(double i,double j,double k){//ritorna il minimo tra i,j e k
    if(i<=j && i<=k){
        return i;
    }
    if(j<=k){
        return j;
    }
    return k;
}