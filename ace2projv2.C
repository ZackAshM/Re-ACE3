
// Example displaying a 2D histogram with its two projections.
// Author: Olivier Couet

// Edited by: Zachary Martin; Date: July 2019
// Now saves hists as pngs for varying 'runTypes'
// and runs over a list of energies.
// This macro assumes the directory to be the
// main directory (which holds all of the
// simulation directories i.e. include, src, etc.)
{

  /* ------- Data save parameters -------- */
  
  // prevent popup windows
  gROOT->SetBatch(kTRUE);

  // define type of runs taken
  auto runType{static_cast<std::string>("nogap")};  // original, nogap, etc.
  
  // directory containing data
  auto dataPath{"data/" + runType + "/"};
  
  // file counter dependent on energies
  std::string energies[6] = {"05", "1", "10", "50", "500", "1000"}//, "3000"};
                           // 0.5, 1, 10, 50, 500, 1000, 3000 GeV

  // time hists min and max
  auto timeMax{0.};
  auto timeMin{5000.};

  /* -------------------------------------- */

  // change to directory containing data
  gSystem->cd(dataPath.c_str());
  
  for (auto const& i : energies) {

    // save path
    auto savePath{i};
    
    // make energy folder if it doesn't already exist
    gSystem->mkdir(i.c_str());
  
    // data file
    auto fileName{"ACE3_Data_" + runType + "_" + i.c_str() + ".root"};
  
    TCanvas *c1 = new TCanvas("c1", "c1",2000,1200);
    //gStyle->SetOptStat(100101000);
    //gStyle->SetOptStat(000101001);
    gStyle->SetOptStat(1111111);
   
    const Int_t NRGBs = 5;
    const Int_t NCont = 255;

    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.87 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.71, 1.00, 0.22, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);
   
   
    // Create the six pads
    c1->Divide(3,2,.01,0.01,0);
    //  TPad *pad1 = new TPad("pad1", "pad1",0,.50,.33,1.0);
    c1_1->Draw();
    //   TPad *pad2 = new TPad("pad2", "pad2",.33,);
    c1_2->Draw();
    //   TPad *pad3 = new TPad("pad3", "pad3",0.0,0.0,0.65,0.6);
    c1_3->Draw();
    //  TPad *pad4 = new TPad("pad4", "pad4",0.0,0.0,0.65,0.6);
    c1_4->Draw();
    //   TPad *pad5 = new TPad("pad5", "pad5",0.0,0.0,0.65,0.6);
    c1_5->Draw();
    //   TPad *pad6 = new TPad("pad6", "pad6",0.0,0.0,0.65,0.6);
    c1_6->Draw(); 
  
 
   
    TFile *f =  new TFile(fileName.c_str());

    TH2F *s2 = (TH2F*)f->Get("s2");  // s2=ACE1, s3=ACE2, s4=ACE3
    TH2F *s3 = (TH2F*)f->Get("s3");
    TH2F *s4 = (TH2F*)f->Get("s4");
    TH2F *s5 = (TH2F*)f->Get("s5");
    TH2F *s6 = (TH2F*)f->Get("s6");
    TH2F *s7 = (TH2F*)f->Get("s7");
  
   
    TH1F *h = (TH1F*)f->Get("h7");  // h7=ACE1, h8=ACE2, h9=ACE3


    // Drawing
    c1_4->cd();
    //gStyle->SetPalette(1);
   
    int Ntot = 20000; // for this run
    s2->SetStats(0);
    //s2->SetContour(99);
    //s->Scale(1/10.);  // scale these for 100/1000 events
    //c1_4->SetLogz();
    int s2min = s2->GetMinimum();
    s2->SetMinimum(s2min);
    s2->Draw("COLZ");
    s2->GetXaxis()->SetTitle("x, mm");
    s2->GetYaxis()->SetTitle("y, mm");  
    c1_4->SetRightMargin(0.16);
    Double_t sint2 = s2->Integral(15,45,15,45);
    std::cout << "S2 INTEGRAL OF 2D: "<<sint2/(Ntot/120)<< " excess charge hits per 120 14.5 GeV events" <<std::endl;

    c1_5->cd();
    //gStyle->SetPalette(1);
    s3->SetStats(0);
    //s3->SetContour(99);
    //s->Scale(1/10.);  // scale these for 100/1000 events
    //c1_5->SetLogz();
    int s3min = s3->GetMinimum();
    s3->SetMinimum(s3min);
    s3->Draw("COLZ");
    s3->GetXaxis()->SetTitle("x, mm");
    s3->GetYaxis()->SetTitle("y, mm");  
    c1_5->SetRightMargin(0.16);
    Double_t sint3 = s3->Integral(15,45,15,45);
    std::cout << "S3 INTEGRAL OF 2D: "<<sint3/(Ntot/120)<< " excess charge hits per 120 14.5 GeV events" <<std::endl;
   
    c1_6->cd();
    //gStyle->SetPalette(1);
    s4->SetStats(0);
    //s4->SetContour(99);
    //s->Scale(1/10.);  // scale these for 100/1000 events
    //  c1_6->SetLogz();
    int s4min = s4->GetMinimum();
    s4->SetMinimum(s4min);
    s4->Draw("COLZ");
    s4->GetXaxis()->SetTitle("x, mm");
    s4->GetYaxis()->SetTitle("y, mm");  
    c1_6->SetRightMargin(0.16);
    Double_t sint4 = s4->Integral(15,45,15,45);
    std::cout << "S4 INTEGRAL OF 2D: "<<sint4/(Ntot/120)<< " excess charge hits per 120 14.5 GeV events" <<std::endl;

    c1_1->cd();
    //gStyle->SetPalette(1);
    s5->SetStats(0);
    //s5->SetContour(99);
    //s->Scale(1/10.);  // scale these for 100/1000 events
    s5->SetMinimum(1);
    c1_1->SetLogz();
    s5->Draw("COLZ");
    s5->GetXaxis()->SetTitle("x, mm");
    s5->GetYaxis()->SetTitle("y, mm");  
    c1_1->SetRightMargin(0.16);
    Double_t sint5 = s5->Integral(15,45,15,45);
    std::cout << "S5 INTEGRAL OF 2D: "<<sint5/(Ntot/120)<< " total charge hits in 120 e- 14.5 GeV events" <<std::endl;

    c1_2->cd();
    //gStyle->SetPalette(1);
    s6->SetStats(0);
    s6->SetMinimum(1);
    //s6->SetContour(99);
    //s->Scale(1/10.);  // scale these for 100/1000 events
    c1_2->SetLogz();
    s6->Draw("COLZ");
    s6->GetXaxis()->SetTitle("x, mm");
    s6->GetYaxis()->SetTitle("y, mm");  
    c1_2->SetRightMargin(0.16);
    Double_t sint6 = s6->Integral(15,45,15,45);
    std::cout << "S6 INTEGRAL OF 2D: "<<sint6/(Ntot/120)<< " total charge hits in 120 e- 14.5 GeV events" <<std::endl;
   
    c1_3->cd();
    //gStyle->SetPalette(1);
    s7->SetStats(0);
    s7->SetMinimum(1);
    //s7->SetContour(99);
    //s->Scale(1/10.);  // scale these for 100/1000 events
    c1_3->SetLogz();
    s7->Draw("COLZ");
    s7->GetXaxis()->SetTitle("x, mm");
    s7->GetYaxis()->SetTitle("y, mm");  
    c1_3->SetRightMargin(0.16);
    Double_t sint7 = s7->Integral(15,45,15,45);
    std::cout << "S7 INTEGRAL OF 2D: "<<sint7/(Ntot/120)<< " total charge hits in 120 e- 14.5GeV events" <<std::endl;  
   
    //    c1->cd();
    //    TLatex *t = new TLatex();
    //    t->SetTextFont(42);
    //    t->SetTextSize(0.04);
    //    t->DrawLatex(0.6,0.88,"GEANT4 ");
    //     t->DrawLatex(0.6,0.84,"simulations");  
    //    t->DrawLatex(0.6,0.80,"of ACE");
    // t->DrawLatex(0.6,0.76,"100 x 12.1 GeV e-");  
   
   
    TCanvas *c2 = new TCanvas("c2", "c2",1200,1800);
   
    gStyle->SetOptStat();
    //c2->SetLogy();
   
    // Create the three pads
    auto top_pad{new TPad("top_pad", "top_pad",0,0.67,1,1)};
    //top_pad->SetLogy();
    top_pad->Draw();

    auto mid_pad{new TPad("mid_pad", "mid_pad",0,.33,1.0,0.67)};
    //mid_pad->SetLogy();
    mid_pad->Draw();

    auto bot_pad{new TPad("bot_pad", "bot_pad",0.0,0.0,1,0.33)};
    // bot_pad->SetLogy();
    bot_pad->Draw();
     
    TH1F *ht1 = (TH1F*)f->Get("h10");  // h10=ACE1, h11=ACE2, h12=ACE3
    TH1F *ht2 = (TH1F*)f->Get("h11"); 
    TH1F *ht3 = (TH1F*)f->Get("h12"); 

    top_pad->cd();
    ht1->Scale(0.01);
    //ht1->SetMinimum();
    //ht1->SetMaximum(2e4);
    ht1->Draw("hist same bar");
    ht1->SetFillColor(kBlue-4);
    top_pad->SetLeftMargin(0.15); 
    ht1->GetXaxis()->SetRangeUser(timeMin,timeMax);
    ht1->GetYaxis()->SetTitleOffset(1.6); 
    ht1->GetYaxis()->SetTitle("e+e- dN/dt, hits per ps");
    ht1->GetXaxis()->SetTitle("time, picoseconds from local reference");
    top_pad->Draw();

    mid_pad->cd();
    //h->Scale(1/10.);
    ht2->Scale(0.01);
    //ht2->SetMinimum(.2);
    //ht2->SetMaximum(2e4);   
    ht2->Draw("hist same bar");
    ht2->SetFillColor(kBlue-4);
    mid_pad->SetLeftMargin(0.15); 
    ht2->GetXaxis()->SetRangeUser(timeMin,timeMax);
    ht2->GetYaxis()->SetTitleOffset(1.6); 
    ht2->GetYaxis()->SetTitle("e+e- dN/dt, hits per ps");
    ht2->GetXaxis()->SetTitle("time, picoseconds from local reference");    
    mid_pad->Draw();
    
    bot_pad->cd();
    //h->Scale(1/10.);
    ht3->Scale(0.01);
    //ht3->SetMinimum(.2);
    //ht3->SetMaximum(2e4);   
    ht3->Draw("hist same bar");
    ht3->SetFillColor(kBlue-4);
    bot_pad->SetLeftMargin(0.15); 
    ht3->GetXaxis()->SetRangeUser(timeMin,timeMax);
    ht3->GetYaxis()->SetTitleOffset(1.6); 
    ht3->GetYaxis()->SetTitle("e+e- dN/dt, hits per ps");
    ht3->GetXaxis()->SetTitle("time, picoseconds from local reference");    
    bot_pad->Draw();
    
 
    TCanvas *c3 = new TCanvas("c3", "c3",1000,1500);
   
    gStyle->SetOptStat();
    //c2->SetLogy();
   
    // Create the three pads
    auto top_pad2{new TPad("top_pad2", "top_pad2",0,0.67,1,1)};
    //top_pad->SetLogy();
    top_pad2->Draw();

    auto mid_pad2{new TPad("mid_pad2", "mid_pad2",0,.33,1.0,0.67)};
    //mid_pad->SetLogy();
    mid_pad2->Draw();

    auto bot_pad2{new TPad("bot_pad2", "bot_pad2",0.0,0.0,1,0.33)};
    // bot_pad->SetLogy();
    bot_pad2->Draw();
   
    //Cauchy distribution fit function
    TF1 *ft = new TF1("fc","[1]/(3.14159*[0]*(1 + (x/[0])*(x/[0])))", -7, 7);
    ft->SetParameters(1.0,50);
   
    TH1D *et1 = s2->ProjectionY("ps2",31,31);// e10=ACE1, e11=ACE2, e12=ACE3
    TH1D *et2 = s3->ProjectionY("ps3",31,31);
    TH1D *et3 = s4->ProjectionY("ps4",31,31);
  
    top_pad2->cd();
    et1->Scale(1./(Ntot/120));
    //ht1->SetMinimum();
    //ht1->SetMaximum(2e4);
    et1->Fit("fc");
    et1->Draw("");
    et1->SetFillColor(kBlue-4);
    top_pad->SetLeftMargin(0.15); 
    //ht1->GetXaxis()->SetRangeUser(0.025,0.075);
    et1->GetYaxis()->SetTitleOffset(1.6); 
    et1->GetYaxis()->SetTitle("excess charge ACE1");
    et1->GetXaxis()->SetTitle("distance, mm");
   
   

    mid_pad2->cd();
    //h->Scale(1/10.);
    et2->Scale(1./(Ntot/120));
    //ht2->SetMinimum(.2);
    //ht2->SetMaximum(2e4);   
    //ft->SetParameters(1.);
    et2->Fit("fc");
    et2->Draw("");
    et2->SetFillColor(kBlue-4);
    mid_pad->SetLeftMargin(0.15); 
    //ht2->GetXaxis()->SetRangeUser(0.025,0.075);
    et2->GetYaxis()->SetTitleOffset(1.6); 
    et2->GetYaxis()->SetTitle("excess charge ACE2");
    et2->GetXaxis()->SetTitle("distance, mm"); 
   
  

    bot_pad2->cd();
    //h->Scale(1/10.);
    et3->Scale(1./(Ntot/120));
    //ht3->SetMinimum(.2);
    //ht3->SetMaximum(2e4);   
    et3->Fit("fc");
    et3->Draw("");
    et3->SetFillColor(kBlue-4);
    bot_pad->SetLeftMargin(0.15); 
    //ht3->GetXaxis()->SetRangeUser();
    et3->GetYaxis()->SetTitleOffset(1.6); 
    et3->GetYaxis()->SetTitle("excess charge  ACE3");
    et3->GetXaxis()->SetTitle("distance, mm"); 
    //ft->SetParameters(1.);

    // continue processing after drawing
    gSystem->ProcessEvents();

    // change directory to save path
    gSystem->cd(savePath.c_str());
    
    // construct image files
    auto c1png{TImage::Create()};
    auto c2png{TImage::Create()};
    auto c3png{TImage::Create()};

    c1png->FromPad(c1);
    c2png->FromPad(c2);
    c3png->FromPad(c3);

    // and save the pngs
    c1png->WriteImage("chargeHists.png");
    c2png->WriteImage("timeHists.png");
    c3png->WriteImage("excessFitHists.png");

    // continue processing after saving
    gSystem->ProcessEvents();

    // change back to directory containing data
    gSystem->cd("..");

  }
  
  // close ROOT
  //gApplication->Terminate();
   
}
