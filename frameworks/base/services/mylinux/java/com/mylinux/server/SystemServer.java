package com.mylinux.server;

import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

/*
 * MyLinux SystemServer
 *
 * A modular Java system-service prototype.
 * Each manager owns smaller structures.
 * SystemServer aggregates and coordinates them.
 */

public final class SystemServer {

    // =========================================================
    // 1. CORE STRUCTURES
    // =========================================================

    enum ServiceState {
        CREATED,
        STARTING,
        RUNNING,
        STOPPING,
        STOPPED,
        FAILED
    }

    enum BootPhase {
        EARLY,
        CORE,
        SERVICES,
        READY
    }

    static final class Identity {
        final int uid;
        final int gid;
        final String name;

        Identity(int uid, int gid, String name) {
            this.uid = uid;
            this.gid = gid;
            this.name = name;
        }
    }

    static final class ServiceInfo {
        final String name;
        final Identity identity;
        ServiceState state;
        long startTime;

        ServiceInfo(String name, Identity identity) {
            this.name = name;
            this.identity = identity;
            this.state = ServiceState.CREATED;
        }
    }

    static final class BootEvent {
        final long time;
        final BootPhase phase;
        final String message;

        BootEvent(BootPhase phase, String message) {
            this.time = System.currentTimeMillis();
            this.phase = phase;
            this.message = message;
        }
    }

    static final class BootLog {
        private final List<BootEvent> events =
            new ArrayList<BootEvent>();

        synchronized void add(BootPhase phase, String message) {
            BootEvent event = new BootEvent(phase, message);
            events.add(event);

            System.out.println(
                "[" + phase + "] " + message
            );
        }

        synchronized int size() {
            return events.size();
        }
    }

    static final class SystemConfig {
        String platformName = "MyLinux";
        String version = "0.1-development";
        String architecture = "arm64";
        int apiLevel = 30;
        boolean safeMode = false;
        boolean debugMode = true;
    }

    static final class RuntimeEnvironment {
        final SystemConfig config = new SystemConfig();
        final BootLog bootLog = new BootLog();
        final EventBus eventBus = new EventBus();
        final ServiceRegistry registry = new ServiceRegistry();
    }

    // =========================================================
    // 2. EVENT SYSTEM
    // =========================================================

    interface EventListener {
        void onEvent(String event);
    }

    static final class EventBus {
        private final Map<String, List<EventListener>> listeners =
            new LinkedHashMap<String, List<EventListener>>();

        synchronized void subscribe(
            String topic,
            EventListener listener
        ) {
            List<EventListener> list = listeners.get(topic);

            if (list == null) {
                list = new ArrayList<EventListener>();
                listeners.put(topic, list);
            }

            list.add(listener);
        }

        synchronized void publish(String topic, String event) {
            List<EventListener> list = listeners.get(topic);

            if (list == null) {
                return;
            }

            List<EventListener> copy =
                new ArrayList<EventListener>(list);

            for (EventListener listener : copy) {
                listener.onEvent(event);
            }
        }
    }

    // =========================================================
    // 3. SERVICE INTERFACE AND BASE SERVICE
    // =========================================================

    interface SystemService {
        String getName();
        String[] getDependencies();
        ServiceState getState();
        boolean start();
        void stop();
    }

    static abstract class BaseService implements SystemService {

        protected final RuntimeEnvironment environment;
        protected final ServiceInfo info;

        BaseService(
            RuntimeEnvironment environment,
            String name,
            Identity identity
        ) {
            this.environment = environment;
            this.info = new ServiceInfo(name, identity);
        }

        @Override
        public final String getName() {
            return info.name;
        }

        @Override
        public final ServiceState getState() {
            return info.state;
        }

        @Override
        public final boolean start() {
            if (info.state == ServiceState.RUNNING) {
                return true;
            }

            info.state = ServiceState.STARTING;
            info.startTime = System.currentTimeMillis();

            try {
                onStart();
                info.state = ServiceState.RUNNING;

                environment.bootLog.add(
                    BootPhase.SERVICES,
                    getName() + " started"
                );

                environment.eventBus.publish(
                    "service.started",
                    getName()
                );

                return true;
            } catch (RuntimeException exception) {
                info.state = ServiceState.FAILED;

                environment.bootLog.add(
                    BootPhase.SERVICES,
                    getName() + " failed: " + exception.getMessage()
                );

                return false;
            }
        }

