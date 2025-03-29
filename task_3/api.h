#ifndef API_H
#define API_H

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast/ssl.hpp>
#include <nlohmann/json.hpp>
#include <future>
#include <vector>
#include <string>

#define BOOST_LOG_DYN_LINK
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>


namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
using json = nlohmann::json;

class ApiClient {
public:
    ApiClient() {
        this->m_endpoint = "reqres.in";

        boost::log::add_console_log(std::cout, boost::log::keywords::format = "[%TimeStamp%] [%Severity%] %Message%");
        boost::log::add_common_attributes();
    };
    
    std::future<std::vector<json>> getUsers(int page);
    std::future<json> getUser(int userId);

private:
    std::string m_endpoint;
    asio::io_context ioc;

    // Inner class for constructing API endpoints
    class EndpointBuilder {
        public:
            static std::string getUsers(int page) {
                return "/api/users?page=" + std::to_string(page);
            }
    
            static std::string getUser(int userId) {
                return "/api/users/" + std::to_string(userId);
            }
        };

    std::string performRequest(const std::string& host, const std::string& target);
};

#endif // API_H
