#define ETHERBONE_THROWS 1

#include "clog.h"
#include "OneWire.h"
#include "TimingReceiver.h"
#include "RegisteredObject.h"

namespace saftlib 
{
  OneWire::OneWire(ConstructorType args)
  {

  }
  
  OneWire::~OneWire()
  {
    
  }

  Glib::RefPtr<OneWire> OneWire::create(const Glib::ustring& objectPath, ConstructorType args)
  {
    return RegisteredObject<OneWire>::create(objectPath, args);
  }
  
  int OneWire::probe(TimingReceiver* tr, std::map< Glib::ustring,std::map< Glib::ustring, Glib::RefPtr<Owned> > > &otherStuff)
  {
    etherbone::Cycle cycle;
    std::vector<sdb_device> one_wire;
  
    /* Find OneWire modules */
    tr->getDevice().sdb_find_by_identity(DISPLAY_GSI_VENDOR_ID, ONEWIRE_ID, one_wire);
    
 
    return 0;
  }
  
} /* namespace saftlib */


