package net

import base "mylinux/net/netbase"

// ============================================================
// MYLINUX NETWORK PACKAGE
// ============================================================

const (
	Version          = base.NetBaseVersion
	MaxInterfaces    = base.MaxInterfaces
	MaxPacketSize    = base.MaxPacketSize
	DefaultMTU       = base.DefaultMTU
	MaxStoredPackets = 1024
)

// Network protocol identifiers.
const (
	ProtocolICMP = 1
	ProtocolTCP  = 6
	ProtocolUDP  = 17
	ProtocolIPv6 = 58
)

// Network types.
const (
	AddressIPv4 = iota
	AddressIPv6
)

// ============================================================
// NETWORK TYPES
// ============================================================

type Address = base.Address
type Interface = base.Interface
type Packet = base.Packet
type Configuration = base.Configuration
type Stack = base.Stack

type Statistics struct {
	Interfaces int
	Routes     int
	Packets    int
	Running    bool
}

type NetworkStatus struct {
	Name    string
	Version int
	Running bool
}

// ============================================================
// STACK CREATION
// ============================================================

func NewStack() *Stack {
	return base.NewStack()
}

func StartStack(stack *Stack) bool {
	if stack == nil {
		return false
	}

	if stack.Running {
		return false
	}

	stack.Start()
	return stack.Running
}

func StopStack(stack *Stack) bool {
	if stack == nil || !stack.Running {
		return false
	}

	stack.Stop()
	return !stack.Running
}

func IsRunning(stack *Stack) bool {
	if stack == nil {
		return false
	}

	return stack.Running
}

// ============================================================
// ADDRESS MANAGEMENT
// ============================================================

func NewAddress(host string, port int, ipv6 bool) Address {
	return Address{
		Host: host,
		Port: port,
		IPv6: ipv6,
	}
}

func ValidateAddress(address Address) bool {
	if address.Host == "" {
		return false
	}

	if address.Port < 0 || address.Port > 65535 {
		return false
	}

	return true
}

func IsIPv6(address Address) bool {
	return address.IPv6
}

func IsIPv4(address Address) bool {
	return !address.IPv6
}

func SameAddress(first Address, second Address) bool {
	return first.Host == second.Host &&
		first.Port == second.Port &&
		first.IPv6 == second.IPv6
}

// ============================================================
// INTERFACE MANAGEMENT
// ============================================================

func AddInterface(
	stack *Stack,
	name string,
	address Address,
	mtu int,
) bool {
	if stack == nil {
		return false
	}

	if !ValidateAddress(address) {
		return false
	}

	return stack.AddInterface(name, address, mtu)
}

func RemoveInterface(stack *Stack, name string) bool {
	if stack == nil {
		return false
	}

	return stack.RemoveInterface(name)
}

func FindInterface(stack *Stack, name string) (*Interface, bool) {
	if stack == nil {
		return nil, false
	}

	item, exists := stack.Interfaces[name]
	return item, exists
}

func EnableInterface(stack *Stack, name string) bool {
	item, exists := FindInterface(stack, name)

	if !exists {
		return false
	}

	item.Enable()
	return true
}

func DisableInterface(stack *Stack, name string) bool {
	item, exists := FindInterface(stack, name)

	if !exists {
		return false
	}

	item.Disable()
	return true
}

func ChangeMTU(stack *Stack, name string, mtu int) bool {
	item, exists := FindInterface(stack, name)

	if !exists {
		return false
	}

	return item.SetMTU(mtu)
}

func InterfaceCount(stack *Stack) int {
	if stack == nil {
		return 0
	}

	return len(stack.Interfaces)
}

// ============================================================
// ROUTING
// ============================================================

func AddRoute(
	stack *Stack,
	destination string,
	gateway Address,
) bool {
	if stack == nil {
		return false
	}

	if !ValidateAddress(gateway) {
		return false
	}

	return stack.AddRoute(destination, gateway)
}

