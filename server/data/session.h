#pragma once
#include "../publisher/publisher.h"
#include "data-odb.hxx"
#include "data.h"
#include <odb/core.hxx>
#include <sw/redis++/redis++.h>

// 会话表的相关操作
namespace VidNovaData {
class OpSession {
public: // 公共接口
  // todo: 这里 可能会加入 rabbitMq
  OpSession(odb::database &db, sw::redis::Redis &redis,
            VidNovaMq::Publisher &publisher);

  // 向数据库 新增会话
  void addSession(Session &session);

  // 更新 数据库的会话
  void updateSession(Session &session);

  // 通过会话Id 删除会话
  void removeBySessionId(const std::string &session_id);

  // 通过 用户id 删除
  void removeByUserId(const std::string &user_id);

  // 获取会话信息
  Session::ptr findSessionBySessionId(const std::string &session_id);

  // 私有接口
private:
  // 向数据库 添加 会话信息
  void insertSessionToDb(Session &session);

  // 从数据库 获取会话信息
  Session::ptr selectSessionFromDb(const std::string &session_id);

  // 修改数据库 会话 信息
  void updateSessionInfoInDb(Session &session);

  // 通过 用户 Id 删除数据库 会话信息
  void removeSessionIdFromDbByUserId(const std::string &user_id);

  // 向 Redis 获取 会话缓存
  void insertSessionToRedis(Session &session);

  // 从redis 获取 会话缓存
  Session::ptr selectSessionFromRedis(const std::string &session_id);

  // 通过 会话 Id 删除 缓存 会话
  void removeSessionFromRedisBySessionId(const std::string &session_id);

  // 发布 用于 二删的消息
  void publishRemoveMsg(const std::string &session_id);

  // 通过 会话 Id 获取缓存的key //todo暂时不知道有啥用
  std::string getCacheKeyBySessionId(const std::string &session_id);

private:
  static const std::string _cache_prefix = "vn_session_";
  static const int _cache_expire = 3600; // 默认过期 时间
  static const std::string _field_session_id =
      "sessionId"; // todo: 目前还不知道这个有啥用
  static const std::string _field_user_id =
      "userId"; // todo: 目前还不知道这个有啥用

  odb::database &_db;
  sw::redis::Redis &_redis;
  VidNovaMq::Publisher::ptr _publisher;
};
}; // namespace VidNovaData