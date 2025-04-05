#ifndef TIMEUTILS_H
#define TIMEUTILS_H

#include <chrono>

class TimeUtils
{
    public:
        TimeUtils();
        virtual ~TimeUtils();
        static int getNowSeconds();

    protected:

    private:
};

#endif // TIMEUTILS_H
