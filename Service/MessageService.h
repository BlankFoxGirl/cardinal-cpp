#include <string>
#include "../Exception/Exceptions.h"
#ifndef MS_H
#define MS_H

using namespace std;

namespace Cardinal {
    namespace Service {
        class MessageService {
            public:
                MessageService ();
                MessageService (string raw);

                MessageService (string event, string message);

                string getEvent ();

                void setEvent (string event);

                void setMessage (string message);

                void setRaw (string raw);

                void appendMessage(string message);

                string getRaw();

                tuple<string,string> Decode();

            private:
                string raw = "";
                string event = "";
                string message = "";

                void Compile ();
                void Decompile();
        };
    };
}

#endif