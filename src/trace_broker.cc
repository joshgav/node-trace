#include "./trace_broker.h"

namespace diag {
namespace trace {

bool TraceBroker::Trace(string category, map<string, string> trace_obj) {
  // Check if category is disabled, in which case return immediately.
  // This would be the place to capture contextual info such as current stack
  // and current locals.

  // Send to generalized processor.
  TraceInternal(category, trace_obj);
}

void TraceBroker::TraceNextTick(string category map<string, string> object) {
  // Call TraceBroker::Trace in the next tick
}

TraceBroker::TraceBroker() {

}

static TraceBroker TraceBroker::Singleton() {
  if (!s_trace_broker_singleton_) {
    s_trace_broker_singleton_ = new TraceBroker();
  }
  // TODO need to guard against failure to create above
  return s_trace_broker_singleton_;
}

bool TraceBroker::TraceInternal( string category, map<string, string> trace_obj ) {
  // Add timestamp, PID, TID, etc.
  

  // Now dispatch to subscribers
  Dispatch(category, trace_obj);
}

/**
 * Dispatch trace to native and JS subscribers
 */
bool TraceBroker::Dispatch( string category, map<string, string> trace_obj ) {
  DispatchNative(category, trace_obj);
  DispatchJSFromNative(category, trace_obj);
}

bool TraceBroker::DispatchNative( string category, map<string, string> trace_obj ) {
  // iterate through s_trace_listeners_native_ and invoke each
}

/**
 * info[0]: Local<String> category
 * info[1]: Local<Object> trace_obj
 * info[return]: Local<Boolean>
 */
bool TraceBroker::DispatchNativeFromJS( const FunctionCallbackInfo<Value>& info ) {
  // transform Local<Object> to map<string, string>

  DispatchNative(category, trace_obj);
  // not Dispatch() and not DispatchJSFromNative() to avoid a loop
}

bool TraceBroker::DispatchJSFromNative(string category, map<string, string> trace_obj) {
  // trace_js() is only initialized if js trace was `require`d in, otherwise it's null
  if (trace_js()) {
    // check if _dispatchJSFromNative has been added in JS, might be a race
    // convert map to Local<Object> (JSON)
    trace_js()->Get(CharStringToV8String("_dispatchJSFromNative")->Call(string category, map...);
  }
}

} // namespace trace
} // namespace diag

