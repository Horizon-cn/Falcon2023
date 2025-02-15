//========================================================================
//  This software is free: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License Version 3,
//  as published by the Free Software Foundation.
//
//  This software is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  Version 3 in the file COPYING that came with this distribution.
//  If not, see <http://www.gnu.org/licenses/>.
//========================================================================
/*!
  \file    VarIntVal.h
  \brief   C++ Interface: VarIntVal
  \author  Stefan Zickler, (C) 2008
*/

#ifndef VINTVAL_H_
#define VINTVAL_H_
#include "VarVal.h"

namespace VarTypes {
  /*!
    \class  VarIntVal
    \brief  A Vartype for storing integers
    \author Stefan Zickler, (C) 2008
    \see    VarTypes.h
  
    If you don't know what VarTypes are, please see \c VarTypes.h 
  */
  
  class VarIntVal : virtual public VarVal
  {
  protected:
  
    int _val;
  
  public:

    /// set the value of this node to val.
    virtual bool setIntz(int val)
    {
      lock();
      if (_val!=val) {
        _val=val;
        unlock();
        changed();
        return true;
      }
      unlock();
      return false;
    };
  
    VarIntVal(int default_val=0) : VarVal()
    {
      setIntz(default_val);
      changed();
    }
  
    virtual ~VarIntVal() {}
  
    virtual void printdebug() const
    {
      lock();
      printf("%d\n",_val);
      unlock();
    }
  
    virtual VarVal * clone() const {
      VarIntVal * tmp = new VarIntVal();
      tmp->setIntz(getIntz());
      return tmp;
    }

  
    virtual VarTypeId getType() const { return VARTYPE_ID_INT; };
  
    virtual string getString() const
    {
      char result[255];
      result[0]=0;
      sprintf(result,"%d",getIntz());
      return result;
    };
  
    virtual int    getIntz()    const{ int res; lock(); res=_val; unlock(); return res; };
    virtual double getDouble() const { return (double)getIntz(); };
    virtual int   get() const { return getIntz(); };
  
    virtual bool   getBool()  const { return (getIntz() == 1 ? true : false); };
  
    virtual bool setString(const string & val) { int num=0; sscanf(val.c_str(),"%d",&num); return setIntz(num); };
    virtual bool setDouble(double val) { return setIntz((int)val);  };
    virtual bool setBool(bool val)     { return setIntz(val ? 1 : 0);  };
  
    //plotting functions:
    virtual bool hasValue() const { return true; }
    virtual bool hasMaxValue() const { return false; }
    virtual bool hasMinValue() const { return false; }
    virtual double getMinValue() const { return 0; }
    virtual double getMaxValue() const  { return 1; }
    virtual double getValue() const { return getDouble(); }

  };
};


#endif /*VINTEGER_H_*/
