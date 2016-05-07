#include "diag_utils.h"
#include "node.h"
#include "v8.h"

using namespace v8;

/*
static Local<Function> ScriptToFunction(const char* script_source, const char* filename) {
  Isolate* isolate = Isolate::GetCurrent();
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
*/

Local<String> diag::utils::CharStringToV8String(const char* charString) {
  return String::NewFromUtf8(Isolate::GetCurrent(), charString, v8::NewStringType::kNormal).ToLocalChecked();
}

const char* diag::utils::V8StringToCharString(Local<String> v8String) {
  uint8_t* buffer = new uint8_t[(v8String->Length() + 1)];
  int ret = v8String->WriteOneByte(buffer);
  if (ret > 0) {
    // this will leak, need to handle better
    return reinterpret_cast<const char*>(buffer);
  } else {
    return "";
  }
}

