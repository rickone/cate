#pragma once

namespace cate {

class server {
public:
    server() = default;
    ~server() = default;

    static server* create();
    void use();
    void run(int port);
};

} // cate
