#ifndef DIAG_TRACE_BROKER_H_
#define DIAG_TRACE_BROKER_H_

#include "v8.h"
#include "diag_utils.h"

#include <map>
#include <vector>

namespace diag {
namespace trace {

using namespace v8;

class TraceBroker {

public:
  /** Called by native components to publish traces. */
  bool Trace(const char* category, std::map<const char*, const char*> trace_map);

  /** Enqueue trace for execution at another time/place.
   *  Could be another thread or a uv_async_t handle.
   */
  void TraceNextTick(const char* category, std::map<const char*, const char*> trace_map);

  /** Called by native components to subscribe to traces.
   *  TODO Allow filtering by category names.
   */
  typedef void (*fp_trace_listener)(const char* category, std::map<const char*, const char*> trace_map); 
  inline void RegisterListener(fp_trace_listener listener) {
    s_trace_listeners_native_.push_back(&listener);
  }

  static TraceBroker* Singleton();

  /**
   * If user has imported `trace.js` this returns a reference
   * to the JS `exports` object. This allows us to send traces from
   * native publishers to JS listeners.
   */
  inline Local<Object> trace_js() { return trace_js_; }
  inline void set_trace_js(Local<Object> value) { trace_js_ = value; }

  // must be public for access from JS
  void DispatchNativeFromJS(const FunctionCallbackInfo<Value>& info);
  static void DispatchNativeFromJS_Static(const FunctionCallbackInfo<Value>& info);

protected:
  TraceBroker();

  // Common trace processing.
  bool TraceInternal(const char* category, std::map<const char*, const char*> trace_map);

  // Dispatchers for native and JS listeners.
  bool Dispatch(const char* category, std::map<const char*, const char*> trace_map);
  bool DispatchNative(const char* category, std::map<const char*, const char*> trace_map);
  bool DispatchJSFromNative(const char* category, std::map<const char*, const char*> trace_map);

private:
  static TraceBroker* s_trace_broker_singleton_;

  std::vector<fp_trace_listener*> s_trace_listeners_native_;
  Local<Object> trace_js_;

}; // class TraceBroker

} // namespace trace
} // namespace diag

#endif // DIAG_TRACE_BROKER_H_

