//---------------------------------------------------------------------------//
//      BOOST --- BESIII Object_Oriented Simulation Tool                     //
//---------------------------------------------------------------------------//
//Description: Handle database I/O and user interface 
//             for MDC geometry parameters
//Author: Yuan Ye(yuany@mail.ihep.ac.cn)
//Created: 4 Dec, 2003
//Modified:
//Comment: Used in "JMQ" now, should be insert in framwork later
//         The units are "mm" and "rad". 
//         Datum plane is the East Endplane of MDC.
//---------------------------------------------------------------------------//

#ifndef JMQStepWriter_H
#define JMQStepWriter_H 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include <CLHEP/Units/PhysicalConstants.h>
#include "globals.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4ThreeVector.hh"

using namespace std;

class JMQStepWriter{
  public:
    JMQStepWriter();
    ~JMQStepWriter();

    int OpenFile(string fileout);

    void WriteEventTag(int id);

    void WriteEdepAndCenter(int trackID, double edep, double hit_x, double hit_y, double hit_z,
                                                      double hitin_x, double hitin_y, double hitin_z,
                                                      double hitout_x, double hitout_y, double hitout_z);

    void CloseFile(){m_fout->close();};

    static JMQStepWriter* Instance();

  private:
    
    ofstream* m_fout;

    static JMQStepWriter* m_JMQStepWriter;
};

#endif
