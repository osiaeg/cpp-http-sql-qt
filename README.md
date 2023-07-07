# cpp-http-sql-qt

## Start docker containers
```shell
docker-compose up -d
```

## PgAdmin4
### Connection to pgadmin
http://localhost:5050

Login: raj@nola.com

Password: admin
### Connection to db
General Tab

Name: Any_name_what_you_want

Connection Tab

Host name/address: local_pgdb(container_name of postgresql)

port: 5432

Username: user

Password: admin

## Postgresql
Create table
```sql
CREATE TABLE IF NOT EXISTS public."Students"
(
    "Student_id" bigint NOT NULL,
    "FIO" character(100) COLLATE pg_catalog."default" NOT NULL,
    birth_year date NOT NULL,
    photo bytea,
    course_num bigint NOT NULL,
    "group" character(10) COLLATE pg_catalog."default" NOT NULL,
    CONSTRAINT "Students_pkey" PRIMARY KEY ("Student_id")
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS public."Students"
    OWNER to "user";
```



