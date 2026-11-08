package main

import (
"encoding/json"
"fmt"
"mylinux/soong/android"
)

func main() {
host := android.DetectHost()

data, err := json.MarshalIndent(host, "", "  ")
if err != nil {
panic(err)
}

fmt.Println(string(data))
}
