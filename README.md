## Node Trace Module

This module provides a pair of `TraceBroker` classes for use in Node, one native (C++) and one JS. These brokers provide `Trace`/`trace` methods for components to publish trace events, and `Register`/`on` methods for registering trace listeners. Listeners in JS are callbacks, and in C++ are function pointers.

The C++ and JS brokers are wired together so that traces from native components are published to JS listeners; and vice versa.

Listeners are invoked when traces are received through `Trace`/`trace`. By default listeners are invoked on the same thread and within the same "tick" as the publication, which is the behavior of `EventEmitter`. A `TraceNextTick` function instead delays publication till the next tick. 

### Quick Start

1. Install node-gyp (`npm install -g node-gyp`).
2. Run `node-gyp build --debug` from this directory.
3. Run `node ./examples/trace_example.js`.

You'll see a log from a JS listener registered within `trace_example.js`, as well as a log from a native listener registered by calling `enabledNativeConsoleListener()` in `lib/trace.js`.

### Native TraceBroker

To add a native listener to your app, use the following pattern:

```cpp
#include "trace_broker.h"

# Declare and define a C function with the following signature:
void ConsoleListener(const char* category, std::map<const char*, const char*> trace_map);
void ConsoleListener(const char* category, std::map<const char*, const char*> trace_map) {
  std::cout << "Category: " << category << std::endl;
  for (auto it = trace_map.begin(); it != trace_map.end(); ++it) {
    std::cout << it->first << ": " << it->second << std::endl;
  }
  std::cout << std::endl;
}

# Register the previous function as a listener:
TraceBroker::Singleton()->RegisterListener(&ConsoleListener);
```

To publish traces from native components in your app, use the following pattern:

```cpp
#include "trace_broker.h"

TraceBroker::Singleton->Trace("category_name", {{"message": "myMessage"}, {"extra": "moreInfo"}});
```

### JS TraceBroker

See [./examples/trace_example.js](./examples/trace_example.js) for an example of how to subscribe to and publish traces in JS scripts.

### More

This is a work in progress.

