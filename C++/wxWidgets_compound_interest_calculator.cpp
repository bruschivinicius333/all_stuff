#include "wx/wx.h"
#include "wx/numdlg.h"
#include "wx/statline.h"
#include "wx/stattext.h"
#include "wx/spinctrl.h"
#include "wx/msgdlg.h"
#include <iostream>

class MainFrame : public wxFrame {
    private:
        wxPanel *mainPanel = new wxPanel(this);

        wxBoxSizer *mainPanelSizer = new wxBoxSizer(wxVERTICAL);

        const int commonSpacing = 10;

        // TODO: Arrumar o MIN e MAX dos campos

        wxStaticText *debtValueLabel = new wxStaticText(mainPanel, wxID_ANY, wxT("Valor do débito:"));
        wxSpinCtrlDouble *debtValueInput = new wxSpinCtrlDouble(mainPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 999, 0, 0.01);

        wxStaticText *monthsLateLabel = new wxStaticText(mainPanel, wxID_ANY, wxT("Meses de atraso:"));
        wxSpinCtrl *monthsLateInput = new wxSpinCtrl(mainPanel);

        wxStaticText *percentualDeMultaLabel = new wxStaticText(mainPanel, wxID_ANY, wxT("Percentual de multa:"));
        wxSpinCtrlDouble *percentualDeMultaInput = new wxSpinCtrlDouble(mainPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 999, 0, 0.01);
        
        wxStaticText *percentualDeJurosLabel = new wxStaticText(mainPanel, wxID_ANY, wxT("Percentual de juros (mensal):"));
        wxSpinCtrlDouble *percentualDeJurosInput = new wxSpinCtrlDouble(mainPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 999, 0, 0.01);

    public:
        MainFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title) {

            mainPanelSizer->Add(debtValueLabel, 0, wxALIGN_CENTER | wxALL, commonSpacing);
            mainPanelSizer->Add(debtValueInput, 0, wxALIGN_CENTER | wxALL, commonSpacing);

            mainPanelSizer->Add(monthsLateLabel, 0, wxALIGN_CENTER | wxALL, commonSpacing);
            mainPanelSizer->Add(monthsLateInput, 0, wxALIGN_CENTER | wxALL, commonSpacing);

            mainPanelSizer->Add(percentualDeMultaLabel, 0, wxALIGN_CENTER | wxALL, commonSpacing);
            mainPanelSizer->Add(percentualDeMultaInput, 0, wxALIGN_CENTER | wxALL, commonSpacing);

            mainPanelSizer->Add(percentualDeJurosLabel, 0, wxALIGN_CENTER | wxALL, commonSpacing);
            mainPanelSizer->Add(percentualDeJurosInput, 0, wxALIGN_CENTER | wxALL, commonSpacing);

            const auto submitButtonsPanel = new wxPanel(mainPanel);

            const auto submitButtonsSizer = new wxBoxSizer(wxVERTICAL);

            const auto submitJurosSimples = new wxButton(submitButtonsPanel, wxID_OK, wxT("Calcular com juros simples"));
            submitJurosSimples->Bind(wxEVT_BUTTON, &MainFrame::OnJurosSimples, this);

            submitButtonsSizer->Add(submitJurosSimples);

            const auto submitJurosCompostos = new wxButton(submitButtonsPanel, wxID_OK, wxT("Calcular com juros compostos"));
            submitJurosCompostos->Bind(wxEVT_BUTTON, &MainFrame::OnJurosCompostos, this);

            submitButtonsSizer->Add(submitJurosCompostos);
            
            submitButtonsPanel->SetSizerAndFit(submitButtonsSizer);

            mainPanelSizer->Add(submitButtonsPanel, 0, wxALIGN_CENTER | wxALL, commonSpacing);

            mainPanel->SetSizerAndFit(mainPanelSizer);
        }
        void OnJurosSimples(wxCommandEvent &) {
            // montante = capital + multa + jurosCalculados
            double totalDebt = debtValueInput->GetValue();
            double multa = totalDebt * (percentualDeMultaInput->GetValue() / 100);
            double juros = totalDebt * (percentualDeJurosInput->GetValue() / 100) * monthsLateInput->GetValue();
            ShowResultPopUp(totalDebt + multa + juros);
        }
        void OnJurosCompostos(wxCommandEvent &) {
            // M = C * ((1 + i) ** t) + multa
            double totalDebt = debtValueInput->GetValue();
            double multa = totalDebt * (percentualDeMultaInput->GetValue() / 100);
            double montante = totalDebt * pow(1 + (percentualDeJurosInput->GetValue() / 100), monthsLateInput->GetValue());
            ShowResultPopUp(montante + multa);
        }
        void ShowResultPopUp(double result) {
            const auto popUpResult = new wxMessageDialog(NULL, wxString("Total: ") + wxString::Format(wxT("%.2lf"), result), wxT("Resultado"), wxSTAY_ON_TOP);
            popUpResult->ShowModal();
        }
        void OnQuit(wxCommandEvent &) {
            Close();
        }
};

class App : public wxApp {
    public:
        virtual bool OnInit() {
            
            const auto minimal = new MainFrame(wxT("Calculadora de débito total"));

            minimal->Show(true);

            return true;
        }
};

IMPLEMENT_APP(App);
