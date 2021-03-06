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
#ifndef CMD_WINDOW
#define CMD_WINDOW

#include "Command.h"

class ParseLine;

class CMD_window : public Command
{
public:
  static CMD_window *Instance()
  {
    if( !cmd_window_ )cmd_window_ = new CMD_window();
    return cmd_window_;
  }
  
  void Execute( ParseLine const * );

private:
  CMD_window();
  static CMD_window *cmd_window_;
};

#endif
