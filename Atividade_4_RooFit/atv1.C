//Importando bibliotecas
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

//Criando função
void atv1() {
    
    //Definindo x
    RooRealVar x("x", "x", -10, 10);
    
    //Definindo o modelo Crystall Ball
    RooRealVar media("media", "media", 0, -10, 10);
    RooRealVar sigma("sigma", "sigma", 1, 0.1, 10);
    RooRealVar alfa("alfa", "alfa", 1, 0.1, 10);
    RooRealVar n("n", "n", 1, 0, 15);
    RooCrystalBall crystalball("crystalball", "CrystalBall", x, media, sigma, alfa, n); 
    
    //Gerando dados 
    RooDataSet* dados = crystalball.generate(RooArgSet(x), 1000);

    //Ajustando os dados com o modelo 
    RooFitResult* resultado = crystalball.fitTo(*dados, RooFit::Save());

    //Criando um frame
    RooPlot* frame = x.frame();

    //Plotando os dados e o modelo no frame
    dados->plotOn(frame);
    crystalball.plotOn(frame);

    //Criando um canvas
    TCanvas* canvas = new TCanvas("canvas", "Eventos gerados com CrystallBall", 800, 600);

    //Desenhando o frame
    frame->Draw();

    //Adicionando informações no gráfico
    TLatex *latex = new TLatex(); 

    latex->SetNDC(); 
    latex->SetTextSize(0.03);
    
    latex->DrawLatex(0.175, 0.70, Form("Eventos: %d", (int)dados->numEntries()));    
    latex->DrawLatex(0.175, 0.66, Form("n: %.3f", n.getVal())); 
    latex->DrawLatex(0.175, 0.62, Form("Alfa: %.3f", alfa.getVal()));   
    latex->DrawLatex(0.175, 0.58, Form("Media: %.3f", media.getVal()));  
    latex->DrawLatex(0.175, 0.54, Form("Desvio Padrao: %.3f", sigma.getVal()));
    
    //Salvando a imagem gerada
    canvas->SaveAs("CrystalballEventos.png");
}

int main() {
    //Executando a função
    atv1();
    return 0;
}
