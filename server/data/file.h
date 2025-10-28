#pragma once
#include "data.h"
#pragma once

// 文件表的相关操作

namespace VidNovaData {
class OpFile {
public:
  OpFile(odb::database &db);
  void insert(File &file);
  void update(File &file);
  void remove(const std::string &file_id);
  File::ptr findById(const std::string &file_id);

private:
  odb::database &_db;
};

} // namespace VidNovaData
