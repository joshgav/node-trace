#include "trace_console_listener.h"
#include "trace_broker.h"

#include <iostream>
#include <map>

namespace diag {
namespace trace {

void ConsoleListener(const char* category, std::map<const char*, const char*> trace_map) {
  std::cout << "Category: " << category << std::endl;
  for (auto it = trace_map.begin(); it != trace_map.end(); ++it) {
    std::cout << it->first << ": " << it->second << std::endl;
  }
  std::cout << std::endl;
}

void RegisterConsoleListener(const FunctionCallbackInfo<Value>& info) {
  RegisterConsoleListener();
}

void RegisterConsoleListener() {
  TraceBroker::Singleton()->RegisterListener(&ConsoleListener);
}


} // namespace trace
} // namespace diag

