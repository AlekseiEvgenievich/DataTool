// **************************************************************
//
//      ------ AlgDataAction.hh  ------
//           by Aleksei (11 Nov 2024)
//        
//
// **************************************************************

#ifndef AlgDataAction_h 
#define AlgDataAction_h 1

#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TFile.h"
#include "TMath.h"
#include "TGraph.h"
#include "string.h"
#include "TTree.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

const int nPixel=3;
class AlgDataAction
{
	public:
	//	AlgDataAction(bool fReadPosPar = false);
	//	AlgDataAction(string fname, bool fReadPosPar = false);
        AlgDataAction();
        AlgDataAction(string fname);
		~AlgDataAction();

	//	void ResetRun(bool fReadPosPar);
        void ResetRun();
		bool ResetEvent(int evti);
		static AlgDataAction* getInstance(string fname); 
		static AlgDataAction* getInstance(); 

		void ReadPixelPosition();

		inline int		 GetNPixel(){return nPixel;};
		inline int		 GetTagEventReset(){return fTagEvtReset;};
		inline int     GetEventNumber(){return TotalEvtNum;};
		inline int     GetInteraction(){return fInteraction;};
		inline int     GetEvtInFOV(){return fEvtInFOV;};
		inline double  GetTotalEnergy(){return TotalDepEnergy;};
		inline double  GetStructureEdep(){return StrucEdep;};
		inline int     GetMaxEID(int i){return MaxEID[i];};
		inline int*    GetMaxEID(){return MaxEID;};
		inline double  GetTotalEdep(int i){return TotalEdep[i];};
		inline double* GetTotalEdep(){return TotalEdep;};

		inline double  GetTotalEdepOfUpACD(){return TotalEdep[0]; };
		inline double  GetTotalEdepOfCAL(){return (TotalEdep[1]+TotalEdep[2]);};
		inline double  GetTotalEdepOfUpCAL(){return TotalEdep[1];};
		inline double  GetTotalEdepOfDownCAL(){return TotalEdep[2];};
//		inline double  GetTotalEdepOfBottomACD(){ return TotalEdep[3];};

		inline float   GetTotalDelayEdep(){return TotalPriEdep_Delay; };
		inline float   GetTotalDelayEdepOfCAL(){return TotalPriEdepCAL_Delay; };
		inline float   GetTotalDelayEdepOfUpACD(){return TotalPriEdepACD_Delay; };
	//	inline float   GetTotalDelayEdepOfBottomACD(){return TotalPriEdepBottomACD_Delay;};

		inline float  GetPrimaryEdepOfUpACD(){return TotalPriEdep[0]; };
		inline float  GetPrimaryEdepOfCAL(){return (TotalPriEdep[1]+TotalPriEdep[2]);};
//		inline float  GetPrimaryEdepOfBottomACD(){ return TotalPriEdep[3]; };

		inline double  GetPixelEdep(int l, int id){return Edep[l][id]; };
		inline double* GetPixelEdep(){return &Edep[0][0];};

		inline int     GetPDG(){return PDG;};
		inline int GetCaloId(){return PixelID[1];}
		inline float   GetPrimaryEnergy(){return PrimaryEng;};
		inline float*  GetDirection(){return Direction;};
		inline float*  GetPosition(){return Position;};
        inline float*  GetIntPosition(){return IntPosition;};

		inline double* GetPixelPosition_ACD(int i){return &PixelPos[i][0][0];};
		inline double* GetPixelPosition_UP(int i){return &PixelPos[i][1][0];};
		inline double* GetPixelPosition_DOWN(int i){return &PixelPos[i][2][0];};
		void GetPriPosition(
				double& x, 
				double& y,
				double& z,
				double  fthe, 
				double  fphi=0
				);

		void GetPriThetaPhi(
				double& fthe,
				double& fphi
				);

		void SetPixelPosition();
		void GetPixelPosition(
				int pixelid, 
				int detector,//atc, up, down
				double& x, 
				double& y,
				double& z
				);

		void GetPixelThetaPhi(
				int pixelid, 
				int detector,//atc, up, down
				double& theta, 
				double& phi
				);

