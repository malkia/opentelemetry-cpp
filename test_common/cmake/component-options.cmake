# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

# All components options

if(NOT DEFINED ENABLE_COMPONENTS)
    set(ENABLE_COMPONENTS ON)
endif()

set(WITH_OTLP_GRPC ${ENABLE_COMPONENTS} CACHE BOOL "" FORCE)
set(WITH_OTLP_HTTP ${ENABLE_COMPONENTS} CACHE BOOL "" FORCE)
set(WITH_OTLP_FILE ${ENABLE_COMPONENTS} CACHE BOOL "" FORCE)

set(WITH_PROMETHEUS ${ENABLE_COMPONENTS} CACHE BOOL "" FORCE)
set(WITH_ZIPKIN ${ENABLE_COMPONENTS} CACHE BOOL "" FORCE)
set(WITH_ELASTICSEARCH ${ENABLE_COMPONENTS} CACHE BOOL "" FORCE)

if(WIN32)
  set(WITH_ETW ${ENABLE_COMPONENTS} CACHE BOOL "" FORCE)
endif()

if(WITH_ABI_VERSION_1)
  set(WITH_OPENTRACING ${ENABLE_COMPONENTS} CACHE BOOL "" FORCE)
endif()
