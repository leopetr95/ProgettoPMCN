package distribuzioni;

import java.lang.Math;

import exceptions.DistributionException;
import util.Rngs;

/**
 * Questa classe modella le distribuzioni delle richieste che possono arrivare 
 * all'interno del sistema. Le definizioni sono situate all'interno del capitolo
 * 3 del libro di testo.
 */

public class Distr {
    
    Rngs rng = new Rngs();

    private double exponential(double z) throws DistributionException{
        if(z <= 0){
            throw new DistributionException("Usage: z > 0", null);
        }
        return (-z * Math.log(1.0 - rng.random()));
    }

    private long geometric(double p) throws DistributionException{
        //0.0 < p < 1.0
        if(p < 0 || p > 1){
            throw new DistributionException("Usage: 0.0 < p < 1.0", null);
        }
        return ((long) (Math.log(1.0 - rng.random()) / Math.log(p)));
    }

    private double uniform(double a, double b) throws DistributionException{
        if (a < b){
            throw new DistributionException("Usage: a > b", null);
        }
        return (a + (b - a) * rng.random());
    }

    private double hyperexponential(double z) throws DistributionException{
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
        //System.out.println(new Distr().createExponential(0));
        //System.out.println(new Distr().geometric(12));
        //System.out.println(new Distr().uniform(2, 3));
        //System.out.println(new Distr().hyperexponential(2));
    }
}
