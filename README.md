# LibraryManageSystem HNU CS 2024

## v5.0 测试版

测试

## v4.7

更新了最新图书的显示

## v4.6

部分读取字符串使用`getline`而非`cin`，避免丢失空格的读取

## v4.5 beta dev分支

* [X]  优化终端配置和书籍数据
* [X]  解决查找问题完善结构功能，趋于完整，完善小的细节
* [X]  "查找问题"的解决：VSCode终端虽然使用utf-8编码，但是在终端中输入中文，仍然出现乱码，怀疑是输入的中文字符串为GBK编码
* [X]  解决方案:外部打开编译文件，即可正常使用中文

VSCode集成终端本来使用`chcp 65001`强制使用utf-8编码打开

本来尝试使用`wstring`宽字符以及实现自定义比较函数来实现中文的匹配（怀疑`stringA==stringB`不可正常使用）

后决定将Windows系统中的UTF-8 beta全球语言支持打开，然后在外部单独打开编译好的main.exe文件，作为一个临时的解决方案

外部打开的终端中可以正常输入中文，但VScode内部的仍然不行，正在研究

## v4.0 beta dev分支

### 改变数据结构

* 实现了`Book`类以及`Books`集合的读写格式问题
* 实现了`User`类以及`Users`集合的读写格式问题
* 实现了`User`类的增删改查 即用户后台管理功能
* 初步实现了`Book`类的增删改查 即图书后台管理功能
* 使用`unordered_map`实现了数据存储

## v3.0

**重构一切（*~推倒重做~*）**

* 使用全新的系统形式，以`LibrarySystem`为核心，移除`ReaderManager.cpp`和`BookManager.cpp`，新建`User.cpp` `UserSystem.cpp`和`Book.cpp` `BookSystem.cpp`
* 对`User`类和`Book`类封装，将数据置于private区，使用get和set方法对私有区进行访问
* 使用Vector来存储`Users`和`Books`，以便进行查找和统一管理，避免了原先的`Book`和`User`类单独对文件进行读写导致的复杂问题
* 去除`User`类和`Book`类的`open`，`load`，`save`，`close`等文件读写方法，所有的读写在`UserSystem`和`BookSystem`中实现

## v2.3

refactor(user): 重构用户信息管理功能

* 更新 `User.json` 文件格式，增加用户 ID 和借阅记录字段
* 重构 `ReaderManager` 和 `UserManager` 类，优化用户信息处理逻辑
* 新增 `Record` 类表示借阅记录，改进数据结构
* 优化用户注册、查找和登录功能，提高系统稳定性

## v2.2

更新`User.json`的结构，增加借阅记录`record`

## v2.1

重构`BookSystem`以及`Book.json`

## v2.0

增加了`open()`和`save()`方法，用于打开和保存用户数据 refactor(data): 重构用户数据并优化读者管理功能

* 删除了 `User.json` 中的多余用户数据
* 优化了 `ReaderManager` 类中的删除用户功能
* 修复了用户数量统计的问题
* 移除了不必要的文件操作，简化了数据保存逻辑

## v1.9.5

refactor(ReaderManager): 重构读者管理模块

* 添加 `open`、`close` 和 `save` 方法，用于管理 `User.json` 文件
* 重构 `addReader`、`deleteID`、`modifyUsername` 等方法，使用新添加的文件操作方法
* 优化 `User.json` 文件的读写逻辑，提高代码复用性和可维护性
* 调整 `BookSystem` 类的 `open` 和 `close` 方法，统一文件操作逻辑

## v1.9

refactor(UserManager): 重构用户管理模块

* 移除 `BorrowRecord` 结构体，改为在 `Book` 类中处理借阅记录
* 优化 `User` 结构体，简化用户信息存储
* 重构 `UserManager` 类，添加文件操作和 JSON 数据处理方法
* 更新相关头文件，调整类和方法的声明
* 优化代码结构，提高可读性和可维护性

## v1.8

feat(BookSystem): 实现图书管理基本功能

* 添加 `Book` 类，实现图书信息的读取、显示、保存等功能
* 新增 `openCode` 和 `openName` 方法，支持按书号和书名查询图书
* 实现 `Borrow` 和 `Return` 方法，支持图书借阅和归还
* 优化 `open` 方法，增加文件打开状态检查
* 重构部分代码，提高可读性和可维护性

## v1.7

feat(BookSystem): 实现图书系统的基础功能

* 新增 `Book` 类，包含图书的基本信息和操作方法
* 实现了打开、读取、显示和保存图书信息的功能
* 添加了根据 ID、价格、编号和名称查询图书的方法
* 定义了图书信息的 getter 和 setter 方法

## v1.6.1

修改`User.json`中部分数据，使得性能优化，对数据的支持更好(优化`User.json`格式)

## v1.6

更新`ReaderManager`对json的支持

## v1.5

使用第三方库`nlohmann/json`实现了cpp下对json文件的操作

初步实现了`users.json`

## v1.0

* 尝试使用git进行版本控制 并创建github仓库
* 搭建最基本的文件框架 初步实现头文件和源码分离操作
* 搭建起`LibrarySystem`类 `ReaderManager`和`UserManager`等等
* 尝试使用git进行版本控制 并创建github仓库
* 搭建最基本的文件框架 初步实现头文件和源码分离操作
* 搭建起`LibrarySystem`类 `ReaderManager`和`UserManager`等等
