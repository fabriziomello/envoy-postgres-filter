#pragma once

#include "postgres_proxy.pb.h"
#include "postgres_proxy.pb.validate.h"

#include "extensions/filters/network/common/factory_base.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace PostgreSQLProxy {

/**
 * Config registration for the PostgreSQL proxy filter.
 */
class PostgreSQLConfigFactory : public Common::FactoryBase<
                               postgres_proxy::PostgreSQLProxy> {
public:
  PostgreSQLConfigFactory() : FactoryBase("envoy.filters.network.postgres_proxy";) {}

private:
  Network::FilterFactoryCb createFilterFactoryFromProtoTyped(
      const postgres_proxy::PostgreSQLProxy& proto_config,
      Server::Configuration::FactoryContext& context) override;
};

} // namespace PostgreSQLProxy
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
