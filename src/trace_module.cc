#include "./trace_module.h"

namespace diag {
namespace trace {

using namespace std;

TraceBroker::TraceBroker() {
  Local<Object> internal_exports;
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

bool TraceBroker::Trace(string category, map<string, string> trace_obj) {

  OnIncomingTraceNative(category, trace_obj);
}

void TraceBroker::TraceNextTick(string category map<string, string> object) {

  // Call TraceBroker::Trace in the next tick
}

bool TraceBroker::RegisterTraceListener(fp_trace_listner listener) {
  s_trace_listeners_native_.add(listener);
}

bool TraceBroker::OnIncomingTraceNative( string category, map<string, string> trace_obj ) {
  // Add timestamp, PID, TID, etc.
  NotifyTraceNative(cateogry, trace_obj);
}

bool TraceBroker::NotifyTraceNative( string category, map<string, string> trace_obj ) {
  // need to make sure we avoid an infinite loop from native->JS->native
  internal_exports->Get(Local<String>::New("_notifyTrace"))->Call(string category, map...);
}


diag::trace::addon_context_register_func(
    v8::Local<v8::Object> exports,
    v8::Local<v8::Value> module,
    v8::Local<v8::Context> context,
    void* priv) {
  
  internal_exports = exports;
  v8::HandleScope handle_scope(exports->Isolate());

  // import `../lib/trace_module.js` and invoke with `exports` local var
  // store `_onIncomingTrace` and `_notifyTrace` JS funcs so 
  // TraceBroker::Trace can call them to notify JS listeners
  // 
  // Also provide access to native `OnIncomingTraceNative` and
  // `NotifyTraceNative` so JS funcs can notify native listeners too.

  TraceBroker tracer = TraceBroker::Singleton();
  Local<Function> fnOnIncomingTraceNative = Local<Function>::New(context, tracer->OnIncomingTraceNative);
  Local<Function> fnNotifyTraceNative     = Local<Function>::New(context, tracer->NotifyTraceNative);
  exports->Set(Local<String>::New("onIncomingTraceNative"), fnOnIncomingTraceNative);
  exports->Set(Local<String>::New("notifyTraceNative"), fnNotifyTraceNative);

}

} // namespace trace
} // namespace diag

NODE_MODULE_CONTEXT_AWARE(diag, diag::trace::addon_context_register_func)
