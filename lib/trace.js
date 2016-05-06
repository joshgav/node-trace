exports = this;

// Some JS functions proxy to native through `this.trace_native`,
// and some native functions proxy to JS through `TraceBroker::trace_js()`.
const trace_native = require("./build/Release/trace_native");
trace_native._dispatchJSFromNative = function _dispatchJSFromNative(category, trace_obj) {
  this._dispatchJSFromNative(category, trace_obj);
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
  var trace_obj = {};
  switch (typeof obj_or_str) {
    case "string": {
      trace_obj.message = obj_or_str;
      break;
    }
    case "object": {
      trace_obj = obj_or_str;
      break;
    }
    default: {

    }
  }

  _traceInternal(category, trace_obj);
}

function traceNextTick(category, obj_or_str) {
  process.nextTick(trace(category, obj_or_str));
}

// ---- internal

// common processing for incoming traces
function _traceInternal(category, trace_obj) {
  // TODO Add standard props like timestamp, PID, TID.
  _dispatch(category, trace_obj);
}

function _dispatch(category, trace_obj) {
  _dispatchJS(category, trace_obj);
  _dispatchNativeFromJS(category, trace_obj);
}

function _dispatchJS(category, trace_obj) {
  ee.emit('trace', category, trace_obj);
}

function _dispatchJSFromNative(category, trace_obj) {
  _dispatchJS(category, trace_obj);
}

function _dispatchNativeFromJS(category, trace_obj) {
  trace_native._dispatchNativeFromJS(category, trace_obj);
}

