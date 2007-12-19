///////////////////////////////////////////////////////////////////////////////
// Name:        wx/unix/apptbase.h
// Purpose:     declaration of wxAppTraits for Unix systems
// Author:      Vadim Zeitlin
// Modified by:
// Created:     23.06.2003
// RCS-ID:      $Id$
// Copyright:   (c) 2003 Vadim Zeitlin <vadim@wxwidgets.org>
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#ifndef _WX_UNIX_APPTBASE_H_
#define _WX_UNIX_APPTBASE_H_

struct wxExecuteData;
class wxPipe;

// ----------------------------------------------------------------------------
// wxAppTraits: the Unix version adds extra hooks needed by Unix code
// ----------------------------------------------------------------------------

class WXDLLIMPEXP_BASE wxAppTraits : public wxAppTraitsBase
{
public:
    // wxExecute() support methods
    // ---------------------------

    // called before starting the child process and creates the pipe used for
    // detecting the process termination asynchronously in GUI, does nothing in
    // wxBase
    //
    // if it returns false, we should return from wxExecute() with an error
    virtual bool CreateEndProcessPipe(wxExecuteData& execData) = 0;

    // test if the given descriptor is the end of the pipe create by the
    // function above
    virtual bool IsWriteFDOfEndProcessPipe(wxExecuteData& execData, int fd) = 0;

    // ensure that the write end of the pipe is not closed by wxPipe dtor
    virtual void DetachWriteFDOfEndProcessPipe(wxExecuteData& execData) = 0;

    // wait for the process termination, return whatever wxExecute() must
    // return
    virtual int WaitForChild(wxExecuteData& execData) = 0;


    // wxThread helpers
    // ----------------

    // TODO

#if wxUSE_SOCKETS
    // returns the select()-based socket manager for console applications which
    // is also used by some ports (wxX11, wxDFB) in the GUI build (hence it is
    // here and not in wxConsoleAppTraits)
    virtual GSocketManager *GetSocketManager();
#endif
};

#endif // _WX_UNIX_APPTBASE_H_

