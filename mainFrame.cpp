#include "mainFrame.h"
#include <wx/wx.h>
#include <vector>
#include <string>
#include "task.h"


mainFrame::mainFrame(const wxString& title) 
	: wxFrame(nullptr , wxID_ANY , title)
{
	CreateControls();
	setUpSizers();
	BindEventHandlers();
	addSavedTasks();

}



void mainFrame::CreateControls()
{
	wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Bold());
	wxFont mainFont(wxFontInfo(wxSize(0, 24)));

	panel = new wxPanel(this);
	panel->SetFont(mainFont);

	headlineText = new wxStaticText(panel, wxID_ANY, "TO-DO List");
	headlineText->SetFont(headlineFont);
	

	inputField = new wxTextCtrl(panel, wxID_ANY, "",wxDefaultPosition , wxDefaultSize , wxTE_PROCESS_ENTER);
	addButton = new wxButton(panel, wxID_ANY, "Add");
	checkListBox = new wxCheckListBox(panel, wxID_ANY);
	clearButton = new wxButton(panel, wxID_ANY, "Clear");




}

void mainFrame::BindEventHandlers()
{
	addButton->Bind(wxEVT_BUTTON, &mainFrame::onAddButtonClicked, this);
	inputField->Bind(wxEVT_TEXT_ENTER, &mainFrame::onInputEnter, this);
	checkListBox->Bind(wxEVT_KEY_DOWN, &mainFrame::onListKeyDown, this);
	clearButton->Bind(wxEVT_BUTTON, &mainFrame::onClearButtonClicked, this);
	

}

void mainFrame::addSavedTasks()
{
	std::vector<task> tasks = loadTasksFromFile("tasks.txt");
	for (const task& task : tasks) {
		int index = checkListBox->GetCount();
		checkListBox->Insert(task.description, index);
		checkListBox->Check(index, task.done);
	}
}

void mainFrame::setUpSizers()
{

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	mainSizer->Add(headlineText, wxSizerFlags().CenterHorizontal());
	mainSizer->AddSpacer(25);

	
	wxBoxSizer* inputSizer = new wxBoxSizer(wxGA_HORIZONTAL);

	inputSizer->Add(inputField, wxSizerFlags().Proportion(1));
	inputSizer->AddSpacer(5);
	inputSizer->Add(addButton);


	mainSizer->Add(inputSizer, wxSizerFlags().Expand());
	mainSizer->AddSpacer(5);

	mainSizer->Add(checkListBox, wxSizerFlags().Expand().Proportion(1));
	mainSizer->AddSpacer(5);

	mainSizer->Add(clearButton);

	wxGridSizer* outerSizer = new wxGridSizer(1);
	outerSizer->Add(mainSizer, wxSizerFlags().Border(wxALL, 25).Expand());

	panel->SetSizer(outerSizer);
	outerSizer->SetSizeHints(this);

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

void mainFrame::onClearButtonClicked(wxCommandEvent& evt)
{
	if (checkListBox->IsEmpty()) {
		return;
	}

	wxMessageDialog dialog(this, "Are you sure you want to clear task ",
		"Clear", wxYES_NO );
	int result = dialog.ShowModal();

	if (result == wxID_YES)
	{
		checkListBox->Clear();
	}
}

void mainFrame::onWidnowsClose(wxCloseEvent& evt)
{
	std::vector<task> tasks;
	for (int i = 0; i < checkListBox->GetCount(); i++) {
		task task;
		task.description = checkListBox->GetString(i);
		task.done = checkListBox->IsChecked(i);
		tasks.push_back(task);
	}
	safeTaskToFile(tasks, "tasks.txt");
	evt.Skip();

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
