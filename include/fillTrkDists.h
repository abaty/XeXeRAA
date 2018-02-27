#ifndef FILLTRKDIST
#define FILLTRKDIST

#include "TH1D.h"

void fillTrkDists(TH1D * phi, TH1D * phi2, float phi_f, TH1D * DCAz, TH1D * DCAz2, float DCAz_f, TH1D * DCAxy, TH1D * DCAxy2, float DCAxy_f, TH1D * nHit, TH1D * nHit2, float nHit_f, TH1D * chi2, TH1D * chi22, float chi2_f, TH1D * ptErr, TH1D * ptErr2, float ptErr_f, TH1D * calo, TH1D * calo2, float calo_f, float w){
  phi->Fill(phi_f,w);
  phi2->Fill(phi_f,w);
  DCAz->Fill(DCAz_f,w);
  DCAz2->Fill(DCAz_f,w);
  DCAxy->Fill(DCAxy_f,w);
  DCAxy2->Fill(DCAxy_f,w);
  nHit->Fill(nHit_f,w);
  nHit2->Fill(nHit_f,w);
  chi2->Fill(chi2_f,w);
  chi22->Fill(chi2_f,w);
  ptErr->Fill(ptErr_f,w);
  ptErr2->Fill(ptErr_f,w);
  calo->Fill(calo_f,w);
  calo2->Fill(calo_f,w);
}

#endif
