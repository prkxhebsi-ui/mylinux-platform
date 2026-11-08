package devices

const (
    DeviceUnknown = iota
    DeviceBlock
    DeviceCharacter
    DeviceNetwork
    DeviceInput
    DeviceOutput
)

type Device struct {
    Name  string
    Path  string
    Type  int
    Major uint32
    Minor uint32
    Active bool
}

type Manager struct {
    Entries map[string]*Device
    Enabled bool
}

func NewManager() *Manager {
    return &Manager{
        Entries: make(map[string]*Device),
        Enabled: true,
    }
}

func (m *Manager) Register(name string, path string, kind int, major uint32, minor uint32) bool {
    if m == nil || !m.Enabled || name == "" || path == "" {
        return false
    }
    if _, exists := m.Entries[name]; exists {
        return false
    }
    m.Entries[name] = &Device{
        Name: name,
        Path: path,
        Type: kind,
        Major: major,
        Minor: minor,
        Active: true,
    }
    return true
}

func (m *Manager) Find(name string) (*Device, bool) {
    if m == nil {
        return nil, false
    }
    device, exists := m.Entries[name]
    return device, exists
}

func (m *Manager) Remove(name string) bool {
    if m == nil {
        return false
    }
    if _, exists := m.Entries[name]; !exists {
        return false
    }
    delete(m.Entries, name)
    return true
}

func (m *Manager) Count() int {
    if m == nil {
        return 0
    }
    return len(m.Entries)
}
