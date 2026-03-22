// **************************************************************
//
//      ------ AlgDataAction.cc ------
//           by Aleksei  (11 Nov 2024)
//    
//
// **************************************************************

#include "AlgDataAction.hh"


AlgDataAction* AlgDataAction::DataInstance = 0;

//------------------------------------------------------------
/*
AlgDataAction::AlgDataAction(string fname, bool fReadPosPar)
{
	ResetRun( fReadPosPar );

	FileOpen = new TFile(fname.c_str());
	if( FileOpen->IsZombie() ){
		ThrowError("AlgDataAction(): Open The Data File Failed!!!");
	}
	t_Total   = (TTree*)FileOpen->Get("Total");
	t_ACD     = (TTree*)FileOpen->Get("Anticoincidence");
	t_CAL     = (TTree*)FileOpen->Get("Calorimeter");
	t_Primary = (TTree*)FileOpen->Get("PrimaryParameter");
	TotalEvtNum = (int)t_Total->GetEntries();
	
	//Tree: Total
	t_Total   -> SetBranchAddress("TotalEdep",     &TotalPriDepEnergy);
	t_Total   -> SetBranchAddress("TotalEdep_ACD",       &TotalPriEdep[0]);
	t_Total   -> SetBranchAddress("TotalEdep_BottomACD", &TotalPriEdep[3]);
	t_Total   -> SetBranchAddress("TotalEdep_UP",        &TotalPriEdep[1]);
	t_Total   -> SetBranchAddress("TotalEdep_DOWN",      &TotalPriEdep[2]);
	t_Total   -> SetBranchAddress("StructureEdep", &StrucEdep);
	t_Total   -> SetBranchAddress("Interaction",   &fInteraction);
	t_Total   -> SetBranchAddress("EventInFOV",    &fEvtInFOV);
	t_Total   -> SetBranchAddress("TotalEdepDelay",           &TotalPriEdep_Delay);
	t_Total   -> SetBranchAddress("TotalEdepDelay_ACD",       &TotalPriEdepACD_Delay);
	t_Total   -> SetBranchAddress("TotalEdepDelay_CAL",       &TotalPriEdepCAL_Delay);
	t_Total   -> SetBranchAddress("TotalEdepDelay_BottomACD", &TotalPriEdepBottomACD_Delay);

	//Tree: ACD
	t_ACD -> SetBranchAddress("PixelID_ACD",  &PixelID[0]);
	t_ACD -> SetBranchAddress("Edep_ACD",     &PixelEdep[0]);
	t_ACD -> SetBranchAddress("Order_ACD",    &PixelHitOrder[0]);
	//t_ACD -> SetBranchAddress("EdepDelay_ACD",&PixelEdepDelay[0]);

	//Tree: CAL
	t_CAL -> SetBranchAddress("PixelID_CAL",  &PixelID[1]);
	t_CAL -> SetBranchAddress("Edep_CAL",     &PixelEdep[1]);
	t_CAL -> SetBranchAddress("Order_CAL",    &PixelHitOrder[1]);
	//t_CAL -> SetBranchAddress("EdepDelay_CAL",&PixelEdepDelay[1]);

	//Tree: PrimaryParameters
	t_Primary -> SetBranchAddress("PDG",     &PDG);
	t_Primary -> SetBranchAddress("Kinetic", &PrimaryEng);
	t_Primary -> SetBranchAddress("Dir_x",	 &Direction[0]);
	t_Primary -> SetBranchAddress("Dir_y",	 &Direction[1]);
	t_Primary -> SetBranchAddress("Dir_z",	 &Direction[2]);
	t_Primary -> SetBranchAddress("Pos_x",   &Position[0]);
	t_Primary -> SetBranchAddress("Pos_y",   &Position[1]);
	t_Primary -> SetBranchAddress("Pos_z",   &Position[2]);
	
}
*/

//------------------------------------------------------------
AlgDataAction::AlgDataAction()
{
    cout << "1" <<endl;
	//ResetRun( fReadPosPar );
    ResetRun();
    
}

//------------------------------------------------------------
AlgDataAction::AlgDataAction( string fname)
{
    cout << "2" <<endl;
//	ResetRun( fReadPosPar );
    ResetRun();

	t_Total   = new TChain("Total");
	t_ACD     = new TChain("Anticoincidence");
	t_CAL     = new TChain("Calorimeter");
	t_Primary = new TChain("PrimaryParameter");
	cout << "We run constructor"<< endl;

	cout<<"===>   "<<fname.c_str()<<"   <==="<<endl;
	if( fname.find(".root") != fname.npos ){
		cout<<"Add File: "<<fname.c_str()<<endl;
		t_Total->Add( fname.c_str() );
		t_ACD  ->Add( fname.c_str() );
		t_CAL  ->Add( fname.c_str() );
		t_Primary->Add( fname.c_str() );
	}
	else{
		ifstream fListOpen;
		fListOpen.open( fname.c_str() );
		if( !fListOpen.good() ){
			ThrowError("AlgDataAction(): Can Not Open The Input List File!!!");
			exit(0);
		}
		while( fListOpen.peek() != EOF ){
			string line;
			getline( fListOpen, line );
			cout<<"AddListFile:  "<<line.c_str()<<endl;
			t_Total->Add( line.c_str() );
			t_ACD  ->Add( line.c_str() );
			t_CAL  ->Add( line.c_str() );
			t_Primary->Add( line.c_str() );
		}
	}

	TotalEvtNum = (int)t_Total->GetEntries();
	cout<<"DataTool: TotalEvtNum = "<<TotalEvtNum<<endl;
	//Tree: Total
	t_Total   -> SetBranchAddress("TotalEdep",           &TotalPriDepEnergy);
	t_Total   -> SetBranchAddress("TotalEdep_ACD",       &TotalPriEdep[0]);
//	t_Total   -> SetBranchAddress("TotalEdep_BottomACD", &TotalPriEdep[3]);
	t_Total   -> SetBranchAddress("TotalEdep_UP",        &TotalPriEdep[1]);
	t_Total   -> SetBranchAddress("TotalEdep_DOWN",      &TotalPriEdep[2]);
	t_Total   -> SetBranchAddress("StructureEdep",       &StrucEdep);
	t_Total   -> SetBranchAddress("Interaction",         &fInteraction);
	t_Total   -> SetBranchAddress("EventInFOV",          &fEvtInFOV);
	t_Total   -> SetBranchAddress("TotalEdepDelay",           &TotalPriEdep_Delay);
	t_Total   -> SetBranchAddress("TotalEdepDelay_ACD",       &TotalPriEdepACD_Delay);
	t_Total   -> SetBranchAddress("TotalEdepDelay_CAL",       &TotalPriEdepCAL_Delay);
//	t_Total   -> SetBranchAddress("TotalEdepDelay_BottomACD", &TotalPriEdepBottomACD_Delay);

	//Tree: ACD
	t_ACD -> SetBranchAddress("PixelID_ACD",  &PixelID[0]);
	t_ACD -> SetBranchAddress("Edep_ACD",     &PixelEdep[0]);
	t_ACD -> SetBranchAddress("Order_ACD",    &PixelHitOrder[0]);
	//t_ACD -> SetBranchAddress("EdepDelay_ACD",&PixelEdepDelay[0]);
	t_ACD -> SetBranchAddress("EventID",      &EventID[0]);

	//Tree: CAL
	t_CAL -> SetBranchAddress("PixelID_CAL",  &PixelID[1]);
	t_CAL -> SetBranchAddress("Edep_CAL",     &PixelEdep[1]);
	t_CAL -> SetBranchAddress("Order_CAL",    &PixelHitOrder[1]);
	//t_CAL -> SetBranchAddress("EdepDelay_CAL",&PixelEdepDelay[1]);
	t_CAL -> SetBranchAddress("EventID",      &EventID[1]);

	//Tree: PrimaryParameters
	t_Primary -> SetBranchAddress("PDG",         &PDG);
	t_Primary -> SetBranchAddress("Kinetic",     &PrimaryEng);
	t_Primary -> SetBranchAddress("Dir_x",	     &Direction[0]);
	t_Primary -> SetBranchAddress("Dir_y",	     &Direction[1]);
	t_Primary -> SetBranchAddress("Dir_z",	     &Direction[2]);
	t_Primary -> SetBranchAddress("Pos_x",       &Position[0]);
	t_Primary -> SetBranchAddress("Pos_y",       &Position[1]);
	t_Primary -> SetBranchAddress("Pos_z",       &Position[2]);
	t_Primary -> SetBranchAddress("EventID_ACD", &FirstID_ACD);
	t_Primary -> SetBranchAddress("Hits_ACD",    &nHits_ACD);
	t_Primary -> SetBranchAddress("EventID_CAL", &FirstID_CAL);
	t_Primary -> SetBranchAddress("Hits_CAL",    &nHits_CAL);
    t_Primary -> SetBranchAddress("Int_x",       &IntPosition[0]);
    t_Primary -> SetBranchAddress("Int_y",       &IntPosition[1]);
    t_Primary -> SetBranchAddress("Int_z",       &IntPosition[2]);
}

//------------------------------------------------------------
AlgDataAction::~AlgDataAction()
{
	//FileOpen->Close();
	//delete FileOpen;	FileOpen = NULL;
	delete t_Total;		t_Total  = NULL;
	delete t_ACD;			t_ACD		 = NULL;
	delete t_CAL;			t_CAL		 = NULL;
	delete t_Primary;	t_Primary= NULL;
}

//------------------------------------------------------------
AlgDataAction* AlgDataAction::getInstance(string fname){
    cout << "3" <<endl;
	if(DataInstance == 0 ){
		DataInstance = new AlgDataAction(fname);
	}
	return DataInstance;
}

//------------------------------------------------------------
AlgDataAction* AlgDataAction::getInstance(){

	if(DataInstance == 0 ){
		cout<<"======  Error in getInstance(): Please Pass the ROOT FILE NAME!!!  ======"<<endl;;
	}
	else
		return DataInstance;
}

//------------------------------------------------------------
/*void AlgDataAction::ReadPixelPosition(){

		for(int i=0;i<nPixel;i++){
			PixelMap[i][0] = -1;
			PixelMap[i][1] = -1;
			for(int j=0;j<3;j++)
				for(int k=0;k<3;k++)
					PixelPos[i][j][k] = -1;
		}

		ifstream txtopen;
		//---  ACD Parameter  ---
		txtopen.open("/Users/aleksejsmirnov/Downloads/Code_Libo/CrystalEye/DetectorStructure/Parameter/Position_atc.txt");
		if( !txtopen.is_open() ){
			ThrowError("AlgDataAction(): Can Not Open the TXT File!!!");
		}
		for(int i=0; i<nPixel; i++){
			txtopen>>PixelPos[i][0][0]>>PixelPos[i][0][1]>>PixelPos[i][0][2];
		}
		txtopen.close();
		//---  UP Parameter  ---
		txtopen.open("/Users/aleksejsmirnov/Downloads/Code_Libo/CrystalEye/DetectorStructure/Parameter/Position_up.txt");
		if( !txtopen.is_open() ){
			ThrowError("AlgDataAction(): Can Not Open the TXT File!!!");
		}
		for(int i=0; i<nPixel; i++){
			txtopen>>PixelPos[i][1][0]>>PixelPos[i][1][1]>>PixelPos[i][1][2];
		}
		txtopen.close();
		//---  DOWN Parameter  ---
		txtopen.open("/Users/aleksejsmirnov/Downloads/Code_Libo/CrystalEye/DetectorStructure/Parameter/Position_down.txt");
		if( !txtopen.is_open() ){
			ThrowError("AlgDataAction(): Can Not Open the TXT File!!!");
		}
		for(int i=0; i<nPixel; i++){
			txtopen>>PixelPos[i][2][0]>>PixelPos[i][2][1]>>PixelPos[i][2][2];
		}
		txtopen.close();
		//---  MAP Parameter  ---
		txtopen.open("/Users/aleksejsmirnov/Downloads/Code_Libo/CrystalEye/DetectorStructure/Parameter/ID_map.txt");
		if( !txtopen.is_open() ){
			ThrowError("AlgDataAction(): Can Not Open the TXT File!!!");
		}
		int tmp = -1;
		for(int i=0; i<nPixel; i++){
			txtopen>>tmp>>PixelMap[i][0]>>PixelMap[i][1];
		}
		txtopen.close();

}*/
//------------------------------------------------------------
void AlgDataAction::ResetRun(){
    cout << "we again here" << endl;
		fTagEvtReset = false;
		ThresholdACD = 0.;
	//	ThresholdBottomACD = 0.;
		ThresholdCAL = 0.;
		fThresholdOpen= false;

	//-----  Read The Parameters of Pixel_UP  -----
/*	if(fReadPosPar==true){
		ReadPixelPosition();
	}*/

}
//------------------------------------------------------------
bool AlgDataAction::ResetEvent(int evti){
	fTagThresholdACD       = false;
//	fTagThresholdBottomACD = false;
	fTagThresholdCAL       = false;

	fTagEvtReset = false;
	for(int li=0; li<3; li++){
		MaxEID[li] = -1;
		nHits[li]  = 0.; 
		for(int pi=0; pi<nPixel; pi++){
			Edep[li][pi] = -1;
		}
	}
	HitOrder_ACD.clear();
	HitOrder_CAL.clear();

	//Tree: Total
	t_Total -> GetEntry(evti);
//	if(TotalPriEdep[3]==-1)
//		TotalPriEdep[3] = 0;
	
	//Tree: PrimaryParameters
	t_Primary -> GetEntry(evti);

	TotalDepEnergy = 0;
	for(int i=0; i<3;i++){
		TotalEdep[i] = 0;
		TotalEdep_Delay[i] = 0;
	}

	//Tree: ACD
	double tmpe = -1;
	//int nhits_acd = nPixel + 1; //nPixel + BottomACD!!!
	int evti_acd  = FirstID_ACD;
	int nhits_acd = nHits_ACD;
	for(int i=0; i < nhits_acd; i++){
		t_ACD -> GetEntry( evti_acd + i );
		if( EventID[0] != evti ){
			cout
				<<"  RealEventID = "<<evti
				<<"  AcdEventID = "<<evti_acd
				<<endl;
			ThrowError("ResetEvent(): EventID_ACD is Wrong!!!");
		}

		int    fid  = PixelID[0];
		double fedep     = PixelEdep[0];
		if(PixelHitOrder[0]!=-1 && fid!=nPixel && fedep>=ThresholdACD)	
			HitOrder_ACD.insert( map<int, int>::value_type( PixelHitOrder[0], fid ) );


		if( fid<nPixel ){// Up ACD
			if( fedep>=ThresholdACD){
				fTagThresholdACD  = true;
				Edep[0][fid] = fedep;

				if(Edep[0][fid]>tmpe){
					tmpe = Edep[0][fid];
					MaxEID[0] = fid;
				}
					nHits[0]++;
				TotalEdep[0] = TotalEdep[0]+fedep;
				TotalDepEnergy = TotalDepEnergy + fedep;
			}//Judge threshold
		}
		else if( fid==nPixel){/* Bottom ACD
			if( fedep>=ThresholdBottomACD){
				fTagThresholdBottomACD = true;
				TotalEdep[3] = fedep;
				TotalDepEnergy = TotalDepEnergy + fedep;
				if(TotalEdep[3] != TotalPriEdep[3]){
					ThrowError("ResetEvent(): Edep of BottomACD is Wrong!!!");
				}
			}*/
		}
		else{
			cout<<"Error In Reset(): The PixelID of ACD is out of the range!!!"<<endl;
			exit(0);
		}
	}

	//Tree: CAL
	double tmpe1 = -1;
	double tmpe2 = -1;
	int evti_cal  = FirstID_CAL;
	int nhits_cal = nHits_CAL;
	for(int i=0; i<nhits_cal; i++){
		t_CAL -> GetEntry( evti_cal + i );
		if( EventID[1] != evti ){
			cout
				<<"  RealEventID = "<<evti
				<<"  CalEventID = "<<evti_cal
				<<endl;
			ThrowError("ResetEvent(): PixelID_CAL is Wrong!!!");
		}
		int    fid   = PixelID[1];
		double fedep = PixelEdep[1];
		int layer = fid / nPixel + 1;
		int id    = fid % nPixel;

		if(PixelHitOrder[1] != -1 && fedep>ThresholdCAL)	
			HitOrder_CAL.insert( map<int, int>::value_type( PixelHitOrder[1], fid ) );

		if( fedep>=ThresholdCAL ){
			fTagThresholdCAL = true;

			nHits[layer]++;
			Edep[layer][id]  = fedep;
			TotalEdep[layer] = TotalEdep[layer]+fedep;
			TotalDepEnergy   = TotalDepEnergy + fedep;
		}//Judge ThresholdCAL
	}

	for(int i=0; i<nPixel; i++){
		if(Edep[1][i]>tmpe1){
			tmpe1 = Edep[1][i];
			MaxEID[1] = i;
		}
		if(Edep[2][i]>tmpe2){
			tmpe2 = Edep[1][i];
			MaxEID[2] = i;
		}
	}

	fTagEvtReset = true;

	return true;
	
}

