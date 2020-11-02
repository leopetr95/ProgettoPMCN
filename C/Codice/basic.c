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

int dio(int i){

    return i;

}

double max(double i,double j){//ritorna il valore massimo tra i e j
    if(i<=j){
        return j;
    }
    return i;
}

double min(double i,double j){
    if(i<=j){
        return i;
    }
    return j;
}

double min_array_associated_job(double arr[], int len, char *type)
{
    //Ritorna il valore minimo ed assegna la tipologia di Job.
    
    double min = arr[0];
    *type = 1;

    for ( int i = 1; i < len; i++ ){
        if ( arr[i] < min ) {
            min = arr[i];
            *type = i+1;
        }
    }

    return min;
}

double min_array(double arr[], int len)
{
    double min = arr[0];

    for ( int i = 1; i < len; i++ ){
        if ( arr[i] < min ) {
            min = arr[i];
        }
    }

    return min;
}

double* min_element(double *start, double *end)
{
    if (start == end) return end;

    double *min = start++;
    for (; start != end; ++start)
        if (*start < *min) min = start;

    return min;
}

void check_state_variables_during_simulation(int N, struct state state){ //da modificare per aggiungere i controlli da eseguire durante la simulazione.
    if(0){ //inserire le condizioni esatte come il controllo delle palline di gelato.
        handle_error_with_exit("During Simulation Error 1: Not Enough Ice Cream Balls\n");
    }
    return;
}

void check_state_variables_after_simulation(struct state state){
    if(0){ //da modificare per aggiungere i controlli da eseguire dopo la simulazione
        handle_error_with_exit("After Simulation Error 1: Not Enough Ice Cream Balls\n");
    }
    return;
}