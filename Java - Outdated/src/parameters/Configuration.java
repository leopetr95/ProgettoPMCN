package parameters;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class Configuration {
    
    public static long SEED;

    public static double p12;
    public static double p13;
    public static double p14;
    public static double p15;
    public static double p22;
    public static double p33;
    public static double p44;
    public static double p55;
    public static double p26;
    public static double p36;
    public static double p46;
    public static double p56;
    public static double p67;
    public static double p81;
    public static double p77;
    public static double p78;

    public static int M;   //Numero Centri
    public static int N;  //Numero Utenti
    public static int m;   //Numero di server per il centro 7

    public static double E_t_s_1;    //IS
    public static double E_t_s_2;   //FIFO
    public static double E_t_s_3;   //FIFO
    public static double E_t_s_4;   //FIFO
    public static double E_t_s_5;   //FIFO
    public static double E_t_s_6;   //FIFO
    /** FIFO servente multiplo, m = 3 */
    public static double E_t_s_7_1;    
    public static double E_t_s_7_2;
    public static double E_t_s_7_3;
    public static double E_t_s_8;   //FIFO

    public static double mu_1;  //Dubbio solamente perché è IS
    public static double mu_2;
    public static double mu_3;
    public static double mu_4;
    public static double mu_5;
    public static double mu_6;
    public static double mu_7;  /** Questo centro è multiserver con m = 3 */
    public static double mu_8;

    private static Configuration configuration = null;

    public static Configuration getInstance(){
        if(configuration == null){
            configuration = new Configuration();
            startConfiguration();
        }
        return configuration;
    }

    public static void startConfiguration() {
        String basePath = System.getProperty("user.dir");
        try (InputStream input = new FileInputStream(basePath + "/Param.properties")) {

            Properties prop = new Properties();
            // load a properties file
            prop.load(input);

            // get the property value and print it out
            SEED = Long.parseLong(prop.getProperty("seed"));

            p12 = Double.parseDouble(prop.getProperty("p12"));
            p13 = Double.parseDouble(prop.getProperty("p13"));
            p14 = Double.parseDouble(prop.getProperty("p14"));
            p15 = Double.parseDouble(prop.getProperty("p15"));

            p22 = Double.parseDouble(prop.getProperty("p22"));
            p33 = Double.parseDouble(prop.getProperty("p33"));
            p44 = Double.parseDouble(prop.getProperty("p44"));
            p55 = Double.parseDouble(prop.getProperty("p55"));

            p26 = Double.parseDouble(prop.getProperty("p26"));
            p36 = Double.parseDouble(prop.getProperty("p36"));
            p46 = Double.parseDouble(prop.getProperty("p46"));
            p56 = Double.parseDouble(prop.getProperty("p56"));

            p67 = Double.parseDouble(prop.getProperty("p67"));
            p81 = Double.parseDouble(prop.getProperty("p81"));

            p77 = Double.parseDouble(prop.getProperty("p77"));
            p78 = Double.parseDouble(prop.getProperty("p78"));

            M = Integer.parseInt(prop.getProperty("M"));
            N = Integer.parseInt(prop.getProperty("N"));
            m = Integer.parseInt(prop.getProperty("m"));

            E_t_s_1 = Double.parseDouble(prop.getProperty("E_t_s_1"));
            E_t_s_2 = Double.parseDouble(prop.getProperty("E_t_s_2"));
            E_t_s_3 = Double.parseDouble(prop.getProperty("E_t_s_3"));
            E_t_s_4 = Double.parseDouble(prop.getProperty("E_t_s_4"));
            E_t_s_5 = Double.parseDouble(prop.getProperty("E_t_s_5"));
            E_t_s_6 = Double.parseDouble(prop.getProperty("E_t_s_6"));
            E_t_s_7_1 = Double.parseDouble(prop.getProperty("E_t_s_7_1"));
            E_t_s_7_2 = Double.parseDouble(prop.getProperty("E_t_s_7_2"));
            E_t_s_7_3 = Double.parseDouble(prop.getProperty("E_t_s_7_3"));
            E_t_s_8 = Double.parseDouble(prop.getProperty("E_t_s_8"));


            mu_1 = 1/E_t_s_1;  //Dubbio solamente perché è IS
            mu_2 = 1/E_t_s_2;
            mu_3 = 1/E_t_s_3;
            mu_4 = 1/E_t_s_4;
            mu_5 = 1/E_t_s_5;
            mu_6 = 1/E_t_s_6;
            mu_7 = 1/(m*E_t_s_7_1);  /** Questo centro è multiserver con m = 3 */
            mu_8 = 1/E_t_s_8;

        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

}
