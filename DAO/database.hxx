#pragma once

#include <string>
#include <memory>   
#include <cstdlib> 
#include <iostream>

#include <odb/database.hxx>
#include <odb/connection.hxx>
#include <odb/transaction.hxx>
#include <odb/schema-catalog.hxx>
#include <odb/mssql/database.hxx>

inline std::auto_ptr<odb::database> create_database(int& argc, char* argv[])
{
	using namespace std;
	using namespace odb::core;

	if (argc > 1 && argv[1] == string("--help"))
	{
		cout << "Usage: " << argv[0] << " [options]" << endl
			<< "Options:" << endl;

		odb::mssql::database::print_usage(cout);

		exit(0);
	}
    auto_ptr<database> db(new odb::mssql::database("", "", "TransportEmpireDB"));

	return db;
}

