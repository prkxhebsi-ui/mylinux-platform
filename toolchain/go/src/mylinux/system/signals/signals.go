package signals

const (
    SIGHUP = 1
    SIGINT = 2
    SIGQUIT = 3
    SIGKILL = 9
    SIGTERM = 15
    SIGCHLD = 17
)

type Signal struct {
    Number int
    TargetPID int
    Name string
}

type Manager struct {
    Queue []Signal
    Enabled bool
    MaxQueue int
}

func NewManager() *Manager {
    return &Manager{
        Queue: make([]Signal, 0),
        Enabled: true,
        MaxQueue: 128,
    }
}

func (m *Manager) Send(pid int, number int, name string) bool {
    if m == nil || !m.Enabled || pid <= 0 || number <= 0 {
        return false
    }
    if len(m.Queue) >= m.MaxQueue {
        return false
    }
    m.Queue = append(m.Queue, Signal{
        Number: number,
        TargetPID: pid,
        Name: name,
    })
    return true
}

func (m *Manager) Receive() (Signal, bool) {
    if m == nil || len(m.Queue) == 0 {
        return Signal{}, false
    }
    signal := m.Queue[0]
    m.Queue = m.Queue[1:]
    return signal, true
}

func (m *Manager) Pending() int {
    if m == nil {
        return 0
    }
    return len(m.Queue)
}
