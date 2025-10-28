#include "session.h"

namespace VidNovaData {

OpSession(odb::database &db, sw::redis::Redis &redis,
          VidNovaMq::Publisher &publisher)
    : _db(db), _redis(redis), _publisher(publisher) {}

// 向数据库 新增会话
void OpSession::addSession(Session &session) {}

// 更新 数据库的会话
void OpSession::updateSession(Session &session) {}

// 通过会话Id 删除会话
void OpSession::removeBySessionId(const std::string &session_id) {}

// 通过 用户id 删除
void OpSession::removeByUserId(const std::string &user_id) {}

// 获取会话信息
Session::ptr OpSession::findSessionBySessionId(const std::string &session_id) {}

// 私有接口
// 向数据库 添加 会话信息
void OpSession::insertSessionToDb(Session &session) {}

// 从数据库 获取会话信息
Session::ptr OpSession::selectSessionFromDb(const std::string &session_id) {}

// 修改数据库 会话 信息
void OpSession::updateSessionInfoInDb(Session &session) {}

// 通过 用户 Id 删除数据库 会话信息
void OpSession::removeSessionIdFromDbByUserId(const std::string &user_id) {}

// 向 Redis 获取 会话缓存
void OpSession::insertSessionToRedis(Session &session) {}

// 从redis 获取 会话缓存
Session::ptr OpSession::selectSessionFromRedis(const std::string &session_id) {}

// 通过 会话 Id 删除 缓存 会话
void OpSession::removeSessionFromRedisBySessionId(
    const std::string &session_id) {}

// 发布 用于 二删的消息
void OpSession::publishRemoveMsg(const std::string &session_id) {}

// 通过 会话 Id 获取缓存的key //todo暂时不知道有啥用
std::string OpSession::getCacheKeyBySessionId(const std::string &session_id) {}

} // namespace VidNovaData
