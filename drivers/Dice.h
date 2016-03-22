#ifndef DICE_H
#define DICE_H


#include "OpenDevice.h"
#include "interfaces/Dice.h"


namespace saftlib {


class Dice : public iDice, public Glib::Object {
  public:
    typedef Dice_Service ServiceType;
    struct ConstructorType {
      int upperLimit;
    };

    static Glib::RefPtr<Dice> create(const Glib::ustring& objectPath, ConstructorType args);

    Dice(ConstructorType args);
    ~Dice();
// methods
    guint32 Roll();

    void RollMultiple(guint32);

// properties
    Glib::ustring getVersion() const {return "1.2.a.b";};

    guint32 getCount() const;

    double getAverage() const;

    guint32 getSeed() const {return seed_;};

    guint32 getUpperLimit() const;
    void setUpperLimit(guint32);

  protected:
    int upperLimit_;
    guint32 count_;
    guint32 sum_;
    const int seed_;
};

}

#endif
