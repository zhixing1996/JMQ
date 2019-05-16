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
#include "JMQStepWriter.hh"

JMQStepWriter::JMQStepWriter():m_fout(NULL){
    if(m_JMQStepWriter){G4cout<<"Wariing::JMQStepWriter is constructed twice." << G4endl;}
    m_JMQStepWriter=this;
}

JMQStepWriter::~JMQStepWriter(){
    if(m_fout) delete m_fout;
}

JMQStepWriter* JMQStepWriter::m_JMQStepWriter=NULL;

JMQStepWriter* JMQStepWriter::Instance(){
    if(!m_JMQStepWriter) m_JMQStepWriter = new JMQStepWriter();
    return m_JMQStepWriter;
}

int JMQStepWriter::OpenFile(string fileout){
    m_fout = new ofstream(fileout.c_str(),ios::out);
    if(m_fout == NULL){
        std::cerr << "Failed to open out file: "<< fileout << std::endl;
        return 0;
    }
    m_fout->precision(3);
    m_fout->setf(ios::left);

    (*m_fout)<<"edep\thit_x\thit_y\thit_z\thitin_x\thintin_y\thintin_z\thitout_x\thintout_y\thintout_z"<<endl;

    return 1;
}

void JMQStepWriter::WriteEventTag(int id){
  (*m_fout)<<""<<endl;  
  (*m_fout)<<"EventID: "<<id<<endl;    
}

void JMQStepWriter::WriteEdepAndCenter(int trackID, double edep, double hit_x, double hit_y, double hit_z,
                                                             double hitin_x, double hitin_y, double hitin_z,
                                                             double hitout_x, double hitout_y, double hitout_z){
  (*m_fout)<<trackID<<"\t"<<edep<<"\t"<<hit_x<<"\t"<<hit_y<<"\t"<<hit_z<<"\t"<<hitin_x<<"\t"<<hitin_y<<"\t"<<hitin_z<<"\t"<<hitout_x<<"\t"<<hitout_y<<"\t"<<hitout_z<<endl;
}
