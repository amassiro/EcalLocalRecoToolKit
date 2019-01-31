

void drawDifference () {
   
  TCanvas* cc_ratio = new TCanvas ("cc_ratio", "Ratio", 800, 600);
  TTree* tree = (TTree*) _file0->Get("TreeComparisonProducer/tree");
  tree->Draw("second_onlineEnergyEB/onlineEnergyEB >> h1(100,0,2)", "onlineEnergyEB>0", "goff");
  h1->SetLineColor(kBlack);
  float integral = 1.;
  integral = h1->Integral();  h1->Scale (1. / integral );
  
  h1->Draw();

  TCanvas* cc_separate = new TCanvas ("cc_separate", "cc_separate", 800, 600);
  tree->Draw("onlineEnergyEB >> h2(200,0,200)", "onlineEnergyEB>0", "goff");
  h2->SetLineColor(kBlack);
  h2->Draw();
  tree->Draw("second_onlineEnergyEB >> h3(200,0,200)", "second_onlineEnergyEB>0", "goff");
  h3->SetLineColor(kRed);
  h3->SetLineStyle(2);
  h3->Draw("same");
  
  
}




  
  