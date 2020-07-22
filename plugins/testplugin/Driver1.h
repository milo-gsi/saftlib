#ifndef TESTPLUGIN_DRIVER1_H_
#define TESTPLUGIN_DRIVER1_H_

#include <MainContext.h>
#include <memory>


#include "Super.h"
#include <Driver.h>
#include <OpenDevice.h>

extern saftlib::DriverBase *top;

namespace testplugin
{
	class Driver1 : public Super
	{
	public:
		Driver1();
		Driver1(const std::shared_ptr<Slib::MainContext> &context);
		~Driver1();
		// saftbus method
		bool SayHello();
		static void probe(saftlib::OpenDevice& od);
	private:
		sigc::connection con;
	};

}

#endif
