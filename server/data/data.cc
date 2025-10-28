
#include "data.h"

namespace VidNovaData {
////////////////////////////////////
Session::Session() = default;
Session::Session(const std::string &session_id) : _session_id(session_id) {}
Session::Session(const std::string &session_id, const std::string &user_id)
    : _session_id(session_id), _user_id(user_id) {}
std::size_t Session::getId() const { return _id; }
const std::string Session::getSessionId() const { return _session_id; }
odb::nullable<std::string> Session::getUserId() const { return _user_id; }

void Session::setId(size_t id_out) { _id = id_out; }
void Session::setSessionId(const std::string &session_id) {
  _session_id = session_id;
}
void Session::setUserId(const std::string &user_id) { _user_id = user_id; }
Session::~Session() {}
////////////////////////////////////

////////////////////////////////////
File::File() = default;
File::File(const std::string file_id, const std::string &upload_id,
           const std::string &path, size_t size, const std::string &mime)
    : _file_id(file_id), _uploader_id(upload_id), _path(path), _size(size),
      _mime(mime) {}
size_t File::getId() const { return _id; }
const std::string &File::getFileId() const { return _file_id; }
const std::string &File::getUploaderId() const { return _uploader_id; }
const std::string &File::getPath() const { return _path; }
size_t File::getSize() const { return _size; }
const std::string &File::getMime() const { return _mime; }

void File::setId(size_t id_out) { _id = id_out; }
void File::setFileId(const std::string &file_id) { _file_id = file_id; }
void File::setUploaderId(const std::string &uploader_id) {
  _uploader_id = uploader_id;
}
void File::setPath(const std::string &path) { _path = path; }
void File::setSize(size_t size) { _size = size; }
void File::setMime(const std::string &mime) { _mime = mime; }
////////////////////////////////////

} // namespace VidNovaData