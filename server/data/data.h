#pragma once
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstddef>
#include <odb/core.hxx>
#include <odb/forward.hxx>
#include <odb/nullable.hxx>
#include <string>

namespace VidNovaData {

////////////////////////////////////////////////
// session 类  sessionId -> userId -> Id
#pragma db object table("session_table")
class Session {
  public:
    using ptr = std::shared_ptr<Session>;
    Session();
    Session(const std::string &session_id);
    Session(const std::string &session_id, const std::string &user_id);

    std::size_t                getId() const;
    const std::string          getSessionId() const;
    odb::nullable<std::string> getUserId() const;

    void setId(size_t id_out);
    void setSessionId(const std::string &session_id);
    void setUserId(const std::string &user_id);

    ~Session();

  private:
    friend class odb::access;
#pragma db id auto // auto -> AUTO_INCREMENT
    size_t _id;
#pragma db unique;
#pragma db unique;
    std::string _session_id;
#pragma db index;
    odb::nullable<std::string> _user_id;
};
////////////////////////////////////////////////

////////////////////////////////////////////////
#pragma db object table("file_table")
class File {
  public:
    using ptr = std::shared_ptr<File>;
    File();
    File(const std::string file_id, const std::string &upload_id, const std::string &path, size_t size,
         const std::string &mime);

    size_t             getId() const;
    const std::string &getFileId() const;
    const std::string &getUploaderId() const;
    const std::string &getPath() const;
    size_t             getSize() const;
    const std::string &getMime() const;

    void setId(size_t id_out);
    void setFileId(const std::string &file_id);
    void setUploaderId(const std::string &uploader_id);
    void setPath(const std::string &path);
    void setSize(size_t size);
    void setMime(const std::string &mime);

  private:
    friend class odb::access;
#pragma db id auto // auto -> AUTO_INCREMENT
    size_t _id;

#pragma db unique;
    std::string _file_id;

#pragma db index;
    std::string _uploader_id; // 上传用户Id

    std::string _path;

    size_t _size;

    std::string _mime;
};

} // namespace VidNovaData
