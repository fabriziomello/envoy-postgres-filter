package(default_visibility = ["//visibility:public"])

load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_binary",
    "envoy_cc_library"
)

load("@envoy_api//bazel:api_build_system.bzl", "api_proto_package")

envoy_cc_binary(
    name = "envoy",
    repository = "@envoy",
    deps = [
        ":postgres_config",
        "@envoy//source/exe:envoy_main_entry_lib",
    ],
)

api_proto_package()

envoy_cc_library(
    name = "postgres_lib",
    srcs = ["postgres_filter.cc"],
    hdrs = ["postgres_filter.h"],
    repository = "@envoy",
    deps = [
        "@envoy//include/envoy/network:filter_interface",
        "@envoy//include/envoy/server:filter_config_interface",
        "@envoy//include/envoy/stats:stats_interface",
        "@envoy//include/envoy/stats:stats_macros",
        "@envoy//source/common/buffer:buffer_lib",
        "@envoy//source/common/network:filter_lib"
    ],
)

envoy_cc_library(
    name = "postgres_config",
    srcs = ["postgres_config.cc"],
    hdrs = ["postgres_config.h"],
    repository = "@envoy",
    deps = [
        ":postgres_lib",
        ":pkg_cc_proto",
        "@envoy//include/envoy/network:filter_interface",
        "@envoy//include/envoy/registry:registry",
        "@envoy//include/envoy/server:filter_config_interface",
        "@envoy//source/extensions/filters/network/common:factory_base_lib"
    ],
)
