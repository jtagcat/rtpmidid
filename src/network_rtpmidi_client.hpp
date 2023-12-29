/**
 * Real Time Protocol Music Instrument Digital Interface Daemon
 * Copyright (C) 2019-2023 David Moreno Montero <dmoreno@coralbits.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

#include "midipeer.hpp"
#include "rtpmidid/rtpclient.hpp"
#include "rtpmidid/signal.hpp"
#include "rtpmidid/utils.hpp"

namespace rtpmidid {
class io_bytes_reader;
} // namespace rtpmidid

namespace rtpmididns {

/**
 * @short A remote peer connection
 *
 * Just does the basic communication with the given remote peer.
 *
 * Data from network to the peer is managed somewhere else, normally
 * a rtpmidid::rtpclient_t or rtpmidid::rtpserver_t object.
 */
class network_rtpmidi_client_t : public midipeer_t {
  NON_COPYABLE_NOR_MOVABLE(network_rtpmidi_client_t);

public:
  std::shared_ptr<rtpmidid::rtpclient_t> peer;
  rtpmidid::connection_t<const rtpmidid::io_bytes_reader &> midi_connection;
  rtpmidid::connection_t<rtpmidid::rtppeer_t::disconnect_reason_e>
      disconnect_connection;
  rtpmidid::connection_t<const std::string &, rtpmidid::rtppeer_t::status_e>
      connected_connection;

  network_rtpmidi_client_t(std::shared_ptr<rtpmidid::rtpclient_t> peer);
  ~network_rtpmidi_client_t() override;

  void send_midi(midipeer_id_t from, const mididata_t &) override;
  json_t status() override;
};
} // namespace rtpmididns
