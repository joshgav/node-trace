#include "trace_module.h"

#include "node.h"
#include "trace_broker.h"
#include "trace_console_listener.h"
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

  Local<Function> fnRegisterConsoleListener = Function::New(context, diag::trace::RegisterConsoleListener).ToLocalChecked();
  exports->Set(CharStringToV8String("enableNativeConsoleListener"), fnRegisterConsoleListener);
}

} // namespace trace
} // namespace diag

NODE_MODULE_CONTEXT_AWARE(trace_native, diag::trace::addon_context_register_func)

