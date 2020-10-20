#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "basic.h"
#include "distributions.h"
#include "next_event.h"
#include "parser.h"
#include "stats.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char *argv[]){

    argc = argc;
    argv = argv;

    int N=NUM_MAX_SERVER;
    double STOP=STOP_SIMULATION;
    int i=0;//indice di batch
    printf("----------------------------------------------------------\n");
    printf("START SIMULATION\n");
    printf("----------------------------------------------------------\n");
    PlantSeeds(123456789);
    struct state state;
    struct last_state last_state;
    struct area area;
    initialize_area(&area);
    initialize_state(&state);
    initialize_last_state(&last_state);

    double time_current = 0.0;//istante corrente
    double time_next = 0.0;//istante di prossimo evento
    double time_arrive = 0.0;//istante di arrivo del job nella cloudlet
    double time_lost_in_cloudlet = 0.0;

    char task_type_next_arrival = 0;//tipo di job del prossimo arrivo
    char task_type_next_cloudlet_termination = 0;//tipo di job del prossimo completamento in cloudlet
    char task_type_next_cloud_termination = 0;

    double next_arrival;//prossimo arrivo

    double next_arrival_type1 = get_arrival_cassa(0);//prossimo arrivo gelato 1 gusto
    double next_arrival_type2 = get_arrival_cassa(1);//prossimo arrivo gelato 2 gusti
    double next_arrival_type2 = get_arrival_cassa(2);//prossimo arrivo gelato 3 gusti

    double next_cloudlet_termination = INF;//prossimo completamento sulla cloudlet
    double next_cloud_termination = INF;//prossimo completamento sul cloud

    struct node *cloudlet_head = NULL;//testa della lista dinamica dei server nella cloudlet
    struct node *cloudlet_tail = NULL;//coda della lista dinamica dei server nella cloudlet

    struct node *cloud_head = NULL;//testa della lista dinamica dei server nel cloud
    struct node *cloud_tail = NULL;//coda della lista dinamica dei server nel cloud

    //alloca array per batch means
    double* response_batch=alloc_array_double(NUM_BATCH);
    double* response_type1_batch = alloc_array_double(NUM_BATCH);
    double* response_type2_batch = alloc_array_double(NUM_BATCH);
    double* tr_batch=alloc_array_double(NUM_BATCH);
    double* tr_type1_batch = alloc_array_double(NUM_BATCH);
    double* tr_type2_batch = alloc_array_double(NUM_BATCH);
    double* tr_cloudlet = alloc_array_double(NUM_BATCH);
    double* tr_cloud = alloc_array_double(NUM_BATCH) ;
    double* tr1_cloud_batch = alloc_array_double(NUM_BATCH);
    double* tr2_cloud_batch = alloc_array_double(NUM_BATCH);
    double* tr1_cloudlet_batch = alloc_array_double(NUM_BATCH);
    double* tr2_cloudlet_batch = alloc_array_double(NUM_BATCH);
    double* resp_1_cloud=alloc_array_double(NUM_BATCH);
    double* resp_2_cloud=alloc_array_double(NUM_BATCH);
    double* resp_cloud=alloc_array_double(NUM_BATCH);
    double* resp_1_cloudlet=alloc_array_double(NUM_BATCH);
    double* resp_2_cloudlet=alloc_array_double(NUM_BATCH);
    double* resp_cloudlet=alloc_array_double(NUM_BATCH);
    double* average_pop_cloud=alloc_array_double(NUM_BATCH);
    double* average_pop_cloudlet=alloc_array_double(NUM_BATCH);

    //double* 

    while (time_current < STOP || state.n1 > 0 || state.n2 > 0 || state.n1_cloud > 0 ||
           state.n2_cloud > 0) {//finquando non termina la simulazione o ci sono job nel sistema
        check_state_variables_during_simulation(N, state);
        //calcolo degli istanti dei prossimi eventi
        if (time_current > STOP) {//se la condizione di termine viene raggiunta allora non si generano più arrivi
            next_arrival = INF;
        } else {//il prossimo arrivo è il minimo tra gli arrivi dei job di classe 1 e quelli di classe 2
            next_arrival = min(next_arrival_type1, next_arrival_type2, &task_type_next_arrival);
        }
        next_cloudlet_termination = find_next_termination(cloudlet_head, &task_type_next_cloudlet_termination);//istante di prossimo completamento nella cloudlet
        next_cloud_termination = find_next_termination(cloud_head, &task_type_next_cloud_termination);//istante di prossimo completamento nel cloud
        time_next = min3(next_cloudlet_termination, next_arrival,
                         next_cloud_termination);//istante del prossimo evento
        update_area(state, &area, time_current, time_next);

        if(time_next-last_state.last_obs >= LENGTH_BATCH_TIME) {

            calculate_batch(time_next,state,area,&last_state,&i,tr_batch,tr_cloudlet,tr_cloud,tr1_cloudlet_batch,tr2_cloudlet_batch,tr1_cloud_batch,tr2_cloud_batch,tr_type1_batch,
                            tr_type2_batch,response_batch,response_type1_batch,response_type2_batch,resp_1_cloud,resp_2_cloud,resp_cloud
                    ,resp_1_cloudlet,resp_2_cloudlet,resp_cloudlet,average_pop_cloud,average_pop_cloudlet);
        }
        time_current = time_next;//rimposta tempo simulazione
        //gestione del prossimo evento,capire che tipo di evento è,gestirlo e generare nuovi eventi inerenti all'evento scatenante
        if (time_current == next_cloud_termination) {//task nel cloud terminato
            state.num_task_completed++;
            delete_head(&cloud_head, &time_arrive, &time_lost_in_cloudlet);//segna server come idle
            area.cloud_v += time_current - time_arrive;
            area.system_v += time_current - time_arrive;
            if (task_type_next_cloud_termination == TASK_TYPE1) {//task di tipo 1 terminato nel cloud
                state.n1_cloud--;
                area.type1_v += time_current - time_arrive;
                area.cloud_type1_v += (time_current - time_arrive);
            } else {//task di tipo 2 terminato nel cloud
                state.n2_cloud--;
                area.type2_v += time_current - time_arrive;
                area.cloud_type2_v += (time_current - time_arrive);
            }
            continue;
        }
        if (time_current == next_arrival) {//il prossimo evento è un arrivo
            if (task_type_next_arrival == TASK_TYPE1) {//handle arrival type 1
                next_arrival_type1 = get_arrival_cloudlet(TASK_TYPE1, 0);//genera un nuovo arrivo di tipo 1
                if (state.n1 + state.n2 == N) {//task type 1 sent on the cloud
                    update_state(TASK_TYPE1, DIRECT_CLOUD, &state);
                    assign_task_to_cloud(time_current, TASK_TYPE1, &cloud_head, &cloud_tail, NO_TIME_LOST);
                } else {//task type 1 accepted on the cloudnet
                    update_state(TASK_TYPE1, DIRECT_CLOUDLET, &state);
                    assign_task_to_cloudlet(time_current, TASK_TYPE1, &cloudlet_head,
                                            &cloudlet_tail);//alloca un nuovo server che gestirà il job di tipo 1 e impostare tempo di fine a time_current+get_service_type1
                }
            } else {//handle_arrival type2
                next_arrival_type2 = get_arrival_cloudlet(TASK_TYPE2, 0);
                if (state.n1 + state.n2 == N) {//task type 2 sent on the cloud
                    update_state(TASK_TYPE2, DIRECT_CLOUD, &state);
                    assign_task_to_cloud(time_current, TASK_TYPE2, &cloud_head, &cloud_tail, NO_TIME_LOST);

                } else {//task type 2 accepted on the cloudlet
                    update_state(TASK_TYPE2, DIRECT_CLOUDLET, &state);
                    assign_task_to_cloudlet(time_current, TASK_TYPE2, &cloudlet_head,
                                            &cloudlet_tail);//alloca un nuovo server che gestirà il job di tipo 2 e impostare il tempo di fine a time_current+get_service_type2
                }
            }
        } else if (time_current ==
                   next_cloudlet_termination) {//il prossimo evento è un completamento nella cloudlet
            state.num_task_completed++;
            delete_head(&cloudlet_head, &time_arrive, &time_lost_in_cloudlet);//segna server come idle
            area.cloudlet_v += time_current - time_arrive;
            area.system_v += time_current - time_arrive;
            if (task_type_next_cloudlet_termination == TASK_TYPE1) {//task type 1 terminated
                state.n1--;
                area.type1_v += time_current - time_arrive;
                area.cloudlet_type1_v += (time_current - time_arrive);
            } else if (task_type_next_cloudlet_termination == TASK_TYPE2) {//task type 2 terminated
                state.n2--;
                area.type2_v += time_current - time_arrive;
                area.cloudlet_type2_v += (time_current - time_arrive);
            } else {//task type 2 terminated
                handle_error_with_exit("error\n");
            }
        } else {
            handle_error_with_exit("error 3\n");
        }
        //ritorna al ciclo while scansionando nuovi eventi
    }
    check_state_variables_after_simulation(state);//verifica variabili di stato
    print_confidence_interval(tr_batch,tr_type1_batch,tr_type2_batch,tr_cloudlet,tr_cloud,tr1_cloudlet_batch,tr2_cloudlet_batch,tr1_cloud_batch,tr2_cloud_batch,response_batch,response_type1_batch,response_type2_batch,resp_1_cloud,resp_2_cloud,resp_cloud
            ,resp_1_cloudlet,resp_2_cloudlet,resp_cloudlet,average_pop_cloud,average_pop_cloudlet);
    free_all_memory(tr_batch,tr_type1_batch,tr_type2_batch,response_batch,response_type1_batch,response_type2_batch,resp_1_cloud,resp_2_cloud,resp_cloud
            ,resp_1_cloudlet,resp_2_cloudlet,resp_cloudlet,average_pop_cloud,average_pop_cloudlet);
    printf("----------------------------------------------------------\n");
    printf("END SIMULATION\n");
    printf("----------------------------------------------------------\n");

}