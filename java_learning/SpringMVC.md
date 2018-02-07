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
### 模型方法(Model Method)
1. `@ModelAttribute`注解:
    - 注解方法, 则会在每个`Mapping`执行之前执行, 当方法有返回值的时候, 会把返回值加入模型属性中
    - 注解参数, 则会把参数加入模型属性中
### 数据绑定方法(Binder Method)
1. 使用`@InitBinder`注解方法来实现数据的绑定
2. 方法的参数除了`@ModelAttribute`之外同`@RequestMapping`方法参数相同
```java
@Controller
public class FormController {

    @InitBinder
    public void initBinder(WebDataBinder binder) {
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
        dateFormat.setLenient(false);
        binder.registerCustomEditor(Date.class, new CustomDateEditor(dateFormat, false));
    }

    // ...
}
```
3. `FormattingConversionService`类的子类可以直接进行绑定
```java
@Controller
public class FormController {

    @InitBinder
    protected void initBinder(WebDataBinder binder) {
        binder.addCustomFormatter(new DateFormatter("yyyy-MM-dd"));
    }

    // ...
}
```
### 控制增强(Controller Advice)
1. `@ControllerAdvice`注释的类会全局的增强`@Controller`类的功能
2. 全局的`@InitBinder`和`@ModelAttribute`会在非全局的控制器方法发之前调用, 而`@Exception`会在非全局的方法之后调用
3. 此注解默认会适用与所有的请求, 不过可以通过参数定制使用的请求
```java
// 适用所有 @RestController 注解的控制类
@ControllerAdvice(annotations = RestController.class)
public class ExampleAdvice1 {}

// 适用包下的所有控制类
@ControllerAdvice("org.example.controllers")
public class ExampleAdvice2 {}

// 适用于所有指定类以及子类
@ControllerAdvice(assignableTypes = {ControllerInterface.class, AbstractController.class})
public class ExampleAdvice3 {}
```
### URI 链接
1. `UriComponentsBuilder`&`UriComponents`用来生成URI
```java
UriComponents uriComponents = UriComponentsBuilder.fromUriString(
        "http://example.com/hotels/{hotel}/bookings/{booking}").build();

URI uri = uriComponents.expand("42", "21").encode().toUri();
```
2. `UriCOmponents`是不可变对象, `expand() encode()`返回的是新的对象
3. 在`Servlet`环境中, 可以使用`ServletUriComponentsBuilder`来复用请求路径的信息
#### 连接到控制方法
1. 可以构建对应特定控制方法的URI
```java
@Controller
@RequestMapping("/hotels/{hotel}")
public class BookingController {

    @GetMapping("/bookings/{booking}")
    public String getBooking(@PathVariable Long booking) {
        // ...
    }
}
// 构造链接到`getBooking`方法的URI
UriComponents uriComponents = MvcUriComponentsBuilder
    .fromMethodName(BookingController.class, "getBooking", 21).buildAndExpand(42);

URI uri = uriComponents.encode().toUri();
```
2. 通过`mock`来连接到控制方法, 确保方法返回值是非`final`对象
```java
UriComponents uriComponents = MvcUriComponentsBuilder
    .fromMethodCall(on(BookingController.class).getBooking(21)).buildAndExpand(42);

URI uri = uriComponents.encode().toUri();
```
### 在视图中创建链接
1. 利用spring标签
```jsp
<%@ taglib uri="http://www.springframework.org/tags" prefix="s" %>
...
<a href="${s:mvcUrl('PAC#getAddress').arg(0,'US').buildAndExpand('123')}">Get Address</a>
```
2. `A#b`: 
    - A : 类名称中的大写字母
    - b : 方法名称
