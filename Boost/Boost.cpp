#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>

char GetSign(std::string& request)
{
    std::vector<char> signs = {'+', '-'};

    for (size_t i = 0; i < signs.size(); i++)
    {
        size_t s_pos = request.find(signs[i]);
        if (s_pos != std::string::npos && s_pos != 0)
        {
            for (size_t j = 0; j < signs.size(); j++)
                if (request[s_pos-1] == signs[i]) continue;
                else return request[s_pos];   
        }
    }  

    return '0';
}

std::vector<std::string> StringProcessing(std::string& request)
{
    std::string p_request;
    std::remove_copy(request.begin(), request.end(), std::back_inserter(p_request), ' ');

    std::vector <std::string> p_string;
    std::string sign;
    size_t pos = 0;
    size_t next_pos;

    sign = GetSign(p_request);
    if (sign == "0") return p_string;

    p_string.push_back(sign);
    while ((next_pos = p_request.find(sign, pos)) != std::string::npos)
    {
        p_string.push_back(p_request.substr(pos, next_pos - pos));
        pos = next_pos + 1;
        sign = "/";
    }
    p_string.push_back(p_request.substr(pos));

    return p_string;
}

// Performs an HTTP GET and prints the response
int main(int argc, char** argv) {
    setlocale(0, "");

    std::string request;
    std::getline(std::cin, request);
    std::vector <std::string> p_request = StringProcessing(request);

    if (p_request.empty())
    {
        std::cout << "The sign can't be found" << std::endl;
        return 0;
    }

    try {
        //http://157.230.27.215/calc/diff/25/12 >> 25 - 12 = 13
        //http://157.230.27.215/calc/sum/35/15 >> 35 + 15 = 50
        std::string a = p_request[1];
        std::string b = p_request[2];
        std::string const host = "157.230.27.215";
        std::string const port = "80";
        std::stringstream url;
        std::string action;

        if (p_request[0] == "-")
            action = "/calc/diff/";
        else
            action = "/calc/sum/";

        url << action << a << "/" << b;

        std::string const target = url.str();
        int const version = 11;
        std::cout << target;
        // The io_context is required for all I/O
        net::io_context ioc;

        // These objects perform our I/O
        tcp::resolver resolver(ioc);
        auto const results = resolver.resolve(host, port);

        beast::tcp_stream stream(ioc);
        stream.connect(results);

        // Set up an HTTP GET request message
        http::request<http::string_body> req{ http::verb::get, target, version };
        //headers
        req.set(http::field::host, host);
        req.set(http::field::user_agent, "gg/test");

        // Send the HTTP request to the remote host
        http::write(stream, req);

        // This buffer is used for reading and must be persisted
        beast::flat_buffer buffer;

        // Declare a container to hold the response
        http::response<http::dynamic_body> res;

        // Receive the HTTP response
        http::read(stream, buffer, res);

        // Write the message to standard out
        std::cout << res << std::endl;

        // Gracefully close the socket
        beast::error_code ec;
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);

        // not_connected happens sometimes
        // so don't bother reporting it.
        //
        if (ec && ec != beast::errc::not_connected)
            throw beast::system_error{ ec };

        // If we get here then the connection is closed gracefully
    }
    catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}