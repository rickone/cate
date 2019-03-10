#include "cate_service.h"

using namespace cate;

service* service::create() {
    return new service();
}
