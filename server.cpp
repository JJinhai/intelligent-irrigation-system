#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include "fcgiapp.h"

using boost::asio::ip::tcp;
using namespace std;

const int PORT = 8080;

class HttpServer {
public:
    HttpServer(boost::asio::io_context& io_context)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), PORT)) {
        accept();
    }

private:
    void accept() {
        socket_.emplace(acceptor_.get_executor());
        acceptor_.async_accept(*socket_, boost::bind(&HttpServer::handle_accept, this, boost::asio::placeholders::error));
    }

    void handle_accept(const boost::system::error_code& error) {
        if (!error) {
            // 这里可以处理客户端连接和HTTP请求
            // 然后你可以使用FastCGI客户端进行HTTP/HTTPS请求
        }
        accept();
    }

    tcp::acceptor acceptor_;
    std::optional<tcp::socket> socket_;
};

int main() {
    try {
        boost::asio::io_context io_context;
        HttpServer server(io_context);
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
