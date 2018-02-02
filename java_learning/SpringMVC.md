# [Spring Web MVC](https://docs.spring.io/spring/docs/current/spring-framework-reference/web.html)
----
## 介绍
1. 原始的基于 Servlet API 的 Web 框架， 包含在 Spring 框架中
2. 并行的还有一个响应式的Web框架`Spring WebFlux`

## DispatcherServlet
1. 基于`Servlet`的前端控制器.
2. 在`web.xml`中注册的基本配置:
```xml
<web-app>
    <servlet>
        <servlet-name>mvcDispatcher</servlet-name>
        <servlet-class>org.springframework.web.servlet.DispatcherServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>mvcDispatcher</servlet-name>
        <url-pattern>/</url-pattern>
    </servlet-mapping>
</web-app>
```
### 上下文层级(Context Hierarchy)
1. `DispatcherServlet`需要一个继承自`ApplicationContext`的`WebAppliicationContext`来配置自己
-  ![](https://docs.spring.io/spring/docs/current/spring-framework-reference/images/mvc-context-hierarchy.png)

### 特殊的Bean类型
- 
| Bean类型 | 解释 |
| :---: | :--:|
| HandlerMapping | 根据`request`找到对应的处理器`Handler`, 最主要的两个实现类:`RequestMappingHandlerMapping`, 支持`@RequestMapping`注解;`SimpleUrlHandleMapping`,主要明确的注册URL与对应的`Handler`|
|HandlerAdapter|帮助`DispatcherServlet`定位需要调用的`Handler`|
|HandlerExceptionResolver|出现异常的时候尝试用此处理|
|LocalResolver, LocaleContextResolver|设置不同的本地语言, 提供国际化的语言支持|
|ThemeResolver|应用的样式控制|
|MultipartResolver|给多样的请求提供支持(例如文件上传)|
|FlashMapManager|存储输入输出的数据, 为多请求提供支持, 通常用在重定向中|

### 框架的配置
1. `DispatcherServlet`首先会在`WebApplicationContext`中寻找特殊的类, 若没有会使用[默认的配置](https://github.com/spring-projects/spring-framework/blob/master/spring-webmvc/src/main/resources/org/springframework/web/servlet/DispatcherServlet.properties)
2. 应用可以声明自己的配置类, 大多数的应用会在更高等级的配置中找到一个最优的开始位置. 

### 容器配置
1. 在Servlet3.0+中, 可以选择编程或者在`web.xml`文件中配置容器
2. 编程注册`DispatcherServlet`:
```Java
import org.springframework.web.WebApplicationInitializer;

public class MyWebApplicationInitializer implements WebApplicationInitializer {

    @Override
    public void onStartup(ServletContext container) {
        XmlWebApplicationContext appContext = new XmlWebApplicationContext();
        appContext.setConfigLocation("/WEB-INF/spring/dispatcher-config.xml");

        ServletRegistration.Dynamic registration = container.addServlet("dispatcher", new DispatcherServlet(appContext));
        registration.setLoadOnStartup(1);
        registration.addMapping("/");
    }
}
```
3. 继承`AbstractDispatcherServletInitializer`类并重写其中的方法可以很方便的配置`DispatcherServlet`, 并且还可以很方便的添加过滤器

### 程序流程
1. `DispatcherServlet`基本流程
    - 搜索`WebApplicationContext`, 并且绑定到 请求 以便于controller等的使用. 默认绑定的是`DispatcherServlet.WEB_APPLICATION_CONTEXT_ATTRIBUTE`
    - 绑定 `Local Resolver`到请求
    - 绑定 `Theme Resolver`到请求
    - 如果有文件, 请求会被包装成`MultipartHttpServletRequest`
    - 寻找恰当的`handler`, 如果找到了, 执行链会被执行, 准备模型或者渲染. 另一种选择是对于注释的解析器, 响应可能会被渲染代替返回一个视图.
    - 如果返回了一个模型(`model`), 视图(`view`)会被渲染. 当没有模型返回的时候, 视图不会被渲染, 请求可能已经响应了.
2. 当执行流程出现异常的时候, `HandlerExceptionResolver`会去抓取异常, 可以自定义不同异常的不同行为.
3. `DispatcherServlet`支持返回最后的修改日期, 当实现了`LastModified`接口时, `getLastModified(request)`会返回给客户端一个`long`型值. 主要用于判断资源是否过期.
4. 可以自定义多个独立的`DispatcherServlet`, 用`init-param`来初始化.
- | Parameter|Explanation|
    | :--:| :--:|
    | contextClass| 定义上下文, 默认是`XmlWebApplicationContext`|
    |contextConfigLocation| 指定上下文路径, 多个上下文用逗号隔开, 有重复的时候以最后一次为准|
    |namespace|`WebApplicationContext`的命名空间, 默认是`[servlet-name]-servlet`|

### 拦截器(Interception)
1. 拦截器需要实现`HandlerInterceptor`接口, 三个方法:
    - `preHandle(...)` : 在 `handler`处理之前执行
    - `postHandle(...)`: 在 `handler`处理之后执行
    - `afterCompletion(...)` : 在完整的请求结束之后执行
2. `preHandle(...)` : 返回`true`, 流程继续执行; 返回`false`, 流程结束
3. 有了`@ResponseBody`和`ResponseEntity`, 所以`postHandle()`比较少用

### 视图解析器(View Resolution)
1. `SpringMVC` 声明了`ViewResolver`和`View`接口用来渲染模型(`model`).
2. `InternalResourceViewResolver`: 支持`InternalResourceView`的方便的解析器, 同时支持`JstlView`和`TilesView`
3. `FreeMarkViewResolver`:支持`FreeMarkView`的解析器
4. 当解析链中有多个解析器时, 最好指定`order`, 值越高, 越晚执行.
#### 重定向(Redirect)
1. 有`redirect:`前缀的`view`名字会被重定向
    - `redirect:/abc/def`会使用当前的上下文
    - `redirect:http://myhost/abc/def`会使用新的上下文
2. 当控制器的方法有`@ResponseStatus`注释时, 注释的值会优先于`RedirectView`设置的值
#### 请求转发(Forward)
1. 有`forward`前缀的会被转发, 由`UrlBasedViewResolver`或者子类处理. 
2. 此动作会生成一个`InternalResourceView`来执行`RequestDispatcher.forward()`方法, 所以此前缀对`InternalResourceViewResolver`没用.
#### 内容转发(Content negotiation)
1. `ContentNegotiatingViewResolver` 不解析`View`而是寻找一个可以解析此类型视图的解析器

### 本地化(Locale)
1. 当请求到来时, `DispatcherServlet`会寻找一个本地化解析器.你可以通过`RequestContext.getLocale()`获得由本地化解析器解析的`Locale`
2. 通过设置拦截器, 也可以改变特定环境下的本地化解析器
#### 时区(TimeZone)
1. `LocaleContextResolver`继承了`LocaleResolver`接口, 丰富了内容, 包括了时区的内容
2. 可以通过`RequestContext.getTimeZone()`获得时区类(`TimeZone`)
#### 头信息解析器(Header Resolver)
1. 检查请求信息头中的`accept-language`信息, 初始化解析器
2. 不支持时区
#### Cookie Resolver
1. 本地化信息保存在Cookie中
#### 会话解析(Session Resolver)
1. 本地化信息保存在会话中
#### 本地化拦截器(Locale Interceptor)
1. 利用拦截器改变本地化方式
```xml
<!--定义国际化资源-->
    <bean id="messageSource" class="org.springframework.context.support.ResourceBundleMessageSource">
        <property name="basename" value="message"/>
    </bean>
    <!--声明 Cookie 本地解析器-->
    <bean id="localeResolver" class="org.springframework.web.servlet.i18n.CookieLocaleResolver">
        <property name="cookieName" value="language"/>
    </bean>
```
```html
<html>
<head>
    <title>Demo Page</title>
</head>
<body>
This is demo page!<br/>
sex:<spring:message code="sex"/>
<br/>
name:<spring:message code="name"/>
<br/>
<select id="language" onchange="changeLanguage(this)">
    <option id='zh' value="zh" >中文(简体)</option>
    <option id='en' value="en" >English</option>
</select>
<script>
    let arr = document.cookie.match(/[^\w]*language=(\w*)/);
    let lang = arr==null?null:document.getElementById(arr[1]);
    if(lang!=null){
        lang.selected = true;
    }

    function changeLanguage(obj) {
        document.cookie = 'language=' + obj.value + ';path=/';
        location.reload();
    }
</script>
</body>
</html>
```
### 主题(Themes)
1. 定义主题
```properties
back=/static/picture/cool.jpg
css=/static/css/cool.css
```
2. 解析主题
```java
@Bean("themeSource")
public ResourceBundleThemeSource theme() {
	ResourceBundleThemeSource rb = new ResourceBundleThemeSource();
	rb.setBasenamePrefix("theme/");

	return rb;
}

@Bean("themeResolver")
public CookieThemeResolver cts() {
	CookieThemeResolver ctr = new CookieThemeResolver();
	ctr.setCookieName("theme");
	ctr.setDefaultThemeName("cool");
	return ctr;
}
```
```xml
<link rel="stylesheet" href="<spring:theme code='css' text='theme.css'/>" type="text/css"/>
<img src="<spring:theme code='back' text='theme.back'/>" alt="picture" />
```
### 多文件解析(Multipart Resolver)
1. 可以用`commons-fileupload`包 也可以用 servlet3.0 自带的配置
```java
@Bean("multipartResolver")
public StandardServletMultipartResolver mul(){
	StandardServletMultipartResolver s = new StandardServletMultipartResolver();
	return s;
}
@PostMapping("upload")
@ResponseBody
public List<String> up(HttpServletRequest request) throws IOException, ServletException {
	List<String> result = new LinkedList<>();
	File dir = new File("h:/shuo");
	if (!dir.exists()) {
		if (!dir.mkdirs()) {
			result.add("Error");
			System.out.println(1);
			return result;
		}
		System.out.println(2);
	}

	for (Part part : request.getParts()) {
		String name = fileName(part.getHeader("Content-disposition"));
		if (name.length() > 0) {
			part.write(dir.getPath() + "/" + name);
			System.out.println(part.getHeader("Content-disposition"));
			result.add(fileName(part.getHeader("Content-disposition")) + " Done");
		}

	}
	return result;
}

private String fileName(String info) {
	String DEFAULT = "";
	System.out.println(info);
	Pattern p = Pattern.compile("[^\\w]*filename(['|\"].*?['|\"])?=['|\"](.*)?['|\"].*");
	Matcher m = p.matcher(info);
	if (m.find()) {
		String na = m.group(2);
		return na.length() > 0 ? na : DEFAULT;
	}
	return DEFAULT;
}
```
## 过滤器(Filter)
### 包装请求参数
1. `ServletRequest.getParameter*()`方法不能获取`get`和`post`方法之外的参数
2. 添加`HttpPutFormContentFilter`可以把参数包装, 从而使得`ServletRequest.getParamter*()`可以获得请求参数
### 转发头(Forwarded Headers)
1. 可以用`ForwardedHeaderFilter`过滤掉不可信的请求头
### 浅显的实体标签(Shallow ETag)
1. 可以添加`ShallowEtagHeaderFilter`过滤器来控制缓存, 生成文件的哈希码, 便于浏览器缓存的使用
### 访问控制(CORS)
1. 可以添加`CorsFilter`来进行访问控制
## 注释控制器
1. 简单的demo, 映射`/hello`请求, 接收一个模型, 返回视图的名字
```java
@Controller
public class HelloController {

    @GetMapping("/hello")
    public String handle(Model model) {
        model.addAttribute("message", "Hello World!");
        return "index";
    }
}
```
### 定义(Declaration)
1. 用`@Controller`/`@Component`/`@RestController`注释
2. `@RestController`结合了`@Controller`和`@ResponseBody`, 直接返回结果, 不会进行模型和视图渲染
#### AOP 代理
1. 当需要AOP代理时, 例如通过`@Transactional`注解, 此时需要明确指出是基于类的代理, `<tx:annotation-driven proxy-target-class="true"/>`
### 请求映射(Request Mapping)
1. 请求映射(`@RequestMapping`)是把请求映射到相应的控制器
2. `@RequestMapping` 有 五个快捷的 请求方法注解:
    - `@GetMapping`
    - `@PostMapping`
    - `@PutMapping`
    - `@DeleteMapping`
    - `@PatchMapping`
3. demo
```java
@RestController
@RequestMapping("/persons")
class PersonController {

    @GetMapping("/{id}")
    public Person getPerson(@PathVariable Long id) {
        // ...
    }

    @PostMapping
    @ResponseStatus(HttpStatus.CREATED)
    public void add(@RequestBody Person person) {
        // ...
    }
}
```
#### URI 模式(Pattern) 
1. 匹配规则:
    - `?` 匹配一个字符
    - `*` 匹配零个或者多个字符, 不包括`/`分隔符
    - `**`匹配领个或者多个字符, 包括`/`分隔符
2. 声明URI变量并且用`@PathVariable`取得声明的变量:
```java
@GetMapping("/{de}")
public String demo(@PathVariable String de) {
	return de;
}
```
```java
@Controller
@RequestMapping("/owners/{ownerId}")
public class OwnerController {

    @GetMapping("/pets/{petId}")
    public Pet findPet(@PathVariable Long ownerId, @PathVariable Long petId) {
        // ...
    }
}
```
3. 支持正则表达式提取
```java
@GetMapping("/{name:[a-z-]+}-{version:\\d\\.\\d\\.\\d}{ext:\\.[a-z]+}")
public void handle(@PathVariable String version, @PathVariable String ext) {
    // ...
}
```
4. 路径匹配支持占位符`${...}`, 需要`<context:property-placeholder location="classpath:cfg.properties"/>`
5. 模式匹配遵循**最精确匹配**原则
#### 后缀匹配(Suffix match)
1. `/demo`可以匹配`/demo.*`
2. 可以禁用后缀匹配
    - `useSuffixPatternMatching(false)`, see `PathMatchConfigurer`
    - `favorPathExtension(false)`, see `ContentNeogiationConfigurer`
3. 可以在使用`ContentNeogiationConfigurer`的`mediaTypes`属性明确的注册文件扩展名来使用文件扩展
#### 后缀匹配与反射文件下载攻击
1. 当请求URL的扩展名既不在白名单也不再注册列表中, 可以用`Content-Disposition:inline;filename=f.txt`来安全下载文件
2. 可以用`HttpMessageConverter `来明确的注册文件扩展名来避免添加`Conteent-Disposition`
#### 内容媒介类型匹配(Consumable media types)
1. 例子:`@PostMapping(path = "/pets", consumes = "application/json")`, 指定特定的请求内容媒介类型, 对应`Content-Type`
2. `MediaType`类中封装了常见的媒介类型
3. `!`取反, 除此之外 : `!text/html`
#### 可接受类型匹配(Producible media types)
1. 例子:`@GetMapping(path = "/pets/{petId}", produces = "application/json;charset=UTF-8")`, 指定特定的可接受的媒介类型, 对应`Accept`
#### 请求头与请求参数匹配
1. `@GetMapping(path = "/pets/{petId}", params = "myParam=myValue")` & `@GetMapping(path = "/pets", headers = "myHeader=myValue")`
2. 最好用`consumes`和`produces`而不是此项匹配
#### `HEAD`&`OPTIONS`
1. `@GetMapping`可以匹配`HEAD`请求
2. `@RequestMapping`可以匹配`OPTIONS`请求
### 方法句柄(Handler Methods)
1. `@RequestsMapping`方法句柄有灵活的标记并且可以方便的处理请求参数与返回值
#### 方法参数(Methods Arguments)
1. 支持的控制方法参数
|控制方法参数(Controller method argument) | 描述(Description)|
| :--: | :--:|
|WebRequest, NativeWebRequest|