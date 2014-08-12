//
//	SQL CONNECTOR. tumanoid@list.ru 2014
//
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "mysql_connection.h"
#include "mysql_driver.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>


static sql::Driver *driver;
static sql::Connection *con;
static sql::Statement *stmt;
static sql::ResultSet *res;


extern "C" void sqlConnect ()
{
	try
	{
		driver = get_driver_instance ();
		con = driver->connect ("tcp://188.120.224.62:3306","root", "DrCranch79");
		con->setSchema ( "test" );
		stmt = con->createStatement ();
	}
	catch ( sql::SQLException &e )
    {
		printf ("SQL err\n");
		std::cout << e.what () << " ERR_CODE: " << e.getErrorCode () << std::endl;
    }
}


extern "C" void sqlQuerry ( const char* str )
{	
	try
	{
		//stmt = con->createStatement ();

		stmt->execute ( str );
		
		res  = stmt->executeQuery ( "SELECT * FROM `ФИО`" );		
		while ( res->next() )
		{
			printf ("%s %s %s %s \n", res->getString (1).c_str (),
								res->getString (2).c_str (),
								res->getString (3).c_str (),
								res->getString (4).c_str ());					
		}
		delete res;
		delete stmt;
    }
    catch ( sql::SQLException &e )
    {
		printf ("SQL err\n");
		std::cout << e.what () << " ERR_CODE: " << e.getErrorCode () << std::endl;
    }
    
}

extern "C" void dur ()
{
	printf ("***********LIB**********\n");
}

