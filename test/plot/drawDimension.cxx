

void drawDimension () {
   
  TTree* tree = (TTree*) _file0->Get("TreeProducer/tree");
  tree->Draw("size_EB + size_EE >>h1(100,0,1000)");
  tree->Draw("size_EB >> h2(100,0,1000)", "", "same");
  tree->Draw("size_EE >> h3(100,0,1000)", "", "same");
  
  h1->SetLineColor(kBlack);
  h2->SetLineColor(kRed);
  h3->SetLineColor(kBlue);
 
  TTree* tree1 = (TTree*) _file1->Get("TreeProducer/tree");
  tree1->Draw("size_EB + size_EE >>h4(100,0,1000)");
  tree1->Draw("size_EB >> h5(100,0,1000)", "", "same");
  tree1->Draw("size_EE >> h6(100,0,1000)", "", "same");
  
  h4->SetLineColor(kBlack);
  h5->SetLineColor(kRed);
  h6->SetLineColor(kBlue);
  
  h4->SetLineStyle(3);
  h5->SetLineStyle(3);
  h6->SetLineStyle(3);
  
  
  
  TLegend* leg = new TLegend(0.5,0.7,0.9,0.9)
  leg->AddEntry(h1, "size EB+EE")
  leg->AddEntry(h2, "size EB")
  leg->AddEntry(h3, "size EE")
  leg->AddEntry(h4, "size EB+EE high PU")
  leg->AddEntry(h5, "size EB high PU")
  leg->AddEntry(h6, "size EE high PU")
  leg->Draw()
  
}


  
  