#pragma once
#include <wx/wx.h>

class mainFrame : public wxFrame
{
public:
	mainFrame(const wxString& title);
private:

	void CreateControls();
	void BindEventHandlers();
	void addSavedTasks();
	void setUpSizers();
	void onAddButtonClicked(wxCommandEvent& evt);
	void onInputEnter(wxCommandEvent& env);
	void onListKeyDown(wxKeyEvent& evt);
	void onClearButtonClicked(wxCommandEvent& evt);
	void onWidnowsClose(wxCloseEvent& evt);


	void AddTaskFromInput();
	void DeleteSelectedTask();

	void MoveSelectedTask(int offset);
	void SwapTask(int i, int j);

	wxPanel* panel;
	wxStaticText* headlineText;
	wxTextCtrl* inputField;
	wxButton* addButton;
	wxCheckListBox* checkListBox;
	wxButton* clearButton;

};

