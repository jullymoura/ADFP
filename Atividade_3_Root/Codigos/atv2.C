#include <TGraph.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <iostream>

void atv2() {
    // Criando canvas
    TCanvas *canvas = new TCanvas("canvas", "Gráfico de erros", 800, 600);

    // Criando TGraph para os dados
    TGraph *graph = new TGraph("graphdata.txt");
    TGraphErrors *graphErrors = new TGraphErrors("graphdata_error.txt");

    // Configurando o plot
    graph->SetMarkerStyle(22); // Estilo do marcador de caixa preta
    graph->SetTitle("Grafico com Erros;X;Y");
    graph->Draw("ALP"); // Desenha os pontos do TGraph com linhas

    // Desenhando os erros no gráfico
    graphErrors->SetMarkerStyle(21);
    graphErrors->SetMarkerColor(kGreen);
    graphErrors->Draw("P"); 

    // Salvando a imagem gerada
    canvas->SaveAs("Gráfico.png");

}
