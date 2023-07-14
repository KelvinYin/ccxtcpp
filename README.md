# ccxtcpp
CryptoCurrency eXchange Trading Library in C++.

受 [Binance C++ API](https://github.com/binance-exchange/binacpp) 启发，使用 cpr 改写了原有的现货代码，替换了 curl 的使用，增加了期货接口。
## 依赖库

- [curl](https://github.com/curl/curl)
- [cpr](https://github.com/libcpr/cpr)
- [libwebsockets](https://github.com/warmcat/libwebsockets)
- [jsoncpp](https://github.com/open-source-parsers/jsoncpp)

其中 libwebsockets 默认使用 poll，可以在编译的时候指定使用 libuv。
