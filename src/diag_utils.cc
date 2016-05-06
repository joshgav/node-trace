#include "diag_utils.h"

namespace diag {

using namespace v8;

static Local<Function> ScriptToFunction(const char* script_source, const char* filename) {
  Isolate isolate = Isolate::GetCurrent();
  EscapableHandleScope scope(isolate);

  ScriptOrigin origin(CharStringToV8String(filename));

  MaybeLocal<Script> script =
      v8::Script::Compile(isolate->GetCurrentContext(), script_source, &origin);
  if (script.IsEmpty()) exit(3);

  Local<Value> result = script.ToLocalChecked()->Run();
  if (result.IsEmpty()) exit(4);

  Local<Value> compiled_function = scope.Escape(result);
  CHECK(compiled_function->IsFunction());
  Local<Function> f = Local<Function>::Cast(compiled_function);
  return f;
}

static Local<String> CharStringToV8String(const char* charString) {
  return v8::String::NewFromUtf8(Isolate::GetCurrent(), charString, v8::NewStringType::kNormal).ToLocalChecked();
}

} // namespace diag
