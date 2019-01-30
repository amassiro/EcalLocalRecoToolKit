

void drawDifference () {
   
  TTree* tree = (TTree*) _file0->Get("TreeComparisonProducer/tree");
  tree->Draw("second_onlineEnergyEB/onlineEnergyEB >> h1(100,0,2)", "onlineEnergyEB>-1");
  h1->SetLineColor(kBlack);
  float integral = 1.;
  integral = h1->Integral();  h1->Scale (1. / integral );
  
  h1->Draw();

  
}




  
  