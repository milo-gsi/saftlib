#include "Driver1.h"

#include <iostream>
#include <RegisteredObject.h>

namespace testplugin
{
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


	std::string interface_xml = "<node><interface name='de.gsi.saftlib.Condition'><property name='ID' type='t' access='readwrite'/><property name='Mask' type='t' access='readwrite'/><property name='Offset' type='x' access='readwrite'/><property name='AcceptLate' type='b' access='readwrite'/><property name='AcceptEarly' type='b' access='readwrite'/><property name='AcceptConflict' type='b' access='readwrite'/><property name='AcceptDelayed' type='b' access='readwrite'/><property name='Active' type='b' access='readwrite'/></interface>"
"</node>";
	saftbus::InterfaceVTable vtable(interface_xml,
		                            sigc::ptr_fun(method_call ), 
		                            sigc::ptr_fun(get_property), 
		                            sigc::ptr_fun(set_property));



	/// member functions 

	Driver1::Driver1(const std::string& objectPath)
		: Owned(objectPath) 
	{
		std::cerr << "Driver1::Driver1()" << std::endl;
	}


	Driver1::~Driver1() {
		std::cerr << "Driver1::~Driver1" << std::endl;
	}



	bool Driver1::SayHello() {
		std::cout << "Hello from Driver1" << std::endl;
		return true;
	}


	void Driver1::probe(saftlib::FirmwareDevice& fd) {

		// fd.ref = saftlib::RegisteredObject<Driver1>::create(SAFTd::get().connection(), od.objectPath, args);
		// fd.ref = std::make_shared<Driver1>(fd.objectPath);
		std::cout << "Driver1::probe() called connection: " << fd.connection.get() << std::endl;
		
	}




}
