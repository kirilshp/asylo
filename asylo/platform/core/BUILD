#
# Copyright 2018 Asylo authors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

licenses(["notice"])  # Apache v2.0

package(
    default_visibility = ["//asylo:implementation"],
)

exports_files(["LICENSE"])

# Core untrusted Asylo components.
cc_library(
    name = "untrusted_core",
    srcs = [
        "enclave_config_util.cc",
        "enclave_config_util.h",
        "enclave_manager.cc",
    ],
    hdrs = [
        "enclave_client.h",
        "enclave_manager.h",
    ],
    deps = [
        ":shared_name",
        ":shared_resource_manager",
        "//asylo:enclave_proto_cc",
        "//asylo/platform/common:time_util",
        "//asylo/util:logging",
        "//asylo/util:status",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/synchronization",
        "@com_google_absl//absl/time",
        "@com_google_absl//absl/types:variant",
    ],
)

# Trusted global state.
cc_library(
    name = "trusted_global_state",
    srcs = select({
        "@com_google_asylo//asylo": ["trusted_global_state.cc"],
        "//conditions:default": ["fake_trusted_global_state.cc"],
    }),
    hdrs = ["trusted_global_state.h"],
    linkstatic = 1,
    deps = [
        "//asylo:enclave_proto_cc",
        "//asylo/util:status",
    ] + select({
        "@com_google_asylo//asylo": [],
        "//conditions:default": ["@com_google_absl//absl/base:core_headers"],
    }),
)

# Core trusted Asylo components.
cc_library(
    name = "trusted_core",
    hdrs = [
        "trusted_global_state.h",
    ],
    linkstatic = 1,
    deps = [
        ":shared_name",
        ":trusted_global_state",
        "//asylo:enclave_proto_cc",
        "//asylo/platform/arch:trusted_arch",
        "//asylo/util:status",
    ],
)

# Trusted application base class for user applications. This target is a
# user-facing leaf in the dependency tree, and no other runtime target may
# depend on it.
cc_library(
    name = "trusted_application",
    srcs = ["trusted_application.cc"],
    hdrs = ["trusted_application.h"],
    linkstatic = 1,
    deps = [
        ":shared_name",
        ":trusted_core",
        "//asylo:enclave_proto_cc",
        "//asylo/identity:init",
        "//asylo/platform/arch:trusted_arch",
        "//asylo/platform/posix/io:io_manager",
        "//asylo/platform/posix/signal:signal_manager",
        "//asylo/platform/posix/threading:thread_manager",
        "//asylo/util:logging",
        "//asylo/util:status",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/synchronization",
    ],
)

# An untrusted mutex object which depends on host kernel resources.
cc_library(
    name = "untrusted_mutex",
    srcs = [
        "untrusted_mutex.cc",
    ],
    hdrs = [
        "untrusted_mutex.h",
    ],
    deps = [
        "//asylo/platform/arch:trusted_arch",
    ],
)

# Shared name data type used by both trusted and untrusted code.
cc_library(
    name = "shared_name",
    hdrs = [
        "shared_name.h",
        "shared_name_kind.h",
    ],
    deps = ["//asylo/platform/common:hash_combine"],
)

cc_library(
    name = "shared_resource_manager",
    srcs = ["shared_resource_manager.cc"],
    hdrs = ["shared_resource_manager.h"],
    deps = [
        ":shared_name",
        "//asylo/util:status",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/synchronization",
    ],
)

# Sanity check test for enclave clock variables.
cc_test(
    name = "enclave_clock_test",
    srcs = ["enclave_clock_test.cc"],
    tags = [
        "regression",
    ],
    deps = [
        ":shared_resource_manager",
        ":untrusted_core",
        "//asylo/platform/common:time_util",
        "//asylo/test/util:test_main",
        "//asylo/util:status",
        "@com_google_absl//absl/time",
        "@com_google_googletest//:gtest",
    ],
)