## 异常处理(Exception Handling)
### 综述(Overview)
1. `HandlerExceptionResolver`接口实现类统一处理执行控制流程过程中出现的异常
### `@ExceptionHandler`
1. `HandlerExceptionResolver`和`SimpleMappingExceptionResolver`的实现类可以允许映射特定的异常到特定的视图. 然而当有`@ResponseBody`注释的时候, 使用`@ExceptionHandler`更为方便
```java
@Controller
public class SimpleController {

    // @RequestMapping methods omitted ...

    @ExceptionHandler(IOException.class)
    public ResponseEntity<String> handleIOException(IOException ex) {
        // prepare responseEntity
        return responseEntity;
    }

}
```
2. `@ExceptionHandler`注释会把所有的声明异常放在一个列表中, 当抛出的异常与列表中的异常匹配时, 会调用响应的方法来处理
3. 注释的方法参数类似`@RequestMapping`, 返回值也相似, `String`对应视图名等
### 框架异常(Framework Exceptions) 
1. `Springmvc`把相应的异常转换为对应的状态吗, 可以在`web.xml`文件中配置响应页面
```xml
<error>
    <error-code>404</error-code>
    <location>/404.jsp</location>
</error>
```
2. 对应关系
    | 异常 | 状态码 |
    | :--: | :--:|
    | BindException | 404(Bad Request) |
    | ConversionNotSupportedException| 500(Internal Server Error) |
    | HttpMediaTypeNotAcceptableException | 406(Not Acceptable) |
    | HttpMediaTypeNotSupportException | 415(Unsupported Media Type) |
    | HttpMessageNotReadableException | 400(Bad Request) |
    | HttpMessageNotWritableException | 500(internal Server Error) |
    | HttpRequestMethodNotSupportedException | 405 (Method Not allowed ) | 
    | MethodArgumentNotValidException | 400(Bad Request) |
    | MissingPathVariableException | 500|
    | MissingServletRequestParameterException | 400|
    | MissingServletRequestPartException | 400|
    | NoHandlerFoundException | 404 (Not found) |
    | NoSuchRequestHandlingMethodException | 404|
    | TypeMismatchException | 400 |
### REST API Exceptions
1. `@RestController`可以使用`@ExceptionHandler`注解的方法来返回一个包含错误信息和状态码的`ResponseEntity`
2. 通过继承`ResponseEntityExceptionHandler`来实现一个自己的异常处理类, 加入`@RestController`, 实现当抛出特定异常的时候返回自定义的`ResponseEntity`
### 容器错误页
1. 可以在`web.xml`文件中配置错误对应的页面
2. 状态码和错误信息写入了`request`, 可以取出显示
    - 状态码 : `javax.servlet.error.status_code`
    - 错误信息 : `javax.servler.error.message`