//------------------------------------------------------------
void AlgDataAction::GetPriPosition(double& x, double& y, double &z, double fthe, double fphi){

	double theta = fthe;
	if(theta==90)
		theta = 89.99;
	double phi = fphi;
	theta = (theta)/180.*TMath::Pi();
	phi = (phi)/180.*TMath::Pi();

	double d1 = -TMath::Sin(theta)*TMath::Cos(phi);
	double d2 = -TMath::Sin(theta)*TMath::Sin(phi);
	double d3 = -TMath::Cos(theta);

	double A= 144.999;//Surface of ACD

	x = -A*d1;
	y = -A*d2;
	z = -A*d3;
	//cout<<"PriX = "<<x<<"  PriY = "<<y<<endl;
}

//------------------------------------------------------------
void AlgDataAction::GetPriThetaPhi( double& fthe, double& fphi ){

	double d1 = -Direction[0];
	double d2 = -Direction[1];
	double d3 = -Direction[2];

	fthe = TMath::ACos(d3);
	fphi = TMath::ASin( d1/TMath::Sin(fthe) );

}

//------------------------------------------------------------
void AlgDataAction::SetPixelPosition(){
}

//------------------------------------------------------------
void AlgDataAction::GetPixelPosition(int pixelid, int detector, double& x, double& y, double& z){
	if(pixelid<0 || pixelid>=nPixel){
		ThrowError("GetPixelPosition(): Pixel ID is out of the range!!!");
	}
	if(detector<0 || detector>=3){
		ThrowError("GetPixelPosition: DetectorID is out of the range!!!");
	}

	pixelid = PixelMap[pixelid][0];

	x = PixelPos[pixelid][detector][0];
	y = PixelPos[pixelid][detector][1];
	z = PixelPos[pixelid][detector][2];

}

//------------------------------------------------------------
void AlgDataAction::GetPixelThetaPhi(int pixelid, int detector, double& theta, double& phi){
	if(pixelid<0 || pixelid>=nPixel){
		ThrowError("GetPixelThetaPhi(): Pixel ID is out of the range!!!");
	}
	if(detector<0 || detector>=3){
		ThrowError("GetPixelThetaPhi(): DetectorID is out of the range!!!");
	}

	pixelid = PixelMap[pixelid][0];

	double x = PixelPos[pixelid][detector][0];
	double y = PixelPos[pixelid][detector][1];
	double z = PixelPos[pixelid][detector][2];
	double r = TMath::Sqrt(x*x + y*y + z*z);

	double dx = x/r;
	double dy = y/r;
	double dz = z/r;

	double cos_theta = dz;
	double tan_phi   = dy/dx;
	theta = TMath::ACos( cos_theta );
  phi   = TMath::ATan( tan_phi );	

	double pi = TMath::Pi();
	if(x<0 && y>0)
		phi = pi + phi;
	if(x<0 && y<0)
		phi = pi + phi;
		//phi = phi - pi;
	if(x>0 && y<0)
		phi = 2*pi + phi; 
	//cout<<" Pixel_i = "<<pixelid<<"  x = "<<x<<"  y = "<<y<<"  the = "<<theta<<"  phi = "<<phi<<endl;

}

//------------------------------------------------------------
int AlgDataAction::GetTotalMaxID(int il, int prescale){

	double TotalMaxPixel[3][2];// [Layer][ID,Energy]
	for(int i=0; i<3; i++){
		for(int j=0; j<2; j++){
			TotalMaxPixel[i][j] = -1;
		}
	}

	int fevts = GetEventNumber();
	if(prescale!=0)
		fevts = fevts/prescale;
	for(int evti = 0; evti<fevts; evti++){
		bool flag = false;
		if(prescale!=0)
			flag = ResetEvent(evti*prescale);
		else
			flag = ResetEvent(evti);
		if(flag==false)		continue;

		for(int l=0; l<3; l++){
			int maxid = MaxEID[l];
			if(Edep[l][maxid]>TotalMaxPixel[l][1]){
				TotalMaxPixel[l][0] = maxid;
				TotalMaxPixel[l][1] = Edep[l][maxid];
			}
		}

	}

	return TotalMaxPixel[il][0];

}

//------------------------------------------------------------
void AlgDataAction::GetAverThePhi(int evti, int layer, double &fthe, double &fphi){

	double the_rec = -1;
	double phi_rec = -1;

	int tmpn = 0;
	double numerator[2]   = {0,0};
	double denominator[2] = {0,0};
	double fhits = GetHitsNumber( layer);
	for(int i=0; i<nPixel; i++){
		if(Edep[layer][i]>=0){
			double the, phi;
			GetPixelThetaPhi(i, layer, the, phi);
			numerator[0]   += Edep[layer][i]*1000./fhits*the;
			numerator[1]   += Edep[layer][i]*1000./fhits*phi;
			denominator[0] += Edep[layer][i]*1000./fhits;
			denominator[1] += Edep[layer][i]*1000./fhits;
			//cout
			//	<<"  evti = "<<evti
			//	<<"  layer = "<<layer
			//	<<"  pixel = "<<i
			//	<<"  fhits = "<<fhits
			//	<<"  Edep = "<<Edep[layer][i]
			//	<<"  the = "<<the
			//	<<"  phi = "<<phi
			//	<<"\n"<<endl;
		}
	}
	if(denominator[0]!=0){
		the_rec = numerator[0]/denominator[0];
	}

	if( denominator[1]!=0 ){
		phi_rec = numerator[1]/denominator[1];
	}
	fthe = the_rec;
	fphi = phi_rec;

}

//------------------------------------------------------------
void AlgDataAction::GetAverPosition(int evti, int layer, double &fx, double &fy, double &fz){

	double tmp_x = -1;
	double tmp_y = -1;
	double tmp_z = -1;

	int tmpn = 0;
	double numerator[3]   = {0,0,0};
	double denominator[3] = {0,0,0};
	double fhits = GetHitsNumber( layer);
	for(int i=0; i<nPixel; i++){
		if(Edep[layer][i]>=0){
			double xx = PixelPos[i][layer][0];
			double yy = PixelPos[i][layer][1];
			double zz = PixelPos[i][layer][2];

			numerator[0]   += Edep[layer][i]*1000.*xx;
			numerator[1]   += Edep[layer][i]*1000.*yy;
			numerator[2]   += Edep[layer][i]*1000.*zz;
			denominator[0] += Edep[layer][i]*1000.;
			denominator[1] += Edep[layer][i]*1000.;
			denominator[2] += Edep[layer][i]*1000.;
			//cout
			//	<<"  evti = "<<evti
			//	<<"  layer = "<<layer
			//	<<"  pixel = "<<i
			//	<<"  fhits = "<<fhits
			//	<<"  Edep = "<<Edep[layer][i]
			//	<<"  the = "<<the
			//	<<"  phi = "<<phi
			//	<<"\n"<<endl;
		}
	}
	if(denominator[0]!=0){
		tmp_x = numerator[0]/denominator[0];
	}
	if(numerator[0]==0){
		tmp_x = 0;
		//cout<<"111"<<endl;
	}

	if( denominator[1]!=0 ){
		tmp_y = numerator[1]/denominator[1];
	}
	if(numerator[1]==0){
		tmp_y = 0;
		//cout<<"222"<<endl;
	}

	if( denominator[2]!=0 ){
		tmp_z = numerator[2]/denominator[2];
	}
	if(numerator[2]==0){
		tmp_z = 0;
		//cout<<"333"<<endl;
	}

	fx = tmp_x;
	fy = tmp_y;
	fz = tmp_z;

}

//------------------------------------------------------------
int AlgDataAction::GetHitsNumber(int il){

	
	//int fhits = 0;
	//for(int ip = 0; ip<nPixel; ip++){
	//	if(Edep[il][ip]>0)
	//		fhits++;
	//}
	//cout<<"layer = "<<il<<"  hitsn = "<<fhits<<endl;
	//return fhits;

	/*if(il==0)
		if( nHits[il] != HitOrder_ACD.size() ){
			ThrowError("GetHitsNumber(): nHits is not equal to the size of order!!!");
		}
	if(il==1 || il==2)
		if( (nHits[1]+nHits[2]) != HitOrder_CAL.size() ){
			ThrowError("GetHitsNumber(): nHits is not equal to the size of order!!!");
		}*/

	return nHits[il];
	

}

//------------------------------------------------------------
int AlgDataAction::GetHitIDFromOrder(int layer, int forder){

	if(layer<0 || layer>1){
		ThrowError("GetHitFromOrder(): Layer is out of the range!!!");
	}

	int fsizeACD = HitOrder_ACD.size();
	int fsizeCAL = HitOrder_CAL.size();

	if(layer==0){
		if(fsizeACD==0){
			return -1;
		}
		if(forder>fsizeACD){
			ThrowError("GetHitFromOrder(): fOrder is out of the range!!!");
		}
		int fpixelid = HitOrder_ACD[forder];
		return fpixelid;

	}
	if(layer==1){
		if(fsizeCAL==0){
			return -1;
		}
		if(forder>fsizeCAL){
			ThrowError("GetHitFromOrder(): fOrder is out of the range!!!");
		}
		int fpixelid = HitOrder_CAL[forder];
		return fpixelid;

	}
}

//------------------------------------------------------------
int AlgDataAction::GetOrderSize(int layer){

	if(layer<0 || layer>1){
		ThrowError("GetOrderSize(): Layer is out of the range!!!");
	}

	if(layer==0)
		return HitOrder_ACD.size();
	if(layer==1)
		return HitOrder_CAL.size();

}

//------------------------------------------------------------
void AlgDataAction::GetEmpty_Fired_Info( double* container, int &firedN, int &emptyN, double thr_low, double thr_high){

	if(container==NULL){
		ThrowError("GetEmpty_Fired_Info(): The pointer of container is NULL!");
	}

	double tmp_min = 99999;
	double tmp_max = -1;
	if(thr_high==0){
		for(int i=0; i<nPixel; i++){
			if(container[i]>thr_low) firedN++;
			else	emptyN++;
		}
	}
	else if(thr_high!=0){
		for(int i=0; i<nPixel; i++){
			if(container[i]<thr_low || container[i]>thr_high)
			 	firedN++;
			else	
				emptyN++;
		}
	}



}

//------------------------------------------------------------
void AlgDataAction::Debug(string cc){
	cout<<"######  "<<cc.c_str()<<"  ######"<<endl;
}

//------------------------------------------------------------
void AlgDataAction::ThrowError(string cc){
	cout<<"======>  Error in "<<cc.c_str()<<"  <======"<<endl;
	exit(0);
}

//------------------------------------------------------------
void AlgDataAction::SetKineticBin(int* fkinetic){

	int funit[4] = {10, 100, 1000, 10000};
	int tmpi = 0;
	for(int unit_i=0; unit_i<4; unit_i++ ){

		for(int i=0;i<9;i++){
			fkinetic[tmpi] = funit[unit_i] * (i+1);
			//cout<<"tmpi = "<<tmpi<<"  Kinetic = "<<fkinetic[tmpi]<<endl;
			tmpi++;
		}
	}
	fkinetic[tmpi] = 100000;
	//cout<<"tmpi = "<<tmpi<<"  Kinetic = "<<fkinetic[tmpi]<<endl;

}

