package mylinuxpath

import (
"path/filepath"
"strings"
)

type PathInfo struct {
FullPath  string
Directory string
BaseName  string
Extension string
Absolute  bool
}

func Clean(path string) string {
if path == "" {
return "."
}
return filepath.Clean(path)
}

func Join(parts ...string) string {
return filepath.Join(parts...)
}

func Base(path string) string {
return filepath.Base(Clean(path))
}

func Dir(path string) string {
return filepath.Dir(Clean(path))
}

func Ext(path string) string {
return filepath.Ext(path)
}

func IsAbsolute(path string) bool {
return filepath.IsAbs(path)
}

func Split(path string) (string, string) {
return filepath.Split(path)
}

func Relative(base, target string) (string, error) {
return filepath.Rel(base, target)
}

func ToSlash(path string) string {
return filepath.ToSlash(path)
}

func FromSlash(path string) string {
return filepath.FromSlash(path)
}

func HasPrefix(path, prefix string) bool {
cleanPath := Clean(path)
cleanPrefix := Clean(prefix)

if cleanPath == cleanPrefix {
return true
}

return strings.HasPrefix(
cleanPath,
strings.TrimRight(cleanPrefix, string(filepath.Separator))+string(filepath.Separator),
)
}

func Inspect(path string) PathInfo {
clean := Clean(path)

return PathInfo{
FullPath:  clean,
Directory: filepath.Dir(clean),
BaseName:  filepath.Base(clean),
Extension: filepath.Ext(clean),
Absolute:  filepath.IsAbs(clean),
}
}

func RemoveExtension(path string) string {
ext := filepath.Ext(path)

if ext == "" {
return path
}

return strings.TrimSuffix(path, ext)
}
