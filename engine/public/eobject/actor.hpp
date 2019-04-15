#pragma once

#include <eobject/object.hpp>
#include <util/single_pointer.hpp>

namespace ENGH {

class Actor : Object {

public:
    Actor();

protected:

    Util::TSinglePointer<class SubComponent> root;

    virtual void BeginPlay();

    virtual void EndPlay();

};

}
