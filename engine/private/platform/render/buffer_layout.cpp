#include <platform/render/buffer_layout.hpp>

namespace ENGH::Platform::Render {

BufferDataTypes::BufferDataTypes() : size(0), count(0) {}

BufferDataTypes::BufferDataTypes(uint32 size, uint32 count) : size(size), count(count) {}

uint32 BufferDataTypes::GetSize() const {
    return size;
}

uint32 BufferDataTypes::GetCount() const {
    return count;
}

const BufferDataTypes BufferDataTypes::BOOL   = BufferDataTypes(1, 1);
const BufferDataTypes BufferDataTypes::FLOAT  = BufferDataTypes(4, 1);
const BufferDataTypes BufferDataTypes::FLOAT2 = BufferDataTypes(4, 2);
const BufferDataTypes BufferDataTypes::FLOAT3 = BufferDataTypes(4, 3);
const BufferDataTypes BufferDataTypes::FLOAT4 = BufferDataTypes(4, 4);
const BufferDataTypes BufferDataTypes::INT    = BufferDataTypes(4, 1);
const BufferDataTypes BufferDataTypes::INT2   = BufferDataTypes(4, 2);
const BufferDataTypes BufferDataTypes::INT3   = BufferDataTypes(4, 3);
const BufferDataTypes BufferDataTypes::INT4   = BufferDataTypes(4, 4);
const BufferDataTypes BufferDataTypes::MAT3   = BufferDataTypes(4, 3 * 3);
const BufferDataTypes BufferDataTypes::MAT4   = BufferDataTypes(4, 4 * 4);

BufferLayout::BufferLayout(const std::initializer_list<BufferLayoutEntry> &entries) : entries(entries), stride(0) {
    for (auto &e : this->entries) {
        e.offset = stride;
        stride += e.type.GetSize() * e.type.GetCount();
    }
}

uint32 BufferLayout::GetStride() const {
    return stride;
}

const std::vector<BufferLayoutEntry> BufferLayout::GetEntries() const {
    return entries;
}

}