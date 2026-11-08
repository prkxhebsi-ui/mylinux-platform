package android

import "testing"

func TestDetectHost(t *testing.T) {
	host := DetectHost()

	if host.OS == "" {
		t.Fatal("host OS was not detected")
	}

	if host.Architecture == "" {
		t.Fatal("host architecture was not detected")
	}

	if host.Platform == "" {
		t.Fatal("host platform was not detected")
	}

	if host.Tools == nil {
		t.Fatal("host tools map was not initialized")
	}
}

func TestHostToolLookup(t *testing.T) {
	host := DetectHost()

	if host.HasTool("this-tool-should-not-exist-mylinux") {
		t.Fatal("nonexistent tool was detected")
	}

	if host.ToolPath("this-tool-should-not-exist-mylinux") != "" {
		t.Fatal("nonexistent tool has a path")
	}
}
