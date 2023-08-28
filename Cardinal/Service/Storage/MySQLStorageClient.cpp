#include "MySQLStorageClient.hpp"
#include "Cardinal/Service/StorageService.hpp"

using namespace Cardinal::Service;
using namespace Cardinal::Service::Storage;

void MySQLStorageClient::Store(){};

QueryResults MySQLStorageClient::Get(Query query) {
    return QueryResults();
}

Cardinal::Service::StorageServiceInterface* MySQLStorageClient::AddValue(QueryValue Value) {
    return this;
}
