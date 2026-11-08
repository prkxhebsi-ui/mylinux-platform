package android.service.autofill;

public abstract class AutofillService {
    public abstract void onFillRequest(
            Object request, Object cancellationSignal, Object callback);

    public abstract void onSaveRequest(
            Object request, Object callback);
}