        @Override
        public final void stop() {
            if (info.state != ServiceState.RUNNING) {
                return;
            }

            info.state = ServiceState.STOPPING;
            onStop();
            info.state = ServiceState.STOPPED;
        }

        protected void onStart() {
        }

        protected void onStop() {
        }
    }

    // =========================================================
    // 4. SERVICE REGISTRY
    // =========================================================

    static final class ServiceRegistry {

        private final Map<String, SystemService> services =
            new LinkedHashMap<String, SystemService>();

        boolean register(SystemService service) {
            if (services.containsKey(service.getName())) {
                return false;
            }

            services.put(service.getName(), service);
            return true;
        }

        SystemService get(String name) {
            return services.get(name);
        }

        boolean isRunning(String name) {
            SystemService service = get(name);

            return service != null &&
                service.getState() == ServiceState.RUNNING;
        }

        boolean startAll() {
            for (SystemService service : services.values()) {
                for (String dependency : service.getDependencies()) {
                    if (!isRunning(dependency)) {
                        System.err.println(
                            "Missing dependency: " +
                            service.getName() + " requires " +
                            dependency
                        );
                        return false;
                    }
                }

                if (!service.start()) {
                    return false;
                }
            }

            return true;
        }

        void stopAll() {
            List<SystemService> reverse =
                new ArrayList<SystemService>(services.values());

            Collections.reverse(reverse);

            for (SystemService service : reverse) {
                service.stop();
            }
        }

        int size() {
            return services.size();
        }
    }

    // =========================================================
    // 5. SMALL DATA STRUCTURES
    // =========================================================

    static final class ProcessRecord {
        int pid;
        int uid;
        String processName;
        boolean alive;
    }

    static final class ProcessTable {
        final List<ProcessRecord> processes =
            new ArrayList<ProcessRecord>();

        void add(ProcessRecord process) {
            processes.add(process);
        }

        int count() {
            return processes.size();
        }
    }

    static final class PackageRecord {
        String packageName;
        int versionCode;
        int userId;
        boolean installed;
    }

    static final class PackageCatalog {
        final Map<String, PackageRecord> packages =
            new LinkedHashMap<String, PackageRecord>();
    }

    static final class WindowRecord {
        int windowId;
        String title;
        boolean visible;
    }

    static final class WindowTree {
        final List<WindowRecord> windows =
            new ArrayList<WindowRecord>();
    }

    static final class PowerState {
        boolean interactive = true;
        boolean sleeping = false;
        int brightness = 100;
    }

    static final class UserRecord {
        int userId;
        String userName;
        boolean enabled;
    }

    static final class UserDirectory {
        final Map<Integer, UserRecord> users =
            new LinkedHashMap<Integer, UserRecord>();
    }

    static final class PermissionRecord {
        String packageName;
        String permission;
        boolean granted;
    }

    static final class PermissionTable {
        final List<PermissionRecord> permissions =
            new ArrayList<PermissionRecord>();
    }

    static final class StorageVolume {
        String name;
        String path;
        boolean mounted;
    }

    static final class StorageTable {
        final List<StorageVolume> volumes =
            new ArrayList<StorageVolume>();
    }

    static final class NetworkState {
        boolean wifiEnabled;
        boolean connected;
        String interfaceName = "wlan0";
    }

    static final class InputState {
        boolean touchscreenAvailable;
        boolean keyboardAvailable;
        int queuedEvents;
    }

    static final class DisplayState {
        int width = 1280;
        int height = 800;
        int densityDpi = 160;
        boolean enabled = true;
    }

    static final class NotificationRecord {
        int id;
        String packageName;
        String title;
        String message;
    }

    static final class NotificationQueue {
        final List<NotificationRecord> notifications =
            new ArrayList<NotificationRecord>();
    }

    static final class JobRecord {
        int jobId;
        String owner;
        boolean running;
    }

    static final class JobQueue {
        final List<JobRecord> jobs =
            new ArrayList<JobRecord>();
    }

    static final class AlarmRecord {
        long triggerTime;
        String owner;
        boolean active;
    }

    static final class AlarmQueue {
        final List<AlarmRecord> alarms =
            new ArrayList<AlarmRecord>();
    }

    static final class BatteryState {
        int level = 100;
        boolean charging;
        boolean lowPowerMode;
    }

    // =========================================================
    // 6. SYSTEM MANAGERS
    // =========================================================

