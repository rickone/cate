#pragma once

#include <unistd.h> // close
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h> // getnameinfo
#include <netinet/tcp.h> // TCP_NODELAY

namespace cate {

class socket_wrap {
public:
    socket_wrap() = default;
    socket_wrap(int fd);
    socket_wrap(int domain, int type, int protocol);
    socket_wrap(const socket_wrap& other) = delete;
    socket_wrap(socket_wrap&& other);
    ~socket_wrap();

    void attach(int fd);
    int detach();
    void close() noexcept;
    void set_option(int level, int optname, bool enable);

    void bind(const struct sockaddr *addr, socklen_t addrlen);
    void connect(const struct sockaddr *addr, socklen_t addrlen);
    void listen(int backlog);

    socket_wrap accept();

    int recvfrom(char *data, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
    int sendto(const char *data, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
    int recv(char *data, size_t len, int flags);
    int send(const char *data, size_t len, int flags);

private:
    int _fd = -1;
};

} // cate
