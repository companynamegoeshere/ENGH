#pragma once

#include <eobject/object.hpp>

namespace ENGH {

class Actor : Object {

public:
    Actor();

protected:

    std::unique_ptr<class SubComponent> root;

    virtual void BeginPlay();

    virtual void EndPlay();

};

}
