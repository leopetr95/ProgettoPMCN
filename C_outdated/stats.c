#include "stats.h"
#include "rvms.h"
#include "basic.h"
#include <math.h>
#include <stdlib.h>

void calculate_mean_and_deviation(double*array,int length,double*mean,double*deviation){//calcola media e deviazione standard con un solo ciclo for
    if(array==NULL || length<=0|| mean== NULL || deviation==NULL){
        handle_error_with_exit("error in calculate mean_and_deviation\n");
    }
    double m=0.0;
    double  res= 0.0;
    for(int i = 0; i <length; i++){
        m+=array[i];
        res = res + ((array[i])*(array[i]));

    }
    m=m/length;
    *mean=m;
    *deviation= res - length*m*m;
    return;

}

void calculate_and_print_interval(double* batch,char*string)
{
    double alpha = 0.05;
    double t,delta;//t=valore critico della student,delta=lunghezza intervallo/2

    double mean = 0.0, s = 0.0;
    if(string==NULL){
        handle_error_with_exit("error  in calculate and print interval");
    }
    t  = idfStudent(NUM_BATCH-1, 1-alpha/2);//calcolo del valore critico
    calculate_mean_and_deviation(batch,NUM_BATCH,&mean,&s);
    delta = (double) t*s/(sqrt(NUM_BATCH-1));//calcolo di delta
    printf("%s:\n",string);
    printf("%lf +/- %lf = (%lf, %lf)\n\n",mean,delta,mean-delta,mean+delta);//stampa intervallo
}

void print_confidence_interval(double*tr_batch,double* tr1_batch,double* tr2_batch,double* tr_cloudlet,double* tr_cloud,double* tr_cloudlet_type1,double* tr_cloudlet_type2,double* tr_cloud_type1,double* tr_cloud_type2,double*response_batch,double* response_batch_type1,double* response_batch_type2,double*resp_1_cloud,double*resp_2_cloud,double*resp_cloud
        ,double*resp_1_cloudlet,double*resp_2_cloudlet,double*resp_cloudlet,double*average_pop_cloud,double*average_pop_cloudlet) {

    printf("\nREQUEST A.3.1:\n\n");
    calculate_and_print_interval(response_batch,"Average system response time");

    calculate_and_print_interval(response_batch_type1,"Average system response time class 1");
    calculate_and_print_interval(response_batch_type2,"Average system response time class 2");

    calculate_and_print_interval(tr_batch,"Throughput global");
    calculate_and_print_interval(tr1_batch,"Throughput global class 1");
    calculate_and_print_interval(tr2_batch,"Throughput global class 2");

    printf("----------------------------------------------------------\n");
    printf("\nREQUEST A.3.2:\n\n");

    calculate_and_print_interval(tr_cloudlet,"Throughput cloudlet global");
    calculate_and_print_interval(tr_cloudlet_type1,"Throughput cloudlet class 1");
    calculate_and_print_interval(tr_cloudlet_type2,"Throughput cloudlet class 2");

    printf("----------------------------------------------------------\n");
    printf("\nREQUEST A.3.3\n\n");
    calculate_and_print_interval(tr_cloud,"Throughput cloud global");
    calculate_and_print_interval(tr_cloud_type1,"Throughput cloud class 1");
    calculate_and_print_interval(tr_cloud_type2,"Throughput cloud class 2");

    printf("----------------------------------------------------------\n");
    printf("\nREQUEST A.3.4\n\n");
    calculate_and_print_interval(resp_cloud,"Average system response time cloud");
    calculate_and_print_interval(resp_1_cloud,"Average system response time cloud class_1");
    calculate_and_print_interval(resp_2_cloud,"Average system response time cloud class_2");
    calculate_and_print_interval(resp_cloudlet,"Average system response time cloudlet");
    calculate_and_print_interval(resp_1_cloudlet,"Average system response time cloudlet class_1");
    calculate_and_print_interval(resp_2_cloudlet,"Average system response time cloudlet class_2");
    calculate_and_print_interval(average_pop_cloud,"Average population cloud");
    calculate_and_print_interval(average_pop_cloudlet,"Average population cloudlet");
}

