#include <stdio.h>
#include <stdlib.h>
#include "basic.h"
#include "next_event.h"
#include "distributions.h"

void update_area(struct state state, struct area *area, double time_current,double time_next) {//funzione che aggiorna tutti i tipi di aree
    //area_tipo=(time_next-time_current)*popolazione_tipo
    if (area == NULL) {
        handle_error_with_exit("error in update area\n");
    }
    if (time_current > time_next) {
        handle_error_with_exit("error in update area1\n");
    }
    if (time_current < 0) {
        handle_error_with_exit("error in update area2\n");
    }
    if (time_next < 0) {
        handle_error_with_exit("error in update area3\n");
    }
    //da finire
    /*
    area->system += (time_next - time_current) * (state.n1 + state.n2 + state.n1_cloud + state.n2_cloud);
    area->cloudlet += (time_next - time_current) * (state.n1 + state.n2);
    area->cloud += (time_next - time_current) * (state.n1_cloud + state.n2_cloud);
    area->type1 += (time_next - time_current) * (state.n1 + state.n1_cloud);
    area->type2 += (time_next - time_current) * (state.n2 + state.n2_cloud);
    area->cloud_type1 += (time_next - time_current) * state.n1_cloud;
    area->cloud_type2 += (time_next - time_current) * state.n2_cloud;
    area->cloudlet_type1 += (time_next - time_current) * state.n1;
    area->cloudlet_type2 += (time_next - time_current) * (state.n2);
    */
    return;
}

void update_state(char task_type, char location, struct state *state) {//aggiorna le variabili del sistema quando c'è un arrivo di tipo 1, di tipo 2 o di tipo 3
    if (state == NULL) {
        handle_error_with_exit("error in update state\n");
    }
    if (task_type != TASK_TYPE1 && task_type != TASK_TYPE2 && task_type != TASK_TYPE3) {
        handle_error_with_exit("error in update state task_type\n");
    }
    if (location != DIRECT_CASSA && location != DIRECT_DELAY && location != DIRECT_MULTISERVER && location != DIRECT_VERIFY) {
        handle_error_with_exit("error in update state location\n");
    }
    
    state->num_task_arrived++;
    if (task_type == TASK_TYPE1) {//task 1 gusto gelato.
        state->num_task_icecream1++;
        if(location == DIRECT_CASSA) { //arrivo task gelato 1 gusto verso cassa
            state->num_user_cassa++;
            state->num_user_total++;
        } else if(location == DIRECT_VERIFY) {//task type 1 e diretto sul  cloud(non interrotto)
            state->num_user_verify++;
            state->num_balls_icecream_type1--;
        } else if(location == DIRECT_MULTISERVER){ //arrivo task gelato 1 gusto verso multiserver
            state->num_user_multiserver++;
            state->num_user_icecream_type1++;
        } else if(location == DIRECT_DELAY){
            state->num_user_delay++;
            state->num_balls_icecream_type1 = MAX_ICECREAM_TUB;
        } else {//task type 1 e non diretto sul cloud(non interrotto)
            handle_error_with_exit("error\n");
        }
    }else if(task_type == TASK_TYPE2){ //task 2 gusti gelato.
        state->num_task_icecream2++;
        if(location == DIRECT_CASSA) { //arrivo task gelato 1 gusto verso cassa
            state->num_user_cassa++;
            state->num_user_total++;
        } else if(location == DIRECT_VERIFY) {//task type 1 e diretto sul  cloud(non interrotto)
            state->num_user_verify++;
            state->num_balls_icecream_type2--;
        } else if(location == DIRECT_MULTISERVER){ //arrivo task gelato 1 gusto verso multiserver
            state->num_user_multiserver++;
            state->num_user_icecream_type2++;
        } else if(location == DIRECT_DELAY){
            state->num_user_delay++;
            state->num_balls_icecream_type2 = MAX_ICECREAM_TUB;
        } else {//task type 1 e non diretto sul cloud(non interrotto)
            handle_error_with_exit("error\n");
        }
    } else { //task 3 gusti gelato.
        state->num_task_icecream3++;
        if(location == DIRECT_CASSA) { //arrivo task gelato 1 gusto verso cassa
            state->num_user_cassa++;
            state->num_user_total++;
        } else if(location == DIRECT_VERIFY) {//task type 1 e diretto sul  cloud(non interrotto)
            state->num_user_verify++;
            state->num_balls_icecream_type3--;
        } else if(location == DIRECT_MULTISERVER){ //arrivo task gelato 1 gusto verso multiserver
            state->num_user_multiserver++;
            state->num_user_icecream_type3++;
        } else if(location == DIRECT_DELAY){
            state->num_user_delay++;
            state->num_balls_icecream_type3 = MAX_ICECREAM_TUB;
        } else {//task type 1 e non diretto sul cloud(non interrotto)
            handle_error_with_exit("error\n");
        }
    }
    
    return;
}

