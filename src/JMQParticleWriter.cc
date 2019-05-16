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
#include "JMQParticleWriter.hh"

JMQParticleWriter::JMQParticleWriter():m_fout(NULL){
    if(m_JMQParticleWriter){G4cout<<"Wariing::JMQParticleWriter is constructed twice." << G4endl;}
    m_JMQParticleWriter=this;
}

JMQParticleWriter::~JMQParticleWriter(){
    if(m_fout) delete m_fout;
}

JMQParticleWriter* JMQParticleWriter::m_JMQParticleWriter=NULL;

JMQParticleWriter* JMQParticleWriter::Instance(){
    if(!m_JMQParticleWriter) m_JMQParticleWriter = new JMQParticleWriter();
    return m_JMQParticleWriter;
}

int JMQParticleWriter::OpenFile(string fileout){
    m_fout = new ofstream(fileout.c_str(),ios::out);
    if(m_fout == NULL){
        std::cerr << "Failed to open out file: "<< fileout << std::endl;
        return 0;
    }
    m_fout->precision(3);
    m_fout->setf(ios::left);
    (*m_fout)<<"Ray_px\tRay_py\tRay_pz\t"<<endl;
    return 1;
}

void JMQParticleWriter::WriteEventTag(int id){
  (*m_fout)<<""<<endl;  
  (*m_fout)<<"EventID: "<<id<<endl;    
}

void JMQParticleWriter::WriteRayDirection(double px, double py, double pz){
  (*m_fout)<<px<<"\t"<<py<<"\t"<<pz<<endl;
}
