// Generated by the smf_gen.
// Any local changes WILL BE LOST.
// source: /home/agallego/workspace/smf/src/rpc/smf_gen/demo_service
#pragma once
#ifndef SMF_DEMO_SERVICE_INCLUDED
#define SMF_DEMO_SERVICE_INCLUDED

#include "demo_service_generated.h"

#include <experimental/optional>
#include <log.h>
#include <rpc/rpc_client.h>
#include <rpc/rpc_recv_typed_context.h>
#include <rpc/rpc_service.h>
namespace smf_gen {
namespace fbs {
namespace rpc {

class SmfStorage : public smf::rpc_service {
  public:
  virtual const char *service_name() const override final {
    return "SmfStorage";
  }
  virtual uint32_t service_id() const override final { return 212494116; }
  virtual std::vector<smf::rpc_service_method_handle> methods() override final {
    std::vector<smf::rpc_service_method_handle> handles;
    handles.emplace_back(
      "Get", 2552873045,
      [this](smf::rpc_recv_context c) -> future<smf::rpc_envelope> {
        using t = smf::rpc_recv_typed_context<Request>;
        return Get(t(std::move(c)));
      });
    return handles;
  }
  virtual future<smf::rpc_envelope>
  Get(smf::rpc_recv_typed_context<Request> &&rec) {
    // Output type: Response
    smf::rpc_envelope e(nullptr);
    // Helpful for clients to set the status.
    // Typically follows HTTP style. Not imposed by smf whatsoever.
    e.set_status(501); // Not implemented
    return make_ready_future<smf::rpc_envelope>(std::move(e));
  }
}; // end of service: SmfStorage

class SmfStorageClient : public smf::rpc_client {
  public:
  SmfStorageClient(ipv4_addr server_addr)
    : smf::rpc_client(std::move(server_addr)) {}

  /// RequestID: 212494116 ^ 2552873045
  /// ServiceID: 212494116 == crc32("SmfStorage")
  /// MethodID:  2552873045 == crc32("Get")
  future<smf::rpc_recv_typed_context<Response>> Get(smf::rpc_envelope e) {
    e.set_request_id(212494116, 2552873045);
    return send<Response>(std::move(e), false);
  }
  future<smf::rpc_recv_typed_context<Response>> SafeGet(smf::rpc_envelope e) {
    return limit_.wait(1).then([this, e = std::move(e)]() mutable {
      return this->Get(std::move(e)).finally([this]() { limit_.signal(1); });
    });
  }
}; // end of rpc client: SmfStorageClient

} // namespace rpc
} // namespace fbs
} // namespace smf_gen


#endif // SMF_DEMO_SERVICE_INCLUDED
