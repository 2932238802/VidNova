#include "publisher.h"
#include <SimpleAmqpClient/BasicMessage.h>
#include <iostream>
namespace VidNovaMq {
Publisher::Publisher(const std::string &host, int port,
                     const std::string &username, const std::string &password,
                     const std::string &vhost) {
  try {

    // 这个是建立连接
    l_channel =
        AmqpClient::Channel::Create(host, port, username, password, vhost);
    std::cout << "成功连接到 RabbitMQ" << std::endl;
  }

  catch (const std::exception &e) {
    std::cerr << "创建RabbitMq 发布者的时候 出现了错误: " << e.what()
              << std::endl;
    throw;
  }
}

Publisher::~Publisher() {
  std::cout << "Publisher destroyed, connection closed." << std::endl;
}
bool Publisher::publish(const std::string &exchange_name,
                        const std::string &routing_key,
                        const std::string &message) {
  if (!l_channel) {
    std::cerr << "RabbitMQ 发布者的通道未打开" << std::endl;
    return false;
  }

  try {
    auto msg = AmqpClient::BasicMessage::Create(message);
    msg->DeliveryMode(AmqpClient::BasicMessage::dm_persistent);
    l_channel->BasicPublish(exchange_name, routing_key, msg);
    return true;
  } catch (const std::exception &e) {
    std::cerr << "发布消息到 RabbitMQ 时出现了错误: " << e.what() << std::endl;
    return false;
  }
};

} // namespace VidNovaMq
