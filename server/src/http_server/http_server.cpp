//
// Created by osia on 23.06.23.
//
#include "crow.h"
//#include "crow_all.h"
#include <string>
#include <format>
#include <string_view>
#include <iostream>
#include <pqxx/pqxx>

//using namespace std;
using namespace pqxx;

std::string CREAT_TABLE_SQL = "CREATE TABLE IF NOT EXISTS public.students\n"
                         "(\n"
                         "    student_id bigint NOT NULL GENERATED ALWAYS AS IDENTITY ( INCREMENT 1 START 1 MINVALUE 1 MAXVALUE 9223372036854775807 CACHE 1 ),\n"
                         "    student_fio character(100) COLLATE pg_catalog.\"default\" NOT NULL,\n"
                         "    student_birth_year date NOT NULL,\n"
                         "    student_photo bytea,\n"
                         "    student_course_num bigint NOT NULL,\n"
                         "    student_group_name character(10) COLLATE pg_catalog.\"default\" NOT NULL,\n"
                         "    CONSTRAINT students_pkey PRIMARY KEY (student_id)\n"
                         ")\n"
                         "\n"
                         "TABLESPACE pg_default;\n"
                         "\n"
                         "ALTER TABLE IF EXISTS public.students\n"
                         "    OWNER to \"user\";";

std::string DB_STRING{"dbname = postgres user = user password = admin hostaddr = 127.0.0.1 port = 54320"};

//class DataBaseManager {
//public:
//    DataBaseManager();
//private:
//    connection* connection_ptr;
//    void creatDB(string sql);
//};
//
//DataBaseManager::DataBaseManager(){
//    try {
//        connection C(DB_STRING);
//        connection_ptr = &C;
//        if (C.is_open()) {
//            cout << "Opened database successfully: " << C.dbname() << endl;
//        } else {
//            cout << "Can't open database" << endl;
//        }
//    }
//    catch (const std::exception &e) {
//        cerr << e.what() << std::endl;
//    }
//}
//
//void DataBaseManager::creatDB(string sql) {
//    work W(connection_ptr);
//
//}

void creatTable(connection &dbConnection) {
    work W(dbConnection);
    W.exec(CREAT_TABLE_SQL);
    W.commit();
}

int main() {
    crow::SimpleApp app; //define your crow application

    //define your endpoint at the root directory
    CROW_ROUTE(app, "/students").methods(crow::HTTPMethod::GET)
    ([](){
        connection C(DB_STRING);
        work W(C);
        std::string sql{"select * from students"};
        result R(W.exec(sql));

        std::vector<crow::json::wvalue> students;

        for (result::const_iterator c = R.begin(); c != R.end(); ++c){
            crow::json::wvalue student = {
                    {"student_id", c["student_id"].as<int>()},
                    {"student_fio", c["student_fio"].as<std::string>()},
                    {"student_birth_year", c["student_birth_year"].as<std::string>()},
                    {"student_photo", (!c["student_photo"].is_null()) ? c["student_photo"].as<std::string>() : "null" },
                    {"student_course_num", c["student_course_num"].as<int>()},
                    {"student_group_name", c["student_group_name"].as<std::string>()},
            };
            students.push_back(student);
        }

        crow::json::wvalue x = {students};
        return x;
    });

    CROW_ROUTE(app, "/student").methods(crow::HTTPMethod::POST)
            ([](const crow::request& req){
                auto student = crow::json::load(req.body);
                std::cout << student["student_course_num"] << std::endl;

                try {
                    connection C(DB_STRING);
                    work W(C);
                    std::string insert_sql{"INSERT INTO public.students(student_fio, student_birth_year, student_course_num, student_group_name) VALUES ('Egor', '2020-11-22', 5, 'O4150');"};
                    W.exec(insert_sql);
                    W.commit();
                } catch (const std::exception &e) {
                    return crow::response(500);
                }

                return crow::response(200, std::string{"Student successfully added."});
            });


    try {
        connection C(DB_STRING);
        if (C.is_open()) {
            std::cout << "Opened database successfully: " << C.dbname() << std::endl;
        } else {
            std::cout << "Can't open database" << std::endl;
            return 1;
        }

        creatTable(C);
//        {
//        }
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    //set the port, set the app to run on multiple threads, and run the app
    app.port(8080).multithreaded().run();
}