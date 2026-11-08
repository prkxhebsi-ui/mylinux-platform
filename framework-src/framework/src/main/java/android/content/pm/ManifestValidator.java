package android.content.pm;

public final class ManifestValidator {
    public ManifestValidationResult validate(ManifestDocument document) {
        ManifestValidationResult result = new ManifestValidationResult();

        if (document == null || document.root == null) {
            add(result, ManifestDiagnostic.Severity.FATAL,
                    "NO_DOCUMENT", "Manifest document is missing", null);
            return result;
        }

        ManifestNode root = document.root;

        if (!"manifest".equals(root.name)) {
            add(result, ManifestDiagnostic.Severity.FATAL,
                    "INVALID_ROOT", "Root element must be manifest", root.name);
            return result;
        }

        String packageName = root.getAttribute("package");

        if (packageName == null || packageName.length() == 0) {
            add(result, ManifestDiagnostic.Severity.ERROR,
                    "MISSING_PACKAGE", "Package name is required", "manifest");
        } else if (!validPackageName(packageName)) {
            add(result, ManifestDiagnostic.Severity.ERROR,
                    "INVALID_PACKAGE", "Invalid package name", "manifest");
        }

        ManifestNode application = root.getChild("application");

        if (application == null) {
            add(result, ManifestDiagnostic.Severity.WARNING,
                    "NO_APPLICATION",
                    "Manifest has no application element", "manifest");
        }

        validatePermissions(root, result);
        validateFeatures(root, result);

        if (application != null) {
            validateComponents(application, result);
        }

        document.validated = !result.hasErrors();
        return result;
    }

    private void validatePermissions(
            ManifestNode root, ManifestValidationResult result) {
        ManifestNode[] permissions = root.getChildren("uses-permission");

        for (int i = 0; i < permissions.length; i++) {
            String name = permissions[i].getAttribute("android:name");

            if (name == null) {
                add(result, ManifestDiagnostic.Severity.ERROR,
                        "PERMISSION_WITHOUT_NAME",
                        "Permission request has no android:name",
                        "uses-permission");
            }
        }
    }

    private void validateFeatures(
            ManifestNode root, ManifestValidationResult result) {
        ManifestNode[] features = root.getChildren("uses-feature");

        for (int i = 0; i < features.length; i++) {
            String name = features[i].getAttribute("android:name");
            String version = features[i].getAttribute("android:version");

            if (name == null && version == null) {
                add(result, ManifestDiagnostic.Severity.WARNING,
                        "EMPTY_FEATURE",
                        "Feature declaration has no name or version",
                        "uses-feature");
            }
        }
    }

    private void validateComponents(
            ManifestNode application, ManifestValidationResult result) {
        String[] names = new String[application.childCount];
        int count = 0;

        for (int i = 0; i < application.childCount; i++) {
            ManifestNode component = application.children[i];

            if (!isComponent(component.name)) continue;

            String name = component.getAttribute("android:name");

            if (name == null || name.length() == 0) {
                add(result, ManifestDiagnostic.Severity.ERROR,
                        "COMPONENT_WITHOUT_NAME",
                        "Component requires android:name", component.name);
                continue;
            }

            for (int j = 0; j < count; j++) {
                if (names[j].equals(name)) {
                    add(result, ManifestDiagnostic.Severity.ERROR,
                            "DUPLICATE_COMPONENT",
                            "Duplicate component: " + name, component.name);
                }
            }

            names[count++] = name;

            if ("provider".equals(component.name)
                    && component.getAttribute("android:authorities") == null) {
                add(result, ManifestDiagnostic.Severity.WARNING,
                        "PROVIDER_WITHOUT_AUTHORITY",
                        "Provider has no authorities", component.name);
            }
        }
    }

    private boolean isComponent(String name) {
        return "activity".equals(name)
                || "activity-alias".equals(name)
                || "service".equals(name)
                || "receiver".equals(name)
                || "provider".equals(name);
    }

    private boolean validPackageName(String name) {
        if (name.startsWith(".") || name.endsWith(".")) return false;
        if (name.indexOf("..") >= 0) return false;

        for (int i = 0; i < name.length(); i++) {
            char c = name.charAt(i);

            if (!Character.isLetterOrDigit(c) && c != '_' && c != '.') {
                return false;
            }
        }

        return name.indexOf('.') > 0;
    }

    private void add(
            ManifestValidationResult result,
            ManifestDiagnostic.Severity severity,
            String code,
            String message,
            String element) {
        result.add(new ManifestDiagnostic(severity, code, message, element));
    }
}
