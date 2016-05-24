const trace = require('../lib/trace')();
trace.enableNativeConsoleListener();

// register a JS listener
trace.on('trace', (category, trace_obj) => {
  console.log('from JS:\n  category:', category, '\n  trace_obj:', trace_obj, '\n');
});

// send a trace
trace.trace('joshgav-trace', { message: "stuff happened" });

