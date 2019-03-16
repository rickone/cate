#include "cate_socket_wrap.h"
#include "asyn_panic.h"

using namespace cate;
using namespace asyn;

socket_wrap::socket_wrap(int fd) : _fd(fd) {
}

socket_wrap::socket_wrap(int domain, int type, int protocol) {
    int fd = ::socket(domain, type, protocol);
    if (fd < 0) {
        panic_system("socket");
    }

    _fd = fd;
}

socket_wrap::socket_wrap(socket_wrap&& other) : _fd(other._fd) {
    other._fd = -1;
}

socket_wrap::~socket_wrap() {
    close();
}

void socket_wrap::attach(int fd) {
    close();
    _fd = fd;
}

int socket_wrap::detach() {
    int fd = _fd;
    _fd = -1;
    return fd;
}

void socket_wrap::close() noexcept {
    if (_fd >= 0) {
        ::close(_fd);
        _fd = -1;
    }
}

void socket_wrap::set_option(int level, int optname, bool enable) {
    int opt_val = enable ? 1 : 0;
    //socklen_t int_len = sizeof(opt_val);

    int ret = setsockopt(_fd, level, optname, (const char *)&opt_val, (socklen_t)sizeof(opt_val));
    if (ret != 0) {
        panic_system("setsockopt");
    }
}

void socket_wrap::bind(const struct sockaddr *addr, socklen_t addrlen) {
    int ret = ::bind(_fd, addr, addrlen);
    if (ret != 0) {
        panic_system("bind");
    }

    //auto name = get_addrname(addr, addrlen);
    //log_info("fd(%d) bind to %s", _fd, name.c_str());
}

void socket_wrap::connect(const struct sockaddr *addr, socklen_t addrlen) {
    int ret = ::connect(_fd, addr, addrlen);
    if (ret != 0) {
        panic_system("connect");
    }

    //auto name = get_addrname(addr, addrlen);
    //bool connected = (ret == 0);
    //log_info("fd(%d) connect %s ... %s", _fd, name.c_str(), (connected ? "OK" : "pending"));
}

void socket_wrap::listen(int backlog) {
    int ret = ::listen(_fd, backlog);
    if (ret != 0) {
        panic_system("listen");
    }

    //log_info("fd(%d) listen backlog(%d)", _fd, backlog);
}

socket_wrap socket_wrap::accept() {
    struct sockaddr_storage addr;
    socklen_t addrlen = (socklen_t)sizeof(addr);

    int fd = ::accept(_fd, (struct sockaddr *)&addr, &addrlen);
    if (fd < 0) {
        panic_system("accept");
    }

    return socket_wrap(fd);
}

int socket_wrap::recvfrom(char *data, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen) {
    int ret = ::recvfrom(_fd, data, len, flags, src_addr, addrlen);
    if (ret < 0) {
        panic_system("recvfrom");
    }

    return ret;
}

int socket_wrap::sendto(const char *data, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen) {
    int ret = ::sendto(_fd, data, len, flags, dest_addr, addrlen);
    if (ret < 0) {
        panic_system("sendto");
    }

    return ret;
}

int socket_wrap::recv(char *data, size_t len, int flags) {
    int ret = ::recv(_fd, data, len, flags);
    if (ret < 0) {
        panic_system("recv");
    }

    //log_debug("fd(%d) recv %d bytes", _fd, ret);
    return ret;
}

int socket_wrap::send(const char *data, size_t len, int flags) {
    int ret = ::send(_fd, data, len, flags);
    if (ret < 0) {
        panic_system("send");
    }

    //log_debug("fd(%d) send %d bytes", _fd, ret);
    return ret;
}
