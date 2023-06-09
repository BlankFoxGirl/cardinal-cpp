#include "RedisStackStorage.hpp"
#include "Cardinal/Global/Utility.hpp"

using namespace Cardinal::Service::Storage;

void RedisStackStorage::Connect(std::string ConnectionURL)
{
    this->redisStack = sw::redis::Redis(ConnectionURL);
}

void RedisStackStorage::Connect(std::string Hostname, std::string Port, std::string Protocol)
{
    this->redisStack = sw::redis::Redis(Protocol + "://" + Hostname + ":" + Port);
}

Cardinal::Service::StoredObject RedisStackStorage::Get(const std::string &primary, const std::string &table)
{
    // FT.SEARCH user "@email:{ sarmth\\@me\\.com }" limit 0 10
    return StoredObject();
}

Cardinal::Service::StoredObjectCollection RedisStackStorage::Find(Cardinal::Service::StoredObject &parameter, const std::string &table)
{
    auto command = this->ConstructFindCommand(table, parameter);
    auto result = this->redisStack.command(command);
    auto res = result.get();
    auto v = res->elements;

    return StoredObjectCollection();
}

Cardinal::Service::StoredObject RedisStackStorage::Save(Cardinal::Service::StoredObject &object, const std::string &table)
{
    return StoredObject();
}

// ToDo: This needs to be broken down into fields, constraints, and limits.
std::string RedisStackStorage::ConstructFindCommand(std::string table, Cardinal::Service::StoredObject parameters)
{
    // RedisStack: FT.SEARCH user "@email: { sarmth\\@me\\.com }" limit 0 10
    // SQL: SELECT * FROM user WHERE email = "sarmth@me.com" limit 10 0
    // Loop through parameters.rows and construct the command
    std::vector<std::string> command;
    command.push_back("FT.SEARCH");
    command.push_back(table);
    command.push_back("\"");

    for (auto &row : parameters.rows)
    {
        std::vector<std::string> findParameter;
        // row.key
        findParameter.push_back("@" + row.key + ":");

        // row.value
        findParameter.push_back("{ " + Cardinal::Global::Utility::Escape(row.value) + " } ");

        command.push_back(Cardinal::Global::Utility::Join(findParameter, ""));
    }

    command.push_back("\"");

    return Cardinal::Global::Utility::Join(command, "");
}

void RedisStackStorage::CreateIndexes()
{
    // ft.create user on JSON prefix 1 user: schema $.email as email TAG
}