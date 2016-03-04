#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>

#include "Owned.h"
#include "interfaces/Display.h"

namespace saftlib 
{
  
  class TimingReceiver;
  
  class Display : public Owned, public iDisplay
  {
    /* Public */
    /* ==================================================================================================== */
    public:
      typedef Display_Service ServiceType;
      
      struct ConstructorType {
        TimingReceiver* dev;
        guint32 DeviceAddress;
      };
      
      static Glib::RefPtr<Display> create(const Glib::ustring& objectPath, ConstructorType args);
      
    /* Private */
    /* ==================================================================================================== */
    private:

    
    /* Protected */
    /* ==================================================================================================== */
    protected:
      Display(ConstructorType args);
      ~Display();
      
      TimingReceiver* dev;
      guint32 DeviceAddress;
  };

} /* namespace saftlib */

#endif
