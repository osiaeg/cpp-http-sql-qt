//
// Created by osia on 21.08.23.
//

#ifndef HTTP_SERVER_PGCONNECTION_H
#define HTTP_SERVER_PGCONNECTION_H


#include <memory>
#include <pqxx/pqxx>
#include <iostream>

using namespace pqxx;

class PGConnection {
public:
    PGConnection();
    std::shared_ptr<connection> get_connection() const;
private:
    std::string m_dbhost = "127.0.0.1";
    int         m_dbport = 54320;
    std::string m_dbname = "postgres";
    std::string m_dbuser = "user";
    std::string m_dbpass = "admin";

    std::shared_ptr<connection>  m_connection;
};

#endif //HTTP_SERVER_PGCONNECTION_H
