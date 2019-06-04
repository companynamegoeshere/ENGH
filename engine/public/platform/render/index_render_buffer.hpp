#pragma once

#include <platform/render/render_buffer.hpp>

namespace ENGH::Platform::Render {

class IndexRenderBuffer : public RenderBuffer {
protected:
    uint32 count;
public:

    inline uint32 GetCount() { return count; }

    virtual void SetData(const TArray<uint32>& data) = 0;

};

}