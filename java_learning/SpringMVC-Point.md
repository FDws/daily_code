1. 当用`AnnotationConfigWebApplicationContext`配置上下文时, 有两种选择:
    - 实现`WebMvcConfigurer`并且加上`@EnableWebMvc`注解
    - 继承`WebMvcConfigurationSupport`, 不要加`@EnableWebMvc`
2. 使用`@MatrixVariable`
    - 配置文件加入`<mvc:annotation-driven enable-matrix-variables="true"/>`
    - URL映射务必用模型匹配
    ```java
    // wrong
    @GetMapping("demo/a")
    public String a(@MatrixVariable String b) {
        //
    }
    // Good
    @GetMapping("demo/{a}")
    public String a(@MatrixVariable String b) {
        //
    }
    ```
3. 使用`@SessionAttributes`注解控制类时, 无法在第一次请求的会话中获得此注解注册的值