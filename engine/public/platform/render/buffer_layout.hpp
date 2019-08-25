#pragma once

#include <core/data_types.hpp>
#include <string>
#include <vector>

namespace ENGH::Platform::Render {

class BufferDataTypes {
    uint32 size;
    uint32 count;
public:

    BufferDataTypes();

    BufferDataTypes(uint32 size, uint32 count);

    uint32 GetSize() const;

    uint32 GetCount() const;

    static const BufferDataTypes BOOL;
    static const BufferDataTypes FLOAT;
    static const BufferDataTypes FLOAT2;
    static const BufferDataTypes FLOAT3;
    static const BufferDataTypes FLOAT4;
    static const BufferDataTypes INT;
    static const BufferDataTypes INT2;
    static const BufferDataTypes INT3;
    static const BufferDataTypes INT4;
    static const BufferDataTypes MAT3;
    static const BufferDataTypes MAT4;
};

struct BufferLayoutEntry {
    std::string     name;
    BufferDataTypes type;
    bool            normalized;
    uint32          offset;
};

class BufferLayout {

    std::vector<BufferLayoutEntry> entries;

    uint32 stride;

public:
    BufferLayout(const std::initializer_list<BufferLayoutEntry> &entries);

    uint32 GetStride() const;

    const std::vector<BufferLayoutEntry> GetEntries() const;

};

}