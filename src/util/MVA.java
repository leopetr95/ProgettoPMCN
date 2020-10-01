package util;

import java.util.ArrayList;

/**
 * Questa classe è necessaria al calcolo del tempo medio di risposta del sistema 
 * ed altri elementi annessi, andando a sfruttare l'algoritmo MVA. 
 */

public class MVA {
    
    /** Dichiarazione delle variabili */
    private int N;                              /**Numero di utenti del sistema */
    private int M;                              /**Numero di centri nel sistema */
    private double meanUsers[];                 /**Numero medio di utenti nel sottocentro del sistema */
    private double responseTime[];              /**Tempo di risposta media per ogni sottocentro del sistema */
    private double llambda[];                   /**Tasso di arrivo del centro i al variare di n */
    private double meanServiceTime[];           /**Tempo medio di servizio per ogni centro */
    private double visitRatioForCenter[][];       /**Tasso di visita relativo per ogni centro */

    public double[] calculateMVA(){

        ArrayList<Double[]> returnArray = new ArrayList<Double[]>();                   /**Dichiarazione dell'array per il ritorno dei valori dell'algoritmo */
        ArrayList<Double> valueSum = new ArrayList<Double>();

        /**Fasi di inizializzazione: Imponiamo a 0 E(n_i(0)) */
        for(int i = 0; i <= M; i++){
            meanUsers[i] = 0;
        }
        /**Passo ricorsivo */
        for(int j = 1; j <= N; j++){
            for(int h = 1; h <= M; h++){
                responseTime[h] = meanServiceTime[h]*(1 + meanUsers[j - 1]);
            }
            /**Calcolo della sommatoria per Lambda */
            for(int c = 1; c<=M; c++){
                //valueSum[c] = (visitRatioForCenter[c][j] * responseTime[c]); //Da sistemare
            }

            for(int z = 1; z <= M; z++){
                llambda[z] = (j / valueSum.get(z)); /**Calcolo del valore per lambda */
                meanUsers[z] = llambda[z]*responseTime[z];
            }
        }

        /** Definizione dei valori di ritorno dell'algoritmo */
        //returnArray.add(0, llambda);

        return null;
    }

    
    

}
