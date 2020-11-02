#include <stdio.h>
#include <stdlib.h>

double lambda1 = 4.0;//frequenza arrivi di tipo 1
double lambda2 = 6.25;//frequenza arrivi di tipo 2
double lambda_tot = 10.25;//frequenza arrivi totale
double u1_local = 0.45;//frequenza di servizio job di tipo 1 cloudlet
double u2_local = 0.27;//frequenza di servizio job di tipo 2 cloudlet
double u1_cloud = 0.25;//frequenza di servizio job di tipo 1 cloud
double u2_cloud = 0.22;//frequenza di servizio job di tipo 2 cloud

//soluzioni al sistema ottenuto dalla catena di markov per N=4
double p00 = 0.000020032119151546545737;
double p10 = 0.0001780632813470804065515;
double p20 = 0.0007913923615425795846732;
double p30 = 0.0023448662564224580286612;
double p40 = 0.0052108139031610178414694;
double p11 = 0.0041218352163676020035061;
double p21 = 0.0183192676283004533489158;
double p22 = 0.2120285605127367285754146;
double p31 = 0.0542793114912606025153061;
double p12 = 0.0477064261153657639294683;
double p13 = 0.3681051397790568204434281;
double p01 = 0.0004637064618413552253944;
double p02 = 0.0053669729379786484420652;
double p03 = 0.0414118282251438922998857;
double p04 = 0.2396517837103234508095235;

