#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sigc++/sigc++.h>
#include <saftbus.h>
#include <MainContext.h>
#include <Connection.h>

#include "Driver1.h"

extern "C" {



	// can this be a std::shard_ptr? -> TODO: try this
	static saftlib::FirmwareDriver<testplugin::Driver1> *driver1;


	void initialize(const std::shared_ptr<Slib::MainContext> &context,
		            const std::shared_ptr<saftbus::Connection> &connection)
	{

		// this registers the driver as FirmwareDriver in saftlib 
		driver1 = new saftlib::FirmwareDriver<testplugin::Driver1>();


		std::cerr << "plugin initialize() connection_ptr: " << connection.get() << std::endl;

		// connection_ptr = connection;
		// id = connection->register_object(
		// 	"/de/gsi/saftlib/Driver1", 
		// 	std::make_shared< saftbus::InterfaceInfo >("de.gsi.saftlib.Condition", interface_xml),
		// 	vtable);
	}

	void cleanup()
	{
		std::cerr << "plugin cleanup" << std::endl;
		delete driver1;
	}


}
