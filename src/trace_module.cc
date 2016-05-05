#include "./trace_module.h"

namespace diag {
namespace trace {

using namespace std;

TraceBroker::TraceBroker() {

}

static TraceBroker TraceBroker::Singleton() {
  if (s_trace_brokers_.empty()) {
    try {
      // TODO Make threadsafe.
      s_trace_brokers_[0] = new TraceBroker();
    } catch (e) {
      // TODO Probably just warn that tracing couldn't be configured?
    }
  }
  // TODO need to guard against failure to create above
  return s_trace_brokers_[0];
}

bool TraceBroker::Trace(string category, map<string, string> object) {

}

void TraceBroker::TraceNextTick(string category map<string, string> object) {

}

bool TraceBroker::RegisterTraceListener(fp_trace_listner listener) {

}

bool TraceBroker::RegisterTraceListener(const FunctionCallbackInfo<Value>& args) {

}


addon_context_register_func(
    v8::Local<v8::Object> exports,
    v8::Local<v8::Value> module,
    v8::Local<v8::Context> context,
    void* priv) {

  v8::HandleScope handle_scope(exports->Isolate());
  TraceBroker tracer = TraceBroker::Singleton();
  Local<FunctionTemplate> fnTrace = Local<FunctionTemplate>::New(tracer->Trace);
  exports->Set(Local<String>::New("trace"), fnTrace->GetFunction());

}

} // namespace trace
} // namespace diag

NODE_MODULE_CONTEXT_AWARE(diag, diag::trace::addon_context_register_func)
