#ifndef PHYSICAL_H
#define PHYSICAL_H

class Physical {
public:
    virtual ~Physical(void) {}

    virtual void collide(Physical& target1, Physical& target2) = 0;
};

#endif // PHYSICAL_H
