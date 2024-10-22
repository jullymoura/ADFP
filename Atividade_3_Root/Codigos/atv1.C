//Importando bibliotecas
#include <iostream>
#include <vector>
#include <TCanvas.h>
#include <TF1.h>
#include <TLegend.h>
#include <TMath.h> 

void atv1() {
    
    //Definindo função de seno
    auto fseno = [](double *x, double *par) {
        double p0 = par[0];
        double p1 = par[1];
        return (x[0] == 0) ? p0 * p1 : p0 * sin(p1 * x[0]) / x[0]; 
    };

    // Definindo parâmetros
    std::vector<std::pair<double, double>> parameters = {
        {0.5, 1.5},
        {1.0, 2.0},
        {2.0, 4.0},
        {1.5, 6}
    };

    // Criando loop para cada par de p0 e p1
    for (const auto& param : parameters) {
        double p0 = param.first; 
        double p1 = param.second;

        // Criando  canvas para cada gráfico
        TCanvas *canvas = new TCanvas(Form("canvas_p0_%.1f_p1_%.1f", p0, p1), "Função Parametrica", 800, 600);
        TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9); 

        // Criando a função
        TF1 *func = new TF1("func", fseno, 0, 5, 2); 

        //Configurando parâmetros
        func->SetParameters(p0, p1); 

        // Desenhando a função no canvas
        func->SetLineColor(kBlue);
        func->Draw(); 

        // Cálculando os valores
        std::cout << "p0 = " << p0 << ", p1 = " << p1 << ":\n";
        std::cout << "Valor em x=1: " << func->Eval(1.0) << "\n"; // Valor da função
        std::cout << "Derivada em x=1: " << func->Derivative(1.0) << "\n"; // Derivada
        std::cout << "Integral de 0 a 3: " << func->Integral(0, 3) << "\n"; // Integral

        // Adicionando legenda
        legend->AddEntry(func, Form("p0 = %.1f, p1 = %.1f", p0, p1), "l");
        legend->Draw(); 

        // Salvando a imagem gerada
        canvas->SaveAs(Form("Plot_p0_%.1f_p1_%.1f.png", p0, p1)); 

    }
}