//------------------------------------------------------------
void AlgDataAction::SetKineticBin(double* fkinetic){

	double funit[4] = {10, 100, 1000, 10000};
	int tmpi = 0;
	for(int unit_i=0; unit_i<4; unit_i++ ){

		for(int i=0;i<9;i++){
			fkinetic[tmpi] = funit[unit_i] * (i+1);
			//cout<<"tmpi = "<<tmpi<<"  Kinetic = "<<fkinetic[tmpi]<<endl;
			tmpi++;
		}
	}
	fkinetic[tmpi] = 100000;
	//cout<<"tmpi = "<<tmpi<<"  Kinetic = "<<fkinetic[tmpi]<<endl;

}

//------------------------------------------------------------
void AlgDataAction::SetKineticBinRange(double* frange){
	
	int bin_n = 37;
	double fkinetic[37];
	SetKineticBin(fkinetic);

	frange[0] = fkinetic[0]/2.;
	for(int i=0; i<bin_n-1; i++){
		frange[i+1] = fkinetic[i] + (fkinetic[i+1] - fkinetic[i])/2.;
	}
	//frange[bin_n] = fkinetic[bin_n-1] + fkinetic[bin_n-1]/2.;
	frange[bin_n] = fkinetic[bin_n-1] + fkinetic[bin_n-1]/10.;

	//for(int i=0; i<bin_n; i++)
	//	cout
	//		<<"  i = "<<i
	//		<<"  fkinetic = "<<fkinetic[i]
	//		<<"  rangeD = "<<frange[i]
	//		<<"  rangeU = "<<frange[i+1]
	//		<<endl;


}

//------------------------------------------------------------
void AlgDataAction::SetKineticBinRange(int fbins, int* fbinc, double* frange){
	
	//frange[0] = fbinc[0]/2.;
	//for(int i=0; i<fbins-1; i++){
	//	frange[i+1] = fbinc[i] + (fbinc[i+1]-fbinc[i])/2.;
	//}
	//frange[fbins] = fbinc[fbins-1] + fbinc[fbins-1]/10.;

	frange[0] = 0;
	for(int i=0; i<fbins; i++){
		frange[i+1] = fbinc[i] + (fbinc[i]-frange[i]);
	}

	//for(int i=0; i<fbins; i++)
	//	cout
	//		<<" i = "<<i
	//		<<" binc = "<<fbinc[i]
	//		<<" up = "<<frange[i]
	//		<<" down = "<<frange[i+1]
	//		<<endl;

}

//------------------------------------------------------------
double AlgDataAction::GetPixelContainerThreshold(int layer_i,int eng_i){

	double fthreshold[37][3]={
		0.015,  0.5e-6, 0,  //0
		6.5e-6, 2.9e-5, 0,  //1
		6.5e-6, 7.6e-5, 0,  //2
		6.5e-6, 8.5e-5, 0,  //3
		6.5e-6, 1.7e-4, 0,  //4
		6.5e-6, 2.0e-4, 0,  //5
		6.5e-6, 2.0e-4, 0,  //6
		6.5e-6, 2.0e-4, 0,  //7
	 	6.5e-6, 2.0e-4, 0,  //8
		0,      2.0e-4, 0,  //9
		0,      4.0e-4, 0,  //10
		0,      0.001,  0,  //11
		0,      0.001,  0,  //12
		0,      0.0015, 0,  //13
		0,      0.0025, 0,  //14
		0,      0.0025, 0,  //15
		0,      0.0028, 0,  //16
		0,      0.0030, 0,  //17
		0,      0.0030, 0,  //18
    0,      0.0070, 0,  //19
		0,      0.0120, 0,  //20
		0,      0.0150, 0,  //21
		0,      0.0170, 0,  //22
		0,      0.0220, 0,  //23
		0,      0.0250, 0,  //24
		0,      0.0330, 0,  //25
		0,      0.0400, 0,  //26
		0,      0.0400, 0,  //27
		0,      0.0800, 0,  //28
		0,      0.1100, 0,  //29
		0,      0.1600, 0,  //30
		0,      0.2000, 0,  //31
		0,      0.2000, 0,  //32
		0,      0.2900, 0,  //33
		0,      0.3200, 0,  //34
		0,      0.3900, 0,  //35
		0,      0.3900, 0,  //36
	}; 
	return fthreshold[eng_i][layer_i];

}
//------------------------------------------------------------
double AlgDataAction::GetPixelContainerThreshold(int layer_i, double fprie){

	double tmp_prie[37];
	SetKineticBin(tmp_prie);

	double tmp_min = 999;
	int eng_i = -1;
	for(int i=0; i<37; i++){
		double diff = TMath::Abs( fprie - tmp_prie[i] );
		if(diff<tmp_min){
			tmp_min = diff;
			eng_i = i;
		}
	}
	if(eng_i!=-1)
		return GetPixelContainerThreshold(layer_i, eng_i);
	else
		ThrowError("GetPixelContainerThreshold(): eng_i is -1 !!!!!");


}
//------------------------------------------------------------
void AlgDataAction::SetLogBinRange(double *range,std::vector<double> spectrumE,vector<double> spectrumN){
	if(spectrumE.empty()){
		cout<<"Error in AlgDataAction: The Parameter in SetLogBinRange() is 0!!!"<<endl;
		exit(0);
	}

	int spectrumSize = spectrumE.size();
	if( spectrumN.size() != (spectrumSize-1)){
		cout<<"Error in AlgDataAction: The Parameter in SetLogBinRange() is 0!!!"<<endl;
		exit(0);
	}

	double log_range = -1;
	range[0] = spectrumE[0];

	int tmpi = 0;
	for(int i=0;i<(spectrumSize-1);i++){
		double E0 = spectrumE[i];
		double E1 = spectrumE[i+1];
		double bin_n = spectrumN[i];
		log_range = (TMath::Log10(E1)-TMath::Log10(E0))/double(bin_n);
		//cout
		//	<<"  SpE_i = "<<i
    //  <<"  E0 = "<<E0
		//	<<"  E1 = "<<E1
		//	<<"  LogE0 = "<<TMath::Log10(E0)
		//	<<"  LogE1 = "<<TMath::Log10(E1)
		//	<<endl;
 
		for(int j=1;j<=bin_n;++j){
			tmpi++;
			range[tmpi] = range[tmpi-1]*TMath::Power(10.,log_range);
		}
	}

}
//------------------------------------------------------------
void AlgDataAction::SetLogBinRange(int bin_n, double* range, double begin, double end){

	range[0] = begin;
	if(begin<=0)
		begin = 0.1;

	double log_gap = ( TMath::Log10(end) - TMath::Log10(begin) )/double(bin_n);
	for(int i=1; i<=bin_n; i++){
		if(i==1)
			range[i] = begin * TMath::Power(10., log_gap);
		else
			range[i] = range[i-1] * TMath::Power(10., log_gap);
	}

}

//------------------------------------------------------------
void AlgDataAction::SetThreshold(double facd,  double fcal){

    cout << "we arehere!!!!!!" << endl;
	fThresholdOpen = true;
	ThresholdACD       = facd/1000.;//MeV
//	ThresholdBottomACD = fbottom_acd/1000.;//MeV
	ThresholdCAL       = fcal/1000.;//MeV

	//cout
	//	<<"===>"
	//	<<"  ThresholdACD = "<<facd<<" keV"
	//	<<"  ThresholdBottomACD = "<<fbottom_acd<<" keV"
	//	<<"  ThresholdCAL = "<<fcal<<" keV"
	//	<<"  <==="
	//	<<endl;

}

//------------------------------------------------------------
void AlgDataAction::GetThresholdTag(bool& tag_acd, bool& tag_cal){

	tag_acd        = fTagThresholdACD;
//	tag_bottom_acd = fTagThresholdBottomACD;
	tag_cal        = fTagThresholdCAL;

}

//------------------------------------------------------------
bool AlgDataAction::GetTriggerACD( double thr ){
	bool tmp = false;

	double edep = TotalEdep[0]*1000.;
	//if((edep<=thr)&&(edep > 0)){
    if((edep<=thr)){
		tmp = true;
	}

	return tmp;
}

//------------------------------------------------------------
/*bool AlgDataAction::GetTriggerBottomACD( double thr ){
	bool tmp = false;
	
	double edep = TotalEdep[3]*1000.;
	if(edep<=thr)
		tmp = true;

	return tmp;
}*/

//------------------------------------------------------------
void AlgDataAction::Reweight(
		TH1D *&h1_nor, TH1D *h1_kin, TH2D *&h2_read, TF1*& func, bool fSetBin){
  //cout << "1: " << h1_nor<<"  2: "<<h1_kin<<"   3: "<<h2_read<<endl;

	int xbins = h2_read->GetNbinsX();
	int ybins = h2_read->GetNbinsY();
  //cout<<"xbins = "<<xbins<<"   ybins ="<<ybins<<endl;

	double* binRangeX;
	double* binRangeY;
	if(fSetBin==true){
		binRangeX = new double[xbins+1];
		for(int i=0; i<xbins+1; i++){
			binRangeX[i] = h2_read->GetXaxis()->GetBinLowEdge(i+1);
		}

		binRangeY = new double[ybins+1];
		for(int i=0; i<ybins+1; i++){
		  binRangeY[i] = h2_read->GetYaxis()->GetBinLowEdge(i+1);
		}
		h1_nor->SetBins(ybins, binRangeY);
	}

	for(int iy=0;iy<ybins;iy++){//DepositedEnergy
		double x_nor = 0;
		double x_err = 0;
		for(int ix=0;ix<xbins;ix++){//PrimaryEnergy
			double binC   = h1_kin->GetBinCenter(ix+1);
			double binN   = h1_kin->GetBinContent(ix+1);
			double coeff  = func->Eval(binC);
			double xy_nor = h2_read->GetBinContent(ix+1,iy+1);
			double xy_nor_err = 0;

			if(binN!=0){
				xy_nor = xy_nor/binN;
				if(xy_nor!=0)
					//xy_nor_err = xy_nor*xy_nor*( 1./xy_nor + 1./binN );
					xy_nor_err = TMath::Sqrt( 1./xy_nor + 1./binN )*coeff;
			}
			else{
				xy_nor = 0;
			}

			xy_nor = coeff*xy_nor;

			x_nor = x_nor + xy_nor;
			x_err = x_err + xy_nor_err*xy_nor_err;
			
		}

		//cout
		//	<<" x_nor = "<<x_nor
		//	<<" x_err = "<<x_err
		//	<<endl;
		h1_nor->SetBinContent(iy+1,x_nor);
		//h1_nor->SetBinError(iy+1, TMath::Sqrt(x_err) );
	}

	delete [] binRangeX;	binRangeX=NULL;
	delete [] binRangeY;  binRangeY=NULL;

}

//------------------------------------------------------------
void AlgDataAction::Reweight(
		TH1D *&h1_nor, TH1D *h1_kin, TH2D *&h2_read, TF1*& func, int fbini, bool fSetBin){
  //cout << "1: " << h1_nor<<"  2: "<<h1_kin<<"   3: "<<h2_read<<endl;

	int xbins = h2_read->GetNbinsX();
	int ybins = h2_read->GetNbinsY();
  //cout<<"xbins = "<<xbins<<"   ybins ="<<ybins<<endl;

	double* binRangeX;
	double* binRangeY;
	if(fSetBin==true){
		binRangeX = new double[xbins+1];
		for(int i=0; i<xbins+1; i++){
			binRangeX[i] = h2_read->GetXaxis()->GetBinLowEdge(i+1);
		}

		binRangeY = new double[ybins+1];
		for(int i=0; i<ybins+1; i++){
		  binRangeY[i] = h2_read->GetYaxis()->GetBinLowEdge(i+1);
		}
		h1_nor->SetBins(ybins, binRangeY);
	}

	for(int iy=0;iy<ybins;iy++){//DepositedEnergy
		double x_nor = 0;
		double x_err = 0;
		//for(int ix=0;ix<xbins;ix++){//PrimaryEnergy
		int ix = fbini;
		double binC   = h1_kin->GetBinCenter(ix+1);
		double binN   = h1_kin->GetBinContent(ix+1);
		double coeff  = func->Eval(binC);
		double xy_nor = h2_read->GetBinContent(ix+1,iy+1);
		double xy_nor_err = 0;

		if(binN!=0){
			xy_nor = xy_nor/binN;
			if(xy_nor!=0)
				//xy_nor_err = xy_nor*xy_nor*( 1./xy_nor + 1./binN );
				xy_nor_err = TMath::Sqrt( 1./xy_nor + 1./binN )*coeff;
		}
		else{
			xy_nor = 0;
		}

		xy_nor = coeff*xy_nor;

		x_nor = x_nor + xy_nor;
		x_err = x_err + xy_nor_err*xy_nor_err;

		//}

		//cout
		//	<<" x_nor = "<<x_nor
		//	<<" x_err = "<<x_err
		//	<<endl;
		h1_nor->SetBinContent(iy+1,x_nor);
		//h1_nor->SetBinError(iy+1, TMath::Sqrt(x_err) );
	}

	delete [] binRangeX;	binRangeX=NULL;
	delete [] binRangeY;  binRangeY=NULL;

}

