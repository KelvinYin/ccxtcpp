#include <libwebsockets.h>
#include "ws_callback.h"
#include "ws_client.h"

class websocket : public websocket_client, public client_callback_t
{
    bool run_ = true;

public:
    websocket() : websocket_client(this, "wss://fstream.binance.com/stream?streams=btcusdt@depth5") {}
    // wss://stream.binance.com:9443/ws/btcusdt@depth5

    [[nodiscard]] bool working() const noexcept { return run_; }

    void on_connected() override
    {
        lwsl_user("client connected\n");
        std::string msg = R"({"method": "SUBSCRIBE","params":["btcusdt@depth5"],"id": 1})";
        send(msg.data(), msg.size());
    }
    void on_disconnected() override
    {
        lwsl_user("client disconnected\n");
    }
    void on_error(const char *msg, size_t len) override
    {
        lwsl_user("client error\n");
    }
    void on_data(const char *data, size_t len, size_t remaining) override
    {
        std::string msg(data, len);
        printf("data from server: %s\n", msg.c_str());
        if (count_++ == 10)
        {
            std::string send_msg = R"({"method":"UNSUBSCRIBE", "params":["btcusdt@depth5"],"id":31})";
            send(send_msg.data(), send_msg.size());
            // send_msg = R"({"method":"SUBSCRIBE", "params":["btcusdt@markPrice@1s"],"id":32})";
            // send(send_msg.data(), send_msg.size());
        }
    }

    long count_{0};
};

int main()
{
    lws_set_log_level(LLL_USER | LLL_ERR | LLL_WARN | LLL_NOTICE, nullptr);
    websocket client;
    client.connect();
    while (client.working())
    {
    }
    return 0;
}