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
            prop.setProperty("prova", "provissima");

            prop.store(output, null); //Necessario per lo store delle informazioni
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
