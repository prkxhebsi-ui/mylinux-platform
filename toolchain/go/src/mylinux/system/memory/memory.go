package memory

type Region struct {
    Name      string
    Start     uint64
    Size      uint64
    Used      uint64
    Available uint64
}

type Manager struct {
    Regions map[string]*Region
    Enabled bool
}

func NewManager() *Manager {
    return &Manager{
        Regions: make(map[string]*Region),
        Enabled: true,
    }
}

func (m *Manager) Register(name string, start uint64, size uint64) bool {
    if m == nil || !m.Enabled || name == "" || size == 0 {
        return false
    }
    if _, exists := m.Regions[name]; exists {
        return false
    }
    m.Regions[name] = &Region{
        Name: name,
        Start: start,
        Size: size,
        Used: 0,
        Available: size,
    }
    return true
}

func (m *Manager) Allocate(name string, amount uint64) bool {
    if m == nil {
        return false
    }
    region, exists := m.Regions[name]
    if !exists || amount > region.Available {
        return false
    }
    region.Used += amount
    region.Available -= amount
    return true
}

func (m *Manager) Release(name string, amount uint64) bool {
    if m == nil {
        return false
    }
    region, exists := m.Regions[name]
    if !exists || amount > region.Used {
        return false
    }
    region.Used -= amount
    region.Available += amount
    return true
}

func (m *Manager) Total() uint64 {
    if m == nil {
        return 0
    }
    var total uint64
    for _, region := range m.Regions {
        total += region.Size
    }
    return total
}

func (m *Manager) Used() uint64 {
    if m == nil {
        return 0
    }
    var total uint64
    for _, region := range m.Regions {
        total += region.Used
    }
    return total
}
