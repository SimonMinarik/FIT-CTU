#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

string toUpper ( string s ){
  transform(s.begin(), s.end(), s.begin(), [](char c){ return toupper(c); });
  return s;
}

unsigned g_Index = 0;

class CLand {
  public:
  CLand ( const string & city, const string & addr, const string & region, unsigned id, const string & owner, unsigned indexOw );
  //void Print ( void ) const;
  int Compare ( const CLand & x, int a ) const;
  bool ifExistsCA ( const CLand & x ) const;
  bool ifExistsRI ( const CLand & x ) const;
  bool ifExistsO ( const CLand & x ) const;
  string GetOwner ( void ) const;
  //private:
  string m_City;
  string m_Addr;
  string m_Region;
  unsigned m_ID;
  string m_Owner;
  unsigned m_Index;
};

CLand::CLand ( const string & city, const string & addr, const string & region, unsigned id, const string & owner, unsigned indexOw )
: m_City ( city ),
  m_Addr ( addr ),
  m_Region ( region ),
  m_ID ( id ),
  m_Owner ( owner ),
  m_Index ( indexOw ){
  }

/*void CLand::Print ( void ) const {
  cout << m_City << " " << m_Addr << " " << m_Region << " " << m_ID << " " << m_Owner << " " << m_Index;
}*/

int CLand::Compare ( const CLand & x, int a ) const{
  switch ( a )
  {
    case 1:
      return ( m_Addr.compare(x.m_Addr) );
      break;
    case 2:
      return ( m_City.compare(x.m_City) );
      break;
    case 3:
      return ( m_Region.compare(x.m_Region) );
      break;
    case 4:
      return ( m_ID - x.m_ID );
      break;
    case 5:
      return ( m_Index - x.m_Index );
      break;
  
    default:
      return 0;
      break;
  }
}

bool CLand::ifExistsCA ( const CLand & x ) const{
  //cout << "help" << endl;
  return m_City == x.m_City && m_Addr == x.m_Addr;
}

bool CLand::ifExistsRI ( const CLand & x ) const{
  //cout << "help" << endl;
  return m_Region == x.m_Region && m_ID == x.m_ID;
}

bool CLand::ifExistsO ( const CLand & x ) const{
  return toUpper(m_Owner) == toUpper(x.m_Owner);
}

string CLand::GetOwner ( void ) const{
  return m_Owner;
}

class CIterator
{
  public:
    bool                     AtEnd                         ( void ) const;
    void                     Next                          ( void );
    string                   City                          ( void ) const;
    string                   Addr                          ( void ) const;
    string                   Region                        ( void ) const;
    unsigned                 ID                            ( void ) const;
    string                   Owner                         ( void ) const;
    void Add ( const CLand & x );
    vector<CLand *> m_Iter;
    //vector<CLand *> byOwner;
    unsigned index;
    unsigned size;
  private:
};

bool CIterator::AtEnd ( void ) const{
  //cout << index << "   " << size << endl;
  return index == size;
}

void CIterator::Next ( void ){
  ++index;
}

string CIterator::City ( void ) const{
  //cout << m_Iter.at(index) -> m_City << " at: " << index << endl;
  return m_Iter.at(index) -> m_City;
}

string CIterator::Addr ( void ) const{
  return m_Iter.at(index) -> m_Addr;
}

string CIterator::Region ( void ) const{
  return m_Iter.at(index) -> m_Region;
}

unsigned CIterator::ID ( void ) const{
  return m_Iter.at(index) -> m_ID;
}

string CIterator::Owner ( void ) const{
  return m_Iter.at(index) -> m_Owner;
}

class CLandRegister
{
  public:
    ~CLandRegister ( void );
    bool                     Add                           ( const string    & city,
                                                             const string    & addr,
                                                             const string    & region,
                                                             unsigned int      id );

    bool                     Del                           ( const string    & city,
                                                             const string    & addr );

    bool                     Del                           ( const string    & region,
                                                             unsigned int      id );

    bool                     GetOwner                      ( const string    & city,
                                                             const string    & addr,
                                                             string          & owner ) const;

    bool                     GetOwner                      ( const string    & region,
                                                             unsigned int      id,
                                                             string          & owner ) const;

    bool                     NewOwner                      ( const string    & city,
                                                             const string    & addr,
                                                             const string    & owner );

    bool                     NewOwner                      ( const string    & region,
                                                             unsigned int      id,
                                                             const string    & owner );

    //void                     Print                         ( void ) const;
    
    unsigned                 Count                         ( const string    & owner ) const;

    CIterator                ListByAddr                    ( void ) const;

    CIterator                ListByOwner                   ( const string    & owner ) const;
  private:
    vector<CLand *> m_ListCA;
    vector<CLand *> m_ListRI;
    //vector<CLand *> m_ListO;
    //vector<string> owners;
};

