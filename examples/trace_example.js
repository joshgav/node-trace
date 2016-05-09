const trace = require('../lib/trace')();

// register a JS listener
trace.on('trace', (category, trace_obj) => {
  console.log(category, trace_obj);
});

// send a trace
trace.trace('joshgav-trace', { message: "stuff happened" });

