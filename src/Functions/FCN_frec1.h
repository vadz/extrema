/*
Copyright (C) 2005 Joseph L. Chuma, TRIUMF

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#ifndef FCN_FREC1
#define FCN_FREC1

#include "wx/wx.h"

#include "ScalarFunction.h"

class FCN_frec1 : public ScalarFunction
{
public:
  static FCN_frec1 *Instance()
  {
    if( !fcn_frec1_ )fcn_frec1_ = new FCN_frec1();
    return fcn_frec1_;
  }
  
  void ScalarEval( int, std::vector<double> & ) const;

private:
  FCN_frec1() : ScalarFunction( wxT("FREC1") )
  {}

  static FCN_frec1 *fcn_frec1_;
};

#endif