		int  GetTotalMaxID(int il, int prescale=0);

		int GetHitsNumber(int il);

		void GetAverThePhi(
				int evti, 
				int layer,
				double &fthe, double &fphi);

		void GetAverPosition(
				int evti, 
				int layer,
				double &fx, double &fy, double &fz);


		int GetHitIDFromOrder(
				int flayer, 
				int forder);
		int GetOrderSize(int layer);

		void GetEmpty_Fired_Info(
				double* container,
				int     &firedN,
				int     &emptyN,
				double  thr_low = 0,
				double  thr_high = 0
				);

		void Debug(string cc);
		void ThrowError(string cc);
		void SetKineticBin(int* fkinetic);
		void SetKineticBin(double* fkinetic);
		void SetKineticBinRange(double* frange);
		void SetKineticBinRange(
				int  fbins,
				int* fbinc,
				double* frange);

		double GetPixelContainerThreshold(
				int layer_i,
				int eng_i);
		double GetPixelContainerThreshold(
				int layer_i,
				double fprie);

		void SetLogBinRange(
				int     bin_n,
				double* range,
				double  begin,
				double  end);

		void SetLogBinRange(
				double *range,
				vector<double> spectrumE,
				vector<double> spectrumN
				);

/*		void SetThreshold(
				double facd,
				double fbottom_acd,
				double fcal
				);*/
    
    void SetThreshold(
            double facd,
            double fcal
            );
    
/*		void GetThresholdTag(
				bool& tag_acd,
				bool& tag_bottom_acd,
				bool& tag_cal
				);*/

       void GetThresholdTag(
                    bool& tag_acd,
                    bool& tag_cal
                    );
    
		bool GetTriggerACD(double thr = 200);
//		bool GetTriggerBottomACD(double thr = 0);

		void Reweight(
				TH1D*& h1_nor,
				TH1D*  h1_kin,
				TH2D*& h2_read,
				TF1*&   func,
				bool fSetBin=false);

		void Reweight(
				TH1D*& h1_nor,
				TH1D*  h1_kin,
				TH2D*& h2_read,
				TF1*&   func,
				int    fbini,
				bool fSetBin=false);

		void Reweight(
				TH2D*& h2_nor,
				TH1D*  h1_kin,
				TH2D*& h2_read,
				TF1*&   func,
				bool fSetBin=false);

		void SetMap(
				TH2D*& h2_map,
				TH1D*  h1_total,
				TH1D** h1_pixel,
				int    npixel
				);

		void CopyHistogram(
				TH1D*& h_copy,
				TH1D*  h_prim
				);

		void CopyHistogram(
				TH2D*& h_copy,
				TH2D*  h_prim
				);

		void CopyHistogram(
				TH2D*& h_copy,
				TH2D** h_prim
				);

		void CopyHistogram(
				TH2D*& h_copy,
				TH2D*  h_prim,
				int&   minBinX,
				int&   minBinY
				);

		void CopyHistogram(
				TH1D*& h_copy,
				TH2D*  h_prim,
				int    fbini = -1,
				bool   fAxis = false
				//false:Project to X(Theta) 
				//true: Project to Y(Phi)
				);

		double CopyHistogram(
				TGraph*& tg_copy,
				TH2D*   h_prim,
				int     fbini = -1,
				bool    fAxis = false
				//false:Project to X(Theta) 
				//true: Project to Y(Phi)
				);
		
		double GetPositionChiSquare(
				TH2D* h_map,
				TH2D* h_sig,
				int&  fDf
				);
		double GetPositionChiSquare(
				TH2D* h_map,
				TH2D* h_sig,
				TH2D* h_bgk
				);

		double GetPositionChiSquare(
				TH2D* h_map,
				TH2D* h_sig,
				int&   fDf,
				double ftime
				);
		double GetPositionChiSquare2(
				TH2D* h_map,
				TH2D* h_sig,
				int&   fDf,
				double ftime
				);

