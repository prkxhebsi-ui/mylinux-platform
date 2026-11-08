package netbase

const (
    DefaultHTTPPort  = 80
    DefaultHTTPSPort = 443
)

func IsValidPort(port int) bool {
    return port > 0 && port <= 65535
}

func IsHTTPS(value string) bool {
    return len(value) >= 8 && value[:8] == "https://"
}

func IsHTTP(value string) bool {
    return len(value) >= 7 && value[:7] == "http://"
}

func NetworkVersion() string {
    return "MyLinux Network 1.0"
}
