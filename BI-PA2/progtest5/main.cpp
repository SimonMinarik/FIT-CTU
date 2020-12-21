class CMailLog
{
  public:
    int ParseLog ( istream & in );
    list<CMail> ListMail ( const CTimeStamp & from, const CTimeStamp & to ) const;
    set<string> ActiveUsers ( const CTimeStamp & from, const CTimeStamp & to ) const;
    int getMonth ( const string & x );


  private:
    vector<CMail> m_MailVec;
    multimap<string, CMail> m_MailMap;
};

int CMailLog::ParseLog ( istream & in ){
  int count = 0;
  string month, day, year, thyme, relay, id, user; 
  while( in >> month >> day >> year >> thyme >> relay >> id ){
    getline(in, user);
    replace(thyme.begin(), thyme.end(), ':', ' ');
    stringstream ss(thyme);
    string hod, min, sek;
    ss >> hod;
    ss >> min;
    ss >> sek;
    if ( user.substr(1,5) == "from=" ){
      CMail x = CMail(CTimeStamp(stoi(year),getMonth(month),stoi(day),stoi(hod),stoi(min),stod(sek)), user.substr(6), "", "");
      m_MailMap.insert(pair <string, CMail> (id, x) );
    }
    else if ( user.substr(1,8) == "subject=" ){
      m_MailMap.insert(pair <string, CMail> (id, CMail(CTimeStamp(stoi(year),getMonth(month),stoi(day),stoi(hod),stoi(min),stod(sek)), "", "", user.substr(9))) );
    }
    else if ( user.substr(1,3) == "to=" ) {
      ++count;
      auto it = m_MailMap.equal_range(id);
      string from, subject;
      auto i = it.first;
      from = i -> second.From();
      ++i;
      subject = i -> second.Subject();
      CMail x = CMail(CTimeStamp(stoi(year),getMonth(month),stoi(day),stoi(hod),stoi(min),stod(sek)), from, user.substr(4), subject );
      auto where = upper_bound(m_MailVec.begin(), m_MailVec.end(), x, [](const CMail & a, const CMail & b){return a . CompareByTime(b . TimeStamp()) < 0;});
      m_MailVec.insert( where, x );
    }
  }
  return count;
  
}

list<CMail> CMailLog::ListMail ( const CTimeStamp & from, const CTimeStamp & to ) const{
  CMail x = CMail(from, "", "", "");
  list<CMail> y;
  auto index = lower_bound(m_MailVec.begin(), m_MailVec.end(), x, []( const CMail & a, const CMail & b ){ return a.CompareByTime (b) < 0; } );
  while ( m_MailVec[index - m_MailVec.begin()].CompareByTime(to) <= 0 && index != m_MailVec.end() ){
    if ( m_MailVec[index - m_MailVec.begin()].To() != "" ) {
      y.push_back(m_MailVec[index - m_MailVec.begin()]);
    }
    index ++;
  }
  
  return y;
}

set<string> CMailLog::ActiveUsers ( const CTimeStamp & from, const CTimeStamp & to ) const{
  CMail x = CMail(from, "", "", "");
  set<string> y;
  auto index = lower_bound(m_MailVec.begin(), m_MailVec.end(), x, []( const CMail & a, const CMail & b ){ return a.CompareByTime (b) < 0; } );
  while ( m_MailVec[index - m_MailVec.begin()].CompareByTime(to) <= 0 && index != m_MailVec.end() ){
    y.insert(m_MailVec[index - m_MailVec.begin()].From());
    y.insert(m_MailVec[index - m_MailVec.begin()].To());
    index ++;
  }  
  return y;
}

int CMailLog::getMonth ( const string & x ){
  if ( x == "Jan" ) {
    return 1;
  } else if ( x == "Feb" ) {
    return 2;
  } else if ( x == "Mar" ) {
    return 3;
  } else if ( x == "Apr" ) {
    return 4;
  } else if ( x == "May" ) {
    return 5;
  } else if ( x == "Jun" ) {
    return 6;
  } else if ( x == "Jul" ) {
    return 7;
  } else if ( x == "Aug" ) {
    return 8;
  } else if ( x == "Sep" ) {
    return 9;
  } else if ( x == "Oct" ) {
    return 10;
  } else if ( x == "Nov" ) {
    return 11;
  } else {
    return 12;
  }
  
}