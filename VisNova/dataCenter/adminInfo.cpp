#include "adminInfo.h"

namespace model{


AdminInfo::AdminInfo() {}


//////////////////////////////
/// \brief AdminInfo::LoadFromJson
/// \param admin_info
///
void AdminInfo::LoadFromJson(const QJsonObject &admin_info)
{

    nickName = admin_info["nickName"].toString();
    userId = admin_info["userId"].toString();
    emailNumber = admin_info["emailNumber"].toString();
    userMemo = admin_info["userMemo"].toString();
    roleType = static_cast<model::RoleType>(admin_info["roleType"].toInt());
    state =static_cast<model::AdminState>(admin_info["state"].toInt());
}


//////////////////////////////
/// \brief AdminList::addAdmin
/// \param adminInfo
/// 增加用户
void AdminList::addAdmin(const AdminInfo &adminInfo)
{
    adminList.append(adminInfo);
}

//////////////////////////////
/// \brief AdminList::setAddStatus
/// \param userId
/// \param state
///
void AdminList::setAddStatus(const QString &userId, AdminState state)
{
    for(auto& a: adminList )
    {
        if(a.userId == userId)
        {
            a.state = state;
            return;
        }
    }
}
//////////////////////////////

}
















