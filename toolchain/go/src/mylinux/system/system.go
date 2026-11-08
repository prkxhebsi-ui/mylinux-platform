package system

import (
	"mylinux/fileops"
	myfmt "mylinux/fmt"
	myio "mylinux/io"
	mynet "mylinux/net"
	myos "mylinux/os"
	myruntime "mylinux/runtime"
	"mylinux/system/cpu"
	"mylinux/system/devices"
	"mylinux/system/environment"
	"mylinux/system/filesystem"
	"mylinux/system/groups"
	"mylinux/system/memory"
	"mylinux/system/mount"
	"mylinux/system/permissions"
	"mylinux/system/process"
	"mylinux/system/properties"
	"mylinux/system/signals"
	"mylinux/system/syscall"
	"mylinux/system/users"
)

const (
	SystemVersion = "1.0"
	SystemName    = "MyLinux System"
)

type Configuration struct {
	Hostname         string
	Architecture     string
	EnableNetwork    bool
	EnableRuntime    bool
	EnableFilesystem bool
	EnableDevices    bool
}

type Status struct {
	Running        bool
	Hostname       string
	ProcessCount   int
	UserCount      int
	GroupCount     int
	DeviceCount    int
	MountCount     int
	MemoryTotal    uint64
	MemoryUsed     uint64
	NetworkRunning bool
	RuntimeRunning bool
}

type Kernel struct {
	Config Configuration

	OS      *myos.System
	Runtime *myruntime.Runtime
	Network *mynet.Stack

	Processes   *process.Manager
	CPU         *cpu.Manager
	Devices     *devices.Manager
	Environment *environment.Manager
	Filesystem  *filesystem.Manager
	Groups      *groups.Manager
	Memory      *memory.Manager
	Mounts      *mount.Manager
	Permissions *permissions.Manager
	Properties  *properties.Manager
	Signals     *signals.Manager
	Syscalls    *syscall.Dispatcher
	Users       *users.Manager

	Files  *fileops.FileManager
	Buffer *myio.Buffer

	Running bool
}

func NewKernel(hostname string) *Kernel {
	if hostname == "" {
		hostname = "mylinux"
	}

	osSystem := myos.NewSystem(hostname)

	kernel := &Kernel{
		Config: Configuration{
			Hostname:         hostname,
			Architecture:     "arm64",
			EnableNetwork:    true,
			EnableRuntime:    true,
			EnableFilesystem: true,
			EnableDevices:    true,
		},

		OS:      osSystem,
		Runtime: myruntime.NewRuntime(),
		Network: mynet.NewStack(),

		Processes:   process.NewManager(osSystem),
		CPU:         cpu.NewManager(osSystem),
		Devices:     devices.NewManager(),
		Environment: environment.NewManager(osSystem),
		Filesystem:  filesystem.NewManager(),
		Groups:      groups.NewManager(),
		Memory:      memory.NewManager(),
		Mounts:      mount.NewManager(),
		Permissions: permissions.NewManager(),
		Properties:  properties.NewManager(),
		Signals:     signals.NewManager(),
		Syscalls:    syscall.NewDispatcher(),
		Users:       users.NewManager(),

		Files:  fileops.NewFileManager(),
		Buffer: myio.NewBuffer(),
	}

	kernel.RegisterDefaults()
	return kernel
}

func (k *Kernel) RegisterDefaults() bool {
	if k == nil {
		return false
	}

	k.Properties.Set("system.name", SystemName)
	k.Properties.Set("system.version", SystemVersion)
	k.Properties.Set("system.hostname", k.Config.Hostname)
	k.Properties.Set("system.architecture", k.Config.Architecture)
	k.Properties.SetReadOnly("system.name", true)
	k.Properties.SetReadOnly("system.version", true)

	k.Environment.Set("HOSTNAME", k.Config.Hostname)
	k.Environment.Set("HOME", "/")
	k.Environment.Set("SHELL", "/system/bin/sh")
	k.Environment.Set("PATH", "/system/bin:/vendor/bin")

	k.Filesystem.Register("/", "rootfs", filesystem.TypeRoot, false)
	k.Filesystem.Register("/system", "system", filesystem.TypeSystem, true)
	k.Filesystem.Register("/data", "userdata", filesystem.TypeData, false)
	k.Filesystem.Register("/cache", "cache", filesystem.TypeCache, false)
	k.Filesystem.Register("/tmp", "tmpfs", filesystem.TypeTemporary, false)

	k.Memory.Register("kernel", 0, 0x100000)
	k.Memory.Register("system", 0x100000, 0x400000)
	k.Memory.Register("temporary", 0x500000, 0x100000)

	k.Devices.Register("console", "/dev/console",
		devices.DeviceCharacter, 5, 1)

	k.Devices.Register("null", "/dev/null",
		devices.DeviceCharacter, 1, 3)

	k.Devices.Register("zero", "/dev/zero",
		devices.DeviceCharacter, 1, 5)

	k.Devices.Register("random", "/dev/random",
		devices.DeviceCharacter, 1, 8)

	k.Devices.Register("urandom", "/dev/urandom",
		devices.DeviceCharacter, 1, 9)

	return true
}

