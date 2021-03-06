/*
 * Copyright (c) 2015 peeracle contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef PEERACLE_SESSION_SESSIONPEEROBSERVER_H_
#define PEERACLE_SESSION_SESSIONPEEROBSERVER_H_

#include <string>

#include "peeracle/Peer/PeerInterface.h"
#include "peeracle/Session/SessionInterface.h"

namespace peeracle {

class SessionPeerObserver
  : public PeerInterface::Observer {
 public:
  explicit SessionPeerObserver(SessionInterface *session);
  ~SessionPeerObserver();
  void onIceCandidate(const std::string &sdpMid, int sdpMLineIndex,
                      const std::string &candidate);
  void onSignalingChange(int state);
  void onStateChange(int state);
  void onIceConnectionChange(int state);
  void onIceGatheringChange(int state);
  void setPeer(PeerInterface *peer);

 private:
  PeerInterface *_peer;
  SessionInterface *_session;
};

}  // namespace peeracle

#endif  // PEERACLE_SESSION_SESSIONPEEROBSERVER_H_
