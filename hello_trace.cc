#include <iostream>

#include "traces.pb.h"

int main() {
  anduril::telemetry::v1::TraceEvents traces;
  std::cerr << traces.ByteSizeLong() << std::endl;
  auto dur = traces.mutable_durations()->Add();
  std::cerr << traces.ByteSizeLong() << std::endl;

  std::cerr << traces.ByteSizeLong() << std::endl;
}
