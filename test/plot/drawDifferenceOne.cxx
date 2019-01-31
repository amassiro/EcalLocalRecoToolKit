

void drawDifferenceOne (std::string name, int numbin, float min, float max) {
   
  TTree* tree = (TTree*) _file0->Get("TreeComparisonProducer/tree");
  float integral = 1.;
  TString plot;
  TString cut;
  
  TCanvas* cc_ratio_EB = new TCanvas ("cc_ratio_EB", "Ratio", 800, 600);
  plot = Form ("second_%sEB/%sEB >> h_EB(400,0.8,1.2)", name.c_str(), name.c_str());
  cut = Form ("%sEB>0", name.c_str());  
  tree->Draw(plot.Data(), cut.Data(), "goff");
  
  h_EB->SetLineColor(kBlack);
  integral = h_EB->Integral();  h_EB->Scale (1. / integral );
  
  h_EB->Draw();
  cc_ratio_EB->SetLogy();
  

  TCanvas* cc_ratio_EE = new TCanvas ("cc_ratio_EE", "Ratio", 800, 600);
  plot = Form ("second_%sEE/%sEE >> h_EE(400,0.8,1.2)", name.c_str(), name.c_str());
  cut = Form ("%sEE>0", name.c_str());  
  tree->Draw(plot.Data(), cut.Data(), "goff");
  
  h_EE->SetLineColor(kBlack);
  integral = h_EE->Integral();  h_EE->Scale (1. / integral );
  
  h_EE->Draw();
  cc_ratio_EE->SetLogy();
  
  
  
  
  
  TCanvas* cc_single_EB = new TCanvas ("cc_single_EB", "EB", 800, 600);
  plot = Form ("second_%sEB >> h_EB_2(%d,%f,%f)", name.c_str(), numbin, min, max);
  cut = Form ("second_%sEB>0", name.c_str());  
  tree->Draw(plot.Data(), cut.Data(), "goff");
  h_EB_2->SetLineColor(kBlack);
  h_EB_2->Draw();
  
  plot = Form ("%sEB >> h_EB_1(%d,%f,%f)", name.c_str(), numbin, min, max);
  cut = Form ("%sEB>0", name.c_str());  
  tree->Draw(plot.Data(), cut.Data(), "goff");
  h_EB_1->SetLineColor(kRed);
  h_EB_1->SetLineStyle(2);
  h_EB_1->Draw("same");
  
  cc_single_EB->SetLogy();


  
  
  TCanvas* cc_single_EE = new TCanvas ("cc_single_EE", "EE", 800, 600);
  plot = Form ("second_%sEE >> h_EE_2(%d,%f,%f)", name.c_str(), numbin, min, max);
  cut = Form ("second_%sEE>0", name.c_str());  
  tree->Draw(plot.Data(), cut.Data(), "goff");
  h_EE_2->SetLineColor(kBlack);
  h_EE_2->Draw();
  
  plot = Form ("%sEE >> h_EE_1(%d,%f,%f)", name.c_str(), numbin, min, max);
  cut = Form ("%sEE>0", name.c_str());  
  tree->Draw(plot.Data(), cut.Data(), "goff");
  h_EE_1->SetLineColor(kRed);
  h_EE_1->SetLineStyle(2);
  h_EE_1->Draw("same");
  
  cc_single_EE->SetLogy();
  
  
}




  
  