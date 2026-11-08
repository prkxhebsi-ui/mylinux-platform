package features

// Variables and constants
var GlobalNumber int = 100
const Version int = 1

// Struct
type Computer struct {
    Name string
    RAM  int
}

// Methods
func (c *Computer) SetRAM(value int) {
    c.RAM = value
}

func (c Computer) GetRAM() int {
    return c.RAM
}

// Functions
func Add(a int, b int) int {
    return a + b
}

// If, else and for
func Calculate(value int) int {
    result := 0

    if value > 10 {
        result = value * 2
    } else {
        result = value + 2
    }

    for i := 0; i < 3; i++ {
        result++
    }

    return result
}

// Arrays and slices
func ArrayExample() int {
    var values [3]int
    values[0] = 10
    values[1] = 20
    values[2] = 30

    var total int

    for _, value := range values {
        total += value
    }

    return total
}

func SliceExample() []int {
    values := []int{10, 20, 30}
    values = append(values, 40)
    return values
}

// Maps
func MapExample() int {
    values := make(map[string]int)

    values["CPU"] = 8
    values["RAM"] = 4

    return values["CPU"] + values["RAM"]
}

// Pointers
func PointerExample() int {
    value := 50
    pointer := &value

    *pointer = 75

    return value
}

// Goroutines
func GoroutineExample() {
    go func() {
        println("MyLinux goroutine running")
    }()
}

// Channels
func ChannelExample() int {
    channel := make(chan int)

    go func() {
        channel <- 123
    }()

    return <-channel
}

// Built-in println
func PrintExample() {
    println("MyLinux Go features")
    println("No imports required")
}
