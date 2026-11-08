package network

import (
    "errors"
    "net/http"
    "time"
)

func HTTPSGet(url string) (*http.Response, error) {
    if !CheckHTTPS(url) {
        return nil, errors.New("HTTPS URL required")
    }

    client := &http.Client{
        Timeout: 20 * time.Second,
    }

    return client.Get(url)
}
