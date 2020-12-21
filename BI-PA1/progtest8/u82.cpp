TOFFICE          * initOffice   ()
{
    TOFFICE * a;
    a = ( TOFFICE * ) malloc ( sizeof ( *a ) );
    a -> m_Emp = NULL;
    a -> m_Car = NULL;
    return a;
}
void               addEmployee  ( TOFFICE         * office,
                                  const char      * name )
{
    TEMPLOYEE * a = ( TEMPLOYEE * ) malloc ( sizeof ( TEMPLOYEE ) );
    a -> m_Next = office -> m_Emp;
    a -> m_Name = ( char * ) malloc ( strlen ( name ) + 10 );
    strcpy ( a -> m_Name, name );
    a -> m_Car = NULL;
    office -> m_Emp = a;
}
void               addCar       ( TOFFICE         * office,
                                  const char      * model )
{
    TCAR * a = ( TCAR * ) malloc ( sizeof ( TCAR ) );
    a -> m_Next = office -> m_Car;
    a -> m_Model = ( char * ) malloc ( strlen ( model ) + 10 );
    strcpy ( a -> m_Model, model );
    office -> m_Car = a;
}
TOFFICE          * cloneOffice  ( TOFFICE         * office )
{
    TOFFICE * clone = NULL;
    TEMPLOYEE * temp_e = NULL, * start_temp_e = NULL, * end_temp_e = NULL, * start_e = office -> m_Emp;
    TCAR * temp_c = NULL, * start_temp_c = NULL, * end_temp_c = NULL, * start_c = office -> m_Car;
    clone = initOffice ();
    while ( office -> m_Emp != NULL ) {
        temp_e = ( TEMPLOYEE * ) malloc ( sizeof ( TEMPLOYEE ) );
        temp_e -> m_Name = ( char * ) malloc ( strlen ( office -> m_Emp -> m_Name ) + 10 );
        strcpy ( temp_e -> m_Name, office -> m_Emp -> m_Name );
        temp_e -> m_Car = NULL;
        temp_e -> m_Next = NULL;
        if ( ! end_temp_e ) {
            start_temp_e = temp_e;
        }
        else {
            end_temp_e -> m_Next = temp_e;
        }
        end_temp_e = temp_e;
        office -> m_Emp = office -> m_Emp -> m_Next;
    }
    clone -> m_Emp = start_temp_e;
    office -> m_Emp = start_e;
    
    while ( office -> m_Car != NULL ) {
        temp_c = ( TCAR * ) malloc ( sizeof ( TCAR ) );
        temp_c -> m_Model = ( char * ) malloc ( strlen ( office -> m_Car -> m_Model ) + 10 );
        strcpy ( temp_c -> m_Model, office -> m_Car -> m_Model );
        temp_c -> m_Next = NULL;
        if ( ! end_temp_c ) {
            start_temp_c = temp_c;
        }
        else {
            end_temp_c -> m_Next = temp_c;
        }
        end_temp_c = temp_c;
        office -> m_Car = office -> m_Car -> m_Next;
    }
    clone -> m_Car = start_temp_c;
    office -> m_Car = start_c;
    
    int posEmp = 1, posCar = 1;
    TCAR * carOfEmp = NULL;
    while ( office -> m_Emp != NULL ) {
        while ( office -> m_Emp -> m_Car == NULL && office -> m_Emp != NULL ) {
            office -> m_Emp = office -> m_Emp -> m_Next;
            if ( office -> m_Emp == NULL ) {
                break;
            }
            posEmp++;
        }
        if ( office -> m_Emp != NULL ) {
            
            carOfEmp = office -> m_Emp -> m_Car;
            office -> m_Car = start_c;
            while ( office -> m_Car != carOfEmp ) {
                office -> m_Car = office -> m_Car -> m_Next;
                posCar++;
            }
            for ( int i = 1; i < posEmp; i++ ) {
                clone -> m_Emp = clone -> m_Emp -> m_Next;
            }
            for ( int i = 1; i < posCar; i++ ) {
                clone -> m_Car = clone -> m_Car -> m_Next;
            }
            clone -> m_Emp -> m_Car = clone -> m_Car;
            clone -> m_Emp = start_temp_e;
            clone -> m_Car = start_temp_c;
            office -> m_Car = start_c;
            posCar = 1;
            posEmp++;
            office -> m_Emp = office -> m_Emp -> m_Next;
        }
    }
    
    clone -> m_Emp = start_temp_e;
    clone -> m_Car = start_temp_c;
    office -> m_Emp = start_e;
    office -> m_Car = start_c;
    return clone;
}
void               freeOffice   ( TOFFICE         * office )
{
    TEMPLOYEE * help_e = NULL;
    while ( office -> m_Emp != NULL ) {
        free ( office -> m_Emp -> m_Name );
        help_e = office -> m_Emp -> m_Next;
        free ( office -> m_Emp );
        office -> m_Emp = help_e;
    }
    TCAR * help_c = NULL;
    while ( office -> m_Car != NULL ) {
        free ( office -> m_Car -> m_Model );
        help_c = office -> m_Car -> m_Next;
        free ( office -> m_Car );
        office -> m_Car = help_c;
    }
    free ( office );
}
