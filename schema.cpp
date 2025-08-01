#include "schema.h"

std::optional<DrawTextParamSchema> DrawTextParamSchema::FromV8(v8::Isolate* isolate, v8::Local<v8::Object> obj) {

    v8::Local<v8::Context> context = isolate->GetCurrentContext();

    DrawTextParamSchema result;

    // Validate "text"
    v8::Local<v8::Value> text_val;
    if (!obj->Get(context, v8::String::NewFromUtf8Literal(isolate, "text")).ToLocal(&text_val) || !text_val->IsString()) {
        return std::nullopt; // text is required
    }
    result.text = *v8::String::Utf8Value(isolate, text_val);

    // Validate: "posX"
    v8::Local<v8::Value> posX_val;
    if (!obj->Get(context, v8::String::NewFromUtf8Literal(isolate, "posX")).ToLocal(&posX_val) || !posX_val->IsNumber()) {
        return std::nullopt; // posX is required
    }
    result.posX = posX_val->Uint32Value(context).FromMaybe(0);

    // Validate "posY"
    v8::Local<v8::Value> posY_val;
    if (!obj->Get(context, v8::String::NewFromUtf8Literal(isolate, "posY")).ToLocal(&posY_val) || !posY_val->IsUint32()) {
        return std::nullopt; // posY is required
    }
    result.posY = posY_val->Uint32Value(context).FromMaybe(0);

    // Validate "fontSize"
    v8::Local<v8::Value> fontSize_val;
    if (!obj->Get(context, v8::String::NewFromUtf8Literal(isolate, "fontSize")).ToLocal(&fontSize_val) || !fontSize_val->IsUint32()) {
        return std::nullopt; // fontSize is required
    }
    result.fontSize = fontSize_val->Uint32Value(context).FromMaybe(0);

    // Optional "color"
    v8::Local<v8::Value> color_val;
    if (obj->Get(context, v8::String::NewFromUtf8Literal(isolate, "color")).ToLocal(&color_val) || !color_val->IsObject()) {
        result.color = ColorSchema::FromV8(isolate, color_val).value_or(LIGHTGRAY); // color is optional
    }

    return result;
}

std::string DrawTextParamSchema::format(const DrawTextParamSchema& param) {
    return std::format("{{ text: {}, posX: {}, posY: {}, fontSize: {}, color: {} }}", param.text, param.posX, param.posY, param.fontSize, ColorSchema::format(param.color));
}

void DrawTextParamSchema::print(const DrawTextParamSchema& param) {
    std::println("DrawTextParamSchema {}", format(param));
}



std::optional<Color> ColorSchema::FromV8(v8::Isolate* isolate, v8::Local<v8::Value> value) {
    if (!value->IsObject()) return std::nullopt;

    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Object> obj = value->ToObject(context).ToLocalChecked();

    auto getUint8 = [&](const char* name) -> std::optional<uint8_t> {
        v8::Local<v8::Value> val;
        if (!obj->Get(context, v8::String::NewFromUtf8(isolate, name).ToLocalChecked()).ToLocal(&val)) return std::nullopt;
        if (!val->IsUint32()) return std::nullopt;
        uint32_t v = val->Uint32Value(context).FromMaybe(0);
        if (v > 255) return std::nullopt;
        return static_cast<uint8_t>(v);
    };

    auto r = getUint8("r");
    auto g = getUint8("g");
    auto b = getUint8("b");
    auto a = getUint8("a");

    if (r && g && b && a) {
        return Color{ *r, *g, *b, *a };
    }
    return std::nullopt;
}

v8::Local<v8::Object> ColorSchema::ToV8(v8::Isolate* isolate, const Color& color) {
    v8::Local<v8::Object> obj = v8::Object::New(isolate);
    obj->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8Literal(isolate, "r"), v8::Integer::NewFromUnsigned(isolate, color.r)).Check();
    obj->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8Literal(isolate, "g"), v8::Integer::NewFromUnsigned(isolate, color.g)).Check();
    obj->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8Literal(isolate, "b"), v8::Integer::NewFromUnsigned(isolate, color.b)).Check();
    obj->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8Literal(isolate, "a"), v8::Integer::NewFromUnsigned(isolate, color.a)).Check();
    return obj;
}

std::string ColorSchema::format(const Color& color) {
    return std::format("{{ red: {}, green: {}, blue: {}, alpha: {} }}", color.r, color.g, color.b, color.a);
}

void ColorSchema::print(const Color& color) {
    std::println("Color {}", format(color));
}
