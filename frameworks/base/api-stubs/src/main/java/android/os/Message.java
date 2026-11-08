package android.os;

public final class Message {
    public int what;
    public int arg1;
    public int arg2;
    public Object obj;

    public Bundle data;
    public Handler target;
    public Runnable callback;

    public long when;

    public Message() {}

    public static Message obtain() {
        return new Message();
    }

    public static Message obtain(Message source) {
        Message message = new Message();
        if (source != null) {
            message.what = source.what;
            message.arg1 = source.arg1;
            message.arg2 = source.arg2;
            message.obj = source.obj;
            message.data = source.data;
            message.target = source.target;
            message.callback = source.callback;
            message.when = source.when;
        }
        return message;
    }

    public static Message obtain(Handler handler) {
        Message message = new Message();
        message.target = handler;
        return message;
    }

    public static Message obtain(Handler handler, Runnable callback) {
        Message message = obtain(handler);
        message.callback = callback;
        return message;
    }

    public static Message obtain(Handler handler, int what) {
        Message message = obtain(handler);
        message.what = what;
        return message;
    }

    public static Message obtain(Handler handler, int what,
                                 Object object) {
        Message message = obtain(handler, what);
        message.obj = object;
        return message;
    }

    public static Message obtain(Handler handler, int what,
                                 int arg1, int arg2) {
        Message message = obtain(handler, what);
        message.arg1 = arg1;
        message.arg2 = arg2;
        return message;
    }

    public static Message obtain(Handler handler, int what,
                                 int arg1, int arg2, Object object) {
        Message message = obtain(handler, what, arg1, arg2);
        message.obj = object;
        return message;
    }

    public void setData(Bundle data) {
        this.data = data;
    }

    public Bundle getData() {
        if (data == null) data = new Bundle();
        return data;
    }

    public Bundle peekData() {
        return data;
    }

    public void sendToTarget() {
        if (target != null) target.sendMessage(this);
    }

    public void recycle() {
        what = 0;
        arg1 = 0;
        arg2 = 0;
        obj = null;
        data = null;
        target = null;
        callback = null;
        when = 0;
    }

    public void copyFrom(Message source) {
        if (source == null) return;
        what = source.what;
        arg1 = source.arg1;
        arg2 = source.arg2;
        obj = source.obj;
        data = source.data;
        target = source.target;
        callback = source.callback;
        when = source.when;
    }
}
