package android.text.method;

public interface KeyListener {
    int getInputType();
    boolean onKeyDown(Object view, Object text, int keyCode, Object event);
    boolean onKeyUp(Object view, Object text, int keyCode, Object event);
}
