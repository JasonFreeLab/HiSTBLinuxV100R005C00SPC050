// Copyright 2015 Google Inc. All Rights Reserved.
#include "test_host.h"

//#include <gtest/gtest.h>
#include <sys/time.h>

#include "device_cert.h"
#include "log.h"

using namespace widevine;

TestHost::TestHost()
{
    Reset();
}

void TestHost::Reset()
{
    struct timeval tv;
    tv.tv_sec = tv.tv_usec = 0;
    gettimeofday(&tv, NULL);
    now_ = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL);

    // Surprisingly, std::priority_queue has no clear().
    while (!timers_.empty())
    {
        timers_.pop();
    }

    files_.clear();
    files_["cert.bin"] =
        std::string((const char*)kDeviceCert, kDeviceCertSize);
}

void TestHost::ElapseTime(int64_t milliseconds)
{
    int64_t goal_time = now_ + milliseconds;

    while (now_ < goal_time)
    {
        if (timers_.empty())
        {
            now_ = goal_time;
        }
        else
        {
            Timer t = timers_.top();
            timers_.pop();
            //ASSERT_GE(t.expiry_time, now_);
            now_ = t.expiry_time;
            t.client->onTimerExpired(t.context);
        }
    }
}

int TestHost::NumTimers() const { return timers_.size(); }

bool TestHost::read(const std::string& name,
                    std::string* data)
{
    StorageMap::iterator it = files_.find(name);
    bool ok = it != files_.end();
    LOGD("read file: %s: %s", name.c_str(), ok ? "ok" : "fail");

    if (!ok) { return false; }

    *data = it->second;
    return true;
}

bool TestHost::write(const std::string& name,
                     const std::string& data)
{
    LOGD("write file: %s", name.c_str());
    files_[name] = data;
    return true;
}

bool TestHost::exists(const std::string& name)
{
    StorageMap::iterator it = files_.find(name);
    bool ok = it != files_.end();
    LOGD("exists? %s: %s", name.c_str(), ok ? "true" : "false");
    return ok;
}

bool TestHost::remove(const std::string& name)
{
    LOGD("remove: %s", name.c_str());
    files_.erase(name);
    return true;
}

int32_t TestHost::size(const std::string& name)
{
    StorageMap::iterator it = files_.find(name);

    if (it == files_.end()) { return -1; }

    return it->second.size();
}

int64_t TestHost::now()
{
    return now_;
}

void TestHost::setTimeout(int64_t delay_ms,
                          IClient* client,
                          void* context)
{
    int64_t expiry_time = now_ + delay_ms;
    timers_.push(Timer(expiry_time, client, context));
}

void TestHost::cancel(IClient* client)
{
    // Filter out the timers for this client and put the rest into |others|.
    std::priority_queue<Timer> others;

    while (timers_.size())
    {
        Timer t = timers_.top();
        timers_.pop();

        if (t.client != client)
        {
            others.push(t);
        }
    }

    // Now swap the queues.
    //timers_.swap(others);
}
