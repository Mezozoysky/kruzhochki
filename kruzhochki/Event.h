#ifndef KRUZHOCHKI_EVENT_H
#define KRUZHOCHKI_EVENT_H

namespace kruz
{

  enum MOUSE_INPUT
  {
    MI_LEFT_PRESSED
  };

  struct MouseInput
  {
    MOUSE_INPUT input;
    unsigned short x;
    unsigned short y;
  };

  enum SYSTEM_EVENT
  {
    SE_QUIT
  };

  struct SystemEvent
  {
    SYSTEM_EVENT event;
  };

  enum EVENT_TYPE
  {
    ET_MOUSE,
    ET_SYSTEM
  };

  struct Event
  {
    int type;
    union
    {
      MouseInput mouseInput;
      SystemEvent systemEvent;
    };
  };

} // namespace kruz

#endif // KRUZHOCHKI_EVENT_H
