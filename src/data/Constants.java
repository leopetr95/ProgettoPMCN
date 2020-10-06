package data;

/**
 * Questa classe racchiude la speficica di tutte le costanti necessarie all'interno del progetto
 * NON USARE E' STATA RIMPIAZZATA DALLA CLASSE CONFIGURATION
 */

public class Constants {
    
    /**
     * Paramtri di Routing del sistema:
     */

    static double p12 = 0.25;
    static double p13 = 0.25;
    static double p14 = 0.25;
    static double p15 = 0.25;

    static double p22 = 0.15;
    static double p33 = 0.15;
    static double p44 = 0.15;
    static double p55 = 0.15;

    static double p26 = 0.85;
    static double p36 = 0.85;
    static double p46 = 0.85;
    static double p56 = 0.85;

    static double p67 = 1;
    static double p81 = 1;

    static double p77 = 0.85;
    static double p78 = 0.85;


    /**
     * Numero di centri (ESPONENZIALI) ed Utenti nel sistema massimi:
     */

    static int M = 8;   //Numero Centri
    static int N = 30;  //Numero Utenti

    static int m = 3;   //Numero di server per il centro 7

    /**
    * tempo di servizio medio per i centri E(t_s_i)
    * NB: Il tempo di servizio medio è espresso in secondi.
    */

    static double E_t_s_1 = 12;    //IS

    static double E_t_s_2 = 0.8;   //FIFO
    static double E_t_s_3 = 0.8;   //FIFO
    static double E_t_s_4 = 0.8;   //FIFO
    static double E_t_s_5 = 0.8;   //FIFO
    static double E_t_s_6 = 0.3;   //FIFO

    /** FIFO servente multiplo, m = 3 */
    static double E_t_s_7_1 = 1.5;    
    static double E_t_s_7_2 = 1.5;
    static double E_t_s_7_3 = 1.5;

    static double E_t_s_8 = 0.3;   //FIFO

     /**
      * Tasso medio di servizio per i centri. 
      * Il tasso è stato ricavato attraverso l'equazione
      * µ = 1/E(S)
      */

    static double mu_1 = 1/E_t_s_1;  //Dubbio solamente perché è IS

    static double mu_2 = 1/E_t_s_2;
    static double mu_3 = 1/E_t_s_3;
    static double mu_4 = 1/E_t_s_4;
    static double mu_5 = 1/E_t_s_5;
    
    static double mu_6 = 1/E_t_s_6;

    static double mu_7 = 1/(m*E_t_s_7_1);  /** Questo centro è multiserver con m = 3 */

    static double mu_8 = 1/E_t_s_8;

}