void calculate_batch(double time_next,struct state state,struct area area,struct last_state*last_state,int*i,double*tr_batch,double* tr_cloudlet,double* tr_cloud,double* tr1_cloudlet_batch,double* tr2_cloudlet_batch,double* tr1_cloud_batch,double* tr2_cloud_batch,double* tr_type1_batch,double* tr_type2_batch,double*response_batch,double* response_type1_batch,double* response_type2_batch,double*resp_1_cloud,double*resp_2_cloud,double*resp_cloud
        ,double*resp_1_cloudlet,double*resp_2_cloudlet,double*resp_cloudlet,double*average_pop_cloud,double*average_pop_cloudlet){
    tr_batch[*i]=(state.num_task_completed-last_state->last_num_task_completed)/(time_next-last_state->last_obs);//batch[i] del throughput
    tr_type1_batch[*i] = (double) (state.num_task_type1 - last_state->last_num_type1_completed)/(time_next-last_state->last_obs);
    tr_type2_batch[*i] = (double) (state.num_task_type2 - last_state->last_num_type2_completed)/(time_next-last_state->last_obs);

    double complete_task_cloudlet_type1=state.num_task_type1_cloudlet;
    double complete_task_cloudlet_type2=state.num_task_type2_cloudlet;
    double complete_task_cloud_type1=state.num_task_type1_cloud;
    double complete_task_cloud_type2=state.num_task_type2_cloud;

    tr1_cloudlet_batch[*i] = (double) (complete_task_cloudlet_type1 - last_state->last_num_type1_cloudlet)/(time_next - last_state->last_obs);
    tr2_cloudlet_batch[*i] = (double) (complete_task_cloudlet_type2 - last_state->last_num_type2_cloudlet)/(time_next - last_state->last_obs);
    tr1_cloud_batch[*i] = (double) (complete_task_cloud_type1 - last_state->last_num_type1_cloud)/(time_next - last_state->last_obs);
    tr2_cloud_batch[*i] = (double) (complete_task_cloud_type2 - last_state->last_num_type2_cloud)/(time_next - last_state->last_obs);

    tr_cloudlet[*i] = (double) ((complete_task_cloudlet_type1 + complete_task_cloudlet_type2) - (last_state->last_num_type1_cloudlet + last_state->last_num_type2_cloudlet))/(time_next - last_state->last_obs);
    tr_cloud[*i] = (double) ((complete_task_cloud_type1 + complete_task_cloud_type2) - (last_state->last_num_type1_cloud + last_state->last_num_type2_cloud))/(time_next - last_state->last_obs);

    response_batch[*i] = (double) ((area.type1 + area.type2) - last_state->last_area)/(state.num_task_arrived - last_state->last_task_arrived);
    response_type1_batch[*i] = (double) ((area.type1 - last_state->last_area_type1)/(state.num_task_type1 - last_state->last_num_task1_arrived));
    response_type2_batch[*i] = (double) ((area.type2 - last_state->last_area_type2)/(state.num_task_type2 - last_state->last_num_task2_arrived));


    resp_1_cloud[*i] = (double) ((area.cloud_type1-last_state->last_area_cloud_type1)/(state.num_task_type1_cloud - last_state->last_num_task_type1_cloud));
    resp_2_cloud[*i] = (double) ((area.cloud_type2 - last_state->last_area_cloud_type2)/(state.num_task_type2_cloud - last_state->last_num_task_type2_cloud));
    resp_cloud[*i] = (double) (area.cloud - (last_state->last_area_cloud_type2 + last_state->last_area_cloud_type1))/((state.num_task_type2_cloud + state.num_task_type1_cloud)-(last_state->last_num_task_type1_cloud + last_state->last_num_task_type2_cloud));
    resp_1_cloudlet[*i] = (double) ((area.cloudlet_type1-last_state->last_area_cloudlet_type1)/(state.num_task_type1_cloudlet - last_state->last_num_task_type1_cloudlet));
    resp_2_cloudlet[*i] = (double) ((area.cloudlet_type2_v-last_state->last_area_cloudlet_type2)/((state.num_task_type2_cloudlet) - (last_state->last_num_task_type2_cloudlet)));
    resp_cloudlet[*i] = (double) ((area.cloudlet-last_state->old_area_cloudlet)/(state.num_task_cloudlet - (last_state->last_num_task_type1_cloudlet+last_state->last_num_task_type2_cloudlet)));
    average_pop_cloud[*i] = (double) ((area.cloud - last_state->old_area_cloud))/(time_next - last_state->last_obs);
    average_pop_cloudlet[*i] = (double) ((area.cloudlet - last_state->old_area_cloudlet))/(time_next - last_state->last_obs);

    last_state->last_num_type1_cloudlet = state.num_task_type1_cloudlet;
    last_state->last_num_type2_cloudlet = (state.num_task_type2_cloudlet);
    last_state->last_num_type1_cloud = state.num_task_type1_cloud;
    last_state->last_num_type2_cloud = (state.num_task_type2_cloud);
    last_state->old_area_cloud = area.cloud;
    last_state->old_area_cloudlet = area.cloudlet;
    last_state->last_area = area.type1 + area.type2;
    last_state->last_task_arrived = state.num_task_arrived;
    last_state->last_num_task1_arrived = state.num_task_type1;
    last_state->last_num_task2_arrived = state.num_task_type2;
    last_state->last_area_type1 = area.type1;
    last_state->last_area_type2 = area.type2;
    last_state->last_num_type1_completed = state.num_task_type1;
    last_state->last_num_type2_completed = state.num_task_type2;
    last_state->last_num_task_arrived = state.num_task_arrived;
    last_state->last_num_task_completed = state.num_task_completed;
    last_state->last_area_cloud_type1 = area.cloud_type1;
    last_state->last_area_cloud_type2 = area.cloud_type2;
    last_state->last_num_task_type1_cloud = state.num_task_type1_cloud;
    last_state->last_num_task_type2_cloud = state.num_task_type2_cloud;
    last_state->last_area_cloudlet_type1 = area.cloudlet_type1;
    last_state->last_area_cloudlet_type2 = area.cloudlet_type2_v;
    last_state->last_num_task_type1_cloudlet = state.num_task_type1_cloudlet;
    last_state->last_num_task_type2_cloudlet = state.num_task_type2_cloudlet;

    (*i)++;//aumento batch i;
    last_state->last_obs = time_next;
}
