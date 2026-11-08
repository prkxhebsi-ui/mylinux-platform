package android.appwidget;

public class AppWidgetProvider {
    public void onEnabled(Object context) {}
    public void onDisabled(Object context) {}
    public void onUpdate(Object context, Object manager, int[] ids) {}
    public void onDeleted(Object context, int[] ids) {}
}
