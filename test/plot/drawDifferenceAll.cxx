

void drawDifferenceAll () {
   
  TTree* tree = (TTree*) _file0->Get("TreeComparisonProducer/tree");
  float integral = 1.;
  
  TCanvas* cc_ratio_onlineEnergyEB = new TCanvas ("cc_ratio_onlineEnergyEB", "Ratio EB", 800, 600);
  tree->Draw("second_onlineEnergyEB/onlineEnergyEB >> h_onlineEnergyEB(400,0.8,1.2)", "onlineEnergyEB>0", "goff");
  h_onlineEnergyEB->SetLineColor(kBlack);
  integral = h_onlineEnergyEB->Integral();  h_onlineEnergyEB->Scale (1. / integral );
  
  h_onlineEnergyEB->Draw();
  cc_ratio_onlineEnergyEB->SetLogy();
  
  TCanvas* cc_ratio_onlineEnergyEE = new TCanvas ("cc_ratio_onlineEnergyEE", "Ratio EE", 800, 600);
  tree->Draw("second_onlineEnergyEE/onlineEnergyEE >> h_onlineEnergyEE(400,0.8,1.2)", "onlineEnergyEE>0", "goff");
  h_onlineEnergyEE->SetLineColor(kBlack);
  integral = h_onlineEnergyEE->Integral();  h_onlineEnergyEE->Scale (1. / integral );
  h_onlineEnergyEE->Draw();  
  cc_ratio_onlineEnergyEE->SetLogy();
 
//   float _onlineEnergyEB[61200];
//   float _chi2EB[61200];
//   float _jitterEB[61200];
//   float _amplitudeErrorEB[61200];
//   float _outOfTimeAmplitudeM1EB[61200];
//   float _outOfTimeAmplitudeM2EB[61200];
//   float _outOfTimeAmplitudeM3EB[61200];
//   float _outOfTimeAmplitudeM4EB[61200];
//   float _outOfTimeAmplitudeM5EB[61200];
//   float _outOfTimeAmplitudeP1EB[61200];
//   float _outOfTimeAmplitudeP2EB[61200];
//   float _outOfTimeAmplitudeP3EB[61200];
//   float _outOfTimeAmplitudeP4EB[61200];
  
  
  
  
  
  TCanvas* cc_ratio_allEB = new TCanvas ("cc_ratio_allEB", "EB", 800, 600);
  cc_ratio_allEB->Divide(4,4);
  
  cc_ratio_allEB->cd(1);
  tree->Draw("second_onlineEnergyEB/onlineEnergyEB >> h_onlineEnergyEB(400,0.8,1.2)", "onlineEnergyEB>0", "goff");
  h_onlineEnergyEB->SetLineColor(kBlack);
  integral = h_onlineEnergyEB->Integral();  h_onlineEnergyEB->Scale (1. / integral ); 
  h_onlineEnergyEB->Draw();
  gPad->SetLogy();

  cc_ratio_allEB->cd(2);
  tree->Draw("second_chi2EB/chi2EB >> h_chi2EB(400,0.8,1.2)", "chi2EB>0", "goff");
  h_chi2EB->SetLineColor(kBlack);
  integral = h_chi2EB->Integral();  h_chi2EB->Scale (1. / integral ); 
  h_chi2EB->Draw();
  gPad->SetLogy();
  
  cc_ratio_allEB->cd(3);
  tree->Draw("second_jitterEB/jitterEB >> h_jitterEB(400,0.8,1.2)", "jitterEB>0", "goff");
  h_jitterEB->SetLineColor(kBlack);
  integral = h_jitterEB->Integral();  h_jitterEB->Scale (1. / integral ); 
  h_jitterEB->Draw();
  gPad->SetLogy();
  
  cc_ratio_allEB->cd(4);
  tree->Draw("second_amplitudeErrorEB/amplitudeErrorEB >> h_amplitudeErrorEB(400,0.8,1.2)", "amplitudeErrorEB>0", "goff");
  h_amplitudeErrorEB->SetLineColor(kBlack);
  integral = h_amplitudeErrorEB->Integral();  h_amplitudeErrorEB->Scale (1. / integral ); 
  h_amplitudeErrorEB->Draw();
  gPad->SetLogy();
  
  cc_ratio_allEB->cd(5);
  tree->Draw("second_outOfTimeAmplitudeM1EB/outOfTimeAmplitudeM1EB >> h_outOfTimeAmplitudeM1EB(400,0.8,1.2)", "outOfTimeAmplitudeM1EB>0", "goff");
  h_outOfTimeAmplitudeM1EB->SetLineColor(kBlack);
  integral = h_outOfTimeAmplitudeM1EB->Integral();  h_outOfTimeAmplitudeM1EB->Scale (1. / integral ); 
  h_outOfTimeAmplitudeM1EB->Draw();
  gPad->SetLogy();
 
  cc_ratio_allEB->cd(6);
  tree->Draw("second_outOfTimeAmplitudeM2EB/outOfTimeAmplitudeM2EB >> h_outOfTimeAmplitudeM2EB(400,0.8,1.2)", "outOfTimeAmplitudeM2EB>0", "goff");
  h_outOfTimeAmplitudeM2EB->SetLineColor(kBlack);
  integral = h_outOfTimeAmplitudeM2EB->Integral();  h_outOfTimeAmplitudeM2EB->Scale (1. / integral ); 
  h_outOfTimeAmplitudeM2EB->Draw();
  gPad->SetLogy();
  
  cc_ratio_allEB->cd(7);
  tree->Draw("second_outOfTimeAmplitudeM3EB/outOfTimeAmplitudeM3EB >> h_outOfTimeAmplitudeM3EB(400,0.8,1.2)", "outOfTimeAmplitudeM3EB>0", "goff");
  h_outOfTimeAmplitudeM3EB->SetLineColor(kBlack);
  integral = h_outOfTimeAmplitudeM3EB->Integral();  h_outOfTimeAmplitudeM3EB->Scale (1. / integral ); 
  h_outOfTimeAmplitudeM3EB->Draw();
  gPad->SetLogy();
  
  cc_ratio_allEB->cd(8);
  tree->Draw("second_outOfTimeAmplitudeM4EB/outOfTimeAmplitudeM4EB >> h_outOfTimeAmplitudeM4EB(400,0.8,1.2)", "outOfTimeAmplitudeM4EB>0", "goff");
  h_outOfTimeAmplitudeM4EB->SetLineColor(kBlack);
  integral = h_outOfTimeAmplitudeM4EB->Integral();  h_outOfTimeAmplitudeM4EB->Scale (1. / integral ); 
  h_outOfTimeAmplitudeM4EB->Draw();
  gPad->SetLogy();
  
  cc_ratio_allEB->cd(9);
  tree->Draw("second_outOfTimeAmplitudeP1EB/outOfTimeAmplitudeP1EB >> h_outOfTimeAmplitudeP1EB(400,0.8,1.2)", "outOfTimeAmplitudeP1EB>0", "goff");
  h_outOfTimeAmplitudeP1EB->SetLineColor(kBlack);
  integral = h_outOfTimeAmplitudeP1EB->Integral();  h_outOfTimeAmplitudeP1EB->Scale (1. / integral ); 
  h_outOfTimeAmplitudeP1EB->Draw();
  gPad->SetLogy();
  
  cc_ratio_allEB->cd(10);
  tree->Draw("second_outOfTimeAmplitudeP2EB/outOfTimeAmplitudeP2EB >> h_outOfTimeAmplitudeP2EB(400,0.8,1.2)", "outOfTimeAmplitudeP2EB>0", "goff");
  h_outOfTimeAmplitudeP2EB->SetLineColor(kBlack);
  integral = h_outOfTimeAmplitudeP2EB->Integral();  h_outOfTimeAmplitudeP2EB->Scale (1. / integral ); 
  h_outOfTimeAmplitudeP2EB->Draw();
  gPad->SetLogy();
  
  cc_ratio_allEB->cd(11);
  tree->Draw("second_outOfTimeAmplitudeP3EB/outOfTimeAmplitudeP3EB >> h_outOfTimeAmplitudeP3EB(400,0.8,1.2)", "outOfTimeAmplitudeP3EB>0", "goff");
  h_outOfTimeAmplitudeP3EB->SetLineColor(kBlack);
  integral = h_outOfTimeAmplitudeP3EB->Integral();  h_outOfTimeAmplitudeP3EB->Scale (1. / integral ); 
  h_outOfTimeAmplitudeP3EB->Draw();
  gPad->SetLogy();
  
  cc_ratio_allEB->cd(12);
  tree->Draw("second_outOfTimeAmplitudeP4EB/outOfTimeAmplitudeP4EB >> h_outOfTimeAmplitudeP4EB(400,0.8,1.2)", "outOfTimeAmplitudeP4EB>0", "goff");
  h_outOfTimeAmplitudeP4EB->SetLineColor(kBlack);
  integral = h_outOfTimeAmplitudeP4EB->Integral();  h_outOfTimeAmplitudeP4EB->Scale (1. / integral ); 
  h_outOfTimeAmplitudeP4EB->Draw();
  gPad->SetLogy();
  
  cc_ratio_allEB->cd(13);
  tree->Draw("second_outOfTimeAmplitudeM5EB/outOfTimeAmplitudeM5EB >> h_outOfTimeAmplitudeM5EB(400,0.8,1.2)", "outOfTimeAmplitudeM5EB>0", "goff");
  h_outOfTimeAmplitudeM5EB->SetLineColor(kBlack);
  integral = h_outOfTimeAmplitudeM5EB->Integral();  h_outOfTimeAmplitudeM5EB->Scale (1. / integral ); 
  h_outOfTimeAmplitudeM5EB->Draw();
  gPad->SetLogy();
  
  
  
  
  
  
  
  
  
  
  
  TCanvas* cc_ratio_allEE = new TCanvas ("cc_ratio_allEE", "EE", 800, 600);
  cc_ratio_allEE->Divide(4,4);
  
  cc_ratio_allEE->cd(1);
  tree->Draw("second_onlineEnergyEE/onlineEnergyEE >> h_onlineEnergyEE(400,0.8,1.2)", "onlineEnergyEE>0", "goff");
  h_onlineEnergyEE->SetLineColor(kBlack);
  integral = h_onlineEnergyEE->Integral();  h_onlineEnergyEE->Scale (1. / integral ); 
  h_onlineEnergyEE->Draw();
  gPad->SetLogy();
  
  cc_ratio_allEE->cd(2);
  tree->Draw("second_chi2EE/chi2EE >> h_chi2EE(400,0.8,1.2)", "chi2EE>0", "goff");
  h_chi2EE->SetLineColor(kBlack);
  integral = h_chi2EE->Integral();  h_chi2EE->Scale (1. / integral ); 
  h_chi2EE->Draw();
  gPad->SetLogy();
  
  cc_ratio_allEE->cd(3);
  tree->Draw("second_jitterEE/jitterEE >> h_jitterEE(400,0.8,1.2)", "jitterEE>0", "goff");
  h_jitterEE->SetLineColor(kBlack);
  integral = h_jitterEE->Integral();  h_jitterEE->Scale (1. / integral ); 
  h_jitterEE->Draw();
  gPad->SetLogy();
  
  cc_ratio_allEE->cd(4);
  tree->Draw("second_amplitudeErrorEE/amplitudeErrorEE >> h_amplitudeErrorEE(400,0.8,1.2)", "amplitudeErrorEE>0", "goff");
  h_amplitudeErrorEE->SetLineColor(kBlack);
  integral = h_amplitudeErrorEE->Integral();  h_amplitudeErrorEE->Scale (1. / integral ); 
  h_amplitudeErrorEE->Draw();
  gPad->SetLogy();
  
  cc_ratio_allEE->cd(5);
  tree->Draw("second_outOfTimeAmplitudeM1EE/outOfTimeAmplitudeM1EE >> h_outOfTimeAmplitudeM1EE(400,0.8,1.2)", "outOfTimeAmplitudeM1EE>0", "goff");
  h_outOfTimeAmplitudeM1EE->SetLineColor(kBlack);
  integral = h_outOfTimeAmplitudeM1EE->Integral();  h_outOfTimeAmplitudeM1EE->Scale (1. / integral ); 
  h_outOfTimeAmplitudeM1EE->Draw();
  gPad->SetLogy();
  
  cc_ratio_allEE->cd(6);
  tree->Draw("second_outOfTimeAmplitudeM2EE/outOfTimeAmplitudeM2EE >> h_outOfTimeAmplitudeM2EE(400,0.8,1.2)", "outOfTimeAmplitudeM2EE>0", "goff");
  h_outOfTimeAmplitudeM2EE->SetLineColor(kBlack);
  integral = h_outOfTimeAmplitudeM2EE->Integral();  h_outOfTimeAmplitudeM2EE->Scale (1. / integral ); 
  h_outOfTimeAmplitudeM2EE->Draw();
  gPad->SetLogy();
  
  cc_ratio_allEE->cd(7);
  tree->Draw("second_outOfTimeAmplitudeM3EE/outOfTimeAmplitudeM3EE >> h_outOfTimeAmplitudeM3EE(400,0.8,1.2)", "outOfTimeAmplitudeM3EE>0", "goff");
  h_outOfTimeAmplitudeM3EE->SetLineColor(kBlack);
  integral = h_outOfTimeAmplitudeM3EE->Integral();  h_outOfTimeAmplitudeM3EE->Scale (1. / integral ); 
  h_outOfTimeAmplitudeM3EE->Draw();
  gPad->SetLogy();
  
  cc_ratio_allEE->cd(8);
  tree->Draw("second_outOfTimeAmplitudeM4EE/outOfTimeAmplitudeM4EE >> h_outOfTimeAmplitudeM4EE(400,0.8,1.2)", "outOfTimeAmplitudeM4EE>0", "goff");
  h_outOfTimeAmplitudeM4EE->SetLineColor(kBlack);
  integral = h_outOfTimeAmplitudeM4EE->Integral();  h_outOfTimeAmplitudeM4EE->Scale (1. / integral ); 
  h_outOfTimeAmplitudeM4EE->Draw();
  gPad->SetLogy();
  
  cc_ratio_allEE->cd(9);
  tree->Draw("second_outOfTimeAmplitudeP1EE/outOfTimeAmplitudeP1EE >> h_outOfTimeAmplitudeP1EE(400,0.8,1.2)", "outOfTimeAmplitudeP1EE>0", "goff");
  h_outOfTimeAmplitudeP1EE->SetLineColor(kBlack);
  integral = h_outOfTimeAmplitudeP1EE->Integral();  h_outOfTimeAmplitudeP1EE->Scale (1. / integral ); 
  h_outOfTimeAmplitudeP1EE->Draw();
  gPad->SetLogy();
  
  cc_ratio_allEE->cd(10);
  tree->Draw("second_outOfTimeAmplitudeP2EE/outOfTimeAmplitudeP2EE >> h_outOfTimeAmplitudeP2EE(400,0.8,1.2)", "outOfTimeAmplitudeP2EE>0", "goff");
  h_outOfTimeAmplitudeP2EE->SetLineColor(kBlack);
  integral = h_outOfTimeAmplitudeP2EE->Integral();  h_outOfTimeAmplitudeP2EE->Scale (1. / integral ); 
  h_outOfTimeAmplitudeP2EE->Draw();
  gPad->SetLogy();
  
  cc_ratio_allEE->cd(11);
  tree->Draw("second_outOfTimeAmplitudeP3EE/outOfTimeAmplitudeP3EE >> h_outOfTimeAmplitudeP3EE(400,0.8,1.2)", "outOfTimeAmplitudeP3EE>0", "goff");
  h_outOfTimeAmplitudeP3EE->SetLineColor(kBlack);
  integral = h_outOfTimeAmplitudeP3EE->Integral();  h_outOfTimeAmplitudeP3EE->Scale (1. / integral ); 
  h_outOfTimeAmplitudeP3EE->Draw();
  gPad->SetLogy();
  
  cc_ratio_allEE->cd(12);
  tree->Draw("second_outOfTimeAmplitudeP4EE/outOfTimeAmplitudeP4EE >> h_outOfTimeAmplitudeP4EE(400,0.8,1.2)", "outOfTimeAmplitudeP4EE>0", "goff");
  h_outOfTimeAmplitudeP4EE->SetLineColor(kBlack);
  integral = h_outOfTimeAmplitudeP4EE->Integral();  h_outOfTimeAmplitudeP4EE->Scale (1. / integral ); 
  h_outOfTimeAmplitudeP4EE->Draw();
  gPad->SetLogy();
  
  cc_ratio_allEE->cd(13);
  tree->Draw("second_outOfTimeAmplitudeM5EE/outOfTimeAmplitudeM5EE >> h_outOfTimeAmplitudeM5EE(400,0.8,1.2)", "outOfTimeAmplitudeM5EE>0", "goff");
  h_outOfTimeAmplitudeM5EE->SetLineColor(kBlack);
  integral = h_outOfTimeAmplitudeM5EE->Integral();  h_outOfTimeAmplitudeM5EE->Scale (1. / integral ); 
  h_outOfTimeAmplitudeM5EE->Draw();
  gPad->SetLogy();
  
  
  
}




  
  