## 异步请求(Async Requests)
### 延迟结果(DeferrResult)
1. 示例:
```java
@GetMapping("/async")
@ResponseBody
public DeferredResult<String> asy(){
	DeferredResult<String> deferredResult = new DeferredResult<>();
	new Thread(() -> {
		try {
			TimeUnit.SECONDS.sleep(2);
			deferredResult.setResult("demo");
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}).start();
	return deferredResult;
}
```
### Callable
1. 控制方法也可以把返回结果包装在`Callable`中
```java
@GetMapping("/callable")
@ResponseBody
public Callable<String> ca(){
	return () -> {
		TimeUnit.SECONDS.sleep(2);
		return "callable";
	};
}
```
### 异步请求流程(Processing)
1. 通过调用`request.startAsync()`使`ServletRequest`被放入异步模式, 此模式下, `Servlet`和`Filter`退出时响应流依然存在.
2. `request.startAsync()`返回`AsyncContext`, 它会在异步流程中被其他的控制流使用, `AsyncContext`和容器上下文使用方法基本一致
3. `ServletRequest`提供了获取当前分发类型的方法, 可以用来区分原始请求/异步分发/转发或者其他的分发类型
#### `DeferredResult`流程
1. 控制器返回一个`DeferredResult`并且存储在队列或者列表中
2. `SpringMVC`调用`request.startAsync()`
3. `DispatcherServlet`和所有的过滤器退出请求流程, 响应流仍然打开着
4. 应用把`DeferredResult`放入其他的线程, `Springmvc`分发器分发请求到`Servlet`容器
5. `DispatcherServelet`重新被调用, 去处理异步产生的返回值
#### `Callable`流程
1. 控制器返回一个`Callable`
2. `SpringMVC`调用`request.startAsync()`方法并且提交`Callable`对象到独立线程的任务执行器(TaskExecutor)
3. `DispatcherServlet`和所有的过滤器退出请求流程, 响应流仍然打开着
4. 最终, `Callable`产生结果`SpringMVC`分发结果到容器, 最终完成流程
5. `DispatcherServlet`重新被调用处理异步请求的结果
### 异常处理(Exception handling)
1. 使用`DeferredResult`时 , 可以选择调用`setResult`或`setErrorResult`, 这两种方法都会使分发器把结果提供给容器来完成流程, 然后就可以当作普通的异常来处理, 例如利用`@ExceptionHandler`
2. `Callable`类似与`DeferredResult`, 不同之处在于异常是返回的还是抛出的
### 拦截器(Interception)
1. `AsyncHandlerInterceptor`可以在请求开始异步流程的时候调用`afterConcurrentHandlingStarted`来代替`HandlerInterceptor`的`postHandler`和`afterCompletion`
2. 可以注册`CallableProcessingInterceptor`或者`DeferredResultProcessingInterceptor`来更深入的和异步流程集成
3. `DeferredResult`提供了`onTimeOut(Runnable)`和`onCompletion(Runnable)`方法来回调; `Callable`可以用`WebAsyncTask`代替, 然后就可以获得超时和完成的方法回调
### 响应流(Streaming Response)
1. `ResponseBodyEmitter`可以在一个响应流中多次写入对象, 对象会被`HttpMessageConverter`序列化到响应流中
2. `ResponseBodyEmitter`同样可以用在`ResponsseEntity`中
### `Server-Sent Events`
1. `ResponseBodyEmitter`的子类`SseEmitter`用来提供`Server-Sent`服务
```java
GetMapping(value = "/sseinfo", produces = MediaType.TEXT_EVENT_STREAM_VALUE)
public SseEmitter sse() {
	SseEmitter sseEmitter = new SseEmitter();
	new Thread(() -> {
		try {
			for (int i = 0; i < 10; i++) {
				sseEmitter.send("info " + i);
				TimeUnit.SECONDS.sleep(1);
			}
			sseEmitter.complete();
		} catch (InterruptedException | IOException e) {
			e.printStackTrace();
		}
	}).start();
	System.out.println("Main thread return");
	return sseEmitter;
}
```
```js
let text = document.getElementById("tex");
function sse() {
    let source = new EventSource("/sseinfo");
    source.addEventListener('open', function () {
        text.value = text.value + "\n" + "Open succ";
    });
    source.addEventListener('error', function () {
        text.value = text.value + '\n' + "Has Error";
        source.close();
    });
    source.addEventListener('message', function (event) {
        text.value = text.value + '\n' + event.data;
    });
}
```
2. `IE`浏览器不支持, 此种需求可以用`WebSocket`实现
### 二进制内容
1. `StreamResponseBody`提供了返回二进制内容的异步方法
```java
@GetMapping("/download")
public StreamingResponseBody handle() {
    return new StreamingResponseBody() {
        @Override
        public void writeTo(OutputStream outputStream) throws IOException {
            // write...
        }
    };
}
```
2. `StreamResponseBody`也可以作为`Response Entity`的内容部分
### 异步配置
1. `Servlet`版本`>=3.0`
2. 相应的`Servlet`和`Filter`开启异步支持
3. 过滤器指定对应的分发类型`DispatcherType`
4. `<mvc:annotation>`有子属性`<mvc:async-support>`配置异步参数
5. `WebMvcConfigure`有`configureAsyncSupport`配置异步参数
## 跨域资源分享(CORS)
1. 浏览器禁止使用`AJAX`来请求非同源的信息
2. `CORS`允许指定那些跨域请求是合法的
3. `SpringMVC`内嵌了对`CORS`的支持
    - 当请求映射对应处理器后, `HandlerMapping`会检查`CORS`配置, 采取进一步的动作
    - 预请求(`Preflight`)会被直接处理, 简单请求会被拦截, 验证, 添加`CORS`相应头信息
