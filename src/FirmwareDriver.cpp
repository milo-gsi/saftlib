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
#define ETHERBONE_THROWS 1

#define __STDC_FORMAT_MACROS
#define __STDC_CONSTANT_MACROS

#include "FirmwareDriver.h"
#include <iostream>

namespace saftlib {

static FirmwareDriverBase *top = 0;

FirmwareDevice::FirmwareDevice(Device &dev) : device(dev) {
}


void FirmwareDriverBase::insert_self()
{
	std::cerr << "FirmwareDriverBase::insert_self()" << std::endl;
  next = top;
  top = this;
}

void FirmwareDriverBase::remove_self()
{
  FirmwareDriverBase **i;
  for (i = &top; *i != this; i = &(*i)->next) { }
  *i = next;
}

void FirmwareDrivers::probe(FirmwareDevice& fd)
{
  std::cerr << "FirmwareDrivers::probe(fd) called" << std::endl;
  int n = 0;
  for (FirmwareDriverBase *i = top; i; i = i->next) {
  	std::cerr << "   probe Firmwaredriver " << n++ << " ..." << std::endl;
    i->probe(fd);
    std::cerr << "    ... done" << std::endl;
  }
}

}
