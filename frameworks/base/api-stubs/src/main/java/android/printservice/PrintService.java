package android.printservice;

public abstract class PrintService {
    public abstract Object onCreatePrinterDiscoverySession();
    public abstract void onRequestCancelPrintJob(Object job);
    public abstract void onPrintJobQueued(Object job);
}
