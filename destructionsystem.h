#ifndef DESTRUCTIONSYSTEM_H
#define DESTRUCTIONSYSTEM_H

#include "LibsAndDeclarations.h"
#include "2d_phisLIB/Events.h"
#include "2d_phisLIB/components.h"

class DestructionSystem : public entityx::System<DestructionSystem>, public entityx::Receiver<DestructionSystem>
{

public:
    DestructionSystem(entityx::EntityX &ex);

    void update(entityx::EntityManager & en, entityx::EventManager & ev, double dt);

    void receive(const CollisionEvent & ev);
};

#endif // DESTRUCTIONSYSTEM_H