		double GetPositionChiSquare(
				TH2D* h_map,
				TH2D* h_sig,
				TH1D*& h1_mapN,//Counts Spectrum
				TH1D*& h1_sigN,//Counts Spectrum
				int&   fDf,
				double ftime
				);
		double GetPositionChiSquare2(
				TH2D* h_map,
				TH2D* h_sig,
				TH1D*& h1_mapN,//Counts Spectrum
				TH1D*& h1_sigN,//Counts Spectrum
				int&   fDf,
				double ftime
				);

		double GetPositionChiSquare(
				TH2D* h_map,
				TH2D* h_sig,
				int&   fDf,
				double ftime,
				double fStep
				);
		double GetPositionChiSquare2(
				TH2D* h_map,
				TH2D* h_sig,
				int&   fDf,
				double ftime,
				double fStep
				);

		double GetPositionChiSquare(
				TH2D* h_map,
				TH2D* h_sig,
				TH1D*& h1_mapN,//Counts Spectrum
				TH1D*& h1_sigN,//Counts Spectrum
				int&   fDf,
				double ftime,
				double fStep
				);
		double GetPositionChiSquare2(
				TH2D* h_map,
				TH2D* h_sig,
				TH1D*& h1_mapN,//Counts Spectrum
				TH1D*& h1_sigN,//Counts Spectrum
				int&   fDf,
				double ftime,
				double fStep
				);

		void GetRecDirection(
				double& RecThe,
				double& RecPhi,
				TH2D*    h2_chi2
				);

		void GetRecDirection0(
				double& RecThe,
				double& RecPhi,
				TH2D*    h2_chi2
				);

		void SigmaContour(
				TH2D*& h2_chi,
				TH2D*& h2_chiInSig,
				double fsig
				);

		void SigmaContour(
				TH2D*& h2_chi,
				TH2D*& h2_df,
				TH2D*& h2_chiInSig,
				double fsig
				);

		void SigmaContour(
				double Nsig,
				TH2D*& h2_chi,
				TH2D*& h2_df,
				TH2D*& h2_chiInSig
				);

		void GetEffectiveArea(
				TH1D*& h1_eff,
				TH2D* h2_cut0,
				TH1D* h1_cut1,
				double& fSourceArea
				);

         void GetEffeciency(
            TH1D*& h1_eff,
            TH2D* h2_cut0,
            TH1D* h1_cut1
            );


	private:
		bool   fThresholdOpen;
		bool   fTagThresholdACD;
	//	bool   fTagThresholdBottomACD;
		bool   fTagThresholdCAL;
		double ThresholdACD;
		double ThresholdBottomACD;
		double ThresholdCAL;

		double PixelPos[nPixel][3][3];
		int PixelMap[nPixel][2];
		//[pixelid], [atc,up,down], [x,y,z]

		TFile* FileOpen;
		int		 TotalEvtNum;
		//TTree* t_Total;
		//TTree* t_ACD;
		//TTree* t_CAL;
		//TTree* t_Primary;

		TChain* t_Total;
		TChain* t_ACD;
		TChain* t_CAL;
		TChain* t_Primary;


		// Tree: Total
		int     fEvtInFOV;
		int		  fInteraction;
		float   StrucEdep;
		int     MaxEID[3];
		int			nHits[3];

		double  TotalDepEnergy;
		double  TotalEdep[3];
		float   TotalPriDepEnergy;
		float   TotalPriEdep[3];
		float   TotalEdep_Delay[3];

		float  TotalPriEdep_Delay;
		float  TotalPriEdepACD_Delay;
		float  TotalPriEdepCAL_Delay;
		float  TotalPriEdepBottomACD_Delay;


		//Tree: ACD & CAL
		int			PixelID[2];
		float   PixelEdep[2];
		int     PixelHitOrder[2];
		//float  PixelEdepDelay[2];
		int     EventID[2];

		double  Edep[3][nPixel];
		map<int, int> HitOrder_ACD;
		map<int, int> HitOrder_CAL;

		//Tree: Primary
		int     PDG;
		float   PrimaryEng;
		float 	Direction[3];
		float   Position[3];
        float   IntPosition[3];
		int     FirstID_ACD;
		int     nHits_ACD;
		int     FirstID_CAL;
		int     nHits_CAL;

		static AlgDataAction* DataInstance;
		bool   fTagEvtReset;

};

#endif
