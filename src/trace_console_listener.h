#ifndef DIAG_TRACE_CONSOLE_LISTENER_H_
#define DIAG_TRACE_CONSOLE_LISTENER_H_

#include "v8.h"

#include <map>

namespace diag {
namespace trace {

using namespace v8;

void ConsoleListener(const char* category, std::map<const char*, const char*> trace_map);
void RegisterConsoleListener(const FunctionCallbackInfo<Value>& info);

} // namespace trace
} // namespace diag

#endif // DIAG_TRACE_CONSOLE_LISTENER_H_
