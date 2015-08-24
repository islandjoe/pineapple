#pragma once

#include <signal.h>
#include <string>

#include <wx/filename.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/process.h>
#include <wx/timer.h>
#include <wx/toolbar.h>
#include <wx/webview.h>

#include "callback.hh"

class MainFrame: public wxFrame
{
    enum {
        wxID_EXPORT_PYTHON = 10000, wxID_EXPORT_MARKDOWN,
        wxID_EXPORT_PDF, wxID_EXPORT_HTML,
        wxID_OPEN_EXAMPLE,
        wxID_CLOSE_ALL,
        wxID_CELL_CUT, wxID_CELL_COPY, wxID_CELL_PASTE,
        wxID_INSERT, wxID_DELETE, wxID_UNDELETE,
        wxID_SPLIT, wxID_MERGE,
        wxID_MOVE_UP, wxID_MOVE_DOWN,
        wxID_TRUST,
        wxID_RUN, wxID_RUN_NEXT, wxID_RUN_ALL, wxID_RUN_ALL_ABOVE, wxID_RUN_ALL_BELOW,
        wxID_CELL_CODE, wxID_CELL_MARKDOWN, wxID_CELL_RAW,
        wxID_KERNEL_INTERRUPT, wxID_KERNEL_RESTART, wxID_KERNEL_RECONNECT,
        wxID_HELP_KEYBOARD, wxID_HELP_NOTEBOOK, wxID_HELP_MARKDOWN,
        wxID_KERNEL_BUSY,
        wxID_TIMER
    };

public:

    MainFrame(std::string url0, std::string filename, const wxString &title, const wxPoint &pos, const wxSize &size, bool indirect_load);

    static void Spawn(std::string url, std::string filename, bool indirect_load=false);
    static void CreateNew(bool indirect_load=false);

    wxProcess *server;
    wxWebView *webview;
    wxMenuBar *menubar;
    wxToolBar *toolbar;
    std::string url;
    std::string local_filename;
    CallbackHandler handler;
    bool jupyter_ready;

    void OnClose(wxCloseEvent &event);
    void OnPageLoad(wxWebViewEvent &event);
    void OnSubprocessTerminate(wxProcessEvent &event);
    void OnTitleChanged(wxWebViewEvent &event);
    void OnNewWindow(wxWebViewEvent &event);

    static void OnNew(wxCommandEvent &event);
    static void OnOpen(wxCommandEvent &event);
    void OnSave(wxCommandEvent &event);
    void OnSaveAs(wxCommandEvent &event);
    void OnProperties(wxCommandEvent &event);
    void OnMenuClose(wxCommandEvent &event);
    void OnMenuCloseAll(wxCommandEvent &event);
    void OnPrint(wxCommandEvent &event);
    void OnOpenExample(wxCommandEvent &event);
    void OnTimerEvent(wxTimerEvent &event);

    void SetupMenu();
    void SetupToolbar();
    void SetupWebView();
    void SetupLayout(const wxPoint &pos, const wxSize &size);
    void SetupBindings();
    void LoadDocument(bool indirect_load=true);

    void Save();
    void Save(Callback::t continuation);
    void eval_js(std::string expression);
    void eval_js(std::string expression, Callback::t success);
    void eval_js_event(std::string expression, std::string evtname, Callback::t continuation);
    void Export(std::string format);

    std::string jupyter_click_code(std::string id);
    wxTimer m_save_on_close_timer;
};
