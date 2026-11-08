package filesystem

const (
    TypeUnknown = iota
    TypeRoot
    TypeSystem
    TypeData
    TypeCache
    TypeTemporary
)

type MountPoint struct {
    Path       string
    Device     string
    Type       int
    ReadOnly   bool
    Mounted    bool
}

type Manager struct {
    Mounts  map[string]*MountPoint
    Enabled bool
}

func NewManager() *Manager {
    return &Manager{
        Mounts:  make(map[string]*MountPoint),
        Enabled: true,
    }
}

func (m *Manager) Register(path string, device string, kind int, readOnly bool) bool {
    if m == nil || !m.Enabled || path == "" {
        return false
    }
    if _, exists := m.Mounts[path]; exists {
        return false
    }
    m.Mounts[path] = &MountPoint{
        Path: path,
        Device: device,
        Type: kind,
        ReadOnly: readOnly,
        Mounted: false,
    }
    return true
}

func (m *Manager) Find(path string) (*MountPoint, bool) {
    if m == nil {
        return nil, false
    }
    point, exists := m.Mounts[path]
    return point, exists
}

func (m *Manager) SetMounted(path string, mounted bool) bool {
    point, exists := m.Find(path)
    if !exists {
        return false
    }
    point.Mounted = mounted
    return true
}

func (m *Manager) Remove(path string) bool {
    if m == nil {
        return false
    }
    if _, exists := m.Mounts[path]; !exists {
        return false
    }
    delete(m.Mounts, path)
    return true
}

func (m *Manager) Count() int {
    if m == nil {
        return 0
    }
    return len(m.Mounts)
}
