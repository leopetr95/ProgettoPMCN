package parameters;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.Properties;

/**
 * Questa classe ha lo scopo di andare ad eseguire l'update dei 
 * parametri presenti all'interno del file Params.properties
 */

public class UpdateParameters {
    
    Properties prop = new Properties();
    String basePath = System.getProperty("user.dir");

    public static void main(String[] args) {
        
        UpdateParameters up = new UpdateParameters();
        
        //up.createParameters(); //Use if Param.properties not exist
        up.UpdateParameters();
    }

    private void createParameters(){
        /**
         * Il metodo serve a creare il file Params.properties se
         * se questo non dovesse esistere.
         */
        
        File file = new File(basePath +"/Param.properties");
        try{
            file.createNewFile();
        } catch (Exception e){
            e.printStackTrace();
        }
        
    }

    private void UpdateParameters(){
        /**
         * Il metodo serve ad eseguire un update del
         * file Params.properties.
         */
        try (OutputStream output = new FileOutputStream(basePath+"/Param.properties")) {
            //Specifico i valori da inserire all'interno del file.

            //SEED
            prop.setProperty("seed", "1234567890"); //Imposta il seed del sistema per il generatore di Lehmer

            /**
            * Paramtri di Routing del sistema:
            */
            prop.setProperty("p12", "0.25");
            prop.setProperty("p13", "0.25");
            prop.setProperty("p14", "0.25");
            prop.setProperty("p15", "0.25");

            prop.setProperty("p22", "0.15");
            prop.setProperty("p33", "0.15");
            prop.setProperty("p44", "0.15");
            prop.setProperty("p55", "0.15");

            prop.setProperty("p26", "0.85");
            prop.setProperty("p36", "0.85");
            prop.setProperty("p46", "0.85");
            prop.setProperty("p56", "0.85");

            prop.setProperty("p67", "1");
            prop.setProperty("p81", "1");

            prop.setProperty("p77", "0.85");
            prop.setProperty("p78", "0.85");

            /**
            * Numero di centri (ESPONENZIALI) ed Utenti nel sistema massimi:
            */

            prop.setProperty("M", "8");     
            prop.setProperty("N", "30");
            prop.setProperty("m", "3");     //Parametro multiserver

            /**
            * tempo di servizio medio per i centri E(t_s_i)
            * NB: Il tempo di servizio medio è espresso in secondi.
            */
            
            prop.setProperty("E_t_s_1", "12");
            prop.setProperty("E_t_s_2", "0.8");
            prop.setProperty("E_t_s_3", "0.8");
            prop.setProperty("E_t_s_4", "0.8");
            prop.setProperty("E_t_s_5", "0.8");
            prop.setProperty("E_t_s_6", "0.3");
            prop.setProperty("E_t_s_7_1", "1.5");
            prop.setProperty("E_t_s_7_2", "1.5");
            prop.setProperty("E_t_s_7_3", "1.5");
            prop.setProperty("E_t_s_8", "0.3");

            /**
            * Tasso medio di servizio per i centri. 
            * Il tasso è stato ricavato attraverso l'equazione
            * µ = 1/E(S)
            */
            prop.store(output, null); //Necessario per lo store delle informazioni
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
