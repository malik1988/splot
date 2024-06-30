//
// Created by Malik on 2024/6/29.
//
#pragma once

#ifndef SPLOTER_FACTORY_H
#    define SPLOTER_FACTORY_H

#    include "isploter.h"

namespace splot {
struct sploter_factory
{
    static std::unique_ptr<isploter> create();
};

}   // namespace splot
#endif   // SPLOTER_FACTORY_H
