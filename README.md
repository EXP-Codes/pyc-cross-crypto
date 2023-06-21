# pyc-cross-crypto

> python & c++ 跨平台加解密

------

## 0x00 前言

由于 python 和 C++ 的 AES/DES 填充算法存在细微差异（应该说是第三方库存在差异），默认情况下， crypto++、pycryptodome、pyDes 即使 key、iv、编码 等等都一致的情况下，彼此所生成的密文是无法相互解密的。

这直接导致了跨平台加解密非常麻烦。苦于目前网上并没有现成的跨平台加解密，故有了此工程。


> 其实各个语言的实现都不尽相同，例如在数据本身已对齐 BLOCKSIZE 的情况下会不会再填充一个 BLOCK ，IV 是否强制使用随机等。


## 0x10 环境说明

![](https://img.shields.io/badge/MSVC%20%20-14.3-green.svg) ![](https://img.shields.io/badge/Python-3.10-red.svg)


## 0x20 核心文件

### 0x21 C++

- AES（依赖 [crypto++](./cpp/cryptopp/)）:
    - [aes_crypto.hpp](./cpp/aes_crypto.hpp)
    - [aes_crypto.cpp](./cpp/aes_crypto.cpp)
- DES（依赖 [crypto++](./cpp/cryptopp/)）:
    - [des_crypto.hpp](./cpp/des_crypto.hpp)
    - [des_crypto.cpp](./cpp/des_crypto.cpp)
- 测试：
    - [test_crypto.cpp](./cpp/test_crypto.cpp)
    - 只是 C++ 内部测试，想验证跨平台需要手动把 python 的密文拷贝到 [test_crypto.cpp](./cpp/test_crypto.cpp) 中替换验证

> 使用 VS2022 打开 [cpp.sln](./cpp/cpp.sln) 工程，默认就是已配置好 crypto++ 的依赖，若希望自行配置，可参考《[Visual Studio 搭建 Boost + CryptoPP 开发环境](https://exp-blog.com/lang/vs-da-jian-boostcryptopp-kai-fa-huan-jing/)》


### 0x22 python

- AES（依赖 [pycryptodome](https://pypi.org/project/pycryptodome/)）:
    - [aes_crypto.py](./python/aes_crypto.py)
- DES（依赖 [pyDes](https://pypi.org/project/pyDes/)）:
    - [des_crypto.py](./python/des_crypto.py)
- 测试: `cd python` 
    - 安装依赖: `python -m pip install -r requirements.txt`
    - 执行命令: `python ./test/test_crypto.py`
    - 只是 python 内部测试，想验证跨平台需要手动把 C++ 的密文拷贝到 [test_crypto.py](./python/test/test_crypto.py) 中替换验证



## 0x30 开发环境部署

python 环境直接安装就好， windows 和 mac 都是一样的。

主要说一下 C++ 的环境：

- windows: 使用 Visual Studio Version 17（或更高版本）打开 [cpp.sln](./cpp/cpp.sln) 文件即可
- mac (需要提前安装 g++ 和 cmake): 
  1. `mkdir -p cpp/build`
  2. `cd cpp/build`
  3. `cmake -DCMAKE_BUILD_TYPE=Release ..`
  4. 编译: `make`
  5. 执行: `./cpp`