    static final Identity SYSTEM_IDENTITY =
        new Identity(1000, 1000, "system");

    static final class UserManagerService extends BaseService {
        final UserDirectory directory = new UserDirectory();

        UserManagerService(RuntimeEnvironment env) {
            super(env, "UserManagerService", SYSTEM_IDENTITY);
        }

        public String[] getDependencies() {
            return new String[0];
        }

        protected void onStart() {
            UserRecord user = new UserRecord();
            user.userId = 0;
            user.userName = "owner";
            user.enabled = true;
            directory.users.put(0, user);
        }
    }

    static final class PackageManagerService extends BaseService {
        final PackageCatalog catalog = new PackageCatalog();

        PackageManagerService(RuntimeEnvironment env) {
            super(env, "PackageManagerService", SYSTEM_IDENTITY);
        }

        public String[] getDependencies() {
            return new String[] {"UserManagerService"};
        }
    }

    static final class PermissionManagerService extends BaseService {
        final PermissionTable table = new PermissionTable();

        PermissionManagerService(RuntimeEnvironment env) {
            super(env, "PermissionManagerService", SYSTEM_IDENTITY);
        }

        public String[] getDependencies() {
            return new String[] {
                "UserManagerService",
                "PackageManagerService"
            };
        }
    }

    static final class PowerManagerService extends BaseService {
        final PowerState power = new PowerState();

        PowerManagerService(RuntimeEnvironment env) {
            super(env, "PowerManagerService", SYSTEM_IDENTITY);
        }

        public String[] getDependencies() {
            return new String[0];
        }
    }

    static final class DisplayManagerService extends BaseService {
        final DisplayState display = new DisplayState();

        DisplayManagerService(RuntimeEnvironment env) {
            super(env, "DisplayManagerService", SYSTEM_IDENTITY);
        }

        public String[] getDependencies() {
            return new String[] {"PowerManagerService"};
        }
    }

    static final class InputManagerService extends BaseService {
        final InputState input = new InputState();

        InputManagerService(RuntimeEnvironment env) {
            super(env, "InputManagerService", SYSTEM_IDENTITY);
        }

        public String[] getDependencies() {
            return new String[] {"DisplayManagerService"};
        }
    }

    static final class WindowManagerService extends BaseService {
        final WindowTree tree = new WindowTree();

        WindowManagerService(RuntimeEnvironment env) {
            super(env, "WindowManagerService", SYSTEM_IDENTITY);
        }

        public String[] getDependencies() {
            return new String[] {
                "DisplayManagerService",
                "InputManagerService",
                "PowerManagerService"
            };
        }
    }

    static final class ActivityManagerService extends BaseService {
        final ProcessTable processes = new ProcessTable();

        ActivityManagerService(RuntimeEnvironment env) {
            super(env, "ActivityManagerService", SYSTEM_IDENTITY);
        }

        public String[] getDependencies() {
            return new String[] {
                "PackageManagerService",
                "PermissionManagerService",
                "WindowManagerService"
            };
        }
    }

    static final class StorageManagerService extends BaseService {
        final StorageTable storage = new StorageTable();

        StorageManagerService(RuntimeEnvironment env) {
            super(env, "StorageManagerService", SYSTEM_IDENTITY);
        }

        public String[] getDependencies() {
            return new String[] {"UserManagerService"};
        }
    }

    static final class NetworkManagerService extends BaseService {
        final NetworkState network = new NetworkState();

        NetworkManagerService(RuntimeEnvironment env) {
            super(env, "NetworkManagerService", SYSTEM_IDENTITY);
        }

        public String[] getDependencies() {
            return new String[0];
        }
    }

    static final class NotificationManagerService extends BaseService {
        final NotificationQueue queue = new NotificationQueue();

        NotificationManagerService(RuntimeEnvironment env) {
            super(env, "NotificationManagerService", SYSTEM_IDENTITY);
        }

        public String[] getDependencies() {
            return new String[] {
                "ActivityManagerService",
                "PermissionManagerService"
            };
        }
    }

    static final class JobSchedulerService extends BaseService {
        final JobQueue queue = new JobQueue();

        JobSchedulerService(RuntimeEnvironment env) {
            super(env, "JobSchedulerService", SYSTEM_IDENTITY);
        }

        public String[] getDependencies() {
            return new String[] {
                "ActivityManagerService",
                "PowerManagerService"
            };
        }
    }

