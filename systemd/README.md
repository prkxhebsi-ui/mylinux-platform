# MyLinux systemd

An original C-based, systemd-inspired service manager for MyLinux.

## Initial features

- Service unit file loading
- Description and ExecStart parsing
- Basic process launching
- Child process monitoring
- Restart=always and Restart=on-failure
- PID 1 enforcement for service execution
- Android executable availability checks

## Current limitations

This is an early development implementation.

Not yet implemented:
- Dependency graph and After/Before ordering
- Requires/Wants dependency handling
- Target units
- Mount units
- Android property service
- SELinux domain transitions
- Binder initialization
- Android init .rc compatibility
- cgroups and resource control
- Journal protocol
- Socket and timer activation
- Graceful Android shutdown integration

The current manager starts service files in filename order.
It does not interpret After= or Requires= yet.

Zygote is responsible for launching system_server.
system_server must not be launched as an ordinary native service.

Do not install this as PID 1 or use these example units for device boot.
Android boot integration requires verified SELinux, property, Binder,
mount, device-node, vendor-service and kernel interfaces.
