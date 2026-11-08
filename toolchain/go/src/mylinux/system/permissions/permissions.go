package permissions

const (
    Read  = 1
    Write = 2
    Execute = 4
)

type Permission struct {
    Owner  string
    Group  string
    Mode   uint32
    Path   string
}

type Manager struct {
    Entries map[string]*Permission
    Enabled bool
}

func NewManager() *Manager {
    return &Manager{
        Entries: make(map[string]*Permission),
        Enabled: true,
    }
}

func (m *Manager) Set(path string, owner string, group string, mode uint32) bool {
    if m == nil || !m.Enabled || path == "" || mode > 07777 {
        return false
    }
    m.Entries[path] = &Permission{
        Path: path,
        Owner: owner,
        Group: group,
        Mode: mode,
    }
    return true
}

func (m *Manager) Get(path string) (*Permission, bool) {
    if m == nil {
        return nil, false
    }
    entry, exists := m.Entries[path]
    return entry, exists
}

func (m *Manager) Check(path string, requested uint32) bool {
    entry, exists := m.Get(path)
    if !exists {
        return false
    }
    return entry.Mode&requested == requested
}

func (m *Manager) Remove(path string) bool {
    if m == nil {
        return false
    }
    if _, exists := m.Entries[path]; !exists {
        return false
    }
    delete(m.Entries, path)
    return true
}
