1. 当用`AnnotationConfigWebApplicationContext`配置上下文时, 有两种选择:
    - 实现`WebMvcConfigurer`并且加上`@EnableWebMvc`注解
    - 继承`WebMvcConfigurationSupport`, 不要加`@EnableWebMvc`