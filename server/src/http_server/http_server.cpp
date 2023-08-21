//
// Created by osia on 23.06.23.
//
#define CROW_JSON_USE_MAP

#include "crow.h"
#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include "pgconnection.h"

using namespace pqxx;

std::string CREAT_TABLE_SQL = "CREATE TABLE IF NOT EXISTS public.students\n"
                              "(\n"
                              "    student_id bigint NOT NULL GENERATED ALWAYS AS IDENTITY ( INCREMENT 1 START 1 MINVALUE 1 MAXVALUE 9223372036854775807 CACHE 1 ),\n"
                              "    student_fio character(50) COLLATE pg_catalog.\"default\" NOT NULL,\n"
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

void creatTable(std::shared_ptr<connection> &dbConnection) {
    work W(*dbConnection);
    W.exec(CREAT_TABLE_SQL);
    W.commit();
}

int main() {
    crow::SimpleApp app; //define your crow application
    auto *conn = new PGConnection();

    //define your endpoint at the root directory
    CROW_ROUTE(app, "/students").methods(crow::HTTPMethod::GET)
            ([&conn]() {
                nontransaction N(*conn->get_connection());

                std::vector<crow::json::wvalue> students;

                result R(N.exec("select * from students"));

                for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
                    crow::json::wvalue student = {
                            {"student_id",         c["student_id"].as<int>()},
                            {"student_fio",        c["student_fio"].as<std::string>()},
                            {"student_birth_year", c["student_birth_year"].as<std::string>()},
                            {"student_photo",      (!c["student_photo"].is_null())
                                                   ? c["student_photo"].as<std::string>() : crow::json::wvalue(
                                            nullptr)},
                            {"student_course_num", c["student_course_num"].as<int>()},
                            {"student_group_name", c["student_group_name"].as<std::string>()},
                    };
                    students.push_back(student);
                }

                return crow::json::wvalue({students});
            });

    CROW_ROUTE(app, "/student").methods(crow::HTTPMethod::POST)
            ([&conn](const crow::request &req) {
                std::shared_ptr<connection> db_connection = conn->get_connection();
                auto student = crow::json::load(req.body);
                db_connection->prepare("add_student",
                                       "INSERT INTO public.students (student_fio, student_birth_year, student_photo, student_course_num, student_group_name) VALUES ($1, $2, $3, $4, $5);");
                work W(*db_connection);
                return crow::response(200, "Student successfully added.");
            });

    CROW_ROUTE(app, "/student/delete/<int>").methods(crow::HTTPMethod::DELETE)
            ([&conn](int id) {

                try {
                    work W(*conn->get_connection());

                    std::string deleteSQL{
                            "DELETE FROM public.students WHERE student_id = " + to_string(id) + ";"
                    };

                    result R(W.exec("select * from students where student_id = " + to_string(id) + ";"));

                    if (R.empty()) {
                        return crow::response(404, "Student not found.");
                    }

                    W.exec(deleteSQL);
                    W.commit();
                } catch (const std::exception &e) {
                    return crow::response(500);
                }

                return crow::response(200, "Student successfully deleted");
            });

    CROW_ROUTE(app, "/student/update/<int>").methods(crow::HTTPMethod::PATCH)
            ([&conn](const crow::request &req, int id) {
                crow::json::rvalue dataToChange = crow::json::load(req.body);

                std::string changedField{};
                for (const auto &fieldKey: dataToChange.keys()) {
                    const auto &field = dataToChange[fieldKey];
                    if (field.t() == crow::json::type::Number) {
                        changedField.append(fieldKey + "=" + to_string(field.i()) + ", ");
                    } else {
                        changedField.append(fieldKey + "='" + std::string{field.s()} + "', ");
                    }
                }
                changedField.resize(changedField.size() - 2);

                try {
                    work W(*conn->get_connection());

                    std::string updateSQL{
                            "UPDATE public.students SET " + changedField + " WHERE student_id = " + to_string(id) + ";"
                    };

                    W.exec(updateSQL);
                    W.commit();
                } catch (const std::exception &e) {
                    return crow::response(500);
                }

                return crow::response(200, "Student successfully updated.");
            });

    try {
        std::shared_ptr<connection> C = conn->get_connection();
        if (C->is_open()) {
            std::cout << "Opened database successfully: " << C->dbname() << std::endl;
        } else {
            std::cout << "Can't open database" << std::endl;
            return 1;
        }

        creatTable(C);
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    //set the port, set the app to run on multiple threads, and run the app
    app.port(8080).multithreaded().run();
}