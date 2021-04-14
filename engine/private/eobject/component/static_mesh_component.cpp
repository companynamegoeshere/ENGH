#include <eobject/component/static_mesh_component.hpp>

namespace ENGH::EObject::Comps {

StaticMeshComponent::StaticMeshComponent() {}

Render::Component::PrimitiveRenderDelegate *StaticMeshComponent::CreateRenderDelegate() {
 return nullptr;
}

}
