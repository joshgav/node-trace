#include "trace_broker.h"
#include "diag_utils.h"
#include "trace_console_listener.h"
#include "v8.h"

diag::trace::TraceBroker* diag::trace::TraceBroker::s_trace_broker_singleton_ = nullptr;

namespace diag {
namespace trace {

using namespace diag::utils;
using namespace v8;

bool TraceBroker::Trace(const char* category, std::map<const char*, const char*> trace_map) {
  // Check if category is disabled, in which case return immediately.
  // This would be the place to capture contextual info such as current stack
  // and current locals.

  // Send to generalized processor.
  return TraceInternal(category, trace_map);
}

void TraceBroker::TraceNextTick(const char* category, std::map<const char*, const char*> object) {
  // Call TraceBroker::Trace in the next tick
}

TraceBroker::TraceBroker() {
}

TraceBroker* TraceBroker::Singleton() {
  if (s_trace_broker_singleton_ == nullptr) {
    s_trace_broker_singleton_ = new TraceBroker();
  }
  // TODO need to guard against failure to create above
  return s_trace_broker_singleton_;
}

bool TraceBroker::TraceInternal(const char* category, std::map<const char*, const char*> trace_map) {
  // Add timestamp, PID, TID, etc.
  

  // Now dispatch to subscribers
  return Dispatch(category, trace_map);
}

/**
 * Dispatch trace to native and JS subscribers
 */
bool TraceBroker::Dispatch(const char* category, std::map<const char*, const char*> trace_map) {
  bool ret = DispatchNative(category, trace_map);
  bool ret2 = DispatchJSFromNative(category, trace_map);

  return (ret && ret2);
}

bool TraceBroker::DispatchNative(const char* category, std::map<const char*, const char*> trace_map) {
  // iterate through s_trace_listeners_native_ and invoke each one
  for (auto it = s_trace_listeners_native_.begin(); it != s_trace_listeners_native_.end(); ++it) {
    (**it)(category, trace_map);
  }
  // TODO better error handling
  return true;
}

void TraceBroker::DispatchNativeFromJS_Static(const FunctionCallbackInfo<Value>& info) {
  TraceBroker::Singleton()->DispatchNativeFromJS(info);
}

/**
 * info[0]: Local<String> category
 * info[1]: Local<Object> trace_obj
 * info[return]: Local<Boolean>
 */
void TraceBroker::DispatchNativeFromJS(const FunctionCallbackInfo<Value>& info) {
  Local<Context> ctx = Isolate::GetCurrent()->GetCurrentContext();
  Local<String> category_js = info[0]->ToString(ctx).ToLocalChecked();
  const char* category = V8StringToCharString(category_js);

  // transform Local<Object> to map<const char*, const char*>
  std::map<const char*, const char*> trace_map;
  Local<Object> trace_obj = info[1]->ToObject(ctx).ToLocalChecked();
  Local<Array> trace_obj_keys = trace_obj->GetPropertyNames(ctx).ToLocalChecked();

  for ( uint8_t i = 0; i < trace_obj_keys->Length(); i++ ) {
    Local<String> trace_obj_key = trace_obj_keys->Get(ctx, i).ToLocalChecked()->ToString(ctx).ToLocalChecked();
    Local<String> trace_obj_val = trace_obj->Get(ctx, trace_obj_key).ToLocalChecked()->ToString(ctx).ToLocalChecked();
    trace_map[V8StringToCharString(trace_obj_key)] = V8StringToCharString(trace_obj_val);
  }

  // not Dispatch() and not DispatchJSFromNative() to avoid a loop
  bool ret = DispatchNative(category, trace_map);
  info.GetReturnValue().Set(ret);
}

bool TraceBroker::DispatchJSFromNative(const char* category, std::map<const char*, const char*> trace_map) {
  // trace_js() is only initialized if js trace was `require`d in, otherwise it's an empty object
  Local<Context> ctx = Isolate::GetCurrent()->GetCurrentContext();
  if (trace_js()->Has(ctx, CharStringToV8String("_dispatchJSFromNative")).IsJust()) {
    Local<String> category_js = CharStringToV8String(category);

    // convert map to Local<Object>
    Local<Object> trace_obj = Object::New(Isolate::GetCurrent()); 
    for (auto it = trace_map.begin(); it != trace_map.end(); ++it) {
      trace_obj->Set(ctx, CharStringToV8String(it->first), CharStringToV8String(it->second));
    }

    Local<Value> argv[2];
    argv[0] = category_js;
    argv[1] = trace_obj;
    Function::Cast(*trace_js()->Get(CharStringToV8String("_dispatchJSFromNative")))->Call(Local<Value>(), 2, argv);
  }

  // TODO fix error handling
  return true;
}

} // namespace trace
} // namespace diag