func RemoveRoute(stack *Stack, destination string) bool {
	if stack == nil || destination == "" {
		return false
	}

	if _, exists := stack.Routes[destination]; !exists {
		return false
	}

	delete(stack.Routes, destination)
	return true
}

func FindRoute(
	stack *Stack,
	destination string,
) (Address, bool) {
	if stack == nil {
		return Address{}, false
	}

	return stack.FindRoute(destination)
}

func RouteCount(stack *Stack) int {
	if stack == nil {
		return 0
	}

	return len(stack.Routes)
}

// ============================================================
// PACKET CREATION AND VALIDATION
// ============================================================

func NewPacket(
	source Address,
	destination Address,
	payload []byte,
	protocol int,
) Packet {
	return base.NewPacket(
		source,
		destination,
		payload,
		protocol,
	)
}

func ValidatePacket(packet Packet) bool {
	return base.ValidatePacket(packet)
}

func ValidateProtocol(protocol int) bool {
	switch protocol {
	case ProtocolICMP, ProtocolTCP, ProtocolUDP, ProtocolIPv6:
		return true
	default:
		return false
	}
}

func CopyPayload(data []byte) []byte {
	return base.CopyPayload(data)
}

func PacketSize(packet Packet) int {
	return len(packet.Payload)
}

func PacketProtocol(packet Packet) int {
	return packet.Protocol
}

// ============================================================
// PACKET STORAGE
// ============================================================

func StorePacket(stack *Stack, packet Packet) bool {
	if stack == nil {
		return false
	}

	return stack.StorePacket(packet)
}

func PacketTotal(stack *Stack) int {
	if stack == nil {
		return 0
	}

	return stack.PacketTotal()
}

func GetPacket(
	stack *Stack,
	index int,
) (Packet, bool) {
	if stack == nil {
		return Packet{}, false
	}

	if index < 0 || index >= len(stack.Packets) {
		return Packet{}, false
	}

	return stack.Packets[index], true
}

func ClearPackets(stack *Stack) bool {
	if stack == nil {
		return false
	}

	stack.Packets = make([]Packet, 0)
	return true
}

// ============================================================
// INCOMING AND OUTGOING QUEUES
// ============================================================

func SubmitPacket(stack *Stack, packet Packet) bool {
	if stack == nil {
		return false
	}

	return stack.Submit(packet)
}

func ReceivePacket(stack *Stack) (Packet, bool) {
	if stack == nil {
		return Packet{}, false
	}

	return stack.ReceiveOutgoing()
}

func QueueIncoming(stack *Stack, packet Packet) bool {
	if stack == nil || !stack.Running {
		return false
	}

	if !ValidatePacket(packet) {
		return false
	}

	select {
	case stack.Incoming <- packet:
		return true
	default:
		return false
	}
}

func IncomingQueueLength(stack *Stack) int {
	if stack == nil {
		return 0
	}

	return len(stack.Incoming)
}

func OutgoingQueueLength(stack *Stack) int {
	if stack == nil {
		return 0
	}

	return len(stack.Outgoing)
}

// ============================================================
// WORKERS
// ============================================================

func StartWorkers(stack *Stack) bool {
	if stack == nil || !stack.Running {
		return false
	}

	stack.StartWorkers()
	return true
}

func StartPacketWorker(
	input <-chan Packet,
	output chan<- Packet,
) {
	base.PacketWorker(input, output)
}

func CreatePacketWorker() (
	chan<- Packet,
	<-chan Packet,
) {
	return base.StartPacketWorker()
}

// ============================================================
// NETWORK CONFIGURATION
// ============================================================

func NewConfiguration(hostname string) Configuration {
	return base.NewConfiguration(hostname)
}

func SetOption(
	config *Configuration,
	key string,
	value string,
) bool {
	if config == nil || key == "" {
		return false
	}

	config.SetOption(key, value)
	return true
}

