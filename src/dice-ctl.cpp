
#include <iostream>
#include <giomm.h>

#include "interfaces/SAFTd.h"
#include "interfaces/Dice.h"


Glib::RefPtr<Glib::MainLoop> mainloop;
Glib::RefPtr<saftlib::Dice_Proxy> dice;

void on_rolled(guint32 score, guint32 count)
{
  std::cout << "rolled event: " << score << std::endl;
  mainloop->quit();
}

void on_count(guint32 count)
{
  std::cout << "count updated: " << count << std::endl;
}


static void runTests() {
  // method calls with no mainloop
  // properties remain at cached values
  std::cout << "using dice version " << dice->getVersion() << "[" << dice->getSeed() << "]" << std::endl;
  dice->setUpperLimit(100);
  std::cout << "dice upper limit: " << dice->getUpperLimit() << std::endl; // outdated, signal not received yet
  std::cout << "roll (method): " << dice->Roll() << std::endl;
  std::cout << "count: " << dice->getCount() << " average score: " << dice->getAverage() << std::endl; // outdated, signal not received yet
  dice->setUpperLimit(6);
  std::cout << "dice upper limit: " << dice->getUpperLimit() << std::endl;
  std::cout << "roll (method): " << dice->Roll() << std::endl;
  std::cout << "count: " << dice->getCount() << " average score: " << dice->getAverage() << std::endl;
  std::cout << "roll (method): " << dice->Roll() << std::endl;
  std::cout << "count: " << dice->getCount() << " average score: " << dice->getAverage() << std::endl;


  dice->Rolled.connect(sigc::ptr_fun(&on_rolled));
  dice->Count.connect(sigc::ptr_fun(&on_count));

// method calls with mainloop paused betweem events
// properties updated
  for (int i=0;i<3;i++)
  {
    dice->RollMultiple(1);
    mainloop->run();
    std::cout << "count: " << dice->getCount() << " average score: " << dice->getAverage() << std::endl;
  }
}


int main(int argc, char** argv)
{
  try {
  	Gio::init();
    mainloop = Glib::MainLoop::create();
  	Glib::RefPtr<saftlib::SAFTd_Proxy> saftd = saftlib::SAFTd_Proxy::create();
    std::map<Glib::ustring, Glib::ustring> devices = saftlib::SAFTd_Proxy::create()->getDevices();
    std::map<Glib::ustring, Glib::ustring>::iterator it;
    std::cout << "saftd devices:" << std::endl;
    for (it=devices.begin(); it != devices.end(); ++it ){
      std::cout << it->first << ":" << it->second << std::endl;
      if (it->first == "dice"){
        dice = saftlib::Dice_Proxy::create(it->second);
        runTests();
      }
    }

    

  } catch (const Glib::Error& error) {
    std::cerr << "glib error: " << error.what() << std::endl;
  }

  return 0;
}