void initialize_state(struct state *state) {//inizializza la struct state
    if (state == NULL) {
        handle_error_with_exit("error in initialize state\n");
    }
    memset(state, 0, sizeof(struct state));
}

void initialize_last_state(struct last_state *last_state) {//inizializza la struct state
    if (last_state == NULL) {
        handle_error_with_exit("error in initialize last_state\n");
    }
    memset(last_state, 0, sizeof(struct last_state));
}

void initialize_area(struct area *area) {//inizializza la struct area
    if (area == NULL) {
        handle_error_with_exit("error in initialize area\n");
    }
    memset(area, 0, sizeof(struct area));
}

double get_time_service_cassa(char task_type){
    /**
     * Il metodo va a determinare qunato impiega un task per essere completato
     * nella cassa.
     */
    double service;
    if (task_type != TASK_TYPE1 && task_type != TASK_TYPE2 && task_type != TASK_TYPE3) {
        handle_error_with_exit("error in get_time_service_cassa\n");
    }
    if (task_type == TASK_TYPE1) {//il job è di tipo 1
        SelectStream(STREAM_SERV_CASSA1);//selezionare stream servizio1 
        service = Exponential(1 / SERVICEONE);//genera servizio
        //service=Exponential(1/SERVICEONE);
    } else if(task_type == TASK_TYPE2) {//il job è di tipo 2
        SelectStream(STREAM_SERV_CASSA2);//seleziona stream servizio2 
        service = Exponential(1 / SERVICETWO);//genera servizio
        //service=Exponential(1/SERVICETWO);
    } else {
        SelectStream(STREAM_SERV_CASSA3);//seleziona stream servizio3 
        service = Exponential(1 / SERVICETHREE);//genera servizio
    }

    return service;

}

double get_time_service_verify(char task_type){
    /**
     * Il metodo va a determinare qunato impiega un task per essere completato
     * nella verifica.
     */
    double service;
    if (task_type != TASK_TYPE1 && task_type != TASK_TYPE2 && task_type != TASK_TYPE3) {
        handle_error_with_exit("error in get_time_service_verify\n");
    }
    if (task_type == TASK_TYPE1) {//il job è di tipo 1
        SelectStream(STREAM_SERV_VERIFY1);//selezionare stream servizio1 
        service = Exponential(1 / SERVICEONE);//genera servizio
        //service=Exponential(1/SERVICEONE);
    } else if(task_type == TASK_TYPE2) {//il job è di tipo 2
        SelectStream(STREAM_SERV_VERIFY2);//seleziona stream servizio2 
        service = Exponential(1 / SERVICETWO);//genera servizio
        //service=Exponential(1/SERVICETWO);
    } else {
        SelectStream(STREAM_SERV_VERIFY3);//seleziona stream servizio3
        service = Exponential(1 / SERVICETHREE);//genera servizio
    }

    return service;

}

double get_time_service_multiserver(char task_type){
    /**
     * Il metodo va a determinare qunato impiega un task per essere completato
     * nel multiserver.
     */
    double service;
    if (task_type != TASK_TYPE1 && task_type != TASK_TYPE2 && task_type != TASK_TYPE3) {
        handle_error_with_exit("error in get_time_service_multiserver\n");
    }
    if (task_type == TASK_TYPE1) {//il job è di tipo 1
        SelectStream(STREAM_SERV_MULTISERVER1);//selezionare stream servizio1 
        service = Exponential(1 / SERVICEONE);//genera servizio
        //service=Exponential(1/SERVICEONE);
    } else if(task_type == TASK_TYPE2) {//il job è di tipo 2
        SelectStream(STREAM_SERV_MULTISERVER2);//seleziona stream servizio2 
        service = Exponential(1 / SERVICETWO);//genera servizio
        //service=Exponential(1/SERVICETWO);
    } else {
        SelectStream(STREAM_SERV_MULTISERVER3);//seleziona stream servizio3
        service = Exponential(1 / SERVICETHREE);//genera servizio
    }

    return service;

}

