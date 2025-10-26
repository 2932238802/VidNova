FROM ccr.ccs.tencentyun.com/maxhou/myimage:rabbitmq_3_12_6_management

MAINTAINER bit

# 添加插件到指定目
ADD ./rabbitmq_delayed_message_exchange-3.12.0.ez /plugins

# 开启延迟队列插件
RUN rabbitmq-plugins enable rabbitmq_delayed_message_exchange
# 开启web管理
RUN rabbitmq-plugins enable rabbitmq_management

ENTRYPOINT ["rabbitmq-server"]
