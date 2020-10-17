package entities;

public class Server{
    /**
     * Questa classe serve a genereare l'oggetto generico Server che verrà successivamente 
     * implementato per essere specializzato a seconda del tipo di server che stiamo 
     * considerando.
     */

    //Variabili del server:
    private double E_t_s = 0;

    
    //Numero Job all'interno dei centri.
    public int number_job_centro1 = 0;

    public int number_job_centro2 = 0;
    public int number_job_centro3 = 0;
    public int number_job_centro4 = 0;
    public int number_job_centro5 = 0;

    public int number_job_centro6 = 0;

    public int number_job_centro7 = 0;          //Multiserver m=3

    public int number_job_centro8 = 0;

    //Numero Job completati
    public int number_completed_job_centro1 = 0;
    public int number_completed_job_centro2 = 0;
    public int number_completed_job_centro3 = 0;
    public int number_completed_job_centro4 = 0;
    public int number_completed_job_centro5 = 0;
    public int number_completed_job_centro6 = 0;
    public int number_completed_job_centro7 = 0;
    public int number_completed_job_centro8 = 0;


    public int getAllCompletedJob(){
        return (number_completed_job_centro1 + number_completed_job_centro2 + number_completed_job_centro3 + number_completed_job_centro4 + number_completed_job_centro5 + number_completed_job_centro6 + number_completed_job_centro7 + number_completed_job_centro8);
    }
}