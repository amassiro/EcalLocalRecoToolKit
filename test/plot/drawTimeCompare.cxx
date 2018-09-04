

void drawTimeCompare (std::string nameFileOld, std::string nameFileNew) {

  TH1F* h_time_new = new TH1F("h_time_new", "New", 15,0,15);
  TH1F* h_time_old = new TH1F("h_time_old", "Old", 15,0,15);
  
  std::ifstream file_new (nameFileNew); 
  std::string buffer;
  float value;
  std::string temp_name;
  
  if(!file_new.is_open()) {
    std::cerr << "** ERROR: Can't open '" << nameFileNew << "' for input" << std::endl;
    return false;
  }
  
  while(!file_new.eof()) {
    getline(file_new,buffer);
    if (buffer != "" && buffer.at(0) != '#'){ ///---> save from empty line at the end!
      std::stringstream line( buffer );  
      
      line >> temp_name; // std::cout << " temp_name = " << temp_name << std::endl;  // skip
      line >> temp_name; // std::cout << " temp_name = " << temp_name << std::endl; // skip
      line >> temp_name; // std::cout << " temp_name = " << temp_name << std::endl; // skip
      line >> temp_name; // std::cout << " temp_name = " << temp_name << std::endl; // skip
      line >> temp_name; // std::cout << " temp_name = " << temp_name << std::endl; // skip

      line >> value;
      // std::cout << " value = " << value << std::endl;
      
      h_time_new -> Fill (value * 1000000);
      
    } 
  }

  
  
  
  
  
  std::ifstream file_old (nameFileOld); 
  
  if(!file_old.is_open()) {
    std::cerr << "** ERROR: Can't open '" << nameFileOld << "' for input" << std::endl;
    return false;
  }
  
  while(!file_old.eof()) {
    getline(file_old,buffer);
    if (buffer != "" && buffer.at(0) != '#'){ ///---> save from empty line at the end!
      std::stringstream line( buffer );  
      
      line >> temp_name; // std::cout << " temp_name = " << temp_name << std::endl;  // skip
      line >> temp_name; // std::cout << " temp_name = " << temp_name << std::endl; // skip
      line >> temp_name; // std::cout << " temp_name = " << temp_name << std::endl; // skip
      line >> temp_name; // std::cout << " temp_name = " << temp_name << std::endl; // skip
      line >> temp_name; // std::cout << " temp_name = " << temp_name << std::endl; // skip
      
      line >> value;
      // std::cout << " value = " << value << std::endl;
      
      h_time_old -> Fill (value * 1000000);
      
    } 
  }
  
  
  
  h_time_new -> Draw();
  h_time_new -> SetLineColor(kBlue);
  h_time_new -> SetLineWidth(2);
  h_time_new -> GetXaxis () -> SetTitle ("time (#mus)");
  
  h_time_old -> Draw("same");
  h_time_old -> SetLineColor(kRed);
  h_time_old -> SetLineWidth(2);
  
  gPad->BuildLegend();
  
}


