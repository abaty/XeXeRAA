#include <iostream>

//written by Austin Baty, same as what is used for 5 TeV charged particle RAA (HIN-15-015)
//calculated by taking double-ratios of the same data and MC reconstructed in HI and pp reconstructions and comparing the two
//returns the tracking relative uncertainty
//give track pt and centrality
//if doing a ratio of 2 observatbles, set isRatio to 1
//otherwise set isRatio to 0 and set isPP to 1 or 0 depending on if you are using pp or PbPb
float trackingDataMCDiffUncert(float trkPt = -1, int cent = -1, bool isRatio = 1, bool isPP = 0){
  if(trkPt<0){
    std::cout << "Error in trackingDataMCDiffUncert()!  negative Pt!" << std::endl;
    return -99;
  }
  if(cent<0 || cent>99){
    std::cout << "Error in trackingDataMCDiffUncert()!  centrality not in the range of [0,99]!" << std::endl;
    return -99;
  }

  if(!isRatio && isPP) return 0.04;
  if(!isRatio && !isPP) return 0.05;

  //low pt tracks seem pretty constant vs centrality
  if(trkPt < 1.0) return 0.04;

  //mid-pt tracks
  if(trkPt<1.4){
    if(cent<30) return 0.052;
    if(cent<50) return 0.045;
    if(cent<70) return 0.035;
    return 0.03;
  }
  
  //high-pt tracks
  if(cent<30) return 0.064;//no cancallation assumed
  if(cent<50) return 0.05;
  if(cent<70) return 0.03;
  return 0.02; 
}
