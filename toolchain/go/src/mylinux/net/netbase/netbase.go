package netbase

// Network constants
const (
	NetBaseVersion = 1
	MaxInterfaces  = 16
	MaxPacketSize  = 65535
	DefaultMTU     = 1500
)

// Global variables
var (
	NetworkRunning = false
	NetworkName    = "MyLinux NetBase"
	PacketCount    uint64
)

// Network address
type Address struct {
	Host string
	Port int
	IPv6 bool
}

// Network interface
type Interface struct {
	Name    string
	Address Address
	MTU     int
	Enabled bool
}

// Network packet
type Packet struct {
	Source      Address
	Destination Address
	Payload     []byte
	Length      int
	Protocol    int
}

// Network configuration
type Configuration struct {
	Hostname   string
	Interfaces []Interface
	Options    map[string]string
}

// Network stack
type Stack struct {
	Running    bool
	Interfaces map[string]*Interface
	Routes     map[string]Address
	Packets    []Packet
	Incoming   chan Packet
	Outgoing   chan Packet
}

// Create a network stack
func NewStack() *Stack {
	return &Stack{
		Running:    false,
		Interfaces: make(map[string]*Interface),
		Routes:     make(map[string]Address),
		Packets:    make([]Packet, 0),
		Incoming:   make(chan Packet, 64),
		Outgoing:   make(chan Packet, 64),
	}
}

// Start the network stack
func (s *Stack) Start() {
	if s == nil {
		return
	}

	s.Running = true
	NetworkRunning = true

	println("NetBase started")
}

// Stop the network stack
func (s *Stack) Stop() {
	if s == nil {
		return
	}

	s.Running = false
	NetworkRunning = false

	println("NetBase stopped")
}

// Add an interface
func (s *Stack) AddInterface(name string, address Address, mtu int) bool {
	if s == nil || name == "" {
		return false
	}

	if len(s.Interfaces) >= MaxInterfaces {
		return false
	}

	if mtu <= 0 || mtu > MaxPacketSize {
		return false
	}

	if _, exists := s.Interfaces[name]; exists {
		return false
	}

	s.Interfaces[name] = &Interface{
		Name:    name,
		Address: address,
		MTU:     mtu,
		Enabled: true,
	}

	return true
}

// Remove an interface
func (s *Stack) RemoveInterface(name string) bool {
	if s == nil {
		return false
	}

	if _, exists := s.Interfaces[name]; !exists {
		return false
	}

	delete(s.Interfaces, name)
	return true
}

// Enable an interface
func (i *Interface) Enable() {
	if i != nil {
		i.Enabled = true
	}
}

// Disable an interface
func (i *Interface) Disable() {
	if i != nil {
		i.Enabled = false
	}
}

// Set interface MTU
func (i *Interface) SetMTU(mtu int) bool {
	if i == nil || mtu <= 0 || mtu > MaxPacketSize {
		return false
	}

	i.MTU = mtu
	return true
}

// Create a packet
func NewPacket(source Address, destination Address, payload []byte, protocol int) Packet {
	data := make([]byte, len(payload))
	copy(data, payload)

	return Packet{
		Source:      source,
		Destination: destination,
		Payload:     data,
		Length:      len(data),
		Protocol:    protocol,
	}
}

// Validate a packet
func ValidatePacket(packet Packet) bool {
	if packet.Length < 0 {
		return false
	}

	if packet.Length > MaxPacketSize {
		return false
	}

	if packet.Length != len(packet.Payload) {
		return false
	}

	if packet.Destination.Host == "" {
		return false
	}

	return true
}

// Add a routing entry
func (s *Stack) AddRoute(destination string, gateway Address) bool {
	if s == nil || destination == "" || gateway.Host == "" {
		return false
	}

	s.Routes[destination] = gateway
	return true
}

// Find a route
func (s *Stack) FindRoute(destination string) (Address, bool) {
	if s == nil {
		return Address{}, false
	}

	route, exists := s.Routes[destination]
	return route, exists
}

// Save a packet in the stack
func (s *Stack) StorePacket(packet Packet) bool {
	if s == nil || !ValidatePacket(packet) {
		return false
	}

	if len(s.Packets) >= 1024 {
		return false
	}

	s.Packets = append(s.Packets, packet)
	PacketCount++

	return true
}

// Get packet count
func (s *Stack) PacketTotal() int {
	if s == nil {
		return 0
	}

	return len(s.Packets)
}

// Create a configuration
func NewConfiguration(hostname string) Configuration {
	return Configuration{
		Hostname:   hostname,
		Interfaces: make([]Interface, 0),
		Options:    make(map[string]string),
	}
}

// Set a configuration option
func (c *Configuration) SetOption(key string, value string) {
	if c == nil || key == "" {
		return
	}

	c.Options[key] = value
}

// Get a configuration option
func (c Configuration) GetOption(key string) (string, bool) {
	value, exists := c.Options[key]
	return value, exists
}

// Process incoming packets
func (s *Stack) ProcessIncoming() {
	if s == nil {
		return
	}

	for packet := range s.Incoming {
		if !ValidatePacket(packet) {
			println("NetBase: invalid incoming packet")
			continue
		}

		s.StorePacket(packet)
	}
}

// Start packet processing in a goroutine
func (s *Stack) StartWorkers() {
	if s == nil {
		return
	}

	go s.ProcessIncoming()
}

// Submit an incoming packet
func (s *Stack) Submit(packet Packet) bool {
	if s == nil || !s.Running {
		return false
	}

	if !ValidatePacket(packet) {
		return false
	}

	select {
	case s.Incoming <- packet:
		return true
	default:
		return false
	}
}

// Read an outgoing packet
func (s *Stack) ReceiveOutgoing() (Packet, bool) {
	if s == nil {
		return Packet{}, false
	}

	select {
	case packet := <-s.Outgoing:
		return packet, true
	default:
		return Packet{}, false
	}
}

// Print network information
func (s *Stack) PrintInfo() {
	if s == nil {
		println("NetBase: no stack")
		return
	}

	println("Network:", NetworkName)
	println("Version:", NetBaseVersion)
	println("Running:", s.Running)
	println("Interfaces:", len(s.Interfaces))
	println("Routes:", len(s.Routes))
	println("Packets:", len(s.Packets))
}

// Basic array example
func ProtocolTable() [4]int {
	return [4]int{
		1, 6, 17, 58,
	}
}

// Slice example
func CopyPayload(data []byte) []byte {
	result := make([]byte, len(data))
	copy(result, data)
	return result
}

// Basic network worker
func PacketWorker(input <-chan Packet, output chan<- Packet) {
	for packet := range input {
		if ValidatePacket(packet) {
			output <- packet
		} else {
			println("NetBase: packet rejected")
		}
	}
}

// Launch packet worker
func StartPacketWorker() (chan<- Packet, <-chan Packet) {
	input := make(chan Packet, 32)
	output := make(chan Packet, 32)

	go PacketWorker(input, output)

	return input, output
}

// Network test
func TestNetBase() {
	stack := NewStack()

	stack.Start()

	address := Address{
		Host: "127.0.0.1",
		Port: 80,
	}

	stack.AddInterface("loopback", address, DefaultMTU)

	packet := NewPacket(
		address,
		address,
		[]byte("MyLinux NetBase test"),
		6,
	)

	stack.StorePacket(packet)
	stack.PrintInfo()

	stack.Stop()
}
