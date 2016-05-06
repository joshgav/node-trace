#ifndef DIAG_TRACE_CONSOLE_LISTENER_H_
#define DIAG_TRACE_CONSOLE_LISTENER_H_

#include <map>

namespace diag {
namespace trace {

void ConsoleListener(const char* category, std::map<const char*, const char*> trace_map);

} // namespace trace
} // namespace diag

#endif // DIAG_TRACE_CONSOLE_LISTENER_H_
