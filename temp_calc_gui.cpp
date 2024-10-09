// To build: g++ temp_calc_gui.cpp `wx-config --cxxflags --libs` -o temp_calc_gui
#include <wx/wx.h>
 
class MyApp : public wxApp
{
public:
    bool OnInit() override;
};
 
wxIMPLEMENT_APP(MyApp);
 
class MyFrame : public wxFrame
{
public:
    MyFrame();
 
private:
    void OnNew(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};
 
enum
{
    ID_New = 1
};
 
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}
 
MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Reklewt's Spellcrafting Calculator")
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_New, "&New...\tCtrl-N",
                     "Create a new template");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
 
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
 
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
 
    SetMenuBar( menuBar );
 
    CreateStatusBar();
    SetStatusText("Welcome to Reklewt's Spellcrafting Calculator");
 
    Bind(wxEVT_MENU, &MyFrame::OnNew, this, ID_New);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}
 
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
 
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a spellcrafting calculator developed for the DAOC Eden Private Server",
                 "About Reklewt's Spellcrafting Calculator", wxOK | wxICON_INFORMATION);
}
 
void MyFrame::OnNew(wxCommandEvent& event)
{
    wxLogMessage("Created new template.");
}
