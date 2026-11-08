package android.app;

import android.content.Context;
import android.content.Intent;
import android.content.ComponentName;
import android.os.Bundle;
import android.view.View;
import android.view.Window;

public class Activity extends Context {
    public static final int RESULT_CANCELED = 0;
    public static final int RESULT_OK = -1;

    private Intent intent;
    private Bundle savedState;
    private int resultCode = RESULT_CANCELED;
    private Intent resultData;
    private boolean finished;

    protected void onCreate(Bundle state) {}
    protected void onStart() {}
    protected void onRestart() {}
    protected void onResume() {}
    protected void onPause() {}
    protected void onStop() {}
    protected void onDestroy() {}
    protected void onSaveInstanceState(Bundle state) {}
    protected void onRestoreInstanceState(Bundle state) {}
    protected void onNewIntent(Intent intent) {}
    protected void onActivityResult(int requestCode,
                                    int resultCode,
                                    Intent data) {}
    protected void onPostCreate(Bundle state) {}
    protected void onPostResume() {}
    protected void onUserLeaveHint() {}
    protected void onBackPressed() {
        finish();
    }

    public void setContentView(View view) {
        throw new UnsupportedOperationException("API stub");
    }

    public void setContentView(int layoutResource) {
        throw new UnsupportedOperationException("API stub");
    }

    public void addContentView(View view, Object params) {
        throw new UnsupportedOperationException("API stub");
    }

    public View findViewById(int id) {
        return null;
    }

    public void startActivity(Intent intent) {
        throw new UnsupportedOperationException("API stub");
    }

    public void startActivityForResult(Intent intent, int requestCode) {
        throw new UnsupportedOperationException("API stub");
    }

    public void finish() {
        finished = true;
    }

    public boolean isFinishing() {
        return finished;
    }

    public Intent getIntent() {
        return intent;
    }

    public void setIntent(Intent intent) {
        this.intent = intent;
    }

    public void setResult(int code) {
        resultCode = code;
        resultData = null;
    }

    public void setResult(int code, Intent data) {
        resultCode = code;
        resultData = data;
    }

    public int getResultCode() {
        return resultCode;
    }

    public Intent getResultData() {
        return resultData;
    }

    public Bundle getSavedInstanceState() {
        return savedState;
    }

    public ComponentName getComponentName() {
        return new ComponentName(this, getClass());
    }

    public Window getWindow() {
        return null;
    }

    public void runOnUiThread(Runnable action) {
        if (action != null) action.run();
    }

    @Override
    public Object getSystemService(String name) {
        throw new UnsupportedOperationException("API stub");
    }

    @Override
    public String getPackageName() {
        throw new UnsupportedOperationException("API stub");
    }

    @Override
    public java.io.File getFilesDir() {
        throw new UnsupportedOperationException("API stub");
    }

    @Override
    public java.io.File getCacheDir() {
        throw new UnsupportedOperationException("API stub");
    }
}
