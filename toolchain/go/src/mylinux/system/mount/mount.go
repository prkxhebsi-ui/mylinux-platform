package mount

const (
    FlagReadOnly = 1
    FlagNoSUID   = 2
    FlagNoDevice = 4
    FlagNoExec   = 8
)

type Entry struct {
    Source string
    Target string
    Type   string
    Flags  uint64
    Active bool
}

type Manager struct {
    Entries map[string]*Entry
    Enabled bool
}

func NewManager() *Manager {
    return &Manager{
        Entries: make(map[string]*Entry),
        Enabled: true,
    }
}

func (m *Manager) Mount(source string, target string, kind string, flags uint64) bool {
    if m == nil || !m.Enabled || source == "" || target == "" {
        return false
    }
    if _, exists := m.Entries[target]; exists {
        return false
    }
    m.Entries[target] = &Entry{
        Source: source,
        Target: target,
        Type: kind,
        Flags: flags,
        Active: true,
    }
    return true
}

func (m *Manager) Unmount(target string) bool {
    if m == nil {
        return false
    }
    entry, exists := m.Entries[target]
    if !exists || !entry.Active {
        return false
    }
    entry.Active = false
    delete(m.Entries, target)
    return true
}

func (m *Manager) Find(target string) (*Entry, bool) {
    if m == nil {
        return nil, false
    }
    entry, exists := m.Entries[target]
    return entry, exists
}

func (m *Manager) Count() int {
    if m == nil {
        return 0
    }
    return len(m.Entries)
}
