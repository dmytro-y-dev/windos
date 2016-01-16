#include "Schema.h"

using namespace todos_model_schema;

Schema::Schema(const char *filename) : m_db(nullptr), m_referencesCounter(nullptr)
{
  Open(filename);
}

Schema::Schema(const Schema &schema) : m_db(schema.m_db), m_referencesCounter(schema.m_referencesCounter)
{
  if (m_referencesCounter != nullptr) {
    *m_referencesCounter += 1;
  }
}

Schema::~Schema()
{
  Close();
}

Schema::DatabaseHandle Schema::GetDatabaseHandle() const
{
  return m_db;
}

bool Schema::IsOpened() const
{
  return (m_db != nullptr);
}

bool Schema::Open(const char *filename)
{
  if (m_db != nullptr) {
    Close();
  }

  if (sqlite3_open(filename, &m_db) != SQLITE_OK) {
    return false;
  }

  m_referencesCounter = new CounterValue;
  *m_referencesCounter = 1;

  return true;
}

void Schema::Close()
{
  if (m_db == nullptr) {
    // No connection is present -- nothing to close

    return;
  }

  *m_referencesCounter -= 1;

  if (*m_referencesCounter == 0) {
    // If no one references to connection, then close it and remove references counter ...

    sqlite3_close(m_db);

    m_db = nullptr;

    delete m_referencesCounter;
    m_referencesCounter = nullptr;
  } else {
    // ... otherwise detach from connection and references counter

    m_db = nullptr;
    m_referencesCounter = nullptr;
  }
}

void Schema::CreateTables()
{
  // TODO: Enable foreign key constraints

  static const char* query =
    "CREATE TABLE `Category`( "
    "`category_id` INTEGER PRIMARY KEY, "
    "`name` VARCHAR(255) UNIQUE NOT NULL "
    "); "
    "CREATE TABLE `Task`( "
    "`task_id` INTEGER PRIMARY KEY, "
    "`category_id` INT NOT NULL REFERENCES `Category`(`category_id`) ON UPDATE CASCADE ON DELETE CASCADE, "
    "`title` VARCHAR(255) NOT NULL, "
    "`priority` VARCHAR(20) NOT NULL, "
    "`creation_date` DATETIME NULL, "
    "`due_date` DATETIME NULL, "
    "`reminder_date` DATETIME NULL, "
    "`status` VARCHAR(20) NOT NULL "
    "); "
    "CREATE TABLE `Commentary`( "
    "`commentary_id` INTEGER PRIMARY KEY, "
    "`task_id` INT NOT NULL REFERENCES `Task`(`task_id`) ON UPDATE CASCADE ON DELETE CASCADE, "
    "`published_on` DATETIME NOT NULL, "
    "`type` VARCHAR(20) NOT NULL, "
    "`content` BLOB NOT NULL "
    "); ";

  sqlite3_exec(m_db, query, nullptr, nullptr, nullptr);
}

void Schema::DestroyTables()
{
  static const char* query =
    "DROP TABLE `Commentary`; "
    "DROP TABLE `Task`; "
    "DROP TABLE `Category`; ";

  sqlite3_exec(m_db, query, nullptr, nullptr, nullptr);
}

Schema& Schema::operator=(const Schema &schema)
{
  if (this == &schema) {
    return *this;
  }

  Close();

  m_db = schema.m_db;

  m_referencesCounter = schema.m_referencesCounter;
  *m_referencesCounter += 1;

  return *this;
}
