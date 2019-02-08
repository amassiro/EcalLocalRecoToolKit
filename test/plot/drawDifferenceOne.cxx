

void drawDifferenceOne (std::string name, int numbin, float min, float max, int applycut=1) {
   
  TTree* tree = (TTree*) _file0->Get("TreeComparisonProducer/tree");
  float integral = 1.;
  TString plot;
  TString cut = Form ("1");;
  
  TCanvas* cc_ratio_EB = new TCanvas ("cc_ratio_EB", "Ratio EB", 800, 600);
  plot = Form ("second_%sEB/%sEB >> h_EB(1000,-0.2,2.2)", name.c_str(), name.c_str());
  if (applycut ==1) cut = Form ("%sEB>0", name.c_str());  
  else if (applycut ==2) cut = Form ("%sEB!=-99", name.c_str());  
  tree->Draw(plot.Data(), cut.Data(), "goff");
  
  h_EB->SetLineColor(kBlack);
  integral = h_EB->Integral();  h_EB->Scale (1. / integral );
  
  h_EB->Draw();
  cc_ratio_EB->SetLogy();
  

  TCanvas* cc_ratio_EE = new TCanvas ("cc_ratio_EE", "Ratio EE", 800, 600);
  plot = Form ("second_%sEE/%sEE >> h_EE(1000,-0.2,2.2)", name.c_str(), name.c_str());
  if (applycut ==1) cut = Form ("%sEE>0", name.c_str());  
  else if (applycut ==2)  cut = Form ("%sEE!=-99", name.c_str()); 
  tree->Draw(plot.Data(), cut.Data(), "goff");
  
  h_EE->SetLineColor(kBlack);
  integral = h_EE->Integral();  h_EE->Scale (1. / integral );
  
  h_EE->Draw();
  cc_ratio_EE->SetLogy();
  
  
  
  
  
  TCanvas* cc_single_EB = new TCanvas ("cc_single_EB", "EB", 800, 600);
  plot = Form ("second_%sEB >> h_EB_2(%d,%f,%f)", name.c_str(), numbin, min, max);
  if (applycut ==1) cut = Form ("second_%sEB>0", name.c_str());  
  else if (applycut ==2) cut = Form ("second_%sEB!=-99", name.c_str());  
  tree->Draw(plot.Data(), cut.Data(), "goff");
  h_EB_2->SetLineColor(kBlack);
  h_EB_2->Draw();
  
  plot = Form ("%sEB >> h_EB_1(%d,%f,%f)", name.c_str(), numbin, min, max);
  if (applycut ==1) cut = Form ("%sEB>0", name.c_str());  
  else if (applycut ==2) cut = Form ("%sEB!=-99", name.c_str());  
  tree->Draw(plot.Data(), cut.Data(), "goff");
  h_EB_1->SetLineColor(kRed);
  h_EB_1->SetLineStyle(2);
  h_EB_1->Draw("same");
  
  cc_single_EB->SetLogy();


  
  
  TCanvas* cc_single_EE = new TCanvas ("cc_single_EE", "EE", 800, 600);
  plot = Form ("second_%sEE >> h_EE_2(%d,%f,%f)", name.c_str(), numbin, min, max);
  if (applycut ==1) cut = Form ("second_%sEE>0", name.c_str());  
  else if (applycut ==2)  cut = Form ("second_%sEE!=-99", name.c_str());  
  tree->Draw(plot.Data(), cut.Data(), "goff");
  h_EE_2->SetLineColor(kBlack);
  h_EE_2->Draw();
  
  plot = Form ("%sEE >> h_EE_1(%d,%f,%f)", name.c_str(), numbin, min, max);
  if (applycut ==1) cut = Form ("%sEE>0", name.c_str());  
  else if (applycut ==2) cut = Form ("%sEE!=-99", name.c_str());  
  tree->Draw(plot.Data(), cut.Data(), "goff");
  h_EE_1->SetLineColor(kRed);
  h_EE_1->SetLineStyle(2);
  h_EE_1->Draw("same");
  
  cc_single_EE->SetLogy();
  
  
}




  
  