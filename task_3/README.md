### Compilation
```
$ g++ -std=c++17 main.cpp api.cpp -o api_program \
    -lboost_log -lboost_log_setup -lboost_system -lboost_thread -lpthread \
    -lboost_filesystem -lboost_system -lssl -lcrypto

```