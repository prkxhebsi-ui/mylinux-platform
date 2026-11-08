package environment

import myos "mylinux/os"

type Manager struct {
    System  *myos.System
    Enabled bool
}

func NewManager(system *myos.System) *Manager {
    return &Manager{System: system, Enabled: true}
}

func (m *Manager) Set(name string, value string) bool {
    if m == nil || !m.Enabled || m.System == nil {
        return false
    }
    return m.System.SetEnvironment(name, value)
}

func (m *Manager) Get(name string) (string, bool) {
    if m == nil || m.System == nil {
        return "", false
    }
    return m.System.GetEnvironment(name)
}

func (m *Manager) Delete(name string) bool {
    if m == nil || m.System == nil {
        return false
    }
    return m.System.DeleteEnvironment(name)
}

func (m *Manager) Count() int {
    if m == nil || m.System == nil {
        return 0
    }
    return len(m.System.Environment)
}
