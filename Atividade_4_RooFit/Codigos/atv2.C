//Importando biblioteca
#include <RooRealVar.h>
#include <RooDataSet.h>
#include <RooExponential.h>
#include <RooFitResult.h>
#include <RooPlot.h>
#include <RooRandom.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <cstdio>  
#include <TPaveText.h>
#include <TLegend.h>

//Criando função
void atv2() {

    //Definindo x
    RooRealVar x("x", "x", 0, 10);

    //Definindo a taxa de decaimento
    RooRealVar lambda("lambda", "Taxa de decaimento", 1, 0.1, 2);

    //Definindo o numero de eventos
    RooRealVar Eventos("Eventos", "Número de Eventos", 1500, 100, 5000);
    
    // Definindo modelo de função exponencial decrescente
    RooExponential expDecay("expDecay", "Decaimento Exponencial", x, lambda);
    
    // Gerando eventos
    RooDataSet* dados = expDecay.generate(RooArgSet(x), 1500);
        
    // Ajustando os dados com o modelo
    RooFitResult* resultado = expDecay.fitTo(*dados, RooFit::Save(), RooFit::Extended(kTRUE));
    
    // Criando um frame 
    RooPlot* frame = x.frame();

    //Plorando os dados e o modelo no frame
    dados->plotOn(frame);               
    expDecay.plotOn(frame);           
       
    // Criando um canvas 
    TCanvas* canvas = new TCanvas("canvas", "Ajuste Exponencial", 800, 600);

    //Dezenhando o frame no canvas
    frame->Draw();
       
    //Adicionando os valores de lambda e de eventos ao gráfico
    TLatex *latex = new TLatex();
    
    latex->SetNDC(); 
    latex->SetTextSize(0.03);
    latex->DrawLatex(0.175, 0.70, Form("lambda: %.3f", lambda.getVal()));
    latex->DrawLatex(0.175, 0.66, Form("Eventos: %.0f", Eventos.getVal()));
      
    // Salvando a imagem gerada
    canvas->SaveAs("Exponencial.png");
}
    

int main() {
    //Executando a função
    atv2();  
    return 0;
}
