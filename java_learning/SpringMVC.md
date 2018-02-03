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
    | 控制方法参数(Controller method argument) | 描述(Description) |
    | :--: | :--: |
    |WebRequest, NativeWebRequest | 不用直接操作`Servlet API`就可以操作请求参数, 请求或者会话的属性|
    | javax.servlet.ServletRequest javax.servlet.ServletResponse|可以直接选择特殊的请求或者响应类型, 例如`HTTPServletRequest`/`MultipartRequest`/`MultipartHttpServletRequest`|
    | javax.servlet.http.HttpSession|强制一个会话的存在. 获得会话的过程不是线程安全的, 可以考虑设置`RequestMappingHandlerAdapter`的`synchronizeOnSession`为`true`|
    | javax.servlet.http.PushBuilder | 符合`HTTP/2`标准的`servlet`4.0 API, 不支持`HTTP/2`的请求此属性为`null`|
    | HTTP Method | 请求的方法|
    | java.util.Locale | 请求的本地环境对象|
    | ZoneId TimeZone | 本地化的识别对象 |
    | InputStream Reader | 请求的输入流 |
    | OutputStream Writer | 响应的输出流 |
    | `@PathVariable` | 从请求的URI中获取定义的信息|
    | `@MatrixVariable` | 获取请求参数|
    | `@RequestParam` | 获取查询参数 |
    | `@RequestHeader`| 获取请求头内容 |
    | `@CookieValue`| 获取Cookie中的内容 |
    | `@RequestBody`| 把请求参数封装成对象 |
    | `HttpEntity` | 把请求头和请求内容封装 |
    | `RequestPart` | 获取`multipart/form-data`内容|
    | `java.util.Map, org.springframework.ui.Model, org.springframework.ui.ModelMap` | 获取 模型(`model`)|
    | `RedirectAttributes` | 重定向时参数的处理|
    | `@ModelAttribute` | 获取已经存在的模型的属性 |
    | Errors, BindingResult | 从校验器或者数据绑定的对象获得错误信息|
    | `SessionStatus + class-level @SessionAttributes` | 获取会话状态与属性 |
    | `UriComponentsBuilder` | Uri生成器 |
    | `@SessionAttribute` | 会话属性 |
    | `@RequestAttribute` | 请求属性|
    | Any other argument | 其他的属性会被封装成`RequestParameter`或者`ModelAttribute`|
#### 返回值(Return Value)
1. 支持的返回值控制    
    | 返回值 | 描述|
    | :--: | :--: |
    | `@ReturnBody` | 把方法的返回值直接写入输出流 |
    | `HttpEntity<B>, ResponseEntity<B>` | 控制返回的内容和返回头等信息 |
    | `HttpHeaders` | 只返回头信息, 没有内容 |
    | `String` | 返回视图的名称, 进而渲染视图返回 |
    | `View` | 返回确定的视图 |
    | `java.util.Map, org.springframework.ui.Model` | 返回模型内容并且通过`RequestToViewNameTranslator`找到视图名称 |
    | `@ModelAttribute` | 为模型添加属性, 并且通过`RequestToViewNameTranslator`找到相应的视图名称 | 
    | `ModelAndView ` | 返回指定的模型和视图名称 |
    | `void` | 返回为`void`或者`null`的时候, 程序会当作已经处理过响应内容, 或者没有内容返回, 或者返回默认的视图|
    | `Callable<V>` | 在`SpringMVC`主线程中返回一个异步调用 |
    | `DeferredResult<V>`| 在任意线程中返回一个事件或者回调函数|
    | `ListenableFuture<V>, java.util.concurrent.CompletionStage<V>, java.util.concurrent.CompletableFuture<V>` | `DeferredResult<V>`的另一种更便利的选择 |
    | `ResponseBodyEmitter, SseEmitter` | 生成一个异步的响应流|
    | `StreamingResponseBody` | 异步写入响应流中|
    | `Reactive types — Reactor, RxJava, or others via ReactiveAdapterRegistry` | 对于多值(Multi-value)的流来说是`Deferred Result<V>`的另一种选择|
    | Any other return value | 对于其他的`String/void`来说, 他们被当作视图名称返回, 或者被当作模型的属性|
#### 类型转换
1. 请求参数通常是`String`类型的, 对于简单的类型(int, lang, Date等)会进行类型转换
2. 可以通过`WebDataBinder`来自定义转换
#### `@ModelAttribute`
1. 对于`public String processSubmit(@ModelAttribute Pet pet) { }`的定义, `Pet`的初始化遵循以下顺序
    - 模型中已经有的属性直接赋值
    - 从会话中获得
    - 从`URI Path`变量中获得
    - 默认的构造函数
    - 有参数的构造函数, 参数从`ServletRequest`中获得