//------------------------------------------------------------
void AlgDataAction::Reweight(
		TH2D *&h2_nor, TH1D *h1_kin, TH2D *&h2_read, TF1*& func, bool fSetBin){

  //cout << "1: " << h2_nor<<"  2: "<<h1_kin<<"   3: "<<h2_read<<endl;

	int xbins = h2_read->GetNbinsX();
	int ybins = h2_read->GetNbinsY();
  //cout<<"xbins = "<<xbins<<"   ybins ="<<ybins<<endl;

	double* binRangeX;
	double* binRangeY;
	if(fSetBin==true){
		binRangeX = new double[xbins+1];
		for(int i=0; i<xbins+1; i++){
			binRangeX[i] = h2_read->GetXaxis()->GetBinLowEdge(i+1);
		}
		binRangeY = new double[ybins+1];
		for(int i=0; i<ybins+1; i++){
		  binRangeY[i] = h2_read->GetYaxis()->GetBinLowEdge(i+1);
		}

		h2_nor->SetBins(xbins, binRangeX, ybins, binRangeY);
	}

	for(int ix=0;ix<xbins;ix++){//PrimaryEnergy
		for(int iy=0;iy<ybins;iy++){//DepositedEnergy
			double binC   = h1_kin->GetBinCenter(ix+1);
			double binN   = h1_kin->GetBinContent(ix+1);
			double coeff  = func->Eval(binC);
			double xy_nor = h2_read->GetBinContent(ix+1,iy+1);
			double xy_nor_err = 0;
			if(binN!=0){
				xy_nor = xy_nor/binN;
				if(xy_nor!=0)
					//xy_nor_err = xy_nor*xy_nor*( 1./xy_nor + 1./binN );
					xy_nor_err = TMath::Sqrt( 1./xy_nor + 1./binN )*coeff;
			}
			else{
				xy_nor = 0;
			}
			xy_nor = coeff*xy_nor;

			h2_nor->SetBinContent(ix+1,iy+1,xy_nor);
			//h2_nor->SetBinError(ix+1,iy+1, xy_nor_err );
		}
	}

	delete [] binRangeX; binRangeX=NULL;
	delete [] binRangeY; binRangeY=NULL;

}

//------------------------------------------------------------
void AlgDataAction::SetMap(TH2D*& h2_map, TH1D* h1_total, TH1D** h1_pixel, int npixel){

	int xbins = npixel;
	int ybins = h1_total->GetNbinsX();
	double* binRangeX = new double[npixel+1] ;
	double* binRangeY = new double[ybins+1];
	for(int i=0; i<xbins+1; i++){
		binRangeX[i] = i+0.5;
	}
	for(int i=0; i<ybins+1; i++){
		binRangeY[i] = h1_total->GetXaxis()->GetBinLowEdge(i+1);
	}
	h2_map->SetBins(xbins, binRangeX, ybins, binRangeY);

	double ftotal = 0;
	for(int iy=0; iy<ybins; iy++){
		ftotal = ftotal+h1_total->GetBinContent(iy+1);
	}
	//cout<<"======>  ftotal = "<<ftotal<<"   <======"<<endl;

	for(int ix=0; ix<xbins; ix++){
		//cout<<"Pointer["<<ix<<"] = "<<h1_pixel[ix]<<endl;
		for(int iy=0; iy<ybins; iy++){
			double binC_pixel = h1_pixel[ix]->GetBinContent(iy+1) / ftotal;
			h2_map->SetBinContent(ix+1, iy+1, binC_pixel);
		}
	}



	delete [] binRangeX; binRangeX=NULL;
	delete [] binRangeY; binRangeY=NULL;

}

//------------------------------------------------------------
void AlgDataAction::CopyHistogram(TH1D*& h_copy, TH1D* h_prim){

	int xbins = h_prim->GetNbinsX();
	double* binRangeX = new double[xbins+1];
	for(int i=0; i<xbins+1; i++)
		binRangeX[i] = h_prim->GetXaxis()->GetBinLowEdge(i+1);
	h_copy->SetBins(xbins, binRangeX);

	for(int ix=0; ix<xbins; ix++){
		double binC = h_prim->GetBinContent(ix+1);
		h_copy->SetBinContent(ix+1, binC);
	}
	delete [] binRangeX; binRangeX=NULL;

}

//------------------------------------------------------------
void AlgDataAction::CopyHistogram(TH2D*& h_copy, TH2D* h_prim){

	int xbins = h_prim->GetNbinsX();
	int ybins = h_prim->GetNbinsY();
	double* binRangeX = new double[xbins+1];
	double* binRangeY = new double[ybins+1];
	for(int i=0; i<xbins+1; i++)
		binRangeX[i] = h_prim->GetXaxis()->GetBinLowEdge(i+1);
	for(int i=0; i<ybins+1; i++)
		binRangeY[i] = h_prim->GetYaxis()->GetBinLowEdge(i+1);
	h_copy->SetBins(xbins, binRangeX, ybins, binRangeY);

	for(int ix=0; ix<xbins; ix++){
		for(int iy=0; iy<ybins; iy++){
			double binC = h_prim->GetBinContent(ix+1, iy+1);
			h_copy->SetBinContent(ix+1, iy+1, binC);
		}
	}
	delete [] binRangeX; binRangeX=NULL;
	delete [] binRangeY; binRangeY=NULL;

}

//------------------------------------------------------------
void AlgDataAction::CopyHistogram(TH2D*& h_copy, TH2D** h_prim){

	int xbins = h_prim[0]->GetNbinsX();
	int ybins = h_prim[0]->GetNbinsY();
	double* binRangeX = new double[xbins+1];
	double* binRangeY = new double[ybins+1];
	for(int i=0; i<xbins+1; i++)
		binRangeX[i] = h_prim[0]->GetXaxis()->GetBinLowEdge(i+1);
	for(int i=0; i<ybins+1; i++)
		binRangeY[i] = h_prim[0]->GetYaxis()->GetBinLowEdge(i+1);
	h_copy->SetBins(xbins, binRangeX, ybins, binRangeY);

	for(int ix=0; ix<xbins; ix++){
		for(int iy=0; iy<ybins; iy++){
			double binC = 0;
			for(int i=0; i<4; i++){
				if(h_prim[i]==NULL){
					cout<<"Error in AlgDataAction: Can NOT Find Pointer of h_prim["<<i<<"] !!!"<<endl;
				}
				binC = binC + h_prim[i]->GetBinContent(ix+1, iy+1);
			}
			h_copy->SetBinContent(ix+1, iy+1, binC);
		}
	}

	delete [] binRangeX; binRangeX=NULL;
	delete [] binRangeY; binRangeY=NULL;
}

//------------------------------------------------------------
void AlgDataAction::CopyHistogram(TH2D*& h_copy, TH2D* h_prim, int& minBinX, int& minBinY){

	int xbins = h_prim->GetNbinsX();
	int ybins = h_prim->GetNbinsY();
	double* binRangeX = new double[xbins+1];
	double* binRangeY = new double[ybins+1];
	for(int i=0; i<xbins+1; i++)
		binRangeX[i] = h_prim->GetXaxis()->GetBinLowEdge(i+1);
	for(int i=0; i<ybins+1; i++)
		binRangeY[i] = h_prim->GetYaxis()->GetBinLowEdge(i+1);
	h_copy->SetBins(xbins, binRangeX, ybins, binRangeY);

	minBinX = -1;
	minBinY = -1;
	double minBinN = 999;
	for(int ix=0; ix<xbins; ix++){
		for(int iy=0; iy<ybins; iy++){
			double binC = h_prim->GetBinContent(ix+1, iy+1);
			h_copy->SetBinContent(ix+1, iy+1, binC);

			if( TMath::Log10(binC) < minBinN ){
				minBinX = ix;
				minBinY = iy;
				minBinN = TMath::Log10(binC);
			}

		}
	}
	delete [] binRangeX; binRangeX=NULL;
	delete [] binRangeY; binRangeY=NULL;
}

//------------------------------------------------------------
void AlgDataAction::CopyHistogram(
		TH1D*& h_copy, TH2D* h_prim, int fbini, bool fAxis){

	int xbins = h_prim->GetNbinsX();
	int ybins = h_prim->GetNbinsY();
	double* binRangeX = new double[xbins+1];
	double* binRangeY = new double[ybins+1];
	for(int i=0; i<xbins+1; i++)
		binRangeX[i] = h_prim->GetXaxis()->GetBinLowEdge(i+1);
	for(int i=0; i<ybins+1; i++)
		binRangeY[i] = h_prim->GetYaxis()->GetBinLowEdge(i+1);

	if( fAxis==false){//Project to X(Theta) to get Y(Phi)
		h_copy->SetBins( xbins, binRangeX );

		if( fbini<-1 || fbini>ybins){
			cout<<"Error in CopyHistogram(): Wrong fbini of Y Axis!!!"<<endl;
			exit(0);
		}
		int iy = fbini;
		for(int ix=0; ix<xbins; ix++){
			double binC = h_prim->GetBinContent(ix+1, iy+1);
			h_copy->SetBinContent(ix+1, TMath::Log10(binC) );
		}
	}
	else if( fAxis==true){//Project to Y(Phi) to get X(Theta)
		h_copy->SetBins( ybins, binRangeY );

		if( fbini<-1 || fbini>xbins){
			cout<<"Error in CopyHistogram(): Wrong fbini of X Axis!!!"<<endl;
			exit(0);
		}
		int ix = fbini;
		for(int iy=0; iy<ybins; iy++){
			double binC = h_prim->GetBinContent(ix+1, iy+1);
			h_copy->SetBinContent(iy+1, TMath::Log10(binC) );
		}
	}

	delete [] binRangeX; binRangeX=NULL;
	delete [] binRangeY; binRangeY=NULL;
}

//------------------------------------------------------------
double AlgDataAction::CopyHistogram(
		TGraph*& tg_copy, TH2D* h_prim, int fbini, bool fAxis){

	int xbins = h_prim->GetNbinsX();
	int ybins = h_prim->GetNbinsY();
	vector<double> binC; binC.clear();
	vector<double> binN; binN.clear();
	double MinC = 400;
	double MinN = 999;

	if( fAxis==false){//Project to X(Theta) to get Y(Phi)
		if( fbini<-1 || fbini>ybins){
			cout<<"Error in CopyHistogram(): Wrong fbini of Y Axis!!!"<<endl;
			exit(0);
		}
		int iy = fbini;
		//for(int ix=xbins-1; ix>=0; ix--){
		//	double tmpC = -h_prim->GetXaxis()->GetBinCenter( ix+1 );
		//	double tmpN =  h_prim->GetBinContent(ix+1, iy+1);
		//	binC.push_back( tmpC );
		//	//binN.push_back( tmpN );
		//	binN.push_back( TMath::Log10(tmpN) );
		//}
		for(int ix=0; ix<xbins; ix++){
			double tmpC = h_prim->GetXaxis()->GetBinCenter( ix+1 );
			double tmpN = h_prim->GetBinContent(ix+1, iy+1);
			binC.push_back( tmpC );
			//binN.push_back( tmpN );
			binN.push_back( TMath::Log10(tmpN) );

			if( TMath::Log10(tmpN) < MinN ){
				MinC = tmpC;
				MinN = TMath::Log10(tmpN);
			}
		}
		//for(int ix=xbins-1; ix>=0; ix--){
		//	double tmpC = -h_prim->GetXaxis()->GetBinCenter( ix+1 )+180.;
		//	double tmpN =  h_prim->GetBinContent(ix+1, iy+1);
		//	binC.push_back( tmpC );
		//	//binN.push_back( tmpN );
		//	binN.push_back( TMath::Log10(tmpN) );
		//}
	}
	else if( fAxis==true){//Project to Y(Phi) to get X(Theta)
		if( fbini<-1 || fbini>xbins){
			cout<<"Error in CopyHistogram(): Wrong fbini of X Axis!!!"<<endl;
			exit(0);
		}
		int ix = fbini;
		//for(int iy=ybins-1; iy>=0; iy--){
		//	double tmpC = -h_prim->GetYaxis()->GetBinCenter( iy+1 );
		//	double tmpN =  h_prim->GetBinContent(ix+1, iy+1);
		//	binC.push_back( tmpC );
		//	//binN.push_back( tmpN );
		//	binN.push_back( TMath::Log10(tmpN) );
		//}
		for(int iy=0; iy<ybins; iy++){
			double tmpC = h_prim->GetYaxis()->GetBinCenter( iy+1 );
			double tmpN = h_prim->GetBinContent(ix+1, iy+1);
			binC.push_back( tmpC );
			//binN.push_back( tmpN );
			binN.push_back( TMath::Log10(tmpN) );

			if( TMath::Log10(tmpN) < MinN ){
				MinC = tmpC;
				MinN = TMath::Log10(tmpN);
			}
		}
		//for(int iy=ybins-1; iy>=0; iy--){
		//	double tmpC = -h_prim->GetYaxis()->GetBinCenter( iy+1 )+2*360.;
		//	double tmpN =  h_prim->GetBinContent(ix+1, iy+1);
		//	binC.push_back( tmpC );
		//	//binN.push_back( tmpN );
		//	binN.push_back( TMath::Log10(tmpN) );
		//}
	}

	int sizeN = binN.size();
	for(int i=0; i<sizeN; i++){
		tg_copy->SetPoint( i, binC[i], binN[i] );
		//if(fAxis==true)
		//	cout<<"i = "<<i<<"  phi = "<<binC[i]<<"  N = "<<binN[i]<<endl;
	}

	return MinC;
}

//------------------------------------------------------------
double AlgDataAction::GetPositionChiSquare(TH2D* h_map, TH2D* h_sig, int& fDf){

	TH1D* h_mapY = h_map->ProjectionY();
	double ftotalN_map = 0;
	//cout<<"DepENbins_Map = "<<h_mapY->GetNbinsX()<<endl;
	for(int i=0; i<h_mapY->GetNbinsX(); i++){
		ftotalN_map = ftotalN_map + h_mapY->GetBinContent(i+1);
		//cout<<"Content["<<i<<"] = "<<h_mapY->GetBinContent(i+1)<<endl;
	}

	TH1D* h_sigY = h_sig->ProjectionY();
	double ftotalN_sig = 0;
	//cout<<"DepENbins_Sig = "<<h_sigY->GetNbinsX()<<endl;
	for(int i=0; i<h_sigY->GetNbinsX(); i++){
		ftotalN_sig = ftotalN_sig + h_sigY->GetBinContent(i+1);
		//cout<<"Content["<<i<<"] = "<<h_sigY->GetBinContent(i+1)<<endl;;
	}

	double xbins = h_map->GetNbinsX();//PixelID
	double ybins = h_map->GetNbinsY();//DepE
	//cout<<"Map Bins: xbins = "<<xbins<<"  ybins = "<<ybins<<endl;

	double tmp_totalNsig = 0;
	double tmp_totalNmap = 0;

	double ChiSquare = 0;
	int    Dfreedom  = 0;
	for(int ix=0; ix<xbins; ix++){//PixelID
		double binN_sig = 0;
		double binN_map = 0;
		double binN_rec = 0;
		for(int iy=0; iy<ybins; iy++){//DepE Bins

			binN_sig = binN_sig + h_sig->GetBinContent(ix+1, iy+1);
			binN_map = binN_map + h_map->GetBinContent(ix+1, iy+1);

			tmp_totalNsig = tmp_totalNsig + h_sig->GetBinContent(ix+1, iy+1);
			tmp_totalNmap = tmp_totalNmap + h_map->GetBinContent(ix+1, iy+1);
		}

		binN_rec = binN_map/ftotalN_map * ftotalN_sig;
		//cout<<"PixelID = "<<ix<<"  binN_rec = "<<binN_rec<<"  ftotalN_map = "<<ftotalN_map<<"  ftotalN_sig = "<<ftotalN_sig<<endl;

		if(binN_rec>0){
			double pixelChiS = TMath::Power( binN_sig-binN_rec, 2) / (binN_rec);
			ChiSquare = ChiSquare+pixelChiS;
			Dfreedom++;
		}
	}
	fDf = Dfreedom-1;
	//cout<<"ftotalN_sig = "<<ftotalN_sig<<"  tmp_totalNsig = "<<tmp_totalNsig<<endl;
	//cout<<"ftotalN_map = "<<ftotalN_map<<"  tmp_totalNmap = "<<tmp_totalNmap<<endl;

	return ChiSquare;
}

