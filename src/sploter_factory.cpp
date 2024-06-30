//
// Created by Malik on 2024/6/29.
//
#include "../include/sploter_factory.h"

#include "sploter.h"

namespace splot {
std::unique_ptr<isploter> sploter_factory::create() {
    return std::make_unique<sploter>(sploter());
}
} // namespace splot