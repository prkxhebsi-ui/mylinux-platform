package fileops

import (
    hostio "io"
    hostos "os"
    "path/filepath"

    "mylinux/features"
    "mylinux/net/netbase"
    "mylinux/os"
    mylinuxfmt "mylinux/fmt"
    myruntime "mylinux/runtime"
    "mylinux/crypto"
    mylinuxio "mylinux/io"
)

const (
    FileOpsVersion = "1.0"
    MaxFileSize    = 67108864
)

var (
    FileOpsEnabled = true
    FilesProcessed uint64
)

type FileInfo struct {
    Name      string
    Path      string
    Size      int64
    Directory bool
    Mode      uint32
}

type FileManager struct {
    Runtime *myruntime.Runtime
    System  *mylinuxos.System
    Enabled bool
    Options map[string]string
}

// Initialize file operations and MyLinux dependencies
func NewFileManager() *FileManager {
    runtime := myruntime.NewRuntime()
    runtime.Start()
    runtime.RegisterModule("fileops", FileOpsVersion)

    system := mylinuxos.NewSystem("mylinux-fileops")
    system.Start()

    network := netbase.NewStack()
    network.Start()
    network.Stop()

    mylinuxfmt.PrintSystem()
    mylinuxio.PrintIOInfo()

    println("MyLinux feature test:", features.Add(10, 20))
    println("MyLinux checksum test:", crypto.Checksum([]byte("fileops")))

    return &FileManager{
        Runtime: runtime,
        System:  system,
        Enabled: true,
        Options: make(map[string]string),
    }
}

// Enable file operations
func (m *FileManager) Enable() {
    if m != nil {
        m.Enabled = true
    }
}

// Disable file operations
func (m *FileManager) Disable() {
    if m != nil {
        m.Enabled = false
    }
}

// Read a file
func ReadFile(path string) ([]byte, error) {
    if path == "" {
        return nil, hostos.ErrInvalid
    }

    data, err := hostos.ReadFile(path)
    if err != nil {
        return nil, err
    }

    if len(data) > MaxFileSize {
        return nil, hostos.ErrInvalid
    }

    buffer := mylinuxio.NewBuffer()
    buffer.Write(data)

    FilesProcessed++

    return buffer.Bytes(), nil
}

// Write a file
func WriteFile(path string, data []byte, mode hostos.FileMode) error {
    if path == "" || len(data) > MaxFileSize {
        return hostos.ErrInvalid
    }

    buffer := mylinuxio.NewBuffer()
    buffer.Write(data)

    err := hostos.WriteFile(path, buffer.Bytes(), mode)
    if err == nil {
        FilesProcessed++
    }

    return err
}

// Append data to a file
func AppendFile(path string, data []byte, mode hostos.FileMode) error {
    if path == "" {
        return hostos.ErrInvalid
    }

    file, err := hostos.OpenFile(
        path,
        hostos.O_CREATE|hostos.O_WRONLY|hostos.O_APPEND,
        mode,
    )

    if err != nil {
        return err
    }

    _, writeErr := file.Write(data)
    closeErr := file.Close()

    if writeErr != nil {
        return writeErr
    }

    if closeErr != nil {
        return closeErr
    }

    FilesProcessed++
    return nil
}

// Copy a file
func CopyFile(source string, destination string) (int64, error) {
    if source == "" || destination == "" {
        return 0, hostos.ErrInvalid
    }

    input, err := hostos.Open(source)
    if err != nil {
        return 0, err
    }
    defer input.Close()

    output, err := hostos.Create(destination)
    if err != nil {
        return 0, err
    }

    size, copyErr := hostio.Copy(output, input)
    closeErr := output.Close()

    if copyErr != nil {
        return size, copyErr
    }

    if closeErr != nil {
        return size, closeErr
    }

    FilesProcessed++
    return size, nil
}

// Create a directory and parent directories
func CreateDirectory(path string, mode hostos.FileMode) error {
    if path == "" {
        return hostos.ErrInvalid
    }

    return hostos.MkdirAll(path, mode)
}

// Remove a file
func RemoveFile(path string) error {
    if path == "" {
        return hostos.ErrInvalid
    }

    err := hostos.Remove(path)
    if err == nil {
        FilesProcessed++
    }

    return err
}

