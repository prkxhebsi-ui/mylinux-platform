package android.os;

public final class Message {
    public int what;
    public int arg1;
    public int arg2;
    public Object obj;

    public Bundle data;

    Handler target;
    Runnable callback;
    Message next;

    private boolean inUse;

    public Message() {
    }

    public static Message obtain() {
        return new Message();
    }

    public static Message obtain(Handler handler) {
        Message message = new Message();
        message.target = handler;
        return message;
    }

    public static Message obtain(Handler handler, int what) {
        Message message = obtain(handler);
        message.what = what;
        return message;
    }

    public static Message obtain(Handler handler, Runnable callback) {
        Message message = obtain(handler);
        message.callback = callback;
        return message;
    }

    public static Message obtain(
            Handler handler, int what, int arg1, int arg2, Object object) {
        Message message = obtain(handler, what);
        message.arg1 = arg1;
        message.arg2 = arg2;
        message.obj = object;
        return message;
    }

    public Handler getTarget() {
        return target;
    }

    public void setTarget(Handler handler) {
        target = handler;
    }

    public Runnable getCallback() {
        return callback;
    }

    public void setData(Bundle bundle) {
        data = bundle;
    }

    public Bundle getData() {
        if (data == null) data = new Bundle();
        return data;
    }

    public Bundle peekData() {
        return data;
    }

    public boolean isInUse() {
        return inUse;
    }

    void markInUse() {
        inUse = true;
    }

    void recycleUnchecked() {
        what = 0;
        arg1 = 0;
        arg2 = 0;
        obj = null;
        data = null;
        target = null;
        callback = null;
        next = null;
        inUse = false;
    }

    public void sendToTarget() {
        if (target == null) {
            throw new IllegalStateException("Message has no target");
        }
        target.sendMessage(this);
    }
}
