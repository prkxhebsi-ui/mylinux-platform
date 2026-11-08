package android.content;

import java.util.Objects;

public final class ComponentName {
    private final String packageName;
    private final String className;

    public ComponentName(String packageName, String className) {
        if (packageName == null || className == null) {
            throw new IllegalArgumentException(
                    "Package and class names cannot be null");
        }
        this.packageName = packageName;
        this.className = className;
    }

    public ComponentName(Context context, Class<?> cls) {
        this(context.getPackageName(), cls.getName());
    }

    public String getPackageName() {
        return packageName;
    }

    public String getClassName() {
        return className;
    }

    public String flattenToString() {
        return packageName + "/" + className;
    }

    public String flattenToShortString() {
        String prefix = packageName + ".";
        String name = className.startsWith(prefix)
                ? className.substring(prefix.length()) : className;
        return packageName + "/" + name;
    }

    public static ComponentName unflattenFromString(String value) {
        if (value == null) return null;

        int separator = value.indexOf('/');
        if (separator <= 0 || separator == value.length() - 1) {
            return null;
        }

        String pkg = value.substring(0, separator);
        String cls = value.substring(separator + 1);

        if (cls.startsWith(".")) cls = pkg + cls;
        return new ComponentName(pkg, cls);
    }

    @Override
    public boolean equals(Object object) {
        if (this == object) return true;
        if (!(object instanceof ComponentName)) return false;

        ComponentName other = (ComponentName) object;
        return packageName.equals(other.packageName)
                && className.equals(other.className);
    }

    @Override
    public int hashCode() {
        return Objects.hash(packageName, className);
    }

    @Override
    public String toString() {
        return "ComponentInfo{" + flattenToString() + "}";
    }
}