CLandRegister::~CLandRegister ( void ){
  for(size_t i = 0; i < m_ListRI.size(); i++){
    delete m_ListRI[i];
  }
}

bool CLandRegister::Add ( const string & city, const string & addr, const string & region, unsigned int id ){
  CLand * x = new CLand ( city, addr, region, id, "", g_Index );
  ++g_Index;
  if ( ! m_ListCA.empty() ){
  auto indexCA = lower_bound( m_ListCA.begin(), m_ListCA.end(), x, []( const CLand * a, const CLand * b ){ int y = a -> Compare( *b, 2 ); return ( y == 0) ? a -> Compare ( *b, 1 ) < 0 : y < 0; } );
  auto indexRI = lower_bound( m_ListRI.begin(), m_ListRI.end(), x, []( const CLand * a, const CLand * b ){ int y = a -> Compare( *b, 3 ); return ( y == 0) ? a -> Compare ( *b, 4 ) < 0 : y < 0; } );
  auto indexCAs = indexCA;
  auto indexRIs = indexRI;

  if ( indexRI == m_ListRI.end() ) {
    indexRIs--;
  }
  if ( indexCA == m_ListCA.end() ) {
    indexCAs--;
  }

  if ( m_ListCA[indexCAs - m_ListCA.begin()] -> ifExistsCA( *x ) || m_ListRI[indexRIs - m_ListRI.begin()] -> ifExistsRI( *x ) ){
    delete x;
    return false;
  }
  m_ListCA . insert ( indexCA, x);
  m_ListRI . insert ( indexRI, x);
  }
  else {
    m_ListCA . push_back ( x );
    m_ListRI . push_back ( x );
  }
  return true;
}

/*void CLandRegister::Print ( void ) const {
  cout << "m_ListCA:" << endl;
  for ( const auto & land : m_ListCA )
  {
    land -> Print ();
    cout << endl;
  }
  cout << "-----------" << endl << "m_ListRI:" << endl;
  for ( const auto & land : m_ListRI )
  {
    land -> Print ();
    cout << endl;
  }
  cout << "-----------" << endl << "m_ListO:" << endl;
  for ( const auto & land : m_ListO )
  {
    land -> Print ();
    cout << endl;
  }
}*/

bool CLandRegister::Del ( const string & city, const string & addr ){
  CLand * x = new CLand ( city, addr, "", 0, "", 0 );
  auto indexCA = lower_bound( m_ListCA.begin(), m_ListCA.end(), x, []( const CLand * a, const CLand * b ){ int y = a -> Compare( *b, 2 ); return ( y == 0) ? a -> Compare ( *b, 1 ) < 0 : y < 0; } );
  if ( indexCA == m_ListCA.end() ) {
    delete x;
    return false;
  }
  if ( ! m_ListCA[indexCA - m_ListCA.begin()] -> ifExistsCA( *x ) ){
    delete x;
    return false;
  }

  string temp_region = m_ListCA[indexCA - m_ListCA.begin()] -> m_Region;
  unsigned temp_id = m_ListCA[indexCA - m_ListCA.begin()] -> m_ID;
  string temp_owner = m_ListCA[indexCA - m_ListCA.begin()] -> m_Owner;
  unsigned temp_index = m_ListCA[indexCA - m_ListCA.begin()] -> m_Index;
  delete x;
  CLand * y = new CLand ( city, addr, temp_region, temp_id, temp_owner, temp_index );
  auto indexRI = lower_bound( m_ListRI.begin(), m_ListRI.end(), y, []( const CLand * a, const CLand * b ){ int y = a -> Compare( *b, 3 ); return ( y == 0) ? a -> Compare ( *b, 4 ) < 0 : y < 0; } );

  if ( m_ListCA[indexCA - m_ListCA.begin()] -> ifExistsCA( *y ) || m_ListRI[indexRI - m_ListRI.begin()] -> ifExistsRI( *y ) ){
    delete m_ListCA[indexCA - m_ListCA.begin()];
    m_ListCA.erase( indexCA );
    m_ListRI.erase( indexRI );
    /*auto lowerIndex = lower_bound( m_ListO.begin(), m_ListO.end(), y, []( const CLand * a, const CLand * b ){ return a -> Compare( *b, 5 ) < 0; } );
    auto upperIndex = upper_bound( m_ListO.begin(), m_ListO.end(), y, []( const CLand * a, const CLand * b ){ return a -> Compare( *b, 5 ) < 0; } );
    //int a;
    for(auto i = lowerIndex; i < upperIndex; i++){
      if ( m_ListO[i - m_ListO.begin()] -> m_City == city && m_ListO[i - m_ListO.begin()] -> m_Addr == addr ) {
        m_ListO.erase(i);
        //a = i - m_ListO.begin();
        //owners.erase(a + owners.begin());
        break;
      }
    }*/
    
    delete y;
    return true;
  }
  delete y;
  return false;
}

