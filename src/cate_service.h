#pragma once

namespace cate {

class service {
public:
    service() = default;
    ~service() = default;

    static service* create();
};

} // cate
