package distribuzioni;

import java.lang.Math;

import exceptions.DistributionException;
import util.Rngs;

/**
 * Questa classe modella le distribuzioni delle richieste che possono arrivare 
 * all'interno del sistema. Le definizioni sono situate all'interno del capitolo
 * 3 del libro di testo.
 * Il ritorno di ogni funzione rappresenta una Variabile Aleatoria con la distribuzione 
 * prestabilita dal metodo.
 */

public class Distribution {
    
    Rngs rng = new Rngs();

    public double exponential(double z) throws DistributionException{
        if(z <= 0){
            throw new DistributionException("Usage: z > 0", null);
        }
        return (-z * Math.log(1.0 - rng.random()));
    }

    public long geometric(double p) throws DistributionException{
        //0.0 < p < 1.0
        if(p < 0 || p > 1){
            throw new DistributionException("Usage: 0.0 < p < 1.0", null);
        }
        return ((long) (Math.log(1.0 - rng.random()) / Math.log(p)));
    }

    public double uniform(double a, double b) throws DistributionException{
        if (a < b){
            throw new DistributionException("Usage: a > b", null);
        }
        return (a + (b - a) * rng.random());
    }

    public double hyperexponential(double z) throws DistributionException{
        if (z <= 0){
            throw new DistributionException("Usage: ", null);
        }
        double p = 0.2;
        double P = rng.random();
        if (P <= 0){
            return exponential(2 * p * z);
        } else {
            return exponential(2 * (1 - p) * z);
        }
    }

    public static void main(String[] args) throws DistributionException {
        System.out.println(new Distribution().exponential(17));
        //System.out.println(new Distr().geometric(0.87364763));
        //System.out.println(new Distr().uniform(2, 3));
        //System.out.println(new Distr().hyperexponential(2));
    }
}
