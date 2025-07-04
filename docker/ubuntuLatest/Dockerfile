# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

FROM ubuntu:latest@sha256:440dcf6a5640b2ae5c77724e68787a906afb8ddee98bf86db94eea8528c2c076
ENV DEBIAN_FRONTEND=noninteractive

WORKDIR /work

#install grpc and abseil
ARG GRPC_VERSION=v1.38.0
RUN apt-get update && apt-get install -y build-essential autoconf libtool pkg-config cmake git libssl-dev && \
    git clone --depth=1 -b $GRPC_VERSION  https://github.com/grpc/grpc.git && \
    cd grpc && git submodule update --init && \
    mkdir -p "third_party/abseil-cpp/build" && cd "third_party/abseil-cpp/build" && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_POSITION_INDEPENDENT_CODE=TRUE .. && \
    make -j${nproc} install && cd ../../.. && \
    mkdir build && cd build &&  \
    cmake \
        -DCMAKE_BUILD_TYPE=Release \
        -DgRPC_INSTALL=ON \
        -DgRPC_BUILD_TESTS=OFF \
        -DgRPC_ABSL_PROVIDER=package \
        -DgRPC_SSL_PROVIDER=package \
        .. && \
    make -j${nproc} install && make clean && ldconfig && \
    cd ../..

#install opentelemetry-cpp
RUN apt-get install -y --no-install-recommends libcurl4-openssl-dev && git clone --depth=1 https://github.com/open-telemetry/opentelemetry-cpp.git && \
    cd opentelemetry-cpp && git submodule update --init && \
    mkdir -p build && cd build && \
    cmake \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_POSITION_INDEPENDENT_CODE=TRUE  \
        -DWITH_ZIPKIN=ON \
        -DBUILD_TESTING=OFF \
        -DWITH_OTLP_GRPC=ON \
        -DWITH_OTLP_HTTP=ON \
        .. && \
    make -j${nproc} install && ldconfig && \
    cd ../..
