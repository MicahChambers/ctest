load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "opentracing",
    sha256 = "1d84e979d51de993cd5518aca7d63d98999293dfa5220c50ba87948293c3d15b",
    strip_prefix = "opentracing-cpp-4bb431f7728eaf383a07e86f9754a5b67575dab0",
    urls = ["https://github.com/opentracing/opentracing-cpp/archive/4bb431f7728eaf383a07e86f9754a5b67575dab0.zip"],
)

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "rules_proto",
    sha256 = "602e7161d9195e50246177e7c55b2f39950a9cf7366f74ed5f22fd45750cd208",
    strip_prefix = "rules_proto-97d8af4dc474595af3900dd85cb3a29ad28cc313",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_proto/archive/97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz",
        "https://github.com/bazelbuild/rules_proto/archive/97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz",
    ],
)

load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")

rules_proto_dependencies()

rules_proto_toolchains()

http_archive(
    name = "yaml-cpp",
    sha256 = "8f8c556d9e7710c8be167ef7393730f7b1c94b48e4b17bea5746f95c85dbf38a",
    strip_prefix = "yaml-cpp-6701275f1910bf63631528dfd9df9c3ac787365b",
    urls = [
        "https://github.com/jbeder/yaml-cpp/archive/6701275f1910bf63631528dfd9df9c3ac787365b.zip",
    ],
)

http_archive(
    name = "com_github_nelhage_rules_boost",
    sha256 = "3b492b2fffcf3925299e38de38cb116713c09d4e902dcdbb6eaa10b775d7db87",
    strip_prefix = "rules_boost-0cc5bf5513c067917b5e083cee22a8dcdf2e0266",
    urls = ["https://github.com/nelhage/rules_boost/archive/0cc5bf5513c067917b5e083cee22a8dcdf2e0266.zip"],
)

load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")

boost_deps()

http_archive(
    name = "magic_enum",
    build_file = "@//third_party:magic_enum.BUILD",
    sha256 = "b655185e8040f5a741e7a50338f3240a3091312dea7aa989eab92ac29972dc2c",
    strip_prefix = "magic_enum-33a62f9847aaa29c32a2338d50ae15e41a0da671",
    urls = [
        "https://github.com/Neargye/magic_enum/archive/33a62f9847aaa29c32a2338d50ae15e41a0da671.tar.gz",
    ],
)
