//
// Created by osia on 21.08.23.
//

#include "pgconnection.h"

PGConnection::PGConnection() {
    m_connection = std::make_shared<connection>("dbname = " + m_dbname +
            " user = " + m_dbuser +
            " password = " + m_dbpass +
            " hostaddr = " + m_dbhost +
            " port = " + to_string(m_dbport)
            );
}

std::shared_ptr<connection> PGConnection::get_connection() const {
    return m_connection;
}
