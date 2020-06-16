/* 
 *  updatecheck.h is part of the HB-RF-ETH firmware - https://github.com/alexreinert/HB-RF-ETH
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

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "boarddetector.h"
#include "led.h"

class UpdateCheck
{
private:
    board_type_t _boardType;
    const char* _currentVersion;
    LED *_statusLED;
    TaskHandle_t _tHandle = NULL;   
    void _updateLatestVersion();
    char _latestVersion[33] = "n/a";
    char _serial[13];

public:
    UpdateCheck(board_type_t boardType, LED *statusLED);
    void start();
    void stop();

    const char* getLatestVersion();
    const char* getCurrentVersion();

    void _taskFunc();
};