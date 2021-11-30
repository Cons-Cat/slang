#ifndef SLANG_COMPILER_CORE_JSON_NATIVE_H
#define SLANG_COMPILER_CORE_JSON_NATIVE_H

#include "../../slang.h"
#include "../../slang-com-helper.h"
#include "../../slang-com-ptr.h"

#include "slang-json-value.h"

namespace Slang {

struct JSONToNativeConverter
{
    SlangResult convert(const JSONValue& value, const RttiInfo* rttiInfo, void* out);
    template <typename T>
    SlangResult convert(const JSONValue& value, T* in) { return convert(value, GetRttiInfo<T>::get(), (void*)in); }

    JSONToNativeConverter(JSONContainer* container, DiagnosticSink* sink):
        m_container(container),
        m_sink(sink)
    {}

protected:
    static Index _getFieldCount(const StructRttiInfo* structRttiInfo);
    static Index _findFieldIndex(const StructRttiInfo* structRttiInfo, const UnownedStringSlice& fieldName);

    SlangResult _structToNative(const ConstArrayView<JSONKeyValue>& pairs, const StructRttiInfo* structRttiInfo, void* out, Index& outFieldCount);

    DiagnosticSink* m_sink;
    JSONContainer* m_container;
};

struct NativeToJSONConverter
{
    SlangResult convert(const RttiInfo* rttiInfo, const void* in, JSONValue& out);

    template <typename T>
    SlangResult convert(T* in, JSONValue& out) { return convert(GetRttiInfo<T>::get(), (const void*)in, out); }

    NativeToJSONConverter(JSONContainer* container, DiagnosticSink* sink) :
        m_container(container),
        m_sink(sink)
    {}

protected:
    SlangResult _structToJSON(const StructRttiInfo* structRttiInfo, const void* src, List<JSONKeyValue>& outPairs);

    DiagnosticSink* m_sink;
    JSONContainer* m_container;
};


} // namespace Slang

#endif // SLANG_COMPILER_CORE_JSON_NATIVE_H