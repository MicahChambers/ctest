
#include <yaml-cpp/yaml.h>

#include <boost/fusion/adapted/struct.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/algorithm.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/mpl/range_c.hpp>
#include <iostream>
#include <magic_enum.hpp>
#include <map>
#include <string>
#include <type_traits>

////////////////////////////////////////////////////////////////////

namespace struct_yaml_impl {

template <typename Struct>
struct GenericConvert {
  static YAML::Node encode(const Struct& rhs) {
    YAML::Node node;
    boost::fusion::for_each(
        boost::mpl::range_c<unsigned, 0,
                            boost::fusion::result_of::size<Struct>::value>(),
        [&](auto index) {
          std::string name =
              boost::fusion::extension::struct_member_name<Struct,
                                                           index>::call();
          auto value = boost::fusion::at_c<index>(rhs);
          if constexpr (std::is_enum_v<decltype(value)>) {
            node[name] = std::string(magic_enum::enum_name(value));
          } else {
            node[name] = value;
          }
        });
    return node;
  }

  static bool decode(const YAML::Node& node, Struct& rhs) {
    boost::fusion::for_each(
        boost::mpl::range_c<unsigned, 0,
                            boost::fusion::result_of::size<Struct>::value>(),
        [&](auto index) {
          std::string name =
              boost::fusion::extension::struct_member_name<Struct,
                                                           index>::call();
          if (node[name]) {
            using T = typename std::remove_reference<decltype(
                boost::fusion::at_c<index>(rhs))>::type;
            if constexpr (std::is_enum_v<T>) {
              std::optional<T> val =
                  magic_enum::enum_cast<T>(node.as<std::string>());
              if (val) {
                boost::fusion::at_c<index>(rhs) = *val;
              } else {  // throw?
              }
            } else {
              boost::fusion::at_c<index>(rhs) = node[name].as<T>();
            }
          }
        });
    return true;
  }
};

}  // namespace struct_yaml_impl

#define STRUCT_YAML(cls, ...)                                     \
  BOOST_FUSION_ADAPT_STRUCT(cls, __VA_ARGS__);                    \
  namespace YAML {                                                \
  template <>                                                     \
  struct convert<cls> : struct_yaml_impl::GenericConvert<cls> {}; \
  }

///////////////////////////////////////////////////////////////////
enum struct Greeting { HELLO = 0, WORLD = 3 };

struct Vec1 {
  double x = 0.1;
  std::vector<std::string> arr;
  std::array<int, 3> arr2;
  std::map<std::string, std::string> mp;
  Greeting greeting = Greeting::HELLO;
};

STRUCT_YAML(Vec1, x, arr, arr2, mp, greeting);

struct Vec3 {
  double x, y, z;
  std::string info;
  Vec1 v1;
};

STRUCT_YAML(Vec3, x, y, z, info, v1);

int main() {
  // clang-format off
  YAML::Node node = YAML::Load(
      "{"
        "\"x\": 1.0, "
        "\"y\": 3, "
        "\"z\": 0.32, "
        "\"info\": \"hello\", "
        "\"v1\": {"
          "\"x\": 3, "
          "\"arr\": [1, \"2\", \"3\"], "
          "\"arr2\": [1, 2, 3], "
          "\"mp\": {\"hello\": 1}"
        "}"
      "}");
  // clang-format on
  Vec3 v = node.as<Vec3>();
  node = v;
  // auto foo = node.as<Foo>();
  std::cerr << node << std::endl;
}