bool CLandRegister::Del ( const string & region, unsigned id ){
  CLand * x = new CLand ( "", "", region, id, "", 0 );
  auto indexRI = lower_bound( m_ListRI.begin(), m_ListRI.end(), x, []( const CLand * a, const CLand * b ){ int y = a -> Compare( *b, 3 ); return ( y == 0) ? a -> Compare ( *b, 4 ) < 0 : y < 0; } );
  if ( indexRI == m_ListRI.end() ) {
    delete x;
    return false;
  }
  if ( ! m_ListRI[indexRI - m_ListRI.begin()] -> ifExistsRI( *x ) ){
    delete x;
    return false;
  }
  string temp_addr = m_ListRI[indexRI - m_ListRI.begin()] -> m_Addr;
  string temp_city = m_ListRI[indexRI - m_ListRI.begin()] -> m_City;
  string temp_owner = m_ListRI[indexRI - m_ListRI.begin()] -> m_Owner;
  unsigned temp_index = m_ListRI[indexRI - m_ListRI.begin()] -> m_Index;
  delete x;
  CLand * y = new CLand ( temp_city, temp_addr, region, id, temp_owner, temp_index );
  auto indexCA = lower_bound( m_ListCA.begin(), m_ListCA.end(), y, []( const CLand * a, const CLand * b ){ int y = a -> Compare( *b, 2 ); return ( y == 0) ? a -> Compare ( *b, 1 ) < 0 : y < 0; } );
  
  //cout << indexCA - m_ListCA.begin() << endl;
  
  if ( m_ListCA[indexCA - m_ListCA.begin()] -> ifExistsCA( *y ) && m_ListRI[indexRI - m_ListRI.begin()] -> ifExistsRI( *y ) ){
    delete m_ListCA[indexCA - m_ListCA.begin()];
    m_ListCA.erase( indexCA );
    m_ListRI.erase( indexRI );
    /*auto lowerIndex = lower_bound( m_ListO.begin(), m_ListO.end(), y, []( const CLand * a, const CLand * b ){ return a -> Compare( *b, 5 ) < 0; } );
    auto upperIndex = upper_bound( m_ListO.begin(), m_ListO.end(), y, []( const CLand * a, const CLand * b ){ return a -> Compare( *b, 5 ) < 0; } );
    //int a;
    for(auto i = lowerIndex; i < upperIndex; i++){
      if ( m_ListO[i - m_ListO.begin()] -> m_Region == region && m_ListO[i - m_ListO.begin()] -> m_ID == id ) {
        m_ListO.erase(i);
        //a = i - m_ListO.begin();
        //owners.erase(a + owners.begin());
        break;
      }
    }*/
    delete y;
    return true;
  }
  delete y;
  return false;
}

bool CLandRegister::GetOwner ( const string & city, const string & addr, string & owner ) const{
  CLand * x = new CLand ( city, addr, "", 0, "", 0 );
  auto indexCA = lower_bound( m_ListCA.begin(), m_ListCA.end(), x, []( const CLand * a, const CLand * b ){ int y = a -> Compare( *b, 2 ); return ( y == 0) ? a -> Compare ( *b, 1 ) < 0 : y < 0; } );
  if ( indexCA == m_ListCA.end() ) {
    delete x;
    return false;
  }
  if ( m_ListCA[indexCA - m_ListCA.begin()] -> ifExistsCA( *x ) ){
    owner = m_ListCA[indexCA - m_ListCA.begin()] -> GetOwner();
    delete x;
    return true;
  }
  delete x;
  return false;
}

bool CLandRegister::GetOwner ( const string & region, unsigned id, string & owner ) const{
  CLand * x = new CLand ( "", "", region, id, "", 0 );
  auto indexRI = lower_bound( m_ListRI.begin(), m_ListRI.end(), x, []( const CLand * a, const CLand * b ){ int y = a -> Compare( *b, 3 ); return ( y == 0) ? a -> Compare ( *b, 4 ) < 0 : y < 0; } );
  if ( indexRI == m_ListRI.end() ) {
    delete x;
    return false;
  }
  if ( m_ListRI[indexRI - m_ListRI.begin()] -> ifExistsRI( *x ) ){
    owner = m_ListRI[indexRI - m_ListRI.begin()] -> GetOwner();
    delete x;
    return true;
  }
  delete x;
  return false;
}

