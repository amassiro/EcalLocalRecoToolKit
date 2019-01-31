

void drawDifference () {
   
  TCanvas* cc_EB_ratio = new TCanvas ("cc_EB_ratio", "Ratio", 800, 600);
  TTree* tree = (TTree*) _file0->Get("TreeComparisonProducer/tree");
  tree->Draw("second_onlineEnergyEB/onlineEnergyEB >> h1(400,0.8,1.2)", "onlineEnergyEB>0", "goff");
  h1->SetLineColor(kBlack);
  float integral = 1.;
  integral = h1->Integral();  h1->Scale (1. / integral );
  
  h1->Draw();

  TCanvas* cc_EB_separate = new TCanvas ("cc_EB_separate", "cc_EB_separate", 800, 600);
  tree->Draw("onlineEnergyEB >> h2(200,0,200)", "onlineEnergyEB>0", "goff");
  h2->SetLineColor(kBlack);
  h2->Draw();
  tree->Draw("second_onlineEnergyEB >> h3(200,0,200)", "second_onlineEnergyEB>0", "goff");
  h3->SetLineColor(kRed);
  h3->SetLineStyle(2);
  h3->Draw("same");



  TCanvas* cc_EB_separate_different_ones = new TCanvas ("cc_EB_separate_different_ones", "cc_EB_separate_different_ones", 800, 600);
  tree->Draw("onlineEnergyEB >> h4(6000,0, 10)", "onlineEnergyEB>0 && second_onlineEnergyEB/onlineEnergyEB!=1", "goff");
  h4->SetLineColor(kBlack);
  h4->Draw();
  tree->Draw("second_onlineEnergyEB >> h5(6000,0, 10)", "second_onlineEnergyEB>0 && second_onlineEnergyEB/onlineEnergyEB!=1", "goff");
  h5->SetLineColor(kRed);
  h5->SetLineStyle(2);
  h5->Draw("same");
  
  
  
  
   
  
  
  TCanvas* cc_EE_ratio = new TCanvas ("cc_EE_ratio", "Ratio", 800, 600);
  TTree* tree = (TTree*) _file0->Get("TreeComparisonProducer/tree");
  tree->Draw("second_onlineEnergyEE/onlineEnergyEE >> h6(400,0.8,1.2)", "onlineEnergyEE>0", "goff");
  h6->SetLineColor(kBlack);
  float integral = 1.;
  integral = h6->Integral();  h6->Scale (1. / integral );
  
  h6->Draw();
  
  TCanvas* cc_EE_separate = new TCanvas ("cc_EE_separate", "cc_EE_separate", 800, 600);
  tree->Draw("onlineEnergyEE >> h7(200,0,200)", "onlineEnergyEE>0", "goff");
  h7->SetLineColor(kBlack);
  h7->Draw();
  tree->Draw("second_onlineEnergyEE >> h8(200,0,200)", "second_onlineEnergyEE>0", "goff");
  h8->SetLineColor(kRed);
  h8->SetLineStyle(2);
  h8->Draw("same");
  
  
  
  TCanvas* cc_EE_separate_different_ones = new TCanvas ("cc_EE_separate_different_ones", "cc_EE_separate_different_ones", 800, 600);
  tree->Draw("onlineEnergyEE >> h9(6000,0, 10)", "onlineEnergyEE>0 && second_onlineEnergyEE/onlineEnergyEE!=1", "goff");
  h9->SetLineColor(kBlack);
  h9->Draw();
  tree->Draw("second_onlineEnergyEE >> h10(6000,0, 10)", "second_onlineEnergyEE>0 && second_onlineEnergyEE/onlineEnergyEE!=1", "goff");
  h10->SetLineColor(kRed);
  h10->SetLineStyle(2);
  h10->Draw("same");
  
  
  
  
}




  
  