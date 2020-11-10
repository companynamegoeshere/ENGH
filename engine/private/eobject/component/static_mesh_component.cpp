#include <eobject/component/static_mesh_component.hpp>
#include <render/component/primitive_static_mesh_render_delegate.hpp>

namespace ENGH::EObject::Comps {

StaticMeshComponent::StaticMeshComponent(Data::Model3D model): model(std::move(model)) {}

Render::Component::PrimitiveRenderDelegate *StaticMeshComponent::CreateRenderDelegate() {
  return new Render::Component::PrimitiveStaticMeshRenderDelegate(this);
}

}
