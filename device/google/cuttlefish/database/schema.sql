CREATE TABLE IF NOT EXISTS virtual_devices (
    id INTEGER PRIMARY KEY,
    name TEXT NOT NULL UNIQUE,
    architecture TEXT NOT NULL,
    state TEXT NOT NULL DEFAULT 'stopped',
    created_at INTEGER NOT NULL
);

CREATE TABLE IF NOT EXISTS device_settings (
    device_id INTEGER NOT NULL,
    setting_key TEXT NOT NULL,
    setting_value TEXT,
    PRIMARY KEY (device_id, setting_key)
);

CREATE TABLE IF NOT EXISTS device_events (
    id INTEGER PRIMARY KEY,
    device_id INTEGER NOT NULL,
    event_type TEXT NOT NULL,
    event_time INTEGER NOT NULL
);
