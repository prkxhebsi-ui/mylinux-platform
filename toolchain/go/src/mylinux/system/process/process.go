package process

import myos "mylinux/os"

type Manager struct {
    System  *myos.System
    Enabled bool
}

func NewManager(system *myos.System) *Manager {
    return &Manager{System: system, Enabled: true}
}

func (m *Manager) Create(name string, priority int) (int, bool) {
    if m == nil || !m.Enabled || m.System == nil {
        return 0, false
    }
    return m.System.CreateProcess(name, priority)
}

func (m *Manager) Find(pid int) (*myos.Process, bool) {
    if m == nil || m.System == nil {
        return nil, false
    }
    return m.System.FindProcess(pid)
}

func (m *Manager) Terminate(pid int) bool {
    if m == nil || !m.Enabled || m.System == nil {
        return false
    }
    return m.System.TerminateProcess(pid)
}

func (m *Manager) SetPriority(pid int, priority int) bool {
    process, exists := m.Find(pid)
    if !exists {
        return false
    }
    process.SetPriority(priority)
    return true
}

func (m *Manager) SetState(pid int, state int) bool {
    process, exists := m.Find(pid)
    if !exists {
        return false
    }
    return process.SetState(state)
}

func (m *Manager) Count() int {
    if m == nil || m.System == nil {
        return 0
    }
    return m.System.ActiveProcessCount()
}
