#ifndef TRKBINMAP
#define TRKBINMAP

//bins are 0-10,10-30,30-50,50+
//0.5-1,1-8,8-20,20+
//returns hiBinIndex*4+ptindex
int trkBinMap(int hiBin, float pt){
  int ptIndex = -1;
  if(pt>=0.5 && pt<1)  ptIndex = 0;
  if(pt>=1   && pt<8)  ptIndex = 1;
  if(pt>=8   && pt<20) ptIndex = 2;
  if(pt>=20)           ptIndex = 3;

  int hiBinIndex = -1;
  if(hiBin>=0 && hiBin<20) hiBinIndex = 0;
  if(hiBin>=20 && hiBin<60) hiBinIndex = 1;
  if(hiBin>=60 && hiBin<100) hiBinIndex = 2;
  if(hiBin>=100 && hiBin<200) hiBinIndex = 3;

  if(ptIndex>-1 && hiBinIndex>-1) return hiBinIndex*4+ptIndex+1;
  else return -1;
}

#endif
