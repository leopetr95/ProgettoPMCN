#include <stdio.h>
#include <stdlib.h>
#include "basic.h"
#include "dynamic_list.h"
#include <string.h>

void print_state(int n1,int n2,int n1_cloud,int n2_cloud,int N,int S);
double find_next_termination(struct node*head,char*task_type_termination);
////////////////////////////
void assign_task_to_cloudlet(double time_current,char task_type,struct node**head,struct node**tail);
void assign_task_to_cloud(double time_current,char task_type,struct node**head,struct node**tail,double time_lost_in_cloudlet);
////////////////////////////
double get_arrival_cloudlet(char task_type,char new_replication);
double get_time_service_cloudlet(char task_type);
double get_time_service_cloud(char task_type);
double get_time_setup();
////////////////////////////


double get_arrival_cassa();

double get_time_service_cassa(char task_type);
double get_time_service_verify(char task_type);
double get_time_service_multiserver(char task_type);
double get_time_service_delay(char task_type);

double assign_task_to_cassa(double time_current,char task_type,struct node**head,struct node**tail);
double assign_task_to_verify(double time_current,char task_type,struct node**head,struct node**tail);
double assign_task_to_multiserver(double time_current,char task_type,struct node**head,struct node**tail);
double assign_task_to_delay(double time_current,char task_type,struct node**head,struct node**tail);


void initialize_state(struct state*state);
void initialize_last_state(struct last_state*last_state);
void initialize_area(struct area*area);
void update_state(char task_type,char location,struct state*state);
void update_area(struct state state,struct area*area,double time_current,double time_next);