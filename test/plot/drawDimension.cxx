

void drawDimension () {
   
  TTree* tree = (TTree*) _file0->Get("TreeProducer/tree");
  tree->Draw("size_EB + size_EE >> h1(10000,0,20000)");
  tree->Draw("size_EB >> h2(10000,0,20000)");
  tree->Draw("size_EE >> h3(10000,0,20000)");
  
  h1->SetLineColor(kBlack);
  h2->SetLineColor(kRed);
  h3->SetLineColor(kBlue);
 
  std::cout << " h1->Integral() = " << h1->Integral() << std::endl;
  float integral = 1.;
  
  integral = h1->Integral();  h1->Scale (1. / integral );
  integral = h2->Integral();  h2->Scale (1. / integral );
  integral = h3->Integral();  h3->Scale (1. / integral );
  
  TTree* tree1 = (TTree*) _file1->Get("TreeProducer/tree");
  tree1->Draw("size_EB + size_EE >> h4(50,0,20000)");
  tree1->Draw("size_EB >> h5(50,0,20000)");
  tree1->Draw("size_EE >> h6(50,0,20000)");
  
  h4->SetLineColor(kBlack);
  h5->SetLineColor(kRed);
  h6->SetLineColor(kBlue);
  
  h4->SetLineStyle(3);
  h5->SetLineStyle(3);
  h6->SetLineStyle(3);
  
  integral = h4->Integral();  h4->Scale (100 * 50./10000. / integral );
  integral = h5->Integral();  h5->Scale (100 * 50./10000. / integral );
  integral = h6->Integral();  h6->Scale (100 * 50./10000. / integral );
  
  h1->Draw();
  h2->Draw("same");
  h3->Draw("same");
  h4->Draw("same");
  h5->Draw("same");
  h6->Draw("same");
  
  
  TLegend* leg = new TLegend(0.5,0.7,0.9,0.9);
  leg->AddEntry(h1, "size EB+EE");
  leg->AddEntry(h2, "size EB");
  leg->AddEntry(h3, "size EE");
  leg->AddEntry(h4, "size EB+EE high PU");
  leg->AddEntry(h5, "size EB high PU");
  leg->AddEntry(h6, "size EE high PU");
  leg->Draw();
  
}


  
  