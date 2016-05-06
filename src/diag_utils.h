#include "v8.h"

namespace diag {

static Local<Function> ScriptToFunction(const char* script_source, const char* filename);

static Local<String> CharStringToV8String(const char* charString);

} // namespace diag