int main() {

    //percentuale di job di tipo 1
    double p1 = lambda1 / lambda_tot;

    //percentuale di job di tipo 2
    double p2 = lambda2 / lambda_tot;

    //percentuale di arrivi che vanno in cloud
    double p_direct_cloud = (p40 * (lambda1 + lambda2) + p31 * (lambda1 + lambda2) + p22 * (lambda1 + lambda2) +
                             p13 * (lambda1 + lambda2) +p04 * (lambda1 + lambda2)) / lambda_tot;

    //percentuale di arrivi che vanno in cloudlet
    double p_direct_local = 1 - p_direct_cloud;

    //flusso che entra nella cloudlet
    double lambda_local = lambda_tot * p_direct_local;

    //flusso che entra nel cloud
    double lambda_cloud = lambda_tot * p_direct_cloud;

    //utilizzazione
    double utilization = 1 - p00;

    //popolazione media cloudlet
    double E_n_local = 0 * p00 + 1 * p10 + 1 * p01 + 2 * p20 + 2 * p02 + 2 * p11 + 3 * p30 +
            3 * p21 + 3 * p12 + 3 * p03 + 4 * p40 + 4 * p31 + 4 * p22 + 4 * p13 + 4 * p04;

    double v_local = p_direct_local;//visite alla cloudlet
    double v_cloud = p_direct_cloud;//visite al cloud

    double sum_pi = p1 + p2;

    //statistiche tipo 1

    //flusso di job di tipo 1 che entrano nella cloudlet
    double lambda1_local = lambda1 * (p00 + p10 + p20 + p30 + p11 + p12 + p21 + p01 + p02 + p03);

    //flusso di job di tipo 1 che entrano nel cloud
    double lambda1_cloud = lambda1 * (p40 + p31 + p22 + p13 + p04);

    //percentuale di job di tipo 1 che entrano nella cloudlet rispetto al totale dei job nella cloudlet
    double p1_local = lambda1_local / lambda_local;

    //percentuale di job di tipo 1 che vanno nella cloudlet rispetto al totale dei job di tipo 1
    double p1_local_global = lambda1_local / lambda1;

    //percentuale di job di tipo 1 che vanno nel cloud rispetto al totale dei job di tipo 1
    double p1_cloud_global = lambda1_cloud / lambda1;

    //percentuale di job di tipo 1 che vanno nella cloudlet rispetto al totale dei job di tipo 1
    double p1_direct_local = p1_local_global;

    //percentuale di job di tipo 1 che vanno nel cloud rispetto al totale dei job di tipo 1
    double p1_direct_cloud = p1_cloud_global;

    //visite di tipo 1 nella cloudlet
    double v1_local = p1_local_global;

    //visite di tipo 1 nel cloud
    double v1_cloud = p1_cloud_global;

    //tempo medio job di tipo 1 nella cloudlet
    double E_s1_local = 1 / u1_local;

    //tempo medio job di tipo 1 nel cloud
    double E_s1_cloud = 1 / u1_cloud;

    //tempo medio di risposta  job di tipo 1 nella cloudlet
    double E_ts1_local = E_s1_local;

    //tempo medio di risposta job di tipo 1 nel cloud
    double E_ts1_cloud = E_s1_cloud;

    //tempo medio di risposta job di tipo 1
    double E_ts1 = v1_local * E_ts1_local + v1_cloud * E_ts1_cloud;

    //popolazione media di tipo 1
    double E_n1_cloud = lambda1_cloud * E_ts1_cloud;

    //popolazione media di tipo 1 cloudlet
    double E_n1_local = 1 * p10 + 2 * p20 + 3 * p30 + 4 * p40 + 1 * p11 + 1*p12 + 1*p13 + 2 * p21 + 2 * p22 + 3 * p31;

    //throughput della cloudlet di tipo 1
    double x0_local1 = u1_local * p10 + 2 * u1_local * p20 + 3 * u1_local * p30 + 4 * u1_local * p40 + u1_local * p11 +
                       2 * u1_local * p21 + 3 * u1_local * p31 + u1_local * p12 + 2 * u1_local * p22 + u1_local * p13;

    double x0_local1_little = E_n1_local * u1_local;

    double x0_cloud1_little = E_n1_cloud * u1_cloud;

    //popolazione media di tipo 1
    double E_n1 = E_n1_cloud + E_n1_local;

    //throughput del cloud di tipo 1
    double x0_cloud1 = E_n1_cloud * u1_cloud;

    //throughput di tipo 1 =En1*Ets1
    double x0_1 = x0_local1 + x0_cloud1;

    double x0_1_little = E_n1_local * u1_local + E_n1_cloud * u1_cloud;

    //statistiche tipo 2

    //flusso di tipo 2 che entra nella cloudlet
    double lambda2_local = lambda2 * (p00 + p01 + p02 + p03 + p11 + p12 + p21 + p10 + p20 + p30);

    //flusso di job di tipo 2 che entrano nel cloud
    double lambda2_cloud = lambda2 * (p40 + p31 + p22 + p13 + p04);

    //percentuale di job di tipo 2 che entrano nella cloudlet rispetto al totale dei job nella cloudlet
    double p2_local = lambda2_local / lambda_local;

    //percentuale di job di tipo 2 che vanno nella cloudlet rispetto al totale dei job di tipo 2
    double p2_local_global = lambda2_local / lambda2;

    //percentuale di job di tipo 2 che vanno nel cloud rispetto al totale dei job di tipo 2
    double p2_cloud_global = lambda2_cloud / lambda2;

    //percentuale di job di tipo 2 che vanno nella cloudlet rispetto al totale dei job di tipo 2
    double p2_direct_local = p2_local_global;

    //percentuale di job di tipo 2 che vanno nel cloud rispetto al totale dei job di tipo 2
    double p2_direct_cloud = p2_cloud_global;

    //visite di tipo 2 nella cloudlet
    double v2_local = p2_local_global;

    //visite di tipo 2 nel cloud
    double v2_cloud = p2_cloud_global;

    //tempo medio job di tipo 2 nella cloudlet
    double E_s2_local = 1 / u2_local;

    //tempo medio job di tipo 2 nel cloud
    double E_s2_cloud = 1 / u2_cloud;

    //tempo medio di risposta  job di tipo 2 nella cloudlet
    double E_ts2_local = E_s2_local;

    //tempo medio di risposta job di tipo 2 nel cloud
    double E_ts2_cloud = E_s2_cloud;

    //tempo medio di risposta job di tipo 2
    double E_ts2 = v2_local * E_ts2_local + v2_cloud * E_ts2_cloud;

    //popolazione media di tipo 2
    double E_n2_cloud = lambda2_cloud * E_ts2_cloud;

    //popolazione media di tipo 2 cloudlet
    double E_n2_local = 1 * p01 + 2 * p02 + 3 * p03 + 4 * p04 + 1 * p11 + 2 * p12 + 2 * p22 + 3 * p13;

    //throughput della cloudlet di tipo 2
    double x0_local2 = u2_local * p01 + 2 * u2_local * p02 + 3 * u2_local * p03 + 4 * u2_local * p04 + u2_local * p11 +
                       2 * u2_local * p12 + 3 * u2_local * p13 + u2_local * p21 + 2 * u2_local * p22 + u2_local * p31;

    double x0_local2_little = E_n2_local * u2_local;

    double x0_cloud2_little = E_n2_cloud * u2_cloud;

    //popolazione media di tipo 2
    double E_n2 = E_n2_cloud + E_n2_local;

    //throughput del cloud di tipo 2
    double x0_cloud2 = E_n2_cloud * u2_cloud;

    //throughput di tipo 2 =En2*Ets2
    double x0_2 = x0_local2 + x0_cloud2;

    double x0_2_little = E_n2_local * u2_local + E_n2_cloud * u2_cloud;

    //statistiche sistema

    //popolazione media del sistema
    double E_n = E_n2 + E_n1;

    //percentuale di job di tipo 1 che entrano nel cloud rispetto al totale dei job nel cloud
    double p1_cloud = lambda1_cloud / lambda_cloud;

    //percentuale di job di tipo 2 che entrano nel cloud rispetto al totale dei job nel cloud
    double p2_cloud = lambda2_cloud / lambda_cloud;

    double pcloud_sum = p1_cloud + p2_cloud;

    //tempo di risposta medio del cloud
    double E_ts_cloud = p1_cloud * E_s1_cloud + p2_cloud * E_s2_cloud;

    //tempo di risposta della cloudlet
    double E_ts_local = (p1_local * E_s1_local + p2_local * E_s2_local) / (p1_local + p2_local);

    //tempo di risposta globale
    double E_ts_global_system = E_ts_local * v_local + E_ts_cloud * v_cloud;

    //popolazione media del cloud
    double E_n_cloud = lambda_cloud * E_ts_cloud;

    //throughput del cloud
    double x0_cloud = x0_cloud1 + x0_cloud2;

    double x0_cloud_little = E_n1_cloud * u1_cloud + E_n2_cloud * u2_cloud;

    //throughput della cloudlet di tipo 2
    double x0_local = x0_local1 + x0_local2;

    double x0_local_little = E_n1_local * u1_local + E_n2_local * u2_local;

    //throughput del sistema
    double x0 = x0_1 + x0_2;

    double x0_little = E_n1_cloud * u1_cloud + E_n2_cloud * u2_cloud + E_n1_local * u1_local + E_n2_local * u2_local;

    //popolazione media del sistema
    double E_n_system = E_n_cloud + E_n_local;

    double E_n_little = E_ts_global_system * lambda_tot;

    printf("lambda1_local=%lf\n", lambda1_local);
    printf("lambda1_cloud=%lf\n", lambda1_cloud);
    printf("p1_local=%lf\n", p1_local);
    printf("p1_direct_local=%lf\n", p1_direct_local);
    printf("p1_local_global=%lf\n", p1_local_global);
    printf("p1_cloud=%lf\n", p1_cloud);
    printf("p1_direct_cloud=%lf\n", p1_direct_cloud);
    printf("p1_cloud_global=%lf\n", p1_cloud_global);
    printf("v1_local=%lf\n", v1_local);
    printf("v1_cloud=%lf\n", v1_cloud);
    printf("E_s1_local=%lf\n", E_s1_local);
    printf("E_s1_cloud=%lf\n", E_s1_cloud);
    printf("E_ts1_local=%lf\n", E_ts1_local);
    printf("E_ts1_cloud=%lf\n", E_ts1_cloud);
    printf("E_ts1=%lf\n", E_ts1);
    printf("E_n1_local=%lf\n", E_n1_local);
    printf("E_n1_cloud=%lf\n", E_n1_cloud);
    printf("x0_local1=%lf\n", x0_local1);
    printf("x0_local1_little=%lf\n", x0_local1_little);
    printf("x0_cloud1=%lf\n", x0_cloud1);
    printf("x0_cloud1_little=%lf\n", x0_cloud1_little);
    printf("x0_1=%lf\n", x0_1);
    printf("x0_1_little=%lf\n", x0_1_little);
    printf("E_n1=%lf\n", E_n1);

    printf("\n");

    printf("lambda2_local=%lf\n", lambda2_local);
    printf("lambda2_cloud=%lf\n", lambda2_cloud);
    printf("p2_local=%lf\n", p2_local);
    printf("p2_direct_local=%lf\n", p2_direct_local);
    printf("p2_local_global=%lf\n", p2_local_global);
    printf("p2_cloud=%lf\n", p2_cloud);
    printf("p2_direct_cloud=%lf\n", p2_direct_cloud);
    printf("p2_cloud_global=%lf\n", p2_cloud_global);
    printf("v2_local=%lf\n", v2_local);
    printf("v2_cloud=%lf\n", v2_cloud);
    printf("E_s2_local=%lf\n", E_s2_local);
    printf("E_s2_cloud=%lf\n", E_s2_cloud);
    printf("E_ts2_local=%lf\n", E_ts2_local);
    printf("E_ts2_cloud=%lf\n", E_ts2_cloud);
    printf("E_ts2=%lf\n", E_ts2);
    printf("E_n2_local=%lf\n", E_n2_local);
    printf("E_n2_cloud=%lf\n", E_n2_cloud);
    printf("x0_local2=%lf\n", x0_local2);
    printf("x0_local2_little=%lf\n", x0_local2_little);
    printf("x0_cloud2=%lf\n", x0_cloud2);
    printf("x0_cloud2_little=%lf\n", x0_cloud2_little);
    printf("x0_2=%lf\n", x0_2);
    printf("x0_2_little=%lf\n", x0_2_little);

    printf("E_n2=%lf\n", E_n2);

    printf("\n");
    printf("E_ts_local=%lf\n", E_ts_local);
    printf("E_ts_cloud=%lf\n", E_ts_cloud);
    printf("E_ts_global_system=%lf\n", E_ts_global_system);
    printf("E_n_local=%lf\n", E_n_local);
    printf("E_n_cloud=%lf\n", E_n_cloud);
    printf("E_n=%lf\n", E_n);
    printf("E_n_system=%lf\n", E_n_system);
    printf("E_n_little=%lf\n", E_n_little);
    printf("x0_local=%lf\n", x0_local);
    printf("x0_local_little=%lf\n", x0_local_little);
    printf("x0_cloud=%lf\n", x0_cloud);
    printf("x0_cloud_little=%lf\n", x0_cloud_little);
    printf("x0=%lf\n", x0);
    printf("x0_little=%lf\n", x0_little);
    printf("p_direct_local=%lf\n", p_direct_local);
    printf("p_direct_cloud=%lf\n", p_direct_cloud);
    printf("lambda_local=%lf\n", lambda_local);
    printf("lambda_cloud=%lf\n", lambda_cloud);
    printf("v_local=%lf\n", v_local);
    printf("v_cloud=%lf\n", v_cloud);
    printf("utilization=%lf\n", utilization);
    
    return 0;
}