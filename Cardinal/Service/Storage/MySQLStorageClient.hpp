#ifndef CARDINAL_MYSQL_STORAGE_CLIENT_HPP
#define CARDINAL_MYSQL_STORAGE_CLIENT_HPP
#include "Cardinal/Service/StorageService.hpp"
#include <string>
#include <list>
#include <map>
using namespace Cardinal::Service;
namespace Cardinal::Service::Storage {
    class MySQLStorageClient: public Cardinal::Service::StorageServiceInterface
    {
        public:
            void Store();
            QueryResults Get(Query query);
            StorageServiceInterface* AddValue(QueryValue Value);

        private:
            QueryValues Values;
            void Connect();
            void Disconnect();
            void Execute(Query query);
    };
}
#endif