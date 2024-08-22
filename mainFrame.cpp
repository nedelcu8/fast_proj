#include "mainFrame.h"
#include <wx/wx.h>
#include <vector>
#include <string>
#include "task.h"


mainFrame::mainFrame(const wxString& title) : wxFrame(nullptr , wxID_ANY , title)
{
	CreateControls();
	BindEventHandlers();

}

void mainFrame::CreateControls()
{
	wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Bold());
	wxFont mainFont(wxFontInfo(wxSize(0, 24)));

	panel = new wxPanel(this);
	panel->SetFont(mainFont);

	headlineText = new wxStaticText(panel, wxID_ANY, "TO-DO List", 
		wxPoint(0, 22), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
	headlineText->SetFont(headlineFont);
	

	inputField = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 80),
		wxSize(495, 35) , wxTE_PROCESS_ENTER);
	addButton = new wxButton(panel, wxID_ANY, "Add", wxPoint(600, 80),
		wxSize(100, 35));
	checkListBox = new wxCheckListBox(panel, wxID_ANY,wxPoint(100, 120),
		wxSize(600, 400));
	clearButton = new wxButton(panel, wxID_ANY, "Clear", wxPoint(100, 525),
		wxSize(100, 35));



}

void mainFrame::BindEventHandlers()
{
	addButton->Bind(wxEVT_BUTTON, &mainFrame::onAddButtonClicked, this);
	inputField->Bind(wxEVT_TEXT_ENTER, &mainFrame::onInputEnter, this);
	checkListBox->Bind(wxEVT_KEY_DOWN, &mainFrame::onListKeyDown, this);
}

void mainFrame::onAddButtonClicked(wxCommandEvent& evt)
{
	AddTaskFromInput();
}

void mainFrame::onInputEnter(wxCommandEvent& env)
{
	AddTaskFromInput();
}

void mainFrame::onListKeyDown(wxKeyEvent& evt)
{
	switch (evt.GetKeyCode()) {
		case WXK_DELETE :
			DeleteSelectedTask();
			break;
		case WXK_UP :
			MoveSelectedTask(-1);
			break;
		case WXK_DOWN :
			MoveSelectedTask(1);
			break;

	}
}



void mainFrame::AddTaskFromInput()
{
	wxString descripton = inputField->GetValue();

	if (!descripton.IsEmpty()) {
		checkListBox->Insert(descripton, checkListBox->GetCount());
		inputField->Clear();

	}

	inputField->SetFocus();

}

void mainFrame::DeleteSelectedTask()
{
	int selectedIndex = checkListBox->GetSelection();
	
	if (selectedIndex == wxNOT_FOUND) {
		return;
	}
	checkListBox->Delete(selectedIndex);
}

void mainFrame::MoveSelectedTask(int offset)
{
	int selectedIndex = checkListBox->GetSelection();
	if (selectedIndex == wxNOT_FOUND) {
		return;
	}
	int newIndex = selectedIndex + offset;
	if (newIndex >= 0 && newIndex < checkListBox->GetCount()) {
		SwapTask(selectedIndex, newIndex);
		checkListBox->SetSelection(newIndex, true);
	}
}

void mainFrame::SwapTask(int i, int j)
{
	task taskI{ checkListBox->GetString(i).ToStdString(), checkListBox->IsChecked(i) };
	task taskJ{ checkListBox->GetString(j).ToStdString(), checkListBox->IsChecked(j) };
	checkListBox->SetString(i, taskJ.description);
	checkListBox->Check(i, taskJ.done);

	checkListBox->SetString(j, taskI.description);
	checkListBox->Check(j, taskI.done);




}
