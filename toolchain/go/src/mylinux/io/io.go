package mylinuxio

const (
    IOVersion  = "1.0"
    MaxIOSize  = 1048576
    DefaultBuf = 4096
)

var (
    IOEnabled bool = true
    IOCount   uint64
)

type Buffer struct {
    Data     []byte
    Position int
}

type Stream struct {
    Input  chan []byte
    Output chan []byte
    Closed bool
}

type IOResult struct {
    Data  []byte
    Size  int
    Error bool
}

func NewBuffer() *Buffer {
    return &Buffer{
        Data: make([]byte, 0),
    }
}

func NewBufferSize(size int) *Buffer {
    if size < 0 || size > MaxIOSize {
        size = DefaultBuf
    }

    return &Buffer{
        Data: make([]byte, 0, size),
    }
}

func (b *Buffer) Write(data []byte) int {
    if b == nil || len(data) == 0 {
        return 0
    }

    if len(b.Data)+len(data) > MaxIOSize {
        return 0
    }

    b.Data = append(b.Data, data...)
    IOCount += uint64(len(data))

    return len(data)
}

func (b *Buffer) Read(size int) []byte {
    if b == nil || size <= 0 || b.Position >= len(b.Data) {
        return nil
    }

    end := b.Position + size

    if end > len(b.Data) {
        end = len(b.Data)
    }

    result := make([]byte, end-b.Position)
    copy(result, b.Data[b.Position:end])

    b.Position = end
    return result
}

func (b *Buffer) Bytes() []byte {
    if b == nil {
        return nil
    }

    result := make([]byte, len(b.Data))
    copy(result, b.Data)
    return result
}

func (b *Buffer) Reset() {
    if b == nil {
        return
    }

    b.Data = b.Data[:0]
    b.Position = 0
}

func (b *Buffer) Rewind() {
    if b != nil {
        b.Position = 0
    }
}

func (b *Buffer) Len() int {
    if b == nil {
        return 0
    }

    return len(b.Data)
}

func (b *Buffer) Remaining() int {
    if b == nil {
        return 0
    }

    return len(b.Data) - b.Position
}

func CopyBuffer(destination *Buffer, source *Buffer) int {
    if destination == nil || source == nil {
        return 0
    }

    return destination.Write(source.Bytes())
}

func NewStream(size int) *Stream {
    if size <= 0 {
        size = DefaultBuf
    }

    return &Stream{
        Input:  make(chan []byte, size),
        Output: make(chan []byte, size),
    }
}

func (s *Stream) Send(data []byte) bool {
    if s == nil || s.Closed {
        return false
    }

    copied := make([]byte, len(data))
    copy(copied, data)

    select {
    case s.Input <- copied:
        return true
    default:
        return false
    }
}

func (s *Stream) Receive() ([]byte, bool) {
    if s == nil || s.Closed {
        return nil, false
    }

    select {
    case data := <-s.Output:
        return data, true
    default:
        return nil, false
    }
}

func (s *Stream) Close() {
    if s == nil || s.Closed {
        return
    }

    s.Closed = true
    close(s.Input)
}

func StreamWorker(s *Stream) {
    if s == nil {
        return
    }

    for data := range s.Input {
        copied := make([]byte, len(data))
        copy(copied, data)

        select {
        case s.Output <- copied:
        default:
            println("MyLinux IO: output buffer full")
        }
    }
}

func (s *Stream) StartWorker() bool {
    if s == nil || s.Closed {
        return false
    }

    go StreamWorker(s)
    return true
}

func ReadAllChunks(chunks <-chan []byte, output chan<- IOResult) {
    for chunk := range chunks {
        copied := make([]byte, len(chunk))
        copy(copied, chunk)

        output <- IOResult{
            Data: copied,
            Size: len(copied),
        }
    }
}

func StartReaderWorker() (chan []byte, <-chan IOResult) {
    input := make(chan []byte, 32)
    output := make(chan IOResult, 32)

    go ReadAllChunks(input, output)

    return input, output
}

func PrintIOInfo() {
    println("MyLinux IO")
    println("Version:", IOVersion)
    println("Enabled:", IOEnabled)
    println("Bytes processed:", IOCount)
}

func TestIO() {
    buffer := NewBuffer()

    buffer.Write([]byte("Hello MyLinux IO"))

    println("Buffer size:", buffer.Len())
    println("Buffer data:", string(buffer.Bytes()))

    buffer.Rewind()

    println("Read:", string(buffer.Read(5)))
}
