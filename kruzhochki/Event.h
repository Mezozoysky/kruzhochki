#ifndef KRUZHOCHKI_EVENT_H
#define KRUZHOCHKI_EVENT_H

namespace kruz
{

  enum MOUSE_INPUT
  {
    MI_LEFT_PRESSED,
    MI_RIGHT_PRESSED
  };

  struct MouseInput
  {
    MOUSE_INPUT input;
    unsigned short x;
    unsigned short y;
  };

  enum SYSTEM_EVENT
  {
    SE_WINDOW_CLOSE
  };

  struct SystemEvent
  {
    SYSTEM_EVENT event;
    void* data;
  };

  enum EVENT_TYPE
  {
    ET_MOUSE_INPUT,
    ET_SYSTEM_EVENT
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
