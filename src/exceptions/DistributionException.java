package exceptions;

public class DistributionException extends RuntimeException{
    
    public DistributionException(String errorMessage, Throwable err) {
        super(errorMessage, err);
    }
}
