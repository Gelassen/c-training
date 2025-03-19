for test in $(find . -name '*_test.cpp'); do
    g++ -std=c++17 $test -lgtest -lgtest_main -pthread -o test_executable
    ./test_executable
done
