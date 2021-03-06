#include "envoy/config/resource_monitor/fixed_heap/v2alpha/fixed_heap.pb.validate.h"
#include "envoy/registry/registry.h"

#include "common/stats/isolated_store_impl.h"

#include "server/resource_monitor_config_impl.h"

#include "extensions/resource_monitors/fixed_heap/config.h"

#include "test/mocks/event/mocks.h"
#include "test/test_common/test_base.h"

namespace Envoy {
namespace Extensions {
namespace ResourceMonitors {
namespace FixedHeapMonitor {

TEST(FixedHeapMonitorFactoryTest, CreateMonitor) {
  auto factory =
      Registry::FactoryRegistry<Server::Configuration::ResourceMonitorFactory>::getFactory(
          "envoy.resource_monitors.fixed_heap");
  EXPECT_NE(factory, nullptr);

  envoy::config::resource_monitor::fixed_heap::v2alpha::FixedHeapConfig config;
  config.set_max_heap_size_bytes(std::numeric_limits<uint64_t>::max());
  Event::MockDispatcher dispatcher;
  Stats::IsolatedStoreImpl stats_store;
  Api::ApiPtr api = Api::createApiForTest(stats_store);
  Server::Configuration::ResourceMonitorFactoryContextImpl context(dispatcher, *api);
  auto monitor = factory->createResourceMonitor(config, context);
  EXPECT_NE(monitor, nullptr);
}

} // namespace FixedHeapMonitor
} // namespace ResourceMonitors
} // namespace Extensions
} // namespace Envoy
