#include "v8.h"
#include "node.h"

namespace diag {
namespace trace {

using namespace std;

// TODO Should be a singleton or static and threadsafe so that it can be used
// safely everywhere, even say in the _debug_agent.
class TraceBroker {

public:
  // Called by native publishers to publish traces.
  bool Trace(string category, map<string, string> object);

  void TraceNextTick(string category, map<string, string> object);

  // Called by native listeners to subscribe to traces.
  bool RegisterTraceListener(fp_trace_listner listener);

  // TODO Add filtering on publish and subscribe sides.

  TraceBroker Singleton();

protected:
  TraceBroker();

  // Used to process traces for native listeners.
  bool OnIncomingTraceNative(string category, map<string, string> object);
  bool NotifyTraceNative(string category, map<string, string> object);

private:
  // we could potentially have a few brokers, best to take minor hit of array
  // For now we'll only use 1 for the singleton.
  static array<TraceBroker,16> s_trace_brokers_;
  static array<fp_trace_listener, 16> s_trace_listeners_native_;

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
