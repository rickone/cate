#include "cate_server.h"
#include "cate_socket_wrap.h"

using namespace cate;

server* server::create() {
    return new server();
}

void server::run(int port) {
    socket_wrap obj(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    obj.set_option(SOL_SOCKET, SO_REUSEADDR, true);
    obj.set_option(SOL_SOCKET, SO_REUSEPORT, true);
}
