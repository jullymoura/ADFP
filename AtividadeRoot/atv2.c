#include"RooRealVar.h"
#include "RooPlot.h"
#include "RooFit.h"
#include "RooExponential.h"
#include "RooRandom.h"
#include "RooDataSet.h"
#include "TCanvas.h"
#include "RooArgSet.h"


void gerandoeventoscrystallball() {
    RooRealVar x("x","x",-10,10);
    RooRealVar media("media","media", 0, -5,5);
    RooRealVar sigma("sigma","sigma", 1, 0.1, 5);  
    RooRealVar alfa("alfa","alfa",1, 0.1, 5);      
    RooRealVar n("n", "n", 1, 0, 10); 

    RooCrystallBall crystallball("crystallball","CrystallBall",x, media,sigma, alfa,n);

    RooDataSet* dados = crystallball.generate(RooArgSet(x), 1000);  

    crystallball.fitTo(*dados); 
    RooPlot* frame = x.frame();
    dados->plotOn(frame);

    crystallball.plotOn(frame);
    TCanvas* g1 = new TCanvas("g1","Eventos gerados com CrystallBall","800","600");

    frame->Draw();

    g1->Draw();
    g1->SaveAs("CrystallballEventos.png");
 
}