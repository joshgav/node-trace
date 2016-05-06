#include "node.h"
#include "trace_module.h"
#include "trace_broker.h"
#include "diag_utils.h"

namespace diag {
namespace trace {

using namespace diag::utils;

using namespace v8;

void addon_context_register_func(
    Local<Object> exports,
    Local<Value> module,
    Local<Context> context,
    void* priv) {
  
  // Provides access to native listeners for JS publishers.
  Local<Function> fnDispatchNativeFromJS = Function::New(context, TraceBroker::DispatchNativeFromJS_Static).ToLocalChecked();
  exports->Set(CharStringToV8String("_dispatchNativeFromJS"), fnDispatchNativeFromJS);

  // Provides access to JS listeners for native publishers through `_dispatchJSFromNative`.
  TraceBroker::Singleton()->set_trace_js(exports);
}

} // namespace trace
} // namespace diag

NODE_MODULE_CONTEXT_AWARE(trace_native, diag::trace::addon_context_register_func)