bool CLandRegister::NewOwner ( const string & city, const string & addr, const string & owner ){
  CLand * x = new CLand ( city, addr, "", 0, "", 0 );
  auto indexCA = lower_bound( m_ListCA.begin(), m_ListCA.end(), x, []( const CLand * a, const CLand * b ){ int y = a -> Compare( *b, 2 ); return ( y == 0) ? a -> Compare ( *b, 1 ) < 0 : y < 0; } );
  if ( indexCA == m_ListCA.end() ) {
    delete x;
    return false;
  }
  if ( ! m_ListCA[indexCA - m_ListCA.begin()] -> ifExistsCA( *x ) || toUpper(m_ListCA[indexCA - m_ListCA.begin()] -> m_Owner) == toUpper(owner) ){
    delete x;
    return false;
  }
  string temp_region = m_ListCA[indexCA - m_ListCA.begin()] -> m_Region;
  unsigned temp_id = m_ListCA[indexCA - m_ListCA.begin()] -> m_ID;
  string temp_owner = m_ListCA[indexCA - m_ListCA.begin()] -> m_Owner;
  delete x;
  ++g_Index;
  CLand * y = new CLand ( city, addr, temp_region, temp_id, temp_owner, g_Index );
  auto indexRI = lower_bound( m_ListRI.begin(), m_ListRI.end(), y, []( const CLand * a, const CLand * b ){ int y = a -> Compare( *b, 3 ); return ( y == 0) ? a -> Compare ( *b, 4 ) < 0 : y < 0; } );
  
  if ( m_ListCA[indexCA - m_ListCA.begin()] -> ifExistsCA( *y ) || m_ListRI[indexRI - m_ListRI.begin()] -> ifExistsRI( *y ) ){
    m_ListCA[indexCA - m_ListCA.begin()] -> m_Owner = owner;
    m_ListCA[indexCA - m_ListCA.begin()] -> m_Index = g_Index;
    //m_ListRI[indexRI - m_ListRI.begin()] -> m_Owner = owner;
    //auto lowerIndex = lower_bound( m_ListO.begin(), m_ListO.end(), y, []( const CLand * a, const CLand * b ){ return a -> Compare( *b, 5 ) < 0; } );
    /*auto upperIndex = upper_bound( m_ListO.begin(), m_ListO.end(), y, []( const CLand * a, const CLand * b ){ return a -> Compare( *b, 5 ) < 0; } );
    cout << "tuto: " << upperIndex - m_ListO.begin() << "   pre " << owner << endl;
    //int a;
    cout << owner << "  <<<<<<<<<" << endl;
    for(int i = 0; i < m_ListO.size(); i++){
      cout << owner << "  <<<<<<<<<" << endl;
      if ( m_ListO[i] -> m_City == city && m_ListO[i] -> m_Addr == addr ) {
        CLand * tmp = m_ListO[i];
        m_ListO.erase(i + m_ListO.begin());
        //a = i - m_ListO.begin();
        //owners.erase(a + owners.begin());
        auto indexO = upper_bound( m_ListO.begin(), m_ListO.end(), tmp, []( const CLand * a, const CLand * b ){ return a -> Compare( *b, 5 ) < 0; } );
        //cout << "tuto: " << indexO - owners.begin() << "   pre " << owner << endl;
        //owners.insert(indexO, owner);
        //a = indexO - owners.begin();
        m_ListO.insert(indexO, tmp);
        break;
      }
    }*/
    
    delete y;
    return true;
  }
  delete y;
  return false;
}

bool CLandRegister::NewOwner ( const string & region, unsigned id, const string & owner ){
  CLand * x = new CLand ( "", "", region, id, "", 0 );
  auto indexRI = lower_bound( m_ListRI.begin(), m_ListRI.end(), x, []( const CLand * a, const CLand * b ){ int y = a -> Compare( *b, 3 ); return ( y == 0) ? a -> Compare ( *b, 4 ) < 0 : y < 0; } );
  if ( indexRI == m_ListRI.end() ) {
    delete x;
    return false;
  }
  if ( ! m_ListRI[indexRI - m_ListRI.begin()] -> ifExistsRI( *x ) || toUpper(m_ListRI[indexRI - m_ListRI.begin()] -> m_Owner) == toUpper(owner) ){
    delete x;
    return false;
  }
  string temp_addr = m_ListRI[indexRI - m_ListRI.begin()] -> m_Addr;
  string temp_city = m_ListRI[indexRI - m_ListRI.begin()] -> m_City;
  string temp_owner = m_ListRI[indexRI - m_ListRI.begin()] -> m_Owner;
  delete x;
  ++g_Index;
  CLand * y = new CLand ( temp_city, temp_addr, region, id, temp_owner, g_Index );
  auto indexCA = lower_bound( m_ListCA.begin(), m_ListCA.end(), y, []( const CLand * a, const CLand * b ){ int y = a -> Compare( *b, 2 ); return ( y == 0) ? a -> Compare ( *b, 1 ) < 0 : y < 0; } );
    
  if ( m_ListCA[indexCA - m_ListCA.begin()] -> ifExistsCA( *y ) && m_ListRI[indexRI - m_ListRI.begin()] -> ifExistsRI( *y ) ){
    m_ListCA[indexCA - m_ListCA.begin()] -> m_Owner = owner;
    m_ListCA[indexCA - m_ListCA.begin()] -> m_Index = g_Index;
    //m_ListRI[indexRI - m_ListRI.begin()] -> m_Owner = owner;
    //auto lowerIndex = lower_bound( m_ListO.begin(), m_ListO.end(), y, []( const CLand * a, const CLand * b ){ return a -> Compare( *b, 5 ) < 0; } );
    //auto lowerIndexO = lower_bound( owners.begin(), owners.end(), temp_owner );
    //auto upperIndex = upper_bound( m_ListO.begin(), m_ListO.end(), y, []( const CLand * a, const CLand * b ){ return a -> Compare( *b, 5 ) < 0; } );
    //int a;
    /*cout << owner << "  <<<<<<<<<" << endl;
    for(int i = 0; i < m_ListO.size(); i++){
      if ( m_ListO[i] -> m_Region == region && m_ListO[i] -> m_ID == id ) {
        CLand * tmp = m_ListO[i];
        m_ListO.erase(i + m_ListO.begin());
        //a = i - m_ListO.begin();
        //owners.erase(a + owners.begin());
        auto indexO = upper_bound( m_ListO.begin(), m_ListO.end(), tmp, []( const CLand * a, const CLand * b ){ return a -> Compare( *b, 5 ) < 0; } );
        //cout << "tuto: " << indexO - owners.begin() << "   pre " << owner << endl;
        //owners.insert(indexO, owner);
        //a = indexO - owners.begin();
        m_ListO.insert(indexO, tmp);
        break;
      }
    }*/
    delete y;
    return true;
  }
  delete y;
  return false;
}

