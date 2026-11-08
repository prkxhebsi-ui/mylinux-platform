package com.android.server.pm;

public final class PackageUserState {
    private final int userId;
    private boolean installed = true;
    private boolean enabled = true;
    private boolean hidden;

    public PackageUserState(int userId) {
        this.userId = userId;
    }

    public int getUserId() { return userId; }
    public boolean isInstalled() { return installed; }
    public boolean isEnabled() { return enabled; }
    public boolean isHidden() { return hidden; }

    public void setInstalled(boolean value) { installed = value; }
    public void setEnabled(boolean value) { enabled = value; }
    public void setHidden(boolean value) { hidden = value; }
}
