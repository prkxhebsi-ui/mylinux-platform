package android.content.pm;

public class ManifestQuery {
    public String packageName;
    public String componentName;
    public ManifestAction action;
    public ManifestCategory category;
    public boolean requireExported;
    public boolean checkExported;

    public ManifestQuery() {
        packageName = "";
        componentName = "";
    }

    public boolean matchesPackage(String value) {
        if (packageName == null || packageName.length() == 0) {
            return true;
        }
        return packageName.equals(value);
    }

    public boolean matchesComponent(String value) {
        if (componentName == null || componentName.length() == 0) {
            return true;
        }
        return componentName.equals(value);
    }

    public boolean matchesExported(boolean exported) {
        if (!checkExported) {
            return true;
        }
        return exported == requireExported;
    }

    public void clear() {
        packageName = "";
        componentName = "";
        action = null;
        category = null;
        requireExported = false;
        checkExported = false;
    }
}