//------------------------------------------------------------
double AlgDataAction::GetPositionChiSquare(TH2D* h_map, TH2D* h_sig, TH2D* h_bgk){

	TH1D* h_mapY = h_map->ProjectionY();
	double ftotalN_map = 0;
	//cout<<"DepENbins_Map = "<<h_mapY->GetNbinsX()<<endl;
	for(int i=0; i<h_mapY->GetNbinsX(); i++){
		ftotalN_map = ftotalN_map + h_mapY->GetBinContent(i+1);
		//cout<<"Content["<<i<<"] = "<<h_mapY->GetBinContent(i+1)<<endl;
	}
	//cout<<"\n\n\n"<<endl;

	TH1D* h_sigY = h_sig->ProjectionY();
	double ftotalN_sig = 0;
	//cout<<"DepENbins_Sig = "<<h_sigY->GetNbinsX()<<endl;
	for(int i=0; i<h_sigY->GetNbinsX(); i++){
		ftotalN_sig = ftotalN_sig + h_sigY->GetBinContent(i+1);
		//cout<<"Content["<<i<<"] = "<<h_sigY->GetBinContent(i+1)<<endl;;
	}

	TH1D* h_bgkY = h_bgk->ProjectionY();
	double ftotalN_bkg = 0;
	for(int i=0; i<h_bgk->GetNbinsX(); i++){
		ftotalN_bkg = ftotalN_bkg + h_bgkY->GetBinContent(i+1);
	}

	double xbins = h_map->GetNbinsX();//PixelID
	double ybins = h_map->GetNbinsY();//DepE
	//cout<<"Map Bins: xbins = "<<xbins<<"  ybins = "<<ybins<<endl;

	double tmp_totalNbkg = 0;
	double tmp_totalNsig = 0;
	double tmp_totalNmap = 0;

	double ChiSquare = 0;
	for(int ix=0; ix<xbins; ix++){//PixelID
		double binN_bkg = 0;
		double binN_sig = 0;
		double binN_map = 0;
		double binN_rec = 0;
		for(int iy=0; iy<ybins; iy++){//DepE Bins

			binN_bkg = binN_bkg + h_bgk->GetBinContent(ix+1, iy+1);
			binN_sig = binN_sig + h_sig->GetBinContent(ix+1, iy+1);
			binN_map = binN_map + h_map->GetBinContent(ix+1, iy+1);

			tmp_totalNbkg = tmp_totalNbkg + h_bgk->GetBinContent(ix+1, iy+1);
			tmp_totalNsig = tmp_totalNsig + h_sig->GetBinContent(ix+1, iy+1);
			tmp_totalNmap = tmp_totalNmap + h_map->GetBinContent(ix+1, iy+1);
		}

		binN_rec = binN_map/ftotalN_map * (ftotalN_sig+ftotalN_bkg);
		//cout<<"PixelID = "<<ix<<"  binN_rec = "<<binN_rec<<endl;

		double pixelChiS = TMath::Power( (binN_sig+binN_bkg)-binN_rec, 2) / (binN_rec);

		ChiSquare = ChiSquare+pixelChiS;
	}
	//cout<<"ftotalN_sig = "<<ftotalN_sig<<"  tmp_totalNsig = "<<tmp_totalNsig<<endl;
	//cout<<"ftotalN_map = "<<ftotalN_map<<"  tmp_totalNmap = "<<tmp_totalNmap<<endl;

	return ChiSquare;
}

//------------------------------------------------------------
void AlgDataAction::GetRecDirection(double& RecThe, double& RecPhi, TH2D* h2_chi2){

	RecThe = 0;
	RecPhi = 0;

	string histName = h2_chi2->GetName();
	int xbins = h2_chi2->GetNbinsX();//Theta Bins
	int ybins = h2_chi2->GetNbinsY();//Phi Bins

	int nPoints = 5;
	vector<double> minChi2(nPoints, 999);
	vector<double> minChiT(nPoints, -99);
	vector<double> minChiP(nPoints, 999);
	//for(int i=0; i<nPoints; i++){
	//	cout
	//		<<"  i = "<<i
	//		<<"  chi2 = "<<minChi2[i]
	//		<<"  The = "<<minChiT[i]
	//		<<"  Phi = "<<minChiP[i]
	//		<<endl;
	//}

	for(int ix=0; ix<xbins; ix++){
		for(int iy=0; iy<ybins; iy++){

			double fchi = TMath::Log10( h2_chi2->GetBinContent(ix+1, iy+1) );
			//double fchi = h2_chi2->GetBinContent(ix+1, iy+1);
			double fthe = h2_chi2->GetXaxis()->GetBinCenter(ix+1);
			double fphi = h2_chi2->GetYaxis()->GetBinCenter(iy+1);
			///cout<<histName.c_str()<<"  fthe = "<<fthe<<"  fphi = "<<fphi<<"  chi2 = "<<fchi<<endl;

			for(int ic=0; ic<nPoints; ic++){
				if( fchi < minChi2[ic] ){
					for(int i=nPoints-1; i>ic; i--){
						minChi2[i] = minChi2[i-1];
						minChiT[i] = minChiT[i-1];
						minChiP[i] = minChiP[i-1];
					}
					minChi2[ic] = fchi;
					minChiT[ic] = fthe;
					minChiP[ic] = fphi;
					break;
				}
			}

		}
	}

	double chi2_t = 0;
	double chi2_p = 0;

	double pi = TMath::Pi();
	double chi2_x = 0;
	double chi2_y = 0;
	double chi2_z = 0;
	double chi2_N = 0;
	for(int i=0; i<nPoints; i++){
		double fchi = 1./TMath::Power(10., minChi2[i]);
		//double fchi = 1./TMath::Power( minChi2[i], 2);
		double fthe = minChiT[i];
		double fphi = minChiP[i];
		double fx = TMath::Sin(fthe/180.*pi)*TMath::Cos(fphi/180.*pi);
		double fy = TMath::Sin(fthe/180.*pi)*TMath::Sin(fphi/180.*pi);
		double fz = TMath::Cos(fthe/180.*pi);

		//chi2_t = chi2_t + fthe*fchi*fchi;
		//chi2_p = chi2_p + fphi*fchi*fchi;
		chi2_x = chi2_x + fx*fchi*fchi;
		chi2_y = chi2_y + fy*fchi*fchi;
		chi2_z = chi2_z + fz*fchi*fchi;
		chi2_N = chi2_N + fchi*fchi;

		cout
			<<"  i = "<<i
			<<"  fthe = "<<fthe
			<<"  fphi = "<<fphi
			<<"  fx = "<<fx
			<<"  fy = "<<fy
			<<"  fz = "<<fz
			<<"  fchi = "<<fchi
			<<"  Logchi2 = "<<minChi2[i]
			<<endl;
	}
	if(chi2_N!=0){
		//RecThe = chi2_t/chi2_N;
		//RecPhi = chi2_p/chi2_N;

		double ave_x = chi2_x/chi2_N;
		double ave_y = chi2_y/chi2_N;
		double ave_z = chi2_z/chi2_N;
    RecThe = TMath::ACos( ave_z )/pi*180.;
		if(RecThe==0)  RecThe=0.000001;
		RecPhi = TMath::ACos( ave_x/TMath::Sin(RecThe/180.*pi) )/pi*180.;

		if(ave_y<0)
			RecPhi = 360.-RecPhi;

		cout
			<<"  "<<histName.c_str()
			<<"  RecThe = "<<RecThe
			<<"  RecPhi = "<<RecPhi<<"\n"
			<<"  ave_x = "<<ave_x
			<<"  ave_y = "<<ave_y
			<<"  ave_z = "<<ave_z<<"\n"
			<<endl;
	}
	else{
		cout<<"chi2_N = "<<chi2_N<<endl;
		cout<<"Error in GetRecDirection(): Total 1./Chi2 is ZERO!!!"<<endl;
		exit(0);
	}
}

//------------------------------------------------------------
void AlgDataAction::GetRecDirection0(double& RecThe, double& RecPhi, TH2D* h2_chi2){

	RecThe = 0;
	RecPhi = 0;

	string histName = h2_chi2->GetName();
	int xbins = h2_chi2->GetNbinsX();//Theta Bins
	int ybins = h2_chi2->GetNbinsY();//Phi Bins

	double chi2_t = 0;
	double chi2_p = 0;
	double chi2_N = 0;
	for(int ix=0; ix<xbins; ix++){
		for(int iy=0; iy<ybins; iy++){

			double fchi = 1./h2_chi2->GetBinContent(ix+1, iy+1);
			double fthe = h2_chi2->GetXaxis()->GetBinCenter(ix+1);
			double fphi = h2_chi2->GetYaxis()->GetBinCenter(iy+1);
			///cout<<histName.c_str()<<"  fthe = "<<fthe<<"  fphi = "<<fphi<<"  chi2 = "<<fchi<<endl;

			chi2_t = chi2_t + fthe*fchi*fchi;
			chi2_p = chi2_p + fphi*fchi*fchi;
			chi2_N = chi2_N + fchi*fchi;
		}
	}

	if(chi2_N!=0){
		RecThe = chi2_t/chi2_N;
		RecPhi = chi2_p/chi2_N;
		cout<<histName.c_str()<<"  RecThe = "<<RecThe<<"  RecPhi = "<<RecPhi<<endl;
	}
	else{
		cout<<"Error in GetRecDirection(): Total 1./Chi2 is ZERO!!!"<<endl;
		exit(0);
	}
}
//------------------------------------------------------------
double AlgDataAction::GetPositionChiSquare(TH2D* h_map, TH2D* h_sig, int& fDf, double ftime){
	double pi = TMath::Pi();
	double farea = 2.*pi*14.5*14.5/112.;
	double fsr   = 2.*pi;

	TH1D* h_mapY = h_map->ProjectionY();
	double ftotalN_map = 0;
	//cout<<"DepENbins_Map = "<<h_mapY->GetNbinsX()<<endl;
	for(int i=0; i<h_mapY->GetNbinsX(); i++){
		ftotalN_map = ftotalN_map + h_mapY->GetBinContent(i+1);
		//cout<<"Content["<<i<<"] = "<<h_mapY->GetBinContent(i+1)<<endl;
	}
	//cout<<"\n\n\n"<<endl;

	double xbins = h_map->GetNbinsX();//PixelID
	double ybins = h_map->GetNbinsY();//DepE
	//cout<<"Map Bins: xbins = "<<xbins<<"  ybins = "<<ybins<<endl;
	if( xbins!=h_sig->GetNbinsX() || ybins!=h_sig->GetNbinsY() ){
		cout<<"Error: Conflict of Bin Number between h_sig and h_map! "<<endl;
		exit(0);
	}

	double ftotalN_sig = 0;
	for(int ix=0; ix<xbins; ix++){
		for(int iy=0; iy<ybins; iy++){
			double frange0 = h_sig->GetYaxis()->GetBinLowEdge(iy+1);
			double frange1 = h_sig->GetYaxis()->GetBinLowEdge(iy+2);
			double frange = frange1 - frange0;
			double tmp_n = h_sig->GetBinContent(ix+1, iy+1);

			int fbin_n = int( tmp_n * farea * fsr * ftime * frange );
			ftotalN_sig = ftotalN_sig+fbin_n;
		}
	}


	int     tmp_totalNsig = 0;
	double  tmp_totalNmap = 0;

	double ChiSquare = 0;
	int    Dfreedom  = 0;
	for(int ix=0; ix<xbins; ix++){//PixelID
		double binN_sig = 0;
		double binN_map = 0;
		double binN_rec = 0;
		for(int iy=0; iy<ybins; iy++){//DepE Bins
			double frange0 = h_sig->GetYaxis()->GetBinLowEdge(iy+1);
			double frange1 = h_sig->GetYaxis()->GetBinLowEdge(iy+2);
			double frange = frange1 - frange0;
			double tmp_n = h_sig->GetBinContent(ix+1, iy+1);

			int    fsig_binN = int( tmp_n * farea * fsr * ftime * frange );
			double fmap_binN =     h_map->GetBinContent(ix+1,iy+1);

			binN_sig = binN_sig + fsig_binN;
			binN_map = binN_map + fmap_binN;

			tmp_totalNsig = tmp_totalNsig + fsig_binN;
			tmp_totalNmap = tmp_totalNmap + fmap_binN;
		}

		binN_rec = binN_map/ftotalN_map * ftotalN_sig;

		double pixelChiS = TMath::Power( binN_sig-binN_rec, 2) / (binN_rec);

		if(binN_rec>=5){
			ChiSquare = ChiSquare+pixelChiS;
			Dfreedom++;
			//cout
			//	<<"  PixelID = "<<ix
			//	<<"  binN_rec = "<<binN_rec<<"  binN_sig = "<<binN_sig
			//	<<"  ChiSquare = "<<ChiSquare<<"  Dfreedom = "<<Dfreedom
			//	<<endl;
		}
	}
	fDf = Dfreedom-1;

	//cout
	//	<<"  ftotalN_sig = "<<ftotalN_sig
	//	<<"  tmp_totalNsig = "<<tmp_totalNsig
	//	<<"  Chi/df = "<<ChiSquare/fDf
	//	<<endl;
	//cout<<"ftotalN_map = "<<ftotalN_map<<"  tmp_totalNmap = "<<tmp_totalNmap<<endl;

	return ChiSquare;
}

