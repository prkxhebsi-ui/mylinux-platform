package android.content;

import android.net.Uri;
import android.os.Bundle;

import java.util.HashSet;
import java.util.Set;

public class Intent {
    public static final String ACTION_MAIN = "android.intent.action.MAIN";
    public static final String ACTION_VIEW = "android.intent.action.VIEW";
    public static final String ACTION_SEND = "android.intent.action.SEND";
    public static final String ACTION_EDIT = "android.intent.action.EDIT";
    public static final String ACTION_RUN = "android.intent.action.RUN";

    public static final String CATEGORY_DEFAULT =
            "android.intent.category.DEFAULT";
    public static final String CATEGORY_LAUNCHER =
            "android.intent.category.LAUNCHER";
    public static final String CATEGORY_HOME =
            "android.intent.category.HOME";

    public static final int FLAG_ACTIVITY_NEW_TASK = 0x10000000;
    public static final int FLAG_ACTIVITY_CLEAR_TOP = 0x04000000;
    public static final int FLAG_ACTIVITY_SINGLE_TOP = 0x20000000;
    public static final int FLAG_ACTIVITY_CLEAR_TASK = 0x00008000;
    public static final int FLAG_ACTIVITY_NO_HISTORY = 0x40000000;

    private String action;
    private String packageName;
    private String type;
    private Uri data;
    private ComponentName component;
    private Bundle extras = new Bundle();
    private final Set<String> categories = new HashSet<>();
    private int flags;

    public Intent() {}

    public Intent(String action) {
        this.action = action;
    }

    public Intent(String action, Uri data) {
        this.action = action;
        this.data = data;
    }

    public Intent(Context context, Class<?> target) {
        if (context != null && target != null) {
            component = new ComponentName(
                    context.getPackageName(), target.getName());
        }
    }

    public Intent(Intent source) {
        if (source != null) {
            action = source.action;
            packageName = source.packageName;
            type = source.type;
            data = source.data;
            component = source.component;
            extras = new Bundle(source.extras);
            categories.addAll(source.categories);
            flags = source.flags;
        }
    }

    public Intent setAction(String action) {
        this.action = action;
        return this;
    }

    public String getAction() {
        return action;
    }

    public Intent setPackage(String packageName) {
        this.packageName = packageName;
        return this;
    }

    public String getPackage() {
        return packageName;
    }

    public Intent setClassName(String packageName, String className) {
        component = new ComponentName(packageName, className);
        return this;
    }

    public Intent setComponent(ComponentName component) {
        this.component = component;
        return this;
    }

    public ComponentName getComponent() {
        return component;
    }

    public Intent setData(Uri data) {
        this.data = data;
        type = null;
        return this;
    }

    public Uri getData() {
        return data;
    }

    public String getDataString() {
        return data == null ? null : data.toString();
    }

    public Intent setType(String type) {
        this.type = type;
        data = null;
        return this;
    }

    public String getType() {
        return type;
    }

    public Intent setDataAndType(Uri data, String type) {
        this.data = data;
        this.type = type;
        return this;
    }

    public Intent addCategory(String category) {
        if (category != null) categories.add(category);
        return this;
    }

    public void removeCategory(String category) {
        categories.remove(category);
    }

    public Set<String> getCategories() {
        return categories.isEmpty()
                ? null : new HashSet<>(categories);
    }

    public Intent addFlags(int flags) {
        this.flags |= flags;
        return this;
    }

    public Intent setFlags(int flags) {
        this.flags = flags;
        return this;
    }

    public int getFlags() {
        return flags;
    }

    public Intent putExtras(Bundle bundle) {
        if (bundle != null) extras.putAll(bundle);
        return this;
    }

    public Intent replaceExtras(Bundle bundle) {
        extras = bundle == null ? new Bundle() : new Bundle(bundle);
        return this;
    }

    public Bundle getExtras() {
        return new Bundle(extras);
    }

    public boolean hasExtra(String key) {
        return extras.containsKey(key);
    }

    public Intent putExtra(String key, String value) {
        extras.putString(key, value);
        return this;
    }

    public Intent putExtra(String key, int value) {
        extras.putInt(key, value);
        return this;
    }

    public Intent putExtra(String key, long value) {
        extras.putLong(key, value);
        return this;
    }

    public Intent putExtra(String key, boolean value) {
        extras.putBoolean(key, value);
        return this;
    }

    public String getStringExtra(String key) {
        return extras.getString(key);
    }

    public int getIntExtra(String key, int fallback) {
        return extras.getInt(key, fallback);
    }

    public long getLongExtra(String key, long fallback) {
        return extras.getLong(key, fallback);
    }

    public boolean getBooleanExtra(String key, boolean fallback) {
        return extras.getBoolean(key, fallback);
    }

    public Intent removeExtra(String key) {
        extras.remove(key);
        return this;
    }
}
