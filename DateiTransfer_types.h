/**
 * Autogenerated by Thrift Compiler (0.9.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef DateiTransfer_TYPES_H
#define DateiTransfer_TYPES_H

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/cxxfunctional.h>




typedef struct _datenSenden__isset {
  _datenSenden__isset() : neuePosition(false), paket(false) {}
  bool neuePosition;
  bool paket;
} _datenSenden__isset;

class datenSenden {
 public:

  static const char* ascii_fingerprint; // = "19F6485E473538C6BC4AC5F253CBC1B9";
  static const uint8_t binary_fingerprint[16]; // = {0x19,0xF6,0x48,0x5E,0x47,0x35,0x38,0xC6,0xBC,0x4A,0xC5,0xF2,0x53,0xCB,0xC1,0xB9};

  datenSenden() : neuePosition(0) {
  }

  virtual ~datenSenden() throw() {}

  int64_t neuePosition;
  std::vector<int8_t>  paket;

  _datenSenden__isset __isset;

  void __set_neuePosition(const int64_t val) {
    neuePosition = val;
  }

  void __set_paket(const std::vector<int8_t> & val) {
    paket = val;
  }

  bool operator == (const datenSenden & rhs) const
  {
    if (!(neuePosition == rhs.neuePosition))
      return false;
    if (!(paket == rhs.paket))
      return false;
    return true;
  }
  bool operator != (const datenSenden &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const datenSenden & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(datenSenden &a, datenSenden &b);

typedef struct _initUploadReturn__isset {
  _initUploadReturn__isset() : neuePosition(false), verbindungsId(false) {}
  bool neuePosition;
  bool verbindungsId;
} _initUploadReturn__isset;

class initUploadReturn {
 public:

  static const char* ascii_fingerprint; // = "AFAFBCDB9822F9D1AA4E44188E720B47";
  static const uint8_t binary_fingerprint[16]; // = {0xAF,0xAF,0xBC,0xDB,0x98,0x22,0xF9,0xD1,0xAA,0x4E,0x44,0x18,0x8E,0x72,0x0B,0x47};

  initUploadReturn() : neuePosition(0), verbindungsId(0) {
  }

  virtual ~initUploadReturn() throw() {}

  int64_t neuePosition;
  int32_t verbindungsId;

  _initUploadReturn__isset __isset;

  void __set_neuePosition(const int64_t val) {
    neuePosition = val;
  }

  void __set_verbindungsId(const int32_t val) {
    verbindungsId = val;
  }

  bool operator == (const initUploadReturn & rhs) const
  {
    if (!(neuePosition == rhs.neuePosition))
      return false;
    if (!(verbindungsId == rhs.verbindungsId))
      return false;
    return true;
  }
  bool operator != (const initUploadReturn &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const initUploadReturn & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(initUploadReturn &a, initUploadReturn &b);

typedef struct _initDownloadReturn__isset {
  _initDownloadReturn__isset() : dateiGroese(false), verbindungsId(false), neuePosition(false) {}
  bool dateiGroese;
  bool verbindungsId;
  bool neuePosition;
} _initDownloadReturn__isset;

class initDownloadReturn {
 public:

  static const char* ascii_fingerprint; // = "C2C41E587DAC84A77A5056A1DC94ED73";
  static const uint8_t binary_fingerprint[16]; // = {0xC2,0xC4,0x1E,0x58,0x7D,0xAC,0x84,0xA7,0x7A,0x50,0x56,0xA1,0xDC,0x94,0xED,0x73};

  initDownloadReturn() : dateiGroese(0), verbindungsId(0), neuePosition(0) {
  }

  virtual ~initDownloadReturn() throw() {}

  int64_t dateiGroese;
  int32_t verbindungsId;
  int64_t neuePosition;

  _initDownloadReturn__isset __isset;

  void __set_dateiGroese(const int64_t val) {
    dateiGroese = val;
  }

  void __set_verbindungsId(const int32_t val) {
    verbindungsId = val;
  }

  void __set_neuePosition(const int64_t val) {
    neuePosition = val;
  }

  bool operator == (const initDownloadReturn & rhs) const
  {
    if (!(dateiGroese == rhs.dateiGroese))
      return false;
    if (!(verbindungsId == rhs.verbindungsId))
      return false;
    if (!(neuePosition == rhs.neuePosition))
      return false;
    return true;
  }
  bool operator != (const initDownloadReturn &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const initDownloadReturn & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(initDownloadReturn &a, initDownloadReturn &b);



#endif