unsigned CLandRegister::Count ( const string & owner ) const{
  //CLand * x = new CLand( "", "", "", 0, owner, 0 );
  /*auto lowerIndex = lower_bound( m_ListO.begin(), m_ListO.end(), x, []( const CLand * a, const CLand * b ){ return a -> Compare( *b, 5 ) < 0; } );
  auto upperIndex = upper_bound( m_ListO.begin(), m_ListO.end(), x, []( const CLand * a, const CLand * b ){ return a -> Compare( *b, 5 ) < 0; } );
  //auto upperIndex = upper_bound( m_ListO.begin(), m_ListO.end(), x -> m_Owner);
  if ( lowerIndex == m_ListO.end() ){
    return 0;
  }
  if ( m_ListO[lowerIndex - m_ListO.begin()] -> ifExistsO( *x ) && m_ListO[upperIndex - m_ListO.begin() - 1] -> ifExistsO( *x ) ) {
    cout << (upperIndex - m_ListO.begin()) - (lowerIndex - m_ListO.begin()) << " <------" << endl;
    return (upperIndex - m_ListO.begin()) - (lowerIndex - m_ListO.begin());
  }*/
  unsigned count = 0;
  for(size_t i = 0; i < m_ListCA.size(); i++)
  {
    if ( toUpper(owner) == toUpper(m_ListCA[i] -> m_Owner) ) {
      ++count;
    }
  }
  
  
  return count;
}

CIterator CLandRegister::ListByAddr ( void ) const{
  CIterator m_IterCA;
  m_IterCA.m_Iter = this->m_ListCA;
  m_IterCA.index = 0;
  m_IterCA.size = this -> m_ListCA.size();

  return m_IterCA;
}

CIterator CLandRegister::ListByOwner ( const string & owner ) const{
  CIterator m_IterO;
  //CLand * x = new CLand( "", "", "", 0, owner, 0 );
  /*auto lowerIndex = lower_bound( m_ListO.begin(), m_ListO.end(), x, []( const CLand * a, const CLand * b ){ return a -> Compare( *b, 5 ) < 0; } );
  auto upperIndex = upper_bound( m_ListO.begin(), m_ListO.end(), x, []( const CLand * a, const CLand * b ){ return a -> Compare( *b, 5 ) < 0; } );
  for(auto i = lowerIndex; i < upperIndex; i++){
      cout << i - m_ListO.begin() << endl;
      m_IterO.m_Iter.push_back(m_ListO[i - m_ListO.begin()]);
      cout << m_ListO[i - m_ListO.begin()] -> m_City << endl;
    }*/
  
  m_IterO.m_Iter.clear();

  for(size_t i = 0; i < m_ListCA.size(); i++){
    if ( ! m_IterO.m_Iter.empty() ) {
      if ( toUpper(m_ListCA[i] -> m_Owner) == toUpper(owner) ) {
        auto lowerIndexO = lower_bound( m_IterO.m_Iter.begin(), m_IterO.m_Iter.end(), m_ListCA[i], []( const CLand * a, const CLand * b ){ return a -> Compare( *b, 5 ) < 0; } );    
        m_IterO.m_Iter.insert(lowerIndexO,m_ListCA[i]);
      }
    }
    else{
      if ( toUpper(m_ListCA[i] -> m_Owner) == toUpper(owner) ) {
        m_IterO.m_Iter.push_back(m_ListCA[i]);
      }
    }
  }
  
  m_IterO.index = 0;
  m_IterO.size = m_IterO.m_Iter.size();
  return m_IterO;
}

