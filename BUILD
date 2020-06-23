load("@rules_proto//proto:defs.bzl", "proto_library")
load("@bazel_tools//tools/build_defs/pkg:pkg.bzl", "pkg_tar")

cc_binary(
    name = "virtual_deconstructor",
    srcs = ["virtual_deconstructor.cc"],
)

cc_binary(
    name = "envExpand",
    srcs = ["envExpand.cc"],
)


cc_binary(
    name = "string_assign_allo",
    srcs = ["string_assign_allo.cc"],
)

cc_binary(
    name = "string_literal",
    srcs = ["string_literal.cc"],
)

cc_binary(
    name = "hello_proto",
    srcs = ["hello_proto.cc"],
    deps = [":foo_cc_proto"],
)

cc_proto_library(
    name = "foo_cc_proto",
    deps = [":foo_proto"],
)

proto_library(
    name = "foo_proto",
    srcs = ["foo.proto"],
)

cc_binary(
    name = "hello_trace",
    srcs = ["hello_trace.cc"],
    deps = [":traces_cc_proto"],
)

cc_proto_library(
    name = "traces_cc_proto",
    deps = [":traces_proto"],
)

cc_binary(
    name = "yaml-struct",
    srcs = [
        "yaml_struct.cc",
    ],
    deps = [
        "@boost//:fusion",
        "@boost//:phoenix",
        "@magic_enum",
        "@yaml-cpp",
    ],
    copts = ['-std=c++17'],
)

proto_library(
    name = "traces_proto",
    srcs = ["traces.proto"],
    deps = [
        "@com_google_protobuf//:timestamp_proto",
    ],
)

#pkg_tar(
#    name = "count_allocs_pkg",
#    srcs = [":count_allocs"],
#    extension = "tar.bz2",
#)
#
#pkg_tar(
#    name = "debian-data",
#    extension = "tar.gz",
#    deps = [
#        ":bazel-bin",
#        ":bazel-tools",
#    ],
#)
