// #if defined(_MSC_VER)
// #include <opentelemetry/exporters/etw/etw_logger.h>
// #include <opentelemetry/exporters/etw/etw_tracer.h>
// #endif

#include <opentelemetry/version.h>

#include <opentelemetry/exporters/otlp/otlp_grpc_forward_proxy.h>

#include <opentelemetry/sdk/trace/samplers/composable_always_on.h>
#include <opentelemetry/sdk/trace/samplers/composable_always_off.h>
#include <opentelemetry/sdk/configuration/registry_factory.h>

#include <opentelemetry/resource_detectors/container_detector_builder.h>
#include <opentelemetry/resource_detectors/container_detector.h>
#include <opentelemetry/resource_detectors/env_entity_detector.h>
#include <opentelemetry/resource_detectors/host_detector_builder.h>
#include <opentelemetry/resource_detectors/host_detector.h>
#include <opentelemetry/resource_detectors/process_detector_builder.h>
#include <opentelemetry/resource_detectors/process_detector.h>
#include <opentelemetry/resource_detectors/service_detector_builder.h>
#include <opentelemetry/resource_detectors/service_detector.h>
