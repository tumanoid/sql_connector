//
//	SQL CONNECTOR. tumanoid@list.ru 2014
//


#include <stdio.h>
#include "mysql.h"

#include "common.h"

static MYSQL *sock;
static MYSQL_RES *res;
static char	qbuf [160];

static FILE* err_f;


DLL_EXPORT void sqlConnect ( const char* password )
{
	err_f = fopen ("err_out.txt", "w");
	
	if ( !( sock = mysql_init (0)))
	{
		fprintf ( err_f, "Couldn't initialize mysql struct\n" );
		return;
	}

	mysql_options ( sock, MYSQL_READ_DEFAULT_GROUP, "connect" );

	if (!mysql_real_connect ( sock, "188.120.224.62", "root", password, "test", 3306, NULL, 0 ))

	{
		fprintf ( err_f,"Couldn't connect to engine!\n%s\n", mysql_error ( sock ));
		perror ( "" );
		return;
	}

	sock->reconnect = 1;

	if ( mysql_select_db ( sock,"test" ))
	{
		fprintf ( err_f, "Couldn't select database test: Error: %s\n", mysql_error ( sock ));
	}
}


DLL_EXPORT void sqlSetQuery ( const char* query_str )
{	
	mysql_query ( sock, query_str );
}


DLL_EXPORT void sqlGetQuery ( const char* query_str, char* out_str )
{	
	mysql_query ( sock, query_str );
	
	if ( !( res = mysql_store_result ( sock )))
	{
		fprintf ( err_f, "Couldn't get result from %s\n", mysql_error ( sock ));
		return;
    }
	
	MYSQL_ROW curr_row = mysql_fetch_row ( res );

	int count_row   = mysql_num_rows ( res );
	
	sprintf ( out_str, "%s", curr_row [0] );
	
	mysql_free_result ( res );

	fprintf ( err_f, out_str );	
}


DLL_EXPORT void sqlDisconnect ()
{
	mysql_close(sock);
	fclose ( err_f );
}


DLL_EXPORT void Dur ()
{
}
/*
int main(int argc, char **argv)
{
	printf ( "START \n" );


  MYSQL_ROW row;


  
  char	qbuf[160];
 // sprintf(qbuf,INSERT_QUERY,count,count);

  //	INSERT
  mysql_query ( sock, "INSERT INTO ФИО (Фамилия, Имя, Отчество) VALUES ('BUUUBO', 'Ванючая', 'МУПСТКА')" );

  //	SELECT
	mysql_query ( sock, "SELECT * FROM ФИО" );
	
	if (!(res=mysql_store_result(sock)))
    {
      fprintf(stderr,"Couldn't get result from %s\n",
	      mysql_error(sock));
      exit(1);
    }

    //printf ( "number of fields: %d\n", mysql_num_fields ( res ) );
	int count_field = mysql_num_fields ( res );
	int count_row   = mysql_num_rows ( res );

	for ( int j=0;  j < count_row; j++)
	{
		row = mysql_fetch_row ( res );
		for ( int i=0;  i < count_field; i++)
		{
			printf ("|  %s  |",  row [i]);
		}
		printf ("\n");
	}
    mysql_free_result(res);



  mysql_close(sock);
  
	printf ( "END \n" );

  exit(0);
  return 0;
}
*/