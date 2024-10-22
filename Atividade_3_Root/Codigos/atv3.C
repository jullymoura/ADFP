#include <TH1F.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TStyle.h>
#include <TApplication.h>

void atv3() {    

    //Criando histograma
    TH1F *histograma = new TH1F("histograma", "Histograma Gaussiana", 50, 0, 10);
    
    //Criando objeto random
    TRandom *random = new TRandom();

    // Preenchendo 10.000 números aleatórios distribuídos com gaussiana de média 5 e sigma 2.
    for (int i = 0; i < 10000; i++) {
        double value = random->Gaus(5, 2); 
        histograma->Fill(value);
    }

    // Criando um canvas
    TCanvas *canvas = new TCanvas("canvas", "Gaussiana como numero aleatorios", 1000, 600);

    //Adicionando caixa de informações
    gStyle->SetOptStat("kseiorum");
    
    // Desenhando o histograma
    histograma->Draw();

    // Salvando a imagem gerada
    canvas->SaveAs("HistoGaussRandom.png");
}
