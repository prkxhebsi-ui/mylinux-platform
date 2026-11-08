package properties

const (
    MaxProperties = 512
)

type Property struct {
    Name  string
    Value string
    ReadOnly bool
}

type Manager struct {
    Entries map[string]*Property
    Enabled bool
}

func NewManager() *Manager {
    return &Manager{
        Entries: make(map[string]*Property),
        Enabled: true,
    }
}

func (m *Manager) Set(name string, value string) bool {
    if m == nil || !m.Enabled || name == "" {
        return false
    }
    property, exists := m.Entries[name]
    if exists && property.ReadOnly {
        return false
    }
    if !exists && len(m.Entries) >= MaxProperties {
        return false
    }
    m.Entries[name] = &Property{
        Name: name,
        Value: value,
    }
    return true
}

func (m *Manager) Get(name string) (string, bool) {
    if m == nil {
        return "", false
    }
    property, exists := m.Entries[name]
    if !exists {
        return "", false
    }
    return property.Value, true
}

func (m *Manager) SetReadOnly(name string, readOnly bool) bool {
    if m == nil {
        return false
    }
    property, exists := m.Entries[name]
    if !exists {
        return false
    }
    property.ReadOnly = readOnly
    return true
}

func (m *Manager) Remove(name string) bool {
    if m == nil {
        return false
    }
    property, exists := m.Entries[name]
    if !exists || property.ReadOnly {
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
