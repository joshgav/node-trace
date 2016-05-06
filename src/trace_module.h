#include "node.h"
#include "v8.h"

namespace diag {
namespace trace {

addon_context_register_func(
    v8::Local<v8::Object> exports,
    v8::Local<v8::Value> module,
    v8::Local<v8::Context> context,
    void* priv);

} // namespace trace
} // namespace diag