double get_time_service_delay(char task_type){
    /**
     * Il metodo va a determinare qunato impiega un task per essere completato
     * nel server Delay.
     */
    double service;
    if (task_type != TASK_TYPE1 && task_type != TASK_TYPE2 && task_type != TASK_TYPE3) {
        handle_error_with_exit("error in get_time_service_delay\n");
    }
    if (task_type == TASK_TYPE1) {//il job è di tipo 1
        SelectStream(STREAM_SERV_DELAY1);//selezionare stream servizio1 
        service = Exponential(1 / SERVICEONE);//genera servizio
        //service=Exponential(1/SERVICEONE);
    } else if(task_type == TASK_TYPE2) {//il job è di tipo 2
        SelectStream(STREAM_SERV_DELAY2);//seleziona stream servizio2 
        service = Exponential(1 / SERVICETWO);//genera servizio
        //service=Exponential(1/SERVICETWO);
    } else {
        SelectStream(STREAM_SERV_DELAY3);//seleziona stream servizio3 
        service = Exponential(1 / SERVICETHREE);//genera servizio
    }

    return service;

}

double assign_task_to_cassa(double time_current,char task_type,struct node**head,struct node**tail){
    /**
     * Il metodo va ad assegnare un task alla cassa andando ad allocare uno spoazio all'interno della
     * lista dinamica della cassa, andando ad impostare il tempo di completamento di quel task.
     */
    double time_end_service = time_current + get_time_service_cassa(task_type);
    insert_ordered(time_end_service, task_type, time_current, 0, head, tail);
    return;
}

double assign_task_to_verify(double time_current,char task_type,struct node**head,struct node**tail){
    /**
     * Il metodo va ad assegnare un task alla cassa andando ad allocare uno spoazio all'interno della
     * lista dinamica della cassa, andando ad impostare il tempo di completamento di quel task.
     */
    double time_end_service = time_current + get_time_service_verify(task_type);
    insert_ordered(time_end_service, task_type, time_current, 0, head, tail);
    return;
}

double assign_task_to_multiserver(double time_current,char task_type,struct node**head,struct node**tail){
    /**
     * Il metodo va ad assegnare un task alla cassa andando ad allocare uno spoazio all'interno della
     * lista dinamica della cassa, andando ad impostare il tempo di completamento di quel task.
     */
    double time_end_service = time_current + get_time_service_multiserver(task_type);
    insert_ordered(time_end_service, task_type, time_current, 0, head, tail);
    return;
}

double assign_task_to_delay(double time_current,char task_type,struct node**head,struct node**tail){
    /**
     * Il metodo va ad assegnare un task alla cassa andando ad allocare uno spoazio all'interno della
     * lista dinamica della cassa, andando ad impostare il tempo di completamento di quel task.
     */
    double time_end_service = time_current + get_time_service_delay(task_type);
    insert_ordered(time_end_service, task_type, time_current, 0, head, tail);
    return;
}

double get_arrival_cassa(char task_type){
     if (task_type != TASK_TYPE1 && task_type != TASK_TYPE2 && task_type != TASK_TYPE3) {
        handle_error_with_exit("error in get_arrival\n");
    }
    const double mean[3] = {1 / ARRIVALONE, 1 / ARRIVALTWO, 1/ARRIVALTHREE};//mean exp=1/freq
    static double arrivals[3] = {START, START, START};
    static int init = 0;
    double arrival;
    if (init < 3) {//inizializza le tre diverse tipologie di arrivo,blocco di codice eseguito solo tre volte
        if (init == 0) {
            SelectStream(STREAM_ARR1);
            arrivals[0] += Exponential(mean[0]);
            init++;
            return arrivals[0];
        }
        if (init == 1) {
            SelectStream(STREAM_ARR2);
            arrivals[1] += Exponential(mean[1]);
            init++;
            return arrivals[1];
        }
        if(init == 2){
            SelectStream(STREAM_ARR2);
            arrivals[1] += Exponential(mean[2]);
            init++;
            return arrivals[2];
        }
    }
    if (task_type == TASK_TYPE1) {//arrivo di tipo 1
        SelectStream(STREAM_ARR1);
        arrivals[0] += Exponential(mean[0]);
        arrival = arrivals[0];
    } else if(task_type == TASK_TYPE2) { //Arrivo di tipo 3
        SelectStream(STREAM_ARR2);
        arrivals[1] += Exponential(mean[1]);
        arrival = arrivals[1];
    }
    else {//arrivo di tipo 3
        SelectStream(STREAM_ARR3);
        arrivals[2] += Exponential(mean[2]);
        arrival = arrivals[2];
    }
    return arrival;
}

