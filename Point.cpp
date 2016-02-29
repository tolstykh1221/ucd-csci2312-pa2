#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Point.h"

// iostream
using std::cout;
using std::endl;

// fstream
using std::ifstream;

// sstream
using std::stringstream;
using std::string;

//#include <gdiplus/gdiplustypes.h>

namespace Clustering
{
    unsigned int Point::__idGen = 0; // id generator

    Point::Point(int i)
    {
        __dim = i;
        __values = new double[__dim];
        __id = __idGen++;

        for(int i = 0; i < __dim; i++)
        {
            __values[i] = 0;
        }
    }


    Point::Point(const Point &point)
    {
        __id = point.getId();
        __dim = point.getDims();
        __values = new double[__dim];

        for(int i = 0; i < __dim; i++)
        {
            __values[i] = point.getValue(i);
        }

    }

    Point &Point::operator=(const Point &rhs)
    {
        if(this == &rhs)
        {
            return *this;
        }
        else
        {
            __id = rhs.__id;
            __dim = rhs.__dim;
            delete [] __values;

            __values = new double[__dim];

            for(int i = 0; i < __dim; i++)
            {
                __values[i] = rhs.getValue(i);
            }

        }

        return *this;
    }


    Point::~Point()
    {
        delete [] __values;
    }


    int Point::getId() const {
        return __id;
    }

    int Point::getDims() const {
        return __dim;
    }

    void Point::setValue(int i, double d)
    {
        __values[i] = d;
    }

    double Point::getValue(int i) const
    {
        return __values[i];
    }


    double Point::distanceTo(const Point &point) const
    {
        double dis = 0;

        for(int i = 0; i < __dim; i++)
        {
            dis += pow((__values[i] - point.getValue(i)),2);
        }

        return sqrt(dis);
    }


    Point &Point::operator*=(double d)
    {
        if(d==1)
        {
            return *this;
        }
        else
        {
            for(int i = 0; i < __dim; i++)
            {
                __values[i] *= d;
            }
        }
        return *this;
    }

    Point &Point::operator/=(double d)
    {
        if(d==1)
        {
            return *this;
        }
        else
        {
            for(int i = 0; i < __dim; i++)
            {
                __values[i] /= d;
            }
        }
        return *this;
    }


    const Point Point::operator*(double d) const
    {
        Point p(*this);

        p*=d;

        return p;
    }


    const Point Point::operator/(double d) const
    {
        Point p(*this);

        p/=d;

        return p;
    }


    double &Point::operator[](int index) {
        return __values[index];
    }


    Point &operator+=(Point &lhs, const Point &rhs)
    {
        for(int i = 0; i < lhs.getDims(); i++)
        {
            lhs.__values[i] += rhs.__values[i];
        }

        return lhs;
    }

    Point &operator-=(Point &lhs, const Point &rhs)
    {
        for(int i = 0; i < lhs.getDims(); i++)
        {
            lhs.__values[i] -= rhs.__values[i];
        }

        return lhs;
    }


    const Point operator+(const Point &lhs, const Point &rhs)
    {
        Point p(lhs);

        p += rhs;

        return p;
    }

    const Point operator-(const Point &lhs, const Point &rhs)
    {
        Point p(lhs);

        p -= rhs;

        return p;
    }


    bool operator==(const Point &lhs, const Point &rhs)
    {
        bool b = true;

        if(lhs.__id != rhs.__id)
        {
            return false;
        }
        else
        {
            for(int i = 0; i < lhs.__dim; i++)
            {
                if(lhs.__values[i] != rhs.__values[i])
                {
                    b = false;
                }
            }
        }
        return b;
    }

    bool operator!=(const Point &lhs, const Point &rhs)
    {
        if(lhs == rhs)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    bool operator<(const Point &lhs, const Point &rhs)
    {
        if(lhs == rhs)
        {
            return false;
        }
        else
        {
            for(int i = 0; i < lhs.__dim; i++)
            {
                if(lhs.__values[i] > rhs.__values[i])
                {
                    return false;
                }
            }
        }
        return true;
    }


    bool operator>(const Point &lhs, const Point &rhs)
    {
        if(lhs == rhs)
        {
            return false;
        }
        else
        {
            if(lhs < rhs)
                {
                    return false;
                }
        }
        return true;
    }


    bool operator<=(const Point &lhs, const Point &rhs)
    {
        if(lhs > rhs)
        {
            return false;
        }
        else
        {
            return true;
        }
    }


    bool operator>=(const Point &lhs, const Point &rhs)
    {
        if(lhs < rhs)
        {
            return false;
        }
        else
        {
            return true;
        }
    }


    std::ostream &operator<<(std::ostream &ostream, const Point &point)
    {
        int i = 0;
        for(; point.__dim - 1; i++)
        {
            ostream << point.__values[i] << ", ";
        }
        ostream << point.__values[i];

        return ostream;
    }


    std::istream &operator>>(std::istream &istream, Point &point)
    {

        std::string line;
        stringstream lineStream(line);
        string value;
        double d;
        int i = 0;

        while (getline(lineStream, value, ','))
        {
           // d = stod(value);

            point.setValue(i++, d);
        }

        return istream;
    }

}

