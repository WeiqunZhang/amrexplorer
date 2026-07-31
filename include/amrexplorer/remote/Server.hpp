#pragma once

#include <amrexplorer/remote/Frame.hpp>

#include <cstdint>
#include <memory>
#include <string>

namespace amrvis::remote {

struct ServerOptions {
    std::uint16_t port = 0;
    unsigned int workerCount = 0;
    std::uint32_t maximumFrameBytes = defaultMaximumFrameBytes;
    std::uint32_t maximumDatasets = 8;
    std::uint32_t maximumOutstandingRequests = 64;
    std::string softwareVersion = "unknown";
    // Per-session access token. Clients must present a byte-identical token in
    // their handshake or the connection is refused. Left empty, the server
    // generates a fresh random token at construction; there is no way to
    // disable the check. See token().
    std::string sessionToken;
};

class Server {
public:
    explicit Server(ServerOptions options = {});
    ~Server();

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    [[nodiscard]] std::uint16_t port() const noexcept;
    // The access token clients must present. Either the token supplied in
    // ServerOptions or, when that was empty, the one generated at construction.
    [[nodiscard]] const std::string& token() const noexcept;
    void run();
    void requestStop() noexcept;

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

} // namespace amrvis::remote
