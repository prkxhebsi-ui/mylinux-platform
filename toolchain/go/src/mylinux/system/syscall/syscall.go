package syscall

const (
    SYS_GETPID  = 172
    SYS_GETUID  = 174
    SYS_GETGID  = 176
    SYS_MOUNT   = 40
    SYS_UMOUNT2 = 39
)

const (
    StatePending = iota
    StateRunning
    StateComplete
    StateFailed
)

type Request struct {
    Number uint64
    Arg1   uint64
    Arg2   uint64
    Arg3   uint64
    Arg4   uint64
    Arg5   uint64
    Arg6   uint64
}

type Result struct {
    Value  int64
    Error  int64
    State  int
    Name   string
}

type Dispatcher struct {
    Requests  []Request
    Results   []Result
    Enabled   bool
    MaxCalls  int
}

func NewDispatcher() *Dispatcher {
    return &Dispatcher{
        Requests: make([]Request, 0),
        Results:  make([]Result, 0),
        Enabled:  true,
        MaxCalls: 256,
    }
}

func (d *Dispatcher) Submit(request Request) bool {
    if d == nil || !d.Enabled || len(d.Requests) >= d.MaxCalls {
        return false
    }
    d.Requests = append(d.Requests, request)
    return true
}

func (d *Dispatcher) LastRequest() (Request, bool) {
    if d == nil || len(d.Requests) == 0 {
        return Request{}, false
    }
    return d.Requests[len(d.Requests)-1], true
}

func (d *Dispatcher) RecordResult(result Result) bool {
    if d == nil || len(d.Results) >= d.MaxCalls {
        return false
    }
    d.Results = append(d.Results, result)
    return true
}

func (d *Dispatcher) Clear() {
    if d == nil {
        return
    }
    d.Requests = make([]Request, 0)
    d.Results = make([]Result, 0)
}

func (d *Dispatcher) Count() int {
    if d == nil {
        return 0
    }
    return len(d.Requests)
}
