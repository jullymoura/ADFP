void atv4() {
    
    // Abrindo o arquivo
    TFile *file = TFile::Open("tree.root");
    //Acessando a tree
    TTree *tree = (TTree*)file->Get("tree1");

    // Definindo as Variáveis
    float ebeam, px, py, pz;
    tree->SetBranchAddress("ebeam", &ebeam);
    tree->SetBranchAddress("px", &px);
    tree->SetBranchAddress("py", &py);
    tree->SetBranchAddress("pz", &pz);
    
    // Cálculando a média 
    double totalEnergy = 0;
    Long64_t nEntries = tree->GetEntries();

    for (Long64_t i = 0; i < nEntries; i++) {
        tree->GetEntry(i);
        totalEnergy += ebeam; // Soma a energia do feixe
    }

    // Vereficando se a média é maior que 0
    if (nEntries > 0) {
        double meanEnergy = totalEnergy / nEntries; // Média
        double lowerCut = meanEnergy - 0.2;
        double upperCut = meanEnergy + 0.2;

    // Criando os cortes
        TCut cut = Form("ebeam < %f || ebeam > %f", upperCut, lowerCut);

    // Criando o histograma
    TH1F *histograma = new TH1F("Momento_total", "Distribuicao de momento total", 200, 130, 160); 

    //Desenhando a tree no histograma
    tree->Draw("TMath::Sqrt(px*px + py*py + pz*pz)>>Momento_total", cut);

    // Criando um canvas
    TCanvas *canvas = new TCanvas("canvas", "Distribuicao de momento total", 800, 600);
    histograma->Draw();

   // Salvando arquivo gerado em PDF
    canvas->SaveAs("Momento_total.png");

    }

    file->Close();
}
