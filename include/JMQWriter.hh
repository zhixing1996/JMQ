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

#ifndef JMQWriter_H
#define JMQWriter_H 

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

//#include "JMQPixHit.hh"

using namespace std;

class JMQWriter{
  public:
    JMQWriter();
    ~JMQWriter();

    int OpenFile(string fileout);

    void WriteEventTag(int id);

    void WriteRayDirection(double px, double py, double pz);

    void WriteEdepAndCenter(int trackID, double edep, double x, double y, double z);

    void CloseFile(){m_fout->close();};

    static JMQWriter* Instance();

  private:
    
    ofstream* m_fout;

    static JMQWriter* m_JMQWriter;
};

#endif