//#ifndef __PROGTEST__
static void test0 ( void )
{
  CLandRegister x;
  string owner;
  //cout << toUpper("wqfqf") << endl;
  assert ( x . Add ( "Prague", "Thakurova", "Dejvice", 12345 ) );
  assert ( x . Add ( "Prague", "Evropska", "Vokovice", 12345 ) );
  assert ( x . Add ( "Prague", "Technicka", "Dejvice", 9873 ) );
  assert ( x . Add ( "Plzen", "Evropska", "Plzen mesto", 78901 ) );
  assert ( x . Add ( "Liberec", "Evropska", "Librec", 4552 ) );
  assert ( x . Add ( "Bratislava", "hhh", "Bratislava", 81101 ) );
  assert ( x . Del ( "Bratislava", 81101 ) );
  assert ( ! x . Add ( "Liberec", "Evropska", "Librec", 4552 ) );
  //x . Print ();
  assert ( ! x . Del ( "Dejvice", 123425 ) );
  assert ( x . GetOwner ( "Prague", "Evropska", owner ) && owner == "" );
  //x . Print ();
  CIterator i0 = x . ListByAddr ();
  assert ( ! i0 . AtEnd() );
  assert ( ! i0 . AtEnd ()
           && i0 . City () == "Liberec"
           && i0 . Addr () == "Evropska"
           && i0 . Region () == "Librec"
           && i0 . ID () == 4552
           && i0 . Owner () == "" );
  i0 . Next ();
  assert ( ! i0 . AtEnd ()
           && i0 . City () == "Plzen"
           && i0 . Addr () == "Evropska"
           && i0 . Region () == "Plzen mesto"
           && i0 . ID () == 78901
           && i0 . Owner () == "" );
  i0 . Next ();
  assert ( ! i0 . AtEnd ()
           && i0 . City () == "Prague"
           && i0 . Addr () == "Evropska"
           && i0 . Region () == "Vokovice"
           && i0 . ID () == 12345
           && i0 . Owner () == "" );
  i0 . Next ();
  assert ( ! i0 . AtEnd ()
           && i0 . City () == "Prague"
           && i0 . Addr () == "Technicka"
           && i0 . Region () == "Dejvice"
           && i0 . ID () == 9873
           && i0 . Owner () == "" );
  i0 . Next ();
  assert ( ! i0 . AtEnd ()
           && i0 . City () == "Prague"
           && i0 . Addr () == "Thakurova"
           && i0 . Region () == "Dejvice"
           && i0 . ID () == 12345
           && i0 . Owner () == "" );
  i0 . Next ();
  assert ( i0 . AtEnd () );

  assert ( x . Count ( "" ) == 5 );
  assert ( x . Count ( "CVUT" ) == 0 );
  //cout << "ouou" << endl;
  CIterator i1 = x . ListByOwner ( "" );
  assert ( i1 . City () == "Prague" );
  assert ( ! i1 . AtEnd ()
           && i1 . City () == "Prague"
           && i1 . Addr () == "Thakurova"
           && i1 . Region () == "Dejvice"
           && i1 . ID () == 12345
           && i1 . Owner () == "" );
  i1 . Next ();
  assert ( ! i1 . AtEnd ()
           && i1 . City () == "Prague"
           && i1 . Addr () == "Evropska"
           && i1 . Region () == "Vokovice"
           && i1 . ID () == 12345
           && i1 . Owner () == "" );
  i1 . Next ();
  assert ( ! i1 . AtEnd ()
           && i1 . City () == "Prague"
           && i1 . Addr () == "Technicka"
           && i1 . Region () == "Dejvice"
           && i1 . ID () == 9873
           && i1 . Owner () == "" );
  i1 . Next ();
  assert ( ! i1 . AtEnd ()
           && i1 . City () == "Plzen"
           && i1 . Addr () == "Evropska"
           && i1 . Region () == "Plzen mesto"
           && i1 . ID () == 78901
           && i1 . Owner () == "" );
  i1 . Next ();
  assert ( ! i1 . AtEnd ()
           && i1 . City () == "Liberec"
           && i1 . Addr () == "Evropska"
           && i1 . Region () == "Librec"
           && i1 . ID () == 4552
           && i1 . Owner () == "" );
  i1 . Next ();
  assert ( i1 . AtEnd () );

  assert ( x . Count ( "CVUT" ) == 0 );
  CIterator i2 = x . ListByOwner ( "CVUT" );
  assert ( i2 . AtEnd () );

  //x . Print();
  //cout << "--------New Owner----------" << endl;

  assert ( x . NewOwner ( "Prague", "Thakurova", "CVUT" ) );
  assert ( x . Del ( "Prague", "Thakurova" ) );
  assert ( x . Add( "Prague", "Thakurova", "Dejvice", 12345 ) );
  assert ( x . NewOwner ( "Prague", "Thakurova", "CVUT" ) );
  assert ( x . NewOwner ( "Dejvice", 9873, "CVUT" ) );
  assert ( x . NewOwner ( "Plzen", "Evropska", "Anton Hrabis" ) );
  assert ( x . NewOwner ( "Liberec", "Evropska", "Cvut" ) );
  //x . Print();
  assert ( x . GetOwner ( "Prague", "Thakurova", owner ) && owner == "CVUT" );
  assert ( x . GetOwner ( "Dejvice", 12345, owner ) && owner == "CVUT" );
  assert ( x . GetOwner ( "Prague", "Evropska", owner ) && owner == "" );
  assert ( x . GetOwner ( "Vokovice", 12345, owner ) && owner == "" );
  assert ( x . GetOwner ( "Prague", "Technicka", owner ) && owner == "CVUT" );
  assert ( x . GetOwner ( "Dejvice", 9873, owner ) && owner == "CVUT" );
  assert ( x . GetOwner ( "Plzen", "Evropska", owner ) && owner == "Anton Hrabis" );
  assert ( x . GetOwner ( "Plzen mesto", 78901, owner ) && owner == "Anton Hrabis" );
  assert ( x . GetOwner ( "Liberec", "Evropska", owner ) && owner == "Cvut" );
  assert ( x . GetOwner ( "Librec", 4552, owner ) && owner == "Cvut" );
  
  //x . Print();
  
  CIterator i3 = x . ListByAddr ();
  assert ( ! i3 . AtEnd ()
           && i3 . City () == "Liberec"
           && i3 . Addr () == "Evropska"
           && i3 . Region () == "Librec"
           && i3 . ID () == 4552
           && i3 . Owner () == "Cvut" );
  i3 . Next ();
  assert ( ! i3 . AtEnd ()
           && i3 . City () == "Plzen"
           && i3 . Addr () == "Evropska"
           && i3 . Region () == "Plzen mesto"
           && i3 . ID () == 78901
           && i3 . Owner () == "Anton Hrabis" );
  i3 . Next ();
  assert ( ! i3 . AtEnd ()
           && i3 . City () == "Prague"
           && i3 . Addr () == "Evropska"
           && i3 . Region () == "Vokovice"
           && i3 . ID () == 12345
           && i3 . Owner () == "" );
  i3 . Next ();
  assert ( ! i3 . AtEnd ()
           && i3 . City () == "Prague"
           && i3 . Addr () == "Technicka"
           && i3 . Region () == "Dejvice"
           && i3 . ID () == 9873
           && i3 . Owner () == "CVUT" );
  i3 . Next ();
  assert ( ! i3 . AtEnd ()
           && i3 . City () == "Prague"
           && i3 . Addr () == "Thakurova"
           && i3 . Region () == "Dejvice"
           && i3 . ID () == 12345
           && i3 . Owner () == "CVUT" );
  i3 . Next ();
  assert ( i3 . AtEnd () );

  //x . Print();
  //cout << "count: " << x . Count ( "cvut" ) << endl;
  assert ( x . Count ( "cvut" ) == 3 );
  CIterator i4 = x . ListByOwner ( "cVuT" );
  assert ( ! i4 . AtEnd ()
           && i4 . City () == "Prague"
           && i4 . Addr () == "Thakurova"
           && i4 . Region () == "Dejvice"
           && i4 . ID () == 12345
           && i4 . Owner () == "CVUT" );
  i4 . Next ();
  assert ( ! i4 . AtEnd ()
           && i4 . City () == "Prague"
           && i4 . Addr () == "Technicka"
           && i4 . Region () == "Dejvice"
           && i4 . ID () == 9873
           && i4 . Owner () == "CVUT" );
  i4 . Next ();
  assert ( ! i4 . AtEnd ()
           && i4 . City () == "Liberec"
           && i4 . Addr () == "Evropska"
           && i4 . Region () == "Librec"
           && i4 . ID () == 4552
           && i4 . Owner () == "Cvut" );
  i4 . Next ();
  assert ( i4 . AtEnd () );

  assert ( x . NewOwner ( "Plzen mesto", 78901, "CVut" ) );
  assert ( x . Count ( "CVUT" ) == 4 );
  //x . Print();
  CIterator i5 = x . ListByOwner ( "CVUT" );
  assert ( ! i5 . AtEnd ()
           && i5 . City () == "Prague"
           && i5 . Addr () == "Thakurova"
           && i5 . Region () == "Dejvice"
           && i5 . ID () == 12345
           && i5 . Owner () == "CVUT" );
  i5 . Next ();
  assert ( ! i5 . AtEnd ()
           && i5 . City () == "Prague"
           && i5 . Addr () == "Technicka"
           && i5 . Region () == "Dejvice"
           && i5 . ID () == 9873
           && i5 . Owner () == "CVUT" );
  i5 . Next ();
  assert ( ! i5 . AtEnd ()
           && i5 . City () == "Liberec"
           && i5 . Addr () == "Evropska"
           && i5 . Region () == "Librec"
           && i5 . ID () == 4552
           && i5 . Owner () == "Cvut" );
  i5 . Next ();
  assert ( ! i5 . AtEnd ()
           && i5 . City () == "Plzen"
           && i5 . Addr () == "Evropska"
           && i5 . Region () == "Plzen mesto"
           && i5 . ID () == 78901
           && i5 . Owner () == "CVut" );
  i5 . Next ();
  assert ( i5 . AtEnd () );

  assert ( x . Del ( "Liberec", "Evropska" ) );
  assert ( x . Del ( "Plzen mesto", 78901 ) );
  assert ( x . Count ( "cvut" ) == 2 );
  CIterator i6 = x . ListByOwner ( "cVuT" );
  assert ( ! i6 . AtEnd ()
           && i6 . City () == "Prague"
           && i6 . Addr () == "Thakurova"
           && i6 . Region () == "Dejvice"
           && i6 . ID () == 12345
           && i6 . Owner () == "CVUT" );
  i6 . Next ();
  assert ( ! i6 . AtEnd ()
           && i6 . City () == "Prague"
           && i6 . Addr () == "Technicka"
           && i6 . Region () == "Dejvice"
           && i6 . ID () == 9873
           && i6 . Owner () == "CVUT" );
  i6 . Next ();
  assert ( i6 . AtEnd () );

  assert ( x . Add ( "Liberec", "Evropska", "Librec", 4552 ) );
}

