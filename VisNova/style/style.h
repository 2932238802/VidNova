#pragma once

#include<QString>
inline const QString BODY_LEFT_BUTTON_PRESS_FONT_COLOR = "#000000";
inline const QString BODY_LEFT_BUTTON_UNPRESS_FONT_COLOR = "#999999";


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

// 分页器的样式 触发
inline const QString PAGE_BUTTON_FENYEQI_ACTIVED = R"(
    QPushButton{
        color: #FFFFFF;
        background-color: #3ECEFE;
        border: 1px solid #3ECEFE;
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

inline const QString PAGENUMBEREDIT = R"(
    QLineEdit{
    background-color: #FFFFFF;
    border: 1px solid #D9D9D9;
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


inline const QString PLAYER_BEGIN_STYLE = R"(
    border-image:url(":/image/stop.png");

)";

inline const QString PLAYER_STOP_STYLE = R"(
    border-image:url(":/image/play.png");

)";


