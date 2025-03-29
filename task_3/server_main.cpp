#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <iostream>
#include <string>
#include <fstream>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
using tcp = asio::ip::tcp;

class SimpleHttpServer {
public:
    SimpleHttpServer(asio::io_context& ioc, const std::string& address, unsigned short port)
        : ioc_(ioc), acceptor_(ioc, tcp::endpoint(asio::ip::make_address(address), port)) {}

    void run() {
        acceptConnections();
        ioc_.run();
    }

private:
    asio::io_context& ioc_;
    tcp::acceptor acceptor_;

    void acceptConnections() {
        acceptor_.async_accept([this](beast::error_code ec, tcp::socket socket) {
            if (!ec) {
                handleRequest(std::move(socket));
            }
            acceptConnections();
        });
    }

    void handleRequest(tcp::socket socket) {
        try {
            beast::flat_buffer buffer;
            http::request<http::string_body> req;

            http::read(socket, buffer, req);

            if (req.method() == http::verb::get) {
                std::string target = std::string(req.target());
                if (target == "/file1") {
                    sendFile(socket, "file1.txt");
                } else if (target == "/file2") {
                    sendFile(socket, "file2.txt");
                } else if (target == "/file3") {
                    sendFile(socket, "file3.txt");
                } else {
                    sendNotFound(socket);
                }
            } else {
                sendMethodNotAllowed(socket);
            }
        } catch (const std::exception& e) {
            std::cerr << "Error handling request: " << e.what() << std::endl;
        }
    }

    void sendFile(tcp::socket& socket, const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            sendNotFound(socket);
            return;
        }
    
        beast::flat_buffer buffer;
        http::response<http::file_body> res{http::status::ok, 11};
        res.set(http::field::content_type, "application/octet-stream");
    
        // Create an error_code object to catch any errors
        boost::system::error_code ec;
    
        // Open the file and pass it to the response body
        res.body().open(filename.c_str(), beast::file_mode::scan, ec);
    
        // Check for errors
        if (ec) {
            sendNotFound(socket);
            return;
        }
    
        // Write the response
        http::write(socket, res);
    } 

    void sendNotFound(tcp::socket& socket) {
        http::response<http::string_body> res{http::status::not_found, 11};
        res.set(http::field::content_type, "text/plain");
        res.body() = "Not Found";
        http::write(socket, res);
    }

    void sendMethodNotAllowed(tcp::socket& socket) {
        http::response<http::string_body> res{http::status::method_not_allowed, 11};
        res.set(http::field::content_type, "text/plain");
        res.body() = "Method Not Allowed";
        http::write(socket, res);
    }
};

int main() {
    try {
        asio::io_context ioc;
        SimpleHttpServer server(ioc, "127.0.0.1", 8080);
        std::cout << "Server running at http://127.0.0.1:8080\n";
        server.run();
    } catch (const std::exception& e) {
        std::cerr << "Error starting server: " << e.what() << std::endl;
    }

    return 0;
}
