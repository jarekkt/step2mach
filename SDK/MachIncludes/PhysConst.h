//////////////////////////////////////////////////////////////////////
// PhysConst.h: Schnittstelle für die Klasse CPhysConst.
// Header file based on Physical Constants (p.1233) of RPP
// * T. M. Sanders(sanders@umich.edu) 1/95
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PHYSCONST_H__4F565065_8723_477F_B9A6_7F801C4EEC7C__INCLUDED_)
#define AFX_PHYSCONST_H__4F565065_8723_477F_B9A6_7F801C4EEC7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Velocity of light in vacuum (def) m/s		
const double _c = 2.99792458E8;

// Planck constant (40)J s                 
const double _h = 6.6260755E-34;

// Planck constant, reduced (63) J s       
const double _h_BAR = 1.05457266E-34;

// Planck constant, reduced (20) MeV s       
const double _h_BAR_MeVs = 6.5821220E-22;

// electron charge magnitude (49) C      
const double _e_C = 1.60217733E-19;

// electron charge magnitude (15) esu      
const double _e_ESU = 4.8032068E-10;

// conversion constant hbar*c (59) MeV Fm            
const double _hBARc = 197.327053;

// conversion constant (hbar*c)^2 (23) GeV^2 mbarn            
const double _hBARc2 = 0.38937966;

// electron mass (54) kg                  
const double _m_e_kg = 9.1093897E-31;

// electron mass (15) MeV/c^2                   
const double _m_e_MeV = 0.51099906;

// proton mass (28) MeV/c^2                     
const double _m_P_MeV = 938.27231;

// proton mass (12) u                    
const double _m_P_u = 1.007276470;

// proton mass (10) kg                    
const double _m_P_kg = 1.6726231E-27;

// proton mass (37) m_e                    
const double _m_P_M_E = 1836.152701;

// deuteron mass (57) MeV/c^2                  
const double _m_D_MeV = 1875.61339;

// unified atomic mass unit (u) (28) MeV/c^2   
const double _u_MeV = 931.49432;

// unified atomic mass unit (u) (10) kg   
const double _u_kg = 1.6605402E-27;

// permittivity of free space F/m      
const double _EPS_0 = 8.854187817E-12;

// permeability of free space N/A^2      
const double _MU_0 = 12.566370614E-7;

// fine-structure constant (61)        
const double _Alpha = 1/137.0359895;

// classical electron radius (38) m     
const double _r_e = 2.81794092E-15;

// electron Compton wavelength (35) m   
const double _LAMBDA_BAR_e = 3.86159323E-13;

// Bohr radius (mnucleus= infty) (24) m     
const double _a_0 = 0.529177249E-10;

// wavelength of 1 eV/c particle (37) m   
const double _LAMBDA_1EV = 1.23984244E-6;

// Rydberg energy (mnucleus = infinity) (40) eV                 
const double _R_INF_EV = 13.6056981;

// Thomson cross section (18) barn          
const double _SIGMA_0_BARN = 0.66524616;

// Bohr magneton (52)  MeV/T                 
const double _MU_B_MeV_T = 5.78838263E-11;

// nuclear magneton (28) MeV/T               
const double _MU_N_MeV_T = 3.15245166E-14;

// electron cyclotron freq./field (53) C/kg (rad/sT) 
const double _E_M_e = 1.75881962E11;

// proton cyclotron freq./field (29) C/kg (rad/sT) 
const double _E_M_P = 9.5788309E7;

// gravitational constant (85) m^3/kgs^2         
const double _G_SI = 6.67259E-11;

// gravitational constant (86) h_bar c (GeV/c^2)^{-2}       
const double _G_P = 6.70711E-39;

// standard grav. accel., sea level m/s^2 
const double _g = 9.80665;

// Avogadro constant (36)  /mole            
const double _N_A = 6.0221367E23;

// Boltzmann constant (12) J/K             
const double _K_B = 1.380658E-23;

// Boltzmann constant (73) eV/K            
const double _K_B_EV = 8.617385E-5;

// molar volume, ideal gas at STP (19) m^3/mole  
const double _V_MOLAR = 22.41410E-3;

// Wien displacement law constant (24) m K 
const double _LAMBDAT = 2.897756E-3;

// Stefan-Boltzmann constant (19) W/m^2K^4       
const double _SIGMA_SB = 5.67051E-8;

// Fermi coupling constant (2)  GeV^{-2}        
const double _G_F = 1.16639E-5;

// weak mixing angle  (5)  at M_Z           
const double _SIN2_THETA_W = 0.23192;

// W boson mass (26) GeV/c^2                  
const double _M_W = 80.22;

// Z_0 boson mass (7) GeV/c^2                  
const double _M_Z0 = 91.187;

// strong coupling constant (5))  at M_Z     
const double _G_S = 0.117;


class CPhysConst  
{
public:
	CPhysConst();
	virtual ~CPhysConst();

public:
	//Functions
	BOOL IsPhysConst(CString str);
	double GetPhysConstValue(const CString str);
	CString GetEachPhysConst(int i);
	void SetPhysConstOrder();

private:
	// String Array
	CStringArray m_strPhysConst;
};

#endif // !defined(AFX_PHYSCONST_H__4F565065_8723_477F_B9A6_7F801C4EEC7C__INCLUDED_)
