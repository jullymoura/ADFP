//Importando biblioteca
#include <iostream>
#include <RooRealVar.h>
#include <RooPlot.h>
#include <RooFitResult.h>
#include <RooFit.h>
#include <RooRandom.h>
#include <RooDataSet.h>
#include <TCanvas.h>
#include <RooArgSet.h>
#include <RooCrystalBall.h>
#include <TPaveText.h>
#include <TLegend.h>
#include <stdio.h>
#include <stdlib.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TF1.h>
#include <TFile.h>
#include<RooAddPdf.h>
#include <TLatex.h>

//Criando função
void atv3(){
  
    //Abrindo arquivo
    TFile *file = TFile::Open("DataSet_lowstat.root");
    RooDataSet* data = (RooDataSet*)file->Get("data");

    //Definindo a variável de massa
    RooRealVar mass("mass", "Massa [GeV/c^2]", 2, 6); 

    //Numéro de eventos de sinal e de fundo esperados     
    RooRealVar nsig("nsig","Numero de eventos de sinal", 500,0,1000);
    RooRealVar nbkg("nbkg","Numero de eventos de fundo", 500,0,1000);

     //Definindo Pdf de sinal (CrystallBall)
    RooRealVar media("media", "media", 3.1, 2.9, 3.3);  
    RooRealVar sigma("sigma", "sigma", 0.4, 0.0001, 1.5);   
    RooRealVar alfa("alfa", "alfa",1.5, -5., 6);
    RooRealVar n("n", "n", 1.2, 0.1, 4);
    RooCrystalBall crystallball("crystallball", "Sinal", mass, media, sigma, alfa, n);

    //Definindo pdf de fundo (Polynomial)
    RooRealVar a1("a1", "a1", -0.5, -4., 4.);
    RooRealVar a2("a2", "a2", 0.5, -4., 4.);
    RooRealVar a3("a3", "a3", -0.5, -4., 4.);
    RooPolynomial pol("polynomial", "Fundo", mass, RooArgList(a1, a2, a3));

    //Definindo modelo estendido combinando sinal e fundo
    RooAddPdf model("modelo", "Sinal + Fundo",RooArgList(crystallball, pol), RooArgList(nsig,nbkg));

    //Ajustando os dados com o modelo
    RooFitResult* result = model.fitTo(*data, RooFit::Save(), RooFit::Extended());

    //Criando um Canvas    
    TCanvas *canvas = new TCanvas("canvas","canvas",1200,600);
    
    //Criando um frame   
    RooPlot* frame = mass.frame();

    //Plotando os dados e o modelo no frame 
    data->plotOn(frame);
    model.plotOn(frame);

    //Adicionando os parâmetros do modelo ajustado ao gráfico
    model.paramOn(frame);

    //Desenhando o frame
    frame->Draw();
    
    //Criando X²/ndf
    double chi2 = frame->chiSquare();
    int ndf = data->numEntries() - result->floatParsFinal().getSize();
    double chi2_ndf = chi2 / ndf;
    std::cout << "chi²/ndf: " << chi2_ndf << std::endl;

    //Adicionando X²/ndf ao gráfico
    TLatex *latex = new TLatex();
    
    latex->SetNDC(); 
    latex->SetTextSize(0.03);
    latex->DrawLatex(0.175, 0.70, Form("X^2/ndf: %.7f", chi2_ndf));
    
    //Salvando a imagem gerada
    canvas->SaveAs("jpsi.png");
 
    }
int main() {
    // Executando a função
    atv3();
    return 0;
}
 