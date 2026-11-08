package android

import (
	"os"
	"os/exec"
	"path/filepath"
	"runtime"
	"strings"
)

type HostTool struct {
	Name  string `json:"name"`
	Path  string `json:"path"`
	Found bool   `json:"found"`
}

type HostInfo struct {
	OS           string              `json:"os"`
	Architecture string              `json:"architecture"`
	Platform     string              `json:"platform"`
	IsTermux     bool                `json:"is_termux"`
	TermuxPrefix string              `json:"termux_prefix,omitempty"`
	Tools        map[string]HostTool `json:"tools"`
}

var hostToolNames = []string{
	"clang",
	"clang++",
	"ld.lld",
	"llvm-ar",
	"llvm-nm",
	"llvm-objcopy",
	"llvm-readelf",
	"llvm-strip",
	"make",
	"ninja",
	"python",
	"python3",
	"go",
	"git",
	"cmake",
}

func DetectHost() HostInfo {
	host := HostInfo{
		OS:           runtime.GOOS,
		Architecture: runtime.GOARCH,
		Tools:        make(map[string]HostTool),
	}

	prefix := os.Getenv("PREFIX")
	termuxVersion := os.Getenv("TERMUX_VERSION")

	host.IsTermux = termuxVersion != "" ||
		strings.Contains(prefix, "/com.termux/")

	if host.IsTermux {
		host.Platform = "android-" + runtime.GOARCH + "-termux"
		host.TermuxPrefix = prefix
	} else {
		host.Platform = runtime.GOOS + "-" + runtime.GOARCH
	}

	for _, name := range hostToolNames {
		path, err := exec.LookPath(name)

		tool := HostTool{
			Name:  name,
			Found: err == nil,
		}

		if err == nil {
			tool.Path, _ = filepath.Abs(path)
		}

		host.Tools[name] = tool
	}

	return host
}

func (h HostInfo) HasTool(name string) bool {
	tool, ok := h.Tools[name]
	return ok && tool.Found
}

func (h HostInfo) ToolPath(name string) string {
	tool, ok := h.Tools[name]
	if !ok || !tool.Found {
		return ""
	}
	return tool.Path
}
