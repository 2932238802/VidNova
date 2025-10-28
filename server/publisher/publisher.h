#pragma once
#include <SimpleAmqpClient/Channel.h>
#include <memory>
#include <string>

namespace VidNovaMq {

class Publisher {
public:
  using ptr = std::shared_ptr<Publisher>;

  Publisher(const std::string &host, int port, const std::string &username,
            const std::string &password, const std::string &vhost = "/");

  ~Publisher();
  bool publish(const std::string &exchange_name, const std::string &routing_key,
               const std::string &message);

private:
  AmqpClient::Channel::ptr_t l_channel;
};
} // namespace VidNovaMq
