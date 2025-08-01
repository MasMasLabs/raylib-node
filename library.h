#pragma once

#include <node.h>

void helloWorld(const v8::FunctionCallbackInfo<v8::Value>& args);

void initWindowAdapter(const v8::FunctionCallbackInfo<v8::Value>& args);
void setTargetFPSAdapter(const v8::FunctionCallbackInfo<v8::Value>& args);
void windowShouldCloseAdapter(const v8::FunctionCallbackInfo<v8::Value>& args);
void beginDrawingAdapter(const v8::FunctionCallbackInfo<v8::Value>& args);
void endDrawingAdapter(const v8::FunctionCallbackInfo<v8::Value>& args);
void clearBackgroundAdapter(const v8::FunctionCallbackInfo<v8::Value>& args);
void drawTextAdapter(const v8::FunctionCallbackInfo<v8::Value>& args);

void initialize(v8::Local<v8::Object> exports);