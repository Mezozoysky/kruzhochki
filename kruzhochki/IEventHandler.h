#ifndef KRUZHOCHKI_IEVENTHANDLER_H
#define KRUZHOCHKI_IEVENTHANDLER_H

#include "Event.h"

namespace kruz
{
  class IEventHandler
  {
  public:
    virtual ~IEventHandler()
    {
    }

    virtual void handleEvent(const Event& event) = 0;
  };

} // namespace kruz

#endif KRUZHOCHKI_IEVENTHANDLER_H
