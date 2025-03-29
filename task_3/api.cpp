#include "api.h"
#include <iostream>

std::string ApiClient::performRequest(const std::string& host, const std::string& target) {
    // Parse the URL for host and target
    std::string protocol = "https";  // Assumed HTTPS for this example
    std::string endpoint = host;
    std::string path = target;

    if (protocol == "https") {
        asio::io_context ioc;
        boost::asio::ssl::context ctx(boost::asio::ssl::context::tlsv12_client);

        // Load system certificates
        ctx.set_default_verify_paths();

        // Create a stream for SSL
        beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx);

        // Resolve the host
        asio::ip::tcp::resolver resolver(ioc);
        auto const results = resolver.resolve(endpoint, "https");

        // Connect the stream to the endpoint
        beast::get_lowest_layer(stream).connect(results);

        // Perform SSL handshake
        stream.handshake(boost::asio::ssl::stream_base::client);

        // Set up the HTTP GET request
        http::request<http::string_body> req{http::verb::get, path, 11};
        req.set(http::field::host, endpoint);
        req.set(http::field::user_agent, "Boost.Beast");
        req.set(http::field::content_type, "application/json");

        // Send the request
        http::write(stream, req);

        // Receive the response
        beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(stream, buffer, res);

        // Close the stream after the response
        boost::system::error_code ec;
        stream.shutdown(ec);

        // Return the response as a string
        return beast::buffers_to_string(res.body().data());
    }

    return "";
}

std::future<std::vector<json>> ApiClient::getUsers(int page) {
    return std::async(std::launch::async, [this, page]() {
        std::string response = performRequest(this->m_endpoint, EndpointBuilder::getUsers(page));
        json jsonData = json::parse(response);
        return jsonData["data"].get<std::vector<json>>();
    });
}

std::future<json> ApiClient::getUser(int userId) {
    return std::async(std::launch::async, [this, userId]() {
        std::string response = performRequest(this->m_endpoint, EndpointBuilder::getUser(userId));
        json jsonData = json::parse(response);
        return jsonData["data"];
    });
}
