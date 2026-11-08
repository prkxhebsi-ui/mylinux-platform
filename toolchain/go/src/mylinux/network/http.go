package network

import (
    "io"
    "net/http"
    "time"
)

func HTTPGet(url string) (string, error) {
    client := &http.Client{
        Timeout: 15 * time.Second,
    }

    response, err := client.Get(url)
    if err != nil {
        return "", err
    }
    defer response.Body.Close()

    data, err := io.ReadAll(response.Body)
    if err != nil {
        return "", err
    }

    return string(data), nil
}
