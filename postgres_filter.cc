#include "postgres_filter.h"

#include "common/buffer/buffer_impl.h"
#include "common/common/assert.h"
#include "common/common/logger.h"

//#include "extensions/filters/network/well_known_names.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace PostgreSQLProxy {

PostgreSQLFilterConfig::PostgreSQLFilterConfig(const std::string& stat_prefix, Stats::Scope& scope)
    : scope_(scope), stat_prefix_(stat_prefix), stats_(generateStats(stat_prefix, scope)) {}

PostgreSQLFilter::PostgreSQLFilter(PostgreSQLFilterConfigSharedPtr config) : config_(std::move(config)) {}

void PostgreSQLFilter::initializeReadFilterCallbacks(Network::ReadFilterCallbacks& callbacks) {
  read_callbacks_ = &callbacks;
}

Network::FilterStatus PostgreSQLFilter::onData(Buffer::Instance& data, bool) {
  if (sniffing_) {
    read_buffer_.add(data);
  }
  ENVOY_LOG(info, "OnGres is here!!!! {}", data.toString());
  return Network::FilterStatus::Continue;
}

Network::FilterStatus PostgreSQLFilter::onWrite(Buffer::Instance& data, bool) {
  if (sniffing_) {
    write_buffer_.add(data);
  }
  return Network::FilterStatus::Continue;
}

Network::FilterStatus PostgreSQLFilter::onNewConnection() {
  config_->stats_.sessions_.inc();
  return Network::FilterStatus::Continue;
}

} // namespace PostgreSQLProxy
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
