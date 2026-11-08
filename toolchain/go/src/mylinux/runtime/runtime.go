package runtime

const (
    RuntimeName    = "MyLinux Runtime"
    RuntimeVersion = "1.0"
    MaxModules     = 128
    MaxTasks       = 256
)

var (
    RuntimeActive bool
    RuntimeID     uint64
)

type Module struct {
    Name    string
    Version string
    Loaded  bool
}

type RuntimeTask struct {
    ID       int
    Name     string
    Priority int
    Data     []byte
}

type RuntimeResult struct {
    ID      int
    Success bool
    Message string
}

type Runtime struct {
    Active  bool
    Modules map[string]*Module
    Tasks   chan RuntimeTask
    Results chan RuntimeResult
    Stop    chan struct{}
}

func NewRuntime() *Runtime {
    return &Runtime{
        Active:  false,
        Modules: make(map[string]*Module),
        Tasks:   make(chan RuntimeTask, MaxTasks),
        Results: make(chan RuntimeResult, MaxTasks),
        Stop:    make(chan struct{}),
    }
}

func (r *Runtime) Start() bool {
    if r == nil || r.Active {
        return false
    }

    r.Active = true
    RuntimeActive = true
    RuntimeID++

    println(RuntimeName, "started")
    return true
}

func (r *Runtime) Shutdown() {
    if r == nil {
        return
    }

    r.Active = false
    RuntimeActive = false

    println(RuntimeName, "shutdown")
}

func (r *Runtime) RegisterModule(name string, version string) bool {
    if r == nil || name == "" {
        return false
    }

    if len(r.Modules) >= MaxModules {
        if _, exists := r.Modules[name]; !exists {
            return false
        }
    }

    r.Modules[name] = &Module{
        Name:    name,
        Version: version,
        Loaded:  true,
    }

    return true
}

func (r *Runtime) FindModule(name string) (*Module, bool) {
    if r == nil {
        return nil, false
    }

    module, exists := r.Modules[name]
    return module, exists
}

func (r *Runtime) UnregisterModule(name string) bool {
    if r == nil {
        return false
    }

    if _, exists := r.Modules[name]; !exists {
        return false
    }

    delete(r.Modules, name)
    return true
}

func (r *Runtime) SubmitTask(task RuntimeTask) bool {
    if r == nil || !r.Active {
        return false
    }

    select {
    case r.Tasks <- task:
        return true
    default:
        return false
    }
}

func (r *Runtime) TaskWorker() {
    if r == nil {
        return
    }

    for {
        select {
        case task := <-r.Tasks:
            result := RuntimeResult{
                ID:      task.ID,
                Success: true,
                Message: "Runtime task processed",
            }

            select {
            case r.Results <- result:
            default:
                println("Runtime result queue full")
            }

        case <-r.Stop:
            return
        }
    }
}

func (r *Runtime) StartWorker() bool {
    if r == nil || !r.Active {
        return false
    }

    go r.TaskWorker()
    return true
}

func (r *Runtime) StopWorker() {
    if r == nil {
        return
    }

    select {
    case r.Stop <- struct{}{}:
    default:
    }
}

func (r *Runtime) GetResult() (RuntimeResult, bool) {
    if r == nil {
        return RuntimeResult{}, false
    }

    select {
    case result := <-r.Results:
        return result, true
    default:
        return RuntimeResult{}, false
    }
}

func (r *Runtime) ModuleCount() int {
    if r == nil {
        return 0
    }

    return len(r.Modules)
}

func (r *Runtime) PrintInfo() {
    if r == nil {
        println("Runtime unavailable")
        return
    }

    println("Runtime:", RuntimeName)
    println("Version:", RuntimeVersion)
    println("Active:", r.Active)
    println("Modules:", len(r.Modules))
}
