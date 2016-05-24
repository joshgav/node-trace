#ifndef DIAG_UTILS_INL_H_
#define DIAG_UTILS_INL_H_

#include "diag_utils.h"
#include "node.h"
#include "v8.h"

using namespace v8;

namespace diag {
namespace utils {

// private declaration of helper functions
template <class T>
inline Local<T> StrongPersistentToLocal(
    const Persistent<T>& persistent);

template <class T>
inline v8::Local<T> WeakPersistentToLocal(
    Isolate* isolate,
    const Persistent<T>& persistent);

// implementations
template <class T>
inline Local<T> PersistentToLocal(
    Isolate* isolate,
    const Persistent<T>& persistent) {
  if (persistent.IsWeak()) {
    return WeakPersistentToLocal(isolate, persistent);
  } else {
    return StrongPersistentToLocal(persistent);
  }
}

template <class T>
inline Local<T> StrongPersistentToLocal(
    const Persistent<T>& persistent) {
  return *reinterpret_cast<Local<T>*>(
      const_cast<Persistent<T>*>(&persistent));
}

template <class T>
inline Local<T> WeakPersistentToLocal(
    Isolate* isolate,
    const Persistent<T>& persistent) {
  return Local<T>::New(isolate, persistent);
}

} // namespace utils
} // namespace diag

#endif // DIAG_UTILS_INL_H_
