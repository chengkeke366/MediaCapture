#pragma once
#include <memory>
#include <mutex>
#include <vector>
#include "VideoCaptureModule.h"
#include "VideoCaptureCapability.h"

/*��װ�����壺��ͬƽ̨�����ṩ������һ��API �����豸��Ϣ����*/

class DeviceInfoImpl : public VideoCaptureModule::DeviceInfo
{
public:
  DeviceInfoImpl();
  ~DeviceInfoImpl(void) override;
  int32_t NumberOfCapabilities(const char* deviceUniqueIdUTF8) override;
  int32_t GetCapability(const char* deviceUniqueIdUTF8,
    const uint32_t deviceCapabilityNumber,
    VideoCaptureCapability& capability) override;

  int32_t GetBestMatchedCapability(const char* deviceUniqueIdUTF8,
    const VideoCaptureCapability& requested,
    VideoCaptureCapability& resulting) override;
  int32_t GetOrientation(const char* deviceUniqueIdUTF8,
    VideoRotation& orientation) override;

protected:
  /* Initialize this object*/

  virtual int32_t Init() = 0;
  /*
   * Fills the member variable _captureCapabilities with capabilities for the
   * given device name.
   */
  virtual int32_t CreateCapabilityMap(const char* deviceUniqueIdUTF8)=0;

protected:
  // Data members
  typedef std::vector<VideoCaptureCapability> VideoCaptureCapabilities;
  VideoCaptureCapabilities _captureCapabilities;
  std::mutex _apiLock;
  char* _lastUsedDeviceName;
  uint32_t _lastUsedDeviceNameLength;

};

