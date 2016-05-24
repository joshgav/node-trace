#ifndef DIAG_UTILS_H_
#define DIAG_UTILS_H_

#include "v8.h"

namespace diag {
namespace utils {

using namespace v8;

// static Local<Function> ScriptToFunction(const char* script_source, const char* filename);

Local<String> CharStringToV8String(const char* charString);

const char* V8StringToCharString(Local<String> v8String);

template <class T>
inline Local<T> PersistentToLocal(
    Isolate* isolate,
    const Persistent<T>& persistent);

} // namespace utils
} // namespace diag

#endif // DIAG_UTILS_H_
