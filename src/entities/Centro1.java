package entities;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.lang.module.Configuration;
import java.util.Properties;

import distribuzioni.Distribution;

public class Centro1 extends Server{
    
    private Distribution distr = new Distribution();
    static double E_t_s = parameters.Configuration.E_t_s_1;

    private static void importResources() {
        /**
         * Attraverso config.properties andiamo a caricare i valori delle stringhe.
         */
        String basePath = System.getProperty("user.dir");
        try (InputStream input = new FileInputStream(basePath + "/Param.properties")) {

            Properties prop = new Properties();
            // load a properties file
            prop.load(input);
            // qui carichiamo effettivamente i valori nelle varibaili.
            E_t_s = Double.parseDouble(prop.getProperty("gitDirPath")); 
        } catch (IOException e) {
            e.printStackTrace();
        }
    } 

    ///////////////
    private Centro1(){} //Costruttore vuoto
    ///////////////

    public void handleRequest(){
        //TODO Da completare.

    }


}
