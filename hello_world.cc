
// Demonstrates basic usage of the OpenTracing API. Uses OpenTracing's
// mocktracer to capture all the recorded spans as JSON.

#include <opentracing/tracer.h>

#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <sstream>
#include <unordered_map>

// MockTracer provides implements the OpenTracing Tracer API. It provides
// convenient access to finished spans in such a way as to support testing.
class MicahTracer : public opentracing::Tracer,
                    public std::enable_shared_from_this<MicahTracer> {
 public:
  explicit MicahTracer() {}

  std::unique_ptr<opentracing::Span> StartSpanWithOptions(
      opentracing::string_view operation_name,
      const opentracing::StartSpanOptions& options) const noexcept override {
    return nullptr;
  }

  void Close() noexcept override {}

  opentracing::expected<void> Inject(const opentracing::SpanContext& sc,
                                     std::ostream& writer) const override {
    return {};
  }

  opentracing::expected<void> Inject(
      const opentracing::SpanContext& sc,
      const opentracing::TextMapWriter& writer) const override {
    return {};
  }

  opentracing::expected<void> Inject(
      const opentracing::SpanContext& sc,
      const opentracing::HTTPHeadersWriter& writer) const override {
    return {};
  }

  opentracing::expected<std::unique_ptr<opentracing::SpanContext>> Extract(
      std::istream& reader) const override {
    return {};
  }

  opentracing::expected<std::unique_ptr<opentracing::SpanContext>> Extract(
      const opentracing::TextMapReader& reader) const override {
    return {};
  }

  opentracing::expected<std::unique_ptr<opentracing::SpanContext>> Extract(
      const opentracing::HTTPHeadersReader& reader) const override {
    return {};
  }

 private:
  //  std::unique_ptr<Recorder> recorder_;
  //  PropagationOptions propagation_options_;
  //  std::mutex mutex_;
  //  std::vector<SpanData> spans_;
};

int main() {
  std::shared_ptr<opentracing::Tracer> tracer{new MicahTracer{}};

  //  auto parent_span = tracer->StartSpan("parent");
  //  assert(parent_span);
  //  //
  //  // Create a child span.
  //  {
  //    auto child_span =
  //        tracer->StartSpan("childA", {ChildOf(&parent_span->context())});
  //    assert(child_span);
  //
  //    // Set a simple tag.
  //    child_span->SetTag("simple tag", 123);
  //
  //    // Set a complex tag.
  //    child_span->SetTag("complex tag",
  //                       Values{123, Dictionary{{"abc", 123}, {"xyz", 4.0}}});
  //
  //    // Log simple values.
  //    child_span->Log({{"event", "simple log"}, {"abc", 123}});
  //
  //    // Log complex values.
  //    child_span->Log({{"event", "complex log"},
  //                     {"data", Dictionary{{"a", 1}, {"b", Values{1, 2}}}}});
  //
  //    child_span->Finish();
  //  }
  //  //
  //  //  // Create a follows from span.
  //  //  {
  //  //    auto child_span =
  //  //        tracer->StartSpan("childB",
  //  {FollowsFrom(&parent_span->context())});
  //  //
  //  //    // child_span's destructor will finish the span if not done so
  //  //    explicitly.
  //  //  }
  //  //
  //  //  // Use custom timestamps.
  //  //  {
  //  //    auto t1 = SystemClock::now();
  //  //    auto t2 = SteadyClock::now();
  //  //    auto span = tracer->StartSpan(
  //  //        "useCustomTimestamps",
  //  //        {ChildOf(&parent_span->context()), StartTimestamp(t1)});
  //  //    assert(span);
  //  //    span->Finish({FinishTimestamp(t2)});
  //  //  }
  //  //
  //  //  // Extract and Inject a span context.
  //  //  {
  //  //    std::unordered_map<std::string, std::string> text_map;
  //  //    TextMapCarrier carrier(text_map);
  //  //    auto err = tracer->Inject(parent_span->context(), carrier);
  //  //    assert(err);
  //  //    auto span_context_maybe = tracer->Extract(carrier);
  //  //    assert(span_context_maybe);
  //  //    auto span = tracer->StartSpan("propagationSpan",
  //  //                                  {ChildOf(span_context_maybe->get())});
  //  //  }
  //  //
  //  //  // You get an error when trying to extract a corrupt span.
  //  //  {
  //  //    std::unordered_map<std::string, std::string> text_map = {
  //  //        {"x-ot-span-context", "123"}};
  //  //    TextMapCarrier carrier(text_map);
  //  //    auto err = tracer->Extract(carrier);
  //  //    assert(!err);
  //  //    assert(err.error() == span_context_corrupted_error);
  //  //    // How to get a readable message from the error.
  //  //    std::cout << "Example error message: \"" << err.error().message() <<
  //  //    "\"\n";
  //  //  }
  //  //
  //  //  parent_span->Finish();
  //  //  tracer->Close();
  //  //
  //  //  std::cout << "\nRecorded spans as JSON:\n\n";
  //  //  std::cout << oss.str() << "\n";
  return 0;
}
