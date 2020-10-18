#include <limits.h>
#ifndef PROG_BASIC_H
#define PROG_BASIC_H
//
struct state{//variabili di stato
    int num_user_cassa;
    int num_user_verify;
    int num_user_multiserver;
    int num_user_delay;
    int num_user_lost;
    int num_user_total;

    int num_user_icecream_type1;
    int num_user_icecream_type2;
    int num_user_icecream_type3;

    int num_balls_icecream_type1;
    int num_balls_icecream_type2;
    int num_balls_icecream_type3;

    int num_task_arrived;

    int num_task_icecream1;
    int num_task_icecream2;
    int num_task_icecream3;

};
//??
struct last_state{
    int last_num_task_completed;
    int last_num_task_arrived;
    int last_num_task1_arrived;
    int last_num_task2_arrived;
    int last_num_type1_completed;
    int last_num_type2_completed;
    int last_area;
    int last_task_arrived;
    int last_num_type1_cloudlet;
    int last_num_type2_cloudlet;
    int last_num_type1_cloud;
    int last_num_type2_cloud;
    double last_area_cloud_type1;
    int last_num_task_type1_cloud;
    double last_area_cloud_type2;
    int last_num_task_type2_cloud;
    double last_area_cloudlet_type1;
    double last_area_cloudlet_type2;
    int last_num_task_type1_cloudlet;
    int last_num_task_type2_cloudlet;
    double old_area_cloud;
    double old_area_cloudlet;
    double last_area_type1;
    double last_area_type2;
    double last_obs;
};
struct area{ //tipi di aree (calcolo ottenuto non dall'integrale ma dalla forma esplicita)
    double system;
    double cassa;
    double verifica;
    double multiserver;
    double delay_server;
};

#define START 0.0 //istante inizio simulazione
#define STOP_SIMULATION  2000000 //istante fine simulazione
#define INF (STOP_SIMULATION*10)
#define NO_TIME_LOST 0.0
#define NUM_BATCH 64 //k=numero di batch
#define LENGTH_BATCH_TIME (STOP/NUM_BATCH)

#define NUM_MAX_SERVER 3//NUM_MAX_SERVER==N,numero massimo di server della cloudlet

//arrival rate and service rate
#define ARRIVALONE	4.0 //lambda1 1 gusto gelato        [task/s]
#define ARRIVALTWO  6.25 //lambda2 2 gusti gelato       [task/s]
#define ARRIVALTHREE 5.50 //lamdbda3 3 gusti gelato     [task/s]
#define SERVICEONE 0.25  //u1 1 gusto gelato            [task/s]
#define SERVICETWO 0.37  //u2 2 gusti gelato            [task/s]
#define SERVICETHREE 0.59  //u2 3 gusti gelato          [task/s]


//streams per arrivi e servizi
#define STREAM_ARR1 0
#define STREAM_ARR2 10
#define STREAM_ARR3 20

#define STREAM_SERV_CASSA1 30
#define STREAM_SERV_CASSA2 40
#define STREAM_SERV_CASSA3 50

#define STREAM_SERV_DELAY1 60
#define STREAM_SERV_DELAY2 70
#define STREAM_SERV_DELAY3 80

#define STREAM_SERV_MULTISERVER1 90
#define STREAM_SERV_MULTISERVER2 100
#define STREAM_SERV_MULTISERVER3 110

#define STREAM_SERV_VERIFY1 120
#define STREAM_SERV_VERIFY2 130
#define STREAM_SERV_VERIFY3 140

#define STREAM_SETUP 1500




//constants
#define TASK_TYPE1 1    //1 gusto gelato
#define TASK_TYPE2 2    //2 gusti gelato   
#define TASK_TYPE3 3    //3 gusti gelato

//valore massimo vaschetta di gelato
#define MAX_ICECREAM_TUB 30

//locazioni all'iterno della rete
#define DIRECT_CASSA 1          //task diretto alla cassa
#define DIRECT_VERIFY 2         //task diretto alla verifica dei gusti
#define DIRECT_MULTISERVER 3    //task diretto al multiserver
#define DIRECT_DELAY 4          //task diretto al server di Delay

#define SEED_DEFAULT 991102
#define ALPHA 0.05 //ALPHA= 0.05 NECESSARIO PER INTERVALLO DI CONFIDENZA 

void handle_error_with_exit(char*error_string);
long*alloc_array_long(int lenght);
int*alloc_array_int(int lenght);
int**alloc_array_pointer_to_int(int lenght);
int**alloc_matrix_int(int num_row,int num_col);
char*alloc_array_char(int lenght);
void swap_row_matrix(int**matrix,int num_row,int num_col,int row1,int row2);
double max(double i,double j);
double min(double i,double j,char*index);
int index_max_in_array(int *array,int lenght);
double min2(double i,double j, double k);
double min3(double i,double j, double k);
int index_min_in_array(int *array,int lenght);
double**alloc_array_pointer_to_double(int lenght);
double**alloc_matrix_double(int num_row,int num_col);
int**alloc_matrix_int(int num_row,int num_col);
void check_state_variables(int N, struct state state);
void check_state_variables_during_simulation(int N, struct state state);
void check_state_variables_after_simulation(struct state state);
double*alloc_array_double(int lenght);
void free_all_memory(double*tr_batch);
#endif