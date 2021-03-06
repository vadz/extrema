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
#include <iostream>
#include <fstream>

#include "wx/statline.h"
#include "wx/textctrl.h"

#include <wx/persist/toplevel.h>

#include "SetAspectRatioForm.h"
#include "VisualizationWindow.h"
#include "ExGlobals.h"

// the event tables connect the wxWidgets events with the
// event handler functions which process them
//
BEGIN_EVENT_TABLE( SetAspectRatioForm, wxFrame )
  EVT_BUTTON( wxID_OK, SetAspectRatioForm::OnOK )
  EVT_BUTTON( wxID_CANCEL, SetAspectRatioForm::OnCancel )
  EVT_CLOSE( SetAspectRatioForm::CloseEventHandler )
END_EVENT_TABLE()

SetAspectRatioForm::SetAspectRatioForm( VisualizationWindow *parent )
    : wxFrame((wxWindow*)parent,wxID_ANY,wxT("Aspect ratio"),wxDefaultPosition,wxSize(215,130))
{
  wxPanel* const mainPanel = new wxPanel(this);
  wxBoxSizer *mainSizer = new wxBoxSizer( wxVERTICAL );

  wxPanel *topPanel = new wxPanel( mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER );
  wxBoxSizer *topSizer = new wxBoxSizer( wxVERTICAL );

  wxPanel *heightPanel = new wxPanel( topPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER );
  wxBoxSizer *heightSizer = new wxBoxSizer( wxHORIZONTAL );

  heightSizer->Add( new wxStaticText(heightPanel,-1,wxT("Height")), wxSizerFlags(0).Border(wxALL,5) );
  heightTC_ = new wxTextCtrl( heightPanel, -1 );
  heightSizer->Add( heightTC_, wxSizerFlags(0).Border(wxALL,5) );

  heightPanel->SetSizer( heightSizer );
  
  topSizer->Add( heightPanel, wxSizerFlags(0).Border(wxALL,5) );

  topSizer->Add( new wxStaticLine(topPanel), wxSizerFlags(0).Expand().Border(wxALL,1) );

  wxPanel *widthPanel = new wxPanel( topPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER );
  wxBoxSizer *widthSizer = new wxBoxSizer( wxHORIZONTAL );

  widthSizer->Add( new wxStaticText(widthPanel,-1,wxT(" Width")), wxSizerFlags(0).Border(wxALL,5) );
  widthTC_ = new wxTextCtrl( widthPanel, -1 );
  widthSizer->Add( widthTC_, wxSizerFlags(0).Border(wxALL,5) );

  widthPanel->SetSizer( widthSizer );
  
  topSizer->Add( widthPanel, wxSizerFlags(0).Border(wxALL,5) );

  topPanel->SetSizer( topSizer );

  mainSizer->Add( topPanel, wxSizerFlags(0).Centre().Border(wxALL,1) );
  
  wxPanel *bottomPanel = new wxPanel( mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER );
  wxBoxSizer *bottomSizer = new wxBoxSizer( wxHORIZONTAL );

  wxButton *OKButton = new wxButton( bottomPanel, wxID_OK, wxT("OK") );
  OKButton->SetToolTip( wxT("click to accept the height and width as entered and close this form") );
  bottomSizer->Add( OKButton, wxSizerFlags(0).Border(wxALL,2) );

  wxButton *cancelButton = new wxButton( bottomPanel, wxID_CANCEL, wxT("Cancel") );
  cancelButton->SetToolTip( wxT("click to close this form without changing the aspect ratio") );
  bottomSizer->Add( cancelButton, wxSizerFlags(0).Border(wxALL,2) );

  bottomPanel->SetSizer( bottomSizer );

  mainSizer->Add( bottomPanel, wxSizerFlags(0).Centre().Border(wxALL,1) );

  mainPanel->SetSizer( mainSizer );

  wxPersistentRegisterAndRestore(this, "SetAspectRatioForm");

  double ar = ExGlobals::GetAspectRatio();
#if wxMINOR_VERSION < 8
  if( ar > 1.0 )
  {
    heightTC_->SetValue( wxString()<<ar );
    widthTC_->SetValue( wxT("1") );
  }
  else
  {
    heightTC_->SetValue( wxT("1") );
    widthTC_->SetValue( wxString()<<(1./ar) );
  }
#else
  if( ar > 1.0 )
  {
    heightTC_->ChangeValue( wxString()<<ar );
    widthTC_->ChangeValue( wxT("1") );
  }
  else
  {
    heightTC_->ChangeValue( wxT("1") );
    widthTC_->ChangeValue( wxString()<<(1./ar) );
  }
#endif
  Show( true );
}

void SetAspectRatioForm::CloseEventHandler( wxCloseEvent &WXUNUSED(event) )
{
  ExGlobals::GetVisualizationWindow()->ZeroSetAspectRatioForm();

  Destroy();
}

void SetAspectRatioForm::OnOK( wxCommandEvent &WXUNUSED(event) )
{
  double height, width;
  if( !GetValues(height,width) )return;
  ExGlobals::SetAspectRatio( height/width );
  ExGlobals::GetVisualizationWindow()->ResetPages();
  ExGlobals::GetVisualizationWindow()->ResetWindows();
  Close();
}

void SetAspectRatioForm::OnCancel( wxCommandEvent &WXUNUSED(event) )
{ Close(); }

bool SetAspectRatioForm::GetValues( double &height, double &width )
{
  if( heightTC_->GetValue().empty() )
  {
    wxMessageBox( wxString(wxT("No value was entered for height")),
                  wxT("Fatal error"), wxOK|wxICON_ERROR, this );
    return false;
  }
  if( !heightTC_->GetValue().ToDouble(&height) )
  {
    wxMessageBox( wxString(wxT("Invalid value entered for height")),
                  wxT("Fatal error"), wxOK|wxICON_ERROR, this );
#if wxMINOR_VERSION < 8
    heightTC_->SetValue( wxT("") );
#else
    heightTC_->ChangeValue( wxT("") );
#endif
    return false;
  }
  if( height <= 0.0 )
  {
    wxMessageBox( wxString(wxT("Height must be > 0")),
                  wxT("Fatal error"), wxOK|wxICON_ERROR, this );
#if wxMINOR_VERSION < 8
    heightTC_->SetValue( wxT("") );
#else
    heightTC_->ChangeValue( wxT("") );
#endif
    return false;
  }
  if( widthTC_->GetValue().empty() )
  {
    wxMessageBox( wxString(wxT("No value was entered for width")),
                  wxT("Fatal error"), wxOK|wxICON_ERROR, this );
    return false;
  }
  if( !widthTC_->GetValue().ToDouble(&width) )
  {
    wxMessageBox( wxString(wxT("Invalid value entered for width")),
                  wxT("Fatal error"), wxOK|wxICON_ERROR, this );
#if wxMINOR_VERSION < 8
    widthTC_->SetValue( wxT("") );
#else
    widthTC_->ChangeValue( wxT("") );
#endif
    return false;
  }
  if( width <= 0.0 )
  {
    wxMessageBox( wxString(wxT("Width must be > 0")),
                  wxT("Fatal error"), wxOK|wxICON_ERROR, this );
#if wxMINOR_VERSION < 8
    widthTC_->SetValue( wxT("") );
#else
    widthTC_->ChangeValue( wxT("") );
#endif
    return false;
  }
  return true;
}

// end of file
