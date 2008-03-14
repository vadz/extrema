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
#include <iostream>
#include <stdexcept>

#include "CommandTextCtrl.h"
#include "AnalysisCommandPanel.h"
#include "ExGlobals.h"

// the event tables connect the wxWidgets events with the
// event handler functions which process them

BEGIN_EVENT_TABLE( CommandTextCtrl, wxTextCtrl )
  EVT_KEY_DOWN( CommandTextCtrl::OnKeyDown )
  EVT_KEY_UP( CommandTextCtrl::OnKeyUp )
  EVT_CHAR( CommandTextCtrl::OnChar )
END_EVENT_TABLE()

CommandTextCtrl::CommandTextCtrl( AnalysisCommandPanel *parent )
    : wxTextCtrl( (wxWindow*)parent, wxID_ANY, wxT(""), wxDefaultPosition,
                  wxDefaultSize, wxTE_PROCESS_ENTER )
{
  SetToolTip( wxT("enter commands here") );
  commandStringsIndex_ = -1;
}

wxString CommandTextCtrl::GetACommand()
{
  if( GetLineLength(0) == 0 ) // nothing was input
  {
    ExGlobals::WriteOutput( wxT(' ') );
    return wxString(); // return empty string
  }
  wxString inputLine( GetLineText(0) );
  ExGlobals::WriteOutput( inputLine );
  //
  // trim leading and trailing blanks
  //
  std::size_t rTemp = inputLine.find_last_not_of( wxT(' ') );
  if( rTemp != inputLine.npos )
  {
    std::size_t lTemp = inputLine.find_first_not_of( wxT(' ') );
    if( lTemp != inputLine.npos )inputLine = inputLine.substr( lTemp, rTemp-lTemp+1 );
  }
  else inputLine = wxT(' ');
  //
  Clear(); // clear the command entry field
  return inputLine;
}

wxString CommandTextCtrl::GetPreviousCommand()
{
  wxString s;
  if( commandStringsIndex_ >= 0 )s = commandStrings_[commandStringsIndex_--];
  return s;
}

wxString CommandTextCtrl::GetNextCommand()
{
  wxString s;
  if( commandStringsIndex_ < static_cast<int>(commandStrings_.size())-1 )
    s = commandStrings_[++commandStringsIndex_];
  return s;
}

void CommandTextCtrl::AddCommandString( wxString const &s )
{
  commandStrings_.push_back( s );
  commandStringsIndex_ = static_cast<int>(commandStrings_.size())-1;
}

void CommandTextCtrl::OnKeyDown( wxKeyEvent &event )
{
  switch ( event.GetKeyCode() )
  {
    case WXK_DOWN:
    {
      wxString s( GetNextCommand() );
      if( s.empty() )Clear();
      else
      {
        SetValue(s);
        SetInsertionPointEnd();
      }
      
      break;
    }
    case WXK_UP:
    {
      wxString s( GetPreviousCommand() );
      if( s.empty() )Clear();
      else
      {
        SetValue(s);
        SetInsertionPointEnd();
      }
      break;
    }
    case WXK_RETURN:
    {
      DoACommand();
      break;
    }
    default:
    {
      event.Skip();
      break;
    }
  }
}

void CommandTextCtrl::DoACommand()
{
  static wxString command;
  wxString inputLine( GetACommand() );
  //
  bool continuing = false;
  int len = inputLine.size();
  if( inputLine[len-1] == ExGlobals::GetContinuationCharacter() )
  {
    if( --len == 0 )
    {
      ExGlobals::WarningMessage( wxT("continuation line is empty") );
      command.clear();
      return;
    }
    inputLine.erase( len, 1 );  // erase continuation character
    continuing = true;
  }
  command += inputLine;
  if( continuing )return; // go back and get the next part of the command line
  if( command.empty() || command==wxString(wxT(' ')) )
  {
    if( ExGlobals::GetPausingScript() )ExGlobals::RestartScripts();
    return;
  }
  ExGlobals::PreParse( command );
  AddCommandString( command );
  try
  {
    ExGlobals::ProcessCommand( command );
  }
  catch ( std::runtime_error &e )
  {
    wxMessageDialog *md = new wxMessageDialog( (wxWindow*)this,
                                               wxString(e.what(),wxConvUTF8),
                                               wxT("ERROR"),
                                               wxOK|wxICON_ERROR );
    md->ShowModal();
    command.clear();
    return;
  }
  command.clear();
  if( ExGlobals::GetExecuteCommand() )
  {
    // the script run here must be the top level script
    // since it is run interactively
    //
    try
    {
      ExGlobals::RunScript();
    }
    catch ( std::runtime_error const &e )
    {
      ExGlobals::ShowScriptError( e.what() );
      ExGlobals::StopAllScripts();
    }
  }
}

// end of file
