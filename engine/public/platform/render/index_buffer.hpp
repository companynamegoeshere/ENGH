#pragma once

#include <platform/render/render_device.hpp>

namespace ENGH::Platform::Render {

class IndexBuffer : public RenderDevice {
protected:
    uint32 count;
public:

    inline uint32 GetCount() const { return count; }

    virtual void SetData(const TArray<uint32> &data) = 0;

};

}