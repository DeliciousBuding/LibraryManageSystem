# LibraryManageSystem HNU CS 2024

## v1.0

* 尝试使用git进行版本控制 并创建github仓库
* 搭建最基本的文件框架 初步实现头文件和源码分离操作
* 搭建起`LibrarySystem`类 `ReaderManager`和`UserManager`等等

## v1.5

使用第三方库`nlohmann/json`实现了cpp下对json文件的操作

初步实现了`users.json`

## v1.6

更新`ReaderManager`对json的支持

## v1.6.1

修改`User.json`中部分数据，使得性能优化，对数据的支持更好(优化`User.json`格式)

## v1.7

feat(BookSystem): 实现图书系统的基础功能

- 新增 `Book` 类，包含图书的基本信息和操作方法
- 实现了打开、读取、显示和保存图书信息的功能
- 添加了根据 ID、价格、编号和名称查询图书的方法
- 定义了图书信息的 getter 和 setter 方法

## v1.8

feat(BookSystem): 实现图书管理基本功能

- 添加 `Book` 类，实现图书信息的读取、显示、保存等功能
- 新增 `openCode` 和 `openName` 方法，支持按书号和书名查询图书
- 实现 `Borrow` 和 `Return` 方法，支持图书借阅和归还
- 优化 `open` 方法，增加文件打开状态检查
- 重构部分代码，提高可读性和可维护性

## v1.9

refactor(UserManager): 重构用户管理模块

- 移除 `BorrowRecord` 结构体，改为在 `Book` 类中处理借阅记录
- 优化 `User` 结构体，简化用户信息存储
- 重构 `UserManager` 类，添加文件操作和 JSON 数据处理方法
- 更新相关头文件，调整类和方法的声明
- 优化代码结构，提高可读性和可维护性

## v1.9.5

refactor(ReaderManager): 重构读者管理模块

- 添加 `open`、`close` 和 `save` 方法，用于管理 `User.json` 文件
- 重构 `addReader`、`deleteID`、`modifyUsername` 等方法，使用新添加的文件操作方法
- 优化 `User.json` 文件的读写逻辑，提高代码复用性和可维护性
- 调整 `BookSystem` 类的 `open` 和 `close` 方法，统一文件操作逻辑

## v2.0

增加了`open()`和`save()`方法，用于打开和保存用户数据
refactor(data): 重构用户数据并优化读者管理功能

- 删除了 `User.json` 中的多余用户数据
- 优化了 `ReaderManager` 类中的删除用户功能
- 修复了用户数量统计的问题
- 移除了不必要的文件操作，简化了数据保存逻辑

## v2.1

重构`BookSystem`以及`Book.json`

## v2.2

更新`User.json`的结构，增加借阅记录`record`

## v2.3

refactor(user): 重构用户信息管理功能

- 更新 `User.json` 文件格式，增加用户 ID 和借阅记录字段
- 重构 `ReaderManager` 和 `UserManager` 类，优化用户信息处理逻辑
- 新增 `Record` 类表示借阅记录，改进数据结构
- 优化用户注册、查找和登录功能，提高系统稳定性

## v2.4

fix Fatalerror

## v3.0

**重构一切（*~~推倒重做~~*）**

- 使用全新的系统形式，以`LibrarySystem`为核心，移除`ReaderManager.cpp`和`BookManager.cpp`，新建`User.cpp` `UserSystem.cpp`和`Book.cpp` `BookSystem.cpp`
- 对`User`类和`Book`类封装，将数据置于private区，使用get和set方法对私有区进行访问
- 使用Vector来存储`Users`和`Books`，以便进行查找和统一管理，避免了原先的`Book`和`User`类单独对文件进行读写导致的复杂问题
- 去除`User`类和`Book`类的`open`，`load`，`save`，`close`等文件读写方法，所有的读写在`UserSystem`和`BookSystem`中实现

## v4.0 beta dev分支

### 改变数据结构

-实现了`Book`类以及`Books`集合的读写格式问题
-实现了`User`类以及`Users`集合的读写格式问题
-实现了`User`类的增删改查 即用户后台管理功能
-初步实现了`Book`类的增删改查 即图书后台管理功能
-使用unordered_map实现了数据存储

