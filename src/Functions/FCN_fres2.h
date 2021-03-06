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
#ifndef FCN_FRES2
#define FCN_FRES2

#include "wx/wx.h"

#include "ScalarFunction.h"

class FCN_fres2 : public ScalarFunction
{
public:
  static FCN_fres2 *Instance()
  {
    if( !fcn_fres2_ )fcn_fres2_ = new FCN_fres2();
    return fcn_fres2_;
  }
  
  void ScalarEval( int, std::vector<double> & ) const;

private:
  FCN_fres2() : ScalarFunction( wxT("FRES2") )
  {}

  static FCN_fres2 *fcn_fres2_;
};

#endif

