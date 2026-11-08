package com.mylinux.voip;

/**
 * MyLinux VoIP extension API prototype.
 *
 * No microphone, network or calling operations are implemented here.
 */
public final class VoipManager {

    public static final int STATE_IDLE = 0;
    public static final int STATE_CONNECTING = 1;
    public static final int STATE_CONNECTED = 2;
    public static final int STATE_DISCONNECTED = 3;

    private int state = STATE_IDLE;

    public int getState() {
        return state;
    }

    public void reset() {
        state = STATE_IDLE;
    }
}