4. 为了实现跨域请求, 必须明确的声明`CORS`配置
### `@CrossOrigin`
1. 注释控制方法
```java
@RestController
@RequestMapping("/account")
public class AccountController {

    @CrossOrigin
    @GetMapping("/{id}")
    public Account retrieve(@PathVariable Long id) {
        // ...
    }

    @DeleteMapping("/{id}")
    public void remove(@PathVariable Long id) {
        // ...
    }
}
```
2. 支持注释在控制方法或者类
### 全局配置(Global Config)
1. 默认配置
    - 允许所有的源
    - 允许所有的头信息
    - 允许`GET　HEAD　POST`方法.
    - `allowedCredentials` 不被支持
    - 最大时间 30 分钟
2. Java Config
```java
@Configuration
@EnableWebMvc
public class WebConfig implements WebMvcConfigurer {

    @Override
    public void addCorsMappings(CorsRegistry registry) {

        registry.addMapping("/api/**")
            .allowedOrigins("http://domain2.com")
            .allowedMethods("PUT", "DELETE")
            .allowedHeaders("header1", "header2", "header3")
            .exposedHeaders("header1", "header2")
            .allowCredentials(true).maxAge(3600);

        // Add more mappings...
    }
}
```
3. XML Config
```xml
<mvc:cors>

    <mvc:mapping path="/api/**"
        allowed-origins="http://domain1.com, http://domain2.com"
        allowed-methods="GET, PUT"
        allowed-headers="header1, header2, header3"
        exposed-headers="header1, header2" allow-credentials="true"
        max-age="123" />

    <mvc:mapping path="/resources/**"
        allowed-origins="http://domain1.com" />

</mvc:cors>
```
### `CORS`过滤器
```java
CorsConfiguration config = new CorsConfiguration();

// Possibly...
// config.applyPermitDefaultValues()

config.setAllowCredentials(true);
config.addAllowedOrigin("http://domain1.com");
config.addAllowedHeader("");
config.addAllowedMethod("");

UrlBasedCorsConfigurationSource source = new UrlBasedCorsConfigurationSource();
source.registerCorsConfiguration("/**", config);

CorsFilter filter = new CorsFilter(source);
```
## 浏览器缓存(Http Caching)
### `Cache-Control`
1. SpringMVC 使用API配置:`setCachePeriod(int seconds)`
    - -1 : 不会生成`Cache-Control`响应头
    - 0 : 使用`Cache-Control: no-store`禁用缓存
    - n>0 : 设置缓存失效时间
2. `CacheControl`对象可以方便的构建`Cache-Control`指令
```java
// Cache for an hour - "Cache-Control: max-age=3600"
CacheControl ccCacheOneHour = CacheControl.maxAge(1, TimeUnit.HOURS);

// Prevent caching - "Cache-Control: no-store"
CacheControl ccNoStore = CacheControl.noStore();

// Cache for ten days in public and private caches,
// public caches should not transform the response
// "Cache-Control: max-age=864000, public, no-transform"
CacheControl ccCustom = CacheControl.maxAge(10, TimeUnit.DAYS)
                                    .noTransform().cachePublic();
```
### `Static resources`
1. 静态资源应该被缓存以获得最佳的性能
```xml
<mvc:resources mapping="/static/**" location="/static/">
        <mvc:cache-control max-age="36000" cache-public="true"/>
    </mvc:resources>
```
or
```java
@Override
public void addResourceHandlers(ResourceHandlerRegistry registry) {
    registry.addResourceHandler("/resources/**")
            .addResourceLocations("/public-resources/")
            .setCacheControl(CacheControl.maxAge(1, TimeUnit.HOURS).cachePublic());
}
```
### `@Controller caching`
1. 可以在控制方法中返回`ResponseEntity`实现缓存
```java
@GetMapping("/book/{id}")
public ResponseEntity<Book> showBook(@PathVariable Long id) {

Book book = findBook(id);
String version = book.getVersion();

return ResponseEntity
            .ok()
            .cacheControl(CacheControl.maxAge(30, TimeUnit.DAYS))
            .eTag(version) // lastModified is also available
            .body(book);
}
```
2. `RequestMapping`也可以支持缓存, 有两个要点
    - `request.checkNotModified()`
    - `return null`
