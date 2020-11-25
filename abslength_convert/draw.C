
int Count_columns(TString file_name){
    TString command1="head -n1 ";
    TString command2=file_name;
    TString command3="| awk  -F  ' '  '{print NF}' >& log.txt ";
    TString command="";
    command=command1+command2+command3;
    system(command);
     
    ifstream infile("log.txt");
    int n;
    infile>>n;
    return n;   
    
  
}

void  draw(){
    
    int num;

    
     
   // TString file_name="lab_absL_final_junoLS.txt";
    TString file_name="absfraction.txt";
    num=Count_columns(file_name);

    TString  title[num];
    std::vector<TGraph*> g_phy(num);
    TMultiGraph* mg_phys = new TMultiGraph();
  
    ifstream infile(file_name);
    for(int i=0;i<num;i++)
      {
         infile>>title[i];
         g_phy[i]=new TGraph;
         g_phy[i]->SetTitle(title[i]);
      
      }
   for(int i=1;i<num;i++)
     {
       g_phy[i]->SetLineColor(i);
       g_phy[i]->SetMarkerColor(i);
       mg_phys->Add(g_phy[i]);
     }
    
   double tmp[num];
   double point=0;
     while(1)
       {
          infile>>tmp[0];
          if(infile.eof())
                {break;}
     
          for(int k=1;k<num;k++)
             { 
                  infile>>tmp[k];
                  g_phy[k]->SetPoint(point,tmp[0],tmp[k]);
             }
           point++;

  
       }

       

      
       TCanvas* c = 0;
       c = new TCanvas;
       c->SetTitle("c1");


       mg_phys->Draw("ALP");
       c->BuildLegend();
    std::cout<<Count_columns(file_name)<<std::endl;
   /* head -n1 absfraction.txt | awk  -F  ' '  '{print NF}'
    TString command1="head -n1 ";
    TString command2=file_name;
    TString command3="| awk  -F  ' '  '{print NF}' >& log.txt ";
    TString command="";
    command=command1+command2+command3;
    system(command);*/
    


}
