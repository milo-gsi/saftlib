#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <etherbone.h>
#include "Owned.h"
#include "TimingReceiver.h"
#include "interfaces/Display.h"

#define GENERIC_OLED_PRODUCT_ID    0x93a6f3c4
#define GENERIC_LCD_PRODUCT_ID     0xb77a5045
#define GENERIC_SSD1325_PRODUCT_ID 0x55d1325d
#define DISPLAY_GSI_VENDOR_ID      0x00000651

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
        eb_address_t display_addr;
      };
      
      static Glib::RefPtr<Display> create(const Glib::ustring& objectPath, ConstructorType args);
      static int probe(TimingReceiver* tr, std::map< Glib::ustring,std::map< Glib::ustring, Glib::RefPtr<Owned> > > &otherStuff);
      
    /* Private */
    /* ==================================================================================================== */
    private:
    
    /* Protected */
    /* ==================================================================================================== */
    protected:
      Display(ConstructorType args);
      ~Display();
      
      TimingReceiver* dev;
      eb_address_t display_addr;
  };

} /* namespace saftlib */

#endif