//------------------------------------------------------------
double AlgDataAction::GetPositionChiSquare2(TH2D* h_map, TH2D* h_sig, int& fDf, double ftime){
	double pi = TMath::Pi();
	double farea = 2.*pi*14.5*14.5/112.;
	double fsr   = 2.*pi;

	double xbins = h_map->GetNbinsX();//PixelID
	double ybins = h_map->GetNbinsY();//DepE
	//cout<<"Map Bins: xbins = "<<xbins<<"  ybins = "<<ybins<<endl;
	if( xbins!=h_sig->GetNbinsX() || ybins!=h_sig->GetNbinsY() ){
		cout<<"Error: Conflict of Bin Number between h_sig and h_map! "<<endl;
		exit(0);
	}

	double ftotalN_sig = 0;
	double ftotalN_map = 0;
	for(int ix=0; ix<xbins; ix++){
		for(int iy=0; iy<ybins; iy++){
			double frange0 = h_sig->GetYaxis()->GetBinLowEdge(iy+1);
			double frange1 = h_sig->GetYaxis()->GetBinLowEdge(iy+2);
			double frange = frange1 - frange0;
			double tmp_sign = h_sig->GetBinContent(ix+1, iy+1);
			double tmp_mapn = h_map->GetBinContent(ix+1, iy+1);

			int fbin_sign = int( tmp_sign * farea * fsr * ftime * frange );
			int fbin_mapn = int( tmp_mapn * farea * fsr * ftime * frange );
			ftotalN_sig = ftotalN_sig+fbin_sign;
			ftotalN_map = ftotalN_sig+fbin_sign;
		}
	}

	double ChiSquare = 0;
	int    Dfreedom  = 0;
	for(int ix=0; ix<xbins; ix++){//PixelID
		double binN_sig = 0;
		double binN_map = 0;
		double binN_rec = 0;
		for(int iy=0; iy<ybins; iy++){//DepE Bins
			double frange0  = h_sig->GetYaxis()->GetBinLowEdge(iy+1);
			double frange1  = h_sig->GetYaxis()->GetBinLowEdge(iy+2);
			double frange   = frange1 - frange0;
			double tmp_sign = h_sig->GetBinContent(ix+1, iy+1);
			double tmp_mapn = h_map->GetBinContent(ix+1, iy+1);

			int    fsig_binN = int( tmp_sign * farea * fsr * ftime * frange );
			int    fmap_binN = int( tmp_mapn * farea * fsr * ftime * frange );

			binN_sig = binN_sig + fsig_binN;
			binN_map = binN_map + fmap_binN;

		}

		binN_rec = binN_map/ftotalN_map * ftotalN_sig;

		double pixelChiS = TMath::Power( binN_sig-binN_rec, 2) / (binN_rec);

		if(binN_rec>=5){
			ChiSquare = ChiSquare+pixelChiS;
			Dfreedom++;
			//cout
			//	<<"  PixelID = "<<ix
			//	<<"  binN_rec = "<<binN_rec<<"  binN_sig = "<<binN_sig
			//	<<"  ChiSquare = "<<ChiSquare<<"  Dfreedom = "<<Dfreedom
			//	<<endl;
		}
	}
	fDf = Dfreedom-1;

	//cout
	//	<<"  ftotalN_sig = "<<ftotalN_sig
	//	<<"  Chi/df = "<<ChiSquare/fDf
	//	<<endl;

	return ChiSquare;
}

//------------------------------------------------------------
double AlgDataAction::GetPositionChiSquare2(
		TH2D* h_map, TH2D* h_sig, int& fDf, double ftime, double fStep){
	double pi = TMath::Pi();
	double farea = 2.*pi*14.5*14.5/112.;
	double fsr   = 2.*pi;

	double xbins = h_map->GetNbinsX();//PixelID
	double ybins = h_map->GetNbinsY();//DepE
	//cout<<"Map Bins: xbins = "<<xbins<<"  ybins = "<<ybins<<endl;
	if( xbins!=h_sig->GetNbinsX() || ybins!=h_sig->GetNbinsY() ){
		cout<<"Error: Conflict of Bin Number between h_sig and h_map! "<<endl;
		exit(0);
	}

	double ftotalN_sig = 0;
	double ftotalN_map = 0;
	for(int ix=0; ix<xbins; ix++){//Pixel ID
		for(int iy=0; iy<ybins; iy++){//Energy
			double frange0 = h_sig->GetYaxis()->GetBinLowEdge(iy+1);
			double frange1 = h_sig->GetYaxis()->GetBinLowEdge(iy+2);
			double frange = frange1 - frange0;
			double tmp_sign = h_sig->GetBinContent(ix+1, iy+1);
			double tmp_mapn = h_map->GetBinContent(ix+1, iy+1);

			int fbin_sign = int( tmp_sign * farea * fsr * ftime * frange );
			int fbin_mapn = int( tmp_mapn * farea * fsr * ftime * frange );

			ftotalN_sig = ftotalN_sig + fbin_sign;
			ftotalN_map = ftotalN_map + fbin_mapn;
		}
	}

	double ChiSquare = 0;
	int    Dfreedom  = 0;
	for(int it=0; it<90; it+=fStep ){
		for(int ip=0; ip<360; ip+=fStep ){
			vector<int> ftmpID;
			ftmpID.clear();

			for(int id=0; id<xbins; id++){
				double tmp_the = -1;
				double tmp_phi = -1;
				GetPixelThetaPhi( id, 0, tmp_the, tmp_phi );
				tmp_the = tmp_the/TMath::Pi()*180;
				tmp_phi = tmp_phi/TMath::Pi()*180;
				
				bool flag_T = false;
				bool flag_P = false;
				if( tmp_the>=it && tmp_the<(it+fStep) )
					flag_T = true;
				if( tmp_phi>=ip && tmp_phi<(ip+fStep) )
					flag_P = true;
				if( it==0 )	flag_P = true;

				if( flag_P && flag_T )
					ftmpID.push_back(id);
			}

			double IbinN_sig = 0;
			double DbinN_sig = 0;
			double IbinN_map = 0;
			double DbinN_map = 0;
			double binN_rec = 0;
			for(int vi=0; vi<ftmpID.size(); vi++){//Vector Loop 
				int ix = ftmpID[vi];

				for(int iy=0; iy<ybins; iy++){//DepE Bins
					double frange0 = h_sig->GetYaxis()->GetBinLowEdge(iy+1);
					double frange1 = h_sig->GetYaxis()->GetBinLowEdge(iy+2);
					double frange = frange1 - frange0;
					double tmp_sign = h_sig->GetBinContent(ix+1, iy+1);
					double tmp_mapn = h_map->GetBinContent(ix+1, iy+1);

					double Isig_binN = int( tmp_sign * farea * fsr * ftime * frange );
					double Dsig_binN = tmp_sign * farea * fsr * ftime * frange; 
					double Imap_binN = int( tmp_mapn * farea * fsr * ftime * frange ); 
					double Dmap_binN = tmp_mapn * farea * fsr * ftime * frange; 
					double fmap_binN = h_map->GetBinContent(ix+1,iy+1);

					IbinN_sig = IbinN_sig + Isig_binN;
					DbinN_sig = DbinN_sig + Dsig_binN;
					IbinN_map = IbinN_map + Imap_binN;
					DbinN_map = DbinN_map + Dmap_binN;

				}
			}

			binN_rec = IbinN_map/ftotalN_map * ftotalN_sig;
			double pixelChiS = TMath::Power( IbinN_sig-binN_rec, 2) / (binN_rec);

			if(binN_rec>=5){
				ChiSquare = ChiSquare+pixelChiS;
				Dfreedom++;
			}
			if(it==0) break;
		}//Loop for Phi
	}//Loop for The
	fDf = Dfreedom-1;

	//cout
	//	<<"  ftotalN_sig = "<<ftotalN_sig
	//	<<"  Chi/df = "<<ChiSquare/fDf
	//	<<endl;

	return ChiSquare;
}

//------------------------------------------------------------
double AlgDataAction::GetPositionChiSquare(TH2D* h_map, TH2D* h_sig, int& fDf, double ftime, double fStep){
	double pi = TMath::Pi();
	double farea = 2.*pi*14.5*14.5/112.;
	double fsr   = 2.*pi;

	TH1D* h_mapY = h_map->ProjectionY();
	double ftotalN_map = 0;
	//cout<<"DepENbins_Map = "<<h_mapY->GetNbinsX()<<endl;
	for(int i=0; i<h_mapY->GetNbinsX(); i++){
		ftotalN_map = ftotalN_map + h_mapY->GetBinContent(i+1);
		//cout<<"Content["<<i<<"] = "<<h_mapY->GetBinContent(i+1)<<endl;
	}
	//cout<<"\n\n\n"<<endl;

	double xbins = h_map->GetNbinsX();//PixelID
	double ybins = h_map->GetNbinsY();//DepE
	//cout<<"Map Bins: xbins = "<<xbins<<"  ybins = "<<ybins<<endl;
	if( xbins!=h_sig->GetNbinsX() || ybins!=h_sig->GetNbinsY() ){
		cout<<"Error: Conflict of Bin Number between h_sig and h_map! "<<endl;
		exit(0);
	}

	double ftotalN_sig = 0;
	for(int ix=0; ix<xbins; ix++){
		for(int iy=0; iy<ybins; iy++){
			double frange0 = h_sig->GetYaxis()->GetBinLowEdge(iy+1);
			double frange1 = h_sig->GetYaxis()->GetBinLowEdge(iy+2);
			double frange = frange1 - frange0;
			double tmp_n = h_sig->GetBinContent(ix+1, iy+1);

			int fbin_n = int( tmp_n * farea * fsr * ftime * frange );
			ftotalN_sig = ftotalN_sig+fbin_n;
		}
	}


	int     tmp_totalNsig = 0;
	double  tmp_totalNmap = 0;

	double ChiSquare = 0;
	int    Dfreedom  = 0;

	for(int it=0; it<=90; it+=fStep ){
		for(int ip=0; ip<=360; ip+=fStep ){
			vector<int> ftmpID;
			ftmpID.clear();

			for(int id=0; id<xbins; id++){
				double tmp_the = -1;
				double tmp_phi = -1;
				GetPixelThetaPhi( id, 0, tmp_the, tmp_phi );
				tmp_the = tmp_the/TMath::Pi()*180;
				tmp_phi = tmp_phi/TMath::Pi()*180;
				
				bool flag_T = false;
				bool flag_P = false;
				if( tmp_the>=it && tmp_the<(it+fStep) )
					flag_T = true;
				if( tmp_phi>=ip && tmp_phi<(ip+fStep) )
					flag_P = true;
				if( it==0 )	flag_P = true;

				if( flag_P && flag_T )
					ftmpID.push_back(id);
			}

			double binN_sig = 0;
			double binN_map = 0;
			double binN_rec = 0;
			for(int vi=0; vi<ftmpID.size(); vi++){//Vector Loop 
				int ix = ftmpID[vi];

				for(int iy=0; iy<ybins; iy++){//DepE Bins
					double frange0 = h_sig->GetYaxis()->GetBinLowEdge(iy+1);
					double frange1 = h_sig->GetYaxis()->GetBinLowEdge(iy+2);
					double frange = frange1 - frange0;
					double tmp_n = h_sig->GetBinContent(ix+1, iy+1);

					int    fsig_binN = int( tmp_n * farea * fsr * ftime * frange );
					double fmap_binN =     h_map->GetBinContent(ix+1,iy+1);

					binN_sig = binN_sig + fsig_binN;
					binN_map = binN_map + fmap_binN;

					tmp_totalNsig = tmp_totalNsig + fsig_binN;
					tmp_totalNmap = tmp_totalNmap + fmap_binN;
				}
			}

			binN_rec = binN_map/ftotalN_map * ftotalN_sig;
			double pixelChiS = TMath::Power( binN_sig-binN_rec, 2) / (binN_rec);

			if(binN_rec>=5){
				ChiSquare = ChiSquare+pixelChiS;
				Dfreedom++;
				//cout
				//	<<"  PixelID = "<<ix
				//	<<"  binN_rec = "<<binN_rec<<"  binN_sig = "<<binN_sig
				//	<<"  ChiSquare = "<<ChiSquare<<"  Dfreedom = "<<Dfreedom
				//	<<endl;
			}
			if(it==0) break;
		}//Loop for Phi
	}//Loop for The
	fDf = Dfreedom-1;

	//cout
	//	<<"  ftotalN_sig = "<<ftotalN_sig
	//	<<"  tmp_totalNsig = "<<tmp_totalNsig
	//	<<"  Chi/df = "<<ChiSquare/fDf
	//	<<endl;
	//cout<<"ftotalN_map = "<<ftotalN_map<<"  tmp_totalNmap = "<<tmp_totalNmap<<endl;

	return ChiSquare;
}

