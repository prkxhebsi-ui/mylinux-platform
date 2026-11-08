#include "SocketServer.h"
#include "SocketClient.h"
#include "SocketIO.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <thread>
#include <unistd.h>

using namespace mylinux::socket;

int main() {
    const char* temp = std::getenv("TMPDIR");

    std::string directory =
        (temp && temp[0]) ? temp : "/data/local/tmp";

    if (!directory.empty() && directory.back() == '/') {
        directory.pop_back();
    }

    const std::string path =
        directory + "/mylinux-socket-" +
        std::to_string(static_cast<long long>(getpid())) +
        ".sock";

    SocketServer server;

    SocketResult started = server.Start(path, 8);

    if (!started.Success()) {
        std::fprintf(
            stderr,
            "Server start failed: status=%u errno=%d\n",
            static_cast<unsigned>(started.status),
            started.system_error
        );
        return 1;
    }

    assert(server.IsListening());

    bool server_ok = false;

    std::thread worker([&]() {
        SocketFD client;

        SocketResult accepted = server.Accept(&client);

        if (!accepted.Success()) {
            return;
        }

        char request[4] = {};

        SocketResult received = SocketIO::ReceiveExact(
            client.Get(),
            request,
            sizeof(request),
            nullptr
        );

        if (!received.Success()) {
            return;
        }

        if (request[0] != 'P' ||
            request[1] != 'I' ||
            request[2] != 'N' ||
            request[3] != 'G') {
            return;
        }

        const char response[] = {'P', 'O', 'N', 'G'};

        SocketResult sent = SocketIO::SendAll(
            client.Get(),
            response,
            sizeof(response),
            nullptr
        );

        server_ok = sent.Success();
    });

    SocketClient client;

    SocketResult connected = client.Connect(path);

    if (!connected.Success()) {
        std::fprintf(
            stderr,
            "Client connect failed: errno=%d\n",
            connected.system_error
        );

        worker.join();
        server.Stop();
        return 1;
    }

    const char request[] = {'P', 'I', 'N', 'G'};

    SocketResult sent = SocketIO::SendAll(
        client.GetHandle(),
        request,
        sizeof(request),
        nullptr
    );

    if (!sent.Success()) {
        worker.join();
        server.Stop();
        return 1;
    }

    char response[4] = {};

    SocketResult received = SocketIO::ReceiveExact(
        client.GetHandle(),
        response,
        sizeof(response),
        nullptr
    );

    worker.join();

    bool response_ok =
        received.Success() &&
        response[0] == 'P' &&
        response[1] == 'O' &&
        response[2] == 'N' &&
        response[3] == 'G';

    client.Disconnect();
    server.Stop();

    if (!server_ok || !response_ok) {
        std::puts("SOCKET TEST FAILED");
        return 1;
    }

    std::puts("Socket creation: PASS");
    std::puts("bind(): PASS");
    std::puts("listen(): PASS");
    std::puts("accept(): PASS");
    std::puts("connect(): PASS");
    std::puts("send(): PASS");
    std::puts("recv(): PASS");
    std::puts("Socket cleanup: PASS");
    std::puts("ALL SOCKET TESTS PASSED");

    return 0;
}
