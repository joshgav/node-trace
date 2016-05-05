// function is declared here, invoked with `Local<Object> exports`
// from native trace_module.cc.
function (exports) {
  const ee = require('events');
  exports = this;

  // We use ee.emit to notify listeners about traces.
  // We use ee.on('trace', ...) to register listeners.
  ee.apply(this);


  /**
   * Called by a publisher to send trace to broker.
   * @param category string An arbitrary category name.
   * @param obj_or_str any An object or string for the trace.
   * @return boolean True if all is well.
   */
  function trace( category, obj_or_str ) {
    // process obj_or_str into trace_obj
    // before passing to common _onIncomingTrace
    var trace_obj = {};
    switch (typeof obj_or_str) {
      case (String) {
        trace_obj.message = obj_or_str;
        break;
      }
      case (Object) {
        trace_obj = obj_or_str;
        break;
      }
      default {

      }
    }

    _onIncomingTrace(category, trace_obj);
  }

  function traceNextTick( category, obj_or_str) {
    process.nextTick(trace(category,obj_or_str));
  }

  // ---- internal

  // common processing for incoming traces
  function _onIncomingTrace( category, obj ) {
    // TODO Add standard props like timestamp, PID, TID.
    _notifyTrace(category, obj);
  }

  // common processing for outgoing traces
  function _notifyTrace( category, obj) {
    ee.emit('trace', category, obj);
  }

});