## v4.5 beta dev分支

* 优化终端配置和书籍数据
* 解决査找问题完善结构功能，趋于完整，完善小的细节
* "査找问题"的解决：VSCode终端虽然使用utf-8编码，但是在终端中输入中文，仍然出现乱码，怀疑是输入的中文字符串为GBK编码
* 解决方案:外部打开编译文件，即可正常使用中文

VSCode集成终端本来使用chcp 65001强制使用utf-8编码打开

本来尝试使用wstring宽字符以及实现自定义比较函数来实现中文的匹配（怀疑stringA==stringB不可正常使用）

后决定将Windows系统中的UTF-8 beta全球语言支持打开，然后在外部单独打开编译好的main.exe文件，作为一个临时的解决方案

外部打开的终端中可以正常输入中文，但VScode内部的仍然不行，正在研究

# 目录结构

├─data
│      Book.json 存储书籍
│      User.json 存储用户和记录
├─include
│  │  Book.h
│  │  BookSystem.h
│  │  LibrarySystem.h
│  │  User.h
│  │  UserSystem.h
│  │
│  └─nlohmann 第三方库，实现json读写
└─src
│  Book.cpp 实现Book类
│  BookSystem.cpp 实现图书系统
│  User.cpp 实现User类
│  UserSystem.cpp 实现用户系统
│  LibrarySystem.cpp 实现图书馆系统
│  main.cpp 主程序

正在开发中

## 数据结构

### 1.user类

l  账户 l  密码 l  角色：1-管理员、2-读者

### 2.book类

l  题名 l  ISBN/ISSN l  作者 l  出版社 l  价格

## 实验目标

### 一、系统设计与功能实现

1. **设计一款文字式交互的图书管理系统**
   * [X]  注册登录功能
   * [X]  浏览图书功能
   * [X]  借还图书功能

### 二、数据存储

* [X]  以外部文件的形式存储书籍信息
* [X]  以外部文件的形式存储馆藏记录
* [X]  以外部文件的形式存储借阅记录
* [X]  以外部文件的形式存储用户信息

### 三、图书信息管理

* [X]  图书信息包含：题名、ISBN/ISSN、作者、出版社、价格

### 四、用户基类信息与管理

* [X]  用户基类信息：账户、密码、角色（1-管理员、2-读者）
* [X]  管理员权限：
  * [X]  读者用户管理：增、删、改、查
  * [X]  重置读者默认密码为123456
  * [X]  书籍信息管理：增、删、改、查

### 五、搜索功能

* [X]  根据任一信息搜索图书的功能：

  [ ]  题名，精确查找到书

  [ ]  ISBN/ISSN，精确查找到书

  [ ]  作者，查找该作者所有书，结果按字典序排序

## 六、排行榜功能

* [X]  借阅次数前十的图书
* [X]  最新出版前十的图书
* [X]  实现额外排序

### 七、菜单显示与跳转功能

* [X]  分级菜单显示
* [X]  菜单跳转功能：从上级菜单进入下级菜单，从下级菜单返回上级菜单

### 八、加分项（可选）

* [ ]  图书推荐功能：基于借阅记录推荐图书
* [ ]  新增未列出的若干功能
* [ ]  用户体验优化：界面美观、操作方便
* [ ]  搜索性能优化
* [ ]  其他亮点

### 九、完成进度建议

#### 第一阶段

* [ ]  完成图书存储功能
  * [ ]  设计图书类
  * [ ]  设计图书馆系统类
  * [ ]  编写相关实验报告、代码和测试

#### 第二阶段

* [ ]  完成两种用户模式及其基本功能
  * [ ]  管理员模式
  * [ ]  读者模式
  * [ ]  编写相关实验报告、代码和测试

#### 第三阶段

* [ ]  完成排序和搜索功能
  * [ ]  实现排序算法
  * [ ]  实现搜索算法
  * [ ]  编写相关实验报告、代码和测试

### 十、验收安排

* [ ]  第14-16周，向助教预约验收时间，进行系统演示和报告讲解
* [ ]  源码压缩包和实验报告同步上传CG平台
