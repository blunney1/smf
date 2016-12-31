#pragma once
#include "hashing_utils.h"
#include <flatbuffers/idl.h>

namespace smf_gen {
class smf_method {
  public:
  enum Streaming { kNone, kClient, kServer, kBiDi };
  smf_method(const flatbuffers::RPCCall *method,
             std::string service_name,
             uint32_t service_id)
    : method_(method), service_name_(service_name), service_id_(service_id) {
    streaming_ = kNone;
    // you can have the same method name w/ different arguments, so in that
    // case you should change the hash id
    std::string method_id_str =
      method_->name + ":" + input_type_name() + ":" + output_type_name();
    id_ = smf::crc_32(method_id_str.c_str(), method_id_str.length());
  }
  std::string name() const { return method_->name; }
  uint32_t method_id() const { return id_; }

  std::string service_name() const { return service_name_; }
  uint32_t service_id() const { return service_id_; }

  std::string type(const flatbuffers::StructDef &sd) const { return sd.name; }
  std::string input_type_name() const { return type(*method_->request); }
  std::string output_type_name() const { return type(*method_->response); }

  private:
  const flatbuffers::RPCCall *method_;
  const std::string service_name_;
  const uint32_t service_id_;
  Streaming streaming_;

  uint32_t id_;
};
}