//------------------------------------------------------------
double AlgDataAction::GetPositionChiSquare2(
		TH2D* h_map, TH2D* h_sig, TH1D*& h1_mapN, TH1D*& h1_sigN, int& fDf, double ftime, double fStep){
	double pi = TMath::Pi();
	double farea = 2.*pi*14.5*14.5/112.;
	double fsr   = 2.*pi;

	double xbins = h_map->GetNbinsX();//PixelID
	double ybins = h_map->GetNbinsY();//DepE
	//cout<<"Map Bins: xbins = "<<xbins<<"  ybins = "<<ybins<<endl;
	if( xbins!=h_sig->GetNbinsX() || ybins!=h_sig->GetNbinsY() ){
		cout<<"Error: Conflict of Bin Number between h_sig and h_map! "<<endl;
		exit(0);
	}

	int MergeN = (90/fStep-1)*(360/fStep)+1;
	cout<<"MergeN = "<<MergeN<<endl;
	double* binRangeX = new double[ MergeN+1 ];
	for(int i=0; i<MergeN+1; i++)
		binRangeX[i] = i+0.5;
	h1_mapN->SetBins( MergeN, binRangeX );
	h1_sigN->SetBins( MergeN, binRangeX );
	delete [] binRangeX; binRangeX = NULL;

	double ftotalN_sig = 0;
	double ftotalN_map = 0;
	for(int ix=0; ix<xbins; ix++){//Pixel ID
		for(int iy=0; iy<ybins; iy++){//Energy
			double frange0 = h_sig->GetYaxis()->GetBinLowEdge(iy+1);
			double frange1 = h_sig->GetYaxis()->GetBinLowEdge(iy+2);
			double frange = frange1 - frange0;
			double tmp_sign = h_sig->GetBinContent(ix+1, iy+1);
			double tmp_mapn = h_map->GetBinContent(ix+1, iy+1);

			int fbin_sign = int( tmp_sign * farea * fsr * ftime * frange );
			int fbin_mapn = int( tmp_mapn * farea * fsr * ftime * frange );

			ftotalN_sig = ftotalN_sig + fbin_sign;
			ftotalN_map = ftotalN_map + fbin_mapn;
		}
	}

	double ChiSquare = 0;
	int    Dfreedom  = 0;
	int    Grid_i = 0;
	for(int it=0; it<90; it+=fStep ){
		for(int ip=0; ip<360; ip+=fStep ){
			vector<int> ftmpID;
			ftmpID.clear();

			for(int id=0; id<xbins; id++){
				double tmp_the = -1;
				double tmp_phi = -1;
				GetPixelThetaPhi( id, 0, tmp_the, tmp_phi );
				tmp_the = tmp_the/TMath::Pi()*180;
				tmp_phi = tmp_phi/TMath::Pi()*180;
				
				bool flag_T = false;
				bool flag_P = false;
				if( tmp_the>=it && tmp_the<(it+fStep) )
					flag_T = true;
				if( tmp_phi>=ip && tmp_phi<(ip+fStep) )
					flag_P = true;
				if( it==0 )	flag_P = true;

				if( flag_P && flag_T )
					ftmpID.push_back(id);
			}

			double IbinN_sig = 0;
			double DbinN_sig = 0;
			double IbinN_map = 0;
			double DbinN_map = 0;
			double binN_rec = 0;
			for(int vi=0; vi<ftmpID.size(); vi++){//Vector Loop 
				int ix = ftmpID[vi];

				for(int iy=0; iy<ybins; iy++){//DepE Bins
					double frange0 = h_sig->GetYaxis()->GetBinLowEdge(iy+1);
					double frange1 = h_sig->GetYaxis()->GetBinLowEdge(iy+2);
					double frange = frange1 - frange0;
					double tmp_sign = h_sig->GetBinContent(ix+1, iy+1);
					double tmp_mapn = h_map->GetBinContent(ix+1, iy+1);

					double Isig_binN = int( tmp_sign * farea * fsr * ftime * frange );
					double Dsig_binN = tmp_sign * farea * fsr * ftime * frange; 
					double Imap_binN = int( tmp_mapn * farea * fsr * ftime * frange ); 
					double Dmap_binN = tmp_mapn * farea * fsr * ftime * frange; 
					double fmap_binN = h_map->GetBinContent(ix+1,iy+1);

					IbinN_sig = IbinN_sig + Isig_binN;
					DbinN_sig = DbinN_sig + Dsig_binN;
					IbinN_map = IbinN_map + Imap_binN;
					DbinN_map = DbinN_map + Dmap_binN;

				}
			}

			binN_rec = IbinN_map/ftotalN_map * ftotalN_sig;
			double pixelChiS = TMath::Power( IbinN_sig-binN_rec, 2) / (binN_rec);
			h1_mapN->SetBinContent( Grid_i+1, binN_rec );
			h1_sigN->SetBinContent( Grid_i+1, DbinN_sig );
			Grid_i++;

			if(binN_rec>=5){
				ChiSquare = ChiSquare+pixelChiS;
				Dfreedom++;
			}
			if(it==0) break;
		}//Loop for Phi
	}//Loop for The
	cout
		<<"  Grid_i = "<<Grid_i
		<<"  MergeN = "<<MergeN
		<<endl;
	fDf = Dfreedom-1;

	//cout
	//	<<"  ftotalN_sig = "<<ftotalN_sig
	//	<<"  Chi/df = "<<ChiSquare/fDf
	//	<<endl;

	return ChiSquare;
}

//------------------------------------------------------------
double AlgDataAction::GetPositionChiSquare(
		TH2D* h_map, TH2D* h_sig, TH1D*& h1_mapN, TH1D*& h1_sigN, int& fDf, double ftime, double fStep){
	double pi = TMath::Pi();
	double farea = 2.*pi*14.5*14.5/112.;
	double fsr   = 2.*pi;

	TH1D* h_mapY = h_map->ProjectionY();
	double ftotalN_map = 0;
	//cout<<"DepENbins_Map = "<<h_mapY->GetNbinsX()<<endl;
	for(int i=0; i<h_mapY->GetNbinsX(); i++){
		ftotalN_map = ftotalN_map + h_mapY->GetBinContent(i+1);
		//cout<<"Content["<<i<<"] = "<<h_mapY->GetBinContent(i+1)<<endl;
	}
	//cout<<"\n\n\n"<<endl;

	double xbins = h_map->GetNbinsX();//PixelID
	double ybins = h_map->GetNbinsY();//DepE
	//cout<<"Map Bins: xbins = "<<xbins<<"  ybins = "<<ybins<<endl;
	if( xbins!=h_sig->GetNbinsX() || ybins!=h_sig->GetNbinsY() ){
		cout<<"Error: Conflict of Bin Number between h_sig and h_map! "<<endl;
		exit(0);
	}

	int MergeN = (90/fStep-1)*(360/fStep)+1;
	cout<<"MergeN = "<<MergeN<<endl;
	double* binRangeX = new double[ MergeN+1 ];
	for(int i=0; i<MergeN+1; i++)
		binRangeX[i] = i+0.5;
	h1_mapN->SetBins( MergeN, binRangeX );
	h1_sigN->SetBins( MergeN, binRangeX );
	delete [] binRangeX; binRangeX = NULL;

	double ftotalN_sig = 0;
	for(int ix=0; ix<xbins; ix++){//Pixel ID
		for(int iy=0; iy<ybins; iy++){//Energy
			double frange0 = h_sig->GetYaxis()->GetBinLowEdge(iy+1);
			double frange1 = h_sig->GetYaxis()->GetBinLowEdge(iy+2);
			double frange = frange1 - frange0;
			double tmp_n = h_sig->GetBinContent(ix+1, iy+1);

			int fbin_n = int( tmp_n * farea * fsr * ftime * frange );
			ftotalN_sig = ftotalN_sig+fbin_n;
		}
	}

	int     tmp_totalNsig = 0;
	double  tmp_totalNmap = 0;

	double ChiSquare = 0;
	int    Dfreedom  = 0;
	int    Grid_i = 0;
	for(int it=0; it<90; it+=fStep ){
		for(int ip=0; ip<360; ip+=fStep ){
			vector<int> ftmpID;
			ftmpID.clear();

			for(int id=0; id<xbins; id++){
				double tmp_the = -1;
				double tmp_phi = -1;
				GetPixelThetaPhi( id, 0, tmp_the, tmp_phi );
				tmp_the = tmp_the/TMath::Pi()*180;
				tmp_phi = tmp_phi/TMath::Pi()*180;
				
				bool flag_T = false;
				bool flag_P = false;
				if( tmp_the>=it && tmp_the<(it+fStep) )
					flag_T = true;
				if( tmp_phi>=ip && tmp_phi<(ip+fStep) )
					flag_P = true;
				if( it==0 )	flag_P = true;

				if( flag_P && flag_T )
					ftmpID.push_back(id);
			}

			double IbinN_sig = 0;
			double DbinN_sig = 0;
			double binN_map = 0;
			double binN_rec = 0;
			for(int vi=0; vi<ftmpID.size(); vi++){//Vector Loop 
				int ix = ftmpID[vi];

				for(int iy=0; iy<ybins; iy++){//DepE Bins
					double frange0 = h_sig->GetYaxis()->GetBinLowEdge(iy+1);
					double frange1 = h_sig->GetYaxis()->GetBinLowEdge(iy+2);
					double frange = frange1 - frange0;
					double tmp_n = h_sig->GetBinContent(ix+1, iy+1);

					double Isig_binN = int( tmp_n * farea * fsr * ftime * frange );
					double Dsig_binN = tmp_n * farea * fsr * ftime * frange; 
					double fmap_binN = h_map->GetBinContent(ix+1,iy+1);

					IbinN_sig = IbinN_sig + Isig_binN;
					DbinN_sig = DbinN_sig + Dsig_binN;
					binN_map = binN_map + fmap_binN;

					tmp_totalNsig = tmp_totalNsig + Isig_binN;
					tmp_totalNmap = tmp_totalNmap + fmap_binN;
				}
			}

			binN_rec = binN_map/ftotalN_map * ftotalN_sig;
			double pixelChiS = TMath::Power( IbinN_sig-binN_rec, 2) / (binN_rec);
			h1_mapN->SetBinContent( Grid_i+1, binN_rec );
			h1_sigN->SetBinContent( Grid_i+1, DbinN_sig );
			Grid_i++;

			if(binN_rec>=5){
				ChiSquare = ChiSquare+pixelChiS;
				Dfreedom++;
			}
			if(it==0) break;
		}//Loop for Phi
	}//Loop for The
	cout
		<<"  Grid_i = "<<Grid_i
		<<"  MergeN = "<<MergeN
		<<endl;
	fDf = Dfreedom-1;

	//cout
	//	<<"  ftotalN_sig = "<<ftotalN_sig
	//	<<"  tmp_totalNsig = "<<tmp_totalNsig
	//	<<"  Chi/df = "<<ChiSquare/fDf
	//	<<endl;
	//cout<<"ftotalN_map = "<<ftotalN_map<<"  tmp_totalNmap = "<<tmp_totalNmap<<endl;

	return ChiSquare;
}

//------------------------------------------------------------
double AlgDataAction::GetPositionChiSquare(
		TH2D* h_map, TH2D* h_sig, TH1D*& h1_mapN, TH1D*& h1_sigN, int& fDf, double ftime){
	double pi = TMath::Pi();
	double farea = 2.*pi*14.5*14.5/112.;
	double fsr   = 2.*pi;

	TH1D* h_mapY = h_map->ProjectionY();
	double ftotalN_map = 0;
	//cout<<"DepENbins_Map = "<<h_mapY->GetNbinsX()<<endl;
	for(int i=0; i<h_mapY->GetNbinsX(); i++){
		ftotalN_map = ftotalN_map + h_mapY->GetBinContent(i+1);
		//cout<<"Content["<<i<<"] = "<<h_mapY->GetBinContent(i+1)<<endl;
	}
	//cout<<"\n\n\n"<<endl;

	int  xbins = h_map->GetNbinsX();//PixelID
	int  ybins = h_map->GetNbinsY();//DepE
	//cout<<"Map Bins: xbins = "<<xbins<<"  ybins = "<<ybins<<endl;
	if( xbins!=h_sig->GetNbinsX() || ybins!=h_sig->GetNbinsY() ){
		cout<<"Error: Conflict of Bin Number between h_sig and h_map! "<<endl;
		exit(0);
	}

	double* binRangeX = new double[xbins+1];
	for(int i=0; i<xbins+1; i++)
		binRangeX[i] = h_sig->GetXaxis()->GetBinLowEdge(i+1);
	h1_mapN->SetBins(xbins, binRangeX);
	h1_sigN->SetBins(xbins, binRangeX);
	delete [] binRangeX; binRangeX = NULL;

	double ftotalN_sig = 0;
	for(int ix=0; ix<xbins; ix++){
		for(int iy=0; iy<ybins; iy++){
			double frange0 = h_sig->GetYaxis()->GetBinLowEdge(iy+1);
			double frange1 = h_sig->GetYaxis()->GetBinLowEdge(iy+2);
			double frange = frange1 - frange0;
			double tmp_n = h_sig->GetBinContent(ix+1, iy+1);

			int fbin_n = int( tmp_n * farea * fsr * ftime * frange );
			ftotalN_sig = ftotalN_sig+fbin_n;
		}
	}


	int     tmp_totalNsig = 0;
	double  tmp_totalNmap = 0;

	double ChiSquare = 0;
	int    Dfreedom  = 0;
	for(int ix=0; ix<xbins; ix++){//PixelID
		double IbinN_sig = 0;
		double DbinN_sig = 0;
		double binN_map = 0;
		double binN_rec = 0;
		for(int iy=0; iy<ybins; iy++){//DepE Bins
			double frange0 = h_sig->GetYaxis()->GetBinLowEdge(iy+1);
			double frange1 = h_sig->GetYaxis()->GetBinLowEdge(iy+2);
			double frange = frange1 - frange0;
			double tmp_n = h_sig->GetBinContent(ix+1, iy+1);

			double Isig_binN = int( tmp_n * farea * fsr * ftime * frange );
			double Dsig_binN = tmp_n * farea * fsr * ftime * frange; 
			double fmap_binN =     h_map->GetBinContent(ix+1,iy+1);

			IbinN_sig = IbinN_sig + Isig_binN;
			DbinN_sig = DbinN_sig + Dsig_binN;
			binN_map = binN_map + fmap_binN;

			tmp_totalNsig = tmp_totalNsig + Isig_binN;
			tmp_totalNmap = tmp_totalNmap + fmap_binN;
		}

		binN_rec = binN_map/ftotalN_map * ftotalN_sig;

		double pixelChiS = TMath::Power( IbinN_sig-binN_rec, 2) / (binN_rec);
		h1_mapN->SetBinContent(ix+1, binN_rec);
		h1_sigN->SetBinContent(ix+1, DbinN_sig);

		if(binN_rec>=5){
			ChiSquare = ChiSquare+pixelChiS;
			Dfreedom++;
			//cout
			//	<<"  PixelID = "<<ix
			//	<<"  binN_rec = "<<binN_rec<<"  IbinN_sig = "<<IbinN_sig
			//	<<"  ChiSquare = "<<ChiSquare<<"  Dfreedom = "<<Dfreedom
			//	<<endl;
		}
	}
	fDf = Dfreedom-1;

	cout
		<<"  ftotalN_sig = "<<ftotalN_sig
		<<"  tmp_totalNsig = "<<tmp_totalNsig
		<<"  Chi/df = "<<ChiSquare/fDf
		<<endl;
	//cout<<"ftotalN_map = "<<ftotalN_map<<"  tmp_totalNmap = "<<tmp_totalNmap<<endl;

	return ChiSquare;
}