```java
@RequestMapping
public String myHandleMethod(WebRequest webRequest, Model model) {

    long lastModified = // 1. application-specific calculation

    if (request.checkNotModified(lastModified)) {
        // 2. shortcut exit - no further processing necessary
        return null;
    }

    // 3. or otherwise further request processing, actually preparing content
    model.addAttribute(...);
    return "myViewName";
}
```
3. 共有三种检查方法
    - `checkNoModified(lastModified)`
    - `checkNoModified(eTag)`
    - `checkNoModified(eTag, lastModified)`
### ETag Filter
1. `ShallowEtagHeaderFilter`过滤器可以自动添加头信息并且进行比对
2. `writeWeakETag`方法控制是否是严格的比对
## MVC Config
### 开启配置
1. annotation
```java
@Configuration
@EnableWebMvc
public class WebConfig {
}
```
2. XML
```xml
<mvc:annotation-driven/>
```
### 配置接口
1. 
```java
@Configuration
@EnableMvc
public class WebConfig implements WebMvcConfigure {}
```
2. 
```java
@Configuration
public class WebConfig extends WebMvcConfigurationSupport{}
```
### 类型转换(Type conversion)
1. 
```java
@Configuration
@EnableWebMvc
public class WebConfig implements WebMvcConfigurer {

    @Override
    public void addFormatters(FormatterRegistry registry) {
        // ...
    }
}
```
or
```xml
<mvc:annotation-driven conversion-service="conversionService"/>

    <bean id="conversionService"
            class="org.springframework.format.support.FormattingConversionServiceFactoryBean">
        <property name="converters">
            <set>
                <bean class="org.example.MyConverter"/>
            </set>
        </property>
        <property name="formatters">
            <set>
                <bean class="org.example.MyFormatter"/>
                <bean class="org.example.MyAnnotationFormatterFactory"/>
            </set>
        </property>
        <property name="formatterRegistrars">
            <set>
                <bean class="org.example.MyFormatterRegistrar"/>
            </set>
        </property>
    </bean>
```
### 拦截器(Interceptors)
1. 
```java
@Configuration
@EnableWebMvc
public class WebConfig implements WebMvcConfigurer {

    @Override
    public void addInterceptors(InterceptorRegistry registry) {
        registry.addInterceptor(new LocaleInterceptor());
        registry.addInterceptor(new ThemeInterceptor()).addPathPatterns("/**").excludePathPatterns("/admin/**");
        registry.addInterceptor(new SecurityInterceptor()).addPathPatterns("/secure/*");
    }
}
```
or
```xml
<mvc:interceptors>
    <bean class="org.springframework.web.servlet.i18n.LocaleChangeInterceptor"/>
    <mvc:interceptor>
        <mvc:mapping path="/**"/>
        <mvc:exclude-mapping path="/admin/**"/>
        <bean class="org.springframework.web.servlet.theme.ThemeChangeInterceptor"/>
    </mvc:interceptor>
    <mvc:interceptor>
        <mvc:mapping path="/secure/*"/>
        <bean class="org.example.SecurityInterceptor"/>
    </mvc:interceptor>
</mvc:interceptors>
```
### 内容类型(Content-Types)
1. 可以配置如何确定请求内容类型, 例如通过后缀/查询参数/头信息等
2. 默认首先匹配后缀, 然后是`Accept`头信息
3. 手动配置
```java
@Configuration
@EnableWebMvc
public class WebConfig implements WebMvcConfigurer {

    @Override
    public void configureContentNegotiation(ContentNegotiationConfigurer configurer) {
        configurer.mediaType("json", MediaType.APPLICATION_JSON);
    }
}
```
or
```xml
<mvc:annotation-driven content-negotiation-manager="contentNegotiationManager"/>

<bean id="contentNegotiationManager" class="org.springframework.web.accept.ContentNegotiationManagerFactoryBean">
    <property name="mediaTypes">
        <value>
            json=application/json
            xml=application/xml
        </value>
    </property>
</bean>
```
### 信息转换
1. 重写`configureMessageConverters`方法发替换默认的转换器
2. 重写`extendMessageConverters`方法添加自定义转换器
```java
// 添加 JSON 和 XML 转换器
@Configuration
@EnableWebMvc
public class WebConfiguration implements WebMvcConfigurer {

    @Override
    public void configureMessageConverters(List<HttpMessageConverter<?>> converters) {
        Jackson2ObjectMapperBuilder builder = new Jackson2ObjectMapperBuilder()
                .indentOutput(true)
                .dateFormat(new SimpleDateFormat("yyyy-MM-dd"))
                .modulesToInstall(new ParameterNamesModule());
        converters.add(new MappingJackson2HttpMessageConverter(builder.build()));
        converters.add(new MappingJackson2XmlHttpMessageConverter(builder.xml().build()));
    }
}
```
or
```xml
<mvc:annotation-driven>
    <mvc:message-converters>
        <bean class="org.springframework.http.converter.json.MappingJackson2HttpMessageConverter">
            <property name="objectMapper" ref="objectMapper"/>
        </bean>
        <bean class="org.springframework.http.converter.xml.MappingJackson2XmlHttpMessageConverter">
            <property name="objectMapper" ref="xmlMapper"/>
        </bean>
    </mvc:message-converters>
</mvc:annotation-driven>

<bean id="objectMapper" class="org.springframework.http.converter.json.Jackson2ObjectMapperFactoryBean"
      p:indentOutput="true"
      p:simpleDateFormat="yyyy-MM-dd"
      p:modulesToInstall="com.fasterxml.jackson.module.paramnames.ParameterNamesModule"/>

<bean id="xmlMapper" parent="objectMapper" p:createXmlMapper="true"/>
```
### 视图控制
1. 配置直接返回的视图
```java
@Configuration
@EnableWebMvc
public class WebConfig implements WebMvcConfigurer {

    @Override
    public void addViewControllers(ViewControllerRegistry registry) {
        registry.addViewController("/").setViewName("home");
    }
}
```
or
```xml
<mvc:view-controller path="/" view-name="home"/>
```
### 视图处理器(View Resolvers)
1. 示例: 根据内容协商使用 FreeMarker HTML templates 和 Jackson 作为JSON渲染的默认视图
```java
@Configuration
@EnableWebMvc
public class WebConfig implements WebMvcConfigurer {

    @Override
    public void configureViewResolvers(ViewResolverRegistry registry) {
        registry.enableContentNegotiation(new MappingJackson2JsonView());
        registry.jsp();
    }
}
```
or
```xml
<mvc:view-resolvers>
    <mvc:content-negotiation>
        <mvc:default-views>
            <bean class="org.springframework.web.servlet.view.json.MappingJackson2JsonView"/>
        </mvc:default-views>
    </mvc:content-negotiation>
    <mvc:jsp/>
</mvc:view-resolvers>
```
2. FreeMarker, Tiles, Groovy MarkUp等也需要配置底层的视图
```xml
<mvc:view-resolvers>
    <mvc:content-negotiation>
        <mvc:default-views>
            <bean class="org.springframework.web.servlet.view.json.MappingJackson2JsonView"/>
        </mvc:default-views>
    </mvc:content-negotiation>
    <mvc:freemarker cache="false"/>
</mvc:view-resolvers>

<mvc:freemarker-configurer>
    <mvc:template-loader-path location="/freemarker"/>
</mvc:freemarker-configurer>
```
or
```java
@Configuration
@EnableWebMvc
public class WebConfig implements WebMvcConfigurer {

    @Override
    public void configureViewResolvers(ViewResolverRegistry registry) {
        registry.enableContentNegotiation(new MappingJackson2JsonView());
        registry.freeMarker().cache(false);
    }

    @Bean
    public FreeMarkerConfigurer freeMarkerConfigurer() {
        FreeMarkerConfigurer configurer = new FreeMarkerConfigurer();
        configurer.setTemplateLoaderPath("/WEB-INF/");
        return configurer;
    }
}
```
### 静态资源
```java
@Configuration
@EnableWebMvc
public class WebConfig implements WebMvcConfigurer {

    @Override
    public void addResourceHandlers(ResourceHandlerRegistry registry) {
        registry.addResourceHandler("/resources/**")
            .addResourceLocations("/public", "classpath:/static/")
            .setCachePeriod(31556926);
    }
}
```
or
```xml
<mvc:resources mapping="/resources/**"
    location="/public, classpath:/static/"
    cache-period="31556926" />
```
1. `VersionResourceResolver`用来实现静态资源的版本控制
```java
@Configuration
@EnableWebMvc
public class WebConfig implements WebMvcConfigurer {

    @Override
    public void addResourceHandlers(ResourceHandlerRegistry registry) {
        registry.addResourceHandler("/resources/**")
                .addResourceLocations("/public/")
                .resourceChain(true)
                .addResolver(new VersionResourceResolver().addContentVersionStrategy("/**"));
    }
}
```
or
```xml
<mvc:resources mapping="/resources/**" location="/public/">
    <mvc:resource-chain>
        <mvc:resource-cache/>
        <mvc:resolvers>
            <mvc:version-resolver>
                <mvc:content-version-strategy patterns="/**"/>
            </mvc:version-resolver>
        </mvc:resolvers>
    </mvc:resource-chain>
</mvc:resources>
```
### Default Servlet
1. 静态资源需要`DefaultServletHttpRequestHandler`, 映射为`/**`, 是最低的映射权限, `order`为`Integer.MAX_VALUE`
```java
@Configuration
@EnableWebMvc
public class WebConfig implements WebMvcConfigurer {

    @Override
    public void configureDefaultServletHandling(DefaultServletHandlerConfigurer configurer) {
        configurer.enable("myCustomDefaultServlet");
    }

}
```
or
```xml
<mvc:default-servlet-handler default-servlet-name="myCustomDefaultServlet"/>
```
2. 默认名称是`default`, 当更改了名称时, 必须显示的指定默认`Servlet`名称
### 路径匹配(Path Matching)
1. 可以自定义路径匹配的参数
```java
@Configuration
@EnableWebMvc
public class WebConfig implements WebMvcConfigurer {

    @Override
    public void configurePathMatch(PathMatchConfigurer configurer) {
        configurer
            .setUseSuffixPatternMatch(true)
            .setUseTrailingSlashMatch(false)
            .setUseRegisteredSuffixPatternMatch(true)
            .setPathMatcher(antPathMatcher())
            .setUrlPathHelper(urlPathHelper());
    }

    @Bean
    public UrlPathHelper urlPathHelper() {
        //...
    }

    @Bean
    public PathMatcher antPathMatcher() {
        //...
    }

}
```
or
```xml
<mvc:annotation-driven>
    <mvc:path-matching
        suffix-pattern="true"
        trailing-slash="false"
        registered-suffixes-only="true"
        path-helper="pathHelper"
        path-matcher="pathMatcher"/>
</mvc:annotation-driven>

<bean id="pathHelper" class="org.example.app.MyPathHelper"/>
<bean id="pathMatcher" class="org.example.app.MyPathMatcher"/>
```
