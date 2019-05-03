

void drawDifferenceOne (std::string name, int numbin, float min, float max, int applycut=1) {
   
  TTree* tree = (TTree*) _file0->Get("TreeComparisonProducer/tree");
  float integral = 1.;
  TString plot;
  TString cut = Form ("1");
//   TString cut = Form ("event<1520");   ---> still bad in EE
  //   cut = Form ("chi2EB==second_chi2EB");
  
  TH1F* h_EB = new TH1F("h_EB", "", 1000,-0.2,2.2);
  TCanvas* cc_ratio_EB = new TCanvas ("cc_ratio_EB", "Ratio EB", 800, 600);
  plot = Form ("second_%sEB/%sEB >> h_EB", name.c_str(), name.c_str());
  if (applycut ==1) cut = Form ("%sEB>0", name.c_str());  
  else if (applycut ==2) cut = Form ("%sEB!=-99", name.c_str());  
  tree->Draw(plot.Data(), cut.Data(), "goff");
  
  h_EB->SetLineColor(kBlack);
  integral = h_EB->Integral();  h_EB->Scale (1. / integral );
 
  h_EB->GetXaxis()->SetTitle((name + " ratio").c_str());
  h_EB->Draw();
  cc_ratio_EB->SetLogy();
  

//   cut = Form ("chi2EE==second_chi2EE");
  
  TCanvas* cc_ratio_EE = new TCanvas ("cc_ratio_EE", "Ratio EE", 800, 600);
  TH1F* h_EE = new TH1F("h_EE", "", 1000,-0.2,2.2);
  plot = Form ("second_%sEE/%sEE >> h_EE", name.c_str(), name.c_str());
  if (applycut ==1) cut = Form ("%sEE>0", name.c_str());  
  else if (applycut ==2)  cut = Form ("%sEE!=-99", name.c_str()); 
  tree->Draw(plot.Data(), cut.Data(), "goff");
  
  h_EE->SetLineColor(kBlack);
  integral = h_EE->Integral();  h_EE->Scale (1. / integral );
  
  h_EE->GetXaxis()->SetTitle((name + " ratio").c_str());
  h_EE->Draw();
  cc_ratio_EE->SetLogy();
  
  
  
  
  
  
  
  
  
  
//   cut = Form ("chi2EB==second_chi2EB");
  
  TCanvas* cc_2d_EB = new TCanvas ("cc_2d_EB", "2D EB", 800, 600);
  TH2F* h_EB_2D = new TH2F("h_EB_2D", "", numbin, min, max, numbin, min, max);
  plot = Form ("second_%sEB:%sEB >> h_EB_2D", name.c_str(), name.c_str());
  if (applycut ==1) cut = Form ("%sEB>0", name.c_str());  
  else if (applycut ==2) cut = Form ("%sEB!=-99", name.c_str());  
  tree->Draw(plot.Data(), cut.Data(), "goff");
    
  h_EB_2D->GetXaxis()->SetTitle("cpu");
  h_EB_2D->GetYaxis()->SetTitle("gpu");
  h_EB_2D->Draw("colz");
  
  
//   cut = Form ("chi2EE==second_chi2EE");
  
  TCanvas* cc_2d_EE = new TCanvas ("cc_2d_EE", "2D EE", 800, 600);
  TH2F* h_EE_2D = new TH2F("h_EE_2D", "", numbin, min, max, numbin, min, max);
  plot = Form ("second_%sEE:%sEE >> h_EE_2D", name.c_str(), name.c_str());
  if (applycut ==1) cut = Form ("%sEE>0", name.c_str());  
  else if (applycut ==2)  cut = Form ("%sEE!=-99", name.c_str()); 
  tree->Draw(plot.Data(), cut.Data(), "goff");
  
  h_EE_2D->GetXaxis()->SetTitle("cpu");
  h_EE_2D->GetYaxis()->SetTitle("gpu");
  h_EE_2D->Draw("colz");
  
  
  
  
  
  
//   cut = Form ("chi2EB==second_chi2EB");
  
  
  TCanvas* cc_single_EB = new TCanvas ("cc_single_EB", "EB", 800, 600);
  TH1F* h_EB_2 = new TH1F("h_EB_2", "",  numbin, min, max);
  plot = Form ("second_%sEB >> h_EB_2", name.c_str());
  if (applycut ==1) cut = Form ("second_%sEB>0", name.c_str());  
  else if (applycut ==2) cut = Form ("second_%sEB!=-99", name.c_str());  
  tree->Draw(plot.Data(), cut.Data(), "goff");
  h_EB_2->SetLineColor(kBlack);
  h_EB_2->GetXaxis()->SetTitle(name.c_str());
  h_EB_2->Draw();
  
  
  TH1F* h_EB_1 = new TH1F("h_EB_1", "",  numbin, min, max);
  plot = Form ("%sEB >> h_EB_1", name.c_str());
  if (applycut ==1) cut = Form ("%sEB>0", name.c_str());  
  else if (applycut ==2) cut = Form ("%sEB!=-99", name.c_str());  
  tree->Draw(plot.Data(), cut.Data(), "goff");
  h_EB_1->SetLineColor(kRed);
  h_EB_1->SetLineStyle(2);
  h_EB_1->GetXaxis()->SetTitle(name.c_str());
  h_EB_1->Draw("same");
  
  TLegend* leg = new TLegend ( 0.70, 0.70, 0.90, 0.90 );
  leg->AddEntry("h_EB_1","cpu","l");
  leg->AddEntry("h_EB_2","gpu","l");
  leg->Draw();

  cc_single_EB->SetLogy();


  
//   cut = Form ("chi2EE==second_chi2EE");
  
  TCanvas* cc_single_EE = new TCanvas ("cc_single_EE", "EE", 800, 600);
  TH1F* h_EE_2 = new TH1F("h_EE_2", "",  numbin, min, max);
  plot = Form ("second_%sEE >> h_EE_2", name.c_str());
  if (applycut ==1) cut = Form ("second_%sEE>0", name.c_str());  
  else if (applycut ==2)  cut = Form ("second_%sEE!=-99", name.c_str());  
  tree->Draw(plot.Data(), cut.Data(), "goff");
  h_EE_2->SetLineColor(kBlack);
  h_EE_2->GetXaxis()->SetTitle(name.c_str());
  h_EE_2->Draw();
  
  TH1F* h_EE_1 = new TH1F("h_EE_1", "",  numbin, min, max);
  plot = Form ("%sEE >> h_EE_1", name.c_str());
  if (applycut ==1) cut = Form ("%sEE>0", name.c_str());  
  else if (applycut ==2) cut = Form ("%sEE!=-99", name.c_str());  
  tree->Draw(plot.Data(), cut.Data(), "goff");
  h_EE_1->SetLineColor(kRed);
  h_EE_1->SetLineStyle(2);
  h_EE_1->GetXaxis()->SetTitle(name.c_str());
  h_EE_1->Draw("same");
  
  leg->Draw();
  
  cc_single_EE->SetLogy();
  
  
}




  
  