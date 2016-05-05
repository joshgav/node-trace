#include "v8.h"
#include "node.h"

namespace diag {
namespace trace {

using namespace std;

// TODO Should be a singleton or static and threadsafe so that it can be used
// safely everywhere, even say in the _debug_agent.
class TraceBroker {

public:
  // Publishers 
  bool Trace(string category, map<string, string> object);

  // No point in returning anything since we don't know how things will go.
  void TraceNextTick(string category, map<string, string> object);

  // This is where native subscribers can register.
  bool RegisterTraceListener(fp_trace_listner listener);

  // This is for JS listeners. Args:
  // args[0]: (category, object) => { return void; }
  bool RegisterTraceListener(const FunctionCallbackInfo<Value>& args);

  TraceBroker Singleton();

protected:
  TraceBroker();

private:
  // we could potentially have a few brokers, best to take minor hit of array
  // For now we'll only use 
  static array<TraceBroker,16> s_trace_brokers_;

} // class TraceBroker

// Native subscribers are notified through a callback of this type.
typedef void (*fp_trace_listener)(string category, map<string, string> object); 


addon_context_register_func(
    v8::Local<v8::Object> exports,
    v8::Local<v8::Value> module,
    v8::Local<v8::Context> context,
    void* priv);

} // namespace trace
} // namespace diag
