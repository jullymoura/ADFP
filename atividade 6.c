#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TF1.h>
#include <TChain.h>
#include <TLorentzVector.h>

void Exercicio6() {
    
    // Abrindo o arquivo ROOT
    TChain* fChain = new TChain("Events");
    fChain->Add("76A312CE-F9C3-5F4D-9093-F26D7C50BF61.root");

    // Declarando variáveis
    UInt_t nTau, nMuon, nElectron, nJet;
    TLorentzVector muon1, muon2;
    float Tau_pt[9], Muon_pt[9], Electron_pt[9], Jet_pt[9], Tau_eta[9], Muon_eta[9], Electron_eta[9], Jet_eta[9], Tau_phi[9], Muon_phi[9], Electron_phi[9], Jet_phi[9];

    // Ligando as variáveis à tree
    fChain->SetBranchAddress("nTau", &nTau);
    fChain->SetBranchAddress("nMuon", &nMuon);
    fChain->SetBranchAddress("nElectron", &nElectron);
    fChain->SetBranchAddress("nJet", &nJet);
    fChain->SetBranchAddress("Tau_pt", &Tau_pt);
    fChain->SetBranchAddress("Muon_pt", &Muon_pt);
    fChain->SetBranchAddress("Electron_pt", &Electron_pt);
    fChain->SetBranchAddress("Jet_pt", &Jet_pt);
    fChain->SetBranchAddress("Tau_eta", &Tau_eta);
    fChain->SetBranchAddress("Muon_eta", &Muon_eta);
    fChain->SetBranchAddress("Electron_eta", &Electron_eta);
    fChain->SetBranchAddress("Jet_eta", &Jet_eta);
    fChain->SetBranchAddress("Tau_phi", &Tau_phi);
    fChain->SetBranchAddress("Muon_phi", &Muon_phi);
    fChain->SetBranchAddress("Electron_phi", &Electron_phi);
    fChain->SetBranchAddress("Jet_phi", &Jet_phi);

    // Limiar de pT e eta
    const float ptCut = 20.0;  // Limiar de pT (GeV/c)
    const float etaCut = 2.5;  // Limiar de |eta|

    // Criando histogramas
    TH1F *h_pt_tau = new TH1F("Taupt", "Distribuicao de p_{T} - Tau", 50, 0, 200);
    TH1F *h_pt_muon = new TH1F("Muonpt", "Distribuicao de p_{T} - Muon", 50, 0, 200);
    TH1F *h_pt_electron = new TH1F("Electron_pt", "Distribuicao de p_{T} - Eletron", 50, 0, 200);
    TH1F *h_pt_jet = new TH1F("Jetpt", "Distribuicao de p_{T} - Jato", 50, 0, 200);

    TH1F *h_eta_tau = new TH1F("Taueta", "Distribuicao de #eta - Tau", 50, -3, 3);
    TH1F *h_eta_muon = new TH1F("Muoneta", "Distribuicao de #eta - Muon", 50, -3, 3);
    TH1F *h_eta_electron = new TH1F("Electron_eta", "Distribuicao de #eta - Eletron", 50, -3, 3);
    TH1F *h_eta_jet = new TH1F("Jeteta", "Distribuicao de #eta - Jato", 50, -3, 3);

    TH1F *h_phi_tau = new TH1F("Tauphi", "Distribuicao de #phi - Tau", 50, -TMath::Pi(), TMath::Pi());
    TH1F *h_phi_muon = new TH1F("Muonphi", "Distribuicao de #phi - Muon", 50, -TMath::Pi(), TMath::Pi());
    TH1F *h_phi_electron = new TH1F("Electronphi", "Distribuicao de #phi - Eletron", 50, -TMath::Pi(), TMath::Pi());
    TH1F *h_phi_jet = new TH1F("Jetphi", "Distribuicao de #phi - Jato", 50, -TMath::Pi(), TMath::Pi());

    // Criando histograma para massa invariante
    TH1F *h_mass = new TH1F("in_mass", "Massa Invariante", 50, 0, 200);
    h_mass->GetXaxis()->SetTitle("Massa Invariante (GeV/c^{2})");
    h_mass->GetYaxis()->SetTitle("Eventos");

    // Iterando sobre os eventos
    int nentries = fChain->GetEntries();
    for (int i = 0; i < nentries; i++) {
        fChain->GetEntry(i);
        
    // Preenchendo histogramas de distribuição
            for (int j = 0; j < nTau; j++) {
                if (Tau_pt[j] > ptCut && abs(Tau_eta[j]) < etaCut) {
                    h_pt_tau->Fill(Tau_pt[j]);
                    h_eta_tau->Fill(Tau_eta[j]);
                    h_phi_tau->Fill(Tau_phi[j]);
                }
            }
            for (int j = 0; j < nMuon; j++) {
                 if (Muon_pt[j] > ptCut && abs(Muon_eta[j]) < etaCut) {
                    h_pt_muon->Fill(Muon_pt[j]);
                    h_eta_muon->Fill(Muon_eta[j]);
                    h_phi_muon->Fill(Muon_phi[j]);
                 }
            }
            for (int j = 0; j < nElectron; j++) {
                if (Electron_pt[j] > ptCut && abs(Electron_eta[j]) < etaCut) {
                    h_pt_electron->Fill(Electron_pt[j]);
                    h_eta_electron->Fill(Electron_eta[j]);
                    h_phi_electron->Fill(Electron_phi[j]);
                }
            }
            for (int j = 0; j < nJet; j++) {
                if (Jet_pt[j] > ptCut && abs(Jet_eta[j]) < etaCut) {
                    h_pt_jet->Fill(Jet_pt[j]);
                    h_eta_jet->Fill(Jet_eta[j]);
                    h_phi_jet->Fill(Jet_phi[j]);
                }
            }

            if (nMuon >= 2) { // Garante que há pelo menos dois muons no evento
                // Preenchendo os quadrivetores para os dois primeiros muons
                muon1.SetPtEtaPhiM(Muon_pt[0], Muon_eta[0], Muon_phi[0], 0.105); // Massa do muon ≈ 0.105 GeV
                muon2.SetPtEtaPhiM(Muon_pt[1], Muon_eta[1], Muon_phi[1], 0.105);

                // Calculando a massa invariante
                double invMass = (muon1 + muon2).M();

                // Preenchendo o histograma de massa invariante
                h_mass->Fill(invMass);
            }
    }
    // Criando e salvando gráficos de distribuição de pT, eta, phi
    TCanvas *c1 = new TCanvas("c1", "Distribuicao de pT", 800, 600);
    c1->Divide(2, 2);
    c1->cd(1); h_pt_tau->Draw();
    c1->cd(2); h_pt_muon->Draw();
    c1->cd(3); h_pt_electron->Draw();
    c1->cd(4); h_pt_jet->Draw();
    c1->SaveAs("pt_distribuicao.png");

    TCanvas *c2 = new TCanvas("c2", "Distribuicao de #eta", 800, 600);
    c2->Divide(2, 2);
    c2->cd(1); h_eta_tau->Draw();
    c2->cd(2); h_eta_muon->Draw();
    c2->cd(3); h_eta_electron->Draw();
    c2->cd(4); h_eta_jet->Draw();
    c2->SaveAs("eta_distribuicao.png");

    TCanvas *c3 = new TCanvas("c3", "Distribuicao de #phi", 800, 600);
    c3->Divide(2, 2);
    c3->cd(1); h_phi_tau->Draw();
    c3->cd(2); h_phi_muon->Draw();
    c3->cd(3); h_phi_electron->Draw();
    c3->cd(4); h_phi_jet->Draw();
    c3->SaveAs("phi_distribuicao.png");

    // Criando e salvando gráfico da massa invariante
    TCanvas *c4 = new TCanvas("c4", "M", 800, 600);
    h_mass->Draw();
    c4->SaveAs("massa_invariante.png");

    // Ajustando o modelo da massa invariante usando uma função gaussiana para o sinal e uma exponencial para o fundo
    TF1 *signal = new TF1("signal", "gaus(0)", 0, 200);  // Função Gaussiana para o sinal
    TF1 *background = new TF1("background", "expo(0)", 0, 200);  // Função Exponencial para o fundo

    // Ajustando a função (sinal + fundo)
    TF1 *fit = new TF1("fit", "gaus(0) + expo(3)", 0, 200);
    h_mass->Fit(fit, "R");

    // Exibindo os parâmetros do ajuste (massa do sinal e incertezas)
    double signalMass = fit->GetParameter(1);  // Média da Gaussiana
    double signalMassError = fit->GetParError(1);  // Erro da média da Gaussiana
    printf("Massa do sinal: %.2f ± %.2f GeV/c^2\n", signalMass, signalMassError);

    // Salvando a figura do ajuste
    c4->SaveAs("ajuste_massa_invariante.png");


}