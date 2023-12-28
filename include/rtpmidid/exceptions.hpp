/**
 * Real Time Protocol Music Instrument Digital Interface Daemon
 * Copyright (C) 2019-2023 David Moreno Montero <dmoreno@coralbits.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 */

#pragma once
#include <exception>
#include <fmt/core.h>
#include <string>

namespace rtpmidid {
class exception : public std::exception {
  std::string msg;

public:
  template <typename... Args>
  exception(Args... args) : msg(fmt::format(args...)) {}
  const char *what() const noexcept override { return msg.c_str(); }
};

class not_implemented : public std::exception {
public:
  const char *what() const noexcept override { return "Not Implemented"; }
};
class network_exception : public std::exception {
  std::string str;
  int errno_ = 0;

public:
  network_exception(int _errno) : errno_(_errno) {
    str = fmt::format("Network error {} ({})", strerror(errno_), errno_);
  }
  const char *what() const noexcept override { return str.c_str(); }
};
} // namespace rtpmidid
