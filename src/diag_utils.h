#ifndef DIAG_UTILS_H_
#define DIAG_UTILS_H_

#include "v8.h"

namespace diag {
namespace utils {

using namespace v8;

static Local<Function> ScriptToFunction(const char* script_source, const char* filename);

static Local<String> CharStringToV8String(const char* charString);

static const char* V8StringToCharString(Local<String> v8String);

} // namespace utils
} // namespace diag

#endif // DIAG_UTILS_H_
