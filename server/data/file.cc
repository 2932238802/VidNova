#include "file.h"
#include "data.h"
#include "file-odb.hxx"
#include <odb/core.hxx>
#include <odb/database.hxx>
#include <odb/forward.hxx>
#include <odb/query.hxx>

namespace VidNovaData {
OpFile::OpFile(odb::database &db) : _db(db) {}

void OpFile::insert(File &file) { _db.persist(file); }

// 必须是 findById 获得的对象
void OpFile::update(File &file) { _db.update(file); }

void OpFile::remove(const std::string &file_id) {
  using query = odb::query<File>;
  _db.erase_query<File>(query::file_id == file_id);
}

File::ptr OpFile::findById(const std::string &file_id) {
  using query = odb::query<File>;
  return _db.query_one<File>(query::file_id == file_id);
}

} // namespace VidNovaData
