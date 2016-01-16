#include "Workspace.h"

using todos_model_workspace::Workspace;
using todos_model_workspace::WorkspaceBadSchemaException;

WorkspaceBadSchemaException::WorkspaceBadSchemaException(const WorkspaceBadSchemaException::String& hint) : m_hint(hint)
{
}

WorkspaceBadSchemaException::String WorkspaceBadSchemaException::GetHint() const
{
  return m_hint;
}

Workspace::Workspace()
{
}

bool Workspace::Open(const String & location)
{
  if (!m_schema.Open(location.c_str())) {
    m_location = "";
    m_schema = Schema("");

    return false;
  }

  m_location = location;

  return true;
}

bool Workspace::IsReady() const
{
  if (m_schema.GetDatabaseHandle() == nullptr) {
    return false;
  }

  return true;
}

Workspace::String Workspace::GetLocation() const
{
  return m_location;
}

Workspace::Schema Workspace::GetSchema() const
{
  return m_schema;
}

Workspace::TaskRepository Workspace::GetTaskRepository() const
{
  if (m_schema.GetDatabaseHandle() == nullptr) {
    throw WorkspaceBadSchemaException("Schema is not opened!");
  }

  return TaskRepository(m_schema);
}

Workspace::CategoryRepository Workspace::GetCategoryRepository() const
{
  if (m_schema.GetDatabaseHandle() == nullptr) {
    throw WorkspaceBadSchemaException("Schema is not opened!");
  }

  return CategoryRepository(m_schema);
}

Workspace::CommentaryRepository Workspace::GetCommentaryRepository() const
{
  if (m_schema.GetDatabaseHandle() == nullptr) {
    throw WorkspaceBadSchemaException("Schema is not opened!");
  }

  return CommentaryRepository(m_schema);
}
