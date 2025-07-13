#include "octopus_effect.h"

OctopusEffect::OctopusEffect(Octopus * octopus)
: Effect(octopus->get_controller()),
  octopus_ { octopus }
{
}


OctopusEffect::~OctopusEffect()
{
}

