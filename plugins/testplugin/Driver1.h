#ifndef TESTPLUGIN_DRIVER1_H_
#define TESTPLUGIN_DRIVER1_H_

#include <MainContext.h>
#include <memory>


#include <FirmwareDriver.h>
#include <Owned.h>


namespace testplugin 
{

	class Driver1_Service {

	};

	class Driver1 : public saftlib::Owned
	{
	public:
	    struct ConstructorType {
	      saftlib::Device device;
	    };
	    typedef Driver1_Service ServiceType;


		Driver1(const std::string& objectPath);
		~Driver1();
		// saftbus method
		bool SayHello();
		static void probe(saftlib::FirmwareDevice& fd);
	private:
	};

}

#endif
