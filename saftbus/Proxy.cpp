#include "Proxy.h"

#include <iostream>

#include "saftbus.h"

namespace saftbus
{

Glib::RefPtr<saftbus::ProxyConnection> Proxy::_connection;
bool Proxy::_connection_created = false;

Proxy::Proxy(saftbus::BusType  	bus_type,
	const Glib::ustring&  	name,
	const Glib::ustring&  	object_path,
	const Glib::ustring&  	interface_name,
	const Glib::RefPtr< InterfaceInfo >&  	info,
	ProxyFlags  	flags
) : _name(name)
  , _object_path(object_path)
  , _interface_name(interface_name)
{
	std::cerr << "Proxy::Proxy(" << name << "," << object_path << "," << interface_name << ") called   _connection_created = " << _connection.get() << std::endl;

	if (!_connection.get()) {
		std::cerr << "   this process has no ProxyConnection yet. Creating one now" << std::endl;
		_connection = Glib::RefPtr<saftbus::ProxyConnection>(new ProxyConnection);
		std::cerr << "   ProxyConnection created" << std::endl;
	}

	// establish a connection to the service: the service needs to know which proxies are connected in order to dispatch the incoming signals
	// ...
	//_connection->register_proxy(_interface_name, _object_path, this);
}


void Proxy::get_cached_property (Glib::VariantBase& property, const Glib::ustring& property_name) const 
{
	std::cerr << "Proxy::get_cached_property(" << property_name << ") called" << std::endl;

	return; // empty response

	// // fake a response
	// if (property_name == "Devices")
	// {
	// 	std::map<Glib::ustring, Glib::ustring> devices;
	// 	devices["tr0"] = "/de/gsi/saftlib";
	// 	property = Glib::Variant< std::map< Glib::ustring, Glib::ustring > >::create(devices);
	// }
}

void Proxy::on_properties_changed (const MapChangedProperties& changed_properties, const std::vector< Glib::ustring >& invalidated_properties)
{
	std::cerr << "Proxy::on_properties_changed() called" << std::endl;
}
void Proxy::on_signal (const Glib::ustring& sender_name, const Glib::ustring& signal_name, const Glib::VariantContainerBase& parameters)
{
	std::cerr << "Proxy::on_signal() called" << std::endl;
}
Glib::RefPtr<saftbus::ProxyConnection> Proxy::get_connection() const
{
	std::cerr << "Proxy::get_connection() called " << std::endl;
	return _connection;
}

Glib::ustring Proxy::get_object_path() const
{
	std::cerr << "Proxy::get_object_path() called" << std::endl;
	return _object_path;
}
Glib::ustring Proxy::get_name() const
{
	std::cerr << "Proxy::get_name() called" << std::endl;
	return _name;
}

const Glib::VariantContainerBase& Proxy::call_sync(std::string function_name, Glib::VariantContainerBase query)
{
	std::cerr << "Proxy::call_sync(" << function_name << ") called" << std::endl;
	Glib::VariantContainerBase &result = _connection->call_sync(_object_path, 
		                          _interface_name,
		                          function_name,
		                          query);
	std::cerr << "result = " << result.print() << std::endl;
	return result;
}

}
