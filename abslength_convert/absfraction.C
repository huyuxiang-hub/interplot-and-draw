double linear_interpolation(TString data_file,double x){
  
       ifstream infile(data_file);
       double x1;
       double x2;
       double y1;
       double y2; 
       double y;
      
       bool ok=0;  

       infile>>x1;
       if( x1 > x )
       {
          std::cout<<"Error: input data is smaller than the first data of the file!!"<<std::endl;
          return 0;
       }       
       
       infile>>y1;
       while(1){
           
          infile>>x2;
          if(infile.eof())
                { 
                  std::cout<<"Error: the input data is bigger than the last data of the file!!"<<std::endl;
                  break;}   
          infile>>y2;
          if(x2 >= x)
            {
               y=(y2-y1)/(x2-x1)*(x-x1)+y1;
               return y;
            }
          x1=x2;
          y1=y2;
        }
      

}


void absfraction(){
 
  TString LAB_file="./lab_absL_final_junoLS.txt";
  TString PPO_file="./ppo_absL_final_junoLS.txt";
  TString bis_file="./bis_absL_final_junoLS.txt";
  
  double wave_length;
 
  double LAB_abslength;
  double PPO_abslength;
  double bis_abslength;
  
  double pdf[3];  

  std::vector<double> length(3);
  std::map<double, double> MAP;
  
  int width=20;  
  ofstream out("absfraction.txt");
  out<<left<<setw(width)<<"wave_length"<<left<<setw(width)<<"LAB"<<left<<setw(width)<<"PPO"<<left<<setw(width)<<"bis"<<std::endl;
  for(int i=0;i<=1200;i++)
    {
      wave_length=193+0.5*i;  
      LAB_abslength=linear_interpolation(LAB_file,wave_length);
      PPO_abslength=linear_interpolation(PPO_file,wave_length);
      bis_abslength=linear_interpolation(bis_file,wave_length);
     /* MAP[LAB_abslength]=0;
      MAP[PPO_abslength]=1;
      MAP[bis_abslength]=2;*/
      length[0]=LAB_abslength;
      length[1]=PPO_abslength;
      length[2]=bis_abslength;
   //  std::cout<<"length[0]="<<length[0]<<std::endl;
      
      sort(length.begin(),length.end());
   
     pdf[0]=1-length[0]/(2*length[2])-length[0]/(2*length[1])+length[0]*length[0]/(3*length[1]*length[2]);
     pdf[1]=length[0]/(2*length[1])*(1-length[0]/(3*length[2]));
     pdf[2]=length[0]/(2*length[2])*(1-length[0]/(3*length[1]));
     for(int k=0;k<3;k++)
      {
          MAP[length[k]]=pdf[k];
      }
    
     // std::cout<<"wave_length      LAB        PPO        bis "<<std::endl;
      out<<left<<setw(width)<<wave_length<<left<<setw(width)<<MAP[LAB_abslength]<<left<<setw(width)<<MAP[PPO_abslength]<<left<<setw(width)<<MAP[bis_abslength]<<std::endl;
       
    MAP.clear();
       
      
      
    }

  
 /* double abslen=0;
  abslen=linear_interpolation(LAB_file,380);

  std::cout<<"abslen="<<abslen<<std::endl;
*/
  


}



