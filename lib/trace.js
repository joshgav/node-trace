exports = this;

// Some JS functions proxy to native through `this.trace_native`,
// and some native functions proxy to JS through `TraceBroker::trace_js()`.
const trace_native = require("trace_module.node");
trace_native.dispatchJSFromNative = function dispatchJSFromNative(category, trace_obj) {
  this.dispatchJSFromNative(category, trace_obj);
}

// Use ee.emit to dispatch traces to JS listeners.
// Use ee.on('trace', (category, trace_obj) => {}) to register JS listeners.
const ee = require('events');
ee.apply(this);

/**
 * Called by a publisher to send trace to broker.
 * @param category string An arbitrary category name.
 * @param obj_or_str any An object or string for the trace.
 * @return boolean True if all is well.
 */
function trace(category, obj_or_str) {
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

  _traceInternal(category, trace_obj);
}

function traceNextTick(category, obj_or_str) {
  process.nextTick(trace(category,obj_or_str));
}

// ---- internal

// common processing for incoming traces
function _traceInternal(category, obj) {
  // TODO Add standard props like timestamp, PID, TID.
  _dispatch(category, obj);
}

function _dispatch(category, obj) {
  _dispatchJS(category, obj);
  _dispatchNativeFromJS(category, obj);
}

function _dispatchJS(category, obj) {
  ee.emit('trace', category, obj);
}

function _dispatchJSFromNative(category, obj) {
  _dispatchJS(category, obj);
}

function _dispatchNativeFromJS(category, obj) {
  trace_native._dispatchNativeFromJS(category, obj);
}

