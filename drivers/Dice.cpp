#define ETHERBONE_THROWS 1

#include <iostream>
#include <time.h>

#include "Dice.h"

#include "RegisteredObject.h"

namespace saftlib
{

Dice::Dice(ConstructorType args) :  upperLimit_(args.upperLimit), seed_(time(NULL))
{
  srand(seed_);
}

Dice::~Dice()
{
}

Glib::RefPtr<Dice> Dice::create(const Glib::ustring& objectPath, ConstructorType args)
{
  return RegisteredObject<Dice>::create(objectPath, args);
}

guint32 Dice::Roll()
{
  struct timespec sleepfor = {0, 500000000}, rem = {0,0};
  nanosleep(&sleepfor, &rem);

  ++count_;

  guint32 score = (rand() % upperLimit_) + 1;
  sum_ += score;

  Count(count_); // signal change
  Average(getAverage()); // signal new average

  return score;
}

void Dice::RollMultiple(guint32 count)
{
  int score=0;
  for (guint32 roll=0; roll<count; ++roll)
  {
    score += Roll();
  }
  std::cout << score << std::endl;
  Rolled(score, count);
}

guint32 Dice::getCount() const
{
  return count_;
}

double Dice::getAverage() const
{
  return (count_ > 0) ? ((double)sum_)/count_ : 0;
}

guint32 Dice::getUpperLimit() const
{
  return upperLimit_;
}

void Dice::setUpperLimit(guint32 upperLimit)
{
  if (upperLimit < 1)
    throw Gio::DBus::Error(Gio::DBus::Error::INVALID_ARGS, "Dice: Invalid Upper Limit");
  upperLimit_ = upperLimit;
}

}
