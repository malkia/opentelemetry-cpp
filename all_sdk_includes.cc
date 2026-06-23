// #if defined(_MSC_VER)
// #include <opentelemetry/exporters/etw/etw_logger.h>
// #include <opentelemetry/exporters/etw/etw_tracer.h>
// #endif

#include <opentelemetry/version.h>
#include <opentelemetry/exporters/otlp/otlp_grpc_forward_proxy.h>
#include <opentelemetry/sdk/trace/samplers/composable_always_on.h>
#include <opentelemetry/sdk/trace/samplers/composable_always_off.h>
