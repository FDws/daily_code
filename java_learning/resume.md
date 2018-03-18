### Java Map
1. HashMap 在1.7- 是数组加链表实现, 1.8 是数组+链表+红黑树 , 当链表长度大于8时转为红黑树
2. HashTable 锁住整个表, SynchronizedMap 同步代码块
3. ConcurrentHashMap 
    - 1.7- 分段锁, 大大提高了高并发环境下的处理能力. 由于不是对整个Map加锁, 所以一些需要扫描整个Map的方法(size())等需要特殊实现, clear甚至放弃了对一致性的要求. 
    - 1.8+ 使用CAS算法, 底层使用 数组+链表+红黑树 实现, 同时增加了许多辅助类
        - `sizeCtl`: 负数代表正在进行初始化或者扩容, -1 表示初始化, -N表示N-1个线程正在进行扩容操作, 正数表示还没有被初始化, 下一次扩容的大小,
        .75倍
2. mysql lock/dikaer/聚簇索引
3. 微服务
4. jvm
5. 事务/aop/ioc/测试
6. JIT
7. transient 不需要序列化
8. 嵌套`synchronized`死锁
9. volatile