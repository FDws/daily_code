## Nginx 
------
### 搭建动态URL代理服务器
1. 背景: 解决前端需要跨域请求信息或者从Https请求Http的问题:
2. 思路:
    - 把真正的Url放在头信息中 `X-Real-Url`
    - Nginx 提取头信息中的Url进行代理
3. 遇到的问题:
    1. Nginx代理域名的时候需要配置`resolver`, 即DNS服务器 
    2. 前端Axios发出的Ajax请求只能处理文本信息, 所以文件的下载需要利用`window.location`让浏览器处理
        - 当需要下载文件的时候把真正的Url封装在请求参数中, 文件名同理
        - 前端通过`window.location`触发文件下载, Nginx从请求参数中提取URL和文件名
        - 代理提取出的URL同时在响应头中加入`Content-Dispostion: attachment;filename=demo`信息
    3. Nginx运行时的用户必须具有相应的权限, 不然无法把下载的文件缓存, 导致前端只能下载几十KB的部分文件
4. 最终实现了前端Axios发送普通请求, 浏览器原生`Get`发送文件下载请求, 后端Nginx动态代理的功能
5. 使用此功能的[音乐试听工具](https://v4bug.com/tool/song)已经上线