#ifndef TODOS_MODEL_REPOSITORY_TASKFILTERSETTINGS_H
#define TODOS_MODEL_REPOSITORY_TASKFILTERSETTINGS_H

#include <string>
#include <utility/DateTime.h>

namespace todos_model_repository {
  class TaskFilterSettings
  {
  public:
    typedef todos_utility::DateTime DateTime;

  private:
    std::string m_category;
    DateTime m_dueDateLowerLimit;
    DateTime m_dueDateUpperLimit;

    bool m_byCategory;
    bool m_byDueDate;

  public:
    TaskFilterSettings();

    bool IsFilterByCategory() const;
    bool IsFilterByDueDate() const;
    std::string GetCategory() const;
    DateTime GetDueDateUpperLimit() const;
    DateTime GetDueDateLowerLimit() const;

    void EnableFilterByCategory(bool byCategory = true);
    void EnableFilterByDueDate(bool byDueDate = true);
    void SetCategory(const std::string& category);
    void SetDueDateUpperLimit(const DateTime& dueDateUpperLimit);
    void SetDueDateLowerLimit(const DateTime& dueDateLowerLimit);
  };
}

#endif //TODOS_MODEL_REPOSITORY_TASKFILTERSETTINGS_H
