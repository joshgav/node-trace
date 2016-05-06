#include "v8.h"
#include "node.h"
#include "diag_utils.h"
#include "third_party/json/json.hpp"

#include <string>
#include <map>
#include <vector>
#include <array>

namespace diag {
namespace trace {

// TODO Should be a singleton or static and threadsafe so that it can be used
// safely everywhere, even say in the _debug_agent.
class TraceBroker {
  // TODO Add filtering on publish and subscribe sides.

public:
  // Called by native publishers to publish traces.
  bool Trace(string category, map<string, string> object);

  inline void TraceNextTick(string category, map<string, string> object) {
    // process.nextTick(Trace());
  }

  // Called by native listeners to subscribe to traces.
  inline bool RegisterTraceListener(fp_trace_listner listener) {
    s_trace_listeners_native_.push_back(listener);
  }

  static TraceBroker Singleton();

  inline Local<Object> trace_js() { return trace_js_; }
  inline void set_trace_js(Local<Object> value) { trace_js_ = value; }

protected:
  TraceBroker();

  // Common trace processing.
  bool TraceInternal(string category, map<string, string> object);

  // Dispatch events to listeners
  bool Dispatch(string category, map<string, string> object);
  bool DispatchNative(string category, map<string, string> object);
  bool DispatchNativeFromJS(const FunctionCallbackInfo<Value>& info);
  bool DispatchJSFromNative(string category, map<string, string> object);

private:
  static TraceBroker s_trace_broker_singleton_;

  vector<fp_trace_listener> s_trace_listeners_native_;
  Local<Object> trace_js_;

} // class TraceBroker

// Native subscribers are notified through a callback of this type.
typedef void (*fp_trace_listener)(string category, map<string, string> object); 


} // namespace trace
} // namespace diag

