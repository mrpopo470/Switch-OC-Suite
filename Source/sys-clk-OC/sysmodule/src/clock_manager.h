/*
 * --------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <p-sam@d3vs.net>, <natinusala@gmail.com>, <m4x@m4xw.net>
 * wrote this file. As long as you retain this notice you can do whatever you
 * want with this stuff. If you meet any of us some day, and you think this
 * stuff is worth it, you can buy us a beer in return.  - The sys-clk authors
 * --------------------------------------------------------------------------
 */

#pragma once

#include <atomic>
#include <sysclk.h>

#include "config.h"
#include "clocks.h"
#include <nxExt/cpp/lockable_mutex.h>

class ClockManager
{
  public:

    static ClockManager* GetInstance();
    static void Initialize();
    static void Exit();

    void SetRunning(bool running);
    bool Running();
    void Tick();
    void WaitForNextTick();
    SysClkContext GetCurrentContext();
    Config* GetConfig();

  protected:
    ClockManager();
    virtual ~ClockManager();

    bool RefreshContext();

    static ClockManager *instance;
    std::atomic_bool running;
    LockableMutex contextMutex;
    Config *config;
    SysClkContext *context;
    std::uint64_t lastTempLogNs;
    std::uint64_t lastCsvWriteNs;

    SysClkOcExtra *oc;
    const uint32_t CPU_BOOST_FREQ = 2295'000'000;

    bool IsCpuBoostMode();
    bool IsReverseNXEnabled();
    bool IsReverseNXDocked();

    uint32_t GetHz(SysClkModule);
    SysClkProfile ReverseNXProfileHandler();
    ReverseNXMode ReverseNXFileHandler(bool, const char*);

    void CheckReverseNXTool();
    bool CheckReverseNXRT();

    // LockableMutex systemCoreStuckCountMutex;
    // Thread t_CheckSystemCoreStuck_0, t_CheckSystemCoreStuck_1, t_CheckSystemCoreStuck_2;

    // static void CheckSystemCoreStuck(void *arg);
    // void StartCheckSystemCore();
    // void StopCheckSystemCore();
};
