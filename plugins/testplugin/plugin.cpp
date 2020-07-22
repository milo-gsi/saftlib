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

	// std::shared_ptr<testplugin::Driver1> instance;
	static int id;
	static saftbus::Connection *connection_ptr;
	static std::shared_ptr<testplugin::Driver1> instance;

	void method_call(const std::shared_ptr<saftbus::Connection>&, 
		             const std::string&, 
		             const std::string&, 
		             const std::string&, 
		             const std::string&, 
		             const saftbus::Serial&, 
		             const std::shared_ptr<saftbus::MethodInvocation>& )
	{
		std::cerr << "Driver1 method_call" << std::endl;
		instance->SayHello();
	}

	void get_property(saftbus::Serial& property, 
		              const std::shared_ptr<saftbus::Connection>&, 
		              const std::string&, 
		              const std::string&, 
		              const std::string&, 
		              const std::string& )
	{
		uint64_t value = 42;
		property.put(value);
		std::cerr << "Driver1 get_property" << std::endl;
	}

	bool set_property(const std::shared_ptr<saftbus::Connection>&, 
		              const std::string&, 
		              const std::string&, 
		              const std::string&, 
		              const std::string&, 
		              const saftbus::Serial& )
	{
		std::cerr << "Driver1 set_property" << std::endl;

		return true;
	}

	static saftlib::Driver<testplugin::Driver1> *driver1;

	std::string interface_xml = "<node><interface name='de.gsi.saftlib.Condition'><property name='ID' type='t' access='readwrite'/><property name='Mask' type='t' access='readwrite'/><property name='Offset' type='x' access='readwrite'/><property name='AcceptLate' type='b' access='readwrite'/><property name='AcceptEarly' type='b' access='readwrite'/><property name='AcceptConflict' type='b' access='readwrite'/><property name='AcceptDelayed' type='b' access='readwrite'/><property name='Active' type='b' access='readwrite'/></interface>"
"</node>";
	saftbus::InterfaceVTable vtable(interface_xml,
		                            sigc::ptr_fun(method_call ), 
		                            sigc::ptr_fun(get_property), 
		                            sigc::ptr_fun(set_property));

	void initialize(const std::shared_ptr<Slib::MainContext> &context,
		            saftbus::Connection *connection)
	{

		driver1 = new saftlib::Driver<testplugin::Driver1>();


		std::cerr << "creating a Driver1 instance" << std::endl;
		//context->iteration(false);
		// the driver plugin can attach sources to the context here
		//instance = std::make_shared<testplugin::Driver1>(context);

		connection_ptr = connection;
		id = connection->register_object(
			"/de/gsi/saftlib/Driver1", 
			std::make_shared< saftbus::InterfaceInfo >("de.gsi.saftlib.Condition", interface_xml),
			vtable);
	}

	void cleanup()
	{
		delete driver1;
		connection_ptr->unregister_object(id);
		std::cerr << "destroying a Driver1 instance" << std::endl;
		//instance.reset();
	}


}