func GetOption(
	config Configuration,
	key string,
) (string, bool) {
	return config.GetOption(key)
}

func AddConfiguredInterface(
	config *Configuration,
	item Interface,
) bool {
	if config == nil || item.Name == "" {
		return false
	}

	if len(config.Interfaces) >= MaxInterfaces {
		return false
	}

	for _, existing := range config.Interfaces {
		if existing.Name == item.Name {
			return false
		}
	}

	config.Interfaces = append(config.Interfaces, item)
	return true
}

func ApplyConfiguration(
	stack *Stack,
	config Configuration,
) bool {
	if stack == nil {
		return false
	}

	for _, item := range config.Interfaces {
		if !stack.AddInterface(
			item.Name,
			item.Address,
			item.MTU,
		) {
			return false
		}

		if !item.Enabled {
			found, exists := stack.Interfaces[item.Name]

			if exists {
				found.Disable()
			}
		}
	}

	return true
}

// ============================================================
// STATISTICS
// ============================================================

func GetStatistics(stack *Stack) Statistics {
	if stack == nil {
		return Statistics{}
	}

	return Statistics{
		Interfaces: len(stack.Interfaces),
		Routes:     len(stack.Routes),
		Packets:    len(stack.Packets),
		Running:    stack.Running,
	}
}

func GetNetworkStatus(stack *Stack) NetworkStatus {
	if stack == nil {
		return NetworkStatus{
			Name:    base.NetworkName,
			Version: Version,
			Running: false,
		}
	}

	return NetworkStatus{
		Name:    base.NetworkName,
		Version: Version,
		Running: stack.Running,
	}
}

func ProtocolTable() [4]int {
	return base.ProtocolTable()
}

// ============================================================
// INFORMATION OUTPUT
// ============================================================

func PrintInfo(stack *Stack) {
	if stack == nil {
		println("MyLinux Network: unavailable")
		return
	}

	println("MyLinux Network")
	println("Version:", Version)
	println("Running:", stack.Running)
	println("Interfaces:", len(stack.Interfaces))
	println("Routes:", len(stack.Routes))
	println("Packets:", len(stack.Packets))
}

func PrintInterfaces(stack *Stack) {
	if stack == nil {
		return
	}

	for name, item := range stack.Interfaces {
		println(
			"Interface:",
			name,
			"Host:",
			item.Address.Host,
			"Port:",
			item.Address.Port,
			"MTU:",
			item.MTU,
			"Enabled:",
			item.Enabled,
		)
	}
}

func PrintRoutes(stack *Stack) {
	if stack == nil {
		return
	}

	for destination, gateway := range stack.Routes {
		println(
			"Destination:",
			destination,
			"Gateway:",
			gateway.Host,
			"Port:",
			gateway.Port,
		)
	}
}

func PrintPackets(stack *Stack) {
	if stack == nil {
		return
	}

	for index, packet := range stack.Packets {
		println(
			"Packet:",
			index,
			"Source:",
			packet.Source.Host,
			"Destination:",
			packet.Destination.Host,
			"Length:",
			packet.Length,
			"Protocol:",
			packet.Protocol,
		)
	}
}

// ============================================================
// NETWORK TEST
// ============================================================

func TestNetwork() {
	stack := NewStack()

	if !StartStack(stack) {
		println("Network startup failed")
		return
	}

	address := NewAddress(
		"127.0.0.1",
		80,
		false,
	)

	if AddInterface(
		stack,
		"loopback",
		address,
		DefaultMTU,
	) {
		println("Loopback interface created")
	}

	packet := NewPacket(
		address,
		address,
		[]byte("MyLinux network test"),
		ProtocolTCP,
	)

	if StorePacket(stack, packet) {
		println("Packet stored")
	}

	PrintInfo(stack)
	PrintInterfaces(stack)
	PrintPackets(stack)

	StopStack(stack)
}