static void test1 ( void )
{
  CLandRegister x;
  string owner;

  assert ( x . Add ( "Prague", "Thakurova", "Dejvice", 12345 ) );
  assert ( x . Add ( "Prague", "Evropska", "Vokovice", 12345 ) );
  assert ( x . Add ( "Prague", "Technicka", "Dejvice", 9873 ) );
  assert ( ! x . Add ( "Prague", "Technicka", "Hradcany", 7344 ) );
  assert ( ! x . Add ( "Brno", "Bozetechova", "Dejvice", 9873 ) );
  assert ( !x . GetOwner ( "Prague", "THAKUROVA", owner ) );
  assert ( !x . GetOwner ( "Hradcany", 7343, owner ) );
  CIterator i0 = x . ListByAddr ();
  assert ( ! i0 . AtEnd ()
           && i0 . City () == "Prague"
           && i0 . Addr () == "Evropska"
           && i0 . Region () == "Vokovice"
           && i0 . ID () == 12345
           && i0 . Owner () == "" );
  i0 . Next ();
  assert ( ! i0 . AtEnd ()
           && i0 . City () == "Prague"
           && i0 . Addr () == "Technicka"
           && i0 . Region () == "Dejvice"
           && i0 . ID () == 9873
           && i0 . Owner () == "" );
  i0 . Next ();
  assert ( ! i0 . AtEnd ()
           && i0 . City () == "Prague"
           && i0 . Addr () == "Thakurova"
           && i0 . Region () == "Dejvice"
           && i0 . ID () == 12345
           && i0 . Owner () == "" );
  i0 . Next ();
  assert ( i0 . AtEnd () );

  assert ( x . NewOwner ( "Prague", "Thakurova", "CVUT" ) );
  assert ( ! x . NewOwner ( "Prague", "technicka", "CVUT" ) );
  assert ( ! x . NewOwner ( "prague", "Technicka", "CVUT" ) );
  assert ( ! x . NewOwner ( "dejvice", 9873, "CVUT" ) );
  assert ( ! x . NewOwner ( "Dejvice", 9973, "CVUT" ) );
  assert ( ! x . NewOwner ( "Dejvice", 12345, "CVUT" ) );
  assert ( x . Count ( "CVUT" ) == 1 );
  CIterator i1 = x . ListByOwner ( "CVUT" );
  assert ( ! i1 . AtEnd ()
           && i1 . City () == "Prague"
           && i1 . Addr () == "Thakurova"
           && i1 . Region () == "Dejvice"
           && i1 . ID () == 12345
           && i1 . Owner () == "CVUT" );
  i1 . Next ();
  assert ( i1 . AtEnd () );

  assert ( ! x . Del ( "Brno", "Technicka" ) );
  assert ( ! x . Del ( "Karlin", 9873 ) );
  assert ( x . Del ( "Prague", "Technicka" ) );
  assert ( ! x . Del ( "Prague", "Technicka" ) );
  assert ( ! x . Del ( "Dejvice", 9873 ) );
}

int main ( void )
{
  test0();
  test1();
  return 0;
}
//#endif  //__PROGTEST__ */