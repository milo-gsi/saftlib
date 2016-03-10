#ifndef ONEWIRE_H
#define ONEWIRE_H

#include <stdio.h>
#include <etherbone.h>
#include "Owned.h"
#include "TimingReceiver.h"
#include "interfaces/OneWire.h"

#define ONEWIRE_ID    0x779c5443

namespace saftlib 
{
  
  class TimingReceiver;
  
  class OneWire : public Owned, public iOneWire
  {
    /* Public */
    /* ==================================================================================================== */
    public:
      typedef OneWire_Service ServiceType;
      
      struct ConstructorType {
        TimingReceiver* dev;
        eb_address_t one_wire_addr;
      };
      
      static Glib::RefPtr<OneWire> create(const Glib::ustring& objectPath, ConstructorType args);
      static int probe(TimingReceiver* tr, std::map< Glib::ustring,std::map< Glib::ustring, Glib::RefPtr<Owned> > > &otherStuff);
      
      
    /* Private */
    /* ==================================================================================================== */
    private:
    
    /* Protected */
    /* ==================================================================================================== */
    protected:
      OneWire(ConstructorType args);
      ~OneWire();
      
      TimingReceiver* dev;
      eb_address_t one_wire_addr;
      
  };

} /* namespace saftlib */

#endif
