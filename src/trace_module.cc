#include "trace_module.h"
#include "trace_broker.h"

namespace diag {
namespace trace {

addon_context_register_func(
    v8::Local<v8::Object> exports,
    v8::Local<v8::Value> module,
    v8::Local<v8::Context> context,
    void* priv) {
  
  // Provides access to native listeners for JS publishers.
  Local<Function> fnDispatchNative = Local<Function>::New(context, TraceBroker::Singleton()->DispatchNativeFromJS);
  exports->Set(CharStringToV8String("_dispatchNativeFromJS"), fnDispatchNative);

  // Provides access to JS listeners for native publishers through `_dispatchJSFromNative`.
  TraceBroker::set_trace_js(exports);
}

} // namespace trace
} // namespace diag

NODE_MODULE_CONTEXT_AWARE(diag, diag::trace::addon_context_register_func)

