#include "userInfo.h"

void model::UserInfo::loadUserInfo(const QJsonObject &user_info)
{


    // int userState; // 用户状态
    // int isFollowed; //是否被关注
    // QString userMemo; // 用户的备注信息
    // QString userCreateTime; //用户创建的时间
    // QString avatarFileId; // 用户头像id
    userId = user_info["userId"].toString();
    photoNumber = user_info["photoNumber"].toString();
    nickName = user_info["nickName"].toString();
    QJsonArray arrayRole = user_info["roleType"].toArray();

    for(int i = 0 ; i < arrayRole.size() ; i++)
    {
        roleType.append(arrayRole[i].toInt());
    }

    QJsonArray arrayIdentity = user_info["identityType"].toArray();

    for(int i = 0 ; i < arrayIdentity.size() ; i++)
    {
        identityType.append(arrayIdentity[i].toInt());
    }

    likeCount = user_info["likeCount"].toInteger();
    playCount = user_info["playCount"].toInteger();
    fansCount = user_info["fansCount"].toInteger();
    followCount = user_info["followCount"].toInteger();

    userState = user_info["userState"].toInt();
    isFollowed = user_info["isFollowed"].toInt();

    userMemo = user_info["userMemo"].toString();
    userCreateTime = user_info["userCreateTime"].toString();
    avatarFileId = user_info["avatarFileId"].toString();


}

//////////////////
/// \brief model::UserInfo::isB
/// \return
///
bool model::UserInfo::isB() const
{
    for(auto a: identityType)
    {
        if( a == IdentityType::BUser)
        {
            return true;
        }
    }
    return false;
}
//////////////////



//////////////////
/// \brief model::UserInfo::isTempUser
/// \return
///
bool model::UserInfo::isTempUser() const
{
    for(auto a: roleType)
    {

        if( a == RoleType::TempUser)
        {
            return true;
        }
    }
    return false;
}
//////////////////







