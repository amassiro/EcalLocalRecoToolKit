

void drawTime (std::string nameFile) {

  TH1F* h_time = new TH1F("h_time", "", 50,0,50);
  
  std::ifstream file (nameFile); 
  std::string buffer;
  float value;
  std::string temp_name;
  
  if(!file.is_open()) {
    std::cerr << "** ERROR: Can't open '" << nameFile << "' for input" << std::endl;
    return false;
  }
  
  while(!file.eof()) {
    getline(file,buffer);
    if (buffer != "" && buffer.at(0) != '#'){ ///---> save from empty line at the end!
      std::stringstream line( buffer );  
      
      line >> temp_name; // std::cout << " temp_name = " << temp_name << std::endl;  // skip
      line >> temp_name; // std::cout << " temp_name = " << temp_name << std::endl; // skip
      line >> temp_name; // std::cout << " temp_name = " << temp_name << std::endl; // skip
      line >> temp_name; // std::cout << " temp_name = " << temp_name << std::endl; // skip
      line >> temp_name; // std::cout << " temp_name = " << temp_name << std::endl; // skip

      line >> value;
      // std::cout << " value = " << value << std::endl;
      
      h_time -> Fill (value * 1000000);
      
    } 
  }


  h_time -> Draw();
  h_time -> SetLineColor(kBlue);
  h_time -> SetLineWidth(2);
  h_time -> GetXaxis () -> SetTitle ("time (#mus)");
  
  
}