func (k *Kernel) Start() bool {
	if k == nil || k.Running {
		return false
	}

	if k.OS == nil || !k.OS.Start() {
		return false
	}

	if k.Config.EnableRuntime {
		if k.Runtime == nil || !k.Runtime.Start() {
			k.OS.Stop()
			return false
		}
	}

	if k.Config.EnableNetwork {
		if k.Network == nil || !mynet.StartStack(k.Network) {
			if k.Runtime != nil {
				k.Runtime.Shutdown()
			}
			k.OS.Stop()
			return false
		}
	}

	k.Running = true
	k.Properties.Set("system.state", "running")
	return true
}

func (k *Kernel) Shutdown() bool {
	if k == nil || !k.Running {
		return false
	}

	if k.Network != nil && k.Network.Running {
		mynet.StopStack(k.Network)
	}

	if k.Runtime != nil {
		k.Runtime.Shutdown()
	}

	if k.OS != nil {
		k.OS.Stop()
	}

	k.Running = false
	k.Properties.Set("system.state", "stopped")
	return true
}

func (k *Kernel) GetStatus() Status {
	if k == nil {
		return Status{}
	}

	status := Status{
		Running:  k.Running,
		Hostname: k.Config.Hostname,
	}

	if k.Processes != nil {
		status.ProcessCount = k.Processes.Count()
	}

	if k.Users != nil {
		status.UserCount = k.Users.Count()
	}

	if k.Groups != nil {
		status.GroupCount = k.Groups.Count()
	}

	if k.Devices != nil {
		status.DeviceCount = k.Devices.Count()
	}

	if k.Mounts != nil {
		status.MountCount = k.Mounts.Count()
	}

	if k.Memory != nil {
		status.MemoryTotal = k.Memory.Total()
		status.MemoryUsed = k.Memory.Used()
	}

	if k.Network != nil {
		status.NetworkRunning = mynet.IsRunning(k.Network)
	}

	if k.Runtime != nil {
		status.RuntimeRunning = k.Runtime.Running
	}

	return status
}

func (k *Kernel) SetHostname(hostname string) bool {
	if k == nil || hostname == "" || k.Running {
		return false
	}

	k.Config.Hostname = hostname
	k.OS.Hostname = hostname
	k.Environment.Set("HOSTNAME", hostname)
	k.Properties.Set("system.hostname", hostname)
	return true
}

func (k *Kernel) CreateUser(
	name string,
	home string,
	shell string,
	groupName string,
) (uint32, bool) {
	if k == nil || k.Users == nil || k.Groups == nil {
		return 0, false
	}

	groupID, exists := k.Groups.Names[groupName]
	if !exists {
		var created bool
		groupID, created = k.Groups.Add(groupName)
		if !created {
			return 0, false
		}
	}

	userID, created := k.Users.Add(name, home, shell, groupID)
	if !created {
		return 0, false
	}

	k.Groups.AddMember(groupID, userID)
	return userID, true
}

func (k *Kernel) RemoveUser(uid uint32) bool {
	if k == nil || k.Users == nil || k.Groups == nil {
		return false
	}

	user, exists := k.Users.FindUID(uid)
	if !exists {
		return false
	}

	k.Groups.RemoveMember(user.GroupID, uid)
	return k.Users.Remove(uid)
}

func (k *Kernel) CreateProcess(name string, priority int) (int, bool) {
	if k == nil || !k.Running || k.Processes == nil {
		return 0, false
	}

	return k.Processes.Create(name, priority)
}

