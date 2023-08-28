#ifndef CARDINAL_SERVICE_STORAGESERVICE_H
#define CARDINAL_SERVICE_STORAGESERVICE_H

#include <string>
#include <map>
#include <list>

namespace Cardinal::Service {
    struct Query {
        std::string Table = "";
        int Id = -1;
    };

    struct QueryValue {
        std::map<std::string, std::string> Value;
    };

    struct QueryValues {
        std::list<QueryValue> Values;
    };

    struct QueryResult {

    };

    struct QueryResults {

    };

    class StorageServiceInterface {
        public:
            virtual void Store() = 0;
            virtual QueryResults Get(Query query) = 0;
            virtual StorageServiceInterface* AddValue(QueryValue Value) = 0;
    };
}
#endif