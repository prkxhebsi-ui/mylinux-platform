package android.content.pm;

public class InstrumentationInfo extends PackageItemInfo {
    public String targetPackage;
    public String sourceDir;
    public String publicSourceDir;
    public String dataDir;
    public String[] splitNames;
    public boolean functionalTest;
    public boolean handleProfiling;
}
