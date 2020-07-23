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
#ifndef SAFTLIB_FIRMWAREDRIVER_H
#define SAFTLIB_FIRMWAREDRIVER_H

#include <memory>
#include <string>
#include "Device.h"
#include "Owned.h"

namespace saftlib {

struct FirmwareDevice {
  Device &device;
  std::shared_ptr<saftbus::Connection> connection;
  std::string name;
  std::string objectPath;
  std::shared_ptr<Owned> ref;
  FirmwareDevice(Device &dev);
};


class FirmwareDriverBase
{
  public:
    FirmwareDriverBase() { }
    void insert_self();
    void remove_self();
    
  protected:
    virtual void probe(FirmwareDevice& fd) = 0;
    
  private:
    FirmwareDriverBase *next;
    
    // non-copyable
    FirmwareDriverBase(const FirmwareDriverBase&);
    FirmwareDriverBase& operator = (const FirmwareDriverBase&);
  
  friend class FirmwareDrivers;
};

template <typename T>
class FirmwareDriver : private FirmwareDriverBase
{
  public:
    FirmwareDriver() { insert_self(); }
    ~FirmwareDriver() { remove_self(); }
  
  private:
    void probe(FirmwareDevice& fd) { return T::probe(fd); }
};

class FirmwareDrivers
{
  public:
    static void probe(FirmwareDevice& fd);
};

}

#endif
