#include <platform/render/buffer_layout.hpp>

namespace ENGH::Platform::Render {

BufferDataTypes::BufferDataTypes() : id(UByte::MAX), size(0), count(0) {}

BufferDataTypes::BufferDataTypes(ubyte id, uint32 size, uint32 count) :
    id(id), size(size), count(count) {}

const BufferDataTypes BufferDataTypes::BOOL   = BufferDataTypes( 0, 1, 1);
const BufferDataTypes BufferDataTypes::FLOAT  = BufferDataTypes( 1, 4, 1);
const BufferDataTypes BufferDataTypes::FLOAT2 = BufferDataTypes( 2, 4, 2);
const BufferDataTypes BufferDataTypes::FLOAT3 = BufferDataTypes( 3, 4, 3);
const BufferDataTypes BufferDataTypes::FLOAT4 = BufferDataTypes( 4, 4, 4);
const BufferDataTypes BufferDataTypes::INT    = BufferDataTypes( 5, 4, 1);
const BufferDataTypes BufferDataTypes::INT2   = BufferDataTypes( 6, 4, 2);
const BufferDataTypes BufferDataTypes::INT3   = BufferDataTypes( 7, 4, 3);
const BufferDataTypes BufferDataTypes::INT4   = BufferDataTypes( 8, 4, 4);
const BufferDataTypes BufferDataTypes::MAT3   = BufferDataTypes( 9, 4, 3 * 3);
const BufferDataTypes BufferDataTypes::MAT4   = BufferDataTypes(10, 4, 4 * 4);

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