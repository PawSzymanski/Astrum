/*
 *  partbutton.h
 *
 *  Created: 2017-08-06
 *   Author: Patryk Wojtanowski
 *
 */

#ifndef CRANESYSTEM_H
#define CRANESYSTEM_H

#include <entityx/entityx.h>
#include "2d_phisLIB/Events.h"
#include "2d_phisLIB/components.h"

class CraneSystem : public entityx::System<CraneSystem>, public entityx::Receiver<CraneSystem>
{

public:
    CraneSystem(entityx::EntityX & ex);

    void update(entityx::EntityManager & en, entityx::EventManager &ev, double dt);

    void receive(const CollisionEvent & ev);
};

#endif // CRANESYSTEM_H