2. 数据绑定(`DataBinding`)可能会出错, 所以应该在`@ModelAttribute`之后添加参数(`BindingResult`)
```java
@PostMapping("/owners/{ownerId}/pets/{petId}/edit")
public String processSubmit(@ModelAttribute("pet") Pet pet, BindingResult result) {
    if (result.hasErrors()) {
        return "petForm";
    }
    // ...
}
```
3. `@ModelAttribute`注解的方法会在每一个`Mapping`方法之前调用
4. 当不需要数据绑定的时候可以`@ModelAttribute(binding=false)`
#### `@SessionAttributes`
1. 类级别的注解
2. 将参数存储在会话中
3. 无法在第一次请求的函数中获得此值
#### `@SessionAttribute`
1. 获得此前存储在会话中的值
#### `@RequestAttribute`
1. 用来获取以前存储在请求中的属性, 例如在拦截器或者过滤器中添加的属性
#### 重定向属性(Redirect Attribute)
1. 在URI中定义的变量在重定向时可以使
```java
@GetMapping("/demo/{dog}")
public String redic(){
    return "redirect:/demo/{dog}";
}
```
2. 另一种保存重定向参数的方式是`flash attribute`, 此方法把参数保存在会话中
#### Flash Attributes
1. Flash Attributes 提供了在两个请求之间保存属性的方法, 通常在重定向时需要
2. 在控制方法的参数列表中声明`RedirectAttribute`就可以存储属性, 在重定向的方法中可以从模型中取出使用
#### 多部件支持(Multipart)
1. 在声明过`multipartResolver`之后, `POST`请求中`multipart/form-data`会被解析, 然后就可以看成平常的请求参数
2. 上传文件示例:
```java
@PostMapping("upload")
@ResponseBody
public List<String> up(HttpServletRequest request) throws IOException, ServletException {
	List<String> result = new LinkedList<>();
	File dir = new File("h:/shuo");
	if (!dir.exists()) {
		if (!dir.mkdirs()) {
			result.add("Error");
			return result;
		}
	}

	for (Part part : request.getParts()) {
                //fileName : 从头信息中通过正则表达式提取文件名
		String name = fileName(part.getHeader("Content-disposition"));
		if (name.length() > 0) {
			part.write(dir.getPath() + "/" + name);
			result.add(fileName(part.getHeader("Content-disposition")) + " Done");
		}

	}
	return result;
}
```
3. 多部件也可以进行数据绑定
```java
class MyForm {

    private String name;

    private MultipartFile file;

    // ...

}

@Controller
public class FileUploadController {

    @PostMapping("/form")
    public String handleFormUpload(MyForm form, BindingResult errors) {

        if (!form.getFile().isEmpty()) {
            byte[] bytes = form.getFile().getBytes();
            // store the bytes somewhere
            return "redirect:uploadSuccess";
        }

        return "redirect:uploadFailure";
    }

}
```
#### `@RequestBody`
1. 可以用此注释来反序列化请求体, 封装为对象
#### `HttpEntity`
1. 大体上与`@RequestBody`相同, 同时包括头信息
```java
@PostMapping("/accounts")
public void handle(HttpEntity<Account> entity) {
    // ...
}
```
#### `@ResponseBody`
1. 此注释标记函数的返回值直接写入响应流
2. `@RestController` 可以看作`@Controller` + `@ResponseBody`

#### `ResponseEntity`
1. 包含了头信息的`@ResponseBody`
#### `JackSon Json`
1. `SpringMVC`内在支持`Jackson`的序列化, `@ResponseBody`的结果会被序列化
2. `@JsonView`控制序列化区域
3. 控制视图渲染时的序列化
```java
@Controller
public class UserController extends AbstractController {

    @GetMapping("/user")
    public String getUser(Model model) {
        model.addAttribute("user", new User("eric", "7!jd#h23"));
        model.addAttribute(JsonView.class.getName(), User.WithoutPasswordView.class);
        return "userView";
    }
}
```
4. `Jackson JSONP`:
    - 通过继承`AbstractJsonpResponseBodyAdvice`类并添加`@ControllerAdvice`来提供`JSONP`解析支持
    - ```java
        @ControllerAdvice
        public class JsonpAdvice extends AbstractJsonpResponseBodyAdvice {
        
            public JsonpAdvice() {
                super("callback");
            }
        }
        ```