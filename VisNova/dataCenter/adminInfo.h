#pragma once
#include<QString>
#include"dataCenter/userInfo.h"


namespace model{

////////////////////////////
/// \brief The AdminInfo class
///
class AdminInfo
{
public:
    AdminInfo();

    QString nickName;
    QString userId;

    QString emailNumber;
    QString userMemo; // 描述信息

    model::RoleType roleType;
    model::AdminState state;

    void LoadFromJson(const QJsonObject& admin_info);
};
////////////////////////////


////////////////////////////
/// \brief The AdminList class
/// totalCount 用来计算分页器
/// 这个列表 就原生数组 还是 unique_ptr 呢？
/// PAGE_COUNT 默认一页包含的 管理员个数
///
class AdminList{
public:
    QList<AdminInfo> adminList;
    int64_t totalCount;
    const int static PAGE_COUNT = 20;

public:
    void addAdmin(const AdminInfo& adminInfo);


};

////////////////////////////



}










