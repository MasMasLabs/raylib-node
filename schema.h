#pragma once

#include <print>
#include <optional>
#include <v8.h>
#include <raylib.h>

struct ColorSchema {
    static std::optional<Color> FromV8(v8::Isolate* isolate, v8::Local<v8::Value> value);
    static v8::Local<v8::Object> ToV8(v8::Isolate* isolate, const Color& color);
    static std::string format(const Color& color);
    static void print(const Color& color);
};

struct DrawTextParamSchema {
    std::string text;
    uint32_t posX = 0;
    uint32_t posY = 0;
    uint32_t fontSize = 0;
    Color color = LIGHTGRAY;

    static std::optional<DrawTextParamSchema> FromV8(v8::Isolate* isolate, v8::Local<v8::Object> obj);
    static std::string format(const DrawTextParamSchema& param);
    static void print(const DrawTextParamSchema& param);
};