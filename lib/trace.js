'use strict';

module.exports = exports = trace;

const events = require('events');

function trace() {
  return new TraceBroker();
}

// Use EventEmitter.emit to dispatch traces to JS listeners.
// Use EventEmitter.on('trace', (category, trace_obj) => {}) to register JS listeners.
class TraceBroker extends events.EventEmitter {

  constructor() {

    super();

    // Some JS functions proxy to native through `this.trace_native`,
    // and some native functions proxy to JS through `TraceBroker::trace_js()`.
    this.trace_native = require("../build/Debug/trace_native.node");
    this.trace_native._dispatchJSFromNative = (category, trace_obj) => {
      this._dispatchJSFromNative(category, trace_obj);
    }
  }

  /**
   * Called by a publisher to send trace to broker.
   * @param category string An arbitrary category name.
   * @param obj_or_str any An object or string for the trace.
   * @return boolean True if all is well.
   */
  trace(category, obj_or_str) {
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

    this._traceInternal(category, trace_obj);
  }

  traceNextTick(category, obj_or_str) {
    process.nextTick(this.trace(category, obj_or_str));
  }

  // ---- internal

  // common processing for incoming traces
  _traceInternal(category, trace_obj) {
    // TODO Add standard props like timestamp, PID, TID.
    this._dispatch(category, trace_obj);
  }

  _dispatch(category, trace_obj) {
    this._dispatchJS(category, trace_obj);
    this._dispatchNativeFromJS(category, trace_obj);
  }

  _dispatchJS(category, trace_obj) {
    this.emit('trace', category, trace_obj);
  }

  _dispatchJSFromNative(category, trace_obj) {
    this._dispatchJS(category, trace_obj);
  }

  _dispatchNativeFromJS(category, trace_obj) {
    this.trace_native._dispatchNativeFromJS(category, trace_obj);
  }
} // class TraceBroker

module.exports.TraceBroker = TraceBroker;