func (k *Kernel) TerminateProcess(pid int) bool {
	if k == nil || k.Processes == nil {
		return false
	}

	return k.Processes.Terminate(pid)
}

func (k *Kernel) SendSignal(pid int, number int, name string) bool {
	if k == nil || k.Signals == nil || k.Processes == nil {
		return false
	}

	if _, exists := k.Processes.Find(pid); !exists {
		return false
	}

	return k.Signals.Send(pid, number, name)
}

func (k *Kernel) AllocateMemory(region string, amount uint64) bool {
	if k == nil || k.Memory == nil {
		return false
	}

	return k.Memory.Allocate(region, amount)
}

func (k *Kernel) ReleaseMemory(region string, amount uint64) bool {
	if k == nil || k.Memory == nil {
		return false
	}

	return k.Memory.Release(region, amount)
}

func (k *Kernel) RegisterDevice(
	name string,
	path string,
	kind int,
	major uint32,
	minor uint32,
) bool {
	if k == nil || k.Devices == nil {
		return false
	}

	return k.Devices.Register(name, path, kind, major, minor)
}

func (k *Kernel) SetProperty(name string, value string) bool {
	if k == nil || k.Properties == nil {
		return false
	}

	return k.Properties.Set(name, value)
}

func (k *Kernel) GetProperty(name string) (string, bool) {
	if k == nil || k.Properties == nil {
		return "", false
	}

	return k.Properties.Get(name)
}

func (k *Kernel) SetEnvironment(name string, value string) bool {
	if k == nil || k.Environment == nil {
		return false
	}

	return k.Environment.Set(name, value)
}

func (k *Kernel) GetEnvironment(name string) (string, bool) {
	if k == nil || k.Environment == nil {
		return "", false
	}

	return k.Environment.Get(name)
}

func (k *Kernel) RegisterMount(
	source string,
	target string,
	kind string,
	flags uint64,
) bool {
	if k == nil || k.Mounts == nil {
		return false
	}

	return k.Mounts.Mount(source, target, kind, flags)
}

func (k *Kernel) UnregisterMount(target string) bool {
	if k == nil || k.Mounts == nil {
		return false
	}

	return k.Mounts.Unmount(target)
}

func (k *Kernel) CheckPermission(path string, requested uint32) bool {
	if k == nil || k.Permissions == nil {
		return false
	}

	return k.Permissions.Check(path, requested)
}

func (k *Kernel) SetPermission(
	path string,
	owner string,
	group string,
	mode uint32,
) bool {
	if k == nil || k.Permissions == nil {
		return false
	}

	return k.Permissions.Set(path, owner, group, mode)
}

func (k *Kernel) NetworkStatus() mynet.NetworkStatus {
	if k == nil || k.Network == nil {
		return mynet.NetworkStatus{}
	}

	return mynet.GetNetworkStatus(k.Network)
}

func (k *Kernel) PrintStatus() {
	if k == nil {
		return
	}

	status := k.GetStatus()

	k.Buffer.Reset()

	report := []byte(
		"MyLinux System Status\n" +
			"=====================\n" +
			"Hostname: " + status.Hostname + "\n" +
			"Running: " + boolText(status.Running) + "\n",
	)

	k.Buffer.Write(report)

	myfmt.PrintOS()
	myfmt.PrintNetwork()
	myfmt.PrintFeatures()

	_ = status
}

func boolText(value bool) string {
	if value {
		return "true"
	}
	return "false"
}

func Version() string {
	return SystemVersion
}

func Name() string {
	return SystemName
}

func TestSystem() bool {
	kernel := NewKernel("mylinux-test")

	if kernel == nil {
		return false
	}

	if !kernel.RegisterDefaults() {
		return false
	}

	if !kernel.Environment.Set("TEST", "1") {
		return false
	}

	value, exists := kernel.Environment.Get("TEST")
	if !exists || value != "1" {
		return false
	}

	if !kernel.Memory.Allocate("temporary", 4096) {
		return false
	}

	if !kernel.Memory.Release("temporary", 4096) {
		return false
	}

	if !kernel.Start() {
		return false
	}

	pid, created := kernel.CreateProcess("system-test", 5)
	if !created {
		kernel.Shutdown()
		return false
	}

	if !kernel.TerminateProcess(pid) {
		kernel.Shutdown()
		return false
	}

	return kernel.Shutdown()
}
