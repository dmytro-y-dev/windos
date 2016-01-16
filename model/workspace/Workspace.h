#ifndef TODOS_MODEL_WORKSPACE_WORKSPACE_H
#define TODOS_MODEL_WORKSPACE_WORKSPACE_H

#include <string>

#include <model/schema/Schema.h>

#include <model/repository/task/TaskRepository.h>
#include <model/repository/category/CategoryRepository.h>
#include <model/repository/commentary/CommentaryRepository.h>

namespace todos_model_workspace {
  class WorkspaceBadSchemaException
  {
  public:
    typedef std::string String;

  private:
    String m_hint;

  public:
    WorkspaceBadSchemaException(const String& hint);

    String GetHint() const;
  };

  class Workspace
  {
  public:
    typedef todos_model_schema::Schema Schema;
    typedef std::string String;
    typedef todos_model_repository::TaskRepository TaskRepository;
    typedef todos_model_repository::CategoryRepository CategoryRepository;
    typedef todos_model_repository::CommentaryRepository CommentaryRepository;

  private:
    String m_location;
    Schema m_schema;

  public:
    Workspace();

    bool Open(const String& location);

    bool IsReady() const;

    String GetLocation() const;
    Schema GetSchema() const;
    TaskRepository GetTaskRepository() const;
    CategoryRepository GetCategoryRepository() const;
    CommentaryRepository GetCommentaryRepository() const;
  };
}

#endif //TODOS_MODEL_WORKSPACE_WORKSPACE_H