// Remove a directory tree
func RemoveTree(path string) error {
    if path == "" || filepath.Clean(path) == "." {
        return hostos.ErrInvalid
    }

    return hostos.RemoveAll(path)
}

// Rename a file or directory
func Rename(source string, destination string) error {
    if source == "" || destination == "" {
        return hostos.ErrInvalid
    }

    return hostos.Rename(source, destination)
}

// Check whether a path exists
func Exists(path string) bool {
    if path == "" {
        return false
    }

    _, err := hostos.Stat(path)
    return err == nil
}

// Get information about a file
func Stat(path string) (FileInfo, error) {
    info, err := hostos.Stat(path)
    if err != nil {
        return FileInfo{}, err
    }

    return FileInfo{
        Name:      info.Name(),
        Path:      path,
        Size:      info.Size(),
        Directory: info.IsDir(),
        Mode:      uint32(info.Mode()),
    }, nil
}

// List directory entries
func ListDirectory(path string) ([]string, error) {
    entries, err := hostos.ReadDir(path)
    if err != nil {
        return nil, err
    }

    names := make([]string, 0, len(entries))

    for _, entry := range entries {
        names = append(names, entry.Name())
    }

    return names, nil
}

// Change file permissions
func ChangePermissions(path string, mode hostos.FileMode) error {
    if path == "" {
        return hostos.ErrInvalid
    }

    return hostos.Chmod(path, mode)
}

// Read a file into a MyLinux IO buffer
func ReadIntoBuffer(path string, buffer *mylinuxio.Buffer) error {
    if buffer == nil {
        return hostos.ErrInvalid
    }

    data, err := ReadFile(path)
    if err != nil {
        return err
    }

    buffer.Reset()
    buffer.Write(data)

    return nil
}

// Write a MyLinux IO buffer to a file
func WriteBuffer(path string, buffer *mylinuxio.Buffer, mode hostos.FileMode) error {
    if buffer == nil {
        return hostos.ErrInvalid
    }

    return WriteFile(path, buffer.Bytes(), mode)
}

// Manager file read
func (m *FileManager) Read(path string) ([]byte, error) {
    if m == nil || !m.Enabled {
        return nil, hostos.ErrPermission
    }

    return ReadFile(path)
}

// Manager file write
func (m *FileManager) Write(path string, data []byte) error {
    if m == nil || !m.Enabled {
        return hostos.ErrPermission
    }

    return WriteFile(path, data, 0644)
}

// Manager file copy
func (m *FileManager) Copy(source string, destination string) (int64, error) {
    if m == nil || !m.Enabled {
        return 0, hostos.ErrPermission
    }

    return CopyFile(source, destination)
}

// Set manager option
func (m *FileManager) SetOption(name string, value string) {
    if m == nil || name == "" {
        return
    }

    m.Options[name] = value
}

// Get manager option
func (m *FileManager) GetOption(name string) (string, bool) {
    if m == nil {
        return "", false
    }

    value, exists := m.Options[name]
    return value, exists
}

// Print file operations information
func (m *FileManager) PrintInfo() {
    if m == nil {
        println("File manager unavailable")
        return
    }

    println("Subsystem: MyLinux FileOps")
    println("Version:", FileOpsVersion)
    println("Enabled:", m.Enabled)
    println("Files processed:", FilesProcessed)

    if m.Runtime != nil {
        m.Runtime.PrintInfo()
    }
}

// Demonstration
func TestFileOps() {
    manager := NewFileManager()

    path := "mylinux-fileops-test.txt"
    content := []byte("Hello from MyLinux FileOps\n")

    err := manager.Write(path, content)
    if err != nil {
        println("Write failed:", err.Error())
        return
    }

    data, err := manager.Read(path)
    if err != nil {
        println("Read failed:", err.Error())
        return
    }

    println("File contents:", string(data))

    info, err := Stat(path)
    if err == nil {
        println("File name:", info.Name)
        println("File size:", info.Size)
    }

    manager.PrintInfo()

    err = RemoveFile(path)
    if err != nil {
        println("Remove failed:", err.Error())
    }

    manager.System.Stop()
    manager.Runtime.Shutdown()
}
