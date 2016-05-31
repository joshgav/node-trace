const path   = require('path');
const assert = require('assert');

var root = path.join(__dirname, '..');
var lib  = path.join(root, 'lib');
const trace = require(path.join(lib, 'trace'))();

var trace_input = {
  category: 'test-category',
  trace_obj: {
    message: 'this is a test',
    id: 1
  }
}

var trace_result = {};

// register a JS listener
trace.on('trace', (category, trace_obj) => {
  trace_result.category = category;
  trace_result.trace_obj = trace_obj;
});

// send a trace
trace.trace( trace_input.category, trace_input.trace_obj );

// verify trace was received and equals input
assert.equal( trace_input.category, trace_result.category );
assert.equal( trace_input.trace_obj, trace_result.trace_obj );

