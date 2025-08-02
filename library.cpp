#include "library.h"
#include "schema.h"
#include <node.h>
#include <raylib.h>

void helloWorld(const v8::FunctionCallbackInfo<v8::Value> &args) {
    v8::Isolate* isolate = args.GetIsolate();
    v8::HandleScope handle_scope(isolate);

    args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, "Hello World!", v8::NewStringType::kNormal).ToLocalChecked());
}


void initWindowAdapter(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate* isolate = args.GetIsolate();
    v8::HandleScope handle_scope(isolate);

    if (args.Length() < 3) {
        isolate->ThrowException(v8::String::NewFromUtf8Literal(isolate, "Wrong number of arguments! 3 arguments needed!"));
        return;
    }

    if (args[0]->IsString() || !args[0]->IsNumber()) {
        isolate->ThrowException(v8::String::NewFromUtf8Literal(isolate, "First argument must be a positive integer!"));
        return;
    }

    if (args[1]->IsString() || !args[1]->IsNumber()) {
        isolate->ThrowException(v8::String::NewFromUtf8Literal(isolate, "Second argument must be a positive integer!"));
    }

    if (!args[2]->IsString()) {
        isolate->ThrowException(v8::String::NewFromUtf8Literal(isolate, "Third argument must be a string!"));
    }

    int width = args[0]->Int32Value(isolate->GetCurrentContext()).FromJust();
    int height = args[1]->Int32Value(isolate->GetCurrentContext()).FromJust();

    v8::String::Utf8Value utf8(isolate, args[2]);
    char* cstr = *utf8;

    InitWindow(width, height, cstr);
}

void setTargetFPSAdapter(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate* isolate = args.GetIsolate();
    v8::HandleScope handle_scope(isolate);

    if (args.Length() < 1 || !args[0]->IsNumber()) {
        isolate->ThrowException(v8::String::NewFromUtf8Literal(isolate, "Wrong number of arguments! 1 argument needed!"));
        return;
    }

    int fps = args[0]->Int32Value(isolate->GetCurrentContext()).FromJust();

    SetTargetFPS(fps);
}

void windowShouldCloseAdapter(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate* isolate = args.GetIsolate();
    v8::HandleScope handle_scope(isolate);
    args.GetReturnValue().Set(v8::Boolean::New(isolate, WindowShouldClose()));
}

void closeWindowadapter(const v8::FunctionCallbackInfo<v8::Value>& args) {
    CloseWindow();
}

void beginDrawingAdapter(const v8::FunctionCallbackInfo<v8::Value>& args) {
    BeginDrawing();
}

void endDrawingAdapter(const v8::FunctionCallbackInfo<v8::Value>& args) {
    EndDrawing();
}

void clearBackgroundAdapter(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate* isolate = args.GetIsolate();
    v8::HandleScope handle_scope(isolate);

    if (args.Length() < 1 || !args[0]->IsObject()) {
        isolate->ThrowException(v8::String::NewFromUtf8Literal(isolate, "Expected an object"));
        return;
    }

    Color color = ColorSchema::FromV8(isolate, args[0]).value_or(RAYWHITE);

    ClearBackground(color);
}

void drawTextAdapter(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate* isolate = args.GetIsolate();
    v8::HandleScope handle_scope(isolate);

    if (args.Length() < 1 || !args[0]->IsObject()) {
        isolate->ThrowException(v8::String::NewFromUtf8Literal(isolate, "Expected an object"));
        return;
    }

    v8::String::Utf8Value argTypeStr(isolate, args[0]->TypeOf(isolate));

    auto maybeDrawTextParam = DrawTextParamSchema::FromV8(isolate, args[0].As<v8::Object>());

    if (!maybeDrawTextParam) {
        isolate->ThrowException(v8::String::NewFromUtf8Literal(isolate, "Invalid object schema"));
        return;
    }

    const auto& drawTextParam = *maybeDrawTextParam;

    DrawText(drawTextParam.text.c_str(), drawTextParam.posX, drawTextParam.posY, drawTextParam.fontSize, drawTextParam.color);
}


void initialize(v8::Local<v8::Object> exports) {
    NODE_SET_METHOD(exports, "helloWorld", helloWorld);
    NODE_SET_METHOD(exports, "initWindow", initWindowAdapter);
    NODE_SET_METHOD(exports, "setTargetFPS", setTargetFPSAdapter);
    NODE_SET_METHOD(exports, "windowShouldClose", windowShouldCloseAdapter);
    NODE_SET_METHOD(exports, "closeWindow", closeWindowadapter);
    NODE_SET_METHOD(exports, "beginDrawing", beginDrawingAdapter);
    NODE_SET_METHOD(exports, "endDrawing", endDrawingAdapter);
    NODE_SET_METHOD(exports, "clearBackground", clearBackgroundAdapter);
    NODE_SET_METHOD(exports, "drawText", drawTextAdapter);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, initialize)
