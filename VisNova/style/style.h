#pragma once
#include<QString>

////////////////////////////////////////////////////////////////////////////////////
inline const QString BODY_LEFT_BUTTON_PRESS_FONT_COLOR = "#000000";
inline const QString BODY_LEFT_BUTTON_UNPRESS_FONT_COLOR = "#999999";
////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////
/// 个人界面的头像设置
inline const QString MYPAGE_MASK_FOR_AVATAR = R"(
        #myPageMaskForAvatar{
        color: #FFFFFF;
        background-color: rgba(0,0,0,0.5);
        border-radius: 30px;
        }
)";
inline const QString MYPAGE_AVATAR_CLEAR_STYLE = R"(
    background-color: transparent;
    border: none;
    border-radius: 30px;
)";
inline const QString MYPAGE_ATTENTIONED_BTN = R"(
    QPushButton{
        color: #3ECEFE;
        font-size: 15px;
        border-radius:4px;
        border: 2px solid #3ECEFE;
        padding-left: 13px;
        padding-right: 13px;
    }
)";

inline const QString MYPAGE_UNATTENTIONED_BTN = R"(
    QPushButton{
        color: #FFCCCC;
        font-size: 15px;
        border-radius:4px;
        border: 2px solid #FFCCCC;
        padding-left: 13px;
        padding-right: 13px;
    }
)";
////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////
inline const QString SYSTEMPAGE_UNACTIVED_BUTTON = R"(
    QPushButton{
    background-color: #FFFFFF;
    font-family: '微软雅黑';
    font-size: 14px;
    color: #666666;
    border: none;
    border-bottom: 2px solid #F5F6F8;
}
)";
inline const QString SYSTEMPAGE_ACTIVED_BUTTON = R"(
    QPushButton{
    background-color: #FFFFFF;
    font-family: '微软雅黑';
    font-size: 14px;
    color: #666666;
    border: none;
    border-bottom: 2px solid #3ECEFF;
}
)";
////////////////////////////////////////////////////////////////////////////////////







////////////////////////////////////////////////////////////////////////////////////
/// 分页器
inline const QString PAGENUMBEREDIT = R"(
    QLineEdit{
    background-color: #FFFFFF;
    border: 1px solid #D9D9D9;
    border-radius: 2px;
}
)";
// 分页器 没有触发
inline const QString PAGE_BUTTON_FENYEQI_UNACTIVED = R"(
    QPushButton{
        color: #000000;
        background-color: #FFFFFF;
        border: 1px solid #D9D9D9;
        border-radius: 2px;
    }
)";
// 分页器的样式 触发
inline const QString PAGE_BUTTON_FENYEQI_ACTIVED = R"(
    QPushButton{
        color: #FFFFFF;
        background-color: #3ECEFE;
        border: 1px solid #3ECEFE;
        border-radius: 2px;
    }
)";
inline const QString PAGINATOR_QPUSHBUTTON_DEFAULT_FOR_LEFT_AND_RIGHT = R"(
    QPushButton{
        color: #000000;
        background-color: #FFFFFF;
        border: 1px solid #D9D9D9;
        border-radius: 2px;
    }
)";
////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////
// 选中的
inline const QString LOGIN_TOGGLE_BTNCHOOSED = R"(
    QPushButton{
        color: #3ECEFE;
        font-size: 22px;
        font-weight: bold;
        border: none;
        border-bottom: 6px solid #3ECEFE;
    }
)";
inline const QString LOGIN_TOGGLE_BTNUNCHOOSED = R"(
    QPushButton{
        color: #222222;
        font-size: 22px;
        border: none;
        border-bottom: 2px solid #B5ECFF;
    }
)";
////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////
// 浮动窗口的样式 提示窗口
inline const QString TOAST_BG = R"(
    background-color: rgba(102,102,102,0.5);
    border-radius: 4px;
)";
inline const QString TOAST_LABEL = R"(

    font-family: "微软雅黑";
    font-size: 14px;
    color: #FFFFFF;
)";
////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////
/// 播放按钮
inline const QString PLAYER_BEGIN_STYLE = R"(
    border-image:url(":/image/stop.png");

)";

