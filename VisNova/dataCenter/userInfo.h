#pragma once

#include <QObject>

#include<QString>
#include<QList>
#include<QJsonObject>
#include<QJsonArray>
#include "common/myLog.h"

namespace model{

enum RoleType{

    SuperAdmin = 1,
    Admin,
    User,
    TempUser
};

enum IdentityType{
    CUser = 1,
    BUser
};



class UserInfo
{
public:
    QString userId;
    QString photoNumber; // 手机号
    QString nickName; // 用户昵称
    QList<int> roleType;  // 角色类型
    QList<int> identityType; // 身份类型
    int64_t likeCount; // 点赞数
    int64_t playCount; // 播放数量
    int64_t fansCount; // 粉丝数量
    int64_t followCount; //关注数量
    int userState; // 用户状态
    int isFollowed; //是否被关注
    QString userMemo; // 用户的备注信息
    QString userCreateTime; //用户创建的时间
    QString avatarFileId; // 用户头像id

    // 设置用户信息
    void loadUserInfo(const QJsonObject& user_info);

    bool isB() const; // 检测是不是B端用户

    bool isTempUser() const; // 检测是不是临时用户


};



}


