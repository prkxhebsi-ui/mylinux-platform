package cpu

import myos "mylinux/os"

type Information struct {
    Cores       int
    Architecture string
    FrequencyMHz uint64
    Online       bool
}

type Manager struct {
    System  *myos.System
    Info    Information
    Enabled bool
}

func NewManager(system *myos.System) *Manager {
    values := myos.CPUInformation()
    return &Manager{
        System: system,
        Info: Information{
            Cores: values[0],
            Architecture: "arm64",
            FrequencyMHz: 0,
            Online: true,
        },
        Enabled: true,
    }
}

func (m *Manager) SetInformation(cores int, architecture string, frequency uint64) bool {
    if m == nil || cores < 0 || architecture == "" {
        return false
    }
    m.Info.Cores = cores
    m.Info.Architecture = architecture
    m.Info.FrequencyMHz = frequency
    return true
}

func (m *Manager) GetInformation() (Information, bool) {
    if m == nil || !m.Enabled {
        return Information{}, false
    }
    return m.Info, true
}

func (m *Manager) SetOnline(online bool) {
    if m != nil {
        m.Info.Online = online
    }
}
