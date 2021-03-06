/*
Copyright (C) 2007 Joseph L. Chuma, TRIUMF

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
#ifndef CMD_ELLIPSECOMMAND
#define CMD_ELLIPSECOMMAND

#include "Command.h"

class ParseLine;

class CMD_ellipse : public Command
{
public:
  static CMD_ellipse *Instance()
  {
    if( !cmd_ellipse_ )cmd_ellipse_ = new CMD_ellipse();
    return cmd_ellipse_;
  }

  void Execute( ParseLine const * );

private:
  CMD_ellipse();
  void PopulateEllipse( bool, bool, ParseLine const *,
                        int, double, double, double, double, double );

  static CMD_ellipse *cmd_ellipse_;
};

#endif
