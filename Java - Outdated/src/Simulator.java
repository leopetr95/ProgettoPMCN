import java.io.*;
import java.util.Properties;


/**
 * Questa classe ha lo scopo di eseguire la simulazione
 * del sistema, andando successivamente a salvare 
 * i dati all'interno di un file .csv in modo da poterli
 * comporare successivamente con i valori teorici ricavati 
 * tramite gli algoritmi di risoluzione della rete.
 */

public class Simulator {
    

    private static void importResources() {
        /**
         * Attraverso config.properties andiamo a caricare i valori delle stringhe.
         */
        String basePath = System.getProperty("user.dir");
        try (InputStream input = new FileInputStream(basePath+"/Param.properties")) {

            Properties prop = new Properties();
            // load a properties file
            prop.load(input);

            //path = prop.getProperty("gitDirPath"); //qui carichiamo effettivamente i valori nelle varibaili.

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        importResources();

    }
}
