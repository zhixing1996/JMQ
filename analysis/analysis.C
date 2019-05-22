void analysis()
{

    TString rootposition, epsname[1];
    rootposition  = "../build/JMQ.root";

    // epsname[0] = "electricfield_projection_x.png" ;

    TFile *f;
    TTree *t;

    // Int_t EventID;
    Double_t edep_head, edep_chest;
    Double_t head_center_x, head_center_y, head_center_z;
    Double_t chest_center_x, chest_center_y, chest_center_z;
    Double_t particle_momentum_x, particle_momentum_y, particle_momentum_z;

    f = new TFile(rootposition);
    t = (TTree *)f->Get("JMQ");

    // t->SetBranchAddress("EventID",   &EventID);
    t->SetBranchAddress("head_center_x",   &head_center_x);
    t->SetBranchAddress("head_center_y",   &head_center_y);
    t->SetBranchAddress("head_center_z",   &head_center_z);
    t->SetBranchAddress("chest_center_x",   &chest_center_x);
    t->SetBranchAddress("chest_center_y",   &chest_center_y);
    t->SetBranchAddress("chest_center_z",   &chest_center_z);
    t->SetBranchAddress("particle_momentum_x",   &particle_momentum_x);
    t->SetBranchAddress("particle_momentum_y",   &particle_momentum_y);
    t->SetBranchAddress("particle_momentum_z",   &particle_momentum_z);
    t->SetBranchAddress("edep_head",   &edep_head);
    t->SetBranchAddress("edep_chest",   &edep_chest);

    auto c = new TCanvas("c","c",1200,1080);
    auto h1 = new TH1F("h1","head_center_x",1500,-200,1000);
    auto h2 = new TH1F("h2","head_center_y",200,340,540);
    auto h3 = new TH1F("h3","head_center_z",200,-80,80);
    auto h4 = new TH1F("h4","chest_center_x",600,-200,400);
    auto h5 = new TH1F("h5","chest_center_y",1000,-400,500);
    auto h6 = new TH1F("h6","chest_center_z",1200,-500,600);
    auto h7 = new TH1F("h7","particle_momentum_x",1000,-1,1);
    auto h8 = new TH1F("h8","particle_momentum_y",1000,-1,1);
    auto h9 = new TH1F("h9","particle_momentum_z",1000,-1,1);
    auto h10 = new TH1F("h10","edep_head",50,0,0.7);
    auto h11 = new TH1F("h11","edep_chest",50,0,0.7);

    for (Int_t i=0; i<t->GetEntries(); i++){
        t->GetEntry(i);
        h1->Fill(head_center_x);
        h2->Fill(head_center_y);
        h3->Fill(head_center_z);
        h4->Fill(chest_center_x);
        h5->Fill(chest_center_y);
        h6->Fill(chest_center_z);
        h7->Fill(particle_momentum_x);
        h8->Fill(particle_momentum_y);
        h9->Fill(particle_momentum_z);
        if (edep_head>0) {
           h10->Fill(edep_head);
        }
        if (edep_chest>0) {
           h11->Fill(edep_chest);
        }

    }
    
    gStyle->SetEndErrorSize(3);
    gStyle->SetErrorX(1.);

    c->Divide(3,4);

    c->cd(1);
    h1->Draw("E1");
    c->cd(2);
    h2->Draw("E1");
    c->cd(3);
    h3->Draw("E1");
    c->cd(4);
    h4->Draw("E1");
    c->cd(5);
    h5->Draw("E1");
    c->cd(6);
    h6->Draw("E1");
    c->cd(7);
    h7->Draw("E1");
    c->cd(8);
    h8->Draw("E1");
    c->cd(9);
    h9->Draw("E1");
    c->cd(10);
    h10->Draw("E1");
    c->cd(11);
    h11->Draw("E1");

}
