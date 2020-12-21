/**
 * @brief
 * class CComponent serves a purpose of a abstract class,
 * which is inherited by Component classes (CCPU, CMemory and CDisk)
 * in order to print their stored data
 * function Print has 3 parameters - ostream, in which the final string is outputed,
 * branchPrefix, a string which is being changed according to the position of a computer
 * in the CNetwork and last, an int value which tells wheter the component in the computer
 * is or isn't last
 */

class CComponent {
  public:
    CComponent (){
    }
    virtual ~CComponent (){
    }

    virtual void Print ( ostream & os, string branchPrefix, int last ) const = 0;
};

//---------------------------------------------------

/**
 * @brief
 * class CCPU stores the information about the number of cores (m_Core)
 * and frequency (m_Frequency) in MHz
 */

class CCPU : public CComponent {
  public:
    CCPU ( const int & core, const int & frequency ) :
    m_Core ( core ), m_Frequency ( frequency ) {
    }

    void Print ( ostream & os, string branchPrefix,  int last ) const override;
  protected:
    int m_Core;
    int m_Frequency;
};

//---------------------------------------------------

/**
 * @brief
 * class CMemory stores the information about its size (m_Size) in MiB
 */

class CMemory : public CComponent {
  public:
    CMemory ( const int & size ) :
    m_Size ( size ) {
    }

    void Print ( ostream & os, string branchPrefix, int last ) const override;
  protected:
    int m_Size;
};

//---------------------------------------------------

/**
 * @brief 
 * class CDisk stores the information about its type (MAGNETIC or SSD, as can be seen in the enum diskType)
 * and its size (m_Size) in GiB
 * the function AddPartition then stores n-number of partitions of the disc in a vector of pair<int, string> (m_Partitions)
 */

class CDisk : public CComponent {
  public:
    CDisk ( const int & type, const int & size ) :
    m_Type ( type ), m_Size ( size ) {
    }

    CDisk & AddPartition ( const int & size, const string & name );

    void Print ( ostream & os, string branchPrefix, int last ) const override;
    enum diskType { SSD, MAGNETIC };

  protected:
    vector< pair<int, string> > m_Partitions;
    int m_Type;
    int m_Size;
    
};

//---------------------------------------------------

/**
 * @brief 
 * class CComputer stores the information about the computers name (m_Name),
 * its addresses (which are stored in a vector (m_AddressList) through the AddAddress function)
 * and components - for which the three functions AddComponents are. The components are stored
 * in a vector of shared_ptr to ensure zero problems with memory (because is not up to the programmer)
 */

class CComputer {
  public:
    CComputer ( const string & name ) : m_Name ( name ) {
    }
    CComputer & AddAddress ( const string & name );

    CComputer & AddComponent ( const CCPU x );
    CComputer & AddComponent ( const CMemory x );
    CComputer & AddComponent ( const CDisk x );

    string & GetName ( void ) {
      return m_Name;
    }

    void Print ( ostream & os, string branchPrefix, int last ) const;
    friend ostream & operator << ( ostream & os, const CComputer & x );
  protected:
  vector < shared_ptr<CComponent> > m_Components;
  string m_Name;
  vector <string> m_AddressList;
};

//---------------------------------------------------

/**
 * @brief 
 * class CNetwork stores the information about its name (m_Name) and its Computers,
 * which are stored in a vector (m_List)
 */

class CNetwork {
  public:
    CNetwork ( const string & name ) :
    m_Name ( name ){
    }
    ~CNetwork (){
    }

    CNetwork & AddComputer ( CComputer & x );
    CComputer * FindComputer ( const string & network );
    void Print ( ostream & os ) const;
    friend ostream & operator << ( ostream & os, const CNetwork & x );
  protected:
    string m_Name;
    vector < CComputer > m_List;
};

//------------------------------------------------------------------------------------------------------



//---------------------------------------------------
//CNetwork
//---------------------------------------------------

CNetwork & CNetwork::AddComputer ( CComputer & x ) {
  m_List.push_back(x);
  return *this;
}

CComputer * CNetwork::FindComputer ( const string & network ) {
  for (size_t i = 0; i < m_List.size(); i++)
  {
    if ( m_List[i].GetName() == network )
      return &m_List[i];
  }
  return NULL;
}

