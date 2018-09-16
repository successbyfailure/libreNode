#ifndef LEDKEY
#define LEDKEY

#include "nLedBar.h"
#include "nodeComponent.h"

class ledKeyNode : public ledBarNode
{
public:
  ledKeyNode(storage* s) : ledBarNode(s),
    _button("button",s)
  {
    addComponent(&_button);
  }

  void setupNode()
  {

  }

  void nodeLoop()
  {
    uint16_t longPress = _button.released();
    if(longPress)
    {
      //_leds.restoreState();
    }

    if(_button.pressed())
    {
      //_leds.saveState();
      //_leds.rainbow();
    }
  }


protected:
  pushButton _button;
};

#endif
