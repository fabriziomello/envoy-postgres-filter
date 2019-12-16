#pragma once

#include "envoy/access_log/access_log.h"
#include "envoy/network/connection.h"
#include "envoy/network/filter.h"
#include "envoy/stats/scope.h"
#include "envoy/stats/stats.h"
#include "envoy/stats/stats_macros.h"

#include "common/buffer/buffer_impl.h"
#include "common/common/logger.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace PostgreSQLProxy {

/**
 * All PostgreSQL proxy stats. @see stats_macros.h
 */
// clang-format off
#define ALL_POSTGRESQL_PROXY_STATS(COUNTER)                                      \
  COUNTER(sessions)                                                              \
// clang-format on

/**
 * Struct definition for all PostgreSQL proxy stats. @see stats_macros.h
 */
struct PostgreSQLProxyStats {
  ALL_POSTGRESQL_PROXY_STATS(GENERATE_COUNTER_STRUCT)
};

/**
 * Configuration for the PostgreSQL proxy filter.
 */
class PostgreSQLFilterConfig {
public:
  PostgreSQLFilterConfig(const std::string &stat_prefix, Stats::Scope& scope);

  const PostgreSQLProxyStats& stats() { return stats_; }

  Stats::Scope& scope_;
  const std::string stat_prefix_;
  PostgreSQLProxyStats stats_;

private:
  PostgreSQLProxyStats generateStats(const std::string& prefix,
                                Stats::Scope& scope) {
    return PostgreSQLProxyStats{
        ALL_POSTGRESQL_PROXY_STATS(POOL_COUNTER_PREFIX(scope, prefix))};
  }
};

using PostgreSQLFilterConfigSharedPtr = std::shared_ptr<PostgreSQLFilterConfig>;

/**
 * Implementation of PostgreSQL proxy filter.
 */
class PostgreSQLFilter : public Network::Filter, /*DecoderCallbacks,*/ Logger::Loggable<Logger::Id::filter> {
public:
  PostgreSQLFilter(PostgreSQLFilterConfigSharedPtr config);
  ~PostgreSQLFilter() override = default;

  // Network::ReadFilter
  Network::FilterStatus onData(Buffer::Instance& data, bool end_stream) override;
  Network::FilterStatus onNewConnection() override;
  void initializeReadFilterCallbacks(Network::ReadFilterCallbacks& callbacks) override;

  // Network::WriteFilter
  Network::FilterStatus onWrite(Buffer::Instance& data, bool end_stream) override;

  // MySQLProxy::DecoderCallback
  //void onProtocolError() override;
  //void onNewMessage(MySQLSession::State state) override;
  //void onServerGreeting(ServerGreeting&) override {};
  //void onClientLogin(ClientLogin& message) override;
  //void onClientLoginResponse(ClientLoginResponse& message) override;
  //void onClientSwitchResponse(ClientSwitchResponse&) override {};
  //void onMoreClientLoginResponse(ClientLoginResponse& message) override;
  //void onCommand(Command& message) override;
  //void onCommandResponse(CommandResponse&) override {};

  //void doDecode(Buffer::Instance& buffer);
  //DecoderPtr createDecoder(DecoderCallbacks& callbacks);
  //MySQLSession& getSession() { return decoder_->getSession(); }

private:
  Network::ReadFilterCallbacks* read_callbacks_{};
  PostgreSQLFilterConfigSharedPtr config_;
  Buffer::OwnedImpl read_buffer_;
  Buffer::OwnedImpl write_buffer_;
  //std::unique_ptr<Decoder> decoder_;
  bool sniffing_{true};
};

}  // namespace PostgreSQLProxy
}  // namespace NetworkFilters
}  // namespace Extensions
}  // namespace Envoy
