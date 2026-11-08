#include "MessageEncoder.h"
#include "MessageDecoder.h"
#include "MessageQueue.h"
#include "Request.h"
#include "Response.h"
#include "SocketDispatcher.h"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace mylinux::socket::protocol;

static void TestEncodeDecode() {
    Message original;
    original.header.type = MessageType::Event;
    original.header.message_id = 42;
    original.header.flags = 7;
    original.payload = {'H', 'E', 'L', 'L', 'O'};
    original.header.payload_length =
        static_cast<uint32_t>(original.payload.size());

    std::vector<uint8_t> frame;
    std::string error;
    assert(MessageEncoder::Encode(original, &frame, &error));
    assert(frame.size() == kWireHeaderSize + 5);

    Message decoded;
    assert(MessageDecoder::DecodeFrame(frame, &decoded, &error));
    assert(decoded.header.message_id == 42);
    assert(decoded.header.flags == 7);
    assert(decoded.payload == original.payload);

    std::cout << "Encode/decode: PASS\n";
}

static void TestInvalidFrames() {
    Message message;
    message.header.type = MessageType::Event;
    message.header.message_id = 9;
    message.payload = {1, 2, 3};
    message.header.payload_length = 3;

    std::vector<uint8_t> frame;
    assert(MessageEncoder::Encode(message, &frame));

    frame.push_back(0xFF);
    Message decoded;
    std::string error;
    assert(!MessageDecoder::DecodeFrame(frame, &decoded, &error));

    Message invalid;
    invalid.header.message_id = 0;
    assert(!invalid.Validate());

    std::cout << "Invalid frame rejection: PASS\n";
}

static void TestRequestResponse() {
    Request request;
    request.id = 100;
    request.payload = {8, 9, 10};

    Message request_message = request.ToMessage();
    assert(request_message.Validate());

    Request restored;
    assert(Request::FromMessage(request_message, &restored));
    assert(restored.id == 100);
    assert(restored.payload == request.payload);

    Response response;
    response.id = 100;
    response.status = 200;
    response.payload = {'O', 'K'};

    Message response_message = response.ToMessage();
    assert(response_message.Validate());

    Response restored_response;
    assert(Response::FromMessage(response_message, &restored_response));
    assert(restored_response.id == 100);
    assert(restored_response.status == 200);
    assert(restored_response.payload == response.payload);

    std::cout << "Request/response: PASS\n";
}

static void TestQueue() {
    MessageQueue queue(2);

    Message message;
    message.header.type = MessageType::Event;
    message.header.message_id = 1;

    assert(queue.Push(message));
    assert(queue.Size() == 1);

    Message popped;
    assert(queue.TryPop(&popped));
    assert(popped.header.message_id == 1);
    assert(!queue.TryPop(&popped));

    queue.Close();
    assert(queue.IsClosed());
    assert(!queue.Push(message));

    std::cout << "Message queue: PASS\n";
}

static void TestDispatcher() {
    SocketDispatcher dispatcher;

    constexpr uint32_t kEchoCommand = 0x00000001U;
    assert(dispatcher.Register(kEchoCommand,
        [](const Request& request) {
            Response response;
            response.status = 0;
            response.payload = request.payload;
            return response;
        }));

    Request request;
    request.id = 777;
    request.payload = {
        0, 0, 0, 1, // command ID
        'P', 'I', 'N', 'G'
    };

    Message response_message;
    std::string error;
    assert(dispatcher.Dispatch(request.ToMessage(),
                               &response_message, &error));

    Response response;
    assert(Response::FromMessage(response_message, &response));
    assert(response.id == 777);
    assert(response.status == 0);
    assert((response.payload == std::vector<uint8_t>{'P', 'I', 'N', 'G'}));

    assert(dispatcher.Unregister(kEchoCommand));

    std::cout << "Socket dispatcher: PASS\n";
}

int main() {
    TestEncodeDecode();
    TestInvalidFrames();
    TestRequestResponse();
    TestQueue();
    TestDispatcher();

    std::cout << "ALL PROTOCOL TESTS PASSED\n";
    return 0;
}
