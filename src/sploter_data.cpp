//
// Created by Malik on 2024/6/29.
//

#include "../include/sploter_data.h"

#include <algorithm>

namespace splot
{
  sploter_data::sploter_data(std::deque<float> &&xs, std::function<float(float)> func, std::string_view name)
      : x(std::move(xs)),
        color{ irender::colors::UNSET },
        visible{ true },
        name{ name }
  {
    y.resize(x.size());
    std::transform(x.begin(), x.end(), y.begin(), std::move(func));
  }

  sploter_data::sploter_data(std::deque<float> &&xs, std::deque<float> &&ys, std::string_view name)
      : color{ irender::colors::UNSET },
        visible(false),
        name{ name },
        x{ xs },
        y{ ys }
  {
  }
}  // namespace splot