void CNetwork::Print ( ostream & os ) const {
  os << "Network: " << m_Name << endl;
  bool last;
  string branchPrefix;
  m_List.size() < 2 ? branchPrefix = "" : branchPrefix = "| ";

  for (auto it = m_List.begin(); it != m_List.end(); it++)
  {
    if (it == m_List.end() - 1) {
      last = 1;
      branchPrefix = "  ";
    }
      else {
        last = 0;
      }

    (*it).Print(os, branchPrefix, last);
  }
}

ostream & operator << ( ostream & os, const CNetwork & x ) {
  x.Print( os );
  return os;
}

//---------------------------------------------------
//CComputer
//---------------------------------------------------

CComputer & CComputer::AddAddress ( const string & name ) {
  m_AddressList.push_back(name);
  return *this;
}

CComputer & CComputer::AddComponent ( const CCPU x ) {
  m_Components.push_back( make_shared<CCPU>( x ) );
  return *this;
}

CComputer & CComputer::AddComponent ( const CMemory x ) {
  m_Components.push_back( make_shared<CMemory>( x ) );
  return *this;
}

CComputer & CComputer::AddComponent ( const CDisk x ) {
  m_Components.push_back( make_shared<CDisk>( x ) );
  return *this;
}

void CComputer::Print ( ostream & os, string branchPrefix, int last ) const {
  string hostPrefix = "+-";

  if ( last == 2 )
    hostPrefix = "";
  else if ( last == 1 )
      hostPrefix = "\\-";
  
  os << hostPrefix << "Host: " << m_Name << endl;
  for (size_t i = 0; i < m_AddressList.size(); i++)
  { 
    os << branchPrefix << "+-" << m_AddressList[i] << endl;
  }

  for (size_t i = 0; i < m_Components.size(); i++)
  {
    (i == m_Components.size() - 1) ? last = 1 : last = 0;
    m_Components[i] -> Print(os, branchPrefix, last);
  }
  
}

ostream & operator << ( ostream & os, const CComputer & x ) {
  string branchPrefix = "";
  x.Print(os, branchPrefix, 2);
  return os;
}

//---------------------------------------------------
//CComponent
//---------------------------------------------------



//---------------------------------------------------
//CCPU
//---------------------------------------------------

void CCPU::Print ( ostream & os, string branchPrefix, int last ) const {
  string cpuPrefix = "+-";
  if ( last ) cpuPrefix = "\\-";
  os << branchPrefix << cpuPrefix << "CPU, " << m_Core << " cores @ " << m_Frequency << "MHz" << endl;
}


//---------------------------------------------------
//CMemory
//---------------------------------------------------

void CMemory::Print ( ostream & os, string branchPrefix, int last ) const {
  string memoryPrefix = "+-";
  if ( last ) memoryPrefix = "\\-";
  os << branchPrefix << memoryPrefix << "Memory, " << m_Size << " MiB" << endl;
}

//---------------------------------------------------
//CDisk
//---------------------------------------------------

void CDisk::Print ( ostream & os, string branchPrefix, int last ) const {
  string discType;
  string partPrefix = "+-";
  string discPrefix = "+-";
  string partBranchPrefix = "| ";

  if ( last == 2 )
    partBranchPrefix = "";
  else if ( last == 1 ) {
      discPrefix = "\\-";
      partBranchPrefix = "  ";
    }
  
  m_Type == 1 ? discType = "HDD" : discType = "SSD";

  os << branchPrefix << discPrefix << discType << ", " << m_Size << " GiB" << endl;

  for ( size_t i = 0; i < m_Partitions.size(); i++ ){
    if ( i == m_Partitions.size() - 1 ) partPrefix = "\\-";
    os << branchPrefix << partBranchPrefix << partPrefix << "[" << i << "]: " << m_Partitions[i].first << " GiB, " << m_Partitions[i].second << endl;
  }
}

CDisk & CDisk::AddPartition ( const int & size, const string & name ) {
  m_Partitions.push_back( make_pair(size, name) );
  return *this;
}

//------------------------------------------------------------------------------------------------------