/*
double get_arrival_cloudlet(char task_type, char new_replication) {//genera un arrivo di tipo 1 o di tipo 2
    if (task_type != 1 && task_type != 2) {
        handle_error_with_exit("error in get_arrival\n");
    }
    const double mean[2] = {1 / ARRIVALONE, 1 / ARRIVALTWO};//mean exp=1/freq
    static double arrivals[2] = {START, START};
    static int init = 0;
    if (new_replication == 1) {
        init = 0;
        arrivals[0] = START;
        arrivals[1] = START;
    }
    double arrival;
    if (init < 2) {//inizializza i 2 tipi di arrivo,blocco di codice eseguito solo due volte
        if (init == 0) {
            SelectStream(STREAM_ARR1);
            arrivals[0] += Exponential(mean[0]);
            init++;
            return arrivals[0];
        }
        if (init == 1) {
            SelectStream(STREAM_ARR2);
            arrivals[1] += Exponential(mean[1]);
            init++;
            return arrivals[1];
        }
    }
    if (task_type == 1) {//arrivo di tipo 1
        SelectStream(STREAM_ARR1);
        arrivals[0] += Exponential(mean[0]);
        arrival = arrivals[0];
    } else {//arrivo di tipo 2
        SelectStream(STREAM_ARR2);
        arrivals[1] += Exponential(mean[1]);
        arrival = arrivals[1];
    }
    return arrival;
}

double
get_time_service_cloudlet(char task_type) {//ritorna il tempo di servizio del job del tipo specificato nella cloudlet
    double service;
    if (task_type != TASK_TYPE1 && task_type != TASK_TYPE2) {
        handle_error_with_exit("error in get_time_service_cloudlet\n");
    }
    if (task_type == TASK_TYPE1) {//il job è di tipo 1
        SelectStream(STREAM_SERV_CLOUDLET1);//selezionare stream servizio1 cloudlet
        service = Hyperexponential(1 / SERVICEONE);//genera servizio
        //service=Exponential(1/SERVICEONE);
    } else {//il job è di tipo 2
        SelectStream(STREAM_SERV_CLOUDLET2);//seleziona stream servizio2 cloudlet
        service = Hyperexponential(1 / SERVICETWO);//genera servizio
        //service=Exponential(1/SERVICETWO);
    }

    return service;
}

double get_time_service_cloud(char task_type) {//ritorna il tempo di servizio del job del tipo specificato nel cloud
    double service_cloud;
    if (task_type != TASK_TYPE1 && task_type != TASK_TYPE2) {
        handle_error_with_exit("error in get_time_service_cloudlet\n");
    }
    if (task_type == TASK_TYPE1) {//il job è di tipo 1

        SelectStream(STREAM_SERV_CLOUD1);
        service_cloud = Exponential(1 / SERVICE_CLOUD_ONE);
    } else {//job di tipo 2

        SelectStream(STREAM_SERV_CLOUD2);
        service_cloud = Exponential(1 / SERVICE_CLOUD_TWO);//genera tempo di servizio senza aggiungere il tempo di setup

    }
    return service_cloud;
}

void assign_task_to_cloudlet(double time_current, char task_type, struct node **head,
                             struct node **tail) {//assegna un task alla cloudlet,quindi alloca un server nella lista dinamica
    //della cloudlet e imposta il tempo di completamento di quel task
    double time_end_service = time_current + get_time_service_cloudlet(task_type);
    insert_ordered(time_end_service, task_type, time_current, NO_TIME_LOST, head, tail);
    return;
}

void assign_task_to_cloud(double time_current, char task_type, struct node **head, struct node **tail,
                          double time_lost_in_cloudlet) {//assegna un task al cloud,quindi alloca un server nella lista dinamica
    //del cloud e imposta il tempo di completamento di quel task
    double time_end_service = time_current + get_time_service_cloud(task_type);
    insert_ordered(time_end_service, task_type, time_current, time_lost_in_cloudlet, head, tail);
    return;
}
*/

double
find_next_termination(struct node *head, char *task_type_termination) {//ritorna INF se la lista dinamica è vuota,
// altrimenti ritorna l'istante di completamento della testa della lista,ossia l'istante del prossimo completamento
    double end_service;
    if (head == NULL) {
        return INF;
    }
    if (task_type_termination == NULL) {
        handle_error_with_exit("error in fin_next_termination\n");
    }
    end_service = get_instant_end_service_from_linked_list(head, task_type_termination);
    return end_service;
}