#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "mysql_connection.h"
#include "mysql_driver.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>


extern "C" void u_print ( const char * str )
{
	printf ( "%s", str );
}


sql::Driver *driver;
sql::Connection *con;
sql::Statement *stmt;
sql::ResultSet *res;

extern "C" void start ( const char * str )
{
	printf ("Init begin...\n");
	try
	{
		driver = get_driver_instance ();
		con = driver->connect ("tcp://188.120.224.62:3306","root", "DrCranch79");
		con->setSchema ( "test" );
		stmt = con->createStatement ();
		//res  = 
		stmt->execute ( "INSERT INTO `ФИО` (`Фамилия`, `Имя`, `Отчество`) VALUES ('C++','C++','C++')" );

		res  = stmt->executeQuery ( "SELECT * FROM `ФИО` AS _msg" );		
		while ( res->next() )
		{
			//std::cout << res->getString ("_msg");
			//std::cout << res->getString (1);
			//std::cout << res->getString (2);
			//std::cout << res->getString (3);
			
			//printf ("%s %s %s", res->getString (1), res->getString (2), res->getString (3));
		//printf ( "===================================\n");
			printf ("%s %s %s %s \n", res->getString (1).c_str (),
								res->getString (2).c_str (),
								res->getString (3).c_str (),
								res->getString (4).c_str ());
		}
		
    }
    catch ( sql::SQLException &e )
    {
		printf ("SQL err\n");
		std::cout << e.what ();
    }
}

extern "C" void dur ()
{
	printf ("***********LIB**********\n");
}