    static final class AlarmManagerService extends BaseService {
        final AlarmQueue queue = new AlarmQueue();

        AlarmManagerService(RuntimeEnvironment env) {
            super(env, "AlarmManagerService", SYSTEM_IDENTITY);
        }

        public String[] getDependencies() {
            return new String[] {"PowerManagerService"};
        }
    }

    static final class BatteryManagerService extends BaseService {
        final BatteryState battery = new BatteryState();

        BatteryManagerService(RuntimeEnvironment env) {
            super(env, "BatteryManagerService", SYSTEM_IDENTITY);
        }

        public String[] getDependencies() {
            return new String[] {"PowerManagerService"};
        }
    }

    // =========================================================
    // 7. THE LARGE SYSTEMSERVER STRUCTURE
    // =========================================================

    private final RuntimeEnvironment environment =
        new RuntimeEnvironment();

    final UserManagerService userManager =
        new UserManagerService(environment);

    final PackageManagerService packageManager =
        new PackageManagerService(environment);

    final PermissionManagerService permissionManager =
        new PermissionManagerService(environment);

    final PowerManagerService powerManager =
        new PowerManagerService(environment);

    final DisplayManagerService displayManager =
        new DisplayManagerService(environment);

    final InputManagerService inputManager =
        new InputManagerService(environment);

    final WindowManagerService windowManager =
        new WindowManagerService(environment);

    final ActivityManagerService activityManager =
        new ActivityManagerService(environment);

    final StorageManagerService storageManager =
        new StorageManagerService(environment);

    final NetworkManagerService networkManager =
        new NetworkManagerService(environment);

    final NotificationManagerService notificationManager =
        new NotificationManagerService(environment);

    final JobSchedulerService jobScheduler =
        new JobSchedulerService(environment);

    final AlarmManagerService alarmManager =
        new AlarmManagerService(environment);

    final BatteryManagerService batteryManager =
        new BatteryManagerService(environment);

    private boolean running = false;
    private BootPhase currentPhase = BootPhase.EARLY;

    // =========================================================
    // 8. CONSTRUCTION AND BOOT
    // =========================================================

    public SystemServer() {
        registerServices();
    }

    private void registerServices() {
        ServiceRegistry registry = environment.registry;

        registry.register(userManager);
        registry.register(packageManager);
        registry.register(permissionManager);
        registry.register(powerManager);
        registry.register(displayManager);
        registry.register(inputManager);
        registry.register(windowManager);
        registry.register(activityManager);
        registry.register(storageManager);
        registry.register(networkManager);
        registry.register(notificationManager);
        registry.register(jobScheduler);
        registry.register(alarmManager);
        registry.register(batteryManager);
    }

    public boolean start() {
        if (running) {
            return true;
        }

        environment.bootLog.add(
            BootPhase.EARLY,
            "MyLinux SystemServer starting"
        );

        environment.bootLog.add(
            BootPhase.CORE,
            "Initializing system service registry"
        );

        if (!environment.registry.startAll()) {
            environment.bootLog.add(
                BootPhase.READY,
                "SystemServer startup failed"
            );

            return false;
        }

        currentPhase = BootPhase.READY;
        running = true;

        environment.bootLog.add(
            BootPhase.READY,
            "All system services started"
        );

        environment.bootLog.add(
            BootPhase.READY,
            "MyLinux SystemServer is ready"
        );

        return true;
    }

    public void shutdown() {
        if (!running) {
            return;
        }

        environment.bootLog.add(
            currentPhase,
            "SystemServer shutting down"
        );

        environment.registry.stopAll();
        running = false;
    }

    public boolean isRunning() {
        return running;
    }

    public int getServiceCount() {
        return environment.registry.size();
    }

    public BootLog getBootLog() {
        return environment.bootLog;
    }

    // =========================================================
    // 9. ENTRY POINT
    // =========================================================

    public static void main(String[] args) {
        System.out.println("================================");
        System.out.println("       MYLINUX SYSTEMSERVER");
        System.out.println("================================");

        SystemServer server = new SystemServer();

        if (!server.start()) {
            System.err.println("SYSTEMSERVER FAILED");
            System.exit(1);
        }

        System.out.println("--------------------------------");
        System.out.println("Platform: MyLinux");
        System.out.println("Services: " + server.getServiceCount());
        System.out.println("State: RUNNING");
        System.out.println("--------------------------------");

        server.shutdown();

        System.out.println("SystemServer test completed.");
    }
}
