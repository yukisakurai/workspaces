void TestPlot(){

  TString channel = "vbf_rhopi";
  TString tname;
  if      (channel.Index("pipi")!=-1)   {
    var = "Acoplanarity_IP";
    tname = "#tau_{had}^{#pm}#tau_{had}^{#mp} #rightarrow #pi^{#pm}#pi^{#mp}";
  }
  else if (channel.Index("rhorho")!=-1) {
    var = "Acoplanarity_rho_cluster";
    tname = "#tau_{had}^{#pm}#tau_{had}^{#mp} #rightarrow #rho^{#pm}#rho^{#mp}";
  }
  else if (channel.Index("pirho")!=-1)  {
    var = "Acoplanarity_tau1_IP_tau2_rho_cluster";
    tname = "#tau_{had}^{#pm}#tau_{had}^{#mp} #rightarrow #pi^{#pm}#rho^{#mp}";
  }
  else if (channel.Index("rhopi")!=-1)  {
    var = "Acoplanarity_tau2_IP_tau1_rho_cluster";
    tname = "#tau_{had}^{#pm}#tau_{had}^{#mp} #rightarrow #rho^{#pm}#pi^{#mp}";
  }
  if      (channel.Index("vbf")!=-1)     tname += "  VBF";
  else if (channel.Index("boosted")!=-1) tname += "  Boosted";



  TString filename = "hh_cp_" + channel + "/hh_cp_12_combination_125.root";
  TFile *f = TFile::Open(filename);
  TString chname = "channel_hh_12_" + channel + "_125_" + var + "_hists/";

  TH1F *Data = (TH1F*) f->Get(chname + "data/hh_category_" + channel + "_Data_125_" + var);

  TH1F *Fakes = (TH1F*) f->Get(chname + "Fakes/hh_category_" + channel + "_Fakes_125_" + var);
  TH1F *Others = (TH1F*) f->Get(chname + "Others/hh_category_" + channel + "_Others_125_" + var);
  TH1F *Ztautau = (TH1F*) f->Get(chname + "Ztautau/hh_category_" + channel + "_Ztautau_125_" + var);

  TH1F *Signal_Z_125 = (TH1F*) f->Get(chname + "Signal_Z_125/hh_category_" + channel + "_Signal_Z_125_" + var);
  TH1F *Signal_W_125 = (TH1F*) f->Get(chname + "Signal_W_125/hh_category_" + channel + "_Signal_W_125_" + var);
  TH1F *Signal_gg_125 = (TH1F*) f->Get(chname + "Signal_gg_125/hh_category_" + channel + "_Signal_gg_125_" + var);
  TH1F *Signal_VBF_125 = (TH1F*) f->Get(chname + "Signal_VBF_125/hh_category_" + channel + "_Signal_VBF_125_" + var);

  TH1F *Signal_Odd_Z_125 = (TH1F*) f->Get(chname + "Signal_Odd_Z_125/hh_category_" + channel + "_Signal_Odd_Z_125_" + var);
  TH1F *Signal_Odd_W_125 = (TH1F*) f->Get(chname + "Signal_Odd_W_125/hh_category_" + channel + "_Signal_Odd_W_125_" + var);
  TH1F *Signal_Odd_gg_125 = (TH1F*) f->Get(chname + "Signal_Odd_gg_125/hh_category_" + channel + "_Signal_Odd_gg_125_" + var);
  TH1F *Signal_Odd_VBF_125 = (TH1F*) f->Get(chname + "Signal_Odd_VBF_125/hh_category_" + channel + "_Signal_Odd_VBF_125_" + var);

  Data->SetLineColor(1);
  Data->SetMarkerColor(1);

  Fakes->SetFillColor(3);
  Others->SetFillColor(205);
  Ztautau->SetFillColor(64);
  THStack *hst = new THStack();
  hst->Add(Fakes);
  hst->Add(Others);
  hst->Add(Ztautau);
  TH1F *Total = (TH1F*) Fakes->Clone();
  Total->Add(Others);
  Total->Add(Ztautau);
  Total->SetFillColor(1);
  Total->SetLineColor(0);
  Total->SetFillStyle(3004);
  Total->SetMarkerSize(0);

  TH1F *Signal = (TH1F*) Signal_Z_125->Clone();
  Signal->Add(Signal_W_125);
  Signal->Add(Signal_gg_125);
  Signal->Add(Signal_VBF_125);
  Signal->Add(Total);
  TH1F *Signal_Odd = (TH1F*) Signal_Odd_Z_125->Clone();
  Signal_Odd->Add(Signal_Odd_W_125);
  Signal_Odd->Add(Signal_Odd_gg_125);
  Signal_Odd->Add(Signal_Odd_VBF_125);
  Signal_Odd->Add(Total);

  Signal->SetLineColor(4);
  Signal_Odd->SetLineColor(2);
  Signal->SetLineWidth(3);
  Signal_Odd->SetLineWidth(3);

  TCanvas *c = new TCanvas();
  double xmin = Total->GetXaxis()->GetXmin();
  double xmax = Total->GetXaxis()->GetXmax();
  double ymin = 0.01;
  double ymax = Total->GetMaximum()*3.0;
  TH1* frame = (TH1*)gPad->DrawFrame(xmin,ymin,xmax,ymax);
  frame->SetYTitle("Events");
  frame->SetXTitle("Acoplanarity #phi_{CP}");
  frame->Draw();

  hst->Draw("HIST SAMES");
  Total->Draw("E2 SAMES");
  Signal->Draw("HIST SAMES");
  Signal_Odd->Draw("HIST SAMES");

  ATLAS_WorkInProgress(0.19,0.87,0.035);
  myText(0.19,0.8,0.035,"#int L dt = 20.3fb^{-1} #sqrt{s} = 8TeV");
  myText(0.19,0.72,0.035,tname);

  TLegend *leg = new TLegend(0.63,0.9-0.07*5,0.9,0.9);
  leg->AddEntry(Data,"Data (2012)","PL");
  leg->AddEntry(Signal,"H(125)","L");
  leg->AddEntry(Signal_Odd,"A(125)","L");
  leg->AddEntry(Ztautau,"Z#rightarrow#tau#tau","F");
  leg->AddEntry(Others,"Others","F");
  leg->AddEntry(Fakes,"Fakes","F");
  leg->AddEntry(Total,"Uncert.","F");
  leg->SetTextFont(42);
  leg->SetLineColor(0);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->Draw();

  return;
}
