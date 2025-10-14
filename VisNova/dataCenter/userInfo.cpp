#include "userInfo.h"

void model::UserInfo::loadUserInfo(const QJsonObject &user_info)
{


    // int userState; // 用户状态
    // int isFollowed; //是否被关注
    // QString userMemo; // 用户的备注信息
    // QString userCreateTime; //用户创建的时间
    // QString avatarFileId; // 用户头像id
    userId = user_info.value("userId").toString();
    photoNumber = user_info.value("photoNumber").toString();
    nickName = user_info.value("nickName").toString();
    QJsonArray arrayRole = user_info.value("roleType").toArray();

    if(!arrayRole.empty())
    {
        roleType.clear();
    }

    for(int i = 0 ; i < arrayRole.size() ; i++)
    {
        int type = arrayRole[i].toInt();

#ifdef USERINFO_TEST
        LOG()<<"type: " << type;
#endif

        roleType.append(type);
    }


    QJsonArray arrayIdentity = user_info.value("identityType").toArray();

    for(int i = 0 ; i < arrayIdentity.size() ; i++)
    {
        identityType.append(arrayIdentity[i].toInt());
    }

    likeCount = user_info.value("likeCount").toInteger();
    playCount = user_info.value("playCount").toInteger();
    fansCount = user_info.value("fansCount").toInteger();
    followCount = user_info.value("followCount").toInteger();

    userState = user_info.value("userState").toInt();
    isFollowed = user_info.value("isFollowed").toInt();

    userMemo = user_info.value("userMemo").toString();
    userCreateTime = user_info.value("userCreateTime").toString();
    avatarFileId = user_info.value("avatarFileId").toString();


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

#ifdef USERINFO_TEST
        LOG() << "用户身份: " << a;
#endif

        if( a == RoleType::TempUser)
        {
            return true;
        }
    }
    return false;
}
//////////////////


//////////////////
/// \brief model::UserInfo::buildTmpUserInfo
///
void model::UserInfo::buildTmpUserInfo()
{
    userId = "";
    photoNumber = ""; // 手机号
    nickName = "Los"; // 用户昵称
    roleType.append(RoleType::TempUser) ;  // 角色类型
    identityType.append(IdentityType::BUser); // 身份类型
    likeCount = 0; // 点赞数
    playCount = 0; // 播放数量
    fansCount = 0; // 粉丝数量
    followCount = 0; //关注数量
    int userState = 0; // 用户状态
    int isFollowed = 0; //是否被关注
    QString userMemo = "抓紧去登录哦~"; // 用户的备注信息
    QString userCreateTime = ""; //用户创建的时间
    QString avatarFileId = ""; // 用户头像id

}
//////////////////












