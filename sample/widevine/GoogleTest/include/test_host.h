// Copyright 2015 Google Inc. All Rights Reserved.
#ifndef WVCDM_CDM_TEST_TEST_HOST_H_
#define WVCDM_CDM_TEST_TEST_HOST_H_

#include <queue>

#include "cdm.h"
#include "override.h"

class TestHost : public widevine::Cdm::IStorage,
                 public widevine::Cdm::IClock,
                 public widevine::Cdm::ITimer {
 public:
  TestHost();
  void Reset();

  void ElapseTime(int64_t milliseconds);
  int NumTimers() const;

  virtual bool read(const std::string& name,
                    std::string* data) OVERRIDE;
  virtual bool write(const std::string& name,
                     const std::string& data) OVERRIDE;
  virtual bool exists(const std::string& name) OVERRIDE;
  virtual bool remove(const std::string& name) OVERRIDE;
  virtual int32_t size(const std::string& name) OVERRIDE;

  virtual int64_t now() OVERRIDE;

  virtual void setTimeout(int64_t delay_ms,
                          IClient* client,
                          void* context) OVERRIDE;
  virtual void cancel(IClient* client) OVERRIDE;

 private:
  struct Timer {
    Timer(int64_t expiry_time, IClient* client, void* context)
        : expiry_time(expiry_time), client(client), context(context) {}

    bool operator<(const Timer& other) const {
      // We want to reverse the order so that the smallest expiry times go to
      // the top of the priority queue.
      return expiry_time > other.expiry_time;
    }

    int64_t expiry_time;
    IClient* client;
    void* context;
  };

  int64_t now_;
  std::priority_queue<Timer> timers_;

  typedef std::map<std::string, std::string> StorageMap;
  StorageMap files_;
};

// Owned and managed by the test runner.
extern TestHost* g_host;

#endif  // WVCDM_CDM_TEST_TEST_HOST_H_
