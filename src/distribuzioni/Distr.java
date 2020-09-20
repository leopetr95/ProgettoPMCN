package distribuzioni;

import java.lang.Math;
import util.Rngs;

/**
 * Questa classe modella le distribuzioni delle richieste che possono arrivare 
 * all'interno del sistema. Le definizioni sono situate all'interno del capitolo
 * 3 del libro di testo.
 */

public class Distr {
    
    Rngs rng = new Rngs();

    private double createExponential(double z) throws Exception{
        if(z <= 0){
            throw new Exception("Usage: z > 0");
        }
        return (-z * Math.log(1.0 - rng.random()));
    }

    private long geometric(double p) throws Exception{
        //0.0 < p < 1.0
        if(p < 0 || p > 1){
            throw new Exception("Usage: 0.0 < p < 1.0");
        }
        return ((long) (Math.log(1.0 - rng.random()) / Math.log(p)));
    }

    public static void main(String[] args) throws Exception {
        //System.out.println(new Distr().createExponential(0));
        //System.out.println(new Distr().geometric(12));
    }
}
