class NoRouteException 
{ 
};

template <typename _T, typename _E>
class CNode;

template <typename _T, typename _E>
class CRoute
{
  public:
   CRoute(){
   }
   ~CRoute(){
   }
   void Print (){
     for (auto & x: m_NodeMap) {
      cout << x.first << ": " << x.second << '\n';
     }
   }

   CRoute<_T,_E> & Add ( const _T & from, const _T & to, const _E & x ){
     m_NodeMap.insert( pair<_T, CNode<_T,_E>*>( from, new CNode<_T, _E>( from ) ) );
     m_NodeMap.insert( pair<_T, CNode<_T,_E>*>( to, new CNode<_T, _E>( to ) ) );

     m_NodeMap[from] -> AddStation(to);
     m_NodeMap[from] -> AddEdge(x);
     m_NodeMap[to] -> AddStation(from);
     m_NodeMap[to] -> AddEdge(x);
     return *this;
   }
   list <_T> Find ( const _T & from, const _T & to, function<bool( const _E & x )> filter = []( const _E & x){ return true; } ) {
     list<_T> m_List;
     set<_T> m_Visited;
     queue<CNode<_T,_E>*> m_Queue;

     if ( from == to ) {
       m_List.push_back(from);
       return m_List;
     }

     if ( m_NodeMap.find(from) == m_NodeMap.end() || m_NodeMap.find(to) == m_NodeMap.end() )
     {
       throw NoRouteException();
     }

     CNode<_T,_E>* tmp = m_NodeMap[from];
     tmp -> SetParent ( NULL );
     m_Queue.push(tmp);
     //cout << "mal by byt berlin: " << tmp -> GetCity() << endl;
     m_Visited.insert(from);

     while ( ! m_Queue.empty() ) {
       
       //cout << "👿" << endl;
       auto currentNode = m_Queue.front();
       m_Queue.pop();

       if ( currentNode -> GetCity() == to ) {
         //cout << "😡" << endl;
         int help = 0;
         while ( currentNode != NULL ) {
           m_List.push_front( currentNode -> GetCity() );
           currentNode = currentNode -> GetParent();
           //cout << "potom: " << currentNode -> GetCity() << endl;
           help++;
         }
         return m_List;
       }
       
        //cout << "🧐" << endl;
       for (size_t i = 0; i < currentNode -> GetStationSize(); ++i) {
         //cout << "🤷‍♂️" << endl;
         if ( filter( currentNode -> GetFromEdge(i) ) && ( m_Visited.find(currentNode -> GetFromStation(i)) == m_Visited.end() ) ) {
           tmp = m_NodeMap[currentNode -> GetFromStation(i)];
           m_Queue.push(tmp);
           tmp -> SetParent ( currentNode );
           //cout << "my city: " << currentNode -> GetCity() << endl;
           m_Visited.insert(currentNode -> GetFromStation(i));
         }
       }

       
       //cout << "😍" << endl;
     }
     throw NoRouteException();
   }
   
   map<_T, CNode<_T,_E>*> m_NodeMap;
};

template <typename _T, typename _E>
class CNode {
  public:
  CNode ( const _T & city ) : m_Parent ( NULL ), m_City ( city ) {
  }
  ~CNode (){
  }
  void AddStation ( const _T & from ) {
    m_Station.push_back( from );
  }
  void AddEdge ( const _E & to ) {
    m_Edge.push_back( to );
  }
  unsigned GetStationSize () {
    return m_Station.size();
  }
  _E GetFromEdge ( size_t i ) {
    return m_Edge[i];
  }
  _T GetFromStation ( size_t i ) {
    return m_Station[i];
  }
  void SetParent ( CNode * x ) {
    m_Parent = x;
  }
  CNode* GetParent () {
    return m_Parent;
  }
  _T GetCity () {
    return m_City;
  }
  

  protected:
  CNode* m_Parent;
  _T m_City;
  vector<_T> m_Station;
  vector<_E> m_Edge;
};