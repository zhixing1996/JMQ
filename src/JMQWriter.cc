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
#include "JMQWriter.hh"

JMQWriter::JMQWriter():m_fout(NULL){
    if(m_JMQWriter){G4cout<<"Wariing::JMQWriter is constructed twice." << G4endl;}
    m_JMQWriter=this;
}

JMQWriter::~JMQWriter(){
    if(m_fout) delete m_fout;
}

JMQWriter* JMQWriter::m_JMQWriter=NULL;

JMQWriter* JMQWriter::Instance(){
    if(!m_JMQWriter) m_JMQWriter = new JMQWriter();
    return m_JMQWriter;
}

int JMQWriter::OpenFile(string fileout){
    m_fout = new ofstream(fileout.c_str(),ios::out);
    if(m_fout == NULL){
        std::cerr << "Failed to open out file: "<< fileout << std::endl;
        return 0;
    }
    m_fout->precision(9);
    m_fout->setf(ios::left);
    //(*m_fout)<<"Ray_px\tRay_py\tRay_pz\tedep1\tedep2\tx1\ty1\tz1\tx2\ty2\tz2"<<endl;
    //(*m_fout)<<"***********************************************************************"<<endl;
    return 1;
}

void JMQWriter::WriteEventTag(int id){
  (*m_fout)<<""<<endl;  
  (*m_fout)<<"EventID: "<<id<<endl;    
}

void JMQWriter::WriteRayDirection(double px, double py, double pz){
  (*m_fout)<<px<<"\t"<<py<<"\t"<<pz<<endl;
}

void JMQWriter::WriteEdepAndCenter(int trackID, double edep, double hit_x, double hit_y, double hit_z,
                                                             double hitin_x, double hitin_y, double hitin_z,
                                                             double hitout_x, double hitout_y, double hitout_z){
  (*m_fout)<<trackID<<"\t"<<edep<<"\t";
  (*m_fout)<<hit_x<<"\t"<<hit_y<<"\t"<<hit_z<<"\t";
  (*m_fout)<<hitin_x<<"\t"<<hitin_y<<"\t"<<hitin_z<<"\t";
  (*m_fout)<<hitout_x<<"\t"<<hitout_y<<"\t"<<hitout_z<<endl;
}
