#ifndef DIAG_TRACE_MODULE_H_
#define DIAG_TRACE_MODULE_H_ 

#include "v8.h"

namespace diag {
namespace trace {

using namespace v8;

void addon_context_register_func(
    Local<Object> exports,
    Local<Value> module,
    Local<Context> context,
    void* priv);

} // namespace trace
} // namespace diag

#endif // DIAG_TRACE_MODULE_H_
