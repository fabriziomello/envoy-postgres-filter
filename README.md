# Envoy PostgreSQL Network Filter Extension

WIP project based on current issues:
- [PostgreSQL-aware filter](https://github.com/envoyproxy/envoy/issues/2861)
- [Postgres Statistics Envoy Network Filter](https://github.com/envoyproxy/envoy/issues/9107)

## Building

To build the Envoy static binary:

1. `git submodule update --init`
2. `bazel build //:envoy`
