#include "TaskFilterSettings.h"

using todos_model_repository::TaskFilterSettings;

TaskFilterSettings::TaskFilterSettings() :
  m_byCategory(false), m_byDueDate(false), m_showCompleted(false)
{
}

bool TaskFilterSettings::IsShowCompleted() const
{
  return m_showCompleted;
}

bool TaskFilterSettings::IsFilterByCategory() const
{
  return m_byCategory;
}

bool TaskFilterSettings::IsFilterByDueDate() const
{
  return m_byDueDate;
}

std::string TaskFilterSettings::GetCategory() const
{
  return m_category;
}

TaskFilterSettings::DateTime TaskFilterSettings::GetDueDateUpperLimit() const
{
  return m_dueDateUpperLimit;
}

TaskFilterSettings::DateTime TaskFilterSettings::GetDueDateLowerLimit() const
{
  return m_dueDateLowerLimit;
}

void TaskFilterSettings::SetShowCompleted(bool show)
{
  m_showCompleted = show;
}

void TaskFilterSettings::EnableFilterByCategory(bool byCategory)
{
  m_byCategory = byCategory;
}

void TaskFilterSettings::EnableFilterByDueDate(bool byDueDate)
{
  m_byDueDate = byDueDate;
}

void TaskFilterSettings::SetCategory(const std::string &category)
{
  m_category = category;
}

void TaskFilterSettings::SetDueDateUpperLimit(const DateTime &dueDateUpperLimit)
{
  m_dueDateUpperLimit = dueDateUpperLimit;
}

void TaskFilterSettings::SetDueDateLowerLimit(const DateTime &dueDateLowerLimit)
{
  m_dueDateLowerLimit = dueDateLowerLimit;
}
