用c++简单封装了redis的基本操作（hiredis）

接口包括：①链接和断开连接、②设置键值对(set)、③查询键值对(get)、④删除键值对(del)、⑤将所有键显示出来

若任何一处发生错误，返回对应的错误状态码，同时可以调用getErrorMsg()查看错误信息

所有码包括：

M_REDIS_OK = 0, //执行成功
M_CONNECT_FAIL = -1, //连接redis失败
M_CONTEXT_ERROR = -2, //RedisContext返回错误
M_REPLY_ERROR = -3, //redisReply错误
M_EXE_COMMAND_ERROR = -4 //redis命令执行错误

 
tips：在链接hiredis时需要添加链接选项： -levent  -lhiredis
