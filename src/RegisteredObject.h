/** Copyright (C) 2011-2016 GSI Helmholtz Centre for Heavy Ion Research GmbH 
 *
 *  @author Wesley W. Terpstra <w.terpstra@gsi.de>
 *
 *******************************************************************************
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 3 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library. If not, see <http://www.gnu.org/licenses/>.
 *******************************************************************************
 */
#ifndef SAFTLIB_REGISTERED_OBJECT_H
#define SAFTLIB_REGISTERED_OBJECT_H

#include <sstream>
#include <memory>

// this dependence is deprecated: saftlib should not depend on etherbone in the long run!
// #include <etherbone.h>

#include <saftbus.h>

namespace saftlib {

// T must be derived from Glib::Object
// T must provide T::ServiceType     -> an interface Service
// T must provide T::ConstructorType -> the type used for its constructor
template <typename T>
class RegisteredObject : public T
{
  public:
    static std::shared_ptr< RegisteredObject<T> > create(const std::shared_ptr<saftbus::Connection> &connection, const std::string& object_path, const typename T::ConstructorType& args);
    
    const std::shared_ptr<saftbus::Connection>& getConnection() const;
    const std::string& getSender() const;
    
  protected:
    RegisteredObject(const std::shared_ptr<saftbus::Connection> &connection, const std::string& object_path, const typename T::ConstructorType& args);
    virtual void rethrow(const char *method) const;
    
    typename T::ServiceType service;
};

template <typename T>
std::shared_ptr< RegisteredObject<T> > RegisteredObject<T>::create(const std::shared_ptr<saftbus::Connection> &connection, const std::string& object_path, const typename T::ConstructorType& args)
{
  return std::shared_ptr< RegisteredObject<T> >(new RegisteredObject<T>(connection, object_path, args));
}

template <typename T>
RegisteredObject<T>::RegisteredObject(const std::shared_ptr<saftbus::Connection> &connection, const std::string& object_path, const typename T::ConstructorType& args)
 : T(args), service(this, sigc::mem_fun(this, &RegisteredObject<T>::rethrow))
{
  service.register_self(connection, object_path);
}

template <typename T>
const std::shared_ptr<saftbus::Connection>& RegisteredObject<T>::getConnection() const
{
  return service.getConnection();
}

template <typename T>
const std::string& RegisteredObject<T>::getSender() const
{
  return service.getSender();
}

template <typename T>
void RegisteredObject<T>::rethrow(const char *method) const
{
  try {
    throw;
  } catch (std::runtime_error &e) {
    std::ostringstream str;
    str << method << ": " << e.what();
    throw saftbus::Error(saftbus::Error::IO_ERROR, str.str().c_str());
  } catch (...) {
    std::ostringstream str;
    str << method << ": unknown exception";
    throw saftbus::Error(saftbus::Error::IO_ERROR, str.str().c_str());
  }
}

} // saftlib

#endif
