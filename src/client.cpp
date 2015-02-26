#include <iostream>
#include <giomm.h>
#include "TLU_Channel.h"

void on_edge(const guint64& time) {
  std::cout << "Pulse detected: " << time << std::endl;
}

int main(int, char**)
{
  Gio::init();

  try {
  
    Glib::RefPtr<Glib::MainLoop> loop = Glib::MainLoop::create();
    
    Glib::RefPtr<saftlib::TLU_Channel_Proxy> channel =
      saftlib::TLU_Channel_Proxy::create_for_bus_sync(
        Gio::DBus::BUS_TYPE_SESSION, "de.gsi.saftlib", "/de/gsi/saftlib/TLU/pex0_100_0");
    
    // Was it already active?
    std::cout << "Channel was: " << (channel->getEnabled()?"active":"inactive") << std::endl;
    
    // Listen for edges
    channel->Edge.connect(sigc::ptr_fun(&on_edge));
    channel->setLatchEdge(false);
    channel->setStableTime(16);
    channel->setEnabled(true);

    std::cout << "Waiting for edges" << std::endl;
    loop->run();
    
  } catch (const Glib::Error& error) {
    std::cerr << "Failed to invoke method: " << error.what() << std::endl;
  }

  return 0;
}