inline const QString PLAYER_STOP_STYLE = R"(
    border-image:url(":/image/play.png");

)";

////////////////////////////////////////////////////////////////////////////////////






////////////////////////////////////////////////////////////////////////////////////
/// PlayerPage弹幕
inline const QString PLAYERPAGE_TEST_BACKGROUND_FOR_TOP = R"(
    background-color: #E3C014;
)";

inline const QString PLAYERPAGE_TEST_BACKGROUND_FOR_MIDDLE = R"(
    background-color: #E3A714;
)";

inline const QString PLAYERPAGE_TEST_BACKGROUND_FOR_BOTTOM = R"(
    background-color: #E3D914;
)";
inline const QString BULLET_TEXT = R"(
    font-family: 微软雅黑;
    font-size: 18px;
    color: #FFFFFF;
    border: none;
)";

inline const QString BULLET = R"(
    #bulletItem{
    border: 1px solid #3ECEFE;
    border-radius: 19px;
}
)";
inline const QString BULLETBTN_SHOW = R"(
    border-image: url(":/image/bulletOpen.png")

)";
inline const QString BULLETBTN_CLOSE = R"(
    border-image: url(":/image/bulletClose.png");
)";

inline const QString PLAYERPAGE_LIKEBTN_CLIECKED =R"(
    border-image: url(":/image/likeBtnClicked.png");
)";

inline const QString PLAYERPAGE_LIKEBTN_UNCLICKED =R"(
    border-image: url(":/image/likeBtnUnclicked.png");
)";
////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////
/// UPLOADPA_TAG_CHOOSED

inline const QString UPLOADPA_TAG = R"(
    QPushButton{
        border:1px solid #3ECEFE;
        border-radius: 4px;
        color: #3ECEFE;
        font-family: 微软雅黑;
        font-size: 16px;
        background-color: #FFFFFF;
}
    QPushButton:checked{
        background-color: #3ECEFE;
        color: #FFFFFF;
    }

    QPushButton:unchecked{
        background-color: #FFFFFF;
        color: #3ECEFE;
    }

)";
////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////
inline const QString VIDEO_TITLE_LABEL = R"(
    color: #000000;
    font-weight: bold;
    font-size: 16px;
    font-family: '微软雅黑';
)";


inline const QString VIDEO_INFO_BOX = R"(
    #videoInfoBox {
        background-color: transparent;
    }
    QLabel {
        color: #000000;
        background-color: transparent;
        border: none;
        font-size: 14px;
        font-family: '微软雅黑';
    }
)";


inline QString VIDEO_MENU = R"(
    QMenu{
        background-color: #FFFFFF;
        border: none;
        border-radius: 6px;
        padding: 0;
    }

QMenu::item{
    background-color: #FFFFFF;
    border: none;
    border-radius: 6px;
    min-width: 50px;
    min-height: 32px;
    font-size: 12px;
    color: #222222;
    padding-left: 24px;
}

QMenu::item:select{
    background-color: rgb(62,206,254);
    color: #FFFFFF;
}

)";

////////////////////////////////////////////////////////////////////////////////////



inline const QString BG_FOR_CONFIRMBACKGROUND = R"(
    background-color: rgba(0,0,0,0.3);
)";



inline const QString CONTENT_FOR_CONFIRMBACKGROUND = R"(
    #content{
        background-color: #FFFFFF;
        border-radius: 10px;
    }
    *{
        font-family: 微软雅黑;
        font-size: 16px;
    }
)";


inline const QString TEXT_LABEL_FOR_CONFIRMBACKGROUND = R"(
    QLabel {
        background-color: #FFFFFF;
        color: #000000;
    }
)";

inline const QString CONFIRM_BTN_FOR_CONFIRMBACKGROUND = R"(
    background-color: #3ECEFF;
    border-radius: 8px;
    color: #FFFFFF;
)";

inline const QString CANCEL_BTN_FOR_CONFIRMBACKGROUND = R"(
    background-color: #3ECEFF;
    border-radius: 8px;
    border: 1px solid #DEDEDE;
)";










