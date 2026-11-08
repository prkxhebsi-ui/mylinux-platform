package groups

type Group struct {
    GID     uint32
    Name    string
    Members  []uint32
}

type Manager struct {
    Entries map[uint32]*Group
    Names   map[string]uint32
    NextGID uint32
    Enabled bool
}

func NewManager() *Manager {
    return &Manager{
        Entries: make(map[uint32]*Group),
        Names: make(map[string]uint32),
        NextGID: 1000,
        Enabled: true,
    }
}

func (m *Manager) Add(name string) (uint32, bool) {
    if m == nil || !m.Enabled || name == "" {
        return 0, false
    }
    if _, exists := m.Names[name]; exists {
        return 0, false
    }
    gid := m.NextGID
    m.NextGID++
    m.Entries[gid] = &Group{
        GID: gid,
        Name: name,
        Members: make([]uint32, 0),
    }
    m.Names[name] = gid
    return gid, true
}

func (m *Manager) AddMember(gid uint32, uid uint32) bool {
    if m == nil {
        return false
    }
    group, exists := m.Entries[gid]
    if !exists {
        return false
    }
    for _, member := range group.Members {
        if member == uid {
            return false
        }
    }
    group.Members = append(group.Members, uid)
    return true
}

func (m *Manager) RemoveMember(gid uint32, uid uint32) bool {
    if m == nil {
        return false
    }
    group, exists := m.Entries[gid]
    if !exists {
        return false
    }
    for index, member := range group.Members {
        if member == uid {
            group.Members = append(group.Members[:index], group.Members[index+1:]...)
            return true
        }
    }
    return false
}

func (m *Manager) Find(gid uint32) (*Group, bool) {
    if m == nil {
        return nil, false
    }
    group, exists := m.Entries[gid]
    return group, exists
}

func (m *Manager) Count() int {
    if m == nil {
        return 0
    }
    return len(m.Entries)
}
