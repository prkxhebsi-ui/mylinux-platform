package users

type User struct {
    UID      uint32
    Name     string
    Home     string
    Shell    string
    GroupID  uint32
    Active   bool
}

type Manager struct {
    Entries map[uint32]*User
    Names   map[string]uint32
    NextUID uint32
    Enabled bool
}

func NewManager() *Manager {
    return &Manager{
        Entries: make(map[uint32]*User),
        Names: make(map[string]uint32),
        NextUID: 1000,
        Enabled: true,
    }
}

func (m *Manager) Add(name string, home string, shell string, gid uint32) (uint32, bool) {
    if m == nil || !m.Enabled || name == "" {
        return 0, false
    }
    if _, exists := m.Names[name]; exists {
        return 0, false
    }
    uid := m.NextUID
    m.NextUID++
    m.Entries[uid] = &User{
        UID: uid,
        Name: name,
        Home: home,
        Shell: shell,
        GroupID: gid,
        Active: true,
    }
    m.Names[name] = uid
    return uid, true
}

func (m *Manager) FindUID(uid uint32) (*User, bool) {
    if m == nil {
        return nil, false
    }
    user, exists := m.Entries[uid]
    return user, exists
}

func (m *Manager) FindName(name string) (*User, bool) {
    if m == nil {
        return nil, false
    }
    uid, exists := m.Names[name]
    if !exists {
        return nil, false
    }
    return m.FindUID(uid)
}

func (m *Manager) Remove(uid uint32) bool {
    user, exists := m.FindUID(uid)
    if !exists {
        return false
    }
    delete(m.Names, user.Name)
    delete(m.Entries, uid)
    return true
}

func (m *Manager) Count() int {
    if m == nil {
        return 0
    }
    return len(m.Entries)
}
