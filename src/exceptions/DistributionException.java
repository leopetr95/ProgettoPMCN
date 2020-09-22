package exceptions;

public class DistributionException extends RuntimeException{
    
    /**
     *
     */
    private static final long serialVersionUID = 1L;

    public DistributionException(String errorMessage, Throwable err) {
        super(errorMessage, err);
    }
}
