/* 
 *  rawuartudplistener.h is part of the HB-RF-ETH firmware - https://github.com/alexreinert/HB-RF-ETH
 *  
 *  Copyright 2020 Alexander Reinert
 *  
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *  
 *      http://www.apache.org/licenses/LICENSE-2.0
 *  
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#pragma once

#include "lwip/opt.h"
#include "lwip/inet.h"
#include "lwip/udp.h"
#include "lwip/priv/tcpip_priv.h"
#include <atomic>
#define _Atomic(X) std::atomic< X >
#include "radiomoduleconnector.h"

class RawUartUdpListener : FrameHandler {
  private:
    RadioModuleConnector* _radioModuleConnector;
    std::atomic<uint> _remoteAddress;
    std::atomic<ushort> _remotePort;
    std::atomic<bool> _connectionStarted;
    std::atomic<int> _counter;
    uint64_t _lastReceivedKeepAlive;
    udp_pcb* _pcb;
    QueueHandle_t _udp_queue;
    TaskHandle_t _tHandle = NULL;

    void handlePacket(pbuf *pb, ip4_addr_t addr, uint16_t port);
    void sendMessage(unsigned char command, unsigned char* buffer, size_t len);
  
  public:
    RawUartUdpListener(RadioModuleConnector* radioModuleConnector);

    void handleFrame(unsigned char* buffer, uint16_t len);
    void handleEvent();

    void start();
    void stop();

    void _udpQueueHandler();
    bool _udpReceivePacket(pbuf *pb, const ip_addr_t *addr, uint16_t port);
};