//------------------------------------------------------------
double AlgDataAction::GetPositionChiSquare2(
		TH2D* h_map, TH2D* h_sig, TH1D*& h1_mapN, TH1D*& h1_sigN, int& fDf, double ftime){
	double pi = TMath::Pi();
	double farea = 2.*pi*14.5*14.5/112.;
	double fsr   = 2.*pi;

	int  xbins = h_map->GetNbinsX();//PixelID
	int  ybins = h_map->GetNbinsY();//DepE
	//cout<<"Map Bins: xbins = "<<xbins<<"  ybins = "<<ybins<<endl;
	if( xbins!=h_sig->GetNbinsX() || ybins!=h_sig->GetNbinsY() ){
		cout<<"Error: Conflict of Bin Number between h_sig and h_map! "<<endl;
		exit(0);
	}

	double* binRangeX = new double[xbins+1];
	for(int i=0; i<xbins+1; i++)
		binRangeX[i] = h_sig->GetXaxis()->GetBinLowEdge(i+1);
	h1_mapN->SetBins(xbins, binRangeX);
	h1_sigN->SetBins(xbins, binRangeX);
	delete [] binRangeX; binRangeX = NULL;

	double ftotalN_sig = 0;
	double ftotalN_map = 0;
	for(int ix=0; ix<xbins; ix++){
		for(int iy=0; iy<ybins; iy++){
			double frange0 = h_sig->GetYaxis()->GetBinLowEdge(iy+1);
			double frange1 = h_sig->GetYaxis()->GetBinLowEdge(iy+2);
			double frange = frange1 - frange0;
			double tmp_sign = h_sig->GetBinContent(ix+1, iy+1);
			double tmp_mapn = h_map->GetBinContent(ix+1, iy+1);

			int fbin_sign = int( tmp_sign * farea * fsr * ftime * frange );
			int fbin_mapn = int( tmp_mapn * farea * fsr * ftime * frange );
			ftotalN_sig = ftotalN_sig+fbin_sign;
			ftotalN_map = ftotalN_map+fbin_mapn;
		}
	}


	double ChiSquare = 0;
	int    Dfreedom  = 0;
	for(int ix=0; ix<xbins; ix++){//PixelID
		double IbinN_sig = 0;
		double DbinN_sig = 0;
		double IbinN_map = 0;
		double DbinN_map = 0;
		double binN_rec = 0;
		for(int iy=0; iy<ybins; iy++){//DepE Bins
			double frange0 = h_sig->GetYaxis()->GetBinLowEdge(iy+1);
			double frange1 = h_sig->GetYaxis()->GetBinLowEdge(iy+2);
			double frange = frange1 - frange0;
			double tmp_sign = h_sig->GetBinContent(ix+1, iy+1);
			double tmp_mapn = h_map->GetBinContent(ix+1, iy+1);

			double Isig_binN = int( tmp_sign * farea * fsr * ftime * frange );
			double Dsig_binN = tmp_sign * farea * fsr * ftime * frange; 
			double Imap_binN = int( tmp_mapn * farea * fsr * ftime * frange );
			double Dmap_binN = tmp_mapn * farea * fsr * ftime * frange; 

			IbinN_sig = IbinN_sig + Isig_binN;
			DbinN_sig = DbinN_sig + Dsig_binN;
			IbinN_map = IbinN_map + Imap_binN;
			DbinN_map = DbinN_map + Dmap_binN;

		}

		//binN_rec = DbinN_map/ftotalN_map * ftotalN_sig;
		binN_rec = IbinN_map/ftotalN_map * ftotalN_sig;

		double pixelChiS = TMath::Power( IbinN_sig-binN_rec, 2) / (binN_rec);
		h1_mapN->SetBinContent(ix+1, binN_rec);
		h1_sigN->SetBinContent(ix+1, DbinN_sig);

		if(binN_rec>=5){
			ChiSquare = ChiSquare+pixelChiS;
			Dfreedom++;
			//cout
			//	<<"  PixelID = "<<ix
			//	<<"  binN_rec = "<<binN_rec<<"  IbinN_sig = "<<IbinN_sig
			//	<<"  ChiSquare = "<<ChiSquare<<"  Dfreedom = "<<Dfreedom
			//	<<endl;
		}
	}
	fDf = Dfreedom-1;

	cout
		<<"  ftotalN_sig = "<<ftotalN_sig
		<<"  Chi/df = "<<ChiSquare/fDf
		<<endl;

	return ChiSquare;
}

//------------------------------------------------------------
void AlgDataAction::SigmaContour( double Nsig, TH2D*& h2_chi, TH2D*& h2_df, TH2D*& h2_chiInSig){

	int xbins = h2_chi->GetNbinsX();
	int ybins = h2_chi->GetNbinsY();
	double* binRangeX = new double[xbins+1];
	double* binRangeY = new double[ybins+1];
	for(int i=0; i<xbins+1; i++)
		binRangeX[i] = h2_chi->GetXaxis()->GetBinLowEdge(i+1);
	for(int i=0; i<ybins+1; i++)
		binRangeY[i] = h2_chi->GetYaxis()->GetBinLowEdge(i+1);
	h2_chiInSig->SetBins(xbins, binRangeX, ybins, binRangeY);

	int minX = -1; 
	int minY = -1;
	double minChi = 9000000;
	double minDf  = -1;
	for(int ix=0; ix<xbins; ix++){
		for(int iy=0; iy<ybins; iy++){
			double fbin_n = h2_chi->GetBinContent(ix+1, iy+1);
			double fdf    = h2_df ->GetBinContent(ix+1, iy+1);
			if( fdf<=0 ){
				cout<<"fdf = "<<fdf<<endl;
			}
			if(fbin_n<minChi){
				minChi = fbin_n;
				minDf  = fdf;
				minX = ix;
				minY = iy;
			}
		}
	}

	double fsig = TMath::Sqrt(2*minDf);
	double fmea = (minChi-minDf)/TMath::Sqrt(2*minDf);
	for(int ix=0; ix<xbins; ix++){
		for(int iy=0; iy<ybins; iy++){
			double fbin_n = h2_chi->GetBinContent(ix+1, iy+1);
			double fdf    = h2_df ->GetBinContent(ix+1, iy+1);
			if( fdf<=0 ){
				cout<<"fdf = "<<fdf<<endl;
			}

			double tmp = (fbin_n-fdf)/TMath::Sqrt(2*fdf);
			cout
				<<" the = "<<h2_chi->GetXaxis()->GetBinCenter(ix+1)
				<<" phi = "<<h2_chi->GetYaxis()->GetBinCenter(iy+1)
				<<" chi = "<<fbin_n
				<<" df = "<<fdf
				<<" sigN = "<<Nsig
				<<" fsig = "<<fsig
				<<" fmea = "<<fmea
				<<"  minDf = "<<minDf
				<<"  minChi = "<<minChi
				<<endl;

			//if( tmp < (fmea + Nsig*fsig) ){
			if( tmp < Nsig ){
				h2_chiInSig->SetBinContent(ix+1, iy+1, fbin_n);
			}
		}
	}



	delete [] binRangeX; binRangeX = NULL;
	delete [] binRangeY; binRangeY = NULL;
}

//------------------------------------------------------------
void AlgDataAction::SigmaContour( TH2D*& h2_chi, TH2D*& h2_df, TH2D*& h2_chiInSig, double fsig ){

	int xbins = h2_chi->GetNbinsX();
	int ybins = h2_chi->GetNbinsY();
	double* binRangeX = new double[xbins+1];
	double* binRangeY = new double[ybins+1];
	for(int i=0; i<xbins+1; i++)
		binRangeX[i] = h2_chi->GetXaxis()->GetBinLowEdge(i+1);
	for(int i=0; i<ybins+1; i++)
		binRangeY[i] = h2_chi->GetYaxis()->GetBinLowEdge(i+1);
	h2_chiInSig->SetBins(xbins, binRangeX, ybins, binRangeY);

	double flimit = h2_chi->GetMinimum() + fsig;
	//double flimit = fsig;
	for(int ix=0; ix<xbins; ix++){
		for(int iy=0; iy<ybins; iy++){
			double fbin_n = h2_chi->GetBinContent(ix+1, iy+1);
			double fdf    = h2_df ->GetBinContent(ix+1, iy+1);
			if( fdf<=0 ){
				cout<<"fdf = "<<fdf<<endl;
			}
			double fprob  = TMath::Prob(fbin_n, int(fdf) );
			cout
				<<" the = "<<h2_chi->GetXaxis()->GetBinCenter(ix+1)
				<<" phi = "<<h2_chi->GetYaxis()->GetBinCenter(iy+1)
				<<" chi = "<<fbin_n
				<<" df = "<<fdf
				<<" fprob = "<<fprob
				<<endl;

			//if( fbin_n < flimit )
			h2_chiInSig->SetBinContent(ix+1, iy+1, fprob);
		}
	}

	delete [] binRangeX; binRangeX = NULL;
	delete [] binRangeY; binRangeY = NULL;
}

//------------------------------------------------------------
void AlgDataAction::SigmaContour( TH2D*& h2_chi, TH2D*& h2_chiInSig, double fsig ){

	int xbins = h2_chi->GetNbinsX();
	int ybins = h2_chi->GetNbinsY();
	double* binRangeX = new double[xbins+1];
	double* binRangeY = new double[ybins+1];
	for(int i=0; i<xbins+1; i++)
		binRangeX[i] = h2_chi->GetXaxis()->GetBinLowEdge(i+1);
	for(int i=0; i<ybins+1; i++)
		binRangeY[i] = h2_chi->GetYaxis()->GetBinLowEdge(i+1);
	h2_chiInSig->SetBins(xbins, binRangeX, ybins, binRangeY);

	double flimit = h2_chi->GetMinimum() + fsig;
	//double flimit = fsig;
	for(int ix=0; ix<xbins; ix++){
		for(int iy=0; iy<ybins; iy++){
			double fbin_n = h2_chi->GetBinContent(ix+1, iy+1);

			if( fbin_n < flimit )
				h2_chiInSig->SetBinContent(ix+1, iy+1, fbin_n);
		}
	}

	delete [] binRangeX; binRangeX = NULL;
	delete [] binRangeY; binRangeY = NULL;
}

//------------------------------------------------------------
void AlgDataAction::GetEffectiveArea( TH1D*& h1_eff, TH2D* h2_cut0, TH1D* h1_cut1, double& fSourceArea){

	if( h1_eff==NULL||h2_cut0==NULL||h1_cut1==NULL ){
		cout<<"Error in GetEffectiveArea(): Pointer is NULL!!!"<<endl;
		exit(0);
	}
	int xbins = h1_cut1->GetNbinsX();
	double* binRangeX = new double[xbins+1];
	for(int i=0; i<xbins+1; i++){
		binRangeX[i] = h1_cut1->GetXaxis()->GetBinLowEdge(i+1);
	}
	h1_eff->SetBins( xbins, binRangeX );

	TH1D* h1_projectX0 = h2_cut0->ProjectionX();

	for(int i=0; i<xbins; i++){
		double binC = h1_projectX0->GetBinCenter(i+1);
		double n = h1_projectX0->GetBinContent(i+1);
		//double N = h1_projectX1->GetBinContent(i+1);
		double N = h1_cut1->GetBinContent(i+1);
		double fEffArea = 0;

		if(N==0){
			cout<<"Warning in GetEffectiveArea(): Denominator N is 0!!!"<<endl;
		}
		else{
			fEffArea = n/N * fSourceArea;
		}
		h1_eff->SetBinContent( i+1,fEffArea );
		cout
			<<"  n = "<<n
			<<"  N = "<<N
			<<"  fSourceArea = "<<fSourceArea
			<<"  fEffArea = "<<fEffArea
			<<"  binCenter = "<<binC
			<<endl;

	}

	delete [] binRangeX; binRangeX = NULL;
}
void AlgDataAction::GetEffeciency( TH1D*& h1_eff, TH2D* h2_cut0, TH1D* h1_cut1){

    if( h1_eff==NULL||h2_cut0==NULL||h1_cut1==NULL ){
        cout<<"Error in GetEffectiveArea(): Pointer is NULL!!!"<<endl;
        exit(0);
    }
    int xbins = h1_cut1->GetNbinsX();
    double* binRangeX = new double[xbins+1];
    for(int i=0; i<xbins+1; i++){
        binRangeX[i] = h1_cut1->GetXaxis()->GetBinLowEdge(i+1);
    }
    h1_eff->SetBins( xbins, binRangeX );

    TH1D* h1_projectX0 = h2_cut0->ProjectionX();

    for(int i=0; i<xbins; i++){
        double binC = h1_projectX0->GetBinCenter(i+1);
        double n = h1_projectX0->GetBinContent(i+1);
        //double N = h1_projectX1->GetBinContent(i+1);
        double N = h1_cut1->GetBinContent(i+1);
        double fEffArea = 0;

        if(N==0){
            cout<<"Warning in GetEffectiveArea(): Denominator N is 0!!!"<<endl;
        }
        else{
            fEffArea = n/N;
        }
        h1_eff->SetBinContent( i+1,fEffArea );
        cout
            <<"  n = "<<n
            <<"  N = "<<N
       //     <<"  fSourceArea = "<<fSourceArea
            <<"  fEffArea = "<<fEffArea
            <<"  binCenter = "<<binC
            <<endl;

    }

    delete [] binRangeX; binRangeX = NULL;
}

//